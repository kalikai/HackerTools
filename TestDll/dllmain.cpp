// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "header.h"
#include <atlbase.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		MessageBoxA(0, "DLL_PROCESS_ATTACH", "ATTACH", 0);
		break;
    case DLL_THREAD_ATTACH:
		//此处注入增加打开应用程序
		system("start notepad");
		system("start calc");
		system("start mspaint");
		MessageBoxA(0, "DLL_THREAD_ATTACH", "ATTACH", 0);
		break;
    case DLL_THREAD_DETACH:
		MessageBoxA(0, "DLL_THREAD_DETACH", "DETACH", 0);
		break;
    case DLL_PROCESS_DETACH:
		MessageBoxA(0, "DLL_PROCESS_DETACH", "DETACH", 0);
		break;
	default:
		MessageBoxA(0, "default", "default", 0);
    }
    return TRUE;
}

