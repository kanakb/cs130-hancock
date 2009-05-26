#include "stdafx.h"
#include "MPane.h"

MPane::MPane()
{
}

MPane::~MPane()
{
	if(!m_masterMap.empty())					// if the map isnt empty delete its current entries
	{
		map<int,set<string>*>::iterator mit;	// declare a map interator for the master map
		for(mit = m_masterMap.begin(); mit != m_masterMap.end(); mit++)
		{
			if(mit->second != NULL)		// ensure we do not accidentally delete a null pointer
				delete mit->second;
		}
		m_masterMap.clear();
	}

	if(!m_filteredMap.empty())
	{
		m_filteredMap.clear();
	}

	if(!m_directoryListing.empty())
	{
		m_directoryListing.clear();
	}
}

// addFlag adds the flag specified by type to the set of filters used to create filteredMap
// it adds the flag to the set and then adds that set to the filteredMap if it exists in masterMap
void MPane::addFlag(int type)
{
	m_flags.insert(type);	// insert the new filter flag into the set of filers
	updateFilteredMap();	// update the filtered map to include the newly added flag
}

// removeFlag removes the flag specified by type to the set of filters used to create filteredMap
// it removes the flag from the set and then removes that set from the filteredMap if it exists in filteredMap
void MPane::removeFlag(int type)
{
	m_flags.erase(type);
	map<int,set<string>*>::iterator fit;	// declare a map interator for the filtered map
	fit = m_filteredMap.find(type);			// search for key in filtered map
	if(fit != m_filteredMap.end())			// if the key is found, remove it
	{
		fit->second = NULL;					// set the value (set<string>*) pointer to NULL
											// so that the pointer is not accidentally deleted
											// since it points directly to the value set in the master map

		m_filteredMap.erase(fit);			// remove the key-value pair associated with the key: type
	}
}

// AssocToDir takes a string path to a directory, reads the directory, and calls AssocToDirInternal to
// populate the master map with the contents of that directory
void MPane::AssocToDir(string path)
{
	m_cnfFolderCreated = false;
	m_working_dir = path + "\\";

	/* If this test succeeds, then this is not the first call to AssocToDir.
	 * Therefore we must clear the current map of files that we have before
	 * associating the map to a new directory.
	 */

	if(!m_masterMap.empty())					// if the map isnt empty delete its current entries
	{
		map<int,set<string>*>::iterator mit;	// declare a map interator for the master map
		for(mit = m_masterMap.begin(); mit != m_masterMap.end(); mit++)
		{
			if(mit->second != NULL)		// ensure we do not accidentally delete a null pointer
				delete mit->second;
		}
		m_masterMap.clear();
	}

	if(!m_filteredMap.empty())
	{
		m_filteredMap.clear();
	}

	if(!m_directoryListing.empty())
	{
		m_directoryListing.clear();
	}

	// Begin populating master map

	AssocToDirInternal(path+"\\cnf_files","conf");		// first pass through directory we look for *.cnf files
										// these files tell us what type of file * is (ie Malware, Goodware, etc...)
	AssocToDirInternal(path,"*");		// second pass through we add everything else to the master map

	validateMap();						// now that we have built a map and directory listing, validate the map

	updateFilteredMap();				// update the filtered map in case there are flags to filter by
}

map<int,set<string>*>* MPane::getMasterList()
{
	return &m_masterMap;
}

