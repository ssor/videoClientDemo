// NetSDKDemo.h : main header file for the NETSDKDEMO application
//

#if !defined(AFX_NETSDKDEMO_H__F984CDA1_DB9B_44E5_ADD8_44A8BB6D6E9D__INCLUDED_)
#define AFX_NETSDKDEMO_H__F984CDA1_DB9B_44E5_ADD8_44A8BB6D6E9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetSDKDemoApp:
// See NetSDKDemo.cpp for the implementation of this class
//


//老报警接口
//old alarm interface
typedef struct 
{
	NET_CLIENT_STATE cState;
	DWORD dError;
	DWORD dFull;
	BYTE  shelter[16];
	BYTE  soundalarm[16];
	BYTE  almDecoder[16];
}DEV_STATE;
/*
//新报警接口
//new alarm interface
typedef struct 
{
	BYTE	alarmout[16];
	BYTE	motion[16];
	BYTE	videolost[16];
	BYTE	shelter[16];
	BYTE	soundalarm[16];
	BYTE	diskfull;
	BYTE	diskerror[32];
}DEV_STATE;
*/
//设备信息列表结构
//struct of device infomation list
typedef struct _DeviceNode {
	char UserNanme[20]; //login name//登录用户名
	char Name[20];   //device name//设备名称
	char IP[20];     //ip address of device//设备IP地址字符
	LONG LoginID;    //login iD of device//设备登录iD
	NET_DEVICEINFO Info;  //infomation of device//设备信息
	DEV_STATE State; //status of device//设备状态
	DWORD TotalKbps;     //total bit-stream of device//设备当前总码流
	DWORD Max_Kbps;     //set max network stream limit//设置最大网络流量
	BOOL	bIsOnline;
}DeviceNode;

//当前画面显示内容的类型
//the type of current view dislplay
typedef enum _SplitType{
	SPLIT_TYPE_NULL = 0,   //blank//空白
	SPLIT_TYPE_MONITOR,    //network watch//网络监视
	SPLIT_TYPE_NETPLAY,    //network replay//网络回放
	SPLIT_TYPE_MULTIPLAY,  //network preview//网络预览
	SPLIT_TYPE_FILEPLAY,    //play local file//本地文件播放
	SPLIT_TYPE_CYCLEMONITOR,   //tour watch//轮循监视
	SPLIT_TYPE_PBBYTIME		//replay by time//通过时间回放
}SplitType;

//视频参数结构
//param struct of video
typedef union _VideoParam{
		BYTE  bParam[4];
		DWORD dwParam; //param of video//视频参数
}VideoParam;

//画面分割通道显示信息(可以定义成type/param，param自定义)
//displaying infomation of the channel in split views(can defined as type/param, and defined param by yourself)
typedef struct _SplitInfoNode
{
	SplitType Type;     //display type blank/watch/network replay/local replay/etc... //显示类型 空白/监视/网络回放/本地回放等
	DWORD iHandle;  //used to record channel id(watch channel ID/play file iD/etc...) //用于记录通道id(监视通道ID/播放文件iD等)
//	DWORD nTimeCount;   //time statistic,used to bit-stream statictic //时间计数,用于码流统计 
//	DWORD nKBPS;       //bit-stream statistic//not to appplication statictic after add sdk interface //码流统计//sdk增加接口后不用应用层统计
	int isSaveData;  //save data (directly save by in sdk) ? //数据是否保存(直接sdk保存)
	FILE *SavecbFileRaw; //save origin data by callback //保存回调原始数据
	FILE *SavecbFileStd; //save mp4 data by callback//保存回调mp4数据
	FILE *SavecbFileYUV; //save yuv data by callback //保存回调yuv数据
	FILE *SavecbFilePcm;  //save pcm data by callback //保存回调pcm数据
	VideoParam nVideoParam;  //param of video //视频参数
	void *Param;  //param of infomation,there are various params for diffrent display //信息参数,对于不同的显示有不同的参数
}SplitInfoNode;


class CNetSDKDemoApp : public CWinApp
{
public:
	CNetSDKDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetSDKDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetSDKDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
class CDeviceListProtector //全局变量保护类
{
public:
	CDeviceListProtector(CPtrList **list):m_ptrdevicelist(list)
	{
		*m_ptrdevicelist = new CPtrList(sizeof(DeviceNode));
		*list = *m_ptrdevicelist;
	}
	~CDeviceListProtector()
	{
		int count = (*m_ptrdevicelist)->GetCount();
		for (int i = 0; i < count; i++)
		{
			delete (DeviceNode *)((*m_ptrdevicelist)->GetTail());
			(*m_ptrdevicelist)->RemoveTail();
		}
		(*m_ptrdevicelist)->RemoveAll();
		delete (*m_ptrdevicelist);
	}
private:
	CPtrList **m_ptrdevicelist;
};

class CCSLock
{
public:
	CCSLock(CRITICAL_SECTION& cs):m_cs(cs)
	{
		EnterCriticalSection(&m_cs);
	}
	
	~CCSLock()
	{
		LeaveCriticalSection(&m_cs);
	}
private:
	CRITICAL_SECTION& m_cs;
};
*/

//extern CRITICAL_SECTION g_cs;

//全局变量，用于保存程序所在目录的路径名
//global variables,used to save the path name of program
extern CString g_strWorkDir;

//全局变量，用于保存设备列表
//global variable, used to save device list
//extern CPtrList  *g_ptrdevicelist ;

//全局函数，将系统时间格式转换为定义的网络时间格式
//global function, transport system time format to defined net time format
void g_systimetodhtime(SYSTEMTIME *systime , NET_TIME *dhtime);

//全局函数，将定义的网络时间格式转换为系统时间格式
//global function, transport net time format to system time format
void g_dhtimetosystime(NET_TIME *dhtime , SYSTEMTIME *systime);

//全局函数，将定义的网络时间转换为字符串显示
//global function, transport net time format to string display
CString g_TimeOutString(NET_TIME *dhtime );

//全局函数, 计算两时间点之差
//global function, calculate differ between two time point
DWORD g_IntervalTime(NET_TIME *stime, NET_TIME *etime );

void g_SetWndStaticText(CWnd * pWnd);

TCHAR* g_GetIniPath(void);

CString ConvertString(CString strText);

void ConvertComboBox(CComboBox &stuComboBox);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSDKDEMO_H__F984CDA1_DB9B_44E5_ADD8_44A8BB6D6E9D__INCLUDED_)
