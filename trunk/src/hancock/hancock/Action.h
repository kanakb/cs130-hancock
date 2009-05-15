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
using namespace std;

/*** Define Status codes here ***/

class Action {

public:
	virtual void act();					//builds the cmd and runs the action
	virtual string getName();			//returns the name of the executable
	virtual bool isComplete();			//tells if process is done
	
	list<string> m_inputs;				//list of input files  (full path)
	list<string> m_outpus;				//list of output files (full path)
	string exePath;						//Location of the executable
	string exeName;						//Some way to refer to executable. 
	string m_symantecCfg;				//Path of the .cfg file used as input for the executable
	int status;							//status of action
	
};


#endif ACTION_H