// AssocToDirInternal is the function that actually does the work of going through the directory
// It searches the directory specified by path for all files with extension speficied by extension
void MPane::AssocToDirInternal(string path, string extension)
{
	
	
	struct _finddatai64_t data;
	// First create the filename that will be use to initialize the find.
	// "*.*" are wild card characters that tells the find function to return a
	// list of all the files and directories.  You can limit this if you wish
	// to just file with specific extensions, for example "*.txt".  If you do that
	// then finder will not return any directory names.
	string fname = path + "\\*." + extension;

	// start the finder -- on error _findfirsti64() will return -1, otherwise if no
	// error it returns a handle greater than -1.
	long h = _findfirsti64(fname.c_str(),&data);
	if(h >= 0)
	{
		do {
			if( strcmp(data.name,".") != 0 && strcmp(data.name,"..") != 0)
			{
				// this is just a normal file.  So just add it to our map
				int type = UNKNOWN;		// assume that the file is of unknown type
				string tempfn;			// used to strip off the .cnf extension
				// check that the file is not already in the map before doing any other work
				if(!isInMasterMap(data.name))	
				{
					if(extension == "conf")	// if this is the first pass
					{
						type = determineType(path+"\\"+data.name);	// determine the type of the file then add to the master map
						tempfn = data.name;
						tempfn = tempfn.substr(0,tempfn.length() - 5);
					}
					else
						tempfn = data.name;
					map<int,set<string>*>::iterator mit;
					mit = m_masterMap.find(type);
					if(mit != m_masterMap.end()) // this is not the first item of this type to be added to the map
					{
						mit->second->insert(tempfn);
					}
					else // this is the first item of this type we have encountered
					{
						set<string>* strset = new set<string>;
						strset->insert(tempfn);
						m_masterMap.insert(make_pair(type,strset));
					}
				}
				if(extension != "conf")	// we do not want to add the .cnf files into the directory listing
					m_directoryListing.insert(data.name);
			}
		}while( _findnexti64(h,&data) == 0);
		// close the find handle.
		_findclose(h);
	}
}

// Verifies that all of the entries in m_masterMap appear in m_directoryListing.
// Any entry in the map not found in the listing is removed.
void MPane::validateMap()
{
	map<int,set<string>*>::iterator mit;
	set<string>::iterator sit, fit;
	set<string> filesToRemove;
	for(mit = m_masterMap.begin(); mit != m_masterMap.end(); mit++)		// search through m_masterMap
	{
		for(sit = mit->second->begin(); sit != mit->second->end(); sit++)	// search through m_directoryListing
		{
			// entry found in m_mastermap that is not in m_directoryListing, remove it
			if(m_directoryListing.find(*sit) == m_directoryListing.end())
			{
				filesToRemove.insert(*sit);		// add it to the list of files to remove
			}
		}
		for(fit = filesToRemove.begin(); fit != filesToRemove.end(); fit++)	// remove any files added to filesToRemove
		{
			sit = mit->second->find(*fit);		// find the position of the file to remove
			if( sit != mit->second->end())		// ensure it is found before trying to remove it
			{
				mit->second->erase(sit);
			}
		}
		filesToRemove.clear();	// clear the filesToRemove before moving onto the next set of files in the map
	}
}

// Called in AssocToDir to updated the filtered map upon associating the master map to a new directory
void MPane::updateFilteredMap()
{
	map<int,set<string>*>::iterator mit;	// declare a map interator for the master map
	set<int>::iterator	sit;				// declare a set iterator for the flag set
	for(sit = m_flags.begin(); sit != m_flags.end(); sit++)
	{
		mit = m_masterMap.find(*sit);	// search for key in master map
		if(mit != m_masterMap.end())	// if found add it to the filtered map
		{	
			map<int,set<string>*>::iterator fit;	// declare a map interator for the filtered map
			fit = m_filteredMap.find(*sit); // search for key in filtered map
			if(fit != m_filteredMap.end())	// if key already exists, replace its value pair
			{
				fit->second = NULL;			// set the value (set<string>*) pointer to NULL
											// so that the pointer is not accidentally deleted
											// since it points directly to the value set in the master map

				fit->second = mit->second;	// point the set of values in filtered map to the values contained in master map
			}
			else	// add the new set of values into the filtered map
			{
				m_filteredMap.insert(make_pair(*sit,mit->second));
			}
		}
	}
}

