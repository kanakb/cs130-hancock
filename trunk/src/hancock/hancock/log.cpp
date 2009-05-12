#include "stdafx.h"
#include "log.h"

HancockLog::HancockLog(string path)
: dir(path)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	filename = new char[256];
	sprintf_s(filename,256,"%s%d.%d.%d.%d.%d.txt",dir.c_str(),st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute);
	
	fout.open(filename);
	
	this->write("Log Created.");

		
}

HancockLog::~HancockLog()
{
	delete filename;
	fout.close();
}

string HancockLog::getTimestamp(){
	SYSTEMTIME st;
	GetSystemTime(&st);
	char time[256];
	sprintf_s(time,256,"%d.%d.%d  %d:%d - ",st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute);
	return time;
}

char* HancockLog::getFileName(){
	return filename;
}

void HancockLog::write(string info){

	fout << getTimestamp() + info + "\n";
	curLog = curLog + getTimestamp() + info + "\n";
}

string HancockLog::dispCurrLog(){
	return curLog;
}

string HancockLog::dispLog(const char* filename){

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

void HancockLog::setdir(string d)
{
	dir = d;
}
