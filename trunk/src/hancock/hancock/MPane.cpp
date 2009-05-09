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
					m_masterMap.insert(make_pair(type,strset));
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
				string type = line.erase(0,6);		// erase "<type>" from the line
				string::size_type typeEnd = line.find_last_of('<');
				type = type.erase(typeEnd,7);		// erase "</type>" from the line
				fileType = atoi(type.c_str());		// convert the string remaining into an integer
				break;
			}
		}
	}
	return fileType;
}

// Updates m_filteredMap with the new files using the flags currently present in the m_flags set
void MPane::updateFilteredMap()
{
	if(!m_flags.empty())
	{
		set<int>::iterator sit;		// m_flags set iterator
		for(sit = m_flags.begin(); sit != m_flags.end(); sit++)	// iterate through m_flags
		{
			map<int,set<string>*>::iterator mit;	// m_masterMap iterator to search for presence of current flag
			mit = m_masterMap.find(*sit);	// search through m_masterMap for current flag
			if(mit != m_masterMap.end())	// the set exists, proceed to add the set from m_masterMap to m_filteredMap
			{
				map<int,set<string>*>::iterator fit;	// m_filteredMap iterator to search for presence of current flag
				fit = m_filteredMap.find(*sit);		// search through m_filteredMap for current flag
				if(fit != m_filteredMap.end())		// set exists, replace its Item/string set with the new one
				{
					fit->second = mit->second;
				}
				else		// flag does not exist in filtered map, add it
				{
					set<string>* strset = new set<string>;
					strset = mit->second;
					m_filteredMap.insert(make_pair(*sit,strset));
				}
			}
		}
	}
	else	// there currently no filter flags active, add the UNKNOWN set from master map to filtered map
	{
		
		map<int,set<string>*>::iterator mit;	// m_masterMap iterator to search for presence of current flag
		mit = m_masterMap.find(UNKNOWN);	// search through m_masterMap for UNKNOWN flag
		if(mit != m_masterMap.end())		// check to ensure that m_masterMap contains an UNKNOWN set
		{
			set<string>* strset = new set<string>;
			map<int,set<string>*>::iterator fit;	// m_filteredMap iterator to search for presence of current flag
			fit = m_filteredMap.find(UNKNOWN);		// search through m_filteredMap for UNKNOWN flag
			if(fit != m_filteredMap.end())		// set exists, replace m_filteredMap Item/string set with m_masterMap's
			{
				fit->second = mit->second;
			}
			else		// flag does not exist in filtered map, add it
			{
				set<string>* strset = new set<string>;
				strset = mit->second;
				m_filteredMap.insert(make_pair(UKNOWN,strset));
			}
		}
	}
}

map<int,set<string>*>* MPane::getFileList()
{
	return &m_filteredMap;
}

void MPane::labelFileAsFlag(int type, Item* it)
{
}

void MPane::updateConfig()	// place holder
{
}