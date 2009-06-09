#include "stdafx.h"
#include "Scheduler.h"

DWORD WINAPI Scheduler::Thread_Loop (LPVOID lpParam)
{		
	list<actData*>::iterator it;
	list<actData*>* actionList /*= new list<actData*>*/;
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

			// Make sure all dependents of failed tasks also are marked as failed
			if ((*it)->status == UNSUCCESSFUL)
			{
				list<actData*>::iterator dit;
				for (dit = (*it)->dependents.begin(); dit != (*it)->dependents.end(); dit++)
				{
					(*dit)->status = UNSUCCESSFUL;
					(*dit)->endTime = (*it)->endTime;
				}
			}
	        
			else if ((*it)->status == RUNNING && (*it)->m_action->isComplete())		// if task has completed
			{
				list<actData*>::iterator dit;
				
				// remove the completed task from the dependency lists of its dependents
				for (dit = (*it)->dependents.begin(); dit != (*it)->dependents.end(); dit++)
					(*dit)->dependencies.remove(*it);
				
				// update the status of the task and the internal active task count
				if((*it)->m_action->status == 0)		// action returned with 0 status, completed sucessfully
					(*it)->status = COMPLETED;
				else
				{
					(*it)->status = UNSUCCESSFUL;

					// Mark dependents as unsuccessful
					for (dit = (*it)->dependents.begin(); dit != (*it)->dependents.end(); dit++)
					{
						(*dit)->status = UNSUCCESSFUL;
						string logStr = (*dit)->m_action->exeName + " could not be started.";
						((Scheduler*)lpParam)->m_log->write(logStr);
					}
				}
				activeCount--;

				// Logs the status of the completed action
				(*it)->endTime = ((Scheduler*)lpParam)->formatTime();
				string logStr = "";
				logStr += (*it)->m_action->exeName;
				if((*it)->status == COMPLETED)
					logStr += " completed successfully.";
				else
					logStr += " did not complete successfully.";
				((Scheduler*)lpParam)->m_log->write(logStr);
				
				// Send a status update to the MPane
				if ((*it)->status == COMPLETED)
				{
					((Scheduler*)lpParam)->m_mpane->updateCnfAction(((Scheduler*)lpParam)->getActionInt((*it)->m_action->exeName),(*it)->inputs,(*it)->outputs);
					((Scheduler*)lpParam)->m_view->updateCurrentFolder();
				}

				// For Cluster File and Find Signature actions, we must also write the output
				// of the actions to the file specified by optionalOutfile
				// Otherwise, save output to the AppOutput directory
				if((*it)->status == COMPLETED)
				{
					if((*it)->m_action->exeName == "FileClust.exe" || (*it)->m_action->exeName == "FindSigs.exe")
					{
						ofstream output((*it)->m_action->m_optionalOutfile.c_str(),ios_base::app|ios_base::out);
						if(output.is_open())	// file opened successfully
						{
							//output << endl;		// begin adding output to the next line
							output << (*it)->m_action->output;	// write the output to the file
							output.close();		// close file
							// log that the action output was saved to the user specified file
							((Scheduler*)lpParam)->m_log->write("Output of action saved in the file: "+(*it)->m_action->m_optionalOutfile);
						}
						else
						{
							// there was an error in opening the file, output an error to the log file
							((Scheduler*)lpParam)->m_log->write("The following file could not be opened for writing: ");
							((Scheduler*)lpParam)->m_log->write("      "+(*it)->m_action->m_optionalOutfile);
						}
					}
				}

				// Saving all output to AppOutput, even if it's unsuccessful
				CString directory(_T("AppOutput"));
				CreateDirectory(directory, 0);
				string fileTime = (*it)->startTime;
				for (size_t ind = 0; ind < fileTime.size(); ind++)
				{
					if (fileTime[ind] == ' ' || fileTime[ind] == ':' || fileTime[ind] == '/')
						fileTime[ind] = '_';
				}
				string outFileName = "AppOutput\\" + (*it)->m_action->exeName + "_" + fileTime + ".txt";
				ofstream output(outFileName.c_str(), ios_base::app | ios_base::out);
				if(output.is_open())	// file opened successfully
				{
					//output << endl;		// begin adding output to the next line
					output << (*it)->m_action->output;	// write the output to the file
					output.close();		// close file
					// log that the action output was saved to the user specified file
					((Scheduler*)lpParam)->m_log->write("Output of action saved in the file: "+outFileName);
				}
				else
				{
					// there was an error in opening the file, output an error to the log file
					((Scheduler*)lpParam)->m_log->write("The following file could not be opened for writing: ");
					((Scheduler*)lpParam)->m_log->write("      "+outFileName);
				}

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
					bool isStarted = (*it)->m_action->act();
					if (isStarted)
					{
						activeCount++;
						(*it)->status = RUNNING;

						// Logs that a new action has been started.
						string logStr = "";
						logStr += (*it)->m_action->exeName+" has been started.";
						((Scheduler*)lpParam)->m_log->write(logStr);
					}
					else
					{
						(*it)->status = UNSUCCESSFUL;
						string logStr = (*it)->m_action->exeName+" could not be started.";
						(*it)->endTime = ((Scheduler*)lpParam)->formatTime();
					}
				}
				list<actData*>::iterator itDep = (*it)->dependencies.begin();
				while (itDep != (*it)->dependencies.end())
				{
					if ((*itDep)->status != WAITING && (*itDep)->status != RUNNING)
						itDep = (*it)->dependencies.erase(itDep);
					else
						itDep++;
				}
			}

			it++;
			continue;
		}
		Sleep(SLEEP_TIME);
	}
}

