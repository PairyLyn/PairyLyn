#include <windows.h>
#include <iostream>
#include <tlhelp32.h>

using namespace std;

DWORD GetPidByName(LPCWSTR lpName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnap)
	{
		cout << "创建进程快照失败" << endl;
		return 0;
	}
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnap, &pe);
	do
	{
		if (!_wcsicmp(lpName, pe.szExeFile))
		{
			return pe.th32ProcessID;
		}
	} while (Process32Next(hSnap, &pe));
	return 0;
}

// 提权
int EnableDebugPrivilege()
{
	HANDLE token;
	TOKEN_PRIVILEGES tp;
	// 打开进程令牌环
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token))
	{
		cout << "打开进程令牌失败" << endl;
		return 0;
	}
	//  获取进程本地唯一ID
	LUID luid;
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
	{
		cout << "获取LUID失败" << endl;
		return 0;
	}
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;
	// 调整进程权限
	if (!AdjustTokenPrivileges(token, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		cout << "提权失败" << endl;
		return 0;
	}
	return 1;
}

int main()
{
	if (!EnableDebugPrivilege())
	{
		cout << "提权失败" << endl;
		return 0;
	}
	DWORD dwTargetPid = GetPidByName(L"notepad.exe");
	if (!dwTargetPid)
	{
		cout << "获取PID失败" << endl;
		return 0;
	}
	cout << "PID: " << dwTargetPid << endl;

	// 打开进程
	HANDLE hTarget = OpenProcess(PROCESS_ALL_ACCESS, false, dwTargetPid);
	if (!hTarget)
	{
		cout << "打开进程失败" << GetLastError() << endl;
		return 0;
	}

	void* pLoadLibFuncParam = nullptr;
	pLoadLibFuncParam = VirtualAllocEx(hTarget, 0, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pLoadLibFuncParam == nullptr)
	{
		cout << "申请内存失败" << endl;
		CloseHandle(hTarget);
		return 0;
	}

	LPCTSTR lpParam = L"DllTest.dll";
	if (!WriteProcessMemory(hTarget, pLoadLibFuncParam, (LPCVOID)lpParam, (wcslen(lpParam) + 1) * sizeof(TCHAR), NULL))
	{
		cout << "写入内存失败" << endl;
		CloseHandle(hTarget);
		return 0;
	}
	HMODULE hKernel32dll = LoadLibrary(L"kernel32.dll");
	if (!hKernel32dll)
	{
		cout << "加载模块错误" << GetLastError() << endl;
		CloseHandle(hTarget);
		return 0;
	}
	cout << "模块句柄: " << hKernel32dll << endl;
	void* pLoadLibrary = nullptr;
	pLoadLibrary = GetProcAddress(hKernel32dll, "LoadLibraryW");
	if (pLoadLibrary == nullptr)
	{
		cout << "找不到函数" << endl;
		CloseHandle(hTarget);
		return 0;
	}
	cout << "函数地址: " << pLoadLibrary << endl;
	DWORD dwThreadId = 0;
	HANDLE hRemoteThread = CreateRemoteThread(hTarget, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, (LPVOID)pLoadLibFuncParam, 0, &dwThreadId);
	if (!hRemoteThread)
	{
		cout << "创建进程失败" << endl;
		CloseHandle(hTarget);
		return 0;
	}
	cout << "运行结束" << hRemoteThread << endl;
	getchar();
	getchar();
	CloseHandle(hTarget);
	return 0;
}

