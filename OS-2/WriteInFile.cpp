#include "windows.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "WriteInFile.h"
using namespace std;


void WriteInFile::clearFile()
{
	fstream fout(FILE_NAME, fstream::trunc|fstream::app);
	fout << "";
	fout.close();
	fout.open(FILE_LOG_NAME, fstream::trunc|fstream::app);
	fout << "";
	fout.close();
}
void WriteInFile::writeNumberInFile(char*number)
{
	fstream fout(FILE_NAME, ios_base::app);

	fout << number << endl;

	fout.close();

	writeInLog("FP", number);
}
void WriteInFile::writeInLog(char* process, char* number)
{
	fstream fout(FILE_LOG_NAME, ios_base::app);

	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	string s_time = to_string(systemtime.wHour) + ':' + to_string(systemtime.wMinute) + ':' + to_string(systemtime.wSecond) + ':' + to_string(systemtime.wMilliseconds);
	const char* ch_time = s_time.c_str();
	fout << ch_time << "  " << process << "  " << number << endl;

	fout.close();
}
const char* WriteInFile::getTime()
{
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	string s_time = to_string(systemtime.wHour) + ':' + to_string(systemtime.wMinute) + ':' + to_string(systemtime.wSecond) + ':' + to_string(systemtime.wMilliseconds);
	const char* ch_time = s_time.c_str();

	return ch_time;
}
void WriteInFile::writeErrorInLog(char* message, int codeOfError)
{
	fstream fout(FILE_LOG_NAME, ios_base::app);

	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	string s_time = to_string(systemtime.wHour) + ':' + to_string(systemtime.wMinute) + ':' + to_string(systemtime.wSecond) + ':' + to_string(systemtime.wMilliseconds);
	const char* ch_time = s_time.c_str();
	fout << ch_time << "  " << message << "  " << codeOfError << endl;

	fout.close();
}
/*WriteInFile::WriteInFile()
{
hFileLog = CreateFile(TEXT("log.txt"), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
hFile = CreateFile(TEXT("File.txt"), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}*/
/*void WriteInFile::writeNumberInFile(char* ch, HANDLE hFile)
{
WriteFile(hFile, ch, sizeof(ch), NULL, NULL);
WriteFile(hFile, "\n", sizeof("\n"), NULL, NULL);

}
void WriteInFile::writeErrorInLog(int codeError, HANDLE hFileLog)
{
string s_codeError = to_string(codeError);
const char* ch_codeError = s_codeError.c_str();
const char* ch_time = getTime();
WriteFile(hFileLog, ch_time, sizeof(ch_time) * 3, NULL, NULL);
WriteFile(hFileLog, " ", sizeof(" "), NULL, NULL);
WriteFile(hFileLog, "Error", sizeof("Error"), NULL, NULL);
WriteFile(hFileLog, " ", sizeof(" "), NULL, NULL);
WriteFile(hFileLog, ch_codeError, sizeof(ch_codeError), NULL, NULL);
WriteFile(hFileLog, "\n", 1, NULL, NULL);
}
const char* WriteInFile::getTime()
{
SYSTEMTIME systemtime;
GetLocalTime(&systemtime);
string s_time = to_string(systemtime.wHour) + ':' + to_string(systemtime.wMinute) + ':' + to_string(systemtime.wSecond) + ':' + to_string(systemtime.wMilliseconds);
const char* ch_time = s_time.c_str();
return ch_time;
}
void WriteInFile::writeInLog(char* currentProcess, char* number, HANDLE hFileLog)
{
const char* ch_time = getTime();
WriteFile(hFileLog, ch_time, sizeof(ch_time) * 3, NULL, NULL);
WriteFile(hFileLog, " ", sizeof(" "), NULL, NULL);
WriteFile(hFileLog, currentProcess, sizeof(char) * 2, NULL, NULL);
WriteFile(hFileLog, " ", sizeof(" "), NULL, NULL);
WriteFile(hFileLog, number, sizeof(number), NULL, NULL);
WriteFile(hFileLog, "\n", 1, NULL, NULL);
}*/