// Given the name of a file, filename, search through m_masterMap and if found return true, otherwise return false
bool MPane::isInMasterMap(string filename)
{
	if(m_masterMap.empty())
		return false;
	map<int,set<string>*>::iterator mit;
	for(mit = m_masterMap.begin(); mit != m_masterMap.end(); mit++)
	{
		if( (mit->second->find(filename)) != mit->second->end()) // search for the file, if found return true
			return true;
	}
	return false;
}

// Given the name to a .cnf file in the current directory, determineType opens the file, reads the file
// one line at a time searching for the <type> tag. It reads the value between the <type> tags and returns
// the integer value.
int MPane::determineType(string filename)
{
	int fileType = UNKNOWN;
	fstream infile(filename.c_str(),ios_base::in);
	string line;
	if(!infile)	// unable to open the file! ERROR!
		return fileType;
	else
	{
		while(getline(infile,line))
		{
			string::size_type tagloc = line.find("<type>");	// search for the type tag in the line
			if(tagloc != string::npos)	// type tag was found, extract type and return it
			{				
				string::size_type typeEnd = line.find_last_of('<');
				string type = line.erase(0,6);		// erase "<type>" from the line
				type = type.erase(typeEnd,7);		// erase "</type>" from the line
				fileType = atoi(type.c_str());		// convert the string remaining into an integer
				infile.close();
				return fileType;
			}
		}
	}

	//Closing the file
	infile.close();

	return fileType;
}

//Returns a pointer to m_filteredMap
map<int,set<string>*>* MPane::getFileList()
{
	return &m_filteredMap;
}

//Label an unknown file type as type specified in type argument
//This function will also add the file to the appropriate
//set in the master map, remove it from the set that it was
//found.
//
//For now implemented without the Item class
//
//Parameters:
//  int type: the item type, ie GOODWARE = 200
//  string item: the full path to the file , ie c:\\windows\\goodware1.gwd
bool MPane::labelFileAsFlag(int type, string filename)
{
	string TMP = ".tmp";
	
	//Check for range and convert int type to cstring
	if (type < 100 || type > 1000) {
		return false;
	}
	//Buffer for converting int to cstring
	char type_buffer [5];					
	_itoa_s(type, type_buffer, 10);

	//Generate location of .cnf file and .cnf.tmp files
	string cnf_location = getCnfFullPath(filename);
	string cnf_location_temp = cnf_location + TMP;

	int old_type = -1;
	
	if (!cnfFolderUpdate())
		return FALSE;

	///////////////////////////////////////////////////////////////////////
	//Create the cnf file if it does not exist
	//If it exists, change its type
	///////////////////////////////////////////////////////////////////////
	

	//Open the temporary output file (*.cnf.tmp)
	fstream outfile;
	outfile.open(cnf_location_temp.c_str(), ios_base::out);
	//File cannot be opened, return failure
	if(!outfile) {	
		return FALSE;
	}

	//If no .cnf file exists, make it
	if (!checkCnfExists(cnf_location)) 
	{
		//Make a *cnf.tmp file, with only the correct filename value.
		//Other values are blank
		outfile << "<filename>" << filename << "</filename>" << endl;
		outfile << "<type>" << type_buffer << "</type>" << endl;
		outfile << "<operations>" << endl << "</operations>";

		//Close the IO stream
		outfile.close();

		//Rename the *.cnf.tmp to *.cnf file
		//Now correctly formatted to be used by other functions
		rename(cnf_location_temp.c_str(), cnf_location.c_str());

		//Change the m_masterMap flag type for this file
		return changeMasterMapFlag(UNKNOWN, type, filename);		

	}

	//File exists, change its type
	else {

		//If the old type is the same as the new type, return
		old_type = determineType(cnf_location);
		if (type == old_type) {
			outfile.close();
			remove(cnf_location_temp.c_str());
			return true;
		}

		//Otherwise, open the original cnf file as input (read only)
		fstream infile;
		infile.open(cnf_location.c_str(), ios_base::in);
		if (!infile) {
			infile.close();
			outfile.close();
			remove(cnf_location_temp.c_str());
			return false;
		}
				
		//Read each line from the original cnf file
		string line;
		while(getline(infile, line))
		{
			//Search for the <type> tag in the line
			string::size_type tagloc = line.find("<type>");	
			//Type tag was found, modify it
			if(tagloc != string::npos)						
			{
				//Find where the </type> tag is
				string::size_type typeEnd = line.find_last_of("</type>");
				//Remove the old type, which is between <type> and </type>
				line.erase(tagloc + 6, (typeEnd - 6) - (tagloc + 6) );
				//Insert the new type
				line.insert(tagloc + 6, type_buffer);
			}
			//Write each line to the temporary output file (.cnf.tmp)
			outfile << line << endl;
		}
		//Close both of these IO streams
		infile.close();
		outfile.close();

		//Replace the old cnf file with the newly created .cnf.tmp > .cnf file
		remove(cnf_location.c_str());
		rename(cnf_location_temp.c_str(), cnf_location.c_str());

		//Change the m_masterMap flag type for this file
		return changeMasterMapFlag(old_type, type, filename);
	}

	//Should have returned by now, something is wrong otherwise
	return false;

}

