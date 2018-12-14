#pragma once
#include "windows.h"
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

#define FILE_NAME "File.txt"
#define FILE_LOG_NAME "log.txt"

class WriteInFile
{
private:
	/*HANDLE hFileLog;
	HANDLE hFile;*/
public:
	void clearFile();
	void writeNumberInFile(char* number);
	void writeInLog(char* process, char* number);
	//WriteInFile();
	//void writeNumberInFile(char* currentProcess, char* number);
	/*void writeNumberInFile(char* ch, HANDLE hFile);
	void writeErrorInLog(int codeError, HANDLE hFile);
	const char* getTime();
	void writeInLog(char* currentProcess, char* number, HANDLE hFile);*/
};