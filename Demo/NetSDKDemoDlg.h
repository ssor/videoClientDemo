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

//画面分割类型
//the type of view split
enum{
	SPLIT1 = 0,
	SPLIT4,
	SPLIT9,
	SPLIT16,	
	SPLIT_TOTAL
};

//播放控制类型
//the type of play control
enum{
	STATUS_STOP,
	STATUS_PAUSE,
	STATUS_PLAY,
	STATUS_STEP,
};

//设置视频参数
//set param of video
enum{
	VIDEO_BRIGHT = 0,
	VIDEO_CONTRAST,
	VIDEO_HUE,
	VIDEO_SATURATION,
	VIDEO_TOTAL
};

//云台控制操作
//the operation of PTZ control
enum{
	PTZ_START,
	PTZ_STOP
};
//监视信息参数
//infomation params of watch
typedef struct _SplitMonitorParam
{
	DeviceNode *pDevice;  //device pointer//设备指针
	int iChannel;   //the channel index of device//对应的设备中的通道序号
//	BOOL  isTalkOpen;  //open audio talk ? //是否打开语音对讲
}SplitMonitorParam;

//网络回放信息参数
//params of infomation of net replay
typedef struct _SplitNetPlayParam
{
//	DWORD iFilePos;  //file infomation list //文件信息列表position/
	FileInfoNode *pFileInfo;   //file infomation pointer //文件信息指针
	int   iStatus;  //play status normal/pause/fast/slow //播放状态 正常/暂停/快放/慢放
	int   iPlayPos;  //play position of current play //当前播放的位置
}SplitNetPlayParam;

//通过时间回放录象参数
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

//多画面预览信息参数
//params of multi views preview
typedef struct _SplitMulitPlayParam
{
	DeviceNode *pDevice;  //device pointer //设备指针
}SplitMultiPlayParam;

