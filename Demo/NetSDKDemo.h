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


//�ϱ����ӿ�
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
//�±����ӿ�
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
//�豸��Ϣ�б�ṹ
//struct of device infomation list
typedef struct _DeviceNode {
	char UserNanme[20]; //login name//��¼�û���
	char Name[20];   //device name//�豸����
	char IP[20];     //ip address of device//�豸IP��ַ�ַ�
	LONG LoginID;    //login iD of device//�豸��¼iD
	NET_DEVICEINFO Info;  //infomation of device//�豸��Ϣ
	DEV_STATE State; //status of device//�豸״̬
	DWORD TotalKbps;     //total bit-stream of device//�豸��ǰ������
	DWORD Max_Kbps;     //set max network stream limit//���������������
	BOOL	bIsOnline;
}DeviceNode;

//��ǰ������ʾ���ݵ�����
//the type of current view dislplay
typedef enum _SplitType{
	SPLIT_TYPE_NULL = 0,   //blank//�հ�
	SPLIT_TYPE_MONITOR,    //network watch//�������
	SPLIT_TYPE_NETPLAY,    //network replay//����ط�
	SPLIT_TYPE_MULTIPLAY,  //network preview//����Ԥ��
	SPLIT_TYPE_FILEPLAY,    //play local file//�����ļ�����
	SPLIT_TYPE_CYCLEMONITOR,   //tour watch//��ѭ����
	SPLIT_TYPE_PBBYTIME		//replay by time//ͨ��ʱ��ط�
}SplitType;

//��Ƶ�����ṹ
//param struct of video
typedef union _VideoParam{
		BYTE  bParam[4];
		DWORD dwParam; //param of video//��Ƶ����
}VideoParam;

//����ָ�ͨ����ʾ��Ϣ(���Զ����type/param��param�Զ���)
//displaying infomation of the channel in split views(can defined as type/param, and defined param by yourself)
typedef struct _SplitInfoNode
{
	SplitType Type;     //display type blank/watch/network replay/local replay/etc... //��ʾ���� �հ�/����/����ط�/���ػطŵ�
	DWORD iHandle;  //used to record channel id(watch channel ID/play file iD/etc...) //���ڼ�¼ͨ��id(����ͨ��ID/�����ļ�iD��)
//	DWORD nTimeCount;   //time statistic,used to bit-stream statictic //ʱ�����,��������ͳ�� 
//	DWORD nKBPS;       //bit-stream statistic//not to appplication statictic after add sdk interface //����ͳ��//sdk���ӽӿں���Ӧ�ò�ͳ��
	int isSaveData;  //save data (directly save by in sdk) ? //�����Ƿ񱣴�(ֱ��sdk����)
	FILE *SavecbFileRaw; //save origin data by callback //����ص�ԭʼ����
	FILE *SavecbFileStd; //save mp4 data by callback//����ص�mp4����
	FILE *SavecbFileYUV; //save yuv data by callback //����ص�yuv����
	FILE *SavecbFilePcm;  //save pcm data by callback //����ص�pcm����
	VideoParam nVideoParam;  //param of video //��Ƶ����
	void *Param;  //param of infomation,there are various params for diffrent display //��Ϣ����,���ڲ�ͬ����ʾ�в�ͬ�Ĳ���
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
class CDeviceListProtector //ȫ�ֱ���������
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

//ȫ�ֱ��������ڱ����������Ŀ¼��·����
//global variables,used to save the path name of program
extern CString g_strWorkDir;

//ȫ�ֱ��������ڱ����豸�б�
//global variable, used to save device list
//extern CPtrList  *g_ptrdevicelist ;

//ȫ�ֺ�������ϵͳʱ���ʽת��Ϊ���������ʱ���ʽ
//global function, transport system time format to defined net time format
void g_systimetodhtime(SYSTEMTIME *systime , NET_TIME *dhtime);

//ȫ�ֺ����������������ʱ���ʽת��Ϊϵͳʱ���ʽ
//global function, transport net time format to system time format
void g_dhtimetosystime(NET_TIME *dhtime , SYSTEMTIME *systime);

//ȫ�ֺ����������������ʱ��ת��Ϊ�ַ�����ʾ
//global function, transport net time format to string display
CString g_TimeOutString(NET_TIME *dhtime );

//ȫ�ֺ���, ������ʱ���֮��
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
