// NetSDKDemoDlg.h : header file
//

#if !defined(AFX_NETSDKDEMODLG_H__874C22A9_455C_4113_9954_FDC1528EE15D__INCLUDED_)
#define AFX_NETSDKDEMODLG_H__874C22A9_455C_4113_9954_FDC1528EE15D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "searchrecord.h"
#include "clientState.h"
#include "exbutton.h"
#include "systemconfig.h"
#include "PlayWnd.h"
#include "ScreenPannel.h"
#include "PTZPannel.h"
#include "ColorPannel.h"
#include "PlayCtrlPannel.h"
#include "NormalBtnPannel.h"
#include "AdvanceBtnPannel.h"
#include "SaveDataPannel.h"
#include "SelectPannel.h"
#include "RuntimeMsgPannel.h"
#include "AudioBroadcastDlg.h"
#include "downloadbytime.h"
//#include "libmodel.h"
/////////////////////////////////////////////////////////////////////////////
// CNetSDKDemoDlg dialog

#define TIMER_KBPS 1999
#define CUR_MAXCHAN 16
#define	CUR_SPLIT	SPLIT16

//����ָ�����
//the type of view split
enum{
	SPLIT1 = 0,
	SPLIT4,
	SPLIT9,
	SPLIT16,	
	SPLIT_TOTAL
};

//���ſ�������
//the type of play control
enum{
	STATUS_STOP,
	STATUS_PAUSE,
	STATUS_PLAY,
	STATUS_STEP,
};

//������Ƶ����
//set param of video
enum{
	VIDEO_BRIGHT = 0,
	VIDEO_CONTRAST,
	VIDEO_HUE,
	VIDEO_SATURATION,
	VIDEO_TOTAL
};

//��̨���Ʋ���
//the operation of PTZ control
enum{
	PTZ_START,
	PTZ_STOP
};
//������Ϣ����
//infomation params of watch
typedef struct _SplitMonitorParam
{
	DeviceNode *pDevice;  //device pointer//�豸ָ��
	int iChannel;   //the channel index of device//��Ӧ���豸�е�ͨ�����
//	BOOL  isTalkOpen;  //open audio talk ? //�Ƿ�������Խ�
}SplitMonitorParam;

//����ط���Ϣ����
//params of infomation of net replay
typedef struct _SplitNetPlayParam
{
//	DWORD iFilePos;  //file infomation list //�ļ���Ϣ�б�position/
	FileInfoNode *pFileInfo;   //file infomation pointer //�ļ���Ϣָ��
	int   iStatus;  //play status normal/pause/fast/slow //����״̬ ����/��ͣ/���/����
	int   iPlayPos;  //play position of current play //��ǰ���ŵ�λ��
}SplitNetPlayParam;

//ͨ��ʱ��ط�¼�����
//params of replay file by time
typedef struct _SplitPBByTimeParam
{
	DeviceNode *pDevice;
	NET_TIME starttime;
	NET_TIME endtime;
	int nChannel;
	int npos;
	int iStatus;
}SplitPBByTimeParam;

//�໭��Ԥ����Ϣ����
//params of multi views preview
typedef struct _SplitMulitPlayParam
{
	DeviceNode *pDevice;  //device pointer //�豸ָ��
}SplitMultiPlayParam;

//��ѭ������Ϣ����
//params of tour watch
typedef struct _CycleChannelInfo
{
	DWORD dwDeviceID;
	int iChannel;
}CycleChannelInfo;
typedef struct _SplitCycleParam
{
	DeviceNode *pDevice;	//device pointer //�豸ָ��
	CPtrList *pChannelList;	//tour channel list //��ѭͨ���б�
	int iChannelCount;		//channel number //ͨ����
	int iCurPosition;		//the position of current watch channel in array //��ǰ����ͨ�����������λ��
	UINT iInterval;			//time span of views switch(second) //�����л����ʱ�䣨�룩
}SplitCycleParam;	
/*Begin: Add by yehao(10857) For Task.NO.11071 2006-12-26*/
typedef struct _TalkHandleInfo
{
	DeviceNode *pDevice;
	LONG		lHandle;
} TalkHandleInfo, *LPTalkHandleInfo;
/*End: yehao(10857) Task.NO.11071 */

class CNetSDKDemoDlg : public CDialog
{
// Construction
	int m_connectwaittime;  //wait time for connecting//�������ӵȴ�ʱ��
	int m_curScreen;   //index of current display view //��ǰ��ʾ�������
	int m_curSoundSplit;  //index of current display view audio outputed //��ǰ����������ڵĻ������

