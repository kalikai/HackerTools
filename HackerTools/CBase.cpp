// CBase.cpp: 实现文件
//

#include "stdafx.h"
#include "HackerTools.h"
#include "CBase.h"
#include "afxdialogex.h"
#include "resource.h"


// CBase 对话框




IMPLEMENT_DYNAMIC(CBase, CDialogEx)

CBase::CBase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Base, pParent)
	, m_Edit(_T(""))
{

}

CBase::~CBase()
{
}

void CBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CBase, CDialogEx)
	ON_BN_CLICKED(IDC_RunSingle, &CBase::OnBnClickedRunsingle)
	ON_BN_CLICKED(IDC_ReleaseRes, &CBase::OnBnClickedReleaseres)
END_MESSAGE_MAP()



//************************************************************
// 函数名称: OnBnClickedRunsingle
// 函数说明: 防双开按钮
// 作	 者: kalikai
// 时	 间: 2018/12/18
// 参	 数: void
// 返 回 值: void
//************************************************************
void CBase::OnBnClickedRunsingle()
{
	MessageBox(L"防双开已默认开启成功");
}


//************************************************************
// 函数名称: OnBnClickedReleaseres
// 函数说明: 释放资源按钮
// 作	 者: kalikai
// 时	 间: 2018/12/18
// 参	 数: void
// 返 回 值: void
//************************************************************
void CBase::OnBnClickedReleaseres()
{
	/*在VC环境中除了我们所常用的Dialog、Menu和Bitmap等标准资源类型之外，它还支持自定义资源类型.那自定义资源能做什么呢？
	  1.默认的皮肤压缩包或语言包。一些支持换肤的软件特别是一些媒体播放器常常有自定义的皮肤文件
	   （你可以尝试将Media Player或千千静听等软件的Skins目录下的文件的扩展名改为.zip，然后使用WinZip打开看一下），
	    但为了防止Skin文件丢失导致软件无 法显示，他们常常会在EXE文件中内置一套Skin作为默认的皮肤文件。
	    同样，一些支持多语言的EXE文件中存在默认语言包也是这个道理（当然也可以使用 "String Table"资源类型）；
	  2.做为一些病毒 / 木马程序的寄生方式。如果不小心执行了带有病毒 / 木马的程序，它们会在你运行时释放出病毒 / 木马文件。当然许多病毒是将自身写入PE文件头来实现；
	  3.合并EXE与它所需要的DLL文件。出于某些原因程序作者有时可能需要将DLL文件嵌入到可执行的EXE文件中，这可以通过使用自定义资源来实现；
	  4.其它需要在程序中播放一个AVI动画等等，都可以通过将二进制的数据文件作为自定义资源加入到可执行文件中来实现；*/
	//获取指定模块的资源
	HRSRC hRsrc1 = FindResource(NULL, MAKEINTRESOURCE(IDR_kalikai1), TEXT("kalikai"));
	HRSRC hRsrc2 = FindResource(NULL, MAKEINTRESOURCE(IDR_kalikai2), TEXT("kalikai"));

	if (hRsrc1==NULL|| hRsrc2==NULL)
	{
		m_Edit += L"查找资源失败\r\n";
	}
	else
	{
		m_Edit += L"查找资源成功\r\n";
	}
	
	//获取资源大小
	DWORD dwSize1 = SizeofResource(NULL, hRsrc1);
	DWORD dwSize2 = SizeofResource(NULL, hRsrc2);
	if (dwSize1&&dwSize2)
	{
		m_Edit += L"获取资源大小成功!\r\n";
	}
	else
	{
		m_Edit += L"获取资源大小失败\r\n";
	}

	//将资源加载到内存
	HGLOBAL hGlobal1 = LoadResource(NULL, hRsrc1);
	HGLOBAL hGlobal2 = LoadResource(NULL, hRsrc2);
	if (hGlobal1&&hGlobal1)
	{
		m_Edit += L"资源加载成功\r\n";
	}
	else
	{
		m_Edit += L"资源加载失败\r\n";
	}

	//锁定资源
	LPVOID lpVoid1 = LockResource(hGlobal1);
	LPVOID lpVoid2 = LockResource(hGlobal2);
	if (lpVoid1&&lpVoid2)
	{
		m_Edit += L"资源锁定成功\r\n";
	}
	else
	{
		m_Edit += L"资源锁定失败\r\n";
	}

	//将资源保存为文件
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	fopen_s(&fp1, "MyHookDll.dll", "wb+");
	fopen_s(&fp2, "TestDll.dll", "wb+");
	if (fp1&&fp2)
	{
		m_Edit += L"资源载入本地成功!\r\n";
	}
	fwrite(lpVoid1,sizeof(char),dwSize1,fp1);
	fwrite(lpVoid2,sizeof(char),dwSize2,fp2);
	fclose(fp1);
	fclose(fp2);
	UpdateData(FALSE);
}
