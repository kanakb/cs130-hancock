/*
 *  Action.cpp
 *  
 *
 */

// #include "stdafx.h" //!!!!!TEMPORARY!!!!!
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

	//LPTSTR szCmdline = _tcsdup(TEXT("Z:\\test.exe"));
	LPTSTR szCmdline = (LPTSTR)cmd.c_str();

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



/*
	//Optionally check for exe existance	
	STARTUPINFO si;
	SECURITY_ATTRIBUTES sa;
	//SECURITY_DESCRIPTOR sd;

	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;		// allow inheritable handles

	if (!CreatePipe(&newstdin,&write_stdin,&sa,0))		// create stdin pip
	{
		return;
	}

	if (!CreatePipe(&read_stdout,&newstdout,&sa,0))		// create stdout pipe
	{
		CloseHandle(newstdin);
		CloseHandle(write_stdin);
		return;
	}

    //PROCESS_INFORMATION pi;
		
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	// Validate hStd* and wShowWindow members
	GetStartupInfo(&si);				// set startupinfo for the spawned process
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = newstdout;
	si.hStdError = newstdout;			// set the new handles for the child process
	si.hStdInput = newstdin;
		
	if( !CreateProcess( NULL,								// Module name 			   
					   LPWSTR(cmd.c_str()),										// Command line	   
					   NULL,												// Process handle  
					   NULL,												// Thread handle
					   TRUE,												// Set handle inheritance to FALSE
					   0,													// No creation flags
					   NULL,												// Use parent's environment block
					   NULL,												// Use parent's starting directory 
					   &si,												// Pointer to STARTUPINFO structure
					   &pi )												// Pointer to PROCESS_INFORMATION structure
	   )	
	{
		//Create Process failed.
		CloseHandle(newstdin);
		CloseHandle(newstdout);
		CloseHandle(read_stdout);
		CloseHandle(write_stdin);
		return;
	}
	//process_info = pi;

*/
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
	// Close process and thread handles.
	
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return true;

	/*
	DWORD retCode = 0;
	GetExitCodeProcess(pi.hProcess, LPDWORD(retCode));
	
	if(retCode == STILL_ACTIVE)
	{
		return false;
	}
	
	status = retCode;

	unsigned long bread = 0;	// bytes read
	unsigned long avail = MAX_BUF_LEN;	// bytes available

	memset(buf,0,MAX_BUF_LEN);
	if (avail > (MAX_BUF_LEN - 1))
	{
		while (bread >= (MAX_BUF_LEN - 1))
		{
			ReadFile(read_stdout,buf,(MAX_BUF_LEN - 1),&bread,NULL);	// read the stdout pipe
			output += buf;
			memset(buf,0,MAX_BUF_LEN);
		}
	}
	else
	{
		ReadFile(read_stdout,buf,(MAX_BUF_LEN - 1),&bread,NULL);
		output += buf;
	}
	
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	CloseHandle(newstdin);
	CloseHandle(newstdout);
	CloseHandle(read_stdout);
	CloseHandle(write_stdin);

	return true;
	*/
}

int Action::getStatus()
{
	return status;
}

string Action::getName()
{
	return exeName;
}
