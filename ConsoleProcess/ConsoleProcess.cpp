#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include "../OS-2/WriteInFile.h"
using namespace std;

#define MAP_VIEW_OF_FILE_ERROR 2
#define OPEN_SEMAPHORE_ERROR 3
#define OPEN_FILE_MAPPING_ERROR 4

int main()
{
	WriteInFile writeInFile;
	HANDLE semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("MainProcessSemaphore"));
	HANDLE fileMapping = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("FileMapping"));


	//bool key = true;
	if (semaphore == NULL)
	{
		writeInFile.writeErrorInLog("Error of OpenSemaphore", OPEN_SEMAPHORE_ERROR);
		return OPEN_SEMAPHORE_ERROR;
	}
	if (fileMapping == NULL)
	{
		writeInFile.writeErrorInLog("Error of OpenFileMapping", OPEN_FILE_MAPPING_ERROR);
		return OPEN_FILE_MAPPING_ERROR;
	}
	char* ch = (char*)MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0);
	if (ch == NULL)
	{
		writeInFile.writeErrorInLog("Error of MapViewOfFile", MAP_VIEW_OF_FILE_ERROR);
		return MAP_VIEW_OF_FILE_ERROR;
	}
	while (true)
	{
		WaitForSingleObject(semaphore, INFINITE);
		cout << "CP: ";
		cout << ch << "\n";
		writeInFile.writeInLog("CP", ch);
	}
}