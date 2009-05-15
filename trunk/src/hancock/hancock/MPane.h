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
#include <stdio.h>


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
// End of filetypes

using namespace std;

class Item;

class MPane 
{

public:
	MPane();
	~MPane();
	void AssocToDir(string path);				// Given a path, associate the MPane with that path
	void addFlag(int type);						// Add a flag to filter the directory files 
	void removeFlag(int type);					// Remove a flag previously used to filter files
	map<int,set<string>*>* getFileList();		// Return the filtered list of files
	map<int,set<string>*>* getMasterList();		// Return the master list of files
	bool labelFileAsFlag(int type, string item_path);	/* Label an unknown file type as type specified in type argument
														 * This function will also add the file to the appropriate
														 * set in the master map, remove it from the set that it was
														 * found.
														 */
	string getCnfData(string filename);	/* Given a file in the current directory,
										 * this function reads its .conf file and returns all the info in the following format:
										 * <filename>filename</filename>\n
											<type>type</type>\n
											<operations>\n
											operation1\n	//Operations not finalized yet
											</operations>;
										 */

	//class Action;

	/*bool updateConfig(Action* action);				/* Given a cnf_info struct (see below), we append to the cnf file
														 * for a particular file (indicated in cnf_info) with the actions performed
														 */


private:

	string m_working_dir;					// The path of the current working directory. ie C:\\Windows\\Temp\\

	bool m_cnfFolderCreated;

	map<int,set<string>*> m_masterMap;		// the master map contains all directory files
	map<int,set<string>*> m_filteredMap;	// filtered map contains only entries matching the flags
	set<int> m_flags;						// this set contains the list of flags used to filter master map
	set<string> m_directoryListing;			// contains a listing of all the files in the current directory,
											// used to crosscheck that the files added via cnf search
											// are still in the current directory and haven't been moved/deleted

	struct file_info 
	{
		int type;			// 0 indicates file is used for input, 1 for output
		string filename;	// the name of the file
	}file_t;

	struct cnf_info
	{
		int type;			// the type of file (eg malware, goodware, unknown, etc...)
		string filename;	// name of the file that this config file represents (include full directory path)
		multimap<string,list<file_info>> action_list;	// the list of actions that have been performed on this file
	}cnf_info_t;

	void AssocToDirInternal(string path, string extension);	// implementation of above interface method: AssocToDir
	int determineType(string filename);		// reads the .cnf specified by filename and returns the type of the file
	bool isInMasterMap(string filename);	// searches through m_masterMap for an entry with the given filename
	void validateMap();						// validates the master map against the directory listing
	void updateFilteredMap();				// this function is called to update the contents of the filtered map
											// whenever assocToDir is called associating the master map to a new directory


	string getCnfFullPath(string filename);		/* This function takes a string filename, and it returns a string
												 * containing the full path to the .cnf file associated with the input.
												 * ie. getCnfPath(gwd1.gwd) returns C:\\Temp\\cnf_files\\gwd1.gwd.cnf
												 */
	string getFileFullPath(string filename);	/* This function takes a string filename, and it returns a string
												 * containing the full path to the file.
												 * ie. getFileFullPath(gwd1.gwd) returns C:\\Temp\\gwd1.gwd
												 */
	bool checkCnfExists(string full_cnf_path);	/* Given the full path to a cnf file, this function checks 
												 * if the file exists
												 */

	bool changeMasterMapFlag(int old_type, int new_type, string filename);	/* Given the filename, update m_masterMap 
																			 * from old_type to new_type
																			 */

	bool cnfFolderUpdate(); /* If cnf_files exists within a given directory, return true
							 * otherwise, create the cnf_files directory and return the status
							 */
};

#endif // MPANE_H DEFINED