#include "stdafx.h"
#include "Scheduler.h"

DWORD WINAPI Scheduler::Thread_Loop (LPVOID lpParam)
{		
	list<actData*>::iterator it;
	list<actData*>* actionList = new list<actData*>;
	actionList = ((Scheduler*)lpParam)->getActList();
	
	while(actionList->empty())
	{
		Sleep(SLEEP_TIME);
	}
	it = ((Scheduler*)lpParam)->getActList()->begin();
	
	while (true)
	{
		if(!actionList->empty())			// if there are tasks in the m_actions list
		{
			if (it == actionList->end())	// if we have gone through the list already, start at the beginning
			{
				it = actionList->begin();
				Sleep(SLEEP_TIME);
			}
	        
			if ((*it)->status == RUNNING && (*it)->m_action->isComplete())		// if task has completed
			{
				list<actData*>::iterator dit;
				
				// remove the completed task from the dependency lists of its dependents
				for (dit = (*it)->dependents.begin(); dit != (*it)->dependents.end(); dit++)
					(*dit)->dependencies.remove(*it);
				
				// update the status of the task and the internal active task count
				(*it)->status = COMPLETED;
				activeCount--;

				// Logs the status of the completed action
				string logStr = ((Scheduler*)lpParam)->formatTime();
				logStr += " "+(*it)->m_action->exeName+" completed with status: "+(*it)->m_action->output;
				((Scheduler*)lpParam)->m_log->write(logStr);

				// TODO: Here is where the call to the MPane function should go
				// Prabhu, Kanak I have added 2 variables to the actData structure soleley for the purpose
				// of making this task easier: list<string> inputs   &   list<string outputs
				// They can be accessed in this manner:  (*it)->inputs   and   (*it)->outputs
				// This also means that the MPane function signature needs to be:
				//      function(list<string> inputs, list<string outputs)
				// Also, Kanak, you will need to pass these in to the addAction call as well so that they
				// are properly initialized.
				// Below I have written a placeholder for the call to the MPane function:
				//		((Scheduler*)lpParam)->m_mpane->the_function_here((*it)->inputs,(*it)->outputs);
			}

			else if ((*it)->status == RUNNING)
			{
				// It's still running. Don't do anything
			}

			else if ((*it)->status == WAITING)
			{
				if ((*it)->dependencies.empty() && activeCount < threshold)
				{
					(*it)->startTime = formatTime();
					(*it)->m_action->act();
					activeCount++;
					(*it)->status = RUNNING;

					// Logs that a new action has been started.
					string logStr = ((Scheduler*)lpParam)->formatTime();
					logStr += " "+(*it)->m_action->exeName+" has been started.";
					((Scheduler*)lpParam)->m_log->write(logStr);
				}
			}

			it++;
			continue;
		}
		Sleep(SLEEP_TIME);
	}
}

Scheduler::Scheduler(HancockLog* hlog,MPane* mpane)
:m_log(hlog),m_mpane(mpane)
{
	//cout<<"Initializing Scheduler..."<<endl;
	threshold = getThresholdFromFile();
	activeCount = 0;
	//m_actions = (list<actData*>*) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(list<Scheduler::actData>));
	m_actions = new list<actData*>;
	
	Handle_of_Thread_Loop = 0;
    Handle_of_Thread_Loop = CreateThread (NULL, 0, &Scheduler::Thread_Start, (LPVOID*)this, 0, NULL);
	if (Handle_of_Thread_Loop == NULL)
	{
		cout << "Thread creation failed." << endl;
		ExitProcess(0);
	}
}

Scheduler::~Scheduler()
{
	delete m_log;
	delete m_actions;
	CloseHandle(Handle_of_Thread_Loop);
}

//imports threshold value from file
int Scheduler::getThresholdFromFile()
{
	// Sargis: You figure this out.
	return 2;
}

//removes completed action
void Scheduler::removeAction(Action* task)
{
	list<actData*>::iterator it;
	
	for (it = m_actions->begin(); it != m_actions->end(); it++)
    {
		if (((*it)->m_action == task) && ((*it)->m_action->status == COMPLETED))
		{			
            m_actions->remove(*it);
			delete *it;
			return;
		}
	}
}

//returns current time in format (mm/dd/yy hh:mm)
string Scheduler::formatTime()
{
	// ...
	return "";
}
	
//Adds a new action, starts if no dependencies, under threshold.
void Scheduler::addAction(Action* task, list<actData*> inDependencies, list<string> inputs, list<string> outputs)
{
	actData* toAdd = new actData;
	toAdd->m_action = task;
	toAdd->startTime = "";
	toAdd->status = WAITING;
	toAdd->inputs = inputs;
	toAdd->outputs = outputs;
	if(inDependencies.empty())		// if there are no dependencies, 
	{
		m_actions->push_back(toAdd);	// add the actData of this task to the m_actions list
		return;	
	}
	toAdd->dependencies = inDependencies;
	list<actData*>::iterator it;        // list iterator for dependencies list
    list<actData*>::iterator mit;       // list iterator for m_actions list
    for(it = inDependencies.begin(); it != inDependencies.end(); it++)  // for each dependency of this action
    {   
        for(mit = m_actions->begin(); mit != m_actions->end(); mit++)     // search through m_actions for the action
        {
            if( (*it)->m_action == (*mit)->m_action )                   // if this is the action we are looking for
            {
                (*mit)->dependents.push_back(toAdd);                      // add the new task as its dependent
            }
        }
    }
    m_actions->push_back(toAdd);
}
	
//Returns list of actions, statuses, start times, for UI.
list<Scheduler::actData*>* Scheduler::getActList()
{
		return m_actions;
}

//Returns any or all actions that 'task' takes input from.
list<Scheduler::actData*> Scheduler::getDependencies(Action* task)
{
	list<actData*>::iterator it;
			
	for (it = m_actions->begin(); it != m_actions->end(); it++)
	{
		if ((*it)->m_action == task)
			return ((*it)->dependencies);
	}
}

//Returns true if dependencies=0, active actions < threshold
bool Scheduler::canStart(Action* task)
{
	list<actData*>::iterator it;
	int counter=0;
	bool mayStart = false;
	bool foundIt = false;
			
	for (it = m_actions->begin(); it != m_actions->end(); it++)
    {
        if ((*it)->status == RUNNING)
			counter++;

		if ((*it)->m_action == task)
		{
			foundIt = true;

			if ((*it)->dependencies.empty())
				mayStart = true;
		}
	}

	if (foundIt && mayStart && (counter < threshold))
		return true;

	return false;
}

//Writes new threshold value to file, member variable
void Scheduler::SetThreshold(int maxProc)
{
		// Sargis: You figure this out.
}
