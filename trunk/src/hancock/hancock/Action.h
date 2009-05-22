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
	Action(string path, string name, vector<string> &params); //the last parameter is a vector of arguments for the executable.
	virtual void act();					//builds the cmd and runs the action
	virtual string getName();			//returns the name of the executable
	virtual bool isComplete();			//tells if process is done
	virtual int getStatus();
	
	string exePath;						//Location of the executable
	string exeName;						//Some way to refer to executable. 
	string m_symantecCfg;				//Path of the .cfg file used as input for the executable
	int status;							//status of action
	string output;

protected:
	void executeProcess(string cmd);
	char buf[MAX_BUF_LEN];		// i/o buffer
	HANDLE newstdin,newstdout,read_stdout,write_stdin;
	PROCESS_INFORMATION pi;
	vector<string> argv;	
};

#endif ACTION_H