Scheduler::Scheduler(HancockLog* hlog, MPane* mpane, CChildView* view)
:m_log(hlog), m_mpane(mpane), m_view(view)
{
	threshold = getThresholdFromFile();
	activeCount = 0;
	m_actions = new list<actData*>;
	
	Handle_of_Thread_Loop = 0;
    Handle_of_Thread_Loop = CreateThread (NULL, 0, &Scheduler::Thread_Start, (LPVOID*)this, 0, NULL);
	if (Handle_of_Thread_Loop == NULL)
	{
		m_log->write("Scheduler thread creation failed!!");
		ExitProcess(0);
	}
}

Scheduler::~Scheduler()
{
	delete m_log;
	list<actData*>::iterator it = m_actions->begin();
	for (; it != m_actions->end(); it++)
	{
		if (*it != NULL)
		{
			delete (*it)->m_action;
			delete *it;
		}
	}
	delete m_actions;
	CloseHandle(Handle_of_Thread_Loop);
}

//imports threshold value from file
int Scheduler::getThresholdFromFile()
{
	int thresh=0;
	string toLog;
	stringstream threshStr;
	ifstream thresholdFile("threshold.txt",ios_base::in);		// attempt to open threshold file
	if(!thresholdFile.is_open())			// threshold file does not exist yet
	{
		toLog = "Error: Threshold file does not exist.";
		m_log->write(toLog.c_str());
		threshold = 25;			// this is an arbitrary limit I am setting
		thresh = 25;
		ofstream outFile("threshold.txt");
		outFile << thresh << endl;
	}
	else
	{
		thresholdFile >> thresh;
		thresholdFile.close();
		threshStr << thresh;
		toLog = "Setting threshold to: "+threshStr.str();
		m_log->write(toLog.c_str());
	}
	return thresh;
}

//removes completed action
void Scheduler::removeAction(Action* task)
{
	list<actData*>::iterator it;
	
	for (it = m_actions->begin(); it != m_actions->end(); it++)
    {
		if (((*it)->m_action == task) && ((*it)->m_action->status == COMPLETED))
		{			
			(*it)->endTime = formatTime();
            m_actions->remove(*it);
			delete *it;
			*it = NULL;
			return;
		}
	}
}

//returns current time in format (mm/dd/yy hh:mm)
string Scheduler::formatTime()
{
	SYSTEMTIME st; 
	GetSystemTime(&st); 

	char time[256];
	sprintf_s(time,256, "%02d/%02d/%02d %02d:%02d", st.wMonth,st.wDay,st.wYear,st.wHour, st.wMinute);

	return time;

}
	
//Adds a new action, starts if no dependencies, under threshold.
void Scheduler::addAction(Action* task, list<actData*> inDependencies, list<string> inputs, list<string> outputs)
{
	actData* toAdd = new actData;
	toAdd->m_action = task;
	toAdd->startTime = formatTime();
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
	list<actData*> emptyList;
			
	for (it = m_actions->begin(); it != m_actions->end(); it++)
	{
		if ((*it)->m_action == task)
			return ((*it)->dependencies);
	}
	return emptyList;
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
	threshold = maxProc;
	string toLog;
	stringstream threshStr;
	ofstream thresholdFile("threshold.txt",ios_base::trunc);		// attempt to open threshold file
	if(!thresholdFile.is_open())			// file could not be opened ??
	{
		toLog = "Error: Threshold file could not be opened. Update Failed!";
		m_log->write(toLog.c_str()); 
	}
	else
	{
		thresholdFile << maxProc;
		thresholdFile.close();
		threshStr << maxProc;
		toLog = "Updating threshold file to: "+threshStr.str();
		m_log->write(toLog.c_str());
	}
}

// Returns the integer encoding of the action given the action's executable name
int Scheduler::getActionInt(string exeName)
{
	int actionInt = 0; // unknown initially
	
	if(exeName == "GetPEBuffers.exe")
	{
		actionInt = 100;
	}
	else if(exeName == "CreateModel.exe")
	{
		actionInt = 101;
	}
	else if(exeName == "CreateBinIndex.exe")
	{
		actionInt = 102;
	}
	else if(exeName == "PruneModel.exe")
	{
		actionInt = 200;
	}
	else if(exeName == "MergeModels.exe")
	{
		actionInt = 201;
	}
	else if(exeName == "CompileModel.exe")
	{
		actionInt = 202;
	}	
	else if(exeName == "StubGen.exe")
	{
		actionInt = 203;
	}
	else if(exeName == "FindSigs.exe")
	{
		actionInt = 300;
	}
	else if(exeName == "PreProcMalware.exe")
	{
		actionInt = 400;
	}
	else if(exeName == "FileClust.exe")
	{
		actionInt = 500;
	}
	return actionInt;
}
