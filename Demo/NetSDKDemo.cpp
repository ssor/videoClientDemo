// NetSDKDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NetSDKDemo.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//动态设备信息列表指针；
//dynamic pointer of device list
//CRITICAL_SECTION g_cs;
//CPtrList    *g_ptrdevicelist;
//CDeviceListProtector dlp(&g_ptrdevicelist);
//SplitInfoNode g_splitinfo[MAX_CHANNUM];
CString g_strWorkDir;
/////////////////////////////////////////////////////////////////////////////
// CNetSDKDemoApp

BEGIN_MESSAGE_MAP(CNetSDKDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CNetSDKDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetSDKDemoApp construction

CNetSDKDemoApp::CNetSDKDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNetSDKDemoApp object

CNetSDKDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNetSDKDemoApp initialization

BOOL CNetSDKDemoApp::InitInstance()
{
//	InitializeCriticalSection(&g_cs);
	AfxEnableControlContainer();

//	memset((char *)g_splitinfo, 0, sizeof(g_splitinfo));
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	CNetSDKDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

//自定义全局函数
//self definination global functions
void g_systimetodhtime(SYSTEMTIME *systime , NET_TIME *dhtime)
{
	dhtime->dwYear = (DWORD)systime->wYear;
	dhtime->dwMonth = (DWORD)systime->wMonth;
	dhtime->dwDay = (DWORD)systime->wDay;
	dhtime->dwHour = (DWORD)systime->wHour;
	dhtime->dwMinute = (DWORD)systime->wMinute;
	dhtime->dwSecond = (DWORD)systime->wSecond;
}

//自定义全局函数
//self definination global functions
void g_dhtimetosystime(NET_TIME *dhtime , SYSTEMTIME *systime)
{
	systime->wYear = (WORD)dhtime->dwYear;
	systime->wMonth = (WORD)dhtime->dwMonth;
	systime->wDay = (WORD)dhtime->dwDay;
	systime->wHour = (WORD)dhtime->dwHour;
	systime->wMinute = (WORD)dhtime->dwMinute;
	systime->wSecond = (WORD)dhtime->dwSecond;
}

//自定义全局函数
//self definination global functions
CString g_TimeOutString(NET_TIME *dhtime )
{
	CString nStr;

	nStr.Format("%04d-%02d-%02d %02d:%02d:%02d", dhtime->dwYear,dhtime->dwMonth,dhtime->dwDay,
		dhtime->dwHour, dhtime->dwMinute, dhtime->dwSecond);

	return nStr;
}

//自定义全局函数
//self definination global functions
DWORD g_IntervalTime(NET_TIME *stime, NET_TIME *etime )
{
	if(*((DWORD *)&stime) > *((DWORD *)&etime))
	{
		return 0;
	}

	//只处理最多相隔一天的两时间差,大于一天做一天计
	//only deal the two time that differ in one day, and as one day that exceed one day
	DWORD sSec = stime->dwHour * 3600 + stime->dwMinute *60 + stime->dwSecond;
	DWORD eSec = etime->dwHour * 3600 + etime->dwMinute *60 + etime->dwSecond;

	if(sSec > eSec)
	{
		sSec += 3600 * 24;
	}
	return (eSec - sSec);
}

//获取配置路径
//get config path
//打开文件对话框后，当前路径会发生变化，所以需要初始化对话框的时候保存路径
//the path will change after open file dialog, so need to save path when initialize dialog
TCHAR* g_GetIniPath(void)
{
	static TCHAR* pszIniPath = NULL;//it's easy to initilize uing pointer//用指针容易初始化,
	if( NULL == pszIniPath)
	{
		TCHAR szDirBuf[512] = {0};
		pszIniPath = new TCHAR[512];//memory leak if not relaese//不释放就内存泄露
		memset(pszIniPath, 0, 512);
		GetCurrentDirectory(512, szDirBuf);
		sprintf(pszIniPath, "%s\\langchn.ini", szDirBuf);
	}
	return pszIniPath;
}

//“英文字符串”转换为“当前语言类型的字符串”
//"english character string" translate to "current language character string"
CString ConvertString(CString strText)
{
	char *val = new char[200];
	CString strIniPath,strRet;

	memset(val,0,200);
	GetPrivateProfileString("String", strText, "", val, 200, g_GetIniPath());
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//如果ini文件中不存在对应的字符串，设置为默认值（英文）
		//if the corresponding charater string is not exist in ini file, set to default(english)
		strRet=strText;
	}
	delete val;
	return strRet;
}
//设置对话框中的静态文本(英文-->当前语言)   
//set the static text in dialog(english-->current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;

	//设置主窗口的标题
	//set the tile of main window
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}

	//设置子窗口的标题
	//set the title of sub window
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//下一个子窗口
			//the next sub window
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}

		//////////////////////////////////////////////////////////////////////////	

		//设置子窗口的当前语言文本
		//set the current languge text of sub window
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);

		//下一个子窗口
		//the next sub window
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}
/*
 *	组合框语言转换
 *language translate of combine box
 */
void ConvertComboBox(CComboBox &stuComboBox)
{
	int nCount = stuComboBox.GetCount();
	if(nCount <= 0)
	{
		return;
	}
	CString* strText = new CString[nCount];
	int i = 0;
	for( i = 0; i < nCount;i++)
	{
		stuComboBox.GetLBText(i, strText[i]);
		strText[i] = ConvertString(strText[i]);
	}
	stuComboBox.ResetContent();
	for(i = 0; i< nCount; i++)
	{
		stuComboBox.AddString(strText[i]);
	}
	delete []strText;
}

int CNetSDKDemoApp::ExitInstance() 
{
//	DeleteCriticalSection(&g_cs);
	return CWinApp::ExitInstance();
}