// Given a cnf_info struct (see below), we append to the cnf file
// for a particular file (indicated in cnf_info) with the actions performed
//
//Parameters:
//  cnf_info cnf_action_info: struct containing all action info. See declaration.
//  string item: the full path to the file , ie c:\\windows\\goodware1.gwd
//
//NOTE: We are assuming a "cnf_files" subdirectory exists in the current working directory
//		We also require an appropriate .cnf file in that subdirectory. 
//TODO: Iterate through multimap<string,list<file_info>> action_list
			//		and write the info to the .cnf file
/*
bool MPane::updateConfig(cnf_info cnf_action_info)
{
	string CNF_EXT = ".cnf";
	string CNF_DIR = "cnf_files\\";

	string cnf_location = cnf_action_info.filename;
	string cnf_location_temp;

	unsigned int found;

	///////////////////////////////////////////////////////////////////////
	//Here, we are appending the cnf_file directory to string cnf_location
	//We will look for the cnf file in that diectory
	///////////////////////////////////////////////////////////////////////
	//Find the last "\\" and add cnf_files\\ to it
	found = cnf_location.find_last_of("\\");		
	if (found != -1) {
		cnf_location.insert(found + 1, CNF_DIR);
	}
	else {
		//Malformed string item_path
		return FALSE;								
	}
	
	///////////////////////////////////////////////////////////////////////
	//Find the extension of the original string, and replace it with ".cnf"
	///////////////////////////////////////////////////////////////////////
	//Find the last "." of string item (to determine the extension)
	found = cnf_location.find_last_of(".");		
	//If there is an extension, remove it. If no extension skip this step
	if (found != -1 && found > cnf_location.find_last_of("/\\")) {	
		cnf_location = cnf_location.substr(0, found);
	}

	//Append the extension cnf
	cnf_location.append(CNF_EXT);

	//A *.cnf.tmp for temporary writing
	cnf_location_temp = cnf_location + ".tmp";



	///////////////////////////////////////////////////////////////////////
	//Open the original .cnf file and a temporary .cnf.tmp file
	//Perform read/write operations
	///////////////////////////////////////////////////////////////////////
	//Try to open the existing cnf file as input (read only)
	fstream infile;
	infile.open(cnf_location.c_str(), ios_base::in);
	if (!infile)
		return FALSE;

	//Also open the temporary output file (*.cnf.tmp)
	fstream outfile;
	outfile.open(cnf_location_temp.c_str(), ios_base::out);
	if (!outfile)
		return FALSE;



	//Read each line from the original cnf file
	string line;
	while(getline(infile, line))
	{
		//Search for the <type> tag in the line
		string::size_type tagloc = line.find("</operations>");	
		//Type tag was found, modify it
		if(tagloc != string::npos)						
		{
			//TODO: Iterate through multimap<string,list<file_info>> action_list
			//		and write the info to the .cnf file
		}
		//Write each line to the temporary output file (.cnf.tmp)
		outfile << line << endl;
	}
	//Close both of these IO streams
	infile.close();
	outfile.close();

	//Replace the old cnf file with the newly created cnf.tmp > cnf file
	remove(cnf_location.c_str());
	rename(cnf_location_temp.c_str(), cnf_location.c_str());

	return TRUE;

}
*/

