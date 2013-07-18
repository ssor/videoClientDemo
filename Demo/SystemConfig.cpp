// SystemConfig.cpp : implementation file
//

#include "stdafx.h"
#include "netsdkdemo.h"
#include "SystemConfig.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemConfig dialog


CSystemConfig::CSystemConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemConfig::IDD, pParent)
{
	m_deviceID = -1;
	//{{AFX_DATA_INIT(CSystemConfig)
	//}}AFX_DATA_INIT
}


void CSystemConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemConfig)
	DDX_Control(pDX, IDC_SETDEVICECONFIG1, m_ocx_systemset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemConfig, CDialog)
	//{{AFX_MSG_MAP(CSystemConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemConfig message handlers

void CSystemConfig::setDeviceId(LONG deviceID)
{
	m_deviceID = deviceID;
}
void CSystemConfig::ShowDefModal(In_DeviceInfo& di )
{
	m_di = di;
	
	DoModal();
	return;
}

BOOL CSystemConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	m_ocx_systemset.SetConfigPageHide(8);

#ifdef LANG_ENG
	m_ocx_systemset.CreateDeviceFram(0);
#else
	m_ocx_systemset.CreateDeviceFram(1);
#endif

	m_ocx_systemset.SetDeviceShowType((long *)(&m_di));
	
	return TRUE; 
}

