/*
 *  Action.h
 *  
 * 
 */


#ifndef ACTION_H
#define ACTION_H

#include "MPane.h"
#include <list>
#include <string>
#include "windows.h"
#include "stdio.h"
#include <tchar.h>
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
	
	
	
protected:
	
	void executeProcess(string cmd);
	
	PROCESS_INFORMATION process_info;

	vector<string> argv;

	

};



#endif ACTION_H