//getFileData(filename); 

bool MPane::changeMasterMapFlag(int old_type, int new_type, string filename)
{
	map<int,set<string>*>::iterator mit;
	
	//First add it to the new_type section
	mit = m_masterMap.find(new_type);

	//This is not the first item of this type to be added to the map
	if(mit != m_masterMap.end()) 
	{
		mit->second->insert(filename);
	}
	//Else this is the first item of this type we have encountered
	else 
	{
		set<string>* strset = new set<string>;
		strset->insert(filename);
		m_masterMap.insert(make_pair(new_type,strset));
	}

	if(old_type >= 100 && old_type <= 1000)
	{
		//Next remove it from the old section
		mit = m_masterMap.find(old_type);
		if(mit != m_masterMap.end()) 
		{
			mit->second->erase(filename);
		}
	}

	return true;
}

/* Given the full path to a cnf file, this function checks 
 * if the cnf file exists
 */
bool MPane::checkCnfExists(string full_cnf_path)
{
	//Try to open the existing cnf file as input (read only)
	fstream infile;
	infile.open(full_cnf_path.c_str(), ios_base::in);

	//File exists
	if(infile.is_open())
	{
		//Close it
		infile.close();

		return true;
	}

	return false;

}



/* This function takes a string filename, and it returns a string
 * containing the full path to the .cnf file associated with the input.
 * ie. getCnfPath(gwd1.gwd) returns C:\\Temp\\cnf_files\\gwd1.gwd.cnf
 */
string MPane::getCnfFullPath(string filename)
{
	string CNF_EXT = ".conf";
	string CNF_DIR = "cnf_files\\";

	string full_path = m_working_dir;	//Will contain the full path to the cnf file

	unsigned int found;

	///////////////////////////////////////////////////////////////////////
	//Here, we are appending the cnf_file directory to string full_path
	///////////////////////////////////////////////////////////////////////
	//Find the last "\\" and add cnf_files\\ to it
	found = full_path.find_last_of("\\");		
	if (found != -1) {
		full_path.insert(found + 1, CNF_DIR);
	}
	else {
		//Probably a malformed string full_path, return ""
		return "";								
	}

	full_path.append(filename);
	
	
	///////////////////////////////////////////////////////////////////////
	//Append the .cnf extension to the string full_path
	///////////////////////////////////////////////////////////////////////
	full_path.append(CNF_EXT);

	return full_path;
}

/* This function takes a string filename, and it returns a string
 * containing the full path to the file.
 * ie. getFileFullPath(gwd1.gwd) returns C:\\Temp\\gwd1.gwd
 */
string MPane::getFileFullPath(string filename)
{
	return m_working_dir + filename;
}

/* If cnf_files exists within a given directory, return true
 * otherwise, create the cnf_files directory and return the status
 */
BOOL MPane::cnfFolderUpdate()
{
	if(m_cnfFolderCreated) {
		return TRUE;
	}

	string CNF_DIR = "cnf_files\\";
	string path = m_working_dir;
	path = path + CNF_DIR;

	if (GetFileAttributes(CString(path.c_str())) != 0xFFFFFFFF) {
		m_cnfFolderCreated = TRUE;
		return m_cnfFolderCreated;
	}
	else {
		m_cnfFolderCreated = CreateDirectory(CString(path.c_str()), NULL);
		return m_cnfFolderCreated;
	}
}

