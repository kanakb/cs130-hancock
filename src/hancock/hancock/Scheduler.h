#pragma once

#include "Action.h"
#include <string>
#include <list>

class Sheduler{
	
	struct actData{
		Action* m_action;
		CString startTime;
		CString status;
	}


	list<actData*> m_actions;
	int threshold;
	
	//imports threshold value from file
	int getThresFromFile();

	//removes completed action
	void removeAction(Action* task);

	//returns current time in format (mm/dd/yy hh:mm)
	CString formatTime();


public:
	Sheduler();
	~Sheduler();
	
	//Adds a new action, starts if no dependencies, under threshold.
	void addAction(Action* task); 
	
	//Returns list of actions, statuses, start times, for UI.
	void getActList(list<CString>* ActList);

	//Returns any or all actions that 'task' takes input from.
	list<Action*> getDependencies(Action* task);

	//Returns true if dependencies=0, active actions < threshold
	bool canStart(Action* task);

	//Writes new threshold value to file, member variable
	void SetThreshold(int maxProc);
};
