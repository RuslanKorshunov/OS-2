#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include "../OS-2/WriteInFile.h"
using namespace std;

void main(VOID)
{
	WriteInFile writeInFile;
	HANDLE semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("MainProcessSemaphore"));
	HANDLE fileMapping = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("FileMapping"));


	bool key = true;
	if (semaphore == NULL)
	{
		cout << "Error of OpenSemaphore" << endl;
		key = false;
	}
	if (fileMapping == NULL)
	{
		cout << "Error of OpenFileMapping" << endl;
		key = false;
	}
	char* ch = (char*)MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0);
	if (ch == NULL)
	{
		cout << "Error of MapViewOfFile" << endl;
		key = false;
	}
	if (key != false)
		while (true)
		{
			WaitForSingleObject(semaphore, INFINITE);
			cout << "CP: ";
			cout << ch << "\n";
			writeInFile.writeInLog("CP", ch);
		}
}