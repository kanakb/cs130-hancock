#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stdio.h>

const char DIR[256] = "";

using namespace std;

class Log{

	char* filename;
	ofstream fout;
	string curLog;

public:
	Log();
	~Log();
	void write(string info);
	char* getFileName();
	string dispLog(const char* filename);
	string dispCurrLog();
};

string timestamp(){
	SYSTEMTIME st;
	GetSystemTime(&st);
	char time[256];
	sprintf_s(time,256,"%d.%d.%d  %d:%d - ",st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute);
	return time;
}

Log::Log(){
	SYSTEMTIME st;
	GetSystemTime(&st);
	filename = new char[256];
	sprintf_s(filename,256,"%s%d.%d.%d.%d.%d.txt",DIR,st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute);
	
	fout.open(filename);
	
	this->write("Log Created.");

		
}

Log::~Log()
{
	delete filename;
	fout.close();
}

char* Log::getFileName(){
	return filename;
}

void Log::write(string info){

	fout << timestamp() + info + "\n";
	curLog = curLog + timestamp() + info + "\n";
}

string Log::dispCurrLog(){
	return curLog;
}

string Log::dispLog(const char* filename){

	string line;
	string content;
	ifstream fin (filename);
	if (fin.is_open())
	{
		while (! fin.eof() )
		{
			getline (fin,line);
			content =  content + "\n" + line;
		}
		fin.close();
	}

	else content = "Unable to open file\n"; 

	return content;

}

#endif