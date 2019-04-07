// MyHook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdio.h>
#include <atlstr.h>
#include <atltime.h>
#include <iostream>

using namespace std;
extern HMODULE g_hDllMoudle;	//dll的句柄
//共享内存
#pragma data_seg("mydata")	//创建一个名为mydata的数据段
	HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker,"/SECTION:mydata,RWS")  //把mydata数据段设置为可读可写可共享




extern "C" _declspec(dllexport)
//钩子回调函数

LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	//Sleep(2000);
	//MessageBoxA(0, "你中毒了", "你中毒了", 0);

	//此处做更加,因为调用MessageBoxA函数会导致电脑卡死.故改成显示框的模式.
	CTime time;//实例一个时间对象
	CString timeStr;//显示时间
	time = CTime::GetCurrentTime();//获取系统当前时间
	timeStr = time.Format(_T("%Y-%m-%d%H:%M:%S"));//将time对象中的时间信息(年,月,日,时,分,秒)存储到CString变量中进行显示
	std::cout <<"your computer was be hacked !"<< (LPCTSTR)timeStr<< '\n' << std::endl;
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}

extern "C" _declspec(dllexport)
//设置全局钩子
BOOL SetGlobalHook()
{
	g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllMoudle, 0);
	if (g_hHook==NULL)
	{
		return FALSE;
	}
	return TRUE;
}


//卸载全局钩子
