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
	
    PROCESS_INFORMATION pi;
	
	
	
    ZeroMemory( &si, sizeof(si) );
	
    si.cb = sizeof(si);
	
    ZeroMemory( &pi, sizeof(pi) );
	
	
	
	if( !CreateProcess( NULL,								// Module name 
					   
					   LPWSTR(cmd.c_str()),										// Command line
					   
					   NULL,												// Process handle
					   
					   NULL,												// Thread handle
					   
					   FALSE,												// Set handle inheritance to FALSE
					   
					   0,													// No creation flags
					   
					   NULL,												// Use parent's environment block
					   
					   NULL,												// Use parent's starting directory 
					   
					   &si,												// Pointer to STARTUPINFO structure
					   
					   &pi )												// Pointer to PROCESS_INFORMATION structure
	   
	   )
		
	{
		
		//Create Process failed.
		
	}
	
	process_info = pi;
	
}



void Action::act()

{
	
	if(!m_symantecCfg.length())
		
		executeProcess(exePath+exeName+" "+m_symantecCfg);
	
	else
		
	{
		
		string cmd = "";
		
		for(vector<string>::iterator it = argv.begin(); it != argv.end(); it++)
			
		{
			
			cmd+=(" " + *it);
			
		}
		
		executeProcess(exePath+exeName+cmd);
		
	}
	
}



bool Action::isComplete()

{
	
	DWORD retCode = 0;
	
	GetExitCodeProcess(process_info.hProcess, LPDWORD(retCode));
	
	
	
	if(retCode == STILL_ACTIVE)
		
	{
		
		return false;
		
	}
	
	
	
	status = retCode;
	
	// Close process and thread handles. 
	
	CloseHandle( process_info.hProcess );
	CloseHandle( process_info.hThread );


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