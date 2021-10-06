#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

unsigned char buf[] = "shellcode";
byte key[sizeof(buf)] = {};

//xor混淆
void EnXor() {
	int i = 0;
	srand(time(0));	//初始化rand随机数的种子
	//sc进行xor
	for (i; i < sizeof(buf); i++) {
		key[i] = char((rand() % (256)));	//获得0-255随机数
		buf[i] = buf[i] ^ key[i];
	}
	cout << endl;
	FILE* writetofile = NULL;	//文件指针
	fopen_s(&writetofile, "payload.txt", "w");	//以读的方式打开文件并获取文件指针
	if (writetofile == NULL)
		cout << "文件创建失败" << endl;
	else
	{
		//将异或后的sc以及异或key值写入文件保存
		fprintf(writetofile, "unsigned char buf[] = \"");
		for (size_t i = 0; i < sizeof(buf); i++)
		{
			fprintf(writetofile, "\\x%x", buf[i]);
		}
		fprintf(writetofile, "\";\n");

		fprintf(writetofile, "unsigned char key[sizeof(buf)] = {", sizeof(key));
		i = 0;
		for (i; i < sizeof(key); i++)
		{
			if (i == sizeof(key) - 1) {
				fprintf(writetofile, "%d};\n", key[i]);
				break;
			}
			fprintf(writetofile, "%d,", key[i]);
		}
		fclose(writetofile);
		cout << "创建文件成功" << endl;
	}
}
int main()
{
	EnXor();

	return 0;