string MPane::getCnfData(string filename)
{
	string return_string = "";

	int fileType = UNKNOWN;

	string full_cnf_path = getCnfFullPath(filename);
	if (!checkCnfExists(full_cnf_path)) {
		return return_string;
	}

	fstream infile;
	infile.open(full_cnf_path.c_str(), ios_base::in);
	if (!infile) {
		return return_string;
	}

	string line;

	return_string = return_string + "File Name: " + filename + "\n";

	while(getline(infile,line))
	{
		string::size_type tagloc = line.find("<type>");	// search for the type tag in the line
		if(tagloc != string::npos)	// type tag was found, extract type and return it
		{				
			string type = line.substr(6, 3);

			return_string = return_string + "Type: ";

			if (type == "100")
				return_string = return_string + "UNKNOWN" + "\n";
			else if (type == "200")
				return_string = return_string + "GOODWARE" + "\n";
			else if (type == "300")
				return_string = return_string + "MALWARE" + "\n";
			else if (type == "400")
				return_string = return_string + "PRE PROCESSED MALWARE" + "\n";
			else if (type == "500")
				return_string = return_string + "MODEL" + "\n";
			else if (type == "600")
				return_string = return_string + "SIGNATURE" + "\n";
			else if (type == "700")
				return_string = return_string + "STUBMAP" + "\n";
			else if (type == "800")
				return_string = return_string + "CLUSTER" + "\n";
			else if (type == "900")
				return_string = return_string + "INDEX" + "\n";
		}

		tagloc = line.find("<operations>");	// search for the operations tag in the line
		if(tagloc != string::npos)	// type tag was found, extract type and return it
		{
			return_string = return_string + "Operations:" + "\n";
			while(getline(infile,line))
			{
				string::size_type tagloc = line.find("</operations>");	// search for the /operations tag in the line
				if(tagloc != string::npos)
				{
					infile.close();
					return return_string;
				}
				return_string = return_string + line + "\n";
			}
		}
	}

	infile.close();
	return return_string;

}

/* Updates the .conf file after an action has been performed:
   Inputs:	int action_int is the type of action performed:

			100 Extract Buffers, 101 Create Model, 102 Create Index
			200 Prune Model, 201 Merge Models, 202 Compile Models, 203 Create Stub Map
			300 Find Signatures
			400 Preprocess Malware
			500 Cluster Files

			const list<string> &inputs is the list of all the input files to the action
			const list<string> &outputs is the list of all the output files of the action
	Outputs: TRUE if success, FALSE if fail
*/
bool MPane::updateCnfAction(int action_int, const list<string> &inputs, const list<string>  &outputs)
{
	string TMP = ".tmp";

	string action_string = getActionStringFromInt(action_int);

	//The current list we will be iterating through
	list<string> current_list;
	//A temp char array to hold the type info (for entering into .conf files)
	char type_buffer [5];

	string current_filename = ""; //The current file being processed
	
	string line; //For reading lines of a input file

	//We need to iterate through this process twice:
	//Once for the input files list, once for the output files list
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			_itoa_s(UNKNOWN, type_buffer, 10);	
			current_list = inputs;
		}
		if (i == 1)
		{
			_itoa_s( getFiletypeIntFromActionInt(action_int) , type_buffer, 10);
			current_list = outputs;
		}

		for (list<string>::iterator it = current_list.begin(); it != current_list.end(); it++)
		{

			current_filename = *it;


			//Generate location of .cnf file and .cnf.tmp files
			string cnf_location = getCnfFullPath(current_filename);
			string cnf_location_temp = cnf_location + TMP;

			if (!cnfFolderUpdate())
				return FALSE;

			//Open the temporary output file (*.conf.tmp)
			fstream outfile;
			outfile.open(cnf_location_temp.c_str(), ios_base::out);
			//File cannot be opened, return failure
			if(!outfile) {	
				return FALSE;
			}

			//If no .cnf file exists, make it
			if (!checkCnfExists(cnf_location)) 
			{
				//Make a *conf.tmp file
				outfile << "<filename>" << current_filename << "</filename>" << endl;
				outfile << "<type>" << type_buffer << "</type>" << endl;
				outfile << "<operations>" << endl;

				outfile << "Action: " <<  getActionStringFromInt(action_int) << endl;

				for (list<string>::const_iterator it = inputs.begin(); it != inputs.end(); it++)
				{
					outfile << "  Input: " << *it << endl;
				}
				for (list<string>::const_iterator it = outputs.begin(); it != outputs.end(); it++)
				{
					outfile << "  Output: " << *it << endl;
				}		

				outfile << "</operations>";		

				//Close the IO stream
				outfile.close();

				//Rename the *.cnf.tmp to *.cnf file
				//Now correctly formatted to be used by other functions
				rename(cnf_location_temp.c_str(), cnf_location.c_str());
			}

			//File exists, append to its <operations> section
			else {

				// Open the original cnf file as input (read only)
				fstream infile;
				infile.open(cnf_location.c_str(), ios_base::in);
				if (!infile) {
					infile.close();
					outfile.close();
					remove(cnf_location_temp.c_str());
					return false;
				}

				while(getline(infile,line))
				{
					string::size_type tagloc = line.find("<operations>");	// search for the operations tag in the line
					outfile << line << endl;
					if(tagloc != string::npos)
					{
						outfile << "Action: " <<  getActionStringFromInt(action_int) << endl;

						for (list<string>::const_iterator it = inputs.begin(); it != inputs.end(); it++)
						{
							outfile << "  Input: " << *it << endl;
						}
						for (list<string>::const_iterator it = outputs.begin(); it != outputs.end(); it++)
						{
							outfile << "  Output: " << *it << endl;
						}	
					}			
				}

				//Close both of these IO streams
				infile.close();
				outfile.close();

				//Replace the old cnf file with the newly created .cnf.tmp > .cnf file
				remove(cnf_location.c_str());
				rename(cnf_location_temp.c_str(), cnf_location.c_str());
			}
		}
	}

	return TRUE;
}
		


