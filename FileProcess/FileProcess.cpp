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
	HANDLE fileMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, TEXT("FileMapping"));
	//HANDLE hFile = CreateFile(TEXT("File.txt"), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//bool key = true;
	if (semaphore == NULL)
	{
		/*cout << "Error of OpenSemaphore" << endl;
		key = false;*/
		writeInFile.writeErrorInLog("Error of OpenSemaphore", OPEN_SEMAPHORE_ERROR);
		return OPEN_SEMAPHORE_ERROR;
	}
	if (fileMapping == NULL)
	{
		/*cout << "Error of OpenFileMapping" << endl;
		key = false;*/
		writeInFile.writeErrorInLog("Error of OpenFileMapping", OPEN_FILE_MAPPING_ERROR);
		return OPEN_FILE_MAPPING_ERROR;
	}
	/*if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Error of CreateFile" << endl;
		key = false;
	}*/
	char* ch = (char*)MapViewOfFile(fileMapping, FILE_MAP_WRITE, 0, 0, 0);
	if (ch == NULL)
	{
		/*cout << "Error of MapViewOfFile" << endl;
		key = false;*/
		writeInFile.writeErrorInLog("Error of MapViewOfFile", MAP_VIEW_OF_FILE_ERROR);
		return MAP_VIEW_OF_FILE_ERROR;
	}
	//if (key != false)
	while (true)
	{
		WaitForSingleObject(semaphore, INFINITE);
		cout << "FP" << endl;
		writeInFile.writeNumberInFile(ch);
		/*WriteFile(hFile, ch, sizeof(ch), NULL, NULL);
		WriteFile(hFile, "\n", sizeof("\n"), NULL, NULL);*/
	}
}