	//�ڲ����������Ҫ���ӹ��ܺ���
	//sub functions needed by inner according to desin
	void *GetCurDeviceInfo();  //get current selected device pointer in device list //��õ�ǰ�豸�б�ѡ����豸����Ϣָ��
	void *FindDeviceInfo(LONG lLoginID, char *sDVRIP,LONG nDVRPort); //get device pointer by device id //�����豸id����豸��Ϣָ��
	int GetHandleSplit(LONG lPlayHandle);   //get current view index by id //����id,��õ�ǰ�������
	BOOL CheckCurSplitAndClose(); //check current view and close picture display //��鵱ǰ���沢�ر�ͼ����ʾ;
	BOOL IsCycling(DWORD deviceID, int channelNo);  //touring channels ? //�Ƿ�����ѵͨ��
	int  GetCurSplitStart(int nScreen, int nSplit);  //get the first view index appointed in current views split //��ȡ��ǰ����ָ�ģʽ��ָ���������ʼ�������
	int  PlayStop(int iScreen, BOOL bDis = FALSE);   //stop display //����ֹͣ

	//������²�������
	//update operation functions
	void UpdateVideoCtrl(int nMode);     //refresh control area of video params //ˢ����Ƶ����������
	void UpdateDeviceList();    //refresh device list //ˢ���豸�б�
	void UpdateDeviceState(void *pDevice, char *pBuf, DWORD dwBufLen); //refresh device status //�����豸��״̬
	
public:
	CNetSDKDemoDlg(CWnd* pParent = NULL);	// standard constructor


	//���ڻص��Ľӿ�
	//interfaces used to callback
	void DeviceDisConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort);
	void DeviceReConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort);
	void ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);
	BOOL ReceiveMessage(LONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, 
		char *pBuf, DWORD dwBufLen);
	void AddDisplayInfo(LONG lLoginID, LONG lPlayHandle, HDC hDC);  //splice character or picture //�����ַ���ͼƬ
	void ReceivePlayPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize);
	int  ListenCallBack_Imp(LONG lServerHandle, char* ip, WORD port, int nCmd, void* pParam);

	//����ɾ����ѭ����Ĳ���
	//used to delete params of tour views
	void DeleteCycleParam(int nScreen);

	//�豸�Ͽ�ʱ�ص�������������������Ͽ����豸�б�ĸ��¼��豸��ɾ������
	//callback function for device disconnect, can be used to deal with updating device list and deleting device from device list when device disconnect
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	//�������ݻص�����,�����������ص����ݱ�����ļ�
	//callback function of watching data, can be used to save data to file
	friend void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, DWORD dwUser);
	//�ط����ݻص�������demo�ｫ���ݱ�����ļ�
	//callback function of replay data, save data to file in demo
	friend int CALLBACK PBDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, DWORD dwUser);
	friend void CALLBACK RealDataCallBackEx(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, LONG lParam, DWORD dwUser);
	//��Ϣ�ص�������,�Ƕ�����sdkӦ�õĻص�,��������ص������ı�����Ϣ
	//callback function of message, used to deal with alarm information  
	friend BOOL CALLBACK MessCallBack(LONG lCommand, LONG lLoginID, char *pBuf, 
		DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort);
	//�Զ��廭��ص�,����������ʾͨ������
	//self define callback of pallete, used to display channel name
	friend void CALLBACK ChannelAutoDraw(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);
		//���Ž���״̬�ص�����,���������������ʾ
		//callback function of play process, used to deal with display of process
	friend void CALLBACK PlayCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

	//�����������ص�
	//callback function of listen server
	friend  int CALLBACK ListenCallBack(LONG lServerHandle, char* ip, WORD port, int nCmd, void* pParam, DWORD dwUserData);
	//for stream parser
//	friend unsigned long __stdcall SpCallBack(PARSERHANDLE hHandle, PARSERMSG msg, 
//		unsigned long dwParam1, unsigned long dwParam2,
//		unsigned long dwUserData);

	//����״̬ҳ��
	//alarm status page
	CClientState  m_ClientStateDlg;
	