//轮循监视信息参数
//params of tour watch
typedef struct _CycleChannelInfo
{
	DWORD dwDeviceID;
	int iChannel;
}CycleChannelInfo;
typedef struct _SplitCycleParam
{
	DeviceNode *pDevice;	//device pointer //设备指针
	CPtrList *pChannelList;	//tour channel list //轮循通道列表
	int iChannelCount;		//channel number //通道数
	int iCurPosition;		//the position of current watch channel in array //当前监视通道在数组里的位置
	UINT iInterval;			//time span of views switch(second) //画面切换间隔时间（秒）
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
	int m_connectwaittime;  //wait time for connecting//设置连接等待时间
	int m_curScreen;   //index of current display view //当前显示画面序号
	int m_curSoundSplit;  //index of current display view audio outputed //当前声音输出所在的画面序号

	//内部根据设计需要的子功能函数
	//sub functions needed by inner according to desin
	void *GetCurDeviceInfo();  //get current selected device pointer in device list //获得当前设备列表选择的设备的信息指针
	void *FindDeviceInfo(LONG lLoginID, char *sDVRIP,LONG nDVRPort); //get device pointer by device id //根据设备id获得设备信息指针
	int GetHandleSplit(LONG lPlayHandle);   //get current view index by id //根据id,获得当前画面序号
	BOOL CheckCurSplitAndClose(); //check current view and close picture display //检查当前画面并关闭图像显示;
	BOOL IsCycling(DWORD deviceID, int channelNo);  //touring channels ? //是否在轮训通道
	int  GetCurSplitStart(int nScreen, int nSplit);  //get the first view index appointed in current views split //获取当前画面分割模式的指定画面的起始画面序号
	int  PlayStop(int iScreen, BOOL bDis = FALSE);   //stop display //播放停止

	//各类更新操作函数
	//update operation functions
	void UpdateVideoCtrl(int nMode);     //refresh control area of video params //刷新视频参数控制区
	void UpdateDeviceList();    //refresh device list //刷新设备列表
	void UpdateDeviceState(void *pDevice, char *pBuf, DWORD dwBufLen); //refresh device status //更新设备的状态
	
public:
	CNetSDKDemoDlg(CWnd* pParent = NULL);	// standard constructor


	//用于回调的接口
	//interfaces used to callback
	void DeviceDisConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort);
	void DeviceReConnect(LONG lLoginID, char *sDVRIP,LONG nDVRPort);
	void ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);
	BOOL ReceiveMessage(LONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, 
		char *pBuf, DWORD dwBufLen);
	void AddDisplayInfo(LONG lLoginID, LONG lPlayHandle, HDC hDC);  //splice character or picture //叠加字符或图片
	void ReceivePlayPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize);
	int  ListenCallBack_Imp(LONG lServerHandle, char* ip, WORD port, int nCmd, void* pParam);

	//用于删除轮循画面的参数
	//used to delete params of tour views
	void DeleteCycleParam(int nScreen);

	//设备断开时回调函数，可以用来处理断开后设备列表的更新及设备的删除操作
	//callback function for device disconnect, can be used to deal with updating device list and deleting device from device list when device disconnect
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	//监视数据回调函数,可以用来将回调数据保存成文件
	//callback function of watching data, can be used to save data to file
	friend void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, DWORD dwUser);
	//回放数据回调函数，demo里将数据保存成文件
	//callback function of replay data, save data to file in demo
	friend int CALLBACK PBDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, DWORD dwUser);
	friend void CALLBACK RealDataCallBackEx(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, 
		DWORD dwBufSize, LONG lParam, DWORD dwUser);
	//消息回调处理函数,是对整个sdk应用的回调,用来处理回调出来的报警信息
	//callback function of message, used to deal with alarm information  
	friend BOOL CALLBACK MessCallBack(LONG lCommand, LONG lLoginID, char *pBuf, 
		DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort);
	//自定义画板回调,可以用来显示通道名称
	//self define callback of pallete, used to display channel name
	friend void CALLBACK ChannelAutoDraw(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);
		//播放进度状态回调函数,用来处理进度条显示
		//callback function of play process, used to deal with display of process
	friend void CALLBACK PlayCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

	//侦听服务器回调
	//callback function of listen server
	friend  int CALLBACK ListenCallBack(LONG lServerHandle, char* ip, WORD port, int nCmd, void* pParam, DWORD dwUserData);
	//for stream parser
//	friend unsigned long __stdcall SpCallBack(PARSERHANDLE hHandle, PARSERMSG msg, 
//		unsigned long dwParam1, unsigned long dwParam2,
//		unsigned long dwUserData);

	//报警状态页面
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
	void OpenSingleChannel(DeviceNode *pInfo,int nCh, int screenNo, RV_RealPlayType subtype);	//open one watch channel //打开一个监视通道
	void OpenAllChannel(DeviceNode *pInfo, RV_RealPlayType subtype);					//open all watch channels in selected device //打开选中设备的所有监视通道
	void PlayRecordFile(FileInfoNode* playfile, int scrNo);	//open one record file for play //打开一个录象文件的播放
	BOOL ProcessCloseScreen(int scrNo, BOOL bDis = FALSE);  //comit close view //执行关闭画面
	BOOL ProcessCloseAllChannel(DeviceNode *pInfo);			//comit close all channels in selected device //执行关闭选中设备的所有通道
	void SwitchFullScreen();		//switch full screen //切换全屏 
