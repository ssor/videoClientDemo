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



//��������
//serial port configure
typedef struct {
	BYTE Com_Version[8]; /*!< version number *//*!< �汾�� */
	BYTE Function; /*!< serial port function 0-common, 1-control key-board, 2-clarify port, 3-ATM machion *//*!< ���ڹ��� 0-��ͨ, 1-���Ƽ���, 2-͸������, 3-ATM��*/
	BYTE DataBits; /*!< data bit maybe:5,6,7,8 *//*!< ����λ ȡֵΪ5,6,7,8 */
	BYTE StopBits; /*!< stop bit 0-1bit, 1-1.5bits, 2-2bits *//*!< ֹͣλ 0-1λ, 1-1.5λ, 2-2λ */
	BYTE Parity; /*!< verify bit:0-no, 1-odd, 2-even *//*!< У��λ 0-no, 1-odd, 2-even */
	DWORD BaudBase; /*!< baurdrate 0-9 mean: {300,600,1200,2400,4800,9600,19200,38400,57600,115200}*//*!< ������ 0-9 �ֱ��ʾ: {300,600,1200,2400,4800,9600,19200,38400,57600,115200}*/
} CONFIG_COMM;

//��̨����
//PTZ configure
typedef struct
{
	DWORD baudrate; //the value reference to serial port configure // ����ֵ�ο���������
	BYTE databits;
	BYTE parity;
	BYTE stopbits;
} PTZ_ATTR;

typedef struct {
	BYTE Ptz_Version[8]; /*!< version number *//*!< �汾�� */
	PTZ_ATTR PTZAttr; /*!< serial port attributes *//*!< �������� */
	WORD DestAddr; /*!< destnation address 0-255 *//*!< Ŀ�ĵ�ַ 0-255 */
	WORD Protocol; /*!< protocal type, save the subscript of prototcal, dynamic changing *//*!< Э������ ����Э����±꣬��̬�仯 */
	WORD MonitorAddr; /*!< display device address *//*!< ��������ַ 0-64 */
	BYTE Reserved[10]; /*!< reserved *//*!< ���� */
} CONFIG_PTZ;

//¼�󣨶�ʱ������
//record(timver)configue
#define N_WEEKS 7
#define N_TSECT 6
typedef struct { //timer span // ��ʱʱ��
	BYTE StartHour; //start time //��ʼʱ��
	BYTE StartMin;
	BYTE StartSec;
	BYTE EndHour; //end time // ����ʱ��
	BYTE EndMin;
	BYTE EndSec;
	BYTE State; //the second bit is timer, the third bit is motion detect, the forth bit is alarm //�ڶ�λ�Ƕ�ʱ������λ�Ƕ�̬��⣬����λ�Ǳ���
	BYTE Reserve;
} TSECT;
typedef struct {
	BYTE RecVersion[8]; /*!< version number *//*!< �汾�� */
	TSECT Sector[N_WEEKS][N_TSECT]; /*!< timer span, 7 days per-week, N_TSECT spans per-day *//*!< ��ʱʱ�Σ�һ���������죬ÿ��N_TSECTʱ��� */
	BYTE PreRecord; /*!< pre-record switch, 0-closed, 1-open *//*!< Ԥ¼����, 0-�ر�, 1-�� */
	BYTE Redundancy; /*!< redundancy switch, 0-unvalid, 1-valid *//*!< ���࿪�أ�0-��Ч, 1-��Ч */
	BYTE Reserved[2]; /*! reserved *//*!< ���� */
} CONFIG_RECORD;

//ͼ������
//picture configure
// ʹ���еı�����Ϣ�ṹ���壨���ô˽ṹ��
//valid struct of code infomation(please use this struct)
typedef struct {
	BYTE CapVersion[8]; //version number/*!< �汾�� */
	BYTE CifMode; //resolv:QCIF, CIF, CIF4/*!< �ֱ���*/
	BYTE VideoType; //code mode/*!< ����ģʽ*/
	BYTE EncodeMode; //bit-stream control/*!< �������� */
	BYTE ImgQlty; //image quality/*!< �����Ļ��� */
	BYTE Frames; //frame rate/*!< ֡�� */
	BYTE Brightness; //brightness/*!< ���� */
	BYTE Contrast; //contrast/*!< �Աȶ� */
	BYTE Saturation; //sturation/*!< ���Ͷ� */
	BYTE Hue; //hue/*!< ɫ�� */
	BYTE AudioEn; //audio enable/*!< ��Ƶʹ�� */
	BYTE Gain; //gain/*!< ���� */
	BYTE CoverEnable; //area shelter switch/*!< �����ڸǿ��� */
	RECT Cover; //area shelter bound/*!< �����ڸǷ�Χ */
} OLD_CONFIG_CAPTURE;
//! ����õı�����Ϣ�ṹ����ʱû��ʹ�ã�
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
	BYTE CapVersion[8]; //version number/*!< �汾�� */
	BYTE CifMode; //resolve:enum reference to capture_size_t/*!< �ֱ��� ����ö��capture_size_t*/
	BYTE VideoType; //code mode:enum reference to capture_comp_t/*!< ����ģʽ ����ö��capture_comp_t */
	BYTE EncodeMode; //bit-stream control:enum reference to capture_brc_t/*!< �������� ����ö��capture_brc_t */
	BYTE ImgQlty; //image quality 1-6/*!< �����Ļ��� 1-6 */
	BYTE Frames; //frame rate : level : N:1-6, P:1-5/*!< ֡�� ����N��1-6, P��1-5 */
	BYTE Brightness; //brightness:0-100/*!< ���� 0-100 */
	BYTE Contrast; //contrast:0-100/*!< �Աȶ� 0-100 */
	BYTE Saturation; //saturation:0-100/*!< ���Ͷ� 0-100 */
	BYTE Hue; //hue:0-100/*!< ɫ�� 0-100 */
	BYTE AudioEn; //audio enable:0-close;1-open/*!< ��Ƶʹ�� 0-�ر�, 1-�� */
	BYTE Gain; //gain:0-100/*!< ���� 0-100 */
	BYTE CoverEnable; //area shelter switch:0-close;1:open/*!< �����ڸǿ��� 0-�ر�, 1-��*/
	RECT Cover; //area shelter bound/*!< �����ڸǷ�Χ */
	BYTE TimeTilteEn; //time title enable:0-close;1-open/*!< ʱ�����ʹ�� 0-�ر�, 1-�� */
	BYTE ChTitleEn; //channel title enable:0-close;1-open/*!< ͨ������ʹ�� 0-�ر�, 1-�� */
	BYTE Reserver[2]; //reserved/*!< ���� */
} CONFIG_CAPTURE;