BEGIN_EVENTSINK_MAP(CSystemConfig, CDialog)
    //{{AFX_EVENTSINK_MAP(CSystemConfig)
	ON_EVENT(CSystemConfig, IDC_SETDEVICECONFIG1, 13 /* OnBlockAskData */, OnOnBlockAskDataSetdeviceconfig1, VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4)
	ON_EVENT(CSystemConfig, IDC_SETDEVICECONFIG1, 8 /* OnSaveDeviceData */, OnOnSaveDeviceDataSetdeviceconfig1, VTS_I4 VTS_I4 VTS_PI4 VTS_I4 VTS_PI4)
	ON_EVENT(CSystemConfig, IDC_SETDEVICECONFIG1, 18 /* OnDeviceSetInfo */, OnOnDeviceSetInfoSetdeviceconfig1, VTS_PI4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//////////////////////for test///////////////////////



//串口配置
//serial port configure
typedef struct {
	BYTE Com_Version[8]; /*!< version number *//*!< 版本号 */
	BYTE Function; /*!< serial port function 0-common, 1-control key-board, 2-clarify port, 3-ATM machion *//*!< 串口功能 0-普通, 1-控制键盘, 2-透明串口, 3-ATM机*/
	BYTE DataBits; /*!< data bit maybe:5,6,7,8 *//*!< 数据位 取值为5,6,7,8 */
	BYTE StopBits; /*!< stop bit 0-1bit, 1-1.5bits, 2-2bits *//*!< 停止位 0-1位, 1-1.5位, 2-2位 */
	BYTE Parity; /*!< verify bit:0-no, 1-odd, 2-even *//*!< 校验位 0-no, 1-odd, 2-even */
	DWORD BaudBase; /*!< baurdrate 0-9 mean: {300,600,1200,2400,4800,9600,19200,38400,57600,115200}*//*!< 波特率 0-9 分别表示: {300,600,1200,2400,4800,9600,19200,38400,57600,115200}*/
} CONFIG_COMM;

//云台配置
//PTZ configure
typedef struct
{
	DWORD baudrate; //the value reference to serial port configure // 具体值参考串口配置
	BYTE databits;
	BYTE parity;
	BYTE stopbits;
} PTZ_ATTR;

typedef struct {
	BYTE Ptz_Version[8]; /*!< version number *//*!< 版本号 */
	PTZ_ATTR PTZAttr; /*!< serial port attributes *//*!< 串口属性 */
	WORD DestAddr; /*!< destnation address 0-255 *//*!< 目的地址 0-255 */
	WORD Protocol; /*!< protocal type, save the subscript of prototcal, dynamic changing *//*!< 协议类型 保存协议的下标，动态变化 */
	WORD MonitorAddr; /*!< display device address *//*!< 监视器地址 0-64 */
	BYTE Reserved[10]; /*!< reserved *//*!< 保留 */
} CONFIG_PTZ;

//录象（定时）配置
//record(timver)configue
#define N_WEEKS 7
#define N_TSECT 6
typedef struct { //timer span // 定时时段
	BYTE StartHour; //start time //开始时间
	BYTE StartMin;
	BYTE StartSec;
	BYTE EndHour; //end time // 结束时间
	BYTE EndMin;
	BYTE EndSec;
	BYTE State; //the second bit is timer, the third bit is motion detect, the forth bit is alarm //第二位是定时，第三位是动态检测，第四位是报警
	BYTE Reserve;
} TSECT;
typedef struct {
	BYTE RecVersion[8]; /*!< version number *//*!< 版本号 */
	TSECT Sector[N_WEEKS][N_TSECT]; /*!< timer span, 7 days per-week, N_TSECT spans per-day *//*!< 定时时段，一个星期七天，每天N_TSECT时间段 */
	BYTE PreRecord; /*!< pre-record switch, 0-closed, 1-open *//*!< 预录开关, 0-关闭, 1-打开 */
	BYTE Redundancy; /*!< redundancy switch, 0-unvalid, 1-valid *//*!< 冗余开关，0-无效, 1-有效 */
	BYTE Reserved[2]; /*! reserved *//*!< 保留 */
} CONFIG_RECORD;

//图像配置
//picture configure
// 使用中的编码信息结构定义（请用此结构）
//valid struct of code infomation(please use this struct)
typedef struct {
	BYTE CapVersion[8]; //version number/*!< 版本号 */
	BYTE CifMode; //resolv:QCIF, CIF, CIF4/*!< 分辨率*/
	BYTE VideoType; //code mode/*!< 编码模式*/
	BYTE EncodeMode; //bit-stream control/*!< 码流控制 */
	BYTE ImgQlty; //image quality/*!< 码流的画质 */
	BYTE Frames; //frame rate/*!< 帧率 */
	BYTE Brightness; //brightness/*!< 亮度 */
	BYTE Contrast; //contrast/*!< 对比度 */
	BYTE Saturation; //sturation/*!< 饱和度 */
	BYTE Hue; //hue/*!< 色度 */
	BYTE AudioEn; //audio enable/*!< 音频使能 */
	BYTE Gain; //gain/*!< 增益 */
	BYTE CoverEnable; //area shelter switch/*!< 区域遮盖开关 */
	RECT Cover; //area shelter bound/*!< 区域遮盖范围 */
} OLD_CONFIG_CAPTURE;
//! 拟采用的编码信息结构（暂时没有使用）
//!want to used code infomation struct(not used now)
/*
enum capture_size_t {
	CAPTURE_SIZE_D1,
		CAPTURE_SIZE_HD1,
		CAPTURE_SIZE_DCIF,
		CAPTURE_SIZE_CIF,
		CAPTURE_SIZE_QCIF,
		CAPTURE_SIZE_VGA,
		CAPTURE_SIZE_QVGA,
		CAPTURE_SIZE_SVCD,
		CAPTURE_SIZE_NR,
};
enum capture_comp_t {
	CAPTURE_COMP_DIVX_MPEG4,
		CAPTURE_COMP_MS_MPEG4,
		CAPTURE_COMP_MPEG2,
		CAPTURE_COMP_MPEG1,
		CAPTURE_COMP_H263,
		CAPTURE_COMP_MJPG,
		CAPTURE_COMP_FCC_MPEG4,
		CAPTURE_COMP_H264,
		CAPTURE_COMP_NR,
};
enum capture_brc_t {
	CAPTURE_BRC_CBR,
		CAPTURE_BRC_VBR,
		CAPTURE_BRC_MBR,
		CAPTURE_BRC_NR,
};
*/
typedef struct 
{
	BYTE CapVersion[8]; //version number/*!< 版本号 */
	BYTE CifMode; //resolve:enum reference to capture_size_t/*!< 分辨率 参照枚举capture_size_t*/
	BYTE VideoType; //code mode:enum reference to capture_comp_t/*!< 编码模式 参照枚举capture_comp_t */
	BYTE EncodeMode; //bit-stream control:enum reference to capture_brc_t/*!< 码流控制 参照枚举capture_brc_t */
	BYTE ImgQlty; //image quality 1-6/*!< 码流的画质 1-6 */
	BYTE Frames; //frame rate : level : N:1-6, P:1-5/*!< 帧率 档次N制1-6, P制1-5 */
	BYTE Brightness; //brightness:0-100/*!< 亮度 0-100 */
	BYTE Contrast; //contrast:0-100/*!< 对比度 0-100 */
	BYTE Saturation; //saturation:0-100/*!< 饱和度 0-100 */
	BYTE Hue; //hue:0-100/*!< 色度 0-100 */
	BYTE AudioEn; //audio enable:0-close;1-open/*!< 音频使能 0-关闭, 1-打开 */
	BYTE Gain; //gain:0-100/*!< 增益 0-100 */
	BYTE CoverEnable; //area shelter switch:0-close;1:open/*!< 区域遮盖开关 0-关闭, 1-打开*/
	RECT Cover; //area shelter bound/*!< 区域遮盖范围 */
	BYTE TimeTilteEn; //time title enable:0-close;1-open/*!< 时间标题使能 0-关闭, 1-打开 */
	BYTE ChTitleEn; //channel title enable:0-close;1-open/*!< 通道标题使能 0-关闭, 1-打开 */
	BYTE Reserver[2]; //reserved/*!< 保留 */
} CONFIG_CAPTURE;

typedef struct
{
    unsigned char Version[8]; //8 bytes version infomation// 8字节的版本信息
    char HostName[16]; //host name // 主机名
    unsigned long HostIP; //IP address // IP 地址
    unsigned long Submask; //subnet mask// 子网掩码
    unsigned long GateWayIP; //gatewy ip // 网关 IP
    unsigned long DNSIP; // DNS IP
	
    // 外部接口
	//out interfaces
    unsigned long AlarmServerIP; //alarm center ip // 报警中心IP
    unsigned short  AlarmServerPort; //alarm center port // 报警中心端口
    unsigned long SMTPServerIP; // SMTP server IP
    unsigned short  SMTPServerPort; // SMTP server port
    unsigned long LogServerIP; // Log server IP
    unsigned short  LogServerPort; // Log server port
	
    // 本机服务端口
	// local machine server port
    unsigned short  HttpPort; //HTTP server port // HTTP服务端口号
    unsigned short  HttpsPort; //HTTPS server port // HTTPS服务端口号
    unsigned short  TCPPort; //TCP listen port // TCP 侦听端口
    unsigned short  TCPMaxConn; //TCP max connection number // TCP 最大连接数
    unsigned short  SSLPort; //SSL listen port // SSL 侦听端口
    unsigned short  UDPPort; //UDP listen port // UDP 侦听端口
    unsigned long McastIP; //group cast IP // 组播IP
    unsigned short  McastPort; //group cast port // 组播端口
    
    // 其他
	//other
    unsigned char  MonMode; //watch protocal 0-TCP,1-UDP,2-MCAST // 监视协议 0-TCP, 1-UDP, 2-MCAST
    unsigned char  PlayMode; //replay protocal 0-TCP, 1-UDP, 2-MCAST // 回放协议 0-TCP, 1-UDP, 2-MCAST
    unsigned char  AlmSvrStat; //alarm center status 0-close, 1-open // 报警中心状态 0-关闭, 1-打开
}CONFIG_NET;

//alarm
typedef struct
{
	DWORD dwVersion;
	BYTE dbReserve[4];
}VER_CONFIG;
#define NAME_LEN 32

#define ALARM_SECTS 2
typedef struct 
{
	VER_CONFIG sVerConfig; //config file version infomation /*! 配置文件版本信息 */
	DWORD AlarmMask; //mask of alarm out /*! 报警输出掩码 */
	DWORD RecordMask; //mask of record channels /*! 录象通道掩码 */
	DWORD TimeDelay; //record delay:10～300 sec /*! 录象延时：10～300 sec */
	BYTE SensorType; //sense organ type:always opened or always closed/*! 传感器类型：常开 or 常闭 */
	BYTE TimePreRec; //pre record time or pre record switch/*! 预录时间 或者 预录开关 */
	BYTE AlarmTipEn; //alarm promt /*! 报警提示 */
	TSECT sAlarmSects[ALARM_SECTS]; //alarm out and promt time spans /*! 报警输出和提示的时间段 */
	DWORD dwSectMask[ALARM_SECTS]; //alarm out and mask of promt time span /*! 报警输出和提示的时间段的掩码 */
	DWORD dwInputTypeMask; //mask of alarm in type /*! 报警输入类型掩码 */
	BYTE dbTourEn; //allow alarm tour /*! 是否允许报警轮训 */
	BYTE Mailer; //mask of send mail(bit1-bit8 mean max 8 channels) /*! 发送邮件掩码（1-8位表示最多8通道的图像） */
	BYTE SendAlarmMsg; //send alarm infomation(to alarm server, etc...) /*! 发送报警信息（给报警服务器等） */
	BYTE adbReserved; //reserved/*! 保留字段 */
} CONFIG_ALARM, *pCONFIG_ALARM;

//////////////////////end test///////////////////////

void CSystemConfig::OnOnBlockAskDataSetdeviceconfig1(long DeviceID, long lConfigType, long FAR* lpConfigbuf, long FAR* lpMaxLen, long FAR* lpConfigBufLen, long FAR* lpResult) 
{
	BOOL nRet;
	NET_TIME nTime;
	if(DeviceID == 0)
	{
		return;
	}
	switch(lConfigType)
	{
	case 1:
		nRet = CLIENT_QueryDeviceTime(DeviceID, &nTime, 2000);
		if(nRet)
		{
			*(LONG *)lpConfigBufLen =  sizeof(nTime);//g_TimeOutString(&nTime).GetBuffer(0)
			memcpy((char *)lpConfigbuf,(char *)&nTime,sizeof(nTime));
		}
		else if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;
	case 2:   //system code 5 mean character infomation//系统信息5表示字符信息
		nRet = CLIENT_QuerySystemInfo(DeviceID, 5, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 2000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;
	case 3:
		nRet = CLIENT_QueryConfig(DeviceID, 10, (char *)lpConfigbuf,*(LONG *)lpMaxLen, (int *)lpConfigBufLen, 2000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;
	case 4:
		nRet = CLIENT_QueryComProtocol(DeviceID, 0, (char *)lpConfigbuf,*(LONG *)lpMaxLen, (int *)lpConfigBufLen, 2000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;
	case 5:
		nRet = CLIENT_QueryComProtocol(DeviceID, 1, (char *)lpConfigbuf,*(LONG *)lpMaxLen, (int *)lpConfigBufLen, 2000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;	
	case 6:
	//	ZeroMemory(lpConfigbuf, *lpMaxLen);
	//	nRet = 1;
		nRet = CLIENT_QueryConfig(DeviceID, 210, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 2000);
		break;
	case 31:
	case 33:
	case 34: //DDNS
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 10000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		{
			//for test
			char temp[1000] = {0};
			memcpy(temp, lpConfigbuf, *lpConfigBufLen);
			//end test
		}
		break;
	case 50:
		nRet = CLIENT_QueryLog(DeviceID, (char *)lpConfigbuf,*(LONG *)lpMaxLen, (int *)lpConfigBufLen);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;
	case 51:
		ZeroMemory(lpConfigbuf,*lpMaxLen);
		nRet = 1;
	//	nRet = CLIENT_QueryConfig(DeviceID, 200, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 10000);
		break;

/////////////////////////////////for test////////////////////////
		
	case 20: //general
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		break;
	case 21: //comm
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		if (*lpConfigBufLen == sizeof(CONFIG_COMM))
		{
			CONFIG_COMM *temp = (CONFIG_COMM *)lpConfigbuf;
			int i = 0;
		}
		//test
	//	nRet = 1;
		break;
	case 22:
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		if (*lpConfigBufLen == sizeof(CONFIG_NET))
		{
			CONFIG_NET *ptmpNetCfg = (CONFIG_NET *)lpConfigbuf;
			int i = 0;
		}
		break;
	case 23: //record
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		if (*lpConfigBufLen == 16 * sizeof(CONFIG_RECORD))
		{
			int length = *lpConfigBufLen;
			while (length/sizeof(CONFIG_RECORD) > 0)
			{
				CONFIG_RECORD *temp = (CONFIG_RECORD *)lpConfigbuf;
				length -= sizeof(CONFIG_RECORD);
			}
		}
		break;
	case 24: //picture
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		if (*lpConfigBufLen == 16 * sizeof(OLD_CONFIG_CAPTURE))
		{
			int length = *lpConfigBufLen;
			while (length/sizeof(OLD_CONFIG_CAPTURE) > 0)
			{
				OLD_CONFIG_CAPTURE *temp = (OLD_CONFIG_CAPTURE *)lpConfigbuf;
				length -= sizeof(OLD_CONFIG_CAPTURE);
			}
		}
		break;
	case 25: //ptz
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		if (*lpConfigBufLen == 16 * sizeof(CONFIG_PTZ))
		{
			int length = *lpConfigBufLen;
			while (length/sizeof(CONFIG_PTZ) > 0)
			{
				CONFIG_PTZ *temp = (CONFIG_PTZ *)lpConfigbuf;
				length -= sizeof(CONFIG_PTZ);
			}
		}
		break;
	case 27: //alarm
		nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		}
		if (*lpConfigBufLen == 16 * sizeof(CONFIG_ALARM))
		{
			int length = *lpConfigBufLen;
			while (length/sizeof(CONFIG_ALARM) > 0)
			{
				CONFIG_ALARM *temp = (CONFIG_ALARM *)lpConfigbuf;
				length -= sizeof(CONFIG_ALARM);
			}
		}
		break;		
//////////////////////////////test end///////////////////////////////
	default:
		if(lConfigType >= 20 && lConfigType <= 27)
		{
			nRet = CLIENT_QueryConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, *(LONG *)lpMaxLen, (int *)lpConfigBufLen, 5000);
			if (!nRet)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			}
		}
	}
	if(nRet)
	{
		*lpResult = 1;		
	}
	else
	{
		((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		*lpResult = 0;		
	}
}

void CSystemConfig::OnOnSaveDeviceDataSetdeviceconfig1(long DeviceID, long lConfigType, long FAR* lpConfigbuf, long lConfigbuflen, long FAR* lpResult) 
{
	BOOL nRet = false;
	if(DeviceID < 0)
	{
		return;
	}
	switch(lConfigType)
	{
	case 1:
		nRet = CLIENT_SetupDeviceTime(DeviceID, (NET_TIME *)lpConfigbuf);
		break;
	case 3:
		nRet = 1;
		nRet = CLIENT_SetupConfig(DeviceID, 10, (char *)lpConfigbuf, lConfigbuflen, 5000);
		 if (!nRet)
		{
			 ((CNetSDKDemoDlg *)GetParent())->LastError();
		}
		break;
	case 31:
	case 33:
	case 34:
		nRet = CLIENT_SetupConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, lConfigbuflen, 5000);
		if (!nRet)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();
		}
		break;
	case 51:
	//	nRet = 1;
		nRet = CLIENT_SetupConfig(DeviceID, 200, (char *)lpConfigbuf, lConfigbuflen, 10000);
		break;
	default:
		if((lConfigType >= 20 && lConfigType <= 27))
		{
			nRet = CLIENT_SetupConfig(DeviceID, lConfigType - 20, (char *)lpConfigbuf, lConfigbuflen, 5000);
			if (!nRet)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();
			}
		}
	}
	if(nRet)
	{
		*lpResult = 1;		
	}
	else
	{
		((CNetSDKDemoDlg *)GetParent())->LastError();
		*lpResult = 0;
		TRACE("CONFIG ERROR %d",lConfigType );
	}
}

void CSystemConfig::OnOnDeviceSetInfoSetdeviceconfig1(long FAR* lpInfoType) 
{
	if(!*lpInfoType)
	{
		CDialog ::OnCancel();
	}
}