//	void ReturnOrignalSplit(void);	//restore normal views split //恢复正常画面分割
	void UpdateScreen(int nSplit);	//refresh screen, main to refresh video area //刷新屏幕,主要是刷新视频区域

	void AddDevice();				//event handler function for "add device" key //对“添加设备”按键的响应函数 
	void DeleteDevice();			//event handler function for "delete device" key //对“删除设备”按键的响应函数
	void OpenChannel();				//event handler function for "open channel" key //对“打开通道”按键的响应函数
	void OpenMultiplay();			//event handler function for "multi views preview" key //对“多画面预览”按键的响应函数
	void CloseScreen();				//event handler function for "close view" key //对“关闭画面”按键的响应函数
	void CloseAllChannel();			//event handler function for "close device channel" key //对“关闭设备通道”按键的响应函数
	void SearchRecord();			//event handler function for "record query" key //对“录象查询”按键的响应函数
	void CycleMonitor();			//event handler function for "tour" key //对“轮循”按键的响应函数
	void Playbackbytime();			//event handler function for "replay by time" key //对“按时间回放”按键的响应函数
	void Downloadbytime();			//event handler function for "download by time" key //对“按时间下载”按键的响应函数
	void Sysconfig();				//event handler function for "system config" key //对“系统配置”按键的响应函数
	void Sysconfig2();				//event handler function for "system config<X>" key //对“系统配置<X>”按键的响应函数

	BOOL OpenSound(BOOL bOpen);		//open/close audio //打开\关闭音频
	BOOL OpenTalk(BOOL bOpen);		//open/close talk //打开\关闭对讲
	void UpdateDevice();			//event handler function for "update device" key //对“设备升级”按键的响应函数
	void Recordstate();				//event handler function for "record status" key //对“录象状态”按键的响应函数
	void RebootDevice();			//event handler function for "reboot device" key //对“重启设备”按键的响应函数
	void AlarmIOctrl();				//event handler function for "control alarm IO" key //对“报警IO控制”按键的响应函数
	void ShutdownDevice();			//event handler function for "close device" key //对“关闭设备”按键的响应函数
	void DeviceState();				//event handler function for "device status" key //对“设备状态”按键的响应函数
	void CaptureScreen();			//event handler function for "snapshot" key //对“抓图”按键的响应函数
	void SetIframe();				//event handler function for "force I Frame" key //对“强制I帧”按键的响应函数
	void ShowFluxInfo();			//event handler function for "display bit-stream" key //对“显示码流”按键的响应函数
	void Transcom();				//event handler function for "clarity channel" key //对“透明通道”按键的响应函数
	void DDNS_QueryIP();				//event handler function for "DDNS query IP" key //对“DDNS查询IP”按键的响应函数
	void Getversion();				//event handler function for "sdk version" key //对“SDK版本”按键的响应函数
	void OpenAudioBroadcastDlg();	//operation UI of opening audio broadcast //打开语音广播的操作界面
	void Dhptzctrl();				//event handler function for "PTZ menu" key //对“云台菜单”按键的响应函数
	void Extptzctrl();				//event handler function for "PTZ advanced menu" key //对“云台扩展菜单”按键的响应函数

	void SaveRealdata(int nCheck);			//save real-time watch data //保存实时监视数据
	void SavecbdataRaw(int nCheck);				//save callback data - origin data //保存回调数据－原始数据
	void SavecbdataStd(int nCheck);			//save callback data - stantard data //保存回调数据－标准数据
	void Savecbdatapcm(int nCheck);			//save callback data - pcm data //保存回调数据－pcm音频数据
	void Savecbdatayuv(int nCheck);			//save callback data - yuv data //保存回调数据－yuv视频数据
				
	void PtzControl(int type, BOOL stop, int param);   //operation of PTZ //云台控制操作
	void ProcessDeleteDevice(DeviceNode *pDevice,  BOOL bDelList, BOOL bDis = false); //delete device, nDelList:delete device list ? , bDis:disconnect ? //删除设备,nDelList是否删除设备列表, bDis表示是否继线
	
	void NextCycleMonitor(UINT nID);	//open the next channel in tour list //打开轮循列表中下一个通道

	void CtrlColor_Bright(int pos);			//control brightness of picture //控制画面亮度
	void CtrlColor_Contrast(int pos);		//control contrast of picture//控制画面对比度
	void CtrlColor_Saturation(int pos);		//control saturation of picture//控制画面饱和度
	void CtrlColor_Hue(int pos);			//control hue of picture//控制画面色度

	BOOL SeekPlayPositon(int nPos);		//event handler function for play process bar //播放进度条的拖动响应函数
	BOOL PlayCtrl_Play();				//event handler function for "play / pause" key //"播放"\"暂停"按建响应函数
	BOOL PlayCtrl_Stop();				//event handler function for "stop" key //"停止"按键响应函数
	BOOL PlayCtrl_Fast();				//event handler function for "fast" key //"快放"按键响应函数
	BOOL PlayCtrl_Slow();				//event handler function for "slow" key //"慢放"按键响应函数
	BOOL PlayCtrl_Step();				//event handler function for "single frame" key //"单帧"按键响应函数
	BOOL PlayCtrl_Frame(int frame);		//event handler function for "by frame" key //"按帧"按键响应函数

	void GetDeviceWorkstate();			//event handler function for "work status of device" key //"设备工作状态"按键响应函数
	void DeviceControldisk();			//event handler function for "disk control" key //"硬盘控制"按键响应函数
	void DeviceUserinfo();				//event handler function for "users infomation" key //"用户信息"按键响应函数
	
	void SeleteNormalPannel();			//display page of "common" //显示“常规”功能页面
	void SeleteAdvancePannel();			//display page of "advanced" //显示“高级”功能页面
	void SeleteSaveDataPannel();		//display page of "data saving" //显示“数据保存”功能页面
	void SeletePTZPannel();				//display page of "PTZ control" //显示“云台控制”功能页面
	void SeleteColorPannel();			//display page of "color adjust" //显示“颜色调整”功能页面
	void SeletePlayCtrlPannel();		//display page of "play control" //显示“播放控制”功能页面
	void SeleteDevListPannel();			//display page of "device list" //显示“设备列表”功能页面
	
	void UpdatePannelPosition();			//update sub windows position //更新各子窗口位置

	void LastError();						//display error reason of function run //显示函数执行出错原因

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
	void UpdateCurScreenInfo();  //refresh infomation display of current view //刷新当前画面的相关信息显示
	void SetSplit(int split);
	int  GetSplit();
	//获取画面窗口信息
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
	BOOL		m_bPTZCtrl;		//flag control status of PTZ //标识PTZ控制状态
	
