#include "log.h"
#include <string>
using namespace std;

int main(char argc, char** argv)
{
	/* The following flags specified through the command-line are used for testing the Log class above
	 *		-c : display the current log
	 *		-d : display a log file differing from the current running log, dis_log variable below
	 *			 the name of or path to a file should follow this flag, stored in log_filename
	 *			 example: -d log10172008.txt
	 *		-g : get the filename associated with the current log and display it
	 *		-w : write the message follow this flag to the current log file, write_to_log variable below,
	 *			 the message to be written must immediately follow the -w in quotations, stored in info_to_write,
	 *			 example:  -w "AN ERROR OCCURRED WHILE PERFORMING THE REQUESTED OPERATION"
	 */
	bool write_to_log = false, disp_log = false;
	string info_to_write;
	string log_filename;
	Log testLog;
	
	/* Begin command-line parsing 
	 * The above flags can be specified in any order and combination as well as with repititions 
	 */
	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')	// current argument is a flag
		{
			switch(argv[i][1])
			{
				case 'c': // display the log associated with the current instantiation of the program
					cout << testLog.dispCurrLog() << endl;
					cout << endl;
					break;
				case 'd': // display a different log file specified by the input following the -d flag
					disp_log = true;
					break;
				case 'g': // display the name of the current log file
					cout << testLog.getFileName() << endl;
					cout << endl;
					break;
				case 'w': // write the message following the -w flag to the current log file
					write_to_log = true;
					break;
				default:
					break;
			}
		}
		else					// current argument is input
		{
			if(disp_log)		// the input is a log filename since it was read after a -d flag
			{
				log_filename = argv[i];
				cout << testLog.dispLog(log_filename.c_str()) << endl;
				cout << endl;
				disp_log = false;
			}

			else if(write_to_log)	// the input is a message to write to the current log file since it came after a -w flag
			{
				info_to_write = argv[i];
				testLog.write(info_to_write);
				write_to_log = false;
			}
		}	
	} 

	return 0;
}