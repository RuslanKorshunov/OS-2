#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <ctime>
#include <string>
#include "WriteInFile.h"
using namespace std;

#define CREATE_PROCESS_ERROR 1
#define MAP_VIEW_OF_FILE_ERROR 2

//HANDLE hFileLog = CreateFile(TEXT("log.txt"), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

typedef struct
{
	STARTUPINFO startupinfo;//структура, используемая с функ-й CreateProcess, чтобы определить оконный терминал, раб. стол, 
							//стандарт. дескриптор, внешний вид осн. окна для нового процесса
	PROCESS_INFORMATION process_information;
	//структура заполняется функцией CreateProcess с информацией о недавно созданном процессе и его первичном потоке
} processDate;

processDate initializationProcDate()
{
	processDate pd;
	ZeroMemory(&pd.startupinfo, sizeof(pd.startupinfo));
	pd.startupinfo.cb = sizeof(pd.startupinfo);
	ZeroMemory(&pd.process_information, sizeof(pd.process_information));
	return pd;
}

void close(processDate pd)
{
	CloseHandle(pd.process_information.hProcess);
	CloseHandle(pd.process_information.hThread);
}

BOOL createProcess(TCHAR commandLine[], processDate  pd)
{
	return CreateProcess(NULL,//имя приложения; должно содержать полный путь или NULL
		commandLine,//командная строка. ПОЧИТАЙ ДОКУМЕНТАЦИЮ
		NULL,//атрибуты процесса
		NULL,//атрибуты потока
		FALSE,//нследование дескрипторов
		0,//создание флагов
		NULL,//среда
		NULL,//текущая директория
		&pd.startupinfo,
		&pd.process_information);
}

/*void log(char* currentProcess, char* number)
{
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	string s_time = to_string(systemtime.wHour) + ':' + to_string(systemtime.wMinute) + ':' + to_string(systemtime.wSecond) + ':' + to_string(systemtime.wMilliseconds);
	const char* ch_time = s_time.c_str();
	WriteFile(hFileLog, ch_time, sizeof(ch_time) * 3, NULL, NULL);
	WriteFile(hFileLog, " ", sizeof(" "), NULL, NULL);
	WriteFile(hFileLog, currentProcess, sizeof(char) * 2, NULL, NULL);
	WriteFile(hFileLog, " ", sizeof(" "), NULL, NULL);
	WriteFile(hFileLog, number, sizeof(number), NULL, NULL);
	WriteFile(hFileLog, "\n", 1, NULL, NULL);
}*/

void _tmain(int argc, TCHAR *argv[])
{
	HANDLE semaphore = CreateSemaphore(NULL, 0, 2, TEXT("MainProcessSemaphore"));
	HANDLE fileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int), TEXT("FileMapping"));;

	TCHAR consoleProcessCL[] = TEXT("ConsoleProcess");
	TCHAR fileProcessCL[] = TEXT("FileProcess");

	WriteInFile writeInFile;
	writeInFile.clearFile();

	int buffer[20];

	srand(time(0));
	for (int i = 0; i < 20; i++)
		buffer[i] = rand() % 1000 + 1;

	processDate consoleData = initializationProcDate();
	processDate fileData = initializationProcDate();

	BOOL cpSuccess = createProcess(consoleProcessCL, consoleData);
	BOOL fpSuccess = createProcess(fileProcessCL, fileData);

	//if (createProcess(consoleProcessCL, consoleData) && createProcess(fileProcessCL, fileData))//?
	if (cpSuccess && fpSuccess)
	{
		char* ch = (char*)MapViewOfFile(fileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		if (ch == NULL)
			writeInFile.writeErrorInLog("Error of MapViewOfFile", MAP_VIEW_OF_FILE_ERROR);
		for (int i = 0; i < (sizeof(buffer) / sizeof(int)) * 2; i++)
		{
			int index = i;
			if (i % 2 == 1)
				index--;
			string s = to_string(buffer[index]);
			char const *str = s.c_str();
			CopyMemory(ch, str, sizeof(int));
			/*if (i % 2 == 1)
				log("FP", ch);
			else
				log("CP", ch);*/
			ReleaseSemaphore(semaphore, 1, NULL);
			Sleep(400);
		}
		UnmapViewOfFile(ch);
	}
	else
	{
		if (!cpSuccess)
			writeInFile.writeErrorInLog("Error of ConsoleProcess's creation", CREATE_PROCESS_ERROR);
		if (!fpSuccess)
			writeInFile.writeErrorInLog("Error of FileProcess's creation", CREATE_PROCESS_ERROR);
	}
	close(consoleData);
	close(fileData);
	CloseHandle(semaphore);
	CloseHandle(fileMapping);
}