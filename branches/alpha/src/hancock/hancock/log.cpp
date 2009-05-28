#include "stdafx.h"
#include "log.h"


HancockLog::HancockLog(string path)
: dir(path)
{
	CString directory(dir.c_str());
	CreateDirectory(directory,0);
	
	ifstream infile("logdir.txt");
	if (!infile)
	{
		ofstream outfile("logdir.txt");
		outfile << path << endl;
		outfile.close();
	}
	else
	{
		getline(infile, dir);
	}

	SYSTEMTIME st;
	GetSystemTime(&st);
	filename = new char[256];
	sprintf_s(filename,256,"%s%02d.%02d.%d.%02d.%02d.%03d.txt",dir.c_str(),st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute,st.wMilliseconds);
	
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
	sprintf_s(time,256,"%02d.%02d.%d  %02d:%02d - ",st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute);
	return time;
}

char* HancockLog::getFileName(){
	return filename;
}

void HancockLog::write(const string &info){

	fout << getTimestamp() + info + "\r\n";
	curLog = curLog + getTimestamp() + info + "\r\n";
}

string HancockLog::dispCurrLog(){
	return curLog;
}

string HancockLog::dispLog(const char* fname){
	/*string s = fname;
	string t = filename;
	return t + "  " + s;*/
	if (strcmp(fname,filename)==0)
		return dispCurrLog();
	string line;
	string content;
	ifstream fin (fname);
	if (fin.is_open())
	{
		while (! fin.eof() )
		{
			getline (fin,line);
			if (content != "")
				content =  content + "\r\n" + line;
			else
				content = line;
		}
		fin.close();
	}

	else content = "Unable to open file\r\n"; 

	return content;

}

void HancockLog::setdir(const string &d)
{
	dir = d;
	ofstream outfile("logdir.txt");
	outfile << dir << endl;
	outfile.close();
}

string HancockLog::getDir(){
	return dir;
}
