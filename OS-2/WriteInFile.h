#pragma once
#include "windows.h"
#include <stdio.h>
#include <string>
using namespace std;

class WriteInFile
{
/*private:
	HANDLE hFileLog;
	HANDLE hFile;*/
public:
	//WriteInFile();
	//void writeNumberInFile(char* currentProcess, char* number);
	void writeNumberInFile(char* ch, HANDLE hFile);
	void writeErrorInLog(int codeError, HANDLE hFile);
	const char* getTime();
	void writeInLog(char* currentProcess, char* number, HANDLE hFile);
};