string MPane::getActionStringFromInt(int action_int)
{
	string action_string = "";

	if(action_int == 100)
		action_string = "Extract Buffers";
	else if (action_int == 101)
		action_string = "Create Model";
	else if (action_int == 102)
		action_string = "Create Index";
	else if (action_int == 200)
		action_string = "Prune Model";
	else if (action_int == 201)
		action_string = "Merge Models";
	else if (action_int == 202)
		action_string = "Compile Models";
	else if (action_int == 202)
		action_string = "Create Stub Map";
	else if (action_int == 300)
		action_string = "Find Signatures";
	else if (action_int == 400)
		action_string = "Preprocess Malware";
	else if (action_int == 500)
		action_string = "Cluster Files";

	return action_string;
}

/*This function takes the action type (int) and returns the filetype of the output file.
ie. A PreProcess Malware action (int action_int = 400) will return 400,
	which is the PreProcessed Malware filetype (see MPane.h)
*/
int MPane::getFiletypeIntFromActionInt(int action_int)
{
	//Default filetype, UNKNOWN = 100
	int FiletypeInt = 100;

	if(action_int == 100)
		// Extract Buffers
		FiletypeInt = 100; //???
	else if (action_int == 101)
		// Create Model
		FiletypeInt = 500;
	else if (action_int == 102)
		// Create Index
		FiletypeInt = 900;
	else if (action_int == 200)
		// Prune Model
		FiletypeInt = 500;
	else if (action_int == 201)
		// Merge Models
		FiletypeInt = 500;
	else if (action_int == 202)
		// Compile Models
		FiletypeInt = 500;
	else if (action_int == 202)
		// Create Stub Map
		FiletypeInt = 700;
	else if (action_int == 300)
		// Find Signatures
		FiletypeInt = 600;
	else if (action_int == 400)
		// Preprocess Malware
		FiletypeInt = 400;
	else if (action_int == 500)
		//Cluster Files
		FiletypeInt = 800;

	return FiletypeInt;
}