//	CSystemConfig m_SysConfig;
	// Dialog Data
	//{{AFX_DATA(CNetSDKDemoDlg)
	enum { IDD = IDD_NETSDKDEMO_DIALOG };
	CExButton	m_ptz_righttop;
	CExButton	m_ptz_rightdown;
	CExButton	m_ptz_lefttop;
	CExButton	m_ptz_leftdown;
	CExButton	m_zoom_wide;
	CExButton	m_zoom_tele;
	CExButton	m_focus_near;
	CExButton	m_focus_far;
	CExButton	m_iris_open;
	CExButton	m_iris_close;
	CExButton	m_ptz_up;
	CExButton	m_ptz_right;
	CExButton	m_ptz_left;
	CExButton	m_ptz_down;
	CComboBox	m_channelsel;
	CTreeCtrl	m_devicelist;
	int		m_play_frame;
	UINT	m_testvalue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetSDKDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetSDKDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkTreeDevicelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void OpenSingleChannel(DeviceNode *pInfo,int nCh, int screenNo, RV_RealPlayType subtype);	//open one watch channel //��һ������ͨ��
	void OpenAllChannel(DeviceNode *pInfo, RV_RealPlayType subtype);					//open all watch channels in selected device //��ѡ���豸�����м���ͨ��
	void PlayRecordFile(FileInfoNode* playfile, int scrNo);	//open one record file for play //��һ��¼���ļ��Ĳ���
	BOOL ProcessCloseScreen(int scrNo, BOOL bDis = FALSE);  //comit close view //ִ�йرջ���
	BOOL ProcessCloseAllChannel(DeviceNode *pInfo);			//comit close all channels in selected device //ִ�йر�ѡ���豸������ͨ��
	void SwitchFullScreen();		//switch full screen //�л�ȫ�� 
