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
	SECURITY_ATTRIBUTES sa;
	//SECURITY_DESCRIPTOR sd;

	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;		// allow inheritable handles

	if (!CreatePipe(&stdout_from_child,&stdout_in_child,&sa,0))		// create stdoutpipe
	{
		return;
	}

	if ( ! SetHandleInformation(stdout_from_child, HANDLE_FLAG_INHERIT, 0) )
      return; 

    //PROCESS_INFORMATION pi;
		
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	// Validate hStd* and wShowWindow members
	GetStartupInfo(&si);				// set startupinfo for the spawned process
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.hStdOutput = stdout_in_child;
	si.hStdError = stdout_in_child;			// set the new handles for the child process	

	//LPTSTR szCmdline = _tcsdup(TEXT("Z:\\test.exe"));
	//LPTSTR szCmdline = (LPTSTR)cmd.c_str();
	CString cmdline(cmd.c_str());
	LPTSTR szCmdline = T2W(cmdline.GetBuffer());

	if( !CreateProcess( NULL,												// Module name 					   
					   szCmdline,											// Command line					   
					   NULL,												// Process handle					   
					   NULL,												// Thread handle					   
					   TRUE,												// Set handle inheritance to TRUE					   
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
	
	status = retCode;	

	unsigned long bread = 0;	// bytes read
	
	memset(buf,0,MAX_BUF_LEN);
	do
	{
		if(!ReadFile(stdout_from_child,buf,(MAX_BUF_LEN - 1),&bread,NULL))// read the stdout pipe
		{
			cout<<"Error reading pipe: "<<GetLastError()<<endl;
			return true;
		}
		output+=buf;
		memset(buf,0,MAX_BUF_LEN);
	}while(bread==MAX_BUF_LEN - 1);
	
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	CloseHandle(stdout_in_child);
	CloseHandle(stdout_from_child);

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