//	BOOL		m_bFullSCRN;		//flag status of full screen //标识当前是否全屏状态
	CRect		m_clientRect;		//position of UI area //程序界面区域位置
	CRect		m_screenRect;		//store position of screen area //储存屏幕区域的位置
	CRect		m_pannelRect;		//store position of function panal area //储存功能面板区域的位置
	CRect		m_selectRect;		//store position of "select page" panal area //储存“选择页面”面板的位置
	CRect		m_btnAreaRect;		//store position of function keys area //储存功能按键区域的位置
	CRect		m_runtimeMsgRect;			//store position of "runtime infomation" panal area //储存“运行时信息”面板的位置

	CScreenPannel		m_screenPannel;		//play screen motherboard - sub window //播放屏幕底板－子窗口
//	CPlayWnd			m_playWnd[MAX_CHANNUM];		//play windows - sub window //各个播放画面－子窗口
//	CWnd				*m_originParent;	//fathor windows that store sub windows temperarily //临时储存各子窗口的父窗口
	CPTZPannel			m_ptzPannel;		//PTZ control panal - sub window //云台控制面板－子窗口
	CColorPannel		m_colorPannel;		//color control panal - sub window //颜色控制面板－子窗口
	CPlayCtrlPannel		m_playctrlPannel;	//replay control panal - sub window //回放控制面板－子窗口
	CNormalBtnPannel	m_normalBtnPannel;	//common function keys panal - sub window //常规功能按键面板－子窗口
	CAdvanceBtnPannel	m_advanceBtnPannel;	//advanced function keys panal - sub window //高级功能按键面板－子窗口
	CSaveDataPannel		m_saveDataPannel;	//saving data keys panal - sub window //数据保存按键面板－子窗口
	CSelectPannel		m_selectPannel;		//display "select page" keys panal - sub window //显示“选择页面”按键的面板－子窗口
	CRuntimeMsgPannel	m_runtimeMsgPannel;	//display runtime infomation panal - sub window //显示运行时信息的面板－子窗口
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
