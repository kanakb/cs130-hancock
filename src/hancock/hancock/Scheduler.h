#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Action.h"
#include "MPane.h"
#include "log.h"
#include "ChildView.h"
#include <string>
#include <list>
#include <windows.h>
#include <sstream>

#define SLEEP_TIME 1000
#define WAITING 1
#define RUNNING 2
#define COMPLETED 3
#define UNSUCCESSFUL 4

class Scheduler{

public:

    struct actData{
		Action* m_action;
		string startTime;
		string endTime;
		int status;
		list<actData*> dependencies;
        list<actData*> dependents;
		list<string> inputs;
		list<string> outputs;
	};

	HancockLog* m_log;				// pointer to the instance of the current log
	MPane* m_mpane;					// pointer to MPane instance
	CChildView* m_view;				// pointer to the main view class

	Scheduler(HancockLog* hlog, MPane* mpane, CChildView *view);
	~Scheduler();
	
	//Adds a new action, starts if no dependencies, under threshold.
	void addAction(Action* task, list<actData*> inDependencies, list<string> inputs, list<string> outputs); 
	
	//Returns list of actions, statuses, start times, for UI.
	list<actData*>* getActList();

	//Returns any or all actions that 'task' takes input from.
	list<actData*> getDependencies(Action* task);

	//Returns true if dependencies=0, active actions < threshold
	bool canStart(Action* task);

	//Writes new threshold value to file, member variable
	void SetThreshold(int maxProc);

    //imports threshold value from file
	int getThresholdFromFile();

	//removes completed action
	void removeAction(Action* task);

	//returns current time in format (mm/dd/yy hh:mm)
	string formatTime();

	//returns the integer encoding of the action given the action's executable name
	int getActionInt(string exeName);

private:	
	HANDLE Handle_of_Thread_Loop;	// variable to hold handle of Thread
    list<actData*>* m_actions;
    DWORD WINAPI Thread_Loop (LPVOID lpParam);
	int threshold;
	int activeCount;                // current number of running actions
  	static DWORD WINAPI Scheduler::Thread_Start (LPVOID info)
	{
		return static_cast<Scheduler*>(info)->Thread_Loop(info);
	}
};

#endif