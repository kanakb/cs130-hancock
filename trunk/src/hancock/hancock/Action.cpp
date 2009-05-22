/*
 *  Action.cpp
 *  
 *
 */

#include "stdafx.h" 
#include "Action.h"

Action::Action()
{
	exeName = "";
	exePath = "";
	m_symantecCfg = "";
	status = -1;	
}

Action::Action(string path, string name, vector<string> &params)
{
	exeName = name;
	exePath = path;
	m_symantecCfg = "";
	status = -1;
	argv = params;
}

Action::Action(string path, string name, string cfg)
{
	exeName = name;
	exePath = path;
	m_symantecCfg = cfg;
	status = -1;
}

void Action::executeProcess(string cmd){
	
	//Optionally check for exe existance	
	STARTUPINFO si;	
    //PROCESS_INFORMATION pi;		
	
    ZeroMemory( &si, sizeof(si) );	
    si.cb = sizeof(si);	
    ZeroMemory( &pi, sizeof(pi) );	

	LPTSTR szCmdline = _tcsdup(TEXT("Z:\\test.exe"));

	if( !CreateProcess( NULL,												// Module name 					   
					   szCmdline,									// Command line					   
					   NULL,												// Process handle					   
					   NULL,												// Thread handle					   
					   FALSE,												// Set handle inheritance to FALSE					   
					   0,													// No creation flags					   
					   NULL,												// Use parent's environment block					   
					   NULL,												// Use parent's starting directory 
					   &si,													// Pointer to STARTUPINFO structure
					   &pi )												// Pointer to PROCESS_INFORMATION structure
	   )	
	{
		//Create Process failed.
		cout<<"Create Process Failed! Error:"<<GetLastError()<<endl;
	}	




}

void Action::act()
{
	if(m_symantecCfg.length())
		executeProcess("\""+exePath+exeName+"\""+" "+m_symantecCfg);
	else
	{
		string cmd = "";
		for(vector<string>::iterator it = argv.begin(); it != argv.end(); it++)
		{	
			cmd+=(" " + *it);	
		}
		executeProcess("\""+exePath+exeName+"\""+cmd);
	}
}



bool Action::isComplete()
{
	DWORD retCode = 0;	
	if(!GetExitCodeProcess(pi.hProcess, &retCode))
	{
		cout<<"Could not get Exit Code! Error: "<<GetLastError()<<endl;
	}
	
	if(retCode == STILL_ACTIVE)		
	{
		return false;		
	}
	
	cout<<endl<<"Done!!!!"<<endl;
	status = retCode;	
	// Close process and thread handles.
	
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return true;

	
}

int Action::getStatus()
{
	return status;
}

string Action::getName()
{
	return exeName;
}
