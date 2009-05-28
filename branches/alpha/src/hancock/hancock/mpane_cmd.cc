#include "MPane.h"

void printMap(map<int,set<string>*>* theMap);

int main(char argc, char** argv)
{
	/* The following flags specified through the command-line are used for testing the Log class above
	 *		-a "path" // associate the master map to the directory specified by path
	 *		-f "type" // add the specified type to the flag set as well as to the
	 *					  filtered map, if the set exists in the master map
	 *		-r "type" // remove the specified type from the flag set and filtered
	 *					  map, if the set exists in filtered map
	 *		-m        // print the files listed in master map in the following format:       file        type
	 *		-p        // print the files listed in filtered map in the following format:     file        type
	 */
	bool assoc_path = false, addflag = false, removeflag = false;
	string path;
	int type;
	MPane testPane;
	
	/* Begin command-line parsing 
	 * The above flags can be specified in any order and combination as well as with repititions 
	 */
	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')	// current argument is a flag
		{
			switch(argv[i][1])
			{
				case 'a': // associate the master map to the directory specified by path
					assoc_path = true;
					break;
				case 'f': // add the specified type to the flag set and filtered map, if found in master map
					addflag = true;
					break;
				case 'r': // remove the specified type from the flag set and filtered map, if found in filtered map
					removeflag = true;
					break;
				case 'm': // print the files listed in master map in the following format:       file        type
					printMap(testPane.getMasterList());
					break;
				case 'p': // print the files listed in filtered map in the following format:       file        type
					printMap(testPane.getFileList());
					break;
				default:
					break;
			}
		}
		else					// current argument is input
		{
			if(assoc_path)		// the input is a directory path since it was read after a -a flag
			{
				path = argv[i];
				testPane.AssocToDir(path);
				assoc_path = false;
			}

			else if(addflag)	// the input is a flag type to add to the flag set, update the filtered map if necessary
			{
				type = atoi(argv[i]);
				testPane.addFlag(type);
				addflag = false;
			}

			else if(removeflag)	// the input is a flag type to remove from the flag set, update the filtered map if necessary
			{
				type = atoi(argv[i]);
				testPane.removeFlag(type);
				removeflag = false;
			}
		}	
	} 

	return 0;
}

void printMap(map<int,set<string>*>* theMap)
{
	map<int,set<string>*>::iterator mit;	// create a map iterator
	set<string>::iterator sit;	// create a set iterator
	cout << endl;
	cout << "Printing out the map contents" << endl;
	cout << "-----------------------------" << endl;
	cout << "Type\t\tFilename" << endl;
	for(mit = theMap->begin(); mit != theMap->end(); mit++)		// iterate through the map and print out the contents
	{
		for(sit = mit->second->begin(); sit != mit->second->end(); sit++)	// iterate through set contents, print them
		{
			cout << mit->first << "\t\t" << *sit << endl;
		}
	}
}