typedef struct
{
    unsigned char Version[8]; //8 bytes version infomation// 8�ֽڵİ汾��Ϣ
    char HostName[16]; //host name // ������
    unsigned long HostIP; //IP address // IP ��ַ
    unsigned long Submask; //subnet mask// ��������
    unsigned long GateWayIP; //gatewy ip // ���� IP
    unsigned long DNSIP; // DNS IP
	
    // �ⲿ�ӿ�
	//out interfaces
    unsigned long AlarmServerIP; //alarm center ip // ��������IP
    unsigned short  AlarmServerPort; //alarm center port // �������Ķ˿�
    unsigned long SMTPServerIP; // SMTP server IP
    unsigned short  SMTPServerPort; // SMTP server port
    unsigned long LogServerIP; // Log server IP
    unsigned short  LogServerPort; // Log server port
	
    // ��������˿�
	// local machine server port
    unsigned short  HttpPort; //HTTP server port // HTTP����˿ں�
    unsigned short  HttpsPort; //HTTPS server port // HTTPS����˿ں�
    unsigned short  TCPPort; //TCP listen port // TCP �����˿�
    unsigned short  TCPMaxConn; //TCP max connection number // TCP ���������
    unsigned short  SSLPort; //SSL listen port // SSL �����˿�
    unsigned short  UDPPort; //UDP listen port // UDP �����˿�
    unsigned long McastIP; //group cast IP // �鲥IP
    unsigned short  McastPort; //group cast port // �鲥�˿�
    
    // ����
	//other
    unsigned char  MonMode; //watch protocal 0-TCP,1-UDP,2-MCAST // ����Э�� 0-TCP, 1-UDP, 2-MCAST
    unsigned char  PlayMode; //replay protocal 0-TCP, 1-UDP, 2-MCAST // �ط�Э�� 0-TCP, 1-UDP, 2-MCAST
    unsigned char  AlmSvrStat; //alarm center status 0-close, 1-open // ��������״̬ 0-�ر�, 1-��
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
	VER_CONFIG sVerConfig; //config file version infomation /*! �����ļ��汾��Ϣ */
	DWORD AlarmMask; //mask of alarm out /*! ����������� */
	DWORD RecordMask; //mask of record channels /*! ¼��ͨ������ */
	DWORD TimeDelay; //record delay:10��300 sec /*! ¼����ʱ��10��300 sec */
	BYTE SensorType; //sense organ type:always opened or always closed/*! ���������ͣ����� or ���� */
	BYTE TimePreRec; //pre record time or pre record switch/*! Ԥ¼ʱ�� ���� Ԥ¼���� */
	BYTE AlarmTipEn; //alarm promt /*! ������ʾ */
	TSECT sAlarmSects[ALARM_SECTS]; //alarm out and promt time spans /*! �����������ʾ��ʱ��� */
	DWORD dwSectMask[ALARM_SECTS]; //alarm out and mask of promt time span /*! �����������ʾ��ʱ��ε����� */
	DWORD dwInputTypeMask; //mask of alarm in type /*! ���������������� */
	BYTE dbTourEn; //allow alarm tour /*! �Ƿ���������ѵ */
	BYTE Mailer; //mask of send mail(bit1-bit8 mean max 8 channels) /*! �����ʼ����루1-8λ��ʾ���8ͨ����ͼ�� */
	BYTE SendAlarmMsg; //send alarm infomation(to alarm server, etc...) /*! ���ͱ�����Ϣ���������������ȣ� */
	BYTE adbReserved; //reserved/*! �����ֶ� */
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
	case 2:   //system code 5 mean character infomation//ϵͳ��Ϣ5��ʾ�ַ���Ϣ
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
