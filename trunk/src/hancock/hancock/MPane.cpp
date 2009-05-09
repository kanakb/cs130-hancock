#include "MPane.h"

MPane::MPane()
{
}

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
			fit->second->clear();		// clear previous values
			fit->second = mit->second;	// point the set of values in filtered map to the values contained in master map
		}
		else	// add the new set of values into the filtered map
		{
			m_filteredMap.insert(make_pair(type,mit->second));
		}
	}
}

void MPane::removeFlag(int type)
{
	flags->remove(type);
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

void MPane::AssocToDir(string path)
{
	/* If this test succeeds, then this is not the first call to AssocToDir.
	 * Therefore we must clear the current map of files that we have before
	 * associating the map to a new directory.
	 */
	
	struct _finddatai64_t data;
	// First create the filename that will be use to initialize the find.
	// "*.*" are wild card characters that tells the find function to return a
	// list of all the files and directories.  You can limit this if you wish
	// to just file with specific extensions, for example "*.txt".  If you do that
	// then finder will not return any directory names.

	if(!extension.empty)
		string fname = path + "\\*." + extension; //this will find only .txt files. Change to .obj for the tiles
	else
		string fname = path;
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
					if(mit != itemMap->end()) // this is not the first directory to be added to the map
					{
						mit->second->insert(fname);
					}
					else // this is the first directory we have encountered
					{
						set<string>* strset = new set<string>;
						strset->insert(fname);
						itemMap->insert(make_pair(DIR,strset));
					}
				}
			}
			else
			{
				// this is just a normal file.  So just add it to our map
				int type = determineType(data.name);
				map<int,set<string>*>::iterator mit;
				mit = itemMap->find(type);
				if(mit != itemMap->end()) // this is not the first item of this type to be added to the map
				{
					mit->second->insert(data.name);
				}
				else // this is the first item of this type we have encountered
				{
					set<string>* strset = new set<string>;
					strset->insert(data.name);
					itemMap->insert(make_pair(DIR,strset));
				}
			}
		}while( _findnexti64(h,&data) == 0);
		// close the find handle.
		_findclose(h);
	}
}

map<int,set<string>>* MPane::getFileList()
{
	return &m_filteredMap;
}

void MPane::labelFileAsFlag(int type, Item* it);
{
}

void MPane::updateConfig()	// place holder
{
}