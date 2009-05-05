#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stdio.h>

const char DIR[256] = "Logs\\";
// feature request: create directory if it doesn't exist

using namespace std;

class HancockLog{

	char* filename;
	ofstream fout;
	string curLog;
	string getTimestamp();

public:
	HancockLog();
	~HancockLog();
	void write(string info);
	char* getFileName();
	string dispLog(const char* filename);
	string dispCurrLog();
};
