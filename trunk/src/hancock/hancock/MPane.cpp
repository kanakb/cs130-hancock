#include "MPane.h"

MPane::MPane()
{
}

// addFlag adds the flag specified by type to the set of filters used to create filteredMap
// it adds the flag to the set and then adds that set to the filteredMap if it exists in masterMap
void MPane::addFlag(int type)
{
	m_flags.insert(type);	// insert the new filter flag into the set of filers
	map<int,set<string>*>::iterator mit;	// declare a map interator for the master map
	mit = m_masterMap.find(type);	// search for key in master map
	if(mit != m_masterMap.end())	// if found add it to the filtered map
	{	
		map<int,set<string>*>::iterator fit;	// declare a map interator for the filtered map
		fit = m_filteredMap.find(type); // search for key in filtered map
		if(fit != m_filteredMap.end())	// if key already exists, replace its value pair
		{
			fit->second = NULL;			// set the value (set<string>*) pointer to NULL
										// so that the pointer is not accidentally deleted
										// since it points directly to the value set in the master map

			fit->second = mit->second;	// point the set of values in filtered map to the values contained in master map
		}
		else	// add the new set of values into the filtered map
		{
			m_filteredMap.insert(make_pair(type,mit->second));
		}
	}
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

	/* If this test succeeds, then this is not the first call to AssocToDir.
	 * Therefore we must clear the current map of files that we have before
	 * associating the map to a new directory.
	 */

	if(!m_masterMap.empty())
	{
		m_masterMap.clear();
	}

	// Begin populating master map

	AssocToDirInternal(path,"cnf");		// first pass through directory we look for *.cnf files
										// these files tell us what type of file * is (ie Malware, Goodware, etc...)
	AssocToDirInternal(path,"*");		// second pass through we add everything else to the master map
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
			if( (data.attrib & _A_SUBDIR) )
			{
				// make sure we skip "." and "..".  Have to use strcmp here because
				// some file names can start with a dot, so just testing for the
				// first dot is not suffient.
				if( strcmp(data.name,".") != 0 && strcmp(data.name,"..") != 0)
				{
					// We found a sub-directory, label it as such and add it to the map
					fname = path + "\\" + data.name;
					map<int,set<string>*>::iterator mit;
					mit = m_masterMap.find(DIR);
					if(mit != m_masterMap.end()) // this is not the first directory to be added to the map
					{
						mit->second->insert(fname);
					}
					else // this is the first directory we have encountered
					{
						set<string>* strset = new set<string>;
						strset->insert(fname);
						m_masterMap.insert(make_pair(DIR,strset));
					}
				}
			}
			else
			{
				// this is just a normal file.  So just add it to our map
				int type = UNKNOWN;		// assume that the file is of unknown type
				if(extension == "cnf")	// if this is the first pass
					type = determineType(data.name);	// determine the type of the file then add to the master map			
				map<int,set<string>*>::iterator mit;
				mit = m_masterMap.find(type);
				if(mit != m_masterMap.end()) // this is not the first item of this type to be added to the map
				{
					mit->second->insert(data.name);
				}
				else // this is the first item of this type we have encountered
				{
					set<string>* strset = new set<string>;
					strset->insert(data.name);
					m_masterMap.insert(make_pair(DIR,strset));
				}
			}
		}while( _findnexti64(h,&data) == 0);
		// close the find handle.
		_findclose(h);
	}
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
		return -1;
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
//
//NOTE: We are assuming a "cnf_files" subdirectory exists in the current working directory
//		Otherwise we cannot write or read the existing cnf files!
//TODO: Update the m_masterMap for this file.
bool MPane::labelFileAsFlag(int type, string item_path)
{
	string CNF_EXT = ".cnf";
	string CNF_DIR = "cnf_files\\";

	unsigned int found;					//Position of last "." or "\\" in string item
	string cnf_location = item_path;	//Location of cnf file for current file (if it exists)
	string cnf_location_temp;			//Temporary file opened for writing

	string file_filename;				//The filename of the item (file)

	char type_buffer [5];					//buffer for converting int to cstring

	//Check for range and convert int type to cstring
	if (type < 100 || type > 1000) {
		return FALSE;
	}
	_itoa_s(type, type_buffer, 10);
	
	
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

	//Get the filename while we are here
	found = cnf_location.find_last_of("/\\");	
	file_filename = cnf_location.substr(found + 1, cnf_location.length());

	//Append the extension cnf
	cnf_location.append(CNF_EXT);
	//A temporary file for writing
	cnf_location_temp = cnf_location + ".tmp";

	

	///////////////////////////////////////////////////////////////////////
	//Create the cnf file if it does not exist
	//If it exists, change its type
	///////////////////////////////////////////////////////////////////////
	//Try to open the existing cnf file as input (read only)
	fstream infile;
	infile.open(cnf_location.c_str(), ios_base::in);

	//Also open the temporary output file (*.cnf.tmp)
	fstream outfile;
	outfile.open(cnf_location_temp.c_str(), ios_base::out);
	//File cannot be opened, return
	if(!outfile) {	
		return FALSE;
	}
	
	//File exists
	if(infile.is_open())
	{
		//Close it, and check its type
		infile.close();
		//If the old type is the same as the new type, return
		if (type == determineType(cnf_location)) {
			return TRUE;
		}

		//Otherwise, open the original cnf file as input (read only)
		infile.open(cnf_location.c_str(), ios_base::in);
				
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

		//Replace the old cnf file with the newly created cnf.tmp > cnf file
		remove(cnf_location.c_str());
		rename(cnf_location_temp.c_str(), cnf_location.c_str());

		return TRUE;
	}

	//This means that there is no current *.cnf file for the current Item (file)
	else 
	{
		//Make a *cnf.tmp file, with only the correct filename value.
		//Other values are blank
		outfile << "<filename>" << file_filename << "</filename>" << endl;
		outfile << "<type>" << type_buffer << "</type>" << endl;
		outfile << "<operations>" << endl << "</operations>";

		//Close the IO stream
		outfile.close();

		//Rename the *.cnf.tmp to *.cnf file
		//Now correctly formatted to be used by other functions
		rename(cnf_location_temp.c_str(), cnf_location.c_str());

		return TRUE;
	}
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

//getFileData(filename); 


//int main()
//{
//	/*Testing labelFileAsFlag*/
//	/*
//	//Include a subdirectory cnf_files in this folder. A test1.cnf file will be created
//	string ip1 = "C:\\test1\\test1.mal";
//	MPane* mpane1 = new MPane();
//
//	mpane1->labelFileAsFlag(500, ip1);
//	*/
//	return 0;
//}

//Comments:
//- AssocToDirInternal should look for all cnf files in a subdirectory called cnf_files.
//  We do not want to write the cnf files to their directory directly.
//	- Also, perform a crosscheck to make sure all cnf files have a valid real file.
//	  We don't want to have a messed up master map otherwise.
//- AssocToDir should also clear m_filteredMap
//- determineType should close the file it reads (done)
//- determineType should also look for </type> instead of < because there is a chance
//  that the other sections ie <operations> are included in the same line, by a human editor
//
//- We need to somehow check for a cnf_files directory and create it if it is not there
//	- for now i am assuming it will be created elsewhere
//
//Changes:
//- I implemented labelFileAsFlag and updateConfig as boolean functions
//	- if they fail for some reason, they will return false. then the gui can handle the error.
//
//Testing:
//- Tested labelFileAsFlag. Works.
//
//Todo:
//- Update the m_masterMap from the labelFileAsFlag function
//- updateConfig needs to iterate through the map to write the actions into the cnf file
//- Implement getFileData (trivial)