//	void ReturnOrignalSplit(void);	//restore normal views split //�ָ���������ָ�
	void UpdateScreen(int nSplit);	//refresh screen, main to refresh video area //ˢ����Ļ,��Ҫ��ˢ����Ƶ����

	void AddDevice();				//event handler function for "add device" key //�ԡ�����豸����������Ӧ���� 
	void DeleteDevice();			//event handler function for "delete device" key //�ԡ�ɾ���豸����������Ӧ����
	void OpenChannel();				//event handler function for "open channel" key //�ԡ���ͨ������������Ӧ����
	void OpenMultiplay();			//event handler function for "multi views preview" key //�ԡ��໭��Ԥ������������Ӧ����
	void CloseScreen();				//event handler function for "close view" key //�ԡ��رջ��桱��������Ӧ����
	void CloseAllChannel();			//event handler function for "close device channel" key //�ԡ��ر��豸ͨ������������Ӧ����
	void SearchRecord();			//event handler function for "record query" key //�ԡ�¼���ѯ����������Ӧ����
	void CycleMonitor();			//event handler function for "tour" key //�ԡ���ѭ����������Ӧ����
	void Playbackbytime();			//event handler function for "replay by time" key //�ԡ���ʱ��طš���������Ӧ����
	void Downloadbytime();			//event handler function for "download by time" key //�ԡ���ʱ�����ء���������Ӧ����
	void Sysconfig();				//event handler function for "system config" key //�ԡ�ϵͳ���á���������Ӧ����
	void Sysconfig2();				//event handler function for "system config<X>" key //�ԡ�ϵͳ����<X>����������Ӧ����

	BOOL OpenSound(BOOL bOpen);		//open/close audio //��\�ر���Ƶ
	BOOL OpenTalk(BOOL bOpen);		//open/close talk //��\�رնԽ�
	void UpdateDevice();			//event handler function for "update device" key //�ԡ��豸��������������Ӧ����
	void Recordstate();				//event handler function for "record status" key //�ԡ�¼��״̬����������Ӧ����
	void RebootDevice();			//event handler function for "reboot device" key //�ԡ������豸����������Ӧ����
	void AlarmIOctrl();				//event handler function for "control alarm IO" key //�ԡ�����IO���ơ���������Ӧ����
	void ShutdownDevice();			//event handler function for "close device" key //�ԡ��ر��豸����������Ӧ����
	void DeviceState();				//event handler function for "device status" key //�ԡ��豸״̬����������Ӧ����
	void CaptureScreen();			//event handler function for "snapshot" key //�ԡ�ץͼ����������Ӧ����
	void SetIframe();				//event handler function for "force I Frame" key //�ԡ�ǿ��I֡����������Ӧ����
	void ShowFluxInfo();			//event handler function for "display bit-stream" key //�ԡ���ʾ��������������Ӧ����
	void Transcom();				//event handler function for "clarity channel" key //�ԡ�͸��ͨ������������Ӧ����
	void DDNS_QueryIP();				//event handler function for "DDNS query IP" key //�ԡ�DDNS��ѯIP����������Ӧ����
	void Getversion();				//event handler function for "sdk version" key //�ԡ�SDK�汾����������Ӧ����
	void OpenAudioBroadcastDlg();	//operation UI of opening audio broadcast //�������㲥�Ĳ�������
	void Dhptzctrl();				//event handler function for "PTZ menu" key //�ԡ���̨�˵�����������Ӧ����
	void Extptzctrl();				//event handler function for "PTZ advanced menu" key //�ԡ���̨��չ�˵�����������Ӧ����

	void SaveRealdata(int nCheck);			//save real-time watch data //����ʵʱ��������
	void SavecbdataRaw(int nCheck);				//save callback data - origin data //����ص����ݣ�ԭʼ����
	void SavecbdataStd(int nCheck);			//save callback data - stantard data //����ص����ݣ���׼����
	void Savecbdatapcm(int nCheck);			//save callback data - pcm data //����ص����ݣ�pcm��Ƶ����
	void Savecbdatayuv(int nCheck);			//save callback data - yuv data //����ص����ݣ�yuv��Ƶ����
				
	void PtzControl(int type, BOOL stop, int param);   //operation of PTZ //��̨���Ʋ���
	void ProcessDeleteDevice(DeviceNode *pDevice,  BOOL bDelList, BOOL bDis = false); //delete device, nDelList:delete device list ? , bDis:disconnect ? //ɾ���豸,nDelList�Ƿ�ɾ���豸�б�, bDis��ʾ�Ƿ����
	
	void NextCycleMonitor(UINT nID);	//open the next channel in tour list //����ѭ�б�����һ��ͨ��

	void CtrlColor_Bright(int pos);			//control brightness of picture //���ƻ�������
	void CtrlColor_Contrast(int pos);		//control contrast of picture//���ƻ���Աȶ�
	void CtrlColor_Saturation(int pos);		//control saturation of picture//���ƻ��汥�Ͷ�
	void CtrlColor_Hue(int pos);			//control hue of picture//���ƻ���ɫ��

	BOOL SeekPlayPositon(int nPos);		//event handler function for play process bar //���Ž��������϶���Ӧ����
	BOOL PlayCtrl_Play();				//event handler function for "play / pause" key //"����"\"��ͣ"������Ӧ����
	BOOL PlayCtrl_Stop();				//event handler function for "stop" key //"ֹͣ"������Ӧ����
	BOOL PlayCtrl_Fast();				//event handler function for "fast" key //"���"������Ӧ����
	BOOL PlayCtrl_Slow();				//event handler function for "slow" key //"����"������Ӧ����
	BOOL PlayCtrl_Step();				//event handler function for "single frame" key //"��֡"������Ӧ����
	BOOL PlayCtrl_Frame(int frame);		//event handler function for "by frame" key //"��֡"������Ӧ����

	void GetDeviceWorkstate();			//event handler function for "work status of device" key //"�豸����״̬"������Ӧ����
	void DeviceControldisk();			//event handler function for "disk control" key //"Ӳ�̿���"������Ӧ����
	void DeviceUserinfo();				//event handler function for "users infomation" key //"�û���Ϣ"������Ӧ����
	
	void SeleteNormalPannel();			//display page of "common" //��ʾ�����桱����ҳ��
	void SeleteAdvancePannel();			//display page of "advanced" //��ʾ���߼�������ҳ��
	void SeleteSaveDataPannel();		//display page of "data saving" //��ʾ�����ݱ��桱����ҳ��
	void SeletePTZPannel();				//display page of "PTZ control" //��ʾ����̨���ơ�����ҳ��
	void SeleteColorPannel();			//display page of "color adjust" //��ʾ����ɫ����������ҳ��
	void SeletePlayCtrlPannel();		//display page of "play control" //��ʾ�����ſ��ơ�����ҳ��
	void SeleteDevListPannel();			//display page of "device list" //��ʾ���豸�б�����ҳ��
	
	void UpdatePannelPosition();			//update sub windows position //���¸��Ӵ���λ��

	void LastError();						//display error reason of function run //��ʾ����ִ�г���ԭ��

	void SwitchMultiWnd(int nSplit);

	int	 GetCurWinID(void);

	void SetCurWindId(int nCuWinID)
	{
		m_curScreen = nCuWinID;
	}

	int UpdateDeviceListCallback_Imp(const DeviceNode& node);
	int WriteAlarmLogFunc_Imp(const AlarmNode& node);

	void TestProc(); //for test

	//for stream parser
//	void HandleParserMsg(PARSERHANDLE hHandle, PARSERMSG msg, 
//		unsigned long dwParam1, unsigned long dwParam2);

