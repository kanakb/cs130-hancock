#ifndef MPANE_H
#define	MPANE_H
#include <windows.h>
#include <shlobj.h> //for directory functions
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#include <iostream>
#include <io.h>
#include <vector>
#include <set>
#include <stdlib.h>

/* Various file types */
#define UNKNOWN 100
#define GOODWARE 200
#define MALWARE 300
#define PPM 400
#define MODEL 500
#define SIGNATURE 600
#define STUBMAP 700
#define CLUSTER 800
#define INDEX 900
#define DIR 1000
// End of filetypes

using namespace std;

class Item;

class MPane 
{

public:
	MPane();
	void AssocToDir(string path);				// Given a path, associate the MPane with that path
	void addFlag(int type);						// Add a flag to filter the directory files 
	void removeFlag(int type);					// Remove a flag previously used to filter files
	map<int,set<string>*>* getFileList();		// Return the filtered list of files
	void labelFileAsFlag(int type, Item* it);	/* Label an unknown file type as type specified in type argument
												 * This function will also add the file to the appropriate
												 * set in the master map, remove it from the set that it was
												 * found.
												 */
	void updateConfig( /* action info structure */ );	// place holder

private:
	map<int,set<string>*> m_masterMap;			// the master map contains all directory files
	map<int,set<string>*> m_filteredMap;			// filtered map contains only entries matching the flags
	set<int> m_flags;							// this set contains the list of flags used to filter master map

	struct file_info 
	{
		int type;			// 0 indicates file is used for input, 1 for output
		string filename;	// the name of the file
	}file_t;

	struct cnf_info
	{
		int type;			// the type of file (eg malware, goodware, unknown, etc...)
		string filename;	// name of the file that this config file represents
		multimap<string,list<file_info>> action_list;	// the list of actions that have been performed on this file
	}cnf_info_t;

	void AssocToDirInternal(string path, string extension);	// implementation of above interface method: AssocToDir
	int determineType(string filename);		// reads the .cnf specified by filename and returns the type of the file
	void updateFilteredMap();				// updates the filtered map using the flags in the m_flags set
};

#endif // MPANE_H DEFINED