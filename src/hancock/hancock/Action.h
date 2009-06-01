/*
 *  Action.h
 *  
 * 
 */


#ifndef ACTION_H
#define ACTION_H

#define MAX_BUF_LEN 1024

//#include "MPane.h"  // !!!!TEMPORARY!!!!
#include <iostream>	  // !!!!TEMPORARY!!!!
#include <vector>
#include <string>
#include "windows.h"
#include "stdio.h"
#include <tchar.h>
//#include <curses.h>	// !!!!TEMPORARY!!!!
using namespace std;


/*** Define Status codes here ***/


class Action {
	
public:
	Action();
	Action(string path, string name, string cfg);	//used for most actions
	Action(string path, string name, string cfg, string optionalOutfile);	//used for Cluster File and Find Signatures actions
	Action(string path, string name, vector<string> &params); //the last parameter is a vector of arguments for the executable.
	virtual bool act();					//builds the cmd and runs the action
	virtual string getName();			//returns the name of the executable
	virtual bool isComplete();			//tells if process is done
	virtual int getStatus();
	
	string exePath;						//Location of the executable
	string exeName;						//Some way to refer to executable. 
	string m_symantecCfg;				//Path of the .cfg file used as input for the executable
	int status;							//status of action
	string output;
	string m_optionalOutfile;			//Specifies the optional output file to save the action out in

protected:
	bool executeProcess(string cmd);
	char buf[MAX_BUF_LEN];		// i/o buffer
	HANDLE stdout_in_child, stdout_from_child;
	PROCESS_INFORMATION pi;
	vector<string> argv;	
};

#endif ACTION_H