public:
	int GetCurScreen(){return m_curScreen;}
	void UpdateCurScreenInfo();  //refresh infomation display of current view //ˢ�µ�ǰ����������Ϣ��ʾ
	void SetSplit(int split);
	int  GetSplit();
	//��ȡ���洰����Ϣ
	//get infomation of view
	BOOL GetSplitInfo_Main(int nIndex, SplitInfoNode* info);
	BOOL SetSplitInfo_Main(int nIndex, SplitInfoNode* info);
	/*Begin: Add by yehao(10857) 2006-12-20*/
	static void CALLBACK AudioDataCallBack(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);
	LONG GetTalkHandle();
	/*End: yehao(10857) */
private:
	/*Begin: Add by yehao(10857) For Task.NO.11071 2006-12-26*/
	BOOL RecordStart();
	BOOL RecordStop();
	/*End: yehao(10857) Task.NO.11071 */
private:
	BOOL		m_bPTZCtrl;		//flag control status of PTZ //��ʶPTZ����״̬
	
//	BOOL		m_bFullSCRN;		//flag status of full screen //��ʶ��ǰ�Ƿ�ȫ��״̬
	CRect		m_clientRect;		//position of UI area //�����������λ��
	CRect		m_screenRect;		//store position of screen area //������Ļ�����λ��
	CRect		m_pannelRect;		//store position of function panal area //���湦����������λ��
	CRect		m_selectRect;		//store position of "select page" panal area //���桰ѡ��ҳ�桱����λ��
	CRect		m_btnAreaRect;		//store position of function keys area //���湦�ܰ��������λ��
	CRect		m_runtimeMsgRect;			//store position of "runtime infomation" panal area //���桰����ʱ��Ϣ������λ��

	CScreenPannel		m_screenPannel;		//play screen motherboard - sub window //������Ļ�װ壭�Ӵ���
//	CPlayWnd			m_playWnd[MAX_CHANNUM];		//play windows - sub window //�������Ż��棭�Ӵ���
//	CWnd				*m_originParent;	//fathor windows that store sub windows temperarily //��ʱ������Ӵ��ڵĸ�����
	CPTZPannel			m_ptzPannel;		//PTZ control panal - sub window //��̨������壭�Ӵ���
	CColorPannel		m_colorPannel;		//color control panal - sub window //��ɫ������壭�Ӵ���
	CPlayCtrlPannel		m_playctrlPannel;	//replay control panal - sub window //�طſ�����壭�Ӵ���
	CNormalBtnPannel	m_normalBtnPannel;	//common function keys panal - sub window //���湦�ܰ�����壭�Ӵ���
	CAdvanceBtnPannel	m_advanceBtnPannel;	//advanced function keys panal - sub window //�߼����ܰ�����壭�Ӵ���
	CSaveDataPannel		m_saveDataPannel;	//saving data keys panal - sub window //���ݱ��水����壭�Ӵ���
	CSelectPannel		m_selectPannel;		//display "select page" keys panal - sub window //��ʾ��ѡ��ҳ�桱��������壭�Ӵ���
	CRuntimeMsgPannel	m_runtimeMsgPannel;	//display runtime infomation panal - sub window //��ʾ����ʱ��Ϣ����壭�Ӵ���
	/*Begin: Add by yehao(10857) 2006-12-22*/
	list<DeviceNode *>	m_broadcastDevList;
	CAudioBroadcastDlg	m_audioBroadcastDlg;
	BOOL				m_bRecord;
	TalkHandleInfo		m_talkhandle;
	unsigned int		m_uRecordCount;
	/*End: yehao(10857) 2006-12-22*/
	CBrush				m_myBrush;

	
#ifdef DH_STREAMPARSER
	//for stream parser
	PARSERHANDLE m_hSp;
	FILE         *m_spFile;
	BOOL		 m_bGetIFrame;
	int			 m_framecount;
#endif

	//download test
	CDownloadByTime m_dbByTime;

	//specified alarm test
	FILE	*m_almLogFile_Comm;
	FILE	*m_almLogFile_Shelter;
	FILE	*m_almLogFile_dFull;
	FILE	*m_almLogFile_dError;
	FILE	*m_almLogFile_SoundDec;
	
	DEV_STATE	m_lastAlarm;

	//listen device test
	LONG	m_lListenDevice;
	LONG	m_lListenChannel;
	typedef struct 
	{
		int state;
		char ip[16];
		WORD port;
		char serial[48];
	}LISTEN_DATA;
	LISTEN_DATA m_mylsdata;
};

 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSDKDEMODLG_H__874C22A9_455C_4113_9954_FDC1528EE15D__INCLUDED_)
