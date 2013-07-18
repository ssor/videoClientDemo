
#ifndef VD_CLIENT_SDK_H
#define VD_CLIENT_SDK_H

#include "libclient.h"

#ifdef WIN32

#ifdef DHNETSDK_EXPORTS
#define CLIENT_API  __declspec(dllexport) 
#else	//#ifdef DHNETSDK_EXPORTS
#define CLIENT_API  __declspec(dllimport)
#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#else	//linux

#define CLIENT_API	extern "C"
#define CALL_METHOD
#define CALLBACK

#ifdef RELEASE_HEADER

#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	unsigned long
#define TRUE	0x01
#define FALSE	0x00
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
#define NULL	0
typedef struct  tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
}RECT;
#else
#include "../netsdk/osIndependent.h"
#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** constant define  [��������]
***********************************************************************/
#define RV_SERIALNO_LEN 		48		//max size of device serial number [�豸���к��ַ�����]
#define RV_MAX_DISKNUM 			32		//max number of disk [���Ӳ�̸���]
#define RV_MAX_SDCARDNUM		32		//max number of SD card [���SD������]
#define RV_MAX_BURNING_DEV_NUM	32		//max number of imprinting device [����¼�豸����]
#define RV_BURNING_DEV_NAMELEN	32		//max size of device name [��¼�豸������󳤶�]
#define RV_MAX_LINK 			6		
#define RV_MAX_CHANNUM 			16		//max number of channel [���ͨ������]
#define RV_MAX_ALARMIN 			128		//max number of alarm-in [��󱨾��������]
#define RV_MAX_ALARMOUT 		64		//max number of alarm-out [��󱨾��������]

#define RV_MAX_RIGHT_NUM		100		//max number of usr authority [�û�Ȩ�޸�������]
#define RV_MAX_GROUP_NUM		20		//max number of user group [�û����������]
#define RV_MAX_USER_NUM			200		//max number of user [�û���������]
#define RV_RIGHT_NAME_LENGTH	32		//max size of authority name [Ȩ��������]
#define RV_USER_NAME_LENGTH		8		//max size of user name [�û�������]
#define RV_USER_PSW_LENGTH		8		//max size of user password [�û����볤��]
#define RV_MEMO_LENGTH			32		//max size of memo [��ע����]

#define RV_MAX_STRING_LEN		128
#define RV_DEF_REALPLAY_BUF_NUM (3) 
#define RV_MIN_REALPLAY_BUF_NUM (1) 
#define RV_MAX_REALPLAY_BUF_NUM (50) 

//callback type of listen from device [�����豸�ص�����]
#define RV_DVR_SERIAL_RETURN 1   //the callback of sending serial number by device [�豸�������кŻص�]
#define RV_DVR_DISCONNECT -1     //the callback of disconnect from device during verify period [��֤�ڼ��豸���߻ص�]

//constant for overprint character on picture [ͨ�������ַ�������س���]
#define MAX_STRING_LINE_LEN	6		//max six lines [�������]
#define MAX_PER_STRING_LEN  20		//max length per line [ÿ����󳤶�]

//number of DDNS [DDNS��Ŀ����]
#define MAX_DDNS_COUNT 16

//the types of alarm message callbacked, corresponding CLIENT_StartListen [�ص�������Ϣ���ͣ���ӦCLIENT_StartListen]
#define RV_COMM_ALARM			0x1100	//common alarm infomation (include:out-alarm, video lost, motion detect) [���汨����Ϣ(�����ⲿ��������Ƶ��ʧ����̬���)]
#define RV_SHELTER_ALARM		0x1101	//video shelter alarm [��Ƶ�ڵ�����]
#define RV_DISK_FULL_ALARM		0x1102	//disk full alarm [Ӳ��������]
#define RV_DISK_ERROR_ALARM		0x1103	//disk error alarm [Ӳ�̹��ϱ���]
#define RV_SOUND_DETECT_ALARM	0x1104	//audio detect alarm [��Ƶ��ⱨ��]
#define RV_ALARM_DECODER_ALARM	0x1105	//decoder alarm [��������������]

//extended types of alarm message callabcked, corresponding CLIENT_StartListenEx [��չ�ص�������Ϣ���ͣ���ӦCLIENT_StartListenEx]
//seperate alarm types detailly [������������ϸ�ֿ�]
#define RV_ALARM_ALARM_EX			0x2101	//out-alarm [�ⲿ����]
#define RV_MOTION_ALARM_EX			0x2102	//motion detect alarm [��̬��ⱨ��]
#define RV_VIDEOLOST_ALARM_EX		0x2103	//video lost alarm [��Ƶ��ʧ����]
#define RV_SHELTER_ALARM_EX			0x2104	//shelter alarm [�ڵ�����]
#define RV_SOUND_DETECT_ALARM_EX	0x2105	//audio detect alarm [��Ƶ��ⱨ��]
#define RV_DISKFULL_ALARM_EX		0x2106	//disk full alarm [Ӳ��������]
#define RV_DISKERROR_ALARM_EX		0x2107	//disk error alarm [��Ӳ�̱���]
#define RV_ENCODER_ALARM_EX			0x210A	//coder alarm [����������]
#define RV_URGENCY_ALARM_EX			0x210B	//urgent alarm [��������]
#define RV_WIRELESS_ALARM_EX		0x210C	//wireless alarm [���߱���]
#define RV_NEW_SOUND_DETECT_ALARM_EX 0x210D //new audio detect alarm, the struct reference to RV_NEW_SOUND_ALARM_STATE [����Ƶ��ⱨ��������Ϣ�Ľṹ���RV_NEW_SOUND_ALARM_STATE]
#define RV_DECODER_ALARM_EX			0x210E	//decoder alarm [����������]

#define RV_SAVIA_ALARM_TRACK		0x210F	//intelligent:track arithmatic alarm [���ܣ������㷨����]
#define RV_SAVIA_ALARM_CROSSLINE	0x2110	//intelligent:cross-line arithmatic alarm [���ܣ�Խ���㷨����]
#define RV_SAVIA_ALARM_CROSSNET		0x2111	//intelligent:invade arithmatic alarm [���ܣ������㷨����]
#define RV_SAVIA_ALARM_WANDER		0x2112	//intelligent:wander arithmatic alarm [���ܣ��ǻ��㷨����]
#define RV_SAVIA_ALARM_CONVERSE		0x2113	//intelligent:thrash arithmatic alarm [���ܣ������㷨����]
#define RV_SAVIA_ALARM_STATIC		0x2114	//intelligent:left alone arithmatic alarm [���ܣ������㷨����]
#define RV_SAVIA_ALARM_LOST			0x2115	//intelligent:lost arithmatic alarm [���ܣ���ʧ�㷨����]
#define RV_SAVIA_ALARM_DAMAGE		0x2116	//intelligent:spray finishing arithmatic alarm [���ܣ���Ϳ�㷨����]
#define RV_INTE_ALARM_SMOKEFIRE		0x2117	//intelligent:fireworks arithmatic alarm [���ܣ��̻��㷨����]

#define RV_INTE_ALARM_RED_LEVEL_1	0x2118	//intelligent:red detect level-1 [���ܣ����ܺ�ɫ���澯1��]
#define RV_INTE_ALARM_RED_LEVEL_2	0x2119	//intelligent:red detect level-2 [���ܣ����ܺ�ɫ���澯2��]
#define RV_INTE_ALARM_RED_LEVEL_3	0x211a	//intelligent:red detect level-3 [���ܣ����ܺ�ɫ���澯3��]
#define RV_INTE_ALARM_RED_LEVEL_4	0x211b	//intelligent:red detect level-4 [���ܣ����ܺ�ɫ���澯4��]
#define RV_INTE_ALARM_RED_LEVEL_5	0x211c	//intelligent:red detect level-5 [���ܣ����ܺ�ɫ���澯5��]
#define RV_INTE_ALARM_RED_LEVEL_6	0x211d	//intelligent:red detect level-6 [���ܣ����ܺ�ɫ���澯6��]


#define RV_CONFIG_RESULT_EVENT_EX	0X3000  //the returned value code for modify configure, reference to DEV_SET_RESULT [�޸����õķ����뷵�ؽṹ��DEV_SET_RESULT]
#define RV_REBOOT_EVENT_EX			0x3001	//event of device reboot [�豸�����¼�]
#define RV_AUTO_TALK_START_EX		0x3002  //device start talk [�豸������ʼ�����Խ�]
#define RV_AUTO_TALK_STOP_EX		0x3003  //device stop talk [�豸����ֹͣ�����Խ�]

//interface params of query device status : query type used in CLIENT_QueryDevState [��ѯ�豸״̬�ӿڲ�������ѯ���� ����CLIENT_QueryDevState����]
#define RV_DEVSTATE_COMM_ALARM		0x0001	//query common alarm (include:out-alarm, video lost, motion detect) [��ѯ��ͨ����(�����ⲿ��������Ƶ��ʧ����̬���)]
#define RV_DEVSTATE_SHELTER_ALARM	0x0002	//query shelter alarm [��ѯ�ڵ�����]
#define RV_DEVSTATE_RECORDING		0x0003	//query record status [��ѯ¼��״̬]
#define RV_DEVSTATE_DISK			0x0004	//query disk status [��ѯӲ��״̬]
#define RV_DEVSTATE_RESOURCE		0x0005	//system resource status [ϵͳ��Դ״̬]
#define RV_DEVSTATE_BITRATE			0x0006	//get channel bit-stream [��ȡͨ������]
#define RV_DEVSTATE_CONN			0x0007	//get connection status to device [��ȡ�豸����״̬]
#define RV_DEVSTATE_PROTOCAL_VER	0x0008	//get version of network protocal, pBuf = int* [��ȡ����Э��汾��,	pBuf = int*]
#define RV_DEVSTATE_TALK_ECTYPE		0x0009	//get format list of audio talk supported by device, reference to struct DHDEV_TALKFORMAT_LIST [��ȡ�豸֧�ֵ������Խ���ʽ�б����ṹ��DHDEV_TALKFORMAT_LIST]
#define RV_DEVSTATE_SD_CARD			0x000A	//get SD card infomation(products as IPC,etc...) [��ȡSD����Ϣ��IPC���Ʒ��]
#define RV_DEVSTATE_BURNING_DEV			0x000B	//query infomation of imprinting machine[��ѯ��¼����Ϣ]
#define RV_DEVSTATE_BURNING_PROGRESS	0x000C	//query imprinting process [��ѯ��¼����]
#define RV_DEVSTATE_PLATFORM		0x000D	//get supported platform [��ȡ�豸֧�ֵĽ���ƽ̨]
#define RV_DEVSTATE_CAMERA			0x000E	//get attributes of cameral, pBuf = DHDEV_CAMERA_INFO *, can have many bojects [��ȡ����ͷ������Ϣ��pBuf = DHDEV_CAMERA_INFO *�������ж���ṹ��]
#define RV_DEVSTATE_SOFTWARE		0x000F	//software version infomation of device [�豸����汾��Ϣ]
#define RV_DEVSTATE_LANGUAGE        0x0010  //audio types supported by device [�豸֧�ֵ���������]
#define RV_DEVSTATE_DSP				0x0011	//ability description of DSP [DSP��������]
#define	RV_DEVSTATE_OEM				0x0012	//OEM
#define	RV_DEVSTATE_NET				0x0013  //running infomation of network [��������״̬��Ϣ]
#define RV_DEVSTATE_TYPE			0x0014  //devive type [�豸����]
#define RV_DEVSTATE_SNAP			0x0015	 //query ability of snapshot function [ץͼ����������ѯ]

//snapshot and video code mode type [ץͼ��Ƶ��������]
#define CODETYPE_MPEG4   0
#define CODETYPE_H264    1
#define CODETYPE_JPG     2

//error type code, returned by CLIENT_GetLastError [�������ʹ��ţ�CLIENT_GetLastError�����ķ���]
#define _EC(x)						(0x80000000|x)
#define NET_NOERROR 				0				//no error [û�д���]
#define NET_ERROR					-1				//unknown error [δ֪����]
#define NET_SYSTEM_ERROR			_EC(1)			//error in Windows system [Windowsϵͳ����]
#define NET_NETWORK_ERROR			_EC(2)			//net error, maybe because net timeout [������󣬿�������Ϊ���糬ʱ]
#define NET_DEV_VER_NOMATCH			_EC(3)			//device protocal not mathched [�豸Э�鲻ƥ��]
#define NET_INVALID_HANDLE			_EC(4)			//invalid handle [�����Ч]
#define NET_OPEN_CHANNEL_ERROR		_EC(5)			//fail to open channel [��ͨ��ʧ��]
#define NET_CLOSE_CHANNEL_ERROR		_EC(6)			//fail to close channel [�ر�ͨ��ʧ��]
#define NET_ILLEGAL_PARAM			_EC(7)			//user params not valid [�û��������Ϸ�]
#define NET_SDK_INIT_ERROR			_EC(8)			//error occur while initializing SDK [SDK��ʼ������]
#define NET_SDK_UNINIT_ERROR		_EC(9)			//error occur while cleanuping SDK [SDK�������]
#define NET_RENDER_OPEN_ERROR		_EC(10)			//error occur while applying render resource [����render��Դ����]
#define NET_DEC_OPEN_ERROR			_EC(11)			//error occur while opening decode library [�򿪽�������]
#define NET_DEC_CLOSE_ERROR			_EC(12)			//error occur while closing decode library [�رս�������]
#define NET_MULTIPLAY_NOCHANNEL		_EC(13)			//detect that the channel number is 0 in multi-view previewing [�໭��Ԥ���м�⵽ͨ����Ϊ0]
#define NET_TALK_INIT_ERROR			_EC(14)			//fail to initialize audio record library [¼�����ʼ��ʧ��]
#define NET_TALK_NOT_INIT			_EC(15)			//audio record library not inialized [¼����δ����ʼ��]
#define	NET_TALK_SENDDATA_ERROR		_EC(16)			//error occur while sending audio data [������Ƶ���ݳ���]
#define NET_REAL_ALREADY_SAVING		_EC(17)			//real-time data is in saving status [ʵʱ�����Ѿ����ڱ���״̬]
#define NET_NOT_SAVING				_EC(18)			//not saved real-time data [δ����ʵʱ����]
#define NET_OPEN_FILE_ERROR			_EC(19)			//open file fail [���ļ�����]
#define NET_PTZ_SET_TIMER_ERROR		_EC(20)			//fail to lauch PTZ control timer [������̨���ƶ�ʱ��ʧ��]
#define NET_RETURN_DATA_ERROR		_EC(21)			//check returned value unvalid [�Է������ݵ�У�����]
#define NET_INSUFFICIENT_BUFFER		_EC(22)			//not enough buffer [û���㹻�Ļ���]
#define NET_NOT_SUPPORTED			_EC(23)			//not support the function in this SDK [��ǰSDKδ֧�ָù���]
#define NET_NO_RECORD_FOUND			_EC(24)			//can't find out the record [��ѯ����¼��]
#define NET_NOT_AUTHORIZED			_EC(25)			//don't have operation authority [�޲���Ȩ��]
#define NET_NOT_NOW					_EC(26)			//can't comit now [��ʱ�޷�ִ��]
#define NET_NO_TALK_CHANNEL			_EC(27)			//don't find out talk channel [δ���ֶԽ�ͨ��]
#define NET_NO_AUDIO				_EC(28)			//don't find out audio [δ������Ƶ]
#define NET_NO_INIT					_EC(29)			//CLientSDK not initialize [CLientSDKδ����ʼ��]
#define NET_DOWNLOAD_END			_EC(30)			//download over [�����ѽ���]
#define NET_EMPTY_LIST				_EC(31)			//the result list of query is empty [��ѯ���Ϊ��]

#define NET_ERROR_GETCFG_SYSATTR	_EC(32)			//fail position while getting configure : system attributes [��ȡ����ʧ��λ�ã�ϵͳ����]
#define NET_ERROR_GETCFG_SERIAL		_EC(33)			//fail position while getting configure : serial number [��ȡ����ʧ��λ�ã����к�]
#define NET_ERROR_GETCFG_GENERAL	_EC(34)			//fail position while getting configure : common attributes [��ȡ����ʧ��λ�ã���������]
#define NET_ERROR_GETCFG_DSPCAP		_EC(35)			//fail position while getting configure : ability description of DSP [��ȡ����ʧ��λ�ã�DSP��������]
#define NET_ERROR_GETCFG_NETCFG		_EC(36)			//fail position while getting configure : network attributes [��ȡ����ʧ��λ�ã���������]
#define NET_ERROR_GETCFG_CHANNAME	_EC(37)			//fail position while getting configure : channel name [��ȡ����ʧ��λ�ã�ͨ������]
#define NET_ERROR_GETCFG_VIDEO		_EC(38)			//fail position while getting configure : video attributes [��ȡ����ʧ��λ�ã���Ƶ����]
#define NET_ERROR_GETCFG_RECORD		_EC(39)			//fail position while getting configure : configure of timer record [��ȡ����ʧ��λ�ã�¼��ʱ����]
#define NET_ERROR_GETCFG_PRONAME	_EC(40)			//fail position while getting configure : protocal name of decoder [��ȡ����ʧ��λ�ã�������Э������]
#define NET_ERROR_GETCFG_FUNCNAME	_EC(41)			//fail position while getting configure : function name of 232 serial port [��ȡ����ʧ��λ�ã�232���ڹ�������]
#define NET_ERROR_GETCFG_485DECODER	_EC(42)			//fail position while getting configure : attributes of decoder [��ȡ����ʧ��λ�ã�����������]
#define NET_ERROR_GETCFG_232COM		_EC(43)			//fail position while getting configure : attributes of 232 serial port [��ȡ����ʧ��λ�ã�232��������]
#define NET_ERROR_GETCFG_ALARMIN	_EC(44)			//fail position while getting configure : attributes of alarm-in [��ȡ����ʧ��λ�ã��ⲿ������������]
#define NET_ERROR_GETCFG_ALARMDET	_EC(45)			//fail position while getting configure : attributes of picture detect [��ȡ����ʧ��λ�ã�ͼ���ⱨ������]
#define NET_ERROR_GETCFG_SYSTIME	_EC(46)			//fail position while getting configure : device time [��ȡ����ʧ��λ�ã��豸ʱ��]
#define NET_ERROR_GETCFG_PREVIEW	_EC(47)			//fail position while getting configure : params of preview [��ȡ����ʧ��λ�ã�Ԥ������]
#define NET_ERROR_GETCFG_AUTOMT		_EC(48)			//fail position while getting configure : configure of auto-mantance [��ȡ����ʧ��λ�ã��Զ�ά������]
#define NET_ERROR_GETCFG_VIDEOMTRX	_EC(49)			//fail position while getting configure : configure of video matrix [��ȡ����ʧ��λ�ã���Ƶ��������]
#define NET_ERROR_GETCFG_COVER		_EC(50)			//fail position while getting configure : video area shelter [��ȡ����ʧ��λ�ã���Ƶ�����ڵ�]
#define NET_ERROR_GETCFG_WATERMAKE	_EC(51)			//fail position while getting configure : configure of watermask [��ȡ����ʧ��λ�ã�ͼ��ˮӡ����]
#define NET_ERROR_GETCFG_ETHERNET	_EC(300)		//fail position while getting configure : network card configure [��ȡ����ʧ��λ�ã���������]
#define NET_ERROR_GETCFG_WLAN		_EC(301)		//fail position while getting configure : wireless card infomation [��ȡ����ʧ��λ�ã�����������Ϣ]
#define NET_ERROR_GETCFG_WLANDEV	_EC(302)		//fail position while getting configure : search wireless network device [��ȡ����ʧ��λ�ã��������������豸]
#define NET_ERROR_GETCFG_REGISTER	_EC(303)		//fail position while getting configure : configure of auto-register params [��ȡ����ʧ��λ�ã�����ע���������]
#define NET_ERROR_GETCFG_CAMERA		_EC(304)		//fail position while getting configure : configure of cameral attributes [��ȡ����ʧ��λ�ã�����ͷ��������]
#define NET_ERROR_GETCFG_INFRARED	_EC(305)		//fail position while getting configure : configure of infrared ray alarm [��ȡ����ʧ��λ�ã����ⱨ������]
#define NET_ERROR_GETCFG_SOUNDALARM	_EC(306)		//fail position while getting configure : configure of audio alarm [��ȡ����ʧ��λ�ã���Ƶ��������]
#define NET_ERROR_GETCFG_STORAGE    _EC(307)		//fail position while getting configure : configure of store position [��ȡ����ʧ��λ�ã��洢λ������]
#define NET_ERROR_GETCFG_MAIL		_EC(308)		//fail to get email configure [��ȡ�ʼ�����ʧ��]


#define NET_ERROR_SETCFG_GENERAL	_EC(55)			//fail position while setting configure : common attributes [��������ʧ��λ�ã���������]
#define NET_ERROR_SETCFG_NETCFG		_EC(56)			//fail position while setting configure : network attributes [��������ʧ��λ�ã���������]
#define NET_ERROR_SETCFG_CHANNAME	_EC(57)			//fail position while setting configure : channel name [��������ʧ��λ�ã�ͨ������]
#define NET_ERROR_SETCFG_VIDEO		_EC(58)			//fail position while setting configure : video attributes [��������ʧ��λ�ã���Ƶ����]
#define NET_ERROR_SETCFG_RECORD		_EC(59)			//fail position while setting configure : configure of timer record [��������ʧ��λ�ã�¼��ʱ����]
#define NET_ERROR_SETCFG_485DECODER	_EC(60)			//fail position while setting configure : attributes of decoder [��������ʧ��λ�ã�����������]
#define NET_ERROR_SETCFG_232COM		_EC(61)			//fail position while setting configure : attributes of 232 serial port [��������ʧ��λ�ã�232��������]
#define NET_ERROR_SETCFG_ALARMIN	_EC(62)			//fail position while setting configure : attributes of alarm-in [��������ʧ��λ�ã��ⲿ������������]
#define NET_ERROR_SETCFG_ALARMDET	_EC(63)			//fail position while setting configure : attributes of picture detect [��������ʧ��λ�ã�ͼ���ⱨ������]
#define NET_ERROR_SETCFG_SYSTIME	_EC(64)			//fail position while setting configure : device time [��������ʧ��λ�ã��豸ʱ��]
#define NET_ERROR_SETCFG_PREVIEW	_EC(65)			//fail position while setting configure : preview params [��������ʧ��λ�ã�Ԥ������]
#define NET_ERROR_SETCFG_AUTOMT		_EC(66)			//fail position while setting configure : configure of auto-mantance [��������ʧ��λ�ã��Զ�ά������]
#define NET_ERROR_SETCFG_VIDEOMTRX	_EC(67)			//fail position while setting configure : configure of video matrix [��������ʧ��λ�ã���Ƶ��������]
#define NET_ERROR_SETCFG_COVER		_EC(69)			//fail position while setting configure : video area shelter [��������ʧ��λ�ã���Ƶ�����ڵ�]
#define NET_ERROR_SETCFG_WATERMAKE	_EC(60)			//fail position while setting configure : configure of picture watermark [��������ʧ��λ�ã�ͼ��ˮӡ����]
#define NET_ERROR_SETCFG_WLAN		_EC(61)			//fail position while setting configure : wireless network information [��������ʧ��λ�ã�����������Ϣ]
#define NET_ERROR_SETCFG_WLANDEV	_EC(62)			//fail position while setting configure : select wireless network device [��������ʧ��λ�ã�ѡ�����������豸]
#define NET_ERROR_SETCFG_REGISTER	_EC(63)			//fail position while setting configure : configure of auto-register params [��������ʧ��λ�ã�����ע���������]
#define NET_ERROR_SETCFG_CAMERA		_EC(64)			//fail position while setting configure : configure of cameral attributes [��������ʧ��λ�ã�����ͷ��������]
#define NET_ERROR_SETCFG_INFRARED	_EC(65)			//fail position while setting configure : configure of infrared ray alarm [��������ʧ��λ�ã����ⱨ������]
#define NET_ERROR_SETCFG_SOUNDALARM	_EC(66)			//fail position while setting configure : configure of audio alarm [��������ʧ��λ�ã���Ƶ��������]
#define NET_ERROR_SETCFG_STORAGE    _EC(67)			//fail position while setting configure : configure of store position [��������ʧ��λ�ã��洢λ������]

#define NET_AUDIOENCODE_NOTINIT		_EC(70)			//interface of audio code not initialized success [��Ƶ����ӿ�û�гɹ���ʼ��]
#define NET_DATA_TOOLONGH			_EC(71)			//data too long [���ݹ���]

#define NET_UNSUPPORTED				_EC(72)			//device don't support this operation [�豸��֧�ָò���]
#define NET_DEVICE_BUSY				_EC(73)			//resource of device not enough [�豸��Դ����]
#define NET_SERVER_STARTED			_EC(74)			//server had been lauched [�������Ѿ�����]
#define NET_SERVER_STOPPED			_EC(75)			//server had not been lauched [��������δ�ɹ�����]

#define NET_LISTER_INCORRECT_SERIAL	_EC(80)			//inputed serial number is incorrect [�������к�����]
#define NET_QUERY_DISKINFO_FAILED	_EC(81)			//fail to get disk infomation [��ȡӲ����Ϣʧ��]

#define NET_LOGIN_ERROR_PASSWORD	_EC(100)		//passwork not correct [���벻��ȷ]
#define NET_LOGIN_ERROR_USER		_EC(101)		//account not exist [�ʻ�������]
#define NET_LOGIN_ERROR_TIMEOUT		_EC(102)		//wait to login timeout [�ȴ���¼���س�ʱ]
#define NET_LOGIN_ERROR_RELOGGIN	_EC(103)		//account had logined [�ʺ��ѵ�¼]
#define NET_LOGIN_ERROR_LOCKED		_EC(104)		//account had been locked [�ʺ��ѱ�����]
#define NET_LOGIN_ERROR_BLACKLIST	_EC(105)		//account had been add to black ip list [�ʺ��ѱ���Ϊ������]
#define NET_LOGIN_ERROR_BUSY		_EC(106)		//resource is not enough, system is busy [��Դ���㣬ϵͳæ]
#define NET_LOGIN_ERROR_CONNECT		_EC(107)		//fail to connect to host [��������ʧ��"]
#define NET_LOGIN_ERROR_NETWORK		_EC(108)		//fail to connect to network [��������ʧ��"]

#define NET_RENDER_SOUND_ON_ERROR	_EC(120)		//Render Library open audio error [Render�����Ƶ����]
#define NET_RENDER_SOUND_OFF_ERROR	_EC(121)		//Render Library close audio error [Render��ر���Ƶ����]
#define NET_RENDER_SET_VOLUME_ERROR	_EC(122)		//Render Library control volumn error [Render�������������]
#define NET_RENDER_ADJUST_ERROR		_EC(123)		//Render Library set picture param error [Render�����û����������]
#define NET_RENDER_PAUSE_ERROR		_EC(124)		//Render Library pause error [Render����ͣ���ų���]
#define NET_RENDER_SNAP_ERROR		_EC(125)		//Render Library snapshot error [Render��ץͼ����]
#define NET_RENDER_STEP_ERROR		_EC(126)		//Render Library step error [Render�ⲽ������]
#define NET_RENDER_FRAMERATE_ERROR	_EC(127)		//Render Library set frame rate error [Render������֡�ʳ���]

#define NET_GROUP_EXIST				_EC(140)		//group name is exist already [�����Ѵ���]
#define	NET_GROUP_NOEXIST			_EC(141)		//group name is not exist [����������]
#define NET_GROUP_RIGHTOVER			_EC(142)		//authorities of the group exceed range of the authority list [���Ȩ�޳���Ȩ���б�Χ]
#define NET_GROUP_HAVEUSER			_EC(143)		//can't delete the group because there are users belong to this group [�������û�������ɾ��]
#define NET_GROUP_RIGHTUSE			_EC(144)		//some authority of the group is using by some user [���ĳ��Ȩ�ޱ��û�ʹ�ã����ܳ���]
#define NET_GROUP_SAMENAME			_EC(145)		//new group name is duplicate to some exist group name [������ͬ���������ظ�]
#define	NET_USER_EXIST				_EC(146)		//user exist [�û��Ѵ���]
#define NET_USER_NOEXIST			_EC(147)		//user not exist [�û�������]
#define NET_USER_RIGHTOVER			_EC(148)		//the authorities of user excceed to the authorities of group [�û�Ȩ�޳�����Ȩ��]
#define NET_USER_PWD				_EC(149)		//reserved account, can't be modified [�����ʺţ��������޸�����]
#define NET_USER_FLASEPWD			_EC(150)		//incorrect password [���벻��ȷ]
#define NET_USER_NOMATCHING			_EC(151)		//password not matched [���벻ƥ��]


#define NET_CONFIG_DEVBUSY			_EC(999)		//can't set now [��ʱ�޷�����]
#define NET_CONFIG_DATAILLEGAL		_EC(1000)		//data for configure is invalid [�������ݲ��Ϸ�]

//interface for remote configure : CLIENT_GetDEVConfig,CLIENT_GetDEVConfig, their params and commands define [Զ�����ýӿ�CLIENT_GetDEVConfig,CLIENT_GetDEVConfig�����������]
#define RV_DEV_DEVICECFG			1		//get device params [��ȡ�豸����]
#define RV_DEV_NETCFG				2		//get network params [��ȡ�������]
#define RV_DEV_CHANNELCFG			3		//get channel configure - picture and compress params, etc... [��ȡͨ�����ã�ͼ��ѹ��������]
#define RV_DEV_PREVIEWCFG 			4		//get preview params [��ȡԤ������]
#define RV_DEV_RECORDCFG			5		//get record time params [��ȡ¼��ʱ�����]
#define RV_DEV_COMMCFG				6		//get serial port params [��ȡ���ڲ���]
#define RV_DEV_ALARMCFG 			7		//get alarm params [��ȡ��������]
#define RV_DEV_TIMECFG 				8		//get DVR time [��ȡDVRʱ��]
#define RV_DEV_TALKCFG				9		//talk params [�Խ�����]
#define RV_DEV_AUTOMTCFG			10		//auto-mantance configure [�Զ�ά������]		
#define	RV_DEV_VEDIO_MARTIX			11		//configure of local matrix control plot [����������Ʋ�������]	
#define RV_DEV_MULTI_DDNS			12		//configure of multi-DDNS server [��ddns����������]
#define RV_DEV_SNAP_CFG				13		//configure about snapshot [ץͼ�������]
#define RV_DEV_WEB_URL_CFG			14		//configure of HTTP path [HTTP·������]
#define RV_DEV_FTP_PROTO_CFG		15		//configure of FTP [FTP�ϴ�����]
#define RV_DEV_INTERVIDEO_CFG		16		//configure of platform connection, param channel means platform type now [ƽ̨�������ã���ʱchannel��������ƽ̨���ͣ�]
#define RV_DEV_VIDEO_COVER			17		//configure of area shelter [�����ڵ�����]
#define RV_DEV_TRANS_STRATEGY		18		//configure of transport plot, picture quality first / fluency first [����������ã���������\����������]
#define RV_DEV_DOWNLOAD_STRATEGY	19		//configure of record download plot, high download / common download [¼�����ز������ã���������\��ͨ����]
#define RV_DEV_WATERMAKE_CFG		20		//configure of picture watermark [ͼ��ˮӡ����]
#define RV_DEV_WLAN_CFG				21		//configure of wireless network [������������]
#define RV_DEV_WLAN_DEVICE_CFG		22		//configure of search wireless device [���������豸����]
#define RV_DEV_REGISTER_CFG			23		//configure of auto-register params [����ע���������]
#define RV_DEV_CAMERA_CFG			24		//configure of cameral attributes [����ͷ��������]
#define RV_DEV_INFRARED_CFG 		25		//get infrared ray alarm params [��ȡ���ⱨ������]
#define RV_DEV_SNIFFER_CFG			26		//configure of capture packet by Sniffer [Snifferץ������]
#define RV_DEV_MAIL_CFG				27		//configure of email, recommend to use this type of configure [�ʼ�����,�����Ժ���ô���������]
#define RV_DEV_DNS_CFG				28		//configure of DNS server [DNS����������]
#define RV_DEV_NTP_CFG				29		//configure of NTP [NTP����]
#define RV_DEV_AUDIO_DETECT_CFG		30		//configure of audio detect [��Ƶ�������]
#define RV_DEV_STORAGE_STATION_CFG  31      //configure of store position [�洢λ������]
#define RV_DEV_PTZ_OPT_CFG			32		//attributes of PTZ operation [��̨��������]
#define RV_DEV_DDNS_CFG				33		//configure of DDNS [DDNS����]
#define RV_DEV_UPNP_CFG				34		//configure of UPNP [UPNP����]
#define RV_DEV_SAVIA_ALARM_CFG		35		//configure of SAVIA alarm params [SAVIA������������]
#define RV_DEV_SAVIA_COUNT_CFG		36		//SAVIA count [SAVIA��Ŀ]
#define RV_DEV_BLACKWHITE_CFG		37		//params of black and white ip list [�ڰ���������]
#define RV_DEV_DDNS_CFG_EX			38		//configure of DDNS [DDNS����]
#define RV_DEV_DECODER_CFG			39		//configure of decoder [����������]
#define RV_DEV_REG_SERVER_CFG		40		//configure of auto-register [����ע������]
#define RV_DEV_DISPLAY_SPLIT		41		//configure of views combine and split [����ָ�ͨ���������]
#define RV_DEV_DISPLAY_TOUR			42		//configure of tour [��Ѳ����]
#define RV_DEV_DISPLAY_SPLITTOUR	43		//configure of views combine adn split tour [����ָ�ͨ�������Ѳ����]
#define RV_DEV_SNAP_CFG_NEW			44		//configure of snapshot [ץͼ�������]
#define RV_DEV_DECODER_ALARM_CFG	45		//configure of decoder alarm [�������澯����]
#define RV_DEV_MARGIN_CFG			46		//configure of TV adjust [TV��������]
#define RV_DEV_IPCONFLICT_CFG		47		//configure of IP conflict [IP��ͻ����]
#define RV_DEV_MAIL_CFG_EX			48		//new configure of email [����������]
#define RV_DEV_DEV_CFG				49		//device name (use new protocal) [�豸��Ϣ(ʹ��TLVЭ��)]
#define RV_DEV_CHANNEL_ENC_CFG		50		//code infomation of channel (use new protocal) [�豸ͨ��������Ϣ(ʹ��TLVЭ��)]
#define RV_DEV_NET_BASE_CFG			51		//basic network configure (use new protocal) [������������(ʹ��TLVЭ��)]
#define RV_DEV_NET_APP_CFG			52		//application network configure (use new protocal) [Ӧ����������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_CFG			53		//get all alarm configure (use new protocal) [��ȡ���б�������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_IN_CFG			54		//set alarm-in alarm configure (use new protocal) [���ñ������뱨������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_MOTION_CFG		55		//set video detect alarm configure (use new protocal) [������Ƶ���챨������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_LOSS_CFG		56		//set video lost alarm configure (use new protocal) [������Ƶ��Ƶ��ʧ��������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_BIND_CFG		57		//set video shelter alarm configure (use new protocal) [������Ƶ��Ƶ�ڵ���������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_NODISK_CFG		58		//set no disk alarm configure (use new protocal) [������Ӳ�̱�������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_ERRDISK_CFG	59		//set disk error alarm configure (use new protocal) [����Ӳ�̴��󱨾�����(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_FULLDISK_CFG	60		//set disk full alarm configure (use new protocal) [����Ӳ������������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_NETBROKEN_CFG	61		//set network disconnect alarm configure (use new protocal) [���ö�����������(ʹ��TLVЭ��)]
#define RV_DEV_ALARM_IPCONFLICT_CFG	62		//set IP conflict alarm configure (use new protocal) [����IP��ͻ��������(ʹ��TLVЭ��)]

#define RV_DEV_INTERVIDEO_BELL_CFG	64		//configure of bell platform connection [bellƽ̨��������]
#define RV_DEV_INTERVIDEO_MEGA_CFG	65		//configure of HXHT platform connection [���Ż�ͨƽ̨��������]
#define RV_DEV_INTERVIDEO_VS300_CFG	66		//configure of VS300 platform connection [VS300ƽ̨��������]
#define RV_DEV_INTERVIDEO_ZXSHENYAN_CFG	67	//configure of SHENYAN platform connection [����ƽ̨��������]

#define RV_DEV_DISK_CFG				80		//configure of disk (use new protocal) [��������(ʹ��TLVЭ��)]
#define RV_DEV_NET_COMM_CFG			81		//network common configure (use new protocal) [����ͨ������(ʹ��TLVЭ��)]
#define RV_DEV_EMAIL_CFG			82		//email configure (use new protocal) [EMAIL����(ʹ��TLVЭ��)]
#define RV_DEV_DNS_CFG_TLV			83		//dns configure (use new protocal) [dns����(ʹ��TLVЭ��)]
#define RV_DEV_UPNP_CFG_TLV			84		//upnp cpnfigure (use new protocal) [upnp����(ʹ��TLVЭ��)]
#define RV_DEV_PPPOE_CFG			85		//pppoe configure (use new protocal) [pppoe����(ʹ��TLVЭ��)]
#define RV_DEV_MDDNS_CFG			86		//ddns configure (use new protocal) [DDNS����(ʹ��TLVЭ��)]
#define RV_DEV_CODE_CFG				87		//code configure (use new protocal) [��������(ʹ��TLVЭ��)]
#define RV_DEV_NTP_CFG_TLV			88		//NTP configure (use new protocal) [NTP����(ʹ��TLVЭ��)]
#define RV_DEV_OUT_MODE_CFG			89		//output mode configure (use new protocal) [���ģʽ����(ʹ��TLVЭ��)]
#define	RV_DEV_PRESET_CFG			90		//configure of PTZ preset [��̨Ԥ�õ�����]
#define RV_DEV_TOUR_CFG				91		//configure of PTZ tour in prestes [��̨���Ѳ������]
#define RV_DEV_ADDPRESET_CFG		92		//add preset operation [����Ԥ�õ����]
#define RV_DEV_DELETEPRESET_CFG		93		//delete preset operation [ɾ��Ԥ�õ����]
#define	RV_DEV_ADDTOURPRESET_CFG	94		//add preset to tour operation [����Ѳ��Ԥ�õ����]
#define RV_DEV_DELTOURPRESET_CFG	95		//delete preset from tour operation [ɾ��Ѳ��Ԥ�õ����]
#define	RV_DEV_CLEARTOUR_CFG		96		//delete tour [ɾ��Ѳ����·]
#define	RV_DEV_FTP_CFG				97		//FTP configure [FTP����]
#define	RV_DEV_RTSP_CFG				98		//RTSP configure [RTSP����]
#define	RV_DEV_INTERED_CFG			99		//configure of intelligent red detect alarm [���ܺ�ɫ��ⱨ������]
#define RV_DEV_NETCFG_RHEX			100		//get network params (not 98 serial device remotehost's legth is 64 bytes) [��ȡ�������(��98�豸remotehost����64�ֽ�)]
#define	RV_DEV_RECCTL_CFG			101		//record control params (use new protocal) [¼����Ʋ���(ʹ��TLVЭ��)]
#define RV_DEV_COMMCFG_EX			102		//get serial port params (more than 16 channels) [��ȡ���ڲ���(����16ͨ��)]
#define RV_DEV_CHANNEL_NAME			103		//get channel name (use new protocal) [��ȡͨ����(ʹ��TLVЭ��)]
#define RV_DEV_AUDIO_T				104		//audio configure (use new protocal) [��Ƶ����(ʹ��TLVЭ��)]
#define RV_DEV_DIGICHAN_TOUR		105		//digital channel tour configure (use new protocal) [����ͨ����ѵ����(ʹ��TLVЭ��)]
#define RV_DEV_KBD					106		//protocal of control key-board (use new protocal) [���Ƽ���Э��(ʹ��TLVЭ��)]
#define RV_DEV_MATRIX_XINGHUO		107		//matrix (for XINGHUO Corp.) configure (use new protocal) [����(�ǻ�)����(ʹ��TLVЭ��)]
#define RV_DEV_RTSP_CFGEX			108		//get RTSP infomation (not use new protocal) [��ȡRTSP��Ϣ(ʹ�÷�TLVЭ��)]
#define RV_DEV_NTP_CFGEX			109		//get NTP infomation (not use new protocal) [��ȡNTP��Ϣ(ʹ�÷�TLVЭ��)]
#define RV_DEV_OSDZOOM_CFG			110		//Get OSD zoom infomation(use new protocal)	[��ȡOSD zoom��Ϣ(ʹ��TLVЭ��)]
//added by zhubo 
#define RV_DEV_MATRIX_CIDPID        111     //Get the CID and PID relation (use new protocol)[��ȡ����������ͨ�������ŵĶ�Ӧ��ϵ]
#define RV_DEV_SVAC_CFG				112		//Get SVAC infomation(use new protocal) [��ȡSVAC������Ϣ(ʹ��TLVЭ��)]

#define RV_DEV_USER_END_CFG			1000

////////////////constant abount remote configure struct [Զ�����ýṹ����س���]///////////////////////
#define RV_MAX_MAIL_ADDR_LEN		128	//max length of email sender's or receiver's address [�ʼ���(��)�˵�ַ��󳤶�]
#define RV_MAX_MAIL_SUBJECT_LEN		64	//max length of email title [�ʼ�������󳤶�]
#define RV_MAX_IPADDR_LEN			16	//max length of IP address [IP��ַ�ַ�������]
#define RV_MACADDR_LEN				40	//max length of MAC address [MAC��ַ�ַ�������]
#define RV_MAX_URL_LEN				128	//max length of URL [URL�ַ�������]
#define RV_MAX_DEV_ID_LEN			48	//max length of code number of machine [���������󳤶�]
#define	RV_MAX_HOST_NAMELEN			64  //max length of host name [�������ַ�������]
#define RV_MAX_HOST_PSWLEN			32	//max length of password [����]
#define RV_MAX_HOST_PSWLEN_EX		64	//max length of password extend [����]
#define RV_MAX_NAME_LEN				16	//max length of common name [ͨ�������ַ�������]
#define RV_MAX_NAME_LEN_EX			32	//max length of email user name [�����û����ַ�������]	
#define RV_MAX_ETHERNET_NUM			2	//max number of ethernet interface ��̫����������]
#define	RV_DEV_SERIALNO_LEN			48	//max length of serial number string [���к��ַ�������]
#define RV_DEV_TYPE_LEN				32	//max length of device type string [�豸�����ַ�������]
#define RV_N_WEEKS					7	//number of days per week [һ�ܵ�����]
#define RV_N_TSECT					6	//number of common time slice [ͨ��ʱ��θ���]
#define RV_N_REC_TSECT				6	//number of record time slice [¼��ʱ��θ���]
#define RV_N_COL_TSECT				2	//number of color time slice [��ɫʱ��θ���]	
#define RV_CHAN_NAME_LEN			32	//channel name length, limit to dvr DSP ability, max 32 bytes [ͨ��������,dvr DSP�������ƣ����32�ֽ�]		
#define RV_N_ENCODE_AUX				3	//number of assist bit-stream [��չ��������]
#define RV_N_TALK					1	//max talk channel number [���Խ�ͨ������]
#define RV_N_COVERS					1	//number of shelter area [�ڵ��������]	
#define RV_N_CHANNEL				16	//max number of channel [���ͨ������]	
#define RV_N_ALARM_TSECT			2	//number of alarm prompt time slice [������ʾʱ��θ���]
#define RV_MAX_ALARMOUT_NUM			16	//upper limit of number of alarm-out interface [��������ڸ�������]
#define RV_MAX_VIDEO_IN_NUM			16	//upper limit of number of video input interface [��Ƶ����ڸ�������]
#define RV_MAX_ALARM_IN_NUM			16	//upper limit of number of alarm-in interface [��������ڸ�������]
#define RV_MAX_DISK_NUM				16	//upper limit of number of disk, be 16 now[Ӳ�̸������ޣ��ݶ�Ϊ16]
#define RV_MAX_DECODER_NUM			16	//upper limit of number of decoder(485) [��������485����������]	
#define RV_MAX_DECODER_NUM_EX		32	//upper limit of number of decoder [��������������]	
#define RV_MAX_232FUNCS				10	//upper limit of number of function of 232 serial port [232���ڹ��ܸ�������]
#define RV_MAX_232_NUM				2	//upper limit of number of 232 serial port [232���ڸ�������]
#define RV_MAX_DECPRO_LIST_SIZE		100	//upper limit of number of protocal of decoder [������Э���б��������]
#define RV_FTP_MAXDIRLEN			240	//max length of FTP file path [FTP�ļ�Ŀ¼��󳤶�]
#define RV_MATRIX_MAXOUT			16	//upper limit of number of matrix output interface [���������������]
#define RV_TOUR_GROUP_NUM			6	//upper limit of number of matrix output group [���������������]
#define RV_MAX_DDNS_NUM				10	//upper limit of number of ddns server supported by device [�豸֧�ֵ�ddns������������]
#define RV_MAX_SERVER_TYPE_LEN		32	//max length of ddns server type string [ddns���������� ����ַ�������]
#define RV_MAX_DOMAIN_NAME_LEN		256	//max length of ddns server domain [ddns���� ����ַ�������]
#define RV_MAX_DDNS_ALIAS_LEN		32	//max length of ddns server other name [ddns���������� ����ַ�������]
#define RV_MOTION_ROW				32	//row number of motion detect [��̬������������]
#define RV_MOTION_COL				32	//collumn number of moton detect [��̬������������]
#define	RV_FTP_USERNAME_LEN			64  //FTP configure : max size of user name [FTP���ã��û�����󳤶�]
#define	RV_FTP_PASSWORD_LEN			64  //FTP configure : max size of password [FTP���ã�������󳤶�]
#define	RV_TIME_SECTION				2	//FTP configure : max size of time slice per day [FTP���ã�ÿ��ʱ��θ���]
#define RV_FTP_MAX_PATH				240	//FTP configure : max size of file path name [FTP���ã��ļ�·������󳤶�]
#define RV_INTERVIDEO_UCOM_CHANID	32	//platform connection configure : U WANGTONG channel ID [ƽ̨�������ã�U��ͨͨ��ID]
#define RV_INTERVIDEO_UCOM_DEVID	32	//platform connection configure : U WANGTONG device ID [ƽ̨�������ã�U��ͨ�豸ID]
#define RV_INTERVIDEO_UCOM_REGPSW	16	//platform connection configure : U WANGTONG password of registration [ƽ̨�������ã�U��ͨע������]
#define RV_INTERVIDEO_UCOM_USERNAME	32	//platform connection configure : U WANGTONG user name [ƽ̨�������ã�U��ͨ�û���]
#define RV_INTERVIDEO_UCOM_USERPSW	32	//platform connection configure : U WANGTONG password [ƽ̨�������ã�U��ͨ����]
#define RV_INTERVIDEO_NSS_IP		32	//platform connection configure : ZHONGXINGLIWEI IP [ƽ̨�������ã�������άIP]
#define RV_INTERVIDEO_NSS_SERIAL	32	//platform connection configure : ZHONGXINGLIWEI serial [ƽ̨�������ã�������άserial]
#define RV_INTERVIDEO_NSS_USER		32	//platform connection configure : ZHONGXINGLIWEI user [ƽ̨�������ã�������άuser]
#define RV_INTERVIDEO_NSS_PWD		50	//platform connection configure : ZHONGXINGLIWEI password [ƽ̨�������ã�������άpassword]

#define RV_MAX_VIDEO_COVER_NUM		16	//max number of area shelter [�ڵ�����������]
#define RV_MAX_WATERMAKE_DATA		4096//max length of watermark picture data [ˮӡͼƬ������󳤶�]
#define RV_MAX_WATERMAKE_LETTER		128	//max length of watermark text [ˮӡ������󳤶�]
#define RV_MAX_WLANDEVICE_NUM		10	//max number of searched wireless device [����������������豸����]
#define RV_MAX_ALARM_NAME			64	//address length [��ַ����]
#define RV_MAX_REGISTER_SERVER_NUM	10	//number of auto-register sever [����ע�����������]
#define RV_SNIFFER_FRAMEID_NUM		6   //6 FRAME ID options [6��FRAME ID ѡ��]
#define RV_SNIFFER_CONTENT_NUM		4   //4 captured package content per FRAME [ÿ��FRAME��Ӧ��4��ץ������]
#define RV_MAX_PROTOCOL_NAME_LENGTH 20
#define RV_SNIFFER_GROUP_NUM		4   //4 groups capture package configure [4��ץ������]
#define MAX_PATH_STOR				240 //length of remnote folder [Զ��Ŀ¼�ĳ���]
#define MAX_HHCHANNELNAME_LEN		32	//digital channel name length [����ͨ�����Ƴ���]
#define RV_MAX_SAVIA_NUM			16	//max number of savia count [savia��Ŀ���ֵ]
#define RV_MAX_BLACK_IP_NUM			128	//max number of black ip [��������Ŀ���ֵ]
#define RV_MAX_WHITE_IP_NUM			128	//max number of white ip [��������Ŀ���ֵ]
#define RV_MAX_DECODER_CHAN_NUM		32	//max number of dcoder channel [������ͨ����Ŀ���ֵ]


//resolve list, be used to very bit-mask with resolve mask value [�ֱ����б�������ֱ�����������롢�����]
#define	RV_CAPTURE_SIZE_D1			0x00000001
#define RV_CAPTURE_SIZE_HD1			0x00000002
#define RV_CAPTURE_SIZE_BCIF		0x00000004
#define RV_CAPTURE_SIZE_CIF			0x00000008
#define RV_CAPTURE_SIZE_QCIF		0x00000010	
#define RV_CAPTURE_SIZE_VGA			0x00000020	
#define RV_CAPTURE_SIZE_QVGA		0x00000040
#define RV_CAPTURE_SIZE_SVCD		0x00000080
#define RV_CAPTURE_SIZE_QQVGA		0x00000100
#define RV_CAPTURE_SIZE_SVGA		0x00000200
#define RV_CAPTURE_SIZE_XVGA		0x00000400
#define RV_CAPTURE_SIZE_WXGA		0x00000800
#define RV_CAPTURE_SIZE_SXGA		0x00001000
#define RV_CAPTURE_SIZE_WSXGA		0x00002000   
#define RV_CAPTURE_SIZE_UXGA		0x00004000
#define RV_CAPTURE_SIZE_WUXGA       0x00008000

//attributes of PTZ [��̨�����б�]
//lowMask
#define PTZ_DIRECTION				0x00000001				//direction [/*!< ���� */]
#define PTZ_ZOOM					0x00000002	   			//zoom [/*!< �䱶 */]
#define PTZ_FOCUS					0x00000004				//focus [/*!< �۽� */]
#define PTZ_IRIS					0x00000008				//aperture [/*!< ��Ȧ */]
#define PTZ_ALARM					0x00000010				//alarm function [/*!< �������� */]
#define PTZ_LIGHT					0x00000020				//lamp [/*!< �ƹ� */]
#define PTZ_SETPRESET				0x00000040				//set preset [/*!< ����Ԥ�õ� */]
#define PTZ_CLEARPRESET				0x00000080				//clear preset [/*!< ���Ԥ�õ� */]
#define PTZ_GOTOPRESET				0x00000100				//move to preset [/*!< ת��Ԥ�õ� */]
#define PTZ_AUTOPANON				0x00000200				//horizontal start [/*!< ˮƽ��ʼ */]
#define PTZ_AUTOPANOFF				0x00000400				//horizontal stop [/*!< ˮƽ���� */]
#define PTZ_SETLIMIT				0x00000800				//set bound [/*!< ���ñ߽� */]
#define PTZ_AUTOSCANON				0x00001000				//auto scan start [/*!< �Զ�ɨ�迪ʼ */]
#define PTZ_AUTOSCANOFF				0x00002000				//auto scan stop [/*!< �Զ�ɨ�迪ֹͣ */]
#define PTZ_ADDTOUR					0x00004000				//add preset to tour [/*!< ����Ѳ���� */]
#define PTZ_DELETETOUR				0x00008000				//delete preset from tour [/*!< ɾ��Ѳ���� */]
#define PTZ_STARTTOUR				0x00010000				//start tour [/*!< ��ʼѲ�� */]
#define PTZ_STOPTOUR				0x00020000				//end tour [/*!< ����Ѳ�� */]
#define PTZ_CLEARTOUR				0x00040000				//clear tour [/*!< ɾ��Ѳ�� */]
#define PTZ_SETPATTERN				0x00080000				//set mode [/*!< ����ģʽ */]
#define PTZ_STARTPATTERN			0x00100000				//start mode [/*!< ��ʼģʽ */]
#define PTZ_STOPPATTERN				0x00200000				//stop mode [/*!< ֹͣģʽ */]
#define PTZ_CLEARPATTERN			0x00400000				//clear mode [/*!< ���ģʽ */]
#define PTZ_POSITION				0x00800000				//fast locate [/*!< ���ٶ�λ */]
#define PTZ_AUX						0x01000000				//assist switch [/*!< �������� */]
#define PTZ_MENU					0x02000000				//menu of PTZ cameral [/*!< ����˵� */]
#define PTZ_EXIT					0x04000000				//exit from menu of PTZ cameral [/*!< �˳�����˵� */]
#define PTZ_ENTER					0x08000000				//confirm [/*!< ȷ�� */]
#define PTZ_ESC						0x10000000				//cancel [/*!< ȡ�� */]
#define PTZ_MENUUPDOWN				0x20000000				//up and down menu [/*!< �˵����²��� */]
#define PTZ_MENULEFTRIGHT			0x40000000				//left and right operation of menu [/*!< �˵����Ҳ��� */]
#define PTZ_OPT_NUM					0x80000000				//number of operation [/*< �����ĸ��� */]

//hiMask
#define PTZ_DEV						0x00000001				//PTZ control [/*!< ��̨���� */]
#define PTZ_MATRIX					0x00000002				//matrix control [/*!< ������� */]

//code mode list, can be used to very bit-mask with code mode mask value [����ģʽ�б����������ģʽ��������롢�����]
#define RV_CAPTURE_COMP_DIVX_MPEG4	0x00000001
#define RV_CAPTURE_COMP_MS_MPEG4 	0x00000002
#define RV_CAPTURE_COMP_MPEG2		0x00000004
#define RV_CAPTURE_COMP_MPEG1		0x00000008
#define RV_CAPTURE_COMP_H263		0x00000010
#define RV_CAPTURE_COMP_MJPG		0x00000020
#define RV_CAPTURE_COMP_FCC_MPEG4	0x00000040
#define RV_CAPTURE_COMP_H264		0x00000080

//bit-stream control list [���������б�]
#define RV_CAPTURE_BRC_CBR			0
#define RV_CAPTURE_BRC_VBR			1
//#define RV_CAPTURE_BRC_MBR			2

//alarm linkage, be used to very bit-mask with linkage mask value [�������������������뱨������������������롢�����]
#define RV_ALARM_UPLOAD		0x00000001
#define RV_ALARM_RECORD		0x00000002
#define RV_ALARM_PTZ		0x00000004
#define RV_ALARM_MAIL		0x00000008
#define RV_ALARM_TOUR		0x00000010
#define RV_ALARM_TIP		0x00000020
#define RV_ALARM_OUT		0x00000040
#define RV_ALARM_FTP_UL		0x00000080
#define RV_ALARM_BEEP		0x00000100
#define RV_ALARM_VOICE		0x00000200
#define RV_ALARM_SNAP		0x00000400

//"restore default configure" mask, several value can or ["�ָ�Ĭ������"���룬������ÿ��û����]
#define RV_RESTORE_COMMON			0x00000001	//common configure [��ͨ����]
#define RV_RESTORE_CODING			0x00000002	//code configure [��������]
#define RV_RESTORE_VIDEO			0x00000004	//record configure [¼������]
#define RV_RESTORE_COMM				0x00000008	//serial port configure [��������]
#define RV_RESTORE_NETWORK			0x00000010	//network configure [��������]
#define RV_RESTORE_ALARM			0x00000020	//alarm configure [��������]
#define RV_RESTORE_VIDEODETECT		0x00000040	//video detect [��Ƶ���]
#define RV_RESTORE_PTZ				0x00000080	//PTZ control [��̨����]
#define RV_RESTORE_OUTPUTMODE		0x00000100	//output mode [���ģʽ]
#define RV_RESTORE_CHANNELNAME		0x00000200	//channel name [ͨ������]
#define RV_RESTORE_ALL				0x80000000	//all reset [ȫ������]


////////////////end of constant abount remote configure struct [end ofԶ�����ýṹ����س���]///////////////////////


/************************************************************************
** enum define [ö�ٶ���]
***********************************************************************/
//device type [�豸����]
enum NET_DEVICE_TYPE 
{
	NET_PRODUCT_NONE = 0,
	NET_DVR_NONREALTIME_MACE, //not real-time MACE [/*!< ��ʵʱMACE */]
	NET_DVR_NONREALTIME, //not real-time [/*!< ��ʵʱ */]
	NET_NVS_MPEG1, //network video server [/*!< ������Ƶ������ */]
	NET_DVR_MPEG1_2, //MPEG1 two channel recoder [/*!< MPEG1��·¼��� */]
	NET_DVR_MPEG1_8, //MPEG1 eight channel recoder [/*!< MPEG1��·¼��� */]
	NET_DVR_MPEG4_8, //MPEG4 eight channel recoder [/*!< MPEG4��·¼��� */]
	NET_DVR_MPEG4_16, //MPEG4 sixteen channel recoder [/*!< MPEG4ʮ��·¼��� */]
	NET_DVR_MPEG4_SX2, //LB serial recoder [/*!< LBϵ��¼��� */]
	NET_DVR_MEPG4_ST2, //GB serial recoder [/*!< GBϵ��¼��� */]
	NET_DVR_MEPG4_SH2, //HB serial recoder [/*!< HBϵ��¼��� */]
	NET_DVR_MPEG4_GBE, //GBE serial recoder [/*!< GBEϵ��¼��� */]
	NET_DVR_MPEG4_NVSII, //the II genaration of network vider server [/*!< II��������Ƶ������ */]
	NET_DVR_STD_NEW, //new standard configure protocal [/*!< �±�׼����Э�� */]
	NET_DVR_DDNS, //DDNS server [/*DDNS������*/]
	NET_DVR_ATM,  //ATM machine [/* ATM�� */]
	NET_NB_SERIAL, //the II genaration not real-time NB serial machine [/* ������ʵʱNBϵ�л��� */]
	NET_LN_SERIAL, //LN serial products [/* LNϵ�в�Ʒ */]
	NET_BAV_SERIAL, //BAV serial products [/* BAVϵ�в�Ʒ */]
	NET_SDIP_SERIAL, //SDIP serial products [/* SDIPϵ�в�Ʒ */]
	NET_IPC_SERIAL, //IPC serial products [/* IPCϵ�в�Ʒ */]
	NET_NVS_B,		//NVS B serial products [/* NVS Bϵ�� */]
	NET_NVS_C,		//NVS H serial products [/* NVS Hϵ�� */]
	NET_NVS_S,		//NVS S serial products [/* NVS Sϵ�� */]
	NET_NVS_E,		//NVS E serial products [/* NVS Eϵ�� */]
	NET_DVR_NEW_PROTOCOL //query device type form QueryDevState, format it as string [/*��QueryDevState�в�ѯ�豸����,���ַ�����ʽ*/]
};

#define DH_MAX_IPADDR_LEN			16			//max size of IP address string [IP��ַ�ַ�������]
#define DH_MACADDR_LEN				40			//max size of MAC address string [MAC��ַ�ַ�������]
#define DH_DEV_TYPE_LEN				32			//max size of device type string [�豸�����ַ�������]

//configure file type, for CLIENT_ExportConfigFile interface [�����ļ����ͣ���CLIENT_ExportConfigFile�ӿ�ʹ��]
typedef enum __DH_CONFIG_FILE_TYPE
{
	DH_CONFIGFILE_ALL = 0,						//all configure file [ȫ�������ļ�]
	DH_CONFIGFILE_LOCAL,						//local configure file [���������ļ�]
	DH_CONFIGFILE_NETWORK,						//network configure file [���������ļ�]
	DH_CONFIGFILE_USER,							//user configure file [�û������ļ�]
} DH_CONFIG_FILE_TYPE;

//corresponding CLIENT_SearchDevices interface [��ӦCLIENT_SearchDevices�ӿ�]
typedef struct 
{
	char				szIP[DH_MAX_IPADDR_LEN];		//IP [IP]
	int					nPort;							//port [�˿�]
	char				szSubmask[DH_MAX_IPADDR_LEN];	//sub net mask [��������]
	char				szGateway[DH_MAX_IPADDR_LEN];	//gateway [����]
	char				szMac[DH_MACADDR_LEN];			//MAC address [MAC��ַ]
	char				szDeviceType[DH_DEV_TYPE_LEN];	//device type [�豸����]
	BYTE				bReserved[32];					//reserved [�����ֽ�]
} DEVICE_NET_INFO;

//set params on logining [���õ���ʱ����ز���]
typedef struct  
{
	int					nWaittime;				//wait time-out time (unit:millisecond), 0 means default 500ms [�ȴ���ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��5000ms]
	int					nConnectTime;			//connect time-out time (unit:millisecond), 0 means default 1500ms [���ӳ�ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��1500ms]
	int					nConnectTryNum;			//try to connect times, 0 means 1 time [���ӳ��Դ�����Ϊ0Ĭ��1��]
	int					nSubConnectSpaceTime;	//wait time between sub connection (unit:millisecond), 0 means default 10ms [������֮��ĵȴ�ʱ��(����Ϊ��λ),Ϊ0Ĭ��10ms]
	int					nGetDevInfoTime;		//get device info time-out time (unit:millisecond), 0 means default 500ms [��ȡ�豸��Ϣ��ʱʱ�䣬Ϊ0Ĭ��500ms.]
	int					nConnectBufSize;		//buffer size per connection (unit:byte), 0 means default 250*1024 [ÿ�����ӽ������ݻ����С(�ֽ�Ϊ��λ)��Ϊ0Ĭ��250*1024]
	BYTE				bReserved[28];			//reserved [�����ֶ�]
} NET_PARAM;

//common PTZ control commands [ͨ����̨��������]
typedef enum _PTZ_ControlType
{
	RV_PTZ_UP_CONTROL = 0,			//up [��]
	RV_PTZ_DOWN_CONTROL,			//down [��]
	RV_PTZ_LEFT_CONTROL,			//left [��]
	RV_PTZ_RIGHT_CONTROL,			//right [��]
	RV_PTZ_ZOOM_ADD_CONTROL,		//zoom+ [�䱶+]
	RV_PTZ_ZOOM_DEC_CONTROL,		//zoom- [�䱶-]
	RV_PTZ_FOCUS_ADD_CONTROL,		//focus+ [����+]
	RV_PTZ_FOCUS_DEC_CONTROL,		//focus- [����-]
	RV_PTZ_APERTURE_ADD_CONTROL,	//aperture+ [��Ȧ+]
	RV_PTZ_APERTURE_DEC_CONTROL,    //aperture- [��Ȧ-]
	RV_PTZ_POINT_MOVE_CONTROL,      //move to preset [ת��Ԥ�õ�]
	RV_PTZ_POINT_SET_CONTROL,       //set [����]
	RV_PTZ_POINT_DEL_CONTROL,       //delete [ɾ��]
	RV_PTZ_POINT_LOOP_CONTROL,      //tour in presets [���Ѳ��]
	RV_PTZ_LAMP_CONTROL             //lamp and wiper [�ƹ���ˢ]
}RV_PTZ_ControlType;

//common PTZ control extended commands [��̨������չ����]
typedef enum _EXTPTZ_ControlType
{
	RV_EXTPTZ_LEFTTOP = 0X20,		//left-up [����]
	RV_EXTPTZ_RIGHTTOP ,			//right-up [����]
	RV_EXTPTZ_LEFTDOWN ,			//left-down [����]
	RV_EXTPTZ_RIGHTDOWN,			//right-down [����]
	RV_EXTPTZ_ADDTOLOOP,			//add preset to tour : tour : preset [����Ԥ�õ㵽Ѳ��	Ѳ����·	Ԥ�õ�ֵ]	
	RV_EXTPTZ_DELFROMLOOP,			//delete preset from tour : tour : preset [ɾ��Ѳ����Ԥ�õ�	Ѳ����·	Ԥ�õ�ֵ]	
	RV_EXTPTZ_CLOSELOOP,			//cleat tour : tour [���Ѳ��	Ѳ����·]
	RV_EXTPTZ_STARTPANCRUISE,		//start horizontal rotate [��ʼˮƽ��ת]			
	RV_EXTPTZ_STOPPANCRUISE,		//stop horizontal rotate [ֹͣˮƽ��ת]			
	RV_EXTPTZ_SETLEFTBORDER,		//set left bound [������߽�]			
	RV_EXTPTZ_SETRIGHTBORDER,		//set right bound [�����ұ߽�]			
	RV_EXTPTZ_STARTLINESCAN,		//start line scan [��ʼ��ɨ]			
	RV_EXTPTZ_CLOSELINESCAN,		//stop line scan [ֹͣ��ɨ]			
	RV_EXTPTZ_SETMODESTART,			//start set mode : mode [����ģʽ��ʼ	ģʽ��·]		
	RV_EXTPTZ_SETMODESTOP,			//stop set mode : mode [����ģʽ����	ģʽ��·]		
	RV_EXTPTZ_RUNMODE,				//run mode : mode [����ģʽ	ģʽ��·]		
	RV_EXTPTZ_STOPMODE,				//stop mode : mode [ֹͣģʽ	ģʽ��·]		
	RV_EXTPTZ_DELETEMODE,			//cleat mode : mode [���ģʽ	ģʽ��·]		
	RV_EXTPTZ_REVERSECOMM,			//overturn command [��ת����]			
	RV_EXTPTZ_FASTGOTO,				//fast locate : horizontal coordinate (8192) : vertical coordinate (8192) : zoom (4) [���ٶ�λ	ˮƽ����(8192)	��ֱ����(8192)	�䱶(4)]
	RV_EXTPTZ_AUXIOPEN,				//assist switch open : assist point [�������ؿ�	������]	
	RV_EXTPTZ_AUXICLOSE,			//assist switch close : assist point [�������ع�	������]
	RV_EXTPTZ_OPENMENU = 0X36,		//open menu of PTZ cameral [������˵�]
	RV_EXTPTZ_CLOSEMENU ,			//close menu [�رղ˵�]
	RV_EXTPTZ_MENUOK,				//confirm on menu [�˵�ȷ��]
	RV_EXTPTZ_MENUCANCEL,			//cancel on menu [�˵�ȡ��]
	RV_EXTPTZ_MENUUP,				//up on menu [�˵���]
	RV_EXTPTZ_MENUDOWN,				//down on menu [�˵���]
	RV_EXTPTZ_MENULEFT,				//left on menu [�˵���]
	RV_EXTPTZ_MENURIGHT,			//right on menu [�˵���]
	RV_EXTPTZ_ALARMHANDLE = 0x40,	//alarm linkage PTZ, param1:alarm-in channel, param2:alarm linkage type, 1-preset,2-line scan,3-tour, param3:linkage value, for example:preset number [����������̨ parm1:��������ͨ�� parm2:������������1-Ԥ�õ�2-��ɨ3-Ѳ�� parm3:����ֵ����Ԥ�õ��]
	RV_EXTPTZ_MATRIXSWITCH = 0x41,	//matrix switch, patam1:watcher number(video out number), param2:(video in number), param3:matrix number [�����л� parm1:��������(��Ƶ�����) parm2:(��Ƶ�����) parm3:�����]
	RV_EXTPTZ_LIGHTCONTROL,			//lamp controler [�ƹ������]
	RV_EXTPTZ_UP_TELE = 0x70,		//up + TELE, param1=speed(1-8), the same as next [�� + TELE��param1=�ٶȣ�1-8������ͬ]
	RV_EXTPTZ_DOWN_TELE,			//down + TELE [�� + TELE]
	RV_EXTPTZ_LEFT_TELE,			//left + TELE [�� + TELE]
	RV_EXTPTZ_RIGHT_TELE,			//right + TELE [�� + TELE]
	RV_EXTPTZ_LEFTUP_TELE,			//left-up + TELE [���� + TELE]
	RV_EXTPTZ_LEFTDOWN_TELE,		//left-down + TELE [���� + TELE]
	RV_EXTPTZ_TIGHTUP_TELE,			//right-up + TELE [���� + TELE]
	RV_EXTPTZ_RIGHTDOWN_TELE,		//right-down + TELE [���� + TELE]
	RV_EXTPTZ_UP_WIDE,				//up + WIDE,param1=speed(1-8), the same as next [�� + WIDE��param1=�ٶȣ�1-8������ͬ]
	RV_EXTPTZ_DOWN_WIDE,			//down + WIDE [�� + WIDE]
	RV_EXTPTZ_LEFT_WIDE,			//left + WIDE [�� + WIDE]
	RV_EXTPTZ_RIGHT_WIDE,			//right + WIDE [�� + WIDE]
	RV_EXTPTZ_LEFTUP_WIDE,			//left-up + WIDE [���� + WIDE]
	RV_EXTPTZ_LEFTDOWN_WIDE,		//left-down + WIDE [���� + WIDE]
	RV_EXTPTZ_TIGHTUP_WIDE,			//right-up + WIDE [���� + WIDE]
	RV_EXTPTZ_RIGHTDOWN_WIDE,		//right-down + WIDE [���� + WIDE]
	RV_EXTPTZ_TOTAL,				//max command value [�������ֵ]
	RV_EXTPTZ_RESET,				//reset [��λ]
}RV_EXTPTZ_ControlType;

//IO control command [IO��������]
typedef enum _IOTYPE
{
	RV_ALARMINPUT = 1,			//alarm input [��������]
	RV_ALARMOUTPUT = 2,			//alarm output [�������]

	RV_DECODER_ALARMOUT = 3,	//alarm decoder output [�������������]
	RV_WIRELESS_ALARMOUT =5,    //wireless alarm output [���߱������]
	RV_ALARM_TRIGGER_MODE = 7,
}RV_IOTYPE;

//params of extended interface for query log : log type [��ѯ��־��չ�ӿڲ������豸��־����]
typedef enum _RV_LOG_QUERY_TYPE
{
	DHLOG_ALL = 0,		//all log [������־]
	DHLOG_SYSTEM,		//system log [ϵͳ��־]
	DHLOG_CONFIG,		//configure log [������־]
	DHLOG_STORAGE,		//store log [�洢���]
	DHLOG_ALARM,		//alarm log [������־]
	DHLOG_RECORD,		//record log [¼�����]
	DHLOG_ACCOUNT,		//account log [�ʺ����]
	DHLOG_CLEAR,		//clear log [�����־]
	DHLOG_PLAYBACK		//replay log [�ط����]
}RV_LOG_QUERY_TYPE;

//log infomation struct returned - log type [���ص���־��Ϣ�ṹ�壭��־����]
typedef enum _RV_LOG_TYPE
{
	//system logs
	RV_LOG_REBOOT = 0x0000,
	RV_LOG_SHUT,
	//config logs
	RV_LOG_CONFSAVE = 0x0100,
	RV_LOG_CONFLOAD,
	//fs logs
	RV_LOG_FSERROR = 0x0200,   //error in file system [�ļ�ϵͳ����]
	RV_LOG_HDD_WERR,           //error in disk writing [Ӳ��д����]
	RV_LOG_HDD_RERR,           //error in disk reading[Ӳ�̶�����]
	RV_LOG_HDD_TYPE,           //set disk type [����Ӳ������]
	RV_LOG_HDD_FORMAT,         //format disk [��ʽ��Ӳ��]
	//alarm logs
	RV_LOG_ALM_IN = 0x0300,
	RV_LOG_ALM_END = 0x0302,
	RV_LOG_INFRAREDALM_IN = 0x03a0, //wireless alarm input [���߱�������]
	RV_LOG_INFRAREDALM_END,			//wireless alarm end [���߱�������]
	//record
	RV_LOG_MANUAL_RECORD = 0x0401,
	RV_LOG_CLOSED_RECORD,
	//user manager
	RV_LOG_LOGIN = 0x0500,
	RV_LOG_LOGOUT,
	RV_LOG_ADD_USER,
	RV_LOG_DELETE_USER,
	RV_LOG_MODIFY_USER,
	RV_LOG_ADD_GROUP,
	RV_LOG_DELETE_GROUP,
	RV_LOG_MODIFY_GROUP,
	//clear
	RV_LOG_CLEAR = 0x0600,
	RV_LOG_TYPE_NR = 7,
}RV_LOG_TYPE;

typedef enum _RV_RESET_TYPE
{	
	DEFAULT_CFG_GENERAL = 0,		
	DEFAULT_CFG_ENCODE,
	DEFAULT_CFG_RECORD,		
	DEFAULT_CFG_COMM,		
	DEFAULT_CFG_NET,		
	DEFAULT_CFG_ALARM = 5,		
	DEFAULT_CFG_DETECT,		
	DEFAULT_CFG_PTZ,		
	DEFAULT_CFG_AUT,		
	DEFAULT_CFG_CHANTITLE = 9,		
	DEFAULT_CFG_EXCEP,		
	DEFAULT_CFG_ALL = 31,		
	DEFAULT_CFG_END,		
}_RV_RESET_TYPE;

//log infomation struct returned by interface CLIENT_QueryLogEx - log type [�ӿ�CLIENT_QueryLogEx���ص���־��Ϣ�ṹ�壭��־����]
//condition:int nType = 1;param reserved = &nType. [������int nType = 1;����reserved = &nType.]
typedef enum _RV_NEWLOG_TYPE
{
	//system logs
	RV_NEWLOG_REBOOT	 = 0x0000,		//system reboot [ϵͳ����]
	RV_NEWLOG_SHUT,						//system shutdown [ϵͳ�ػ�]

	//config logs
	RV_NEWLOG_CONFSAVE = 0x0100,
	RV_NEWLOG_CONFLOAD,

	//fs logs
	RV_NEWLOG_FSERROR	 = 0x0200,		//error in file system [�ļ�ϵͳ����]
	RV_NEWLOG_HDD_WERR,					//error in disk writing [Ӳ��д����]
	RV_NEWLOG_HDD_RERR,					//error in disk reading [Ӳ�̶�����]
	RV_NEWLOG_HDD_TYPE,					//set disk type [����Ӳ������]
	RV_NEWLOG_HDD_FORMAT,				//format disk [��ʽ��Ӳ��]
	RV_NEWLOG_HDD_NOSPACE,				//current work space not enough [��ǰ�����̿ռ䲻��]

	//alarm logs
	RV_NEWLOG_ALM_IN	 = 0x0300,
	RV_NEWLOG_NETALM_IN,
	RV_NEWLOG_ALM_END,
	RV_NEWLOG_LOSS_IN,
	RV_NEWLOG_LOSS_END,

	//record
	RV_NEWLOG_AUTOMATIC_RECORD = 0x0400,
	RV_NEWLOG_MANUAL_RECORD,
	RV_NEWLOG_CLOSED_RECORD,

	//user manager
	RV_NEWLOG_LOGIN    = 0x0500,
	RV_NEWLOG_LOGOUT,
	RV_NEWLOG_ADD_USER,
	RV_NEWLOG_DELETE_USER,
	RV_NEWLOG_MODIFY_USER,
	RV_NEWLOG_ADD_GROUP,
	RV_NEWLOG_DELETE_GROUP,
	RV_NEWLOG_MODIFY_GROUP,

	//clear
	RV_NEWLOG_CLEAR    = 0x0600,
	RV_NEWLOG_SEARCHLOG,				//query log [��ѯ��־]

	//record operation
	RV_NEWLOG_SEARCH	 = 0x0700,		//record query [¼���ѯ]
	RV_NEWLOG_DOWNLOAD,					//record download [¼������]
	RV_NEWLOG_PLAYBACK,					//record replay [¼��ط�]
	RV_NEWLOG_BACKUP,					//backup record file [/*!< ����¼���ļ� */]
	RV_NEWLOG_BACKUPERROR,				//backup record file fail [/*!< ����¼���ļ�ʧ�� */]

	RV_NEWLOG_TYPE_NR = 8,		
}RV_NEWLOG_TYPE;


//added params of extended interface for real-time preview : preview type [ʵʱԤ����չ�ӿ����ӵĲ�����Ԥ������]
typedef enum _RealPlayType
{
	RV_RType_Realplay = 0,	//real-time preview [ʵʱԤ��]
	RV_RType_Multiplay,		//multi-views preview [�໭��Ԥ��]

	RV_RType_Realplay_0,	//real-time watch - main stream, the same as RV_RType_Realplay [ʵʱ����-����������ͬ��RV_RType_Realplay]
	RV_RType_Realplay_1,	//real-time watch - assist stream1 [ʵʱ����-������1]
	RV_RType_Realplay_2,	//real-time watch - assist stream2 [ʵʱ����-������2]
	RV_RType_Realplay_3,	//real-time watch - assist stream3 [ʵʱ����-������3]

	RV_RType_Multiplay_1,	//multi-views preview : 1 view[�໭��Ԥ����1����]
	RV_RType_Multiplay_4,	//multi-views preview : 4 view[�໭��Ԥ����4����]
	RV_RType_Multiplay_8,	//multi-views preview : 8 view[�໭��Ԥ����8����]
	RV_RType_Multiplay_9,	//multi-views preview : 6 view[�໭��Ԥ����9����]
	RV_RType_Multiplay_16,	//multi-views preview : 16 view[�໭��Ԥ����16����]

	RV_RType_Multiplay_6,	//multi-views preview : 6 view[�໭��Ԥ����6����]
	RV_RType_Multiplay_12,	//multi-views preview : 12 view[�໭��Ԥ����12����]
} RV_RealPlayType;

//params of interface for device control : control type define [�豸���ƽӿڲ������������Ͷ���]
typedef enum _CtrlType
{
	RV_CTRL_REBOOT = 0,	//reboot device [�����豸]
	RV_CTRL_SHUTDOWN,	//shutdown device [�ر��豸]
	RV_CTRL_DISK,		//disk manage [Ӳ�̹���]
	//network key-board [�������]
	RV_KEYBOARD_POWER = 3,
	RV_KEYBOARD_ENTER,
	RV_KEYBOARD_ESC,
	RV_KEYBOARD_UP,
	RV_KEYBOARD_DOWN,
	RV_KEYBOARD_LEFT,
	RV_KEYBOARD_RIGHT,
	RV_KEYBOARD_BTN0,
	RV_KEYBOARD_BTN1,
	RV_KEYBOARD_BTN2,
	RV_KEYBOARD_BTN3,
	RV_KEYBOARD_BTN4,
	RV_KEYBOARD_BTN5,
	RV_KEYBOARD_BTN6,
	RV_KEYBOARD_BTN7,
	RV_KEYBOARD_BTN8,
	RV_KEYBOARD_BTN9,
	RV_KEYBOARD_BTN10,
	RV_KEYBOARD_BTN11,
	RV_KEYBOARD_BTN12,
	RV_KEYBOARD_BTN13,
	RV_KEYBOARD_BTN14,
	RV_KEYBOARD_BTN15,
	RV_KEYBOARD_BTN16,
	RV_KEYBOARD_SPLIT,
	RV_KEYBOARD_ONE,
	RV_KEYBOARD_NINE,
	RV_KEYBOARD_ADDR,
	RV_KEYBOARD_INFO,
	RV_KEYBOARD_REC,
	RV_KEYBOARD_FN1,
	RV_KEYBOARD_FN2,
	RV_KEYBOARD_PLAY,
	RV_KEYBOARD_STOP,
	RV_KEYBOARD_SLOW,
	RV_KEYBOARD_FAST,
	RV_KEYBOARD_PREW,
	RV_KEYBOARD_NEXT,
	RV_KEYBOARD_JMPDOWN,
	RV_KEYBOARD_JMPUP,
	//trigger alarm [��������]
	RV_TRIGGER_ALARM_IN = 100,
	RV_TRIGGER_ALARM_OUT,
	//matrix control [�������]
	RV_CTRL_MATRIX,
	//SD card control(ipc products), params are same as disk control [SD�����ƣ�ipc��Ʒ������ͬӲ�̿���]
	RV_CTRL_SDCARD,
	//imprinting control [��¼������]
	RV_BURNING_START,		//start imprinting [��ʼ��¼]
	RV_BURNING_STOP,		//stop imprinting [������¼]

	RV_BURNING_ADDPWD,	//overprint password (string end with 0, max size 8 bytes) [��������(��0Ϊ��β���ַ���,��󳤶�8λ)]
	RV_BURNING_ADDHEAD,	//overprint head leader (string end with 0, max size 1024 bytes, support multi-lines, line seperator is '\n') [����Ƭͷ(��0Ϊ��β���ַ���,��󳤶�1024�ֽ�,֧�ַ���,�зָ���'\n')��]
	RV_BURNING_ADDSIGN,	//overprint dot to imprinting (no params) [���Ӵ�㵽��¼��Ϣ(������)]
	RV_BURNING_ADDCURSTOMINFO,	//self define overprint (string end with 0, max size 1024 bytes, support multi-lines, line seperator is '\n') [�Զ������(��0Ϊ��β���ַ���,��󳤶�1024�ֽ�,֧�ַ���,�зָ���'\n')]

	//restore device's efault configure [�ָ��豸��Ĭ������]
	RV_CTRL_RESTOREDEFAULT,

	//device tigger DSP snapshot [�豸����DSPץͼ]
	RV_CTRL_CAPTURE_START,		//trigger device snapshot [�����豸ץͼ]

	//cleat log [�����־]
	RV_CTRL_CLEARLOG,
	//wireless alarm [���߱���]
	RV_TRIGGER_ALARM_WIRELESS = 200,
}CtrlType;

//configure type, the interface which using this enum has been die out, not use please [�������ͣ�Ŀǰʹ�ø�ö�ٵĽӿ�����̭���벻Ҫʹ��]
typedef enum _CFG_INDEX
{
	CFG_GENERAL =  0,		//common [��ͨ]
	CFG_COMM   		,		//serial port [����]
	CFG_NET    		,		//network [����]
	CFG_RECORD 		,		//record [¼��]
	CFG_CAPTURE		,		//picture configure [ͼ������]
	CFG_PTZ    		,		//PTZ [��̨]
	CFG_DETECT 		,		//motion detect [��̬���]
	CFG_ALARM  		,		//alarm [����]
	CFG_DISPLAY		,		//display [��ʾ]
	CFG_RESERVED	,		//reserved,  for continuity [������ʹ��������]
	CFG_TITLE  		=10,	//channel title [ͨ������]
	CFG_MAIL  		=11,	//emial function [�ʼ�����]
	CFG_EXCAPTURE	=12,	//preview picture configure [Ԥ��ͼ������]
	CFG_PPPOE		=13,	//pppoe configure [pppoe����]
	CFG_DDNS		=14,	//DDNS configure [DDNS����]
	CFG_SNIFFER		=15,	//network watch capture configure [������Ӳ�������]
	CFG_DSPINFO		=16,	//code ability infomation [����������Ϣ]
	CFG_COLOR		=126,	//color cofigure infomation [��ɫ������Ϣ]
	CFG_ALL,				//reserved [����]
} CFG_INDEX;

typedef enum _SNAP_TYPE
{
	SNAP_TYP_TIMING = 0,
	SNAP_TYP_ALARM,
	SNAP_TYP_NUM,
} SNAP_TYPE;

//resolve enum, for RV_DSP_ENCODECAP using [�ֱ���ö�٣���RV_DSP_ENCODECAPʹ��]
typedef enum _CAPTURE_SIZE
{
	CAPTURE_SIZE_D1,				// <  720*576(PAL)  720*480(NTSC)
	CAPTURE_SIZE_HD1,				// <  352*576(PAL)  352*480(NTSC)
	CAPTURE_SIZE_BCIF,				// <  720*288(PAL)  720*240(NTSC)
	CAPTURE_SIZE_CIF,				// <  352*288(PAL)  352*240(NTSC)
	CAPTURE_SIZE_QCIF,				// <  176*144(PAL)  176*120(NTSC)
	CAPTURE_SIZE_VGA,				// <  640*480
	CAPTURE_SIZE_QVGA,				// <  320*240
	CAPTURE_SIZE_SVCD,				// <  480*480
	CAPTURE_SIZE_QQVGA,				// <  160*128
	CAPTURE_SIZE_720P	= 9,		//	1280*720	720P
	CAPTURE_SIZE_1080P	= 10,		//	1920*1080	1080P
	CAPTURE_SIZE_SVGA,				// <  800*592
	CAPTURE_SIZE_XVGA,				// <  1024*768	VGA input code, 2800 serial device need [VGA������룬2800��Ҫ]
	CAPTURE_SIZE_WXGA,				// <  1280*800
	CAPTURE_SIZE_SXGA,				// <  1280*1024  
	CAPTURE_SIZE_WSXGA,				// <  1600*1024  
	CAPTURE_SIZE_UXGA,				// <  1600*1200
	CAPTURE_SIZE_WUXGA,				// <  1920*1200
	CAPTURE_SIZE_NR  
} CAPTURE_SIZE;

typedef enum __EM_USEDEV_MODE
{
	RV_TALK_CLIENT_MODE,		//set the type of client to start talk [���ÿͻ��˷�ʽ���������Խ�]
	RV_TALK_SERVER_MODE,		//set the type of server to start talk [���÷�������ʽ���������Խ�]
	RV_TALK_ENCODE_TYPE,		//set the code format of audio talk [���������Խ������ʽ]
	RV_ALARM_LISTEN_MODE        //set the type of alarm information subscibe [���ñ������ķ�ʽ]

} EM_USEDEV_MODE;

typedef enum __EM_UPGRADE_TYPE
{
	RV_UPGRADE_BIOS_TYPE=1,		//BIOS upgrade [BIOS����]
	RV_UPGRADE_WEB_TYPE,		//WEB upgrade [WEB����]
	RV_UPGRADE_BOOT_YPE,		//BOOT upgrade [BOOT����]
	RV_UPGRADE_CHARACTER_TYPE,	//the library of Chinese characters [���ֿ�]
	RV_UPGRADE_LOGO_TYPE,		//LOGO
	RV_UPGRADE_EXE_TYPE,		//EXE eg. player etc... [EXE ���粥������]
} EM_UPGRADE_TYPE;

//types of language [��������]
typedef enum __LANGUAGE_TYPE
{
	RV_LANGUAGE_ENGLISH,				//English [Ӣ��]	
	RV_LANGUAGE_CHINESE_SIMPLIFIED,		//Simplified Chinese [��������]	
	RV_LANGUAGE_CHINESE_TRADITIONAL,	//Chinese-traditional [��������]	
	RV_LANGUAGE_ITALIAN,				//Italian [�������]	
	RV_LANGUAGE_SPANISH,				//Spanish [��������]
	RV_LANGUAGE_JAPANESE,				//Japanese [���İ�]	
	RV_LANGUAGE_RUSSIAN,				//Russian [���İ�]		
	RV_LANGUAGE_FRENCH,					//French [���İ�]		
	RV_LANGUAGE_GERMAN, 				//German [���İ�]		
	RV_LANGUAGE_PORTUGUESE,				//Portuguese [��������]	
	RV_LANGUAGE_TURKEY,					//Turkey [��������]	
	RV_LANGUAGE_POLISH,					//Polish [������]	
	RV_LANGUAGE_ROMANIAN,				//Romanian [��������]	
	RV_LANGUAGE_HUNGARIAN,              //Hungarian [��������]	
	RV_LANGUAGE_FINNISH,				//Finnish [������]	
	RV_LANGUAGE_ESTONIAN,				//Estonian [��ɳ������]	
	RV_LANGUAGE_KOREAN,					//Korean [����]	
	RV_LANGUAGE_FARSI,					//Bosnian [��˹��]	
	RV_LANGUAGE_DANSK,					//Denish [������]
	RV_LANGUAGE_CZECHISH,				//Czech [�ݿ���]
	RV_LANGUAGE_BULGARIA,				//Bulgarian [����������]
} RV_LANGUAGE_TYPE;

//audio data format of audio talk [�����Խ���ʽ]
typedef enum __TALK_CODING_TYPE
{
	RV_TALK_DEFAULT = 0,
	RV_TALK_PCM = 1,					//PCM
	RV_TALK_G711a,						//G711a
	RV_TALK_AMR,						//AMR
	RV_TALK_G711u,						//G711u
	RV_TALK_G726,						//G726
}RV_TALK_CODING_TYPE;

/************************************************************************
** definition of struct [�ṹ�嶨��]
***********************************************************************/
typedef struct
{	
	BOOL	bEnable;
	int		dwWebPort;
	int		dwTCPPort;
	DWORD	dwReserved;	
}NET_UPNP;

//time [ʱ��]
typedef struct 
{
	DWORD dwYear;		//year [��]
	DWORD dwMonth;		//month [��]
	DWORD dwDay;		//day [��]
	DWORD dwHour;		//hour [ʱ]
	DWORD dwMinute;		//minute [��]
	DWORD dwSecond;		//second [��]
} NET_TIME,*LPNET_TIME;

//information of device [�豸��Ϣ]
typedef struct {
	BYTE sSerialNumber[RV_SERIALNO_LEN];	//serial number [���к�]
	BYTE byAlarmInPortNum;					//alarm input number of DVR [DVR�����������]
	BYTE byAlarmOutPortNum;					//alarm output number of DVR [DVR�����������]
	BYTE byDiskNum;							//disk number of DVR [DVR Ӳ�̸���]
	BYTE byDVRType;							//DVR type, reference to enum DHDEV_DEVICE_TYPE [DVR����, ��ö��DHDEV_DEVICE_TYPE]
	BYTE byChanNum;							//channel number of DVR [DVR ͨ������]
} NET_DEVICEINFO, *LPNET_DEVICEINFO;

//common alarm information [��ͨ������Ϣ]
typedef struct {
	int channelcount;
	int alarminputcount;
	unsigned char alarm[16];			//out alarm [�ⲿ����]
	unsigned char motiondection[16];	//motion detect [��̬���]
	unsigned char videolost[16];		//video lost [��Ƶ��ʧ]
} NET_CLIENT_STATE;

//query disk information of device in working state [��ѯ�豸����״̬Ӳ����Ϣ]
typedef struct {
	DWORD		dwVolume;		//space of disk [Ӳ�̵�����]
	DWORD		dwFreeSpace;	//left space of disk [Ӳ�̵�ʣ��ռ�]
	BYTE		dwStatus;		//state of disk, 0-dormancy, 1-activity, 2-error; seperate DWORD to 4 parts [Ӳ�̵�״̬,0-����,1-�,2-���ϵȣ���DWORD����ĸ�BYTE]
	BYTE		bDiskNum;		//disk index [Ӳ�̺�]
	BYTE		bSubareaNum;	//partion index [������]
	BYTE		bSignal;		//flag, 0-local, 1-remote [��ʶ��0Ϊ���� 1ΪԶ��]
}NET_DEV_DISKSTATE,*LPNET_DEV_DISKSTATE;

//query disk type of device [��ѯ�豸Ӳ������]
typedef struct {
	int Type[32];
}NET_DEV_DISKTYPE;

//information of record file [¼���ļ���Ϣ]
typedef struct {
	unsigned int     ch;              //channel index [ͨ����]
	char             filename[128];   //file name [�ļ���]
	unsigned int     size;            //file length [�ļ�����]
	NET_TIME         starttime;       //start time [��ʼʱ��]
	NET_TIME         endtime;         //end time [����ʱ��]
	unsigned int     driveno;         //disk index [���̺�]
	unsigned int     startcluster;    //start cluster index [��ʼ�غ�]
	int				 nRecordFileType; //record file type, 0-common record; 1-alarm record; 2-motion detect; 3-record for card [¼���ļ�����  0����ͨ¼��1������¼��2���ƶ���⣻3������¼��]
} NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;

//record file information [¼���ļ���Ϣ]
typedef struct {
	unsigned int     ch;              //channel index [ͨ����]
	char             filename[128];   //file name [�ļ���]
	unsigned int     size;            //file length [�ļ�����]
	NET_TIME         starttime;       //start time [��ʼʱ��]
	NET_TIME         endtime;         //end time [����ʱ��]
	unsigned int     driveno;         //disk index [���̺�]
	unsigned int     startcluster;    //start cluster index [��ʼ�غ�]
	int				 nRecordFileType; //record file type, 0-common record; 1-alarm record; 2-motion detect; 3-record for card [¼���ļ�����  0����ͨ¼��1������¼��2���ƶ���⣻3������¼��]
	unsigned int	 partno;		  //partion index [������]
	unsigned int	 hint;			  
} NET_RECORDFILE_INFO_EX, *LPNET_RECORDFILE_INFO_EX;

//alarm IO control [����IO����]
typedef struct 
{
	unsigned short index;	//port index [�˿����]
	unsigned short state;	//port state [�˿�״̬]
}ALARM_CONTROL;


typedef struct
{
	unsigned short		index;					//port index [�˿����]
	unsigned short		mode;					//port mode [�˿�ģʽ]
	BYTE				bReserved[28];			
} TRIGGER_MODE_CONTROL;

typedef struct 
{
	int	decoderNo;					//alarming decoder index, start with 0 [������������,��0��ʼ]
	unsigned short  alarmChn;		//alarming output channel, start with 0 [���������,��0��ʼ]
	unsigned short  alarmState;		//alarming output state, 1-opened, 0-closed [�������״̬,1-�򿪡�0-�ر�]
}DECODER_ALARM_CONTROL;

///////////////////structs of user account management [�û��ʺŹ�����ؽṹ��]/////////////////////////////////
typedef struct _OPR_RIGHT
{
	DWORD		dwID;
	char		name[RV_RIGHT_NAME_LENGTH];
	char		memo[RV_MEMO_LENGTH];
}OPR_RIGHT;

typedef struct _USER_INFO
{
	DWORD		dwID;
	DWORD		dwGroupID;
	char		name[RV_USER_NAME_LENGTH];
	char		passWord[RV_USER_PSW_LENGTH];
	DWORD		dwRightNum;
	DWORD		rights[RV_MAX_RIGHT_NUM];
	char		memo[RV_MEMO_LENGTH];
	DWORD		dwReusable;		//if this account can be used duplicated, 1-allow, 0-forbid [���û��Ƿ������� 1-���ã�0-������]

}USER_INFO;

typedef struct _USER_GROUP_INFO
{
	DWORD		dwID;
	char		name[RV_USER_NAME_LENGTH];
	DWORD		dwRightNum;
	DWORD		rights[RV_MAX_RIGHT_NUM];
	char		memo[RV_MEMO_LENGTH];
}USER_GROUP_INFO;

//struct of user information configure [�û���Ϣ���ýṹ]
typedef struct _USER_MANAGE_INFO
{
	DWORD				dwRightNum;
	OPR_RIGHT			rightList[RV_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;
	USER_GROUP_INFO		groupList[RV_MAX_GROUP_NUM];
	DWORD				dwUserNum;
	USER_INFO			userList[RV_MAX_USER_NUM];
	DWORD				dwSpecial; //special information, 1-support account be used duplicated, 1-not support account be used duplicated [������Ϣ�� 1-֧���û����ã���0-��֧���û�����]
}USER_MANAGE_INFO;

//////////////////////////////////////////////////////////////////////////////
///////////////////extened structs of user account management [�û��ʺŹ�����չ��ؽṹ��]/////////////////////////////////
#define RV_USER_NAME_LENGTH_EX  16  //user name length [�û�������]
#define RV_USER_PSW_LENGTH_EX   16  //password length [����]
typedef struct _OPR_RIGHT_EX
{
	DWORD  dwID;
	char  name[RV_RIGHT_NAME_LENGTH];
	char  memo[RV_MEMO_LENGTH];
}OPR_RIGHT_EX;

typedef struct _USER_INFO_EX
{
	DWORD  dwID;
	DWORD  dwGroupID;
	char  name[RV_USER_NAME_LENGTH_EX];
	char  passWord[RV_USER_PSW_LENGTH_EX];
	DWORD  dwRightNum;
	DWORD  rights[RV_MAX_RIGHT_NUM];
	char  memo[RV_MEMO_LENGTH];
	DWORD   dwFouctionMask;//mask code [����]

	/* mask code, include [����,����]
	* 0x00000001 - support account be used duplicated [֧���û�����]
	*/

	BYTE  byReserve[32];

}USER_INFO_EX;

typedef struct _USER_GROUP_INFO_EX
{
	DWORD  dwID;
	char  name[RV_USER_NAME_LENGTH_EX];
	DWORD  dwRightNum;
	DWORD  rights[RV_MAX_RIGHT_NUM];
	char  memo[RV_MEMO_LENGTH];
}USER_GROUP_INFO_EX;

//struct user information configure [�û���Ϣ���ýṹ]
typedef struct _USER_MANAGE_INFO_EX
{

	DWORD				dwRightNum;
	OPR_RIGHT_EX		rightList[RV_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;
	USER_GROUP_INFO_EX  groupList[RV_MAX_GROUP_NUM];
	DWORD				dwUserNum;
	USER_INFO_EX		userList[RV_MAX_USER_NUM];
	DWORD				dwFouctionMask;//mask code [����]    
	/* mask code, include [����,����]
	* 0x00000001 - support account be used dupliceted [֧���û�����]
	* 0x00000002 - password modify need verify [�����޸���ҪУ��]
	*/
	BYTE  byNameMaxLength;			//max length of user name supported [֧���û�������󳤶�]
	BYTE  byPSWMaxLength;			//max length of password supported [֧�ֵ�������󳤶�]
	BYTE  byReserve[254];
}USER_MANAGE_INFO_EX;
///////////////////end of extened structs of user account management [end of �û��ʺŹ�����չ��ؽṹ��]////////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////structs of log [��־�ṹ�����]///////////////////////////
//struct of log time [��־ʱ��ṹ]
typedef struct _DHDEVTIME
{
	DWORD second		:6;					//second 1-60 [�� 1-60]		
	DWORD minute		:6;					//minute 1-60 [�� 1-60]		
	DWORD hour			:5;					//hour 1-24	[ʱ 1-24]		
	DWORD day			:5;					//day 1-31 [�� 1-31]		
	DWORD month			:4;					//month 1-12 [�� 1-12]		
	DWORD year			:6;					//year 2000-2063 [�� 2000-2063]	
}DHDEVTIME, *LPDHDEVTIME;

typedef struct _RV_LOG_ITEM
{
	DHDEVTIME time;					//date [����]
	unsigned short type;			//type [����]
	unsigned char reserved;			//reserved [����]
	unsigned char data;				//data [����]
	unsigned char context[8];		//content [����]
}RV_LOG_ITEM, *LPRV_LOG_ITEM;

//log information structs returned by interface CLIENT_QueryLogEx [�ӿ�CLIENT_QueryLogEx���ص���־��Ϣ�ṹ��]
//situation : int nType = 1; param : reserved = &nType. [������int nType = 1;����reserved = &nType.]
typedef struct _RV_NEWLOG_ITEM
{
	DHDEVTIME	time; 				//date [����]
	WORD	type;					//type [����]
	WORD	data;					//data [����]
	char  	szOperator[8]; 			//user name [�û���]
	BYTE	context[16];		    //content [����]	
}RV_NEWLOG_ITEM, *LPRV_NEWLOG_ITEM;

typedef struct _LOG_ITEM_RECORD
{
	DHDEVTIME	time;		//time [ʱ��]
	BYTE	channel;		//channel [ͨ��]
	BYTE	type;			//record type [¼������]
	BYTE	reserved[2];
}LOG_ITEM_RECORD, *LPLOG_ITEM_RECORD;
////////////////////end of structs of log [end of ��־�ṹ�����]///////////////////////////

//frame param struct on video data fram callback [�ص���Ƶ����֡��֡�����ṹ��]
typedef struct _tagVideoFrameParam
{
	BYTE encode;		//code type [��������]
	BYTE frametype;		//I = 0, P = 1, B = 2...
	BYTE format;		//PAL - 0, NTSC - 1
	BYTE size;			//CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
						//SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15,
	DWORD fourcc;		//if H264 code is always 0, MPEG4 here always fill with FOURCC('X','V','I','D'); [�����H264��������Ϊ0��MPEG4����������дFOURCC('X','V','I','D');]
	DWORD reserved;		//reserved [����]
	NET_TIME struTime;	//time information [ʱ����Ϣ]
}tagVideoFrameParam;

//frame param struct on audio data frame callback [�ص���Ƶ����֡��֡�����ṹ��]
typedef struct _tagCBPCMDataParam
{
	BYTE channels;		//audio channel number [������]
	BYTE samples;		//sample 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000 [���� 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000]
	BYTE depth;			//sample depth, 8 or 16, directly show [������� ȡֵ8����16�ȡ�ֱ�ӱ�ʾ]
	BYTE param1;		//0-indicate no symbol, 1-indicate has symbol [0 - ָʾ�޷��ţ�1-ָʾ�з���]
	DWORD reserved;		//reserved [����]
}tagCBPCMDataParam;

//data struct for channel picture title overprinting [ͨ��������Ļ���ӵ����ݽṹ]
typedef struct _RV_CHANNEL_OSDSTRING
{
	BOOL bEnable;												//enable [ʹ��]
	DWORD dwPosition[MAX_STRING_LINE_LEN];						//position of every character line, use 1-9, corresponding to little key-board position [�����ַ���λ�á���1-9������ʾ����С����λ�ö�Ӧ]
																//7 left-up		8 up		9 right-up		[7����	8��		9����]
																//4 left		5 middle	6 right			[4��	5��		6��]
																//1 left-down	2 down		3 right-down	[1����	2��		3����]
	char szStrings[MAX_STRING_LINE_LEN][MAX_PER_STRING_LEN];	//max 6 character lines, max 20 bytes per line [��������ַ���ÿ�����20���ֽ�]
}RV_CHANNEL_OSDSTRING;

////////////////////control param definition for device control interface [�豸���ƽӿڵĿ��Ʋ�������]//////////////////////
typedef struct _DISKCTRL_PARAM
{
	DWORD dwSize;		//size of this structure, for version control
	int nIndex;			//index of stDisks array of disk information struct RV_HARDDISK_STATE, start with 0 [ΪӲ����Ϣ�ṹ��RV_HARDDISK_STATE�������stDisks�±꣬��0��ʼ]
	int ctrlType;		//control type.
						//0-clear data, 1-set read-write disk, 2-set read-only disk [0 - �������,	1 - ��Ϊ��д��, 2 - ��Ϊֻ����]
						//3-set redundancy disk, 4-error restore, 5-set snapshot disk [3 - ��Ϊ������, 4 - �ָ�����,	5 - ��Ϊ������]
}DISKCTRL_PARAM;

typedef struct _ALARMCTRL_PARAM
{
	DWORD dwSize;
	int nAlarmNo;		//alarm channel index, start with 0 [����ͨ���ţ���0��ʼ]
	int nAction;		//0-triggrt to alarm, 1-stop alarm [0-����������1-ֹͣ����]
}ALARMCTRL_PARAM;

typedef struct _MATRIXCTRL_PARAM
{
	DWORD dwSize;
	int nChannelNo;		//video input index, start with 0 [��Ƶ����ţ���0��ʼ]
	int nMatrixNo;		//matrix output index, start with 0 [��������ţ���0��ʼ]
}MATRIXCTRL_PARAM;

typedef struct _BURNING_PARM
{
	int channelMask;	//channel index mask, flag one channel per bit [ͨ�������룬ÿλ��ʾһ��ͨ��]
	int	devMask;		//device mask, flag one device per bit [�豸���룬ÿλ��ʾһ̨�豸]
}BURNNG_PARM;

////////////////////end of control param definition for device control interface [end of�豸���ƽӿڵĿ��Ʋ�������]//////////////////////

////////////////////params definition of query device state [��ѯ�豸״̬�Ĳ�������]////////////////////////////////
typedef struct _RV_HARDDISK_STATE
{
	DWORD	dwDiskNum;								//number [����]
	NET_DEV_DISKSTATE	stDisks[RV_MAX_DISKNUM];	//every disk or partion information [��Ӳ�̻������Ϣ]
}RV_HARDDISK_STATE,*LPRV_HARDDISK_STATE;

typedef RV_HARDDISK_STATE  RV_SDCARD_STATE;	//SD card, data struct is the same as disk information [SD�������ݽṹͬӲ����Ϣ]

typedef struct _NET_DEV_BURNING
{
	DWORD dwDriverType;							//imprinting driver type, 0-DHFS, 1-DISK, 2-CDRW [��¼���������� 0 -	DHFS, 1 - DISK, 2- CDRW]
	DWORD dwBusType;							//bus type, 0-USB, 1-1394, 2-IDE [�������͡�0- USB, 1-1394, 2-IDE]
	DWORD dwTotalSpace;							//total space(KB) [������(KB)]
	DWORD dwRemainSpace;						//left space(KB) [ʣ������(KB)]
	BYTE  dwDriverName[RV_BURNING_DEV_NAMELEN]; //imprinting driver name [��¼����������]
}NET_DEV_BURNING,*LPNET_DEV_BURNING;

typedef struct _RV_BURNING_DEVINFO
{
	DWORD	dwDevNum;								//imprinting device number [��¼�豸����]
	NET_DEV_BURNING	stDevs[RV_MAX_BURNING_DEV_NUM]; //every imprinting device information [����¼�豸��Ϣ]
}RV_BURNING_DEVINFO, *LPRV_BURNING_DEVINFO;

typedef struct _RV_BURNING_PROGRESS
{
	BYTE	bBurning;		//old impriting means if it is imprintinging now [�ɿ�¼����ʾ�Ƿ����ڿ�¼]
	/*
	* new imprinting values : [�¿�¼����ֵ��]
	*0; can imprinting [0;   ���Կ�¼]
	*1; not CD device, device type incorrect [1;   �ǹ����豸,�豸���Ͳ���ȷ]
	*2; no valid device, namely left space is 0 [2;   û����Ч���豸,��ʣ��ռ�Ϊ0]
	*3; there is other CD imprintinging now [3;   �����������ڿ�¼]
	*4; device is not idle, namely it is backuping, imprintinging or relaying now [4;   �豸Ϊ�ǿ���״̬,���ڱ��ݡ���¼��ط���]
	*/
	BYTE	bRomType;		//CD type(new imprinting has this value)(0:RV file system; 1:removable disk or U disk; 2:CD) [������Ƭ����(�¿�¼���������ֵ)(0:RV�ļ�ϵͳ��1���ƶ�Ӳ�̻�u�̣�2������)]
	BYTE	bOperateType;   //operation type(new imprinting has this value)(0:idle; 1:back uping; 2:imprintinging; 3:replaying in CD) [��������(�¿�¼���������ֵ)(0�����У�1�����ڱ����У�2�����ڿ�¼�У�3�����ڽ��й��̻ط�)]
	BYTE	bType;			//state of back up or imprinting(new imprinting has this value)(0:stop or end; 1:start; 2:error; 3:full; 4:initializing) [���ݻ��¼�ù���״̬(�¿�¼���������ֵ)(0��ֹͣ����� ��1����ʼ��2������3����;4�����ڳ�ʼ��)	]
	//**************************
	NET_TIME stTimeStart;	//start time [��ʼʱ��]
	DWORD	dwTimeElapse;	//already imprintinged time(second) [�ѿ�¼ʱ��(��)]
	DWORD	dwTotalSpace;	//CD total space [����������]
	DWORD	dwRemainSpace;	//CD left space [����ʣ������]
	DWORD	dwBurned;		//already imprintinged space [�ѿ�¼����]
	DWORD	dwStatus;		/*
							for compatible old device, resered, new imprinting has no real using [Ϊ�˼������豸�����������ģ��¿�¼��û��ʵ���ô�]
							-1:flag new imprinting device. if it is not -1, flag old imprinting device [-1����ʾ�¿�¼���������Ϊ-1����ʾ�ɿ�¼��]
							down is imprinting state of old device(old device using) if it is not -1, flag old imprinting device [���������豸�Ŀ�¼״̬�����豸�õģ������Ϊ-1����ʾ�ɿ�¼����]
							0-initializing [0-���ڳ�ʼ����]
							1-imprintinging, variables above are valid [1-���ڿ�¼�����ϸ�������Ч]
							2-imprinting error [2-��¼����]
							3-stoped because CD was full [3-����ֹͣ]
							*/
}RV_BURNING_PROGRESS, *LPRV_BURNING_PROGRESS;

//language structs device supported [�豸֧�����Խṹ��]
typedef struct _RV_LANGUAGE_DEVINFO
{
	DWORD	dwLanguageNum;		    //number of language type supported [֧�����Ը���]
	BYTE    byLanguageType[252];    //enum valus, detail to RV_LANGUAGE_TYPE [ö��ֵ,���RV_LANGUAGE_TYPE]
}RV_DEV_LANGUAGE_INFO, *LPRV_DEV_LANGUAGE_INFO;


typedef struct  
{
	RV_TALK_CODING_TYPE		encodeType;		//code type [��������]
	int						nAudioBit;		//using real value, eg. fill it with 8 if 8 bits [��ʵ�ʵ�ֵ��ʾ����8λ ����ֵΪ8]
	DWORD					dwSampleRate;	//sample rate, eg. fill it with 16000 if 16k [�����ʣ���16k ����ֵΪ16000]
	char					reserved[64];
}DHDEV_TALKDECODE_INFO;

//audio talk format device supported [�豸֧�ֵ������Խ���ʽ]
typedef struct 
{
	int						nSupportNum;	//number [����]
	DHDEV_TALKDECODE_INFO	type[64];		//code format [�����ʽ]
	char					reserved[64];
}DHDEV_TALKFORMAT_LIST;

////////////////////end of params definition of query device state [end of ��ѯ�豸״̬�Ĳ�������]////////////////////////////////

//DDNS configure [DDNS ����]
typedef struct 
{
	BOOL	enable;
	int		DDNSKey;
	char	ServerName[64];
	int		ip;
	int		Port;
	char	UserName[64];
	char	Password[64];
	BOOL	Anonymity;
}DDNS;

typedef struct
{
	DDNS Ddns[2];
}NET_DEV_DDNS;

typedef struct
{
	int	 Count;
	DDNS Ddns[MAX_DDNS_COUNT];
}NET_DEV_DDNS_EX;

//struct of GPS information [GPS��Ϣ�ṹ��]
typedef struct _GPS_Info
{
	NET_TIME revTime;        //locate time [��λʱ��]
	char DvrSerial[50];      //device serial number [�豸���к�]
	double longitude;        //longitude [����]
	double latidude;         //latitude [γ��]
	double height;           //height(minute) [�߶ȣ��ף�]
	double angle;            //direction angle(north direction is origin point, clockwise is positive) [����ǣ���������Ϊԭ�㣬˳ʱ��Ϊ����]
	double speed;            //speed(kilometers per hour) [�ٶȣ�����/Сʱ��]
	WORD starCount;          //locate star number [��λ����]
	BOOL antennaState;       //antenna state(true good, false bad) [����״̬(true �ã�false ��)]
	BOOL orientationState;   //locate state(true good, false bad) [��λ״̬��true ��λ��false ����λ��]
}GPS_Info,*LPGPS_Info;

//snapshot param struct [ץͼ�����ṹ��]
typedef struct _snap_param
{
	UINT Channel;				//snapshot channel [ץͼ��ͨ��]
	UINT Quality;				//picture quality 1~6, this param is valid only for DVR on vehicle [����1~6, �˲���ֻ��Գ���DVR�豸��Ч]
	UINT ImageSize;				//picture size 0:QCIF, 1:CIF, 2:D1, this param is valid only for DVR on vehicle [�����С 0:QCIF,1:CIF,2:D1, �˲���ֻ��Գ���DVR�豸��Ч]
	UINT mode;					//snapshot mode, 0:means request one frame; 1:means request timer sendding; 2:means continues request, this param is valid only for DVR on vehicle [ץͼģʽ 0����ʾ����һ֡; 1����ʾ��ʱ��������; 2����ʾ��������,����DVR�豸��Ч��]
	UINT InterSnap;				//time unit second, if mode=1(means timer sending), this time is valid, this param is valid only for DVR on vehicle [ʱ�䵥λ�� ��mode=1��ʾ��ʱ��������ʱ����ʱ����Ч������ֻ�г���DVR��Ч��]
	UINT CmdSerial;				//request serial number [�������к�]
	UINT Reserved[4];
}SNAP_PARAMS,*LPSNAP_PARAMS;

//snapshot struct for network trigger device [���紥���豸ץͼ�ṹ��]
typedef struct __NET_SNAP_COMMANDINFO 
{
	char			szCardInfo[16];		//card information [������Ϣ]
	char			reserved[64];		//reserved [����]
} NET_SNAP_COMMANDINFO, LPNET_SNAP_COMMANDINFO;

//protocal information [Э����Ϣ]
typedef struct 
{
	char            protocolname[12]; //protocal name [Э����]
	unsigned int	baudbase;	      //baudrate [������]
	unsigned char	databits; 	      //data bit [����λ]
	unsigned char	stopbits;	      //stop bit [ֹͣλ]
	unsigned char	parity;		      //veryfy bit [У��λ]
	unsigned char   reserve;
} PROTOCOL_INFO, *LPPROTOCOL_INFO;

//audio format information [��Ƶ��ʽ��Ϣ]
typedef struct {
	BYTE	byFormatTag;			//code type, 0-PCM [�������ͣ���0-PCM]
	WORD	nChannels;				//audio channel number [������]
	WORD	wBitsPerSample;			//sample depth [�������]			
	DWORD	nSamplesPerSec;			//sample rate [������]
} RV_AUDIO_FORMAT, *LPRV_AUDIO_FORMAT;

//query device work state channel information:interface is invalid now, don't use it [��ѯ�豸����״̬ͨ����Ϣ:��ؽӿ�����̭���벻Ҫʹ��]
typedef struct {
	BYTE byRecordStatic;			//channel is recrding, 0-no record, 1-manual record, 2-auto record [ͨ���Ƿ���¼��,0-��¼��,1-�ֶ�¼��2-�Զ�¼��]
	BYTE bySignalStatic;			//signal state of connection, 0-normal, 1-signal lost [���ӵ��ź�״̬,0-����,1-�źŶ�ʧ]
	BYTE byHardwareStatic;			//hardware state of channel, 0-normal, 1-except, eg.DSP is dead [ͨ��Ӳ��״̬,0-����,1-�쳣,����DSP����]
	char reserve;
	DWORD dwBitRate;				//real bit-rate [ʵ������]
	DWORD dwLinkNum;				//cnnection number of client [�ͻ������ӵĸ���]
	DWORD dwClientIP[RV_MAX_LINK];	//IP address of client [�ͻ��˵�IP��ַ]
}NET_DEV_CHANNELSTATE,*LPNET_DEV_CHANNELSTATE;

//auery device work state:interface is invalid now, don't use it [��ѯ�豸����״̬:��ؽӿ�����̭���벻Ҫʹ��]
typedef struct{
	DWORD dwDeviceStatic; 									//device state, 0x00 noamal, 0x01 CPU usage is high, 0x02 hardware error [�豸��״̬,0x00 ����,0x01 CPUռ�ù���,0x02 Ӳ������]
	NET_DEV_DISKSTATE  stHardDiskStatic[RV_MAX_DISKNUM]; 
	NET_DEV_CHANNELSTATE stChanStatic[RV_MAX_CHANNUM];		//channel state [ͨ����״̬]
	BYTE  byAlarmInStatic[RV_MAX_ALARMIN];					//alarm port state, 0-no alarm, 1-alarm [�����˿ڵ�״̬,0-û�б���,1-�б���]
	BYTE  byAlarmOutStatic[RV_MAX_ALARMOUT];				//state of alarm output port, 0-no output, 1-output [��������˿ڵ�״̬,0-û�����,1-�б������]
	DWORD  dwLocalDisplay;									//local display status, 0-normal, 1-unnormal [������ʾ״̬,0-����,1-������]
} NET_DEV_WORKSTATE,*LPNET_DEV_WORKSTATE;

/************************************************************************
** callback function prototype of listen server [�����������ص�ԭ��]
***********************************************************************/
typedef int (CALLBACK *fServiceCallBack)(LONG lHandle, char *pIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, DWORD dwUserData);

/************************************************************************
**callback function prototype of disconnect from server [�������Ͽ��ص�ԭ��]
***********************************************************************/
typedef void (CALLBACK *fDisConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

//	callback function prototype of reconnect to server after disconnection [���������ɹ��ص�����]
typedef void (CALLBACK *fHaveReConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

/************************************************************************
** callback function prototype of real-time preview [ʵʱԤ���ص�ԭ��]
***********************************************************************/
typedef void(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of origin data [ԭʼ���ݻص�ԭ��]
***********************************************************************/
typedef int(CALLBACK *fDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of messasge(alarm) [��Ϣ���������ص�ԭ��]
***********************************************************************/
typedef BOOL (CALLBACK *fMessCallBack)(LONG lCommand, LONG lLoginID, char *pBuf,
	DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

/************************************************************************
** callback function prototype of screen overprint [��Ļ���ӻص�ԭ��]
***********************************************************************/
typedef void (CALLBACK *fDrawCallBack)(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);

/************************************************************************
** callback function prototype of real-time preview extend [ʵʱԤ���ص�ԭ��-��չ]
***********************************************************************/
typedef void(CALLBACK *fRealDataCallBackEx) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, DWORD dwUser);

/************************************************************************
** callback function prototype of replay process [�ط�¼����Ȼص�ԭ��]
***********************************************************************/
typedef void(CALLBACK *fDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

/************************************************************************
** callback function prototype of downloading process by time [ͨ��ʱ������¼����Ȼص�ԭ��]
not used now, using callback function prototype of replay process [���ڰ�ʱ������û��ʹ������ص�������ʹ�õ��ǻط�¼����Ȼص�ԭ��. ]
***********************************************************************/
typedef void(CALLBACK *fTimeDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser);

/************************************************************************
** callback function prototype of downloading process by time [ͨ��ʱ������¼����Ȼص�ԭ��]
not used now, using callback function prototype of replay process [���ڰ�ʱ������û��ʹ������ص�������ʹ�õ��ǻط�¼����Ȼص�ԭ��. ]
***********************************************************************/
typedef void(CALLBACK *fTimeDownLoadPosCallBackNew) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO_EX recordfileinfo, DWORD dwUser);

/************************************************************************
** callback function prototype of query device log data [��ѯ�豸��־���ݻص�ԭ��]
***********************************************************************/
typedef void(CALLBACK *fLogDataCallBack) (LONG lLoginID, char *pBuffer, DWORD dwBufSize, DWORD nTotalSize, BOOL bEnd, DWORD dwUser);

/************************************************************************
** callback function prototype of clarity serial port [͸�����ڻص�ԭ��]
***********************************************************************/
typedef void(CALLBACK *fTransComCallBack) (LONG lLoginID, LONG lTransComChannel, char *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of upgrade device [�����豸����ص�ԭ��]
***********************************************************************/
typedef void(CALLBACK *fUpgradeCallBack) (LONG lLoginID, LONG lUpgradechannel, int nTotalSize, int nSendSize, DWORD dwUser);

/************************************************************************
** callback function prototype of audio data of audio talk [�����Խ�����Ƶ���ݻص�ԭ��]
***********************************************************************/
typedef void(CALLBACK *pfAudioDataCallBack) (LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);

/***********************************************************************
** callback function prototype of snapshot [ץͼ�ص�ԭ��]
***********************************************************************/
typedef void( CALLBACK *fSnapRev)(LONG lLoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, DWORD CmdSerial, DWORD dwUser);

/************************************************************************
** SDK initialization [SDK��ʼ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_Init(fDisConnect cbDisConnect, DWORD dwUser);

/************************************************************************
** SDK cleanup [SDK�˳�����]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_Cleanup();

/************************************************************************
** set the callback function of successfulllu reconnection to server after disconnection, SDK will auto reconnect to server after disconnected from server [���ö��������ɹ��ص����������ú�SDK�ڲ������Զ�����]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetAutoReconnect(fHaveReConnect cbAutoConnect, DWORD dwUser);

/************************************************************************
** return error code for function comminting failed [���غ���ִ��ʧ�ܴ���]
***********************************************************************/
CLIENT_API DWORD CALL_METHOD CLIENT_GetLastError(void);

/************************************************************************
** set the timeout and try-times of conncting to server [�������ӷ�������ʱʱ��ͳ��Դ���]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetConnectTime(int nWaitTime, int nTryTimes);


/************************************************************************
** get version info of SDK [��ȡSDK�İ汾��Ϣ]
***********************************************************************/
CLIENT_API DWORD CALL_METHOD CLIENT_GetSDKVersion();


/************************************************************************
** register to device [���豸ע��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_Login(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

//	nSpecCap = 0 is login by TCP; nSpecCap = 2 is login by auto-register; nSpecCap = 3 is login by group cast; nSpecCap = 4 is login by UDP [nSpecCap = 0ΪTCP��ʽ�µĵ��룻nSpecCap = 2Ϊ����ע��ĵ��룻nSpecCap = 3Ϊ�鲥��ʽ�µĵ��룻nSpecCap = 4ΪUDP��ʽ�µĵ���]
CLIENT_API LONG CALL_METHOD CLIENT_LoginEx(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, int nSpecCap, void* pCapParam, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

/************************************************************************
** logout from device [���豸ע��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_Logout(LONG lLoginID);

/************************************************************************
** 
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetDVRMessCallBack(fMessCallBack cbMessage,DWORD dwUser);


/************************************************************************
** set audio talk mode [���������Խ�ģʽ]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetDeviceMode(LONG lLoginID, EM_USEDEV_MODE emType, void* pValue);


/************************************************************************
** start listen to device [��ʼ֡���豸]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StartListen(LONG lLoginID);

//corresponding to LB device's software version [��ӦLB�豸����汾]
CLIENT_API BOOL CALL_METHOD CLIENT_StartListenEx(LONG lLoginID);

/************************************************************************
** stop listrn to device [ֹͣ֡���豸]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopListen(LONG lLoginID);

/************************************************************************
** start to listrn to server, listen mobile DVR connection [��ʼ�����������������ƶ�DVR����]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_ListenServer(char* ip, WORD port, int nTimeout, fServiceCallBack cbListen, DWORD dwUserData);

/************************************************************************
** stop listen server, stop listen mobile DVR connection [ֹͣ������������ֹͣ�����ƶ�DVR����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopListenServer(LONG lServerHandle);

/************************************************************************
** respond to register device request [��Ӧ�豸��ע������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ResponseDevReg(char *devSerial, char* ip, WORD port, BOOL bAccept);

/************************************************************************
** start service port [��������˿�]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_StartService(WORD wPort, char *pIp = NULL, fServiceCallBack pfscb = NULL, 
	DWORD dwTimeOut = 0xffffffff, DWORD dwUserData = 0);

/************************************************************************
** stop service port [ֹͣ����˿�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopService(LONG lHandle);

/************************************************************************
** set screen overprint callback [������Ļ���ӻص�]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_RigisterDrawFun(fDrawCallBack cbDraw, DWORD dwUser);


/************************************************************************
** start real-time preview [��ʼʵʱԤ��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_RealPlay(LONG lLoginID, int nChannelID, HWND hWnd);
CLIENT_API LONG CALL_METHOD CLIENT_RealPlayEx(LONG lLoginID, int nChannelID, HWND hWnd, RV_RealPlayType rType = RV_RType_Realplay);

CLIENT_API BOOL	CALL_METHOD CLIENT_AdjustFluency(LONG lRealHandle, int nLevel);

/************************************************************************
** stop real-time preview [ֹͣʵʱԤ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlay(LONG lRealHandle);

/************************************************************************
** stop real-time preview extend [ֹͣʵʱԤ��_��չ]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlayEx(LONG lRealHandle);

/************************************************************************
** save data to file [��������Ϊ�ļ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SaveRealData(LONG lRealHandle, const char *pchFileName);


/************************************************************************
** stop saving data to file [������������Ϊ�ļ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopSaveRealData(LONG lRealHandle);


/************************************************************************
** set picture attributes [����ͼ������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffect(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

/************************************************************************
** set picture attributes new [����ͼ������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffectNew(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

/************************************************************************
** get picture attributes [��ȡͼ������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffect(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

/************************************************************************
**  get picture attributes new [��ȡͼ������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffectNew(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

/************************************************************************
** open audio [������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSound(LONG hPlayHandle);

/************************************************************************
** open audio new [������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSoundNew(LONG hPlayHandle);

/************************************************************************
** close audio [�ر�����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSound();

/************************************************************************
** close audio new [�ر�����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSoundNew();

/************************************************************************
** open audio talk [�������Խ�]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_StartTalkEx(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser);

/************************************************************************
** set the volumn of audio talk [���������Խ�������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetAudioClientVolume(LONG lTalkHandle, WORD wVolume);

/************************************************************************
** send audio dta to device [�����������ݵ��豸]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);

/************************************************************************
** start audio recording on PC [��ʼPC��¼��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStart();

/************************************************************************
** stop audio recording on PC [����PC��¼��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStop();

/************************************************************************
** decode audio data [������Ƶ����]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_AudioDec(char *pAudioDataBuf, DWORD dwBufSize);

/************************************************************************
** stop audio talk [ֹͣ�����Խ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalkEx(LONG lTalkHandle);

/************************************************************************
** add device to broadcast group [����豸���㲥��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastAddDev(LONG lLoginID);

/************************************************************************
** delete device from broadcast group [�ӹ㲥����ɾ���豸]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastDelDev(LONG lLoginID);

/************************************************************************
** set the volumn [��������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetVolume(LONG lPlayHandle, int nVolume);

/************************************************************************
** audio code--initialize (specal standard format->RV format) [��Ƶ����--��ʼ��(�ض���׼��ʽ->RV��ʽ)]
***********************************************************************/
CLIENT_API int  CALL_METHOD CLIENT_InitAudioEncode(RV_AUDIO_FORMAT aft);

/************************************************************************
** audio code--data code [��Ƶ����--���ݱ���]
***********************************************************************/
CLIENT_API int	CALL_METHOD	CLIENT_AudioEncode(LONG lTalkHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);

/************************************************************************
** audio code--quit after complete [��Ƶ����--����˳�]
***********************************************************************/
CLIENT_API int	CALL_METHOD	CLIENT_ReleaseAudioEncode();

/************************************************************************
** set the callback function of real-time preview [����ʵʱԤ���ص�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBack(LONG lRealHandle, fRealDataCallBack cbRealData, DWORD dwUser);

/************************************************************************
** set the callback function of real-time preview extend [����ʵʱԤ���ص�-��չ]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBackEx(LONG lRealHandle, fRealDataCallBackEx cbRealData, DWORD dwUser, DWORD dwFlag);

/************************************************************************
** snapshot [ץͼ]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CapturePicture(LONG hPlayHandle, const char *pchPicFileName);

/************************************************************************
** snapshot new [ץͼ]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CapturePictureNew(LONG hPlayHandle, const char *pchPicFileName);

/************************************************************************
** query that if it has record in some time slice [��ѯĳ��ʱ�����Ƿ���¼��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime=1000);

/************************************************************************
** query record file by time [ͨ��ʱ���ѯ¼���ļ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFile(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

/************************************************************************
** query record file by time new [ͨ��ʱ���ѯ¼���ļ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFileNew(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO_EX nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

/************************************************************************
** replay record file [�ط�¼���ļ�]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFile(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** replay record file extend, added data callback params [�ط�¼���ļ���չ_���������ݻص�����]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileEx(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** replay record file extend, added dta callback params new [�ط�¼���ļ���չ_���������ݻص�����]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileExNew(LONG lLoginID, LPNET_RECORDFILE_INFO_EX lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** replay record file new [�ط�¼���ļ�]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileNew(LONG lLoginID, LPNET_RECORDFILE_INFO_EX lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** pause record replay [��ͣ¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBack(LONG lPlayHandle, BOOL bPause);

/************************************************************************
** pause record replay new [��ͣ¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBackNew(LONG lPlayHandle, BOOL bPause);

/************************************************************************
** locate record replay start point [��λ¼��ط���ʼ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBack(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

/************************************************************************
** locate record replay start point new [��λ¼��ط���ʼ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBackNew(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

/************************************************************************
** stop record replay [ֹͣ¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBack(LONG lPlayHandle);

/************************************************************************
** stop record replay new [ֹͣ¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBackNew(LONG lPlayHandle);

/************************************************************************
** step record replay [����¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBack(LONG lPlayHandle, BOOL bStop);

/************************************************************************
** step record replay new [����¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBackNew(LONG lPlayHandle, BOOL bStop);

/************************************************************************
** fast record replay [���¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBack(LONG lPlayHandle);

/************************************************************************
** fast record replay new [���¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBackNew(LONG lPlayHandle);

/************************************************************************
** slow record replay [����¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBack(LONG lPlayHandle);

/************************************************************************
** slow record replay new [����¼��ط�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBackNew(LONG lPlayHandle);

/************************************************************************
** restore normal replay speed [�ָ������ط��ٶ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBack(LONG lPlayHandle);

/************************************************************************
** restore normal replay speed new [�ָ������ط��ٶ�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBackNew(LONG lPlayHandle);

/************************************************************************
** set the replay frame rate [���ûط�֡��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetFramePlayBack(LONG lPlayHandle, int framerate);

/************************************************************************
** get the replay frame rate [��ȡ�ط�֡��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetFramePlayBack(LONG lPlayHandle, int *fileframerate, int *playframerate);

/************************************************************************
** get replay OSD time [��ȡ�ط�OSDʱ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetPlayBackOsdTime(LONG lPlayHandle, LPNET_TIME lpOsdTime, LPNET_TIME lpStartTime, LPNET_TIME lpEndTime);

/************************************************************************
** download record file [����¼���ļ�]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFile(LONG lLoginID,LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record file new [����¼���ļ�]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFileNew(LONG lLoginID,LPNET_RECORDFILE_INFO_EX lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record by time [ͨ��ʱ������¼��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record by time new [ͨ��ʱ������¼��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTimeNew(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBackNew cbTimeDownLoadPos, DWORD dwUserData);

/************************************************************************
** stop downloading record [ֹͣ¼������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownload(LONG lFileHandle);

/************************************************************************
** stop downloading record new [ֹͣ¼������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownloadNew(LONG lFileHandle);

/************************************************************************
** query process of downloading record [��ѯ¼�����ؽ���]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPos(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

/************************************************************************
** query process of downloading record new [��ѯ¼�����ؽ���]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPosNew(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

/************************************************************************
** multi-views real-time preview [�໭��ʵʱԤ��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_MultiPlay(LONG lLoginID, HWND hWnd);

/************************************************************************
** stop multi-views real-time preview [ֹͣ�໭��ʵʱԤ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopMultiPlay(LONG lMultiHandle);

/************************************************************************
** query system server configure-not valid now, please use CLIENT_GetDevConfig [��ѯϵͳ���������� ���ýӿ�����̭����ʹ��CLIENT_GetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int maxlen, int *nConfigbuflen, int waittime=1000);

/************************************************************************
** set system server configure-not valid now, please use CLIENT_SetDevConfig [����ϵͳ���������� ���ýӿ�����̭����ʹ��CLIENT_SetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetupConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int nConfigbuflen, int waittime=1000);

/************************************************************************
** query device channel name [��ѯ�豸ͨ������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryChannelName(LONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime=1000);

/************************************************************************
** set device channel name [�����豸ͨ������]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelName(LONG lLoginID,char *pbuf, int nbuflen);

/************************************************************************
** set device channel charater overprint [�����豸ͨ���ַ�����]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelOsdString(LONG lLoginID, int nChannelNo, RV_CHANNEL_OSDSTRING* struOsdString, int nbuflen);

/************************************************************************
** common PTZ control [ͨ����̨����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

/************************************************************************
** RV PTZ control [RV��̨����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
	unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop);

/************************************************************************
** RV PTZ control extend interface, support 3D fast location [RV��̨������չ�ӿڣ�֧����ά���ٶ�λ]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControlEx(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
	LONG lParam1, LONG lParam2, LONG lParam3, BOOL dwStop);

/************************************************************************
** query device log asynchronously [�첽��ѯ�豸��־]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogCallback(LONG lLoginID, fLogDataCallBack cbLogData, DWORD dwUser);

/************************************************************************
** query device log synchronously [ͬ����ѯ�豸��־]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLog(LONG lLoginID, char *pLogBuffer, int maxlen, int *nLogBufferlen, int waittime=3000);

CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogEx(LONG lLoginID, RV_LOG_QUERY_TYPE logType, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime=3000);

/************************************************************************
** create clarity serial port channel [����͸������ͨ��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_CreateTransComChannel(LONG lLoginID, int TransComType, 
	unsigned int baudrate, unsigned int databits,
	unsigned int stopbits, unsigned int parity,
	fTransComCallBack cbTransCom, DWORD dwUser);

/************************************************************************
** send data by clarity serial port [͸�����ڷ�������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SendTransComData(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

/************************************************************************
** release clarity serial port channel [�ͷ�ͨ������ͨ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_DestroyTransComChannel(LONG lTransComChannel);

/************************************************************************
** this interface is invalid now, please don't use it [�ýӿ�����̭���벻Ҫʹ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_Reset(LONG lLoginID, BOOL bReset);

// set the network evironment for login  [���õ�½���绷��]
CLIENT_API void CALL_METHOD CLIENT_SetNetworkParam(NET_PARAM *pNetParam);

// import configure file [���������ļ�]
CLIENT_API LONG CALL_METHOD CLIENT_ImportConfigFile(LONG lLoginID, char *szFileName, fDownLoadPosCallBack cbUploadPos, DWORD dwUserData, DWORD param=0);

// stop importing configure file [ֹͣ���������ļ�]
CLIENT_API BOOL CALL_METHOD CLIENT_StopImportCfgFile(LONG lImportHandle);

// outport configure file [���������ļ�]
CLIENT_API LONG CALL_METHOD CLIENT_ExportConfigFile(LONG lLoginID, DH_CONFIG_FILE_TYPE emConfigFileType, char *szSavedFilePath, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

// stop outputing configure file [ֹͣ���������ļ�]
CLIENT_API BOOL CALL_METHOD CLIENT_StopExportCfgFile(LONG lExportHandle);

// search IPC, NVS, etc... devices in local network [������������IPC��NVS���豸]
CLIENT_API BOOL CALL_METHOD CLIENT_SearchDevices(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime);

CLIENT_API BOOL CALL_METHOD CLIENT_GetDiskType(LONG lLoginID, NET_DEV_DISKTYPE* Type, DWORD dwSearchTime = 2000);

/************************************************************************
** start to upgrade software of device [��ʼ�����豸����]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_StartUpgrade(LONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

CLIENT_API LONG CALL_METHOD CLIENT_StartUpgradeEx(LONG lLoginID, EM_UPGRADE_TYPE emType, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);


/************************************************************************
** send data [��������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SendUpgrade(LONG lUpgradeID);

/************************************************************************
** end upgrading software of device [���������豸����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopUpgrade(LONG lUpgradeID);

/************************************************************************
** query record state of channel [���ͨ��¼��״̬]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordState(LONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, int waittime=1000);

/************************************************************************
** set record state of channel [����ͨ��¼��״̬]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetupRecordState(LONG lLoginID, char *pRSBuffer, int nRSBufferlen);

/************************************************************************
** query current time of device [��ѯ�豸��ǰʱ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime, int waittime=1000);

/************************************************************************
** set current time of device [�����豸��ǰʱ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetupDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime);

/************************************************************************
** query serial port protocal - not invalid now, please use CLIENT_GetDevConfig [��ѯ����Э�� �� �ýӿ�����̭����ʹ��CLIENT_GetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryComProtocol(LONG lLoginID, int nProtocolType, char *pProtocolBuffer, int maxlen, int *nProtocollen, int waittime=1000);

/************************************************************************
** set serial port protocal - not invalid now, please use CLIENT_SetDevConfig [��ѯϵͳ��Ϣ �� �ýӿ�����̭����ʹ��CLIENT_GetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QuerySystemInfo(LONG lLoginID, int nSystemType, char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime=1000);

/************************************************************************
auery lock state of account [��ѯ�û�����״̬]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetUserLockState(LONG lLoginID, char* UserName, bool *bstate);

/************************************************************************
release lock state of account [����û�����״̬]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_UnlockUserLockState(LONG lLoginID, char* UserName);

/************************************************************************
recommend to use extended interface(the max length of user name of some devices is 16 bytes) from now on[�����Ժ�����չ�ӿ�(��Щ�豸�û�����󳤶���16���ֽڵ�)]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfoEx(LONG lLoginID, USER_MANAGE_INFO_EX *info, int waittime=1000);

/************************************************************************
** query device user (old interface, support 8 bit user name length) [��ѯ�豸�û�(�Ͻӿڡ�֧��8λ�û������ȡ�)]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfo(LONG lLoginID, USER_MANAGE_INFO *info, int waittime=1000);

/************************************************************************
** operate account of device [�����豸�û�]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfo(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);
/************************************************************************
** operate account of device (new interface, support 8 bits and 16 bits user name and password) [�����豸�û����½ӿڣ�֧��8λ��16λ���û������볤�ȣ���]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfoEx(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

/************************************************************************
** start to talk - invalid now, please use CLIENT_StartTalkEx [��ʼ�Խ� �� �ýӿ�����̭����ʹ��CLIENT_StartTalkEx]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StartTalk(LONG lRealHandle, BOOL bCustomSend=false);

/************************************************************************
** stop talk - invalid now, please use CLIENT_StopTalkEx [�����Խ� �� �ýӿ�����̭����ʹ��CLIENT_StopTalkEx]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalk(LONG lRealHandle);

/************************************************************************
** send self defined talk data - invalid now, please use CLIENT_TalkSendData [�����Զ���Խ����� �� �ýӿ�����̭����ʹ��CLIENT_TalkSendData]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SendTalkData_Custom(LONG lRealHandle, char *pBuffer, DWORD dwBufSize);

/************************************************************************
** get channel bit-stream [��ȡͨ������]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

/************************************************************************
** query IO state [��ѯIO״̬]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryIOControlState(LONG lLoginID, RV_IOTYPE emType, 
	void *pState, int maxlen, int *nIOCount, int waittime=1000);

/************************************************************************
** IO control [IO����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_IOControl(LONG lLoginID, RV_IOTYPE emType, void *pState, int maxlen);

/************************************************************************
** query device work state, invalid now, please use CLIENT_QueryDevState [��ѯ�豸����״̬ �ýӿ�����̭����ʹ��CLIENT_QueryDevState]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDEVWorkState(LONG lLoginID, LPNET_DEV_WORKSTATE lpWorkState, int waittime=1000);

/************************************************************************
** force I Frame [ǿ��I֡]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_MakeKeyFrame(LONG lLoginID, int nChannelID, int nSubChannel=0);

/************************************************************************
** set limit bit-stream of device [�����豸��������]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetMaxFlux(LONG lLoginID, WORD wFlux);

/************************************************************************
** qury device IP from DDNS server by device name or device serial number [ͨ���豸���ֻ����豸���к���DDNS��������ѯ�豸IP]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDVRIPByResolveSvr(char *pchDVRIP, WORD wDVRPort, 
	BYTE *sDVRName, WORD wDVRNameLen, 
	BYTE *sDVRSerialNumber, WORD wDVRSerialLen, 
	char* sGetIP);

/************************************************************************
** replay record by time [ͨ��ʱ��ط�¼��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTime(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

/************************************************************************
** replay record by time new [ͨ��ʱ��ط�¼��]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeNew(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

/************************************************************************
** replay record by time extend, added data callback params [ͨ��ʱ��ط�¼����չ_���������ݻص�����]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeEx(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser,
	fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** replay record by time extend, added data callback params new [ͨ��ʱ��ط�¼����չ_���������ݻص�����]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeExNew(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser,
	fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** start to find record files [��ʼ����¼���ļ�]
***********************************************************************/
CLIENT_API LONG	CALL_METHOD CLIENT_FindFile(LONG lLoginID,
	int nChannelId,
	int nRecordFileType, 
	char* cardid, 
	LPNET_TIME time_start,
	LPNET_TIME time_end,
	BOOL bTime, 
	int waittime);

/************************************************************************
** find record file [����¼���ļ�]
***********************************************************************/
CLIENT_API int	CALL_METHOD CLIENT_FindNextFile(LONG lFindHandle,LPNET_RECORDFILE_INFO lpFindData);

/************************************************************************
** end finding record file [����¼���ļ�����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FindClose(LONG lFindHandle);

/************************************************************************
** start to find record files new [��ʼ����¼���ļ�]
***********************************************************************/
CLIENT_API LONG	CALL_METHOD CLIENT_FindFileNew(LONG lLoginID,
	int nChannelId,
	int nRecordFileType, 
	char* cardid, 
	LPNET_TIME time_start,
	LPNET_TIME time_end,
	BOOL bTime, 
	int waittime);

/************************************************************************
** find record file new [����¼���ļ�]
***********************************************************************/
CLIENT_API int	CALL_METHOD CLIENT_FindNextFileNew(LONG lFindHandle,LPNET_RECORDFILE_INFO_EX lpFindData);

/************************************************************************
** end finding record file new [����¼���ļ�����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FindCloseNew(LONG lFindHandle);

/************************************************************************
** reboot device : returned TRUE success, FALSE fail [�����豸������ֵ TRUE �ɹ��� FALSE ʧ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_RebootDev(LONG lLoginID);

/************************************************************************
** reset : returned TRUE success, FALSE fail [�ָ��������ã�����ֵ TRUE �ɹ��� FALSE ʧ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ResetDeafault(LONG lLoginID, unsigned long type);

/************************************************************************
** shutdown device : returned TRUE success, FALSE fail [�ر��豸������ֵ TRUE �ɹ��� FALSE ʧ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ShutDownDev(LONG lLoginID);

/************************************************************************
** control device : returned TRUE success, FALSE fail [�豸���ƣ�����ֵ TRUE �ɹ��� FALSE ʧ��]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ControlDevice(LONG lLoginID, CtrlType type, void *param, int waittime = 1000);

/************************************************************************
** auto query device state, include alarm, disk, record state, etc... [������ѯ�豸״̬������������Ӳ�̡�¼��״̬�ȡ�]
***********************************************************************/
//if nType  = RV_DEVSTATE_BURNING_PROGRESS, *pRetLen means query device's ID No. The reason of dealing as this is that there is no other suction parameter to use [�� nType  = RV_DEVSTATE_BURNING_PROGRESS ʱ,*pRetLen��ʾ��ѯ�豸��id��.��������ԭ����û����������ʹ�õ���ڲ�����]
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDevState(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

///////////////it is function interfaces for dvr on vehicle bellow [�����ǳ���dvr��صĹ��ܽӿ�] /////////////////////////
/************************************************************************
** set the callback function for snapshot [����ץͼ�ص�����]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, DWORD dwUser);

/************************************************************************
** snapshot request [ץͼ����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SnapPicture(LONG lLoginID, SNAP_PARAMS par);

/************************************************************************
** callback function prototype of GPS information subscription [GPS��Ϣ���Ļص�]
***********************************************************************/
typedef void( CALLBACK *fGPSRev)(LONG lLoginID,           //device handle [�豸���]
	GPS_Info  GpsInfo,       //GPS information [GPS��Ϣ]
	DWORD dwUserData);       //user data [�û�����]

/************************************************************************
** set tje callback function of GPS information subscription [����GPS���Ļص�����]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSCallBack(fGPSRev OnGPSMessage, DWORD dwUser);

/************************************************************************
** GPS information subscription [GPS��Ϣ����]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SubcribeGPS (
	LONG lLoginID,        //device handle [�豸���]
	BOOL bStart,		  //if lauch [�Ƿ�����]
	LONG KeepTime,        //subscription duration (unit:second) [���ĳ���ʱ�䣨��λ�룩]
	LONG InterTime);      //subscription GPS send frequency in duration (unit:second) [����ʱ����GPS����Ƶ�ʣ���λ�룩]  

/////////////////////////end of function interfaces for dvr on vehicle [end of ����dvr��صĹ���] ///////////////////////////////


/////////////////////////unfulfilment [δʵ��]//////////////////////////
/************************************************************************
** set the huffer size of real-time preview [����ʵʱԤ�������С]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlayerBufNumber(LONG lRealHandle, DWORD dwBufNum);

/************************************************************************
** download file by time, CLIENT_DownloadByTime has implemented this function [ͨ��ʱ�������ļ���CLIENT_DownloadByTime��ʵ�ָù���]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetFileByTime(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, char *sSavedFileName);

/************************************************************************
** network replay control, it has been detail to several control interfaces [����طſ��ƣ���ϸ��Ϊ�����ƽӿ���]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PlayBackControl(LONG lPlayHandle, 
	DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

//////////////////////////end of unfulfilment [end of δʵ��]//////////////////////


/************************************************************************
** device interfaces of remote configure, configure type showed in the MACRO RV_DEV_DEVICECFG [Զ�������豸�ӿ� �������ͼ�RV_DEV_DEVICECFG ����]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
CLIENT_API BOOL  CALL_METHOD CLIENT_SetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);


/************************************************************************
** platform connection interfaces [ƽ̨����ӿ�]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
CLIENT_API BOOL  CALL_METHOD CLIENT_SetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);

/************************************************************************
**  get PTZ information [��ȡ��̨��Ϣ]	
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPtzOptAttr(LONG lLoginID,DWORD dwProtocolIndex,LPVOID lpOutBuffer,DWORD dwBufLen,DWORD *lpBytesReturned,int waittime=500);

/************************************************************************
**  get decode handle of remote replay [��ȡԶ�̻طŽ�����]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPlayBackPlayerIndex(LONG lPlayHandle);

/************************************************************************
**  get decode handle of preview [��ȡԤ��������]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetRealPlayerIndex(LONG lPlayHandle);

/******************************************************************************
** configure structs [�����Ǹ��������ýṹ��]
*****************************************************************************/

/************************************************************************
*	system information [ϵͳ��Ϣ]
************************************************************************/

/*version information:the high 16 bits is main version number, the low 16 bits is minor version number [�汾��Ϣ:��16λ��ʾ���汾�ţ���16λ��ʾ�ΰ汾��]
*data format of time : yyyymmdd [����ʱ���������֯�ǣ�yyyymmdd] */
typedef struct 
{
	DWORD	dwSoftwareVersion;
	DWORD	dwSoftwareBuildDate;
	DWORD	dwDspSoftwareVersion;
	DWORD	dwDspSoftwareBuildDate;
	DWORD	dwPanelVersion;
	DWORD	dwPanelSoftwareBuildDate;
	DWORD	dwHardwareVersion;
	DWORD	dwHardwareDate;
	DWORD	dwWebVersion;
	DWORD	dwWebBuildDate;
} RV_VERSION_INFO, *LPRV_VERSION_INFO;

/* ability description of DSP (in CLIENT_GetDevConfig), recommend to use CLIENT_QueryDevState [DSP��������(CLIENT_GetDevConfig���)���Ժ�����CLIENT_QueryDevState�ӿ�] */
typedef struct 
{
	DWORD	dwVideoStandardMask;	//mask of video standard, flag device supported standard by bits [��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ]
	DWORD	dwImageSizeMask;		//mask of resolver, flag device supported resolve configure by bits [�ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ�������]
	DWORD	dwEncodeModeMask;		//mask of code mode, flag device supported code mode by bits [����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ����]	

	DWORD	dwStreamCap;			//flag device supported multimedia function by bits [��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�]
									//bit0:support main stream [��һλ��ʾ֧��������]
									//bit1:support assist stream1 [�ڶ�λ��ʾ֧�ָ�����1]
									//bit2:support assist stream2 [����λ��ʾ֧�ָ�����2]
									//bit4:support jpg snapshot [����λ��ʾ֧��jpgץͼ]
	DWORD	dwImageSizeMask_Assi[8];//flag resolve mask of assisit stream according to main stream's reslove [��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣]

	DWORD	dwMaxEncodePower;		//the highest code ability of DSP [DSP ֧�ֵ���߱������� ]
	WORD	wMaxSupportChannel;		//the max video input channel number per DSP [ÿ�� DSP ֧�����������Ƶͨ���� ]
	WORD	wChannelMaxSetSync;		//if the max code configure per DSP channel is synchonous, 0-not be synchonous, 1-be synchonous [DSP ÿͨ���������������Ƿ�ͬ�� 0-��ͬ��, 1-ͬ��]
} RV_DSP_ENCODECAP, *LPRV_DSP_ENCODECAP;

/* struct of device information configure [�豸��Ϣ���ýṹ] */
typedef struct 
{
	DWORD dwSize;
	/*these are read-only of device bellow [�������豸��ֻ������]*/
	RV_VERSION_INFO			stVersion;
	RV_DSP_ENCODECAP		stDspEncodeCap;		//ability description of DSP [DSP��������]
	BYTE	szDevSerialNo[RV_DEV_SERIALNO_LEN];	//serial number [���к�]
	BYTE	byDevType;							//device type, reference to enum DHDEV_DEVICE_TYPE [�豸���ͣ���ö��DHDEV_DEVICE_TYPE]
	BYTE	szDevType[RV_DEV_TYPE_LEN];			//device's detail types, string format, maybe null [�豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��]
	BYTE	byVideoCaptureNum;					//video port number [��Ƶ������]
	BYTE	byAudioCaptureNum;					//audio port number [��Ƶ������]
	BYTE	byTalkInChanNum;					//NSP
	BYTE	byTalkOutChanNum;					//NSP
	BYTE	byDecodeChanNum;					//NSP
	BYTE	byAlarmInNum;						//alarm input port number [�����������]
	BYTE	byAlarmOutNum;						//alarm output port number [�����������]
	BYTE	byNetIONum;							//network port number [�������]
	BYTE	byUsbIONum;							//USB port number [USB������]
	BYTE	byIdeIONum;							//IDE number [IDE����]
	BYTE	byComIONum;							//serial port number [��������]
	BYTE	byLPTIONum;							//parallel port number [��������]
	BYTE	byVgaIONum;							//NSP
	BYTE	byIdeControlNum;					//NSP
	BYTE	byIdeControlType;					//NSP
	BYTE	byCapability;						//NSP, extended description [NSP����չ����]
	BYTE	byMatrixOutNum;						//output-port number of video matrix [��Ƶ�����������]

	/*these are writable parts bellow of device [�������豸�Ŀ�д����]*/
	BYTE	byOverWrite;						//deal method on disk full (overwrite, stop) [Ӳ��������ʽ�����ǡ�ֹͣ��]
	BYTE	byRecordLen;						//package size of record [¼��������]
	BYTE	byStartChanNo;						//NSP
	WORD	wDevNo;								//device No. for remote control [�豸��ţ�����ң��]
	BYTE	byVideoStandard;					//video sandard [��Ƶ��ʽ]
	BYTE	byDateFormat;						//date format [���ڸ�ʽ]
	BYTE	byDateSprtr;						//date seperate (0-"."�� 1-"-"�� 2-"/") [���ڷָ��(0-"."�� 1-"-"�� 2-"/")]
	BYTE	byTimeFmt;							//time format (0-24 hours, 1-12 hours) [ʱ���ʽ (0-24Сʱ��1��12Сʱ)]
	BYTE	byLanguage;						    //enum values, detail in RV_LANGUAGE_TYPE [ö��ֵ���RV_LANGUAGE_TYPE]
} DHDEV_SYSTEM_ATTR_CFG, *LPDHDEV_SYSTEM_ATTR_CFG;

/************************************************************************
*	picture channel [ͼ��ͨ��]
************************************************************************/

/* record type - timer, motion detect, alarm [¼�����ͣ���ʱ����̬��⡢����] */
typedef enum _REC_TYPE
{
	RV_REC_TYPE_TIM = 0,
	RV_REC_TYPE_MTD,
	RV_REC_TYPE_ALM,
	RV_REC_TYPE_NUM,
}REC_TYPE;

/* struct of time slice [ʱ��νṹ] */															    
typedef struct 
{
	BOOL	bEnable;	//if it is meaning record time slice, flag three enable by bits, they are motion detect record, alarm record, common record from low bit to high bit [����ʾ¼��ʱ���ʱ����λ��ʾ����ʹ�ܣ��ӵ�λ����λ�ֱ��ʾ����¼�󡢱���¼����ͨ¼��]
	int		iBeginHour;
	int		iBeginMin;
	int		iBeginSec;
	int		iEndHour;
	int		iEndMin;
	int		iEndSec;
} RV_TSECT, *LPRV_TSECT;

/* area:every edge by 8192 rate [����:���߾ఴ����8192�ı���] */
typedef struct {
	long		left;
	long		top;
	long		right;
	long		bottom;
} RV_RECT,*LPRV_RECT;

/* attributes struct of OSD [OSD���Խṹ] */
typedef struct  tagENCODE_WIDGET
{
	DWORD		rgbaFrontground;		/*!< object's fore RGB and transparency [�����ǰ��RGB����͸����] */
	DWORD		rgbaBackground;			/*!< object's back RGB and transparency [����ĺ�RGB����͸����] */
	RV_RECT		rcRect;					/*!< position [λ��] */
	BYTE		bShow;					/*!< show object [�����ʾ] */
	BYTE		byReserved[3];
} RV_ENCODE_WIDGET, *LPRV_ENCODE_WIDGET;

/* attributes of channel's audio and video [ͨ������Ƶ����] */
typedef struct 
{
	//video params [��Ƶ����]
	BYTE	byVideoEnable;				/* videl enable : 1-open; 0-close [��Ƶʹ��:1���򿪣�0���ر�] */
	BYTE	byBitRateControl;			/* bit-stream control, reference to constant definition [��������,���ճ�������] */
	BYTE	byFramesPerSec;				/* frame rate [֡��] */
	BYTE	byEncodeMode;				/* code mode, reference to constant definition [����ģʽ,���ճ�������] */
	BYTE	byImageSize;				/* resolve params, reference to constant definition [�ֱ��ʲ�,���ճ�������] */
	BYTE	byImageQlty;				/* level 1-6 [����1-6] */
	WORD	wLimitStream;				/* limit stream params, range: 50~4*1024 (k) [����������, ��Χ��50~4*1024 (k)] */

	//audio params [��Ƶ����]
	BYTE	byAudioEnable;				/* audio enable : 1-open, 0-close [��Ƶʹ��:1���򿪣�0���ر�] */
	BYTE	wFormatTag;					/* code type, eg. PCM [�������ͣ���PCM] */
	WORD	nChannels;					/* audio channel number [������] */
	WORD	wBitsPerSample;				/* sample depth [�������] */		
	DWORD	nSamplesPerSec;				/* sample rate [������] */

	BYTE	bIFrameInterval;			/* frame number between I Frame, descripte the P frame number between two I frame, 0-149 [I֡���֡��������������I֮֡���P֡������0-149]*/
	char	reserved;
} RV_VIDEOENC_OPT, *LPRV_VIDEOENC_OPT;

/* attributes of picture color [������ɫ����] */
typedef struct 
{
	RV_TSECT	stSect;
	BYTE		byBrightness;			/*! brightness 0-100 [����	0-100]*/
	BYTE		byContrast;				/*! contrast 0-100 [�Աȶ�	0-100]*/
	BYTE		bySaturation;			/*!	saturation 0-100 [���Ͷ�	0-100]*/
	BYTE		byHue;					/*!	hue 0-100 [ɫ��	0-100]*/
	BYTE		byGainEn;				/*! gain enable [����ʹ��]	 */ 
	BYTE		byGain;					/*! gain 0-100 [����	0-100]*/
	BYTE		byReserved[2];
} RV_COLOR_CFG, *LPRV_COLOR_CFG;

/* attibutes struct of picture channel [ͼ��ͨ�����Խṹ��] */
typedef struct 
{
	DWORD				dwSize;
	char				szChannelName[RV_CHAN_NAME_LEN];
	RV_VIDEOENC_OPT		stMainVideoEncOpt[RV_REC_TYPE_NUM];
	RV_VIDEOENC_OPT		stAssiVideoEncOpt[RV_N_ENCODE_AUX];		
	RV_COLOR_CFG		stColorCfg[RV_N_COL_TSECT];
	RV_ENCODE_WIDGET	stTimeOSD;
	RV_ENCODE_WIDGET	stChannelOSD;
	RV_ENCODE_WIDGET	stBlindCover[RV_N_COVERS];
	BYTE				byBlindEnable;			/*! switch of area shelter 0x00 not enable shelter, 0x01 only shlter device local preview, 0x10 only shelter record(and network preview), 0x11 both shelter [�����ڸǿ��ء�0x00��ʹ���ڸǣ�0x01���ڸ��豸����Ԥ����0x10���ڸ�¼�񣨼�����Ԥ������0x11���ڸ�]	*/
	BYTE				byBlindMask;			/*! mask of area shelter bit0:device local preview, bit1:record(and network preview) [�����ڸ�����  ��һλ���豸����Ԥ�����ڶ�λ��¼��(������Ԥ��)] */
	BYTE				byReserved[2];
} DHDEV_CHANNEL_CFG, *LPDHDEV_CHANNEL_CFG;


/************************************************************************
*	configure of area shelter [�����ڵ�����]
************************************************************************/
typedef struct __VIDEO_COVER_ATTR
{
	RV_RECT				rcBlock;			// overwritten area coordinate [���ǵ���������]
	int					nColor;				// overwritten color [���ǵ���ɫ]
	BYTE				bBlockType;			// overwritten method:0-black block,1-mosaic [���Ƿ�ʽ��0-�ڿ飬1-������]
	BYTE				bEncode;			// shelter in code level,1-valid,0-invalid [���뼶�ڵ�, 1����Ч, 0��������]
	BYTE				bPriview;           // preview shelter,1-valid,0-invalid [Ԥ���ڵ�, 1����Ч, 0������Ч]
	char				reserved[29];		// reserved [����]
}VIDEO_COVER_ATTR;

typedef struct __DHDEV_VIDEOCOVER_CFG 
{
	DWORD				dwSize;
	char				szChannelName[RV_CHAN_NAME_LEN];		//read-only [ֻ��]
	BYTE				bTotalBlocks;							//supported shelter block number [֧�ֵ��ڵ�����]
	BYTE				bCoverCount;							//setted shelter block number [�����õ��ڵ�����]
	VIDEO_COVER_ATTR	CoverBlock[RV_MAX_VIDEO_COVER_NUM];		//overwritten area [���ǵ�����]	
	char				reserved[30];							//reserved [����]
}DHDEV_VIDEOCOVER_CFG;


/************************************************************************
*	preview picture params [Ԥ��ͼ�����]
************************************************************************/

/* preview picture params [Ԥ��ͼ�����] */
typedef struct 
{
	DWORD dwSize;
	RV_VIDEOENC_OPT	stPreView;
	RV_COLOR_CFG  stColorCfg[RV_N_COL_TSECT];
}DHDEV_PREVIEW_CFG;

/************************************************************************
* audio attributes struct of audio talk - invalid, wait to be extended [�����Խ���Ƶ���Խṹ�壭δʵ�֣�����չ] *
************************************************************************/

typedef struct 
{
	//params for audio input [��Ƶ�������]
	BYTE	byInFormatTag;					//code type, eg.PCM [�������ͣ���PCM]
	BYTE	byInChannels;					//audio channel number [������]
	WORD	wInBitsPerSample;				//sample depth [�������]					
	DWORD	dwInSamplesPerSec;				//sample rate [������]

	//params for audio output [��Ƶ�������]
	BYTE	byOutFormatTag;					//code type, eg.PCM [�������ͣ���PCM]
	BYTE	byOutChannels;					//audio channel number [������]
	WORD	wOutBitsPerSample;				//sample depth [�������]				
	DWORD	dwOutSamplesPerSec;				//sample rate [������]
} DHDEV_TALK_CFG, *LPDHDEV_TALK_CFG;

/************************************************************************
*	timer record [��ʱ¼��]
************************************************************************/

typedef struct 
{
	DWORD		dwSize;
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];
	BYTE		byPreRecordLen;					/*! pre-record time, unit is second, 0 means not pre-record [Ԥ¼ʱ��,��λ��s,0��ʾ��Ԥ¼]*/
	BYTE		byRedundancyEn;					/*! record redundancy switch [¼�����࿪��]*/
	BYTE		byReserved[2];
} DHDEV_RECORD_CFG, *LPRV_RECORD_CFG;

/************************************************************************
*	alarm configure [��������]
************************************************************************/

typedef struct 
{
	int iType;
	int iValue;
} RV_PTZ_LINK, LPRV_PTZ_LINK;

typedef struct 
{
	/******************************************************************************
	** configure of message trigger [��Ϣ��������]
	**
	** if device occur messages, eg. occuer one input-alarm message, or video lost message, need to deal it [���豸������Ϣ,Ʃ�����һ�����뱨��,������Ƶ��ʧʱ,��Ҫ����Ӧ�Ĵ���.]
	** here we define how to deal with one message [�˴�������δ���һ����Ϣ]
	*****************************************************************************/

	/* deal method for messages, can combine these values, include [��Ϣ����ʽ,����ͬʱ���ִ���ʽ,����]
	* 0x00000001 - network:send to manage server [����:�ϴ����������]
	* 0x00000002 - record:trigger [¼��:����]
	* 0x00000004 - PTZ lingage [��̨����]
	* 0x00000008 - send email [�����ʼ�]
	* 0x00000010 - device local alarm tour [�豸���ر�����Ѳ]
	* 0x00000020 - device prompt enable [�豸��ʾʹ��]
	* 0x00000040 - device alarm output enable [�豸�������ʹ��]
	* 0x00000080 - Ftp upload enable [Ftp�ϴ�ʹ��]
	* 0x00000100 - beep [����]
	* 0x00000200 - audio prompt [������ʾ]
	* 0x00000400 - snapshot enable [ץͼʹ��]*/

	/*supported deal method for current alarm message, mark by bits [��ǰ������֧�ֵĴ���ʽ����λ�����ʾ]*/
	DWORD		dwActionMask;

	/*trigger action, by bit mask, real action needed params stored in every configure [������������λ�����ʾ�����嶯������Ҫ�Ĳ����ڸ��Ե�����������]*/
	DWORD		dwActionFlag;

	/*triggered output ports, alarm message triggered output, 1 means trigger this output [�������������ͨ��,�������������,Ϊ 1 ��ʾ���������]  */ 
	BYTE		byRelAlarmOut[RV_MAX_ALARMOUT_NUM];
	DWORD		dwDuration;		/* alarm duration [��������ʱ��] */

	/*linage to record [����¼��]*/
	BYTE		byRecordChannel[RV_MAX_VIDEO_IN_NUM];		/*alarm triggered record channel, 1 means trigger this channel [����������¼��ͨ��,Ϊ1��ʾ������ͨ��] */
	DWORD		dwRecLatch;		/*record duration [¼�����ʱ��] */

	/*snapshot channels [ץͼͨ��]*/
	BYTE		bySnap[RV_MAX_VIDEO_IN_NUM];
	/*tour channels [��Ѳͨ��]*/
	BYTE		byTour[RV_MAX_VIDEO_IN_NUM];

	/*PTZ linkage [��̨����]*/
	RV_PTZ_LINK	struPtzLink[RV_MAX_VIDEO_IN_NUM];
	DWORD		dwEventLatch;   /*!<linkage started delay time, unit is second, range is 0-15, default is 0 [������ʼ��ʱʱ�䣬sΪ��λ ��Χ��0����15 Ĭ��ֵ��0]*/
	/*alarm message triggered wireless output channel, alarm triggered output, 1 means triggered this output [�����������������ͨ��,�������������,Ϊ 1 ��ʾ���������]  */ 
	BYTE		byRelWIAlarmOut[RV_MAX_ALARMOUT_NUM];
	BYTE		bMessageToNet;	//message upload network enable [��Ϣ�ϴ�������ʹ��]
	BYTE		byReserved[111];       
} RV_MSG_HANDLE;

/* out-alarm [�ⲿ����] */
typedef struct
{
	BYTE		byAlarmType;							/*alarm type, 0:always closed;1:always opened [����������,0������,1������]  */
	BYTE		byAlarmEn;								/*alarm enable [����ʹ��]*/
	BYTE		byReserved[2];						
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;							/*deal method [����ʽ]  */
} RV_ALARMIN_CFG,*LPDHDEV_ALARMIN_CFG; 

/* motion detect alarm [��̬��ⱨ��] */
typedef struct 
{
	BYTE			byMotionEn;									/*motin detect alarm enable [��̬��ⱨ��ʹ��]*/
	BYTE			byReserved;
	WORD			wSenseLevel;								/*sensitivity [������]*/
	WORD			wMotionRow;									/*line number of motion detect [��̬������������] */
	WORD			wMotionCol;									/*column number of motion detect [��̬������������] */
	BYTE			byDetected[RV_MOTION_ROW][RV_MOTION_COL];	/*detect area, max 32*32 areas [����������32*32������]*/
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];			//NSP
	RV_MSG_HANDLE	struHandle;									/*deal method [����ʽ]*/
}RV_MOTION_DETECT_CFG;

/*video lost alarm [��Ƶ��ʧ����] */
typedef struct
{
	BYTE			byAlarmEn;								/*video lost alarm enable [��Ƶ��ʧ����ʹ��]*/
	BYTE			byReserved[3];
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;								/*deal method [����ʽ]  */
} RV_VIDEO_LOST_CFG;

/*picture shelter alarm [ͼ���ڵ�����] */
typedef struct
{
	BYTE			byBlindEnable;						/*enable [ʹ��] */
	BYTE			byBlindLevel;						/*sensitivity 1-6 [������1-6] */
	BYTE			byReserved[2];
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;							/*deal method [����ʽ]  */
} RV_BLIND_CFG;

/*disk message(inner alarm) [Ӳ����Ϣ(�ڲ�����)] */
typedef struct 
{
	BYTE				byNoDiskEn;									/*alarm on no disk [��Ӳ��ʱ����] */
	BYTE				byReserved_1[3];
	RV_TSECT			stNDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struNDHandle;								/*deal method [����ʽ]  */

	BYTE				byLowCapEn;									/*alarm on low disk space [Ӳ�̵�����ʱ����]*/
	BYTE				byLowerLimit;								/*space threshold value [������ֵ 0-99]*/
	BYTE				byReserved_2[2];
	RV_TSECT			stLCSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struLCHandle;								/*deal method [����ʽ]  */

	BYTE				byDiskErrEn;								/*alarm on disk error [Ӳ�̹��ϱ���]*/
	BYTE				byReserved_3[3];
	RV_TSECT			stEDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struEDHandle;								/*deal method [����ʽ]  */

} RV_DISK_ALARM_CFG;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	RV_MSG_HANDLE		struHandle;
} RV_NETBROKEN_ALARM_CFG;

//struct of IP conflict [IP��ͻ�����ṹ��]
typedef struct  
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	RV_MSG_HANDLE		struHandle;
}RV_IPCONFLICT_ALARM_CFG;

/*alarm guard [��������] */
typedef struct
{
	DWORD dwSize;

	RV_ALARMIN_CFG 		struLocalAlmIn[RV_MAX_ALARM_IN_NUM];
	RV_ALARMIN_CFG		struNetAlmIn[RV_MAX_ALARM_IN_NUM];
	RV_MOTION_DETECT_CFG struMotion[RV_MAX_VIDEO_IN_NUM];
	RV_VIDEO_LOST_CFG	struVideoLost[RV_MAX_VIDEO_IN_NUM];
	RV_BLIND_CFG		struBlind[RV_MAX_VIDEO_IN_NUM];
	RV_DISK_ALARM_CFG	struDiskAlarm;
	RV_NETBROKEN_ALARM_CFG	struNetBrokenAlarm;
	//	RV_SOUND_ALARM_CFG	struSoundAlarm[RV_MAX_VIDEO_IN_NUM];
	//maybe there are other device exceptions [���ܻ����豸�쳣]
} DHDEV_ALARM_SCHEDULE;

typedef struct  
{
	DWORD dwSize;
	RV_IPCONFLICT_ALARM_CFG	struIPConflict;
} DHDEV_ALARM_IPCONFLICT;

/*intelligent DVR SAVIA alarm [����DVR SAVIA����] */
typedef struct
{
	long			iIntelEnable;							/*enable [ʹ��] */
	unsigned long	iIntelIPaddr;							/*ip address [ip��ַ] */
	BYTE			byReserved[4];
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;								/*deal method [����ʽ]  */
} RV_SAVIA_ALARM;
typedef struct
{
	long			iSaviaNum;							//Savia number [Savia��Ŀ]
	RV_SAVIA_ALARM	stSaviaAlarm[RV_MAX_SAVIA_NUM];		//Savia alarm configure [Savia��������]
} RV_SAVIA_ALARM_SCHEDULE;

/*nlack and white ip list [�ڰ�����] */
typedef struct
{
	DWORD			dwSize;								//size of struct [�ṹ���С]
	BOOL			bEnable;							//IP authority configure enable [IPȨ������ʹ��]
	LONG			iBlackCount;						//black IP number [��������Ŀ]
	DWORD			dwBlackIP[RV_MAX_BLACK_IP_NUM];		//black IPs [������IP]
	LONG			iWhiteCount;						//white IP number [��������Ŀ]
	DWORD			dwWhiteIP[RV_MAX_WHITE_IP_NUM];		//white IPs [������IP]
} RV_BLACKWHITE_CFG;

/*decoder configure [����������] */
typedef struct
{
	int				channel;					//local decode channel index, start with 0 [���ؽ���ͨ����, ��0��ʼ]
	unsigned short	device_type;				//device type, 0-visiondigi device, 4-VS300 connection, 3-RTSP [�豸����, 0-��Ǭ�豸 ,4-VS300����,3-RTSP]
	unsigned short	device_port;				//front device's port [����ǰ���豸�˿�]
	unsigned int	device_ip;					//front device's ip, stored in network bytes storage [�����ֽ��򴢴�, ���ӵ�ǰ���豸ip]
	unsigned int	device_channel;				//remote channel index [Զ��ͨ����]
	unsigned int	enable;						//enable switch [ʹ�ܿ���]
	unsigned int	stream_type;				//type of connection type, 0-main stream [������������,0-������]
	char			username[128];				//front device's user name [����ǰ���û���]
	char			password[128];				//connection password [��������]
	//
	unsigned char	ucAVEnable;					//0:only decode video, 1:only decode audio, 2:decode audio and video, decode none is not allowed [0,ֻ����Ƶ 1��ֻ����Ƶ ��2 ������Ƶ ��������ʲô������]
	unsigned char	ucRemotePtzPreset;			//remote preset [Զ��Ԥ�õ�]
	unsigned char	ucRemotePtzPresetEnable;	//if set remote preset on connected [�Ƿ�һ�����Ͼ�����Զ��Ԥ�õ�]   
	unsigned char	ucRes;
	unsigned char	ucUrl[256];					//this is valid in rtsp mode, eg. rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx [rtspģʽ�´�������Ч,��ʽ�磺rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx]
	int				iDecodePolicy;				//decode plot (-2:most real-time; -1:real-time; 0:default; 1:fluency; 2:most fluency) it will extend to self define delay time [������� 	(-2, ��ʵʱ -1 ʵʱ 0 Ĭ����� 1 ���� 2,	������ ) �Ժ������չ���Զ���������ʱʱ��]
	unsigned char	ucRes1[124];
}RV_CFG_DECODE_T;
typedef struct
{
	DWORD			dwSize;
	long			iDecoderNumber;
	RV_CFG_DECODE_T	struDecoder[RV_MAX_DECODER_CHAN_NUM];
}RV_DECODER_CFG;

/************************************************************************
*	network configure [��������]
************************************************************************/
/*                                                                      */
/*ethernet configure [��̫������]*/
typedef struct 
{
	char	sDevIPAddr[RV_MAX_IPADDR_LEN];			/* DVR IP address [DVR IP ��ַ]  */ 
	char	sDevIPMask[RV_MAX_IPADDR_LEN];			/* DVR IP address mask [DVR IP ��ַ����]  */ 
	char	sGatewayIP[RV_MAX_IPADDR_LEN];			/* gateway address [���ص�ַ]  */ 

	/* 10M/100M [10M/100M self adapting, index [����Ӧ,����] 
	* 1-10MBase - T [1-10MBase - T]
	* 2-10MBase-T FDX [2-10MBase-T ȫ˫��] 
	* 3-100MBase - TX [3-100MBase - TX]
	* 4-100M  FDX [4-100M ȫ˫��]
	* 5-10M/100M self adapting [5-10M/100M  ����Ӧ] 
	*/
	//seperate DWORD to four for extend [Ϊ����չ��DWORD����ĸ�]
	BYTE	dwNetInterface;							/* NSP */
	BYTE	bTranMedia;								/* 0:wired;1:wireless [0������ 1������] */
	BYTE	bValid;									/* flag by bits, bit0:valid; 0:invalid, bit1:0:DHCP closed;1:DHCP enable, bit2:0:not support DHCP;1:support DHCP [��λ��ʾ����һλ��1����Ч 0����Ч���ڶ�λ��0��DHCP�ر� 1��DHCPʹ�ܣ�����λ��0����֧��DHCP 1��֧��DHCP] */
	BYTE	bDefaultEth;							/* if treat it as the default net-card, 1:default;0:not default [�Ƿ���ΪĬ�ϵ����� 1��Ĭ�� 0����Ĭ��] */
	char	byMACAddr[RV_MACADDR_LEN];				/* MAC address, read-only [MAC��ַ��ֻ��] */
} RV_ETHERNET; 

/* remote host configure [Զ����������] */
typedef struct 
{
	BYTE	byEnable;								/* connection enable [����ʹ��]  */
	BYTE	byReserved;
	WORD	wHostPort;								/* remote host : port [Զ������ �˿�]  */
	char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* remote host : IP address [Զ������ IP ��ַ]  */ 		
	char	sHostUser[RV_MAX_HOST_NAMELEN];			/* remote host : user name [Զ������ �û���] */ 
	char	sHostPassword[RV_MAX_HOST_PSWLEN];		/* remote host : password [Զ������ ����] */ 
}RV_REMOTE_HOST;

/* remote host configure (length of password is 64 bytes) [Զ����������(����64�ֽ�)] */
typedef struct 
{
	BYTE	byEnable;								/* connection enable [����ʹ��]  */
	BYTE	byReserved;
	WORD	wHostPort;								/* remote host : port [Զ������ �˿�]  */
	char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* remote host : IP address [Զ������ IP ��ַ]  */ 		
	char	sHostUser[RV_MAX_HOST_NAMELEN];			/* remote host : user name [Զ������ �û���] */ 
	char	sHostPassword[RV_MAX_HOST_PSWLEN_EX];	/* remote host : password [Զ������ ����] */ 
}RV_REMOTE_HOST_EX;

/* email configure [�ʼ�����] */
typedef struct 
{
	char	sMailIPAddr[RV_MAX_IPADDR_LEN];			/*IP address of email server [�ʼ�������IP��ַ]*/
	WORD	wMailPort;								/*port of email server [�ʼ��������˿�]*/
	WORD	wReserved;								/*reserved [����]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender address [���͵�ַ]*/
	char	sUserName[RV_MAX_NAME_LEN];				/*user name [�û���]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user password [�û�����]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*Dest address [Ŀ�ĵ�ַ]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*Cc address [���͵�ַ]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*Bcc address [������ַ]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*title [����]*/
}RV_MAIL_CFG;

/*struct of network configure [�������ýṹ��]*/
typedef struct
{ 
	DWORD				dwSize; 

	char				sDevName[RV_MAX_NAME_LEN];				/* device host name [�豸������]*/

	WORD				wTcpMaxConnectNum;						/* max TCP connection number (generaly means video data request number) [TCP���������(һ��ָ��Ƶ����������)]*/
	WORD				wTcpPort;								/* TCP listen port [TCP֡���˿�]*/
	WORD				wUdpPort;								/* UDP listen port [UDP�����˿�]*/
	WORD				wHttpPort;								/* HTTP port [HTTP�˿ں�]*/
	WORD				wHttpsPort;								/* HTTPS port [HTTPS�˿ں�]*/
	WORD				wSslPort;								/* SSL port [SSL�˿ں�]*/
	RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];		/* ethernet port [��̫����]*/ 

	RV_REMOTE_HOST		struAlarmHost;							/* alarm server [����������]*/
	RV_REMOTE_HOST		struLogHost;							/* log server [��־������]*/
	RV_REMOTE_HOST		struSmtpHost;							/* SMTP server [SMTP������]*/
	RV_REMOTE_HOST		struMultiCast;							/* multicast group [�ಥ��]*/
	RV_REMOTE_HOST		struNfs;								/* NFS server [NFS������]*/
	RV_REMOTE_HOST		struPppoe;								/* PPPoE server [PPPoE������]*/
	char				sPppoeIP[RV_MAX_IPADDR_LEN];			/* returned IP by PPPOE register [PPPoEע�᷵�ص�IP]*/
	RV_REMOTE_HOST		struDdns;								/* DDNS server [DDNS������]*/
	char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS host [DDNS������]*/
	RV_REMOTE_HOST		struDns;								/* DNS server [DNS������]*/
	RV_MAIL_CFG			struMail;								/* email configure [�ʼ�����] */
} DHDEV_NET_CFG;

/*struct of network configure [�������ýṹ��]*/
typedef struct
{ 
	DWORD				dwSize; 
	
	char				sDevName[RV_MAX_NAME_LEN];				/* device host name [�豸������] */
	
	WORD				wTcpMaxConnectNum;						/* max TCP connection number (generaly means video data request number) [TCP���������(һ��ָ��Ƶ����������)] */
	WORD				wTcpPort;								/* TCP listen port [TCP֡���˿�] */
	WORD				wUdpPort;								/* UDP listen port [UDP�����˿�] */
	WORD				wHttpPort;								/* HTTP port [HTTP�˿ں�] */
	WORD				wHttpsPort;								/* HTTPS port [HTTPS�˿ں�] */
	WORD				wSslPort;								/* SSL port [SSL�˿ں�]*/
	RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];		/* ethernet port [��̫����]  */ 
	
	RV_REMOTE_HOST_EX		struAlarmHost;						/* alarm server [����������] */
	RV_REMOTE_HOST_EX		struLogHost;						/* log server [��־������] */
	RV_REMOTE_HOST_EX		struSmtpHost;						/* SMTP server [SMTP������] */
	RV_REMOTE_HOST_EX		struMultiCast;						/* multicast group [�ಥ��] */
	RV_REMOTE_HOST_EX		struNfs;							/* NFS server [NFS������] */
	RV_REMOTE_HOST_EX		struPppoe;							/* PPPPoE server [PPPoE������] */
	char				sPppoeIP[RV_MAX_IPADDR_LEN];			/* returned IP by PPPOE register [PPPoEע�᷵�ص�IP] */
	RV_REMOTE_HOST_EX		struDdns;							/* DDNS server [DDNS������] */
	char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS host [DDNS������]*/
	RV_REMOTE_HOST_EX		struDns;							/* DNS server [DNS������]*/
	RV_MAIL_CFG			struMail;								/* email configure [�ʼ�����] */
} DHDEV_NET_CFG_RHEX;

/************************************************************************
*	serial port configure [��������]
************************************************************************/

/* basic attributs of serial port [���ڻ�������] */
typedef struct
{
	BYTE	byDataBit;		//data bit 0-5,1-6,2-7,3-8 [����λ 0-5,1-6,2-7,3-8]
	BYTE	byStopBit;		//stop bit 0-1bit, 1-1.5bits, 2-2bits [ֹͣλ 0-1λ, 1-1.5λ, 2-2λ] 
	BYTE	byParity;		//verify bit 0-no, 1-odd, 2-even [У��λ 0-no, 1-odd, 2-even] 
	BYTE	byBaudRate;		//{0-300,1-600,2-1200,3-2400,4-4800
							// 5-9600,6-19200,7-38400,8-57600,9-115200} 
} RV_COMM_PROP;

/* 485 decoder configure [485����������] */
typedef struct
{ 
	RV_COMM_PROP	struComm;

	BYTE			wProtocol;			/*protocal type, save the index of protocal, dynamicly change [Э������ ����Э����±꣬��̬�仯] */
	BYTE			byReserved;			/*reserved [����]  */	
	BYTE			wDecoderAddress;	/*decoder address : 0 - 255 [��������ַ:0 - 255]*/ 
	BYTE 			byMartixID;			/*matrix No. [�����]*/
} RV_485_CFG; 

/* 232 seial port configure [232��������] */
typedef struct
{
	RV_COMM_PROP	struComm;
	BYTE			byFunction;/*serial port function, corresponding function name list got from serial port configure [���ڹ��ܣ���Ӧ��������ȡ���Ĺ������б�]*/
	BYTE			byReserved[3];
} RV_RS232_CFG;

/* struct of serial port configure [�������ýṹ��] */
typedef struct
{
	DWORD			dwSize;
	//decoder protocal [������Э��]
	DWORD			dwDecProListNum;										//number of protocal [Э�����]
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN];	//protocal name list [Э�����б�]
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM];							//current attributs of every decoder [����������ǰ����]

	DWORD			dw232FuncNameNum;										//number of 232 function [232���ܸ���]
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];			//function name list [�������б�]
	RV_RS232_CFG	st232[RV_MAX_232_NUM];									//current attributs of every 232 serial port [��232���ڵ�ǰ����]
} DHDEV_COMM_CFG;


/************************************************************************
*	auto mantance configure [�Զ�ά������]
***********************************************************************/
/* attributes of auto mantance [�Զ�ά������] */
typedef struct
{
	DWORD dwSize;

	//auto reboot [�Զ�����]
	BYTE byAutoRebootDay;		// 0-never, 1-every day, 2-every sunday, 3-every monday, etc... [0-�Ӳ�, 1-ÿ��, 2-ÿ������, 3-ÿ����һ,.....]
	BYTE byAutoRebootTime;		// 0-0:00 1-1:00,........23-:23:00 */
	//autoly delete files [�Զ�ɾ���ļ�]
	BYTE byAutoDeleteFilesTime; // 0-never, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH [0-�Ӳ�, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH] */

	BYTE reserved[13];			// reserved [����λ]
} DHDEV_AUTOMT_CFG;

/************************************************************************
* configure of local machine's matrix control plot [����������Ʋ�������]
************************************************************************/

typedef struct
{
	BOOL		bTourEnable;			//	tour enable [��Ѳʹ��]
	int			nTourPeriod;			//	tour time slice, unit is second, 5-300 [��Ѳ�������λ��, 5-300] 
	DWORD		dwChannelMask;			//	tour channel, by mask [��Ѳ��ͨ����������ʽ��ʾ]
	char		reserved[64];
}RV_VIDEOGROUP_CFG;

typedef struct
{
	DWORD	dwSize;
	int		nMatrixNum;									//matrix number (read-only) [�������(ע���������޸�)]
	RV_VIDEOGROUP_CFG struVideoGroup[RV_MATRIX_MAXOUT];
	char	reserved[32];
}DHDEV_VIDEO_MATRIX_CFG;   

/************************************************************************
*	multi DDNS configure struct [��ddns���ýṹ��]
************************************************************************/

typedef struct
{
	DWORD	dwId;									//ddns server's id No. [ddns������id��]
	BOOL	bEnable;								//enable, only one ddns server can be enabled in the same time [ʹ�ܣ�ͬһʱ��ֻ����һ��ddns����������ʹ��״̬]
	char	szServerType[RV_MAX_SERVER_TYPE_LEN];	//server type [���������ͣ�ϣ��..]
	char	szServerIp[RV_MAX_DOMAIN_NAME_LEN];		//server ip or domain [������ip��������]
	DWORD	dwServerPort;							//server port [�������˿�]
	char	szDomainName[RV_MAX_DOMAIN_NAME_LEN];	//dvr domain, eg. jeckean.3322.org [dvr��������jeckean.3322.org]
	char	szUserName[RV_MAX_HOST_NAMELEN];		//user name [�û���]
	char	szUserPsw[RV_MAX_HOST_PSWLEN];			//password [����]
	char	szAlias[RV_MAX_DDNS_ALIAS_LEN];			//server's other name, eg. "RV inter ddns" [��������������"RV inter ddns"]
	DWORD	dwAlivePeriod;							//DDNS alive time slice [DDNS ����ʱ��]
	char	reserved[256];
}RV_DDNS_SERVER_CFG;

typedef struct
{
	DWORD	dwSize;
	DWORD	dwDdnsServerNum;	
	RV_DDNS_SERVER_CFG struDdnsServer[RV_MAX_DDNS_NUM];	
}DHDEV_MULTI_DDNS_CFG;


/************************************************************************
*   struct of email [�ʼ����ýṹ��]
************************************************************************/
typedef struct 
{
	char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*email server address (IP or domain) [�ʼ���������ַ(IP��������)]*/
	char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
	WORD	wMailPort;								/*email server port [�ʼ��������˿�]*/
	WORD	wSubMailPort;
	WORD	wReserved;								/*reserved [����]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender's address [���͵�ַ]*/
	char	sUserName[RV_MAX_NAME_LEN];				/*user name [�û���]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user's password [�û�����]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*dest address [Ŀ�ĵ�ַ]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*cc address [���͵�ַ]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*bcc address [������ַ]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*subject [����]*/
	BYTE	bEnable;//ʹ��0:false,	1:true
	char	reserved[255];
} DHDEV_MAIL_CFG;

/************************************************************************
*   extend struct of email [�ʼ����ýṹ����չ]
************************************************************************/
typedef struct 
{
	char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*email server address (IP or domain) [�ʼ���������ַ(IP��������)]*/
	char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
	WORD	wMailPort;								/*emial server's port [�ʼ��������˿�]*/
	WORD	wSubMailPort;
	WORD	wReserved;								/*reserved [����]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender's address [���͵�ַ]*/
	char	sUserName[RV_MAX_NAME_LEN_EX];			/*user name [�û���]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user's password [�û�����]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*dest address [Ŀ�ĵ�ַ]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*cc address [���͵�ַ]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*bcc address [������ַ]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*subject [����]*/
	BYTE	bEnable;								//enalbe, 0:dalse, 1:true [ʹ��0:false,	1:true]
	char	reserved[255];
} DHDEV_MAIL_CFG_EX;

/************************************************************************
*   version information of device's software [�豸����汾��Ϣ]
************************************************************************/
typedef struct  
{
	char	szDevSerialNo[RV_DEV_SERIALNO_LEN];		//serial number [���к�]
	char	byDevType;								//device type, reference to enum DHDEV_DEVICE_TYPE [�豸���ͣ���ö��DHDEV_DEVICE_TYPE]
	char	szDevType[RV_DEV_TYPE_LEN];				//device's detail type, string fromat, maybe null [�豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��]
	int		nProtocalVer;							//protocal version [Э��汾��]
	char	szSoftWareVersion[RV_MAX_URL_LEN];
	DWORD	dwSoftwareBuildDate;
	char	szDspSoftwareVersion[RV_MAX_URL_LEN];
	DWORD	dwDspSoftwareBuildDate;
	char	szPanelVersion[RV_MAX_URL_LEN];
	DWORD	dwPanelSoftwareBuildDate;
	char	szHardwareVersion[RV_MAX_URL_LEN];
	DWORD	dwHardwareDate;
	char	szWebVersion[RV_MAX_URL_LEN];
	DWORD	dwWebBuildDate;
	char	reserved[256];
} DHDEV_VERSION_INFO;


/************************************************************************
*   ability description of DSP [DSP��������]
************************************************************************/
typedef struct 
{
	DWORD	dwVideoStandardMask;		//mask of video sandard, flag supported video standard by bits [��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ]
	DWORD	dwImageSizeMask;			//mask of resolve, flag supported resolve by bits [�ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ�������]
	DWORD	dwEncodeModeMask;			//mask of code mode, flag supported code mode by bits [����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ����	]

	DWORD	dwStreamCap;				//flag supported multivideo by bits [��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�]
										//bit0:support main stream [��һλ��ʾ֧��������]
										//bit1:support assist stream1 [�ڶ�λ��ʾ֧�ָ�����1]
										//bit2:support assist stream2 [����λ��ʾ֧�ָ�����2]
										//bit4:support snapshot by jpg [����λ��ʾ֧��jpgץͼ]
	DWORD	dwImageSizeMask_Assi[32];	//mask of assist stream's supported resolve, corresponding every resolve of main stream [��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣]

	DWORD	dwMaxEncodePower;			//max code ability of DSP [DSP ֧�ֵ���߱������� ]
	WORD	wMaxSupportChannel;			//max video channel number of every DSP [ÿ�� DSP ֧�����������Ƶͨ���� ]
	WORD	wChannelMaxSetSync;			//if the max code configure be synchonous, 0-be not synchonous, 1-be synchonous [DSP ÿͨ���������������Ƿ�ͬ�� 0-��ͬ��, 1-ͬ��]

	BYTE	bMaxFrameOfImageSize[32];	//max sample rate in every resolve, corresponding dwVideoStandardMask by bits [��ͬ�ֱ����µ����ɼ�֡�ʣ���dwVideoStandardMask��λ��Ӧ]
	BYTE	bEncodeCap;					//0:code ability of main stream + code ability of assist stream <= code ability of device [0���������ı�������+�������ı������� <= �豸�ı���������]
										//1:code ability of main stream + code ability of assist stream <= code ability of device [1���������ı�������+�������ı������� <= �豸�ı���������]
										//code ability of assist stream <= code ability of main stream [�������ı������� <= �������ı���������]
										//resolve of assist stream < resolve of main stream [�������ķֱ��� <= �������ķֱ��ʣ�]
										//frame rate of main stream and assist stream <= sample rate of front device [�������͸�������֡�� <= ǰ����Ƶ�ɼ�֡��]

	char	reserved[95];
} DHDEV_DSP_ENCODECAP, *LPDHDEV_DSP_ENCODECAP;


/************************************************************************
*   configure of snapshot fucntion [ץͼ��������]
************************************************************************/
typedef struct 
{
	DWORD	dwSize;
	BOOL	bTimingEnable;						//switch of timer snapshot (switch of timer snapshot for alarm is showed in alarm linkage) [��ʱץͼ���أ�����ץͼ�����ڸ������������������֣�]
	RV_VIDEOENC_OPT struSnapEnc[SNAP_TYP_NUM];	//snapshot code configure, support it's resolve, picture quality, frame rate is negtive here to mean how many pictures snapshoted once [ץͼ�������ã���֧�����еķֱ��ʡ����ʡ�֡�����ã�֡���������Ǹ�������ʾһ��ץͼ�Ĵ�����]
}DHDEV_SNAP_CFG;

/************************************************************************
*   web path configure [web·������]
************************************************************************/
typedef struct 
{
	DWORD	dwSize;
	BOOL	bSnapEnable;					//if snapshot [�Ƿ�ץͼ]
	int		iSnapInterval;					//snapshot timer [ץͼ����]
	char	szHostIp[RV_MAX_IPADDR_LEN];	//HTTP host's IP [HTTP����IP]
	WORD	wHostPort;
	int		iMsgInterval;					//state messgae sending time slice [״̬��Ϣ���ͼ��]
	char	szUrlState[RV_MAX_URL_LEN];		//state message upload URL [״̬��Ϣ�ϴ�URL]
	char	szUrlImage[RV_MAX_URL_LEN];		//picture upload Url [ͼƬ�ϴ�Url]
	char	szDevId[RV_MAX_DEV_ID_LEN];		//local machine's web No. [������web���]
	BYTE	byReserved[2];
}DHDEV_URL_CFG;

/************************************************************************
*   picture watermark configure [ͼ��ˮӡ����]
************************************************************************/
typedef struct __DHDEV_WATERMAKE_CFG 
{
	DWORD				dwSize;
	int					nEnable;								//	enable [ʹ��]
	int					nStream;								//	bit stream (1~n) 0-all stream [������1��n��0-��������]
	int					nKey;									//	data type (1-text, 2-picture) [��������(1-���֣�2-ͼƬ)]
	char				szLetterData[RV_MAX_WATERMAKE_LETTER];	//	text [����]
	char				szData[RV_MAX_WATERMAKE_DATA];			//	picture data [ͼƬ����]
	BYTE				bReserved[512];							//	reserved [����]
} DHDEV_WATERMAKE_CFG;

/************************************************************************
*   FTP upload configure [FTP�ϴ�����]
************************************************************************/
typedef struct
{
	struct
	{
		RV_TSECT	struSect;	//"enable" is invalid in this time slice, can be ignored [��ʱ����ڵġ�ʹ�ܡ���Ч���ɺ���]
		BOOL		bMdEn;		//upload motion detect record [�ϴ���̬���¼��]
		BOOL		bAlarmEn;	//upload out-alarm record [�ϴ��ⲿ����¼��]
		BOOL		bTimerEn;	//upload common timer record [�ϴ���ͨ��ʱ¼��]
		DWORD		dwRev[4];
	} struPeriod[RV_TIME_SECTION];
}RV_FTP_UPLOAD_CFG;

typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;									//enable [�Ƿ�����]
	char				szHostIp[RV_MAX_IPADDR_LEN];				//host's IP [����IP]
	WORD				wHostPort;									//host's port [�����˿�]
	char				szDirName[RV_FTP_MAX_PATH];					//FTP folder path [FTPĿ¼·��]
	char				szUserName[RV_FTP_USERNAME_LEN];			//usr name [�û���]
	char				szPassword[RV_FTP_PASSWORD_LEN];			//password [����]
	int					iFileLen;									//file length [�ļ�����]
	int					iInterval;									//time slice between files [�����ļ�ʱ����]
	RV_FTP_UPLOAD_CFG	struUploadCfg[RV_MAX_CHANNUM][RV_N_WEEKS];
	char 				protocol;									//0-FTP 1-SMB
	char				NASVer;										//version of network store server, 0-old FTP(show time slice in UI), 1-NAS store(hidden time slice in UI) [����洢�������汾0=�ϵ�FTP����������ʾʱ��Σ�,1=NAS�洢������������ʱ��Σ�]
	BYTE 				reserved[128];
}DHDEV_FTP_PROTO_CFG;

// DNS server configure [DNS����������]
typedef struct  
{
	char				szPrimaryIp[RV_MAX_IPADDR_LEN];
	char				szSecondaryIp[RV_MAX_IPADDR_LEN];
	char				reserved[256];
}DHDEV_DNS_CFG;


/************************************************************************
*   record download plot configure [¼�����ز�������]
************************************************************************/
typedef struct
{
	DWORD dwSize;

	BOOL bEnable;	//TRUE - high speed download, FALSE - common download [TRUE���������أ�FALSE-��ͨ����]
}DHDEV_DOWNLOAD_STRATEGY_CFG;

/************************************************************************
*   network transport plot configure [���紫���������]
************************************************************************/
typedef struct
{
	DWORD dwSize;

	BOOL bEnable;
	int  iStrategy;	//picture quality first, 1-fluency first, 2-auto [0-�������ȣ� 1-���������ȣ� 2-�Զ���]
}DHDEV_TRANSFER_STRATEGY_CFG;


/************************************************************************
*	configure of IPC [IPC��һЩ����]
************************************************************************/
//	configure of wireless network [��������������Ϣ]
typedef struct 
{
	int					nEnable;			// enable wireless [����ʹ��]
	char				szSSID[36];			// SSID
	int					nLinkMode;			// connection mode 0:adhoc 1:Infrastructure [����ģʽ 0:auto 1:adhoc 2:Infrastructure]
	int					nEncryption;		// encrypt 0: off  2:WEP64bit 3: WEP128bit [���� 0: off 2:WEP64bit 3: WEP128bit]
	int					nKeyType;			// 0:Hex 1:ASCII
	int					nKeyID;				// serial number [���]
	char				szKeys[4][32];		// four group password [��������]
	int					nKeyFlag;
	char				reserved[12];
} DHDEV_WLAN_INFO;

//	select some wireless device [ѡ��ʹ��ĳ�������豸]
typedef struct  
{
	char				szSSID[36];
	int					nLinkMode;			// connection mode 0:adhoc 1:Infrastructure [����ģʽ 0:adhoc 1:Infrastructure]
	int 				nEncryption;		// encrypt 0: off  2:WEP64bit 3: WEP128bit [���� 0: off  2:WEP64bit 3: WEP128bit]
	char				reserved[48];
} DHDEV_WLAN_DEVICE;

//	found wireless device list [�������������豸�б�]
typedef struct  
{
	DWORD				dwSize;
	BYTE				bWlanDevCount;		// number of found wireless device [�������������豸����]
	DHDEV_WLAN_DEVICE	lstWlanDev[RV_MAX_WLANDEVICE_NUM];
	char				reserved[255];
} DHDEV_WLAN_DEVICE_LIST;

//	configure params of auto registration [����ע���������]
typedef struct  
{
	char				szServerIp[32];		//auto register server's IP [ע�������IP]
	int					nServerPort;		//port [�˿ں�]
	char				reserved[64];
} DHDEV_SERVER_INFO;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bServerNum;         //supported max ip number [֧�ֵ����ip��]
	DHDEV_SERVER_INFO	lstServer[RV_MAX_REGISTER_SERVER_NUM];
	BYTE				bEnable;			//enable [ʹ��]
	char				szDeviceID[32];		//device's id [�豸id��]
	char				reserved[94];
} DHDEV_REGISTER_SERVER;

//	attributs of cameral [����ͷ����]
typedef struct __DHDEV_CAMERA_INFO
{
	BYTE				bBrightnessEn;		// if brightness can be adjusted, 1:can, 0:can't [���ȿɵ� 1���ɣ�0������]
	BYTE				bContrastEn;		// if contrast can be adjusted[�Աȶȿɵ�]
	BYTE				bColorEn;			// if hue can be adjusted[ɫ�ȿɵ�]
	BYTE				bGainEn;			// if gain can be adjusted[����ɵ�]
	BYTE				bSaturationEn;		// if saturation can be adjusted[���Ͷȿɵ�]
	BYTE				bBacklightEn;		// if backlight compensation can be adjusted[���ⲹ���ɵ�]
	BYTE				bExposureEn;		// if exposure selection can be adjusted[�ع�ѡ��ɵ�]
	BYTE				bColorConvEn;		// if auto transform between "multi color" and "black and white"  can be adjusted[�Զ��ʺ�ת���ɵ�]
	BYTE				bAttrEn;			// attributs option, 1:can, 0:can't [����ѡ�� 1���ɣ�0������]
	BYTE				bMirrorEn;			// mirrorimage, 1:support, 0:not support [���� 1��֧�֣�0����֧��]
	BYTE				bFlipEn;			// reversal, 1:support, 0:not support [��ת 1��֧�֣�0����֧��]
	BYTE				bRev[125];			// reserved [����]
} DHDEV_CAMERA_INFO;

//	attributes configure of cameral [����ͷ��������]
typedef struct __DHDEV_CAMERA_CFG 
{
	DWORD				dwSize;
	BYTE				bExposure;			//exposure mode 1-9:manual exposure level; 0:auto exposure [�ع�ģʽ 1-9:�ֶ��ع�ȼ�; 0:�Զ��ع�]
	BYTE				bBacklight;			//backlight compensation 3:hard, 2:middle, 1:weak, 0:closed [���ⲹ�� 3:ǿ��2���У�1������ 0:��]
	BYTE				bAutoColor2BW;		//day/night mode 2:opened, 1:auto, 0:closed [��/ҹģʽ 2:����1���Զ�; 0:��]
	BYTE				bMirror;			//mirrorimage, 1:opened, 0:closed [����  1 ���� 0��]
	BYTE				bFlip;				//reversal, 1:opened, 0:closed [��ת  1 ���� 0��]
	char				bRev[123];			//reserved [����]
} DHDEV_CAMERA_CFG;

#define ALARM_MAX_NAME 64
//(wireless) infrayed alarm configure [(����)���ⱨ������]
typedef struct
{
	BOOL				bEnable;							//alarm input enable [��������ʹ��]
	char				szAlarmName[RV_MAX_ALARM_NAME];		//alarm input name [������������]
	int					nAlarmInPattern;					//alarm input wave [���������벨��]
	int					nAlarmOutPattern;					//alarm output wave [�����������]
	char				szAlarmInAddress[RV_MAX_ALARM_NAME];//alarm input address [���������ַ]
	int					nSensorType;						//out device's sensor type : always opened or always closed [�ⲿ�豸���������ͳ��� or ����]
	int					nDefendEfectTime;					//ally delay time, alarm input is valid after this time [��������ʱʱ�䣬�ڴ�ʱ���ñ���������Ч]
	int					nDefendAreaType;					//area type [�������� ]
	int					nAlarmSmoothTime;					//alarm smooth time, means, if there are two alarm input occured in this time, ignored the second [����ƽ��ʱ�䣬���ڴ�ʱ�������ֻ��һ��������������������������Ե�����һ��]
	char				reserved[128];

	RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];
	RV_MSG_HANDLE		struHandle;							//deal method [����ʽ]
} RV_INFRARED_INFO;

//wireless remote control configure [����ң��������]
typedef struct 
{
	BYTE  address[ALARM_MAX_NAME];							// address of remote control [ң������ַ]
	BYTE  name[ALARM_MAX_NAME];								// name of remote control [ң��������]
	BYTE  reserved[32];										// reserved [�����ֶ�]
}RV_WI_CONFIG_ROBOT;

//wireless alarm output configure [���߱����������]
typedef struct 
{
	BYTE  address[ALARM_MAX_NAME];							//alarm output address [���������ַ]
	BYTE  name[ALARM_MAX_NAME];								//alarm output name [�����������]
	BYTE  reserved[32];										//reserved [�����ֶ�]
}RV_WI_CONFIG_ALARM_OUT;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bAlarmInNum;						//number wireless alarm input [���߱���������]
	BYTE				bAlarmOutNum;						//number of wireless alarm out [���߱��������]
	RV_WI_CONFIG_ALARM_OUT AlarmOutAddr[16];				//address of alarm output [���������ַ]
	BYTE				bRobotNum;							//number of remote control [ң��������]
	RV_WI_CONFIG_ROBOT RobotAddr[16];						//address of remote control [ң������ַ]
	RV_INFRARED_INFO	InfraredAlarm[16];
	char				reserved[256];
} RV_INFRARED_CFG;

//new audio detect alarm information [����Ƶ��ⱨ����Ϣ]
typedef struct {
	int channel;						//alarm channel No. [����ͨ����]
	int alarmType;						//alarm type,0-audio value low, 1-audio value high [��������0--��Ƶֵ���� 1---��Ƶֵ����]
	unsigned int volume;				//audio value [����ֵ]
	char 	reserved[256];
} NET_NEW_SOUND_ALARM_STATE;

typedef struct  
{
	int channelcount;                   //channel number of alarm [������ͨ������]
	NET_NEW_SOUND_ALARM_STATE  SoundAlarmInfo[RV_MAX_ALARM_IN_NUM];
}RV_NEW_SOUND_ALARM_STATE;

//new audio detect alarm configure [����Ƶ��ⱨ������]
typedef struct
{
	BOOL				bEnable;							//alarm input enable [��������ʹ��]
	int					Volume_min;							//min audio volumn [��������Сֵ]
	int					Volume_max;							//max audio volumn [���������ֵ]
	char				reserved[128];	
	RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];	
	RV_MSG_HANDLE		struHandle;							//deal method [����ʽ]
} RV_AUDIO_DETECT_INFO;

typedef struct  
{
	DWORD					dwSize;
	int						AlarmNum;
	RV_AUDIO_DETECT_INFO	AudioDetectAlarm[RV_MAX_ALARM_IN_NUM];
	char					reserved[256];
} RV_AUDIO_DETECT_CFG;

//struct of store position, set stand alone per channel, every channel can select every store type, include local, removable, remote store, now [�洢λ�����ýṹ�壬ÿͨ����������,ÿͨ������ѡ����ִ洢����, Ŀǰ��������, ���ƶ�, Զ�̴洢.]
typedef struct 
{
	DWORD 	dwSize;
	DWORD 	dwLocalMask;					//mask of local store, flag by bits : [���ش洢����  ��λ��ʾ��]
											//bit0:system pre-record [��һλ	ϵͳԤ¼]
											//bit1:timer record [�ڶ�λ	��ʱ¼��]
											//bit2:motion detect record [����λ	����¼��]
											//bit3:alarm record [����λ	����¼��]
											//bit4:card record [����λ	����¼��]
											//bit5:manual record [����λ	�ֶ�¼��]

	DWORD 	dwMobileMask;					//mask of removable store, store mask eg. local store mask [���ƶ��洢���� �洢�����籾�ش洢����]
	int  	RemoteType;						//remote store type, 0:Ftp, 1:Smb [Զ�̴洢���� 0: Ftp  1: Smb ]
	DWORD 	dwRemoteMask;					//remote store mask, store mask eg. local store mask [Զ�̴洢���� �洢�����籾�ش洢����]
	DWORD 	dwRemoteSecondSelLocal;			//local store mask on remote exception [Զ���쳣ʱ���ش洢����]
	DWORD 	dwRemoteSecondSelMobile;		//removable store mask on remote exception [Զ���쳣ʱ���ƶ��洢����]
	char 	SubRemotePath[MAX_PATH_STOR];	//remote folder, the length is 260 [Զ��Ŀ¼, ���г���Ϊ260]
	char	reserved[128];
}RV_STORAGE_STATION_CFG;

/************************************************************************
*   network snapshot configure [����ץ������]
************************************************************************/
typedef struct
{
	int					Offset;			//bit offset of flag bit [��־λ��λƫ��]
	int					Length;			//length of flag bit [��־λ�ĳ���]
	char				Key[16];		//value of flag bit [��־λ��ֵ]
} RV_SNIFFER_FRAMEID;

typedef struct 
{
	int					Offset;			//bit offset of flag bit [��־λ��λƫ��]
	int					Offset2;		//invalid now [Ŀǰû��Ӧ��]
	int					Length;			//length of flag bit [��־λ�ĳ���]
	int					Length2;		//invalid now [Ŀǰû��Ӧ��]
	char				KeyTitle[24];	//value of title [�����ֵ]
} RV_SNIFFER_CONTENT;

typedef struct 
{
	RV_SNIFFER_FRAMEID	snifferFrameId;								//every FRAME's ID option [ÿ��FRAME ID ѡ��]
	RV_SNIFFER_CONTENT	snifferContent[RV_SNIFFER_CONTENT_NUM];		//every FRAME's four capture package content [ÿ��FRAME��Ӧ��4��ץ������]
} RV_SNIFFER_FRAME;

//every captrue package corresponding configure struct [ÿ��ץ����Ӧ�����ýṹ]
typedef struct
{
	char				SnifferSrcIP[RV_MAX_IPADDR_LEN];			//src IP address of sniffer [ץ��Դ��ַ]		
	int					SnifferSrcPort;								//src port of sniffer [ץ��Դ�˿�]
	char				SnifferDestIP[RV_MAX_IPADDR_LEN]; 			//dest IP address of sniffer [ץ��Ŀ���ַ]
	int					SnifferDestPort;							//dest port of sniffer [ץ��Ŀ��˿�]
	char				reserved[28];								//reserved [�����ֶ�]
	RV_SNIFFER_FRAME	snifferFrame[RV_SNIFFER_FRAMEID_NUM];		//6 FRAME options [6��FRAME ѡ��]
	int					displayPosition;							//display position [��ʾλ��]
	int					recdChannelMask;							//channel mask [ͨ������]
} RV_ATM_SNIFFER_CFG;

typedef struct  
{
	DWORD dwSize;
	RV_ATM_SNIFFER_CFG SnifferConfig[4];
	char	reserved[256];											//reserved [�����ֶ�]
}DHDEV_SNIFFER_CFG;


/************************************************************************
*   OEM query [OEM��ѯ]
************************************************************************/
typedef struct  
{
	char				szVendor[RV_MAX_STRING_LEN];
	char				szType[RV_MAX_STRING_LEN];
	char				reserved[128];
}DHDEV_OEM_INFO;


/************************************************************************
*   NTP configure [NTP����]
************************************************************************/

typedef enum __RV_TIME_ZONE_TYPE
{
	RV_TIME_ZONE_0,				// {0, 0*3600,"GMT+00:00"}
	RV_TIME_ZONE_1,				// {1, 1*3600,"GMT+01:00"}
	RV_TIME_ZONE_2,				// {2, 2*3600,"GMT+02:00"}
	RV_TIME_ZONE_3,				// {3, 3*3600,"GMT+03:00"}
	RV_TIME_ZONE_4,				// {4, 3*3600+1800,"GMT+03:30"}
	RV_TIME_ZONE_5,				// {5, 4*3600,"GMT+04:00"}
	RV_TIME_ZONE_6,				// {6, 4*3600+1800,"GMT+04:30"}
	RV_TIME_ZONE_7,				// {7, 5*3600,"GMT+05:00"}
	RV_TIME_ZONE_8,				// {8, 5*3600+1800,"GMT+05:30"}
	RV_TIME_ZONE_9,				// {9, 5*3600+1800+900,"GMT+05:45"}
	RV_TIME_ZONE_10,			// {10, 6*3600,"GMT+06:00"}
	RV_TIME_ZONE_11,			// {11, 6*3600+1800,"GMT+06:30"}
	RV_TIME_ZONE_12,			// {12, 7*3600,"GMT+07:00"}
	RV_TIME_ZONE_13,			// {13, 8*3600,"GMT+08:00"}
	RV_TIME_ZONE_14,			// {14, 9*3600,"GMT+09:00"}
	RV_TIME_ZONE_15,			// {15, 9*3600+1800,"GMT+09:30"}
	RV_TIME_ZONE_16,			// {16, 10*3600,"GMT+10:00"}
	RV_TIME_ZONE_17,			// {17, 11*3600,"GMT+11:00"}
	RV_TIME_ZONE_18,			// {18, 12*3600,"GMT+12:00"}
	RV_TIME_ZONE_19,			// {19, 13*3600,"GMT+13:00"}
	RV_TIME_ZONE_20,			// {20, -1*3600,"GMT-01:00"}
	RV_TIME_ZONE_21,			// {21, -2*3600,"GMT-02:00"}
	RV_TIME_ZONE_22,			// {22, -3*3600,"GMT-03:00"}
	RV_TIME_ZONE_23,			// {23, -3*3600-1800,"GMT-03:30"}
	RV_TIME_ZONE_24,			// {24, -4*3600,"GMT-04:00"}
	RV_TIME_ZONE_25,			// {25, -5*3600,"GMT-05:00"}
	RV_TIME_ZONE_26,			// {26, -6*3600,"GMT-06:00"}
	RV_TIME_ZONE_27,			// {27, -7*3600,"GMT-07:00"}
	RV_TIME_ZONE_28,			// {28, -8*3600,"GMT-08:00"}
	RV_TIME_ZONE_29,			// {29, -9*3600,"GMT-09:00"}
	RV_TIME_ZONE_30,			// {30, -10*3600,"GMT-10:00"}
	RV_TIME_ZONE_31,			// {31, -11*3600,"GMT-11:00"}
	RV_TIME_ZONE_32,			// {32, -12*3600,"GMT-12:00"}
}RV_TIME_ZONE_TYPE;

typedef struct  
{
	BOOL				bEnable;			//	enable [�Ƿ�����]
	int					nHostPort;			//	NTP server's default port is 123 [NTP������Ĭ�϶˿�Ϊ123]
	char				szHostIp[32];		//	host's IP [����IP]
	char				szDomainName[128];	//	domain [����]
	int					nType;				//	can't set, 0:IP, 1:domain, 2:IP and domain [�������� 0����ʾIP��1����ʾ������2����ʾIP������]
	int					nUpdateInterval;	//	update time (minute) [����ʱ��(����)]
	int					nTimeZone;			//	reference to RV_TIME_ZONE_TYPE [��RV_TIME_ZONE_TYPE]
	char				reserved[128];
}DHDEV_NTP_CFG;


/************************************************************************
*   platform connection configure - U WANAG TONG [ƽ̨�������� �� U��ͨ]
************************************************************************/
typedef struct
{
	BOOL bChnEn;
	char szChnId[RV_INTERVIDEO_UCOM_CHANID];
}RV_INTERVIDEO_UCOM_CHN_CFG;

typedef struct
{
	DWORD dwSize;
	BOOL bFuncEnable;										//function enable 0 - enable [���빦��ʹ����� 0 - ʹ��]
	BOOL bAliveEnable;										//alive enable [����ʹ�����]
	DWORD dwAlivePeriod;									//heart cycle, unit is second 0-3600 [�������ڣ���λ�룬0-3600]
	char szServerIp[RV_MAX_IPADDR_LEN];						//CMS's IP [CMS��IP]
	WORD wServerPort;										//CMS's port [CMS��Port]
	char szRegPwd[RV_INTERVIDEO_UCOM_REGPSW];				//regiter password [ע������]
	char szDeviceId[RV_INTERVIDEO_UCOM_DEVID];				//device's id [�豸id]
	char szUserName[RV_INTERVIDEO_UCOM_USERNAME];
	char szPassWord[RV_INTERVIDEO_UCOM_USERPSW];
	RV_INTERVIDEO_UCOM_CHN_CFG  struChnInfo[RV_MAX_CHANNUM];//channel id,en [ͨ��id,en]
}DHDEV_INTERVIDEO_UCOM_CFG;

/************************************************************************
*   platform connection configure - alcater [ƽ̨�������� �� ��������]
************************************************************************/
typedef struct
{
	DWORD dwSize;
	unsigned short usCompanyID[2];		/* Corp. ID, value, different three part service Corp. consider 4 bytes justification, only use the first in array now [��˾ID,��ֵ,��ͬ�ĵ���������˾,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szDeviceNO[32];				/* serial number of front device, string, conrain '\0' total 32 bytes [ǰ���豸���кţ��ַ���, ����'\0'��������32byte] */
	char szVSName[32];					/* front device, string, contain '\0' total 16 bytes [ǰ���豸���ƣ��ַ���, ����'\0'��������16byte] */
	char szVapPath[32];					/* VAP path [VAP·��] */
	unsigned short usTcpPort;			/* TCP port, value : 1~65535 [TCP �˿�,��ֵ: ��ֵ 1~65535] */    
	unsigned short usUdpPort;			/* UDP port, value : 1~65535 [UDP �˿�,��ֵ: ��ֵ 1~65535] */    
	bool bCsEnable[4];					/* enable of center server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [���ķ�����ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szCsIP[16];					/* IP address of center server, string, contain '\0' total 16 bytes [���ķ�����IP��ַ, �ַ���, ����'\0'��������16byte] */
	unsigned short usCsPort[2];			/* port of center server, value : 1~65535, consider 4 bytes justification, only use the first in array now [���ķ������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ��] */    
	bool bHsEnable[4];					/* enable of heart beat server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [����������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szHsIP[16];					/* IP address of heart beat server, string, contain '\0' total 16 bytes [����������IP��ַ, �ַ���, ����'\0'��������16byte] */
	unsigned short usHsPort[2];			/* port of heart beat server, value : 1~65535, consider 4 bytes justification, only use the first in array now [�����������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ��] */ 
	int iHsIntervalTime;				/* time slice of heart beat server, value (unit:second) [�����������������,��ֵ(��λ:��)] */ 
	bool bRsEnable[4];					/* enable of registration server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [ע�������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szRsIP[16];					/* IP address of registration server, string, contain '\0' total 16 bytes [ע�������IP��ַ, �ַ���, ����'\0'��������16byte] */
	unsigned short usRsPort[2];			/* port of registration server, value : 1~65535, consider 4 bytes justification, only use the first in array now [ע��������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	int iRsAgedTime;					/* valid time of registration server, value (unit:hour) [ע���������Чʱ��,��ֵ(��λ:Сʱ)] */
	char szAuthorizeServerIp[16];		/* IP address of authority server [��Ȩ������IP] */
	unsigned short usAuthorizePort[2];  /* port of authority server, value : 1~65535, consider 4 bytes justification, only use the first in array now [��Ȩ�������˿�,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szAuthorizeUsername[32];		/* account of authority server [��Ȩ�������ʺ�] */
	char szAuthorizePassword[36];		/* password of authority server [��Ȩ����������] */

	char szIpACS[16];					/* ACS (auto registration server) IP [ACS(�Զ�ע�������) IP] */
	unsigned short usPortACS[2];		/* ACS port, consider 4 bytes justification, only use the first in array now [ACS Port,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szUsernameACS[32];				/* ACS user name [ACS�û���] */
	char szPasswordACS[36];				/* ACS password [ACS����] */
	bool bVideoMonitorEnabled[4];		/* if DVS timer to up-send message of fornt video signal watch, value : true enable, false not enable [DVS�Ƿ����ϱ�ǰ����Ƶ�źż����Ϣ, ��ֵ: trueʹ��, false��ʹ��] */
	int iVideoMonitorInterval;			/* up-send timer slice (minute) [�ϱ����ڣ����ӣ�] */

	char szCoordinateGPS[64];			/* GPS coordinate [GPS����] */
	char szPosition[32];				/* device position [�豸λ��] */
	char szConnPass[36];				/* device connection passport [�豸������] */
}DHDEV_INTERVIDEO_BELL_CFG;

/************************************************************************
*   configure of plartform connection - ZHONGXINGLIWEI [ƽ̨�������� �� ������ά]
************************************************************************/
typedef struct  
{
	DWORD dwSize;
	unsigned short		nSevPort;								//server port, value 1~65535 [�������˿�, ��ֵ, ��ֵ1~65535]
	char				szSevIp[RV_INTERVIDEO_NSS_IP];			//server IP address, string, contain '\0', total 32 bytes [������IP��ַ, �ַ���, ����'\0'��������32byte]
	char				szDevSerial[RV_INTERVIDEO_NSS_SERIAL];	//serial number of front device, string, contain '\0', total 32 bytes [ǰ���豸���кţ��ַ���,����'\0'��������32byte]
	char				szUserName[RV_INTERVIDEO_NSS_USER];
	char				szPwd[RV_INTERVIDEO_NSS_PWD];
}DHDEV_INTERVIDEO_NSS_CFG;

/************************************************************************
*   state information of network running [��������״̬��Ϣ]
************************************************************************/

typedef struct
{
	int					nChannelNum;	//channel No. [ͨ����]
	char				szUseType[32];	//channel usage [ͨ����;]
	DWORD				dwStreamSize;	//flow rate (unit is kb/s) [������С(��λ:kb/s)]
	char				reserved[32];	//reserved [����]
}DHDEV_USE_CHANNEL_STATE;

typedef struct 
{
	char						szUserName[32];				//user name [�û���]
	char						szUserGroup[32];			//user group [�û���]
	NET_TIME					time;						//logined time [����ʱ��]
	int							nOpenedChannelNum;			//opened channel number [������ͨ������]
	DHDEV_USE_CHANNEL_STATE		channelInfo[RV_MAX_CHANNUM];
	char						reserved[64];
}DHDEV_USER_NET_INFO;

typedef	struct 
{
	int							nUserCount;		//user count [�û�����]
	DHDEV_USER_NET_INFO			stuUserInfo[32];
	char						reserved[256];
}DHDEV_TOTAL_NET_STATE;
/************************************************************************
*   attributes of PTZ [��̨������Ϣ]
************************************************************************/
#define  NAME_MAX_LEN 16
typedef struct 
{
	DWORD		dwHighMask;				/*!< high bits of operation's mask [�����������λ] */
	DWORD		dwLowMask;				/*!< low bits of operation's mask [�����������λ] */
	char		szName[NAME_MAX_LEN];	/*!< operation's protocal name, NAME_MAX_LEN=16 [������Э����NAME_MAX_LEN=16] */
	WORD		wCamAddrMin;			/*!< channel address's min value [ͨ����ַ����Сֵ] */
	WORD		wCamAddrMax;			/*!< channel address's max value [ͨ����ַ�����ֵ] */
	WORD		wMonAddrMin;			/*!< watch address's min value [���ӵ�ַ����Сֵ] */
	WORD		wMonAddrMax;			/*!< watch address's max value [���ӵ�ַ�����ֵ] */
	BYTE		bPresetMin;				/*!< preset's min value [Ԥ�õ����Сֵ] */
	BYTE		bPresetMax;				/*!< preset's max value [Ԥ�õ�����ֵ] */
	BYTE		bTourMin;				/*!< auto tour's min value [�Զ�Ѳ����·����Сֵ] */
	BYTE		bTourMax;				/*!< auto tour's max value [�Զ�Ѳ����·�����ֵ] */
	BYTE		bPatternMin;			/*!< tour's min value [�켣��·����Сֵ] */
	BYTE		bPatternMax;			/*!< tour's max value [�켣��·�����ֵ] */
	BYTE		bTileSpeedMin;			/*!< vertical speed's min value [��ֱ�ٶȵ���Сֵ] */
	BYTE		bTileSpeedMax;			/*!< vertical speed's max value [��ֱ�ٶȵ����ֵ] */
	BYTE		bPanSpeedMin;			/*!< horizontal speed's min value [ˮƽ�ٶȵ���Сֵ] */
	BYTE		bPanSpeedMax;			/*!< horizontal speed's max value [ˮƽ�ٶȵ����ֵ] */
	BYTE		bAuxMin;				/*!< assist function's min value [�������ܵ���Сֵ] */
	BYTE		bAuxMax;				/*!< assist function's max value [�������ܵ����ֵ] */
	int			nInternal;				/*!< send command's time slice [���������ʱ����] */
	char		cType;					/*!< protocal's type [Э�������] */
	char		Reserved[7];
}PTZ_OPT_ATTR;
/************************************************************************
*   returned information of setting device [�����豸����Ϣ]
************************************************************************/
typedef struct
{
	DWORD		dwType;			//type, the same as type of GetDevConfig SetDevConfig [����(��GetDevConfig SetDevConfig������)]
	WORD		wResultCode;	//recturned code [�����룺]
								/*		0:success [�ɹ�]
								*		1:fail [ʧ��]
								*		2:data invalid [���ݲ��Ϸ�]
								*		3:can't set now [��ʱ�޷�����]	
								*		4:no authority [û��Ȩ��]
								*/

	WORD   		wRebootSign;	//reboot flag [������־��]
								/*
								*	0:no need to reboot, 1:need to reboot to make it valid [0:����Ҫ���� 1:��Ҫ��������Ч]
								*/
	DWORD		dwReserved[2];	//reserved [����]	
}DEV_SET_RESULT;

/******************************************************************************
* attributes struct of snapshot function [ץͼ�������Խṹ��]
*****************************************************************************/

typedef struct 
{
	int			nChannelNum;			//channel index [ͨ����]

	DWORD		dwVideoStandardMask	;	//resolve (by bit) detail reference to enum CAPTURE_SIZE [�ֱ���(��λ) ����鿴ö�� CAPTURE_SIZE]
	int			nFramesCount;			//valid length of [Frequence[128] array [Frequence[128]�������Ч����]
	char 		Frames[128];			//frame rate (by value) [֡�ʣ�����ֵ��]
										//-25:25 seconds per frame [-25:25��1֡]
										//-24:24 seconds per frame [-24:24��1֡]
										//-23:23 seconds per frame [-23:23��1֡]
										//-22:22 seconds per frame [-22:22��1֡]
										//����
										//0:valid [0:��Ч]
										//1:1 frames per second [1��1��1֡]
										//2:2 frames per second [2��1��2֡]
										//3:3 frames per second [3��1��3֡]
										//4:4 frames per second [4��1��4֡]
										//5:5 frames per second [5��1��5֡]
										//17:17 frames per second [17��1��17֡]
										//18:18 frames per second [18��1��18֡]
										//19:19 frames per second [19��1��19֡]
										//20:20 frames per second [20��1��20֡]
										//����
										//25:25 frames per second [25: 1��25֡]
	int			nSnapModeCount;			//valid length of SnapMode[16] array [SnapMode[16]�������Ч����]
	char		SnapMode[16];			//(by value) 0:timer snapshot 1:manual triggered snapshot [������ֵ�� 0����ʱ����ץͼ 1���ֶ�����ץͼ]
	int			nPicFormatCount;		//valid length of Format[16] array [Format[16]�������Ч����]
	char 		PictureFormat[16];		//by value 0:BMP format 1:JPG format [������ֵ��0:BMP��ʽ 1:JPG��ʽ]
	int			nPicQualityCount;		//valid length of Quality[32] array [Quality[32]�������Ч����]
	char 		PictureQuality[32];		//(by value) [������ֵ��]
										//100:picture quality 100% [100:ͼ������100%]
										//80:picture quality 80% [80:ͼ������80%]
										//60:picture quality 60% [60:ͼ������60%]
										//50:picture quality 50% [50:ͼ������50%]
										//30:picture quality 30% [30:ͼ������30%]
										//10:picture quality 10% [10:ͼ������10%]
	char 		nReserved[128];			//reserved [����]
} RV_QUERY_SNAP_INFO;

typedef struct 
{
	int			nChannelCount;					//channel number [ͨ������]
	RV_QUERY_SNAP_INFO  stuSnap[RV_MAX_CHANNUM];
}RV_SNAP_ATTR_EN;

typedef struct  
{
	int	iLen;			//real data lenght [ʵ�����ݳ���]
	int iChannel;		//channel index [ͨ����]
	char acData[32];	//real data [ʵ������]
}RV_PTZ_RAW_DATA_H;

/******************************************************************************
* attributes struct of auto registration function [����ע�Ṧ�����Խṹ��]
*****************************************************************************/

typedef struct
{
	DWORD	 dwSize;
	LONG     iEnable;			//enable [ʹ��]
	LONG     iConnectType;		//connection method, 0:single connection(using old command media single connection mode), 1:multi connections (commands auto register to server, media need to dynamicly reconnect to server under command control eg. case of video request) [���ӷ�ʽ��0�������ӣ�ʹ��ԭ�е�����ý�嵥һ����ģʽ�� 1�������� ����ȡ����Ϊ����ע�����ӣ�ý����Ҫ�������������Ƶ��������½����µĶ�̬���ӷ�ʽ��
	char	 strServerIp[16];	//ip of registration server [ע�������ip]	
	LONG     iServerPort;		//port of registration server [ע��������˿�]
	char     strUsr[64];		//user name [�û���]
	char     strPwd[64];		//password [����]
	char     strPuId[32];		//device identify, 32bits, recording to platform server definition [�豸ͳһ��ʶ��32λ��ʶ����ƽ̨������Լ��]
								/*
								rule of identify device [�豸ͳһ��ʶ����] 
								using 32 bytes now, details recording to platform server definition [����ʹ����32�ֽڣ�������Ϣ���ţ���ƽ̨������Լ������]
								
								Xx							yy						zz											a      								b						cccccccc cccccccc ccccccccc
								2 bytes	[2�ֽ�]				2 bytes	[2�ֽ�]			2 bytes	[2�ֽ�]								1 byte [1�ֽ�]     					1 byte [1�ֽ�]			24 bytes [24�ֽ�] 
								No. in province [ʡ�����]	No. in city [�м����]	reserved for No. in city [�м���ű�����]	front 0,client1 [ǰ�� 0���ͻ���1]	device type [�豸����]	device serial number [�豸���]
								
								values of device type : 01:DVR 02:IPC 03:NVS 04:decoder 05:DVR on vehicle [�����豸���� 01�� DVR�� 02 ��IPC ��03��NVS �� 04 ����������05������DVR]
								*/
}RV_CONFIG_REG_SERVER;

/******************************************************************************
* attributes struct of tour function [��Ѳ�������Խṹ��]
*****************************************************************************/
#define V_TOUR_COMBINE_NUM 10
typedef struct
{
	unsigned int iSplitMode;	//support many multi-views preview mode, flag by bits, reference to enum split_combine_t [֧�ֶ��ֻ���Ԥ��ģʽ����λ��ʶ���ο�ö��split_combine_t]
								//bit0 : SPLIT1, this is default in all devices, this is sinlg view and full screen [��0λ SPLIT1 ��Ĭ�϶�֧�֣���Ϊ�����棬ȫ��]
								//bit1 : SPLIT2 [��1λ SPLIT2] 
								//bit2 : SPLIT4 [��2λ SPLIT4]
								//bit3 : SPLIT8 [��3λ SPLIT8] 
								//bit4 : SPLIT9 [��4λ SPLIT9]
								//bit5 : SPLIT16 [��5λ SPLIT16] 
								//bit6 : SPLITIP [��6λ SPLITIP]
								//bit7 : SPLIT6 [��7λ SPLIT6] 
								//bit8 : SPLIT12 [��8λ SPLIT12]
}RV_SPLIT_MODE;
typedef struct
{
	unsigned char bTourEnable;		//enable [ʹ��]
	unsigned char ucRes;	
	unsigned short usIntervalTime;	//tour time slice [��Ѳʱ����]
}RV_DISPLAY_TOUR_CFG;
typedef struct
{
	DWORD	 dwSize;
	RV_DISPLAY_TOUR_CFG stDisplayTour;
	RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
}RV_DISPLAY_TOUR;

/******************************************************************************
* struct of views split function [����ָ�����Խṹ��]
*****************************************************************************/
typedef struct
{
	RV_SPLIT_MODE stSplitMode;		//mode [ģʽ]
	RV_SPLIT_COMBINE_CH stCombineCH;//channel combine [ͨ�����]
}RV_DISPLAY_SPLIT_CFG;

/******************************************************************************
* channel combine and tour struct of decoder views group [�������������ͨ������Լ���ѯ�ṹ��]
*****************************************************************************/
typedef struct
{
	DWORD	 dwSize;
	RV_DISPLAY_SPLIT_CFG stSplitCfg;
	RV_DISPLAY_TOUR_CFG stTourCfg;
	LONG iCombineNum;
	RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
}RV_WSCC;

/******************************************************************************
* struct of snapshot [ץͼ���ýṹ��]
*****************************************************************************/
#define MAX_SNAP_COUNT 32
typedef struct
{   	    	
	int iChannel;
	int Enable;					/*enable of timer snapshot [��ʱץ��ʹ��]*/
	int SnapQuality;			/*picture quality of snapshot, 6 levels, 1:bad, 2:not bad, 3:common, 4:good, 5:better, 6:best [ץ��ͼ��������������6���� 1 �� 2 һ�� 3��ͨ�� 4�ã� 5�ܺã� 6���]*/
								/*snap plot [ץͼ����]
								 usSnapMode : snapshot mode, 0 means mode of how many pictures per second [usSnapMode ץ��ģʽ�� 0 ��ʾ1�뼸��ģʽ]
															 1 means mode of how many seconds per picture [1 ��ʾ����1��ģʽ]
															 2 means mode of how many minutes per picture [2 ��ʾ������1��ģʽ]
								 usCounts : value corresponding snapshot mode [usCounts ��Ӧץ��ģʽ�µ���ֵ]
								*/
	unsigned short usSnapMode;
	unsigned short usCounts;	/*snapshot picture number (under mode of how many pictures per second) or snapshot time (mode of how many seconds per picture) [ץ��������1�뼸��ģʽ������ץ��ʱ�䣨����1��ģʽ��]*/
	int SnapCount;
}RV_CONFIG_SNAP;
typedef struct
{
	DWORD dwSize;
	DWORD dwCount;								//on setting:==channel count is all, >=0&&<channel count is which channel configure [����ʱ��==ͨ����Ϊ���У�>=0&&<ͨ����Ϊ�ĸ�ͨ������]
												//on getting:returned number [��ȡʱ�����ظ���]
	RV_CONFIG_SNAP stSnapCfg[MAX_SNAP_COUNT];
}RV_SNAP;

typedef struct
{
	unsigned short usTotal;  //total channel number [��ͨ����Ŀ]
	unsigned short usIndex;  //which channel's information [�ڼ���ͨ����Ϣ]
}RV_DEV_CHANNEL;

/******************************************************************************
* struct of decoder [�������������ýṹ��]
*****************************************************************************/
#define RV_N_UI_TSECT					6
#define RV_N_WEEKS						7
typedef struct
{
	int				enable;		    //enable [ʹ��]
	unsigned char	startHour; 		//start time : hour [��ʼʱ��:Сʱ]		
	unsigned char	startMinute;	//start time : minute [��ʼʱ��:����]		
	unsigned char	startSecond; 	//start time : second [��ʼʱ��:����]		
	unsigned char	endHour;		//end time : hour [����ʱ��:Сʱ]		
	unsigned char	endMinute; 		//end time : minute [����ʱ��:����]		
	unsigned char	endSecond; 		//end time : second [����ʱ��:����]		
	unsigned char   ucReserved[2];  //reserved [����]
}RV_NETSECTION;		
typedef struct
{
	int				iName;
	RV_NETSECTION	tsSchedule[RV_N_WEEKS][RV_N_UI_TSECT];	/*time slice [ʱ���]*/
}RV_NET_WORKSHEET;
#define RV_N_SYS_CH 16
typedef struct
{		
	unsigned int		dwRecord;				/* record mask [¼������] */
	int					iRecordLatch;			/* record delay : 10~300 second [¼����ʱ��10��300 sec] */ 	
	unsigned int		dwTour;					/* tour mask [��Ѳ����] */	
	unsigned int		dwSnapShot;				/* snapshot mask [ץͼ����] */
	unsigned int		dwAlarmOut;				/* alarm output channel mask [�������ͨ������] */
	int					iAOLatch;				/* alarm output delay : 10~300 second [���������ʱ��10��300 sec] */ 
	RV_PTZ_LINK			PtzLink[RV_N_SYS_CH];	/* PTZ linkage items [��̨������] */		
	int					bRecordEn;				/* record enable [¼��ʹ��] */
	int					bTourEn;				/* tour enable [��Ѳʹ��] */
	int					bSnapEn;				/* snapshot enable [ץͼʹ��] */	
	int					bAlarmOutEn;			/* alarm enable [����ʹ��] */
	int					bPtzEn;					/* PTZ linkage enable [��̨����ʹ��] */
	int					bTip;					/* screen prompt enable [��Ļ��ʾʹ��] */	
	int					bMail;					/* send email [�����ʼ�] */	
	int					bMessage;				/* send message to alarm center [������Ϣ����������] */	
	int					bBeep;					/* beep [����] */	
	int					bVoice;					/* audio prompt [������ʾ] */		
	int					bFTP;					/* lauch FTP transport [����FTP����] */		
	int					iWsName;				/* time table selection, because it is using number as index in time table, and will not be changed [ʱ����ѡ������ʱ�����ʹ���������������Ҳ������] */
	unsigned int		dwMatrix;				/* matrix mask [��������] */
	int					bMatrixEn;				/* matrix enable [����ʹ��] */
	int					bLog;					/* log enable, it is just be using in WTN motion detect [��־ʹ�ܣ�Ŀǰֻ����WTN��̬�����ʹ��] */
	int					iEventLatch;			/* linkage start delay time, second is unit [������ʼ��ʱʱ�䣬sΪ��λ] */
	int					bMessagetoNet;			/* send message to network enable [��Ϣ�ϴ�������ʹ��] */
	unsigned int		dwReserved[7]; 			/* reserved [�����ֽ�] */
}RV_EVENT_HANDLER;
typedef struct
{
	int iEnable;	//alarm guard enable, 0:disable, 1:enable [�澯�������� 0������1����]
	int iReserved;	//common configure, details as bellow [ͨ��������Ϣ�����嶨������]
					//in alarm input, this means sensor type, 0:always opened, 1:always closed [�澯�����ʶ���������ͳ��� or ���գ�0������1����]
					//in video lost and motion detect, this means sensitivity : 0~6 levels, level 6 is most sensitivity [��Ƶ��ʧ�Ͷ���Ϊ�����ȣ�0~6���Σ�6����Ϊ������]
					//in disk, this means the lowest limit of left space in disk, percent [����ΪӲ��ʣ����������, �ٷ���]
					//in intelligent red alarm, this means sensitivity : 0~6 levels, level 6 is most sensitivity [���ܺ�ɫ����Ϊ�����ȣ�0~6���Σ�6����Ϊ������]
}RV_ALARM_GUARD;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [����ʽ]
} RV_DECODER_ALARM,*LPRV_DECODER_ALARM;
 
typedef struct
{
	DWORD dwSize;		
	RV_DECODER_ALARM 		struDecoderAlarm[RV_MAX_DECODER_CHAN_NUM]; //16-32 ���ͨ����Ŀ zb
}RV_DECODER_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//	other alarm structs [���������ṹ]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [����ʽ]
} RV_GEN_ALARM; 
#define RV_MD_REGION_ROW	32
typedef struct
{
	int iRowNum;
	int iColNum;
	BYTE byRegion[32][32];
}RV_REGION;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_REGION				stRegion;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [����ʽ]
} RV_MOTION_ALARM; 
typedef struct
{
	DWORD dwSize;		
	RV_GEN_ALARM 		struLocalAlarmIn[RV_MAX_CHANNUM];
	RV_MOTION_ALARM		struMotionAlarm[RV_MAX_CHANNUM];
	RV_GEN_ALARM 		struVideoLossAlarm[RV_MAX_CHANNUM];
	RV_GEN_ALARM 		struVideoBindAlarm[RV_MAX_CHANNUM];
	RV_GEN_ALARM 		struNoDiskAlarm;
	RV_GEN_ALARM 		struDiskErrAlarm;
	RV_GEN_ALARM 		struDiskFullAlarm;
	RV_GEN_ALARM 		struNetBrokenAlarm;
	RV_GEN_ALARM 		struIPConflictAlarm;
}RV_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//	TV adjuest struct [TV���ڽṹ]
//////////////////////////////////////////////////////////////////////
typedef struct 
{
	int left;	//[0,100]
	int top;	//[0,100]
	int right;	//[0,100]
	int bottom;	//[0,100]
}RV_VD_RECT;
//TV adjust configure [TV��������]
typedef struct
{
	DWORD dwSize;
	RV_VD_RECT rctMargin;		//TV zoom out rate, every value's range are the same [0,100] [TV��С���ʣ�������ȡֵ��ͬ   [0,100]]		
	int iBrightness;			//brightness [0,100] [����[0,100]]		
	int iContrast;				//contrast [0,100] [�Աȶ�[0,100]]	
	int iAntiDither;			//antidither [0,100] [ȥ����[0,100]]
}RV_TVADJUST;

//////////////////////////////////////////////////////////////////////
//	common configure [��ͨ����]
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//	struct of daylight saving time [����ʱ�ṹ��]
typedef struct
{
	int Hour;
	int Minute;
}RV_DSTTIMES;
typedef struct
{
	int iYear;			//year [2000,2037]
	int iMonth;			//month from January=1 [1,12]
	int iWeek;			//week1:first  to2 3 4 -1:last one   0:calculate method by days [-1,4] [��1:first  to2 3 4 -1:last one   0:��ʾʹ�ð��ռ���ķ���[-1,4]]
	union
	{
		int iWeekDay;	//weekday from sunday=0 [0, 6]
		int iDays;		//day from one=1[0, 31]
	};	
	RV_DSTTIMES time;
}RV_DST_POINT;
//week mode selection [��ģʽѡ��]
//iMonth��iWeek(-1,1,2,3,4)�� iWeekDay��Hour��Min
//day mode selection, iWeek=0 [��ģʽѡ�� iWeek=0]
//iYear ,iMonth,iDays��Hour��Min
typedef struct
{
	RV_DST_POINT iDST[2];
	unsigned char ucEnable;//0:disable, 1:enable [0,��ʹ�ܣ�1ʹ��]
	unsigned char ucRes[3];//reserved [����] 
}RV_DST_TIME;
typedef struct
{ 		
	int  iCtrlMask;						/*flag by bit mask [��λ������ʽ]
										0 : deal on disk full, 1:OverWrite, 0:StopRecord [0 Ӳ����ʱ���� 1����"OverWrite", 0ֹͣ"StopRecord"] 
										1 : if mute [1 �Ƿ���]
										2 : LCD screen auto close [2 LCD��Ļ�Զ��ر�]
										3 : if TV output [3 �Ƿ�TV���]
										4 : if VGA output [4 �Ƿ�VGA���]
										5 : if HDMI output [5 �Ƿ�HDMI���]
										*/		
	int iLocalNo;						//local machine No. : [0,?998]? [�������:[0,?998]? ]
	unsigned short usScreenSaveTime;	//screen protection (minute) [0,120] [����ʱ��(����) [0, 120]	]
	unsigned short usAutoLogout;		//local menu auto logout (minute) [0, 120] [���ز˵��Զ�ע��(����) [0, 120]]
	unsigned char ucDateFormat;			//date format :"YYMMDD","MMDDYY","DDMMYY" [���ڸ�ʽ:��YYMMDD��, ��MMDDYY��, ��DDMMYY�� ]
	unsigned char ucDateSprtr;			//date seperate : ".","-","/" [���ڷָ��:��.��, ��-��, ��/��] 
	unsigned char ucTimeFmt;			//time format : 1:12, 0:24 [ʱ���ʽ:1����12��, 0����24��] 
	unsigned char ucRes;
	unsigned char ucSupportVideoFmt;	//device supported video standard, bit0:PAL, bit1:NTSC, bit2:SECAM [�豸����֧�ֵ���ʽ �� ��0λ PAL ����1λ NTSC�� ��2λ SECAM]
	unsigned char ucCurVideoFmt;		//device used video standard, 0:PAL, 1:NTSC, 2:SECAM [�豸ʹ�õ���ʽ ��0 PAL ��1 NTSC�� 2 SECAM]
	unsigned char ucRes1[2];
	unsigned int uiSupportLanguage;		//device supported languages [�豸����֧�ֵ����� �� ]
										//bit0:English, bit1:SimpChinese, bit2:TradChinese [��0λ English����1λ SimpChinese�� ��2λ TradChinese��]
										//bit3:Italian, bit4:Spanish, bit5:Japanese, bit6:Russian, bit7:French, bit8:German [��3λ ��Italian��,4 ��Spanish��, 5��Japanese��, 6��Russian��, 7��French��, 8��German�� ]
	unsigned int uiCurLanguage;			//device used languages [�豸ʹ�õ����� ��]
										//0:English, 1:SimpChinese, 2:TradChinese, 3:Italian, 4:Spanish [0 English��1 SimpChinese��2 TradChinese��3��Italian��,4 ��Spanish��,] 
										//5:Japanese, 6:Russian, 7:French, 8:German [5��Japanese��, 6��Russian��, 7��French��, 8��German��] 
	unsigned int uiRes[3];				//reserved [�����ֽ�]						
}RV_NET_GENERAL;

//2010-10-12 luhj add
typedef struct  
{
	char	cSize;						//�����С��1��ʾ��׼������2��ʾ2����С  ��ֵȡֵ��Χ��1��ucZoomAbility֮��
	char	cRes[3];					//����
}RV_OSDZOOM_PARAM;
//end
// system time struct [ϵͳʱ��ṹ]
typedef struct
{
	int  year;	//year [2000,2037] [�ꡣ[2000,2037]]   
	int  month;	//month January = 1, February = 2, and so on. [�£�January = 1, February = 2, and so on. ]  
	int  day;	//day [�ա�]   
	int  wday;	//week, Sunday = 0, Monday = 1, and so on [���ڣ�Sunday = 0, Monday = 1, and so on]   
	int  hour;	//hour [ʱ��]   
	int  minute;//minute [�֡�]  
	int  second;//second [�롣]   
	int  isdst;	//flag daylight saving time [����ʱ��ʶ��]   
}RV_SYSTEM_TIME;
#define RV_MAX_DRIVERINFO 64
typedef  struct
{
	DWORD dwSize;
	RV_NET_GENERAL stGeneral;
	RV_SYSTEM_TIME stCurTime;
	RV_DST_TIME stDst;
}RV_COMM_CFG;
//////////////////////////////////////////////////////////////////////
//	platform connection configure [ƽ̨��������]
//////////////////////////////////////////////////////////////////////
//platform of HUXINGHUTONG [���Ż�ͨƽ̨��������]
typedef struct
{
	DWORD dwSize;
	BOOL			Enable;			//enable [ʹ��]
	int				MaxConn;		//max connection number of video connection [��Ƶ���������]	
	char			ServerIp[40];	//server IP [������IP]	
	unsigned short	ServerPort;		//server Port [�������˿�]
	unsigned short	MegaPort;		//listen port [�����˿�]	
	char			DeviceId[32];	//device ID [�豸ID]	
	char			UserName[32];	//user name [�û���]
	char			PassWords[32];	//password [����]
	unsigned short	DownLoadMode;	//record download method by bits, 0:TCP, 1:HTXT [¼�����ط�ʽ��λ0 TCP 1 HTXT]
	unsigned short	FunMask;		/*function mask, operate by bits [�������룬��λ����]
									bit0:if support prediction scheme [��0λ�Ƿ�֧��Ԥ��]
									bit1:if support network management [��1λ�Ƿ�֧������]
									bit2:if support pre-record [��2λ�Ƿ�֧��Ԥ¼]
									bit3:if support NAT [��3λ�Ƿ�֧��NAT]
									*/	
	unsigned short	AlarmInterVal;	//alarm time slice [�������]
	unsigned short	Reserve;
}RV_CONFIG_NET_MEGA;
/************************************************************************
*   platform of ALCATEL [ƽ̨�������� �� ��������]
************************************************************************/
typedef struct
{
	DWORD dwSize;
	unsigned short usCompanyID[2];		/* Corp.ID, value, different three part service Corp. consider 4 bytes justification, using the first of the array [��˾ID,��ֵ,��ͬ�ĵ���������˾,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szDeviceNO[32];				/* serial number of front device, string, contain '\0', total 32 bytes [ǰ���豸���кţ��ַ���, ����'\0'��������32byte] */
	char szVSName[32];					/* name of front device, string, contain '\0', total 16 bytes [ǰ���豸���ƣ��ַ���, ����'\0'��������16byte] */
	char szVapPath[32];					/* VAP path [VAP·��] */
	unsigned short usTcpPort;			/* TCP port, value : 1~65535 [TCP �˿�,��ֵ: ��ֵ 1~65535] */    
	unsigned short usUdpPort;			/* UDP port, value : 1~65535 [UDP �˿�,��ֵ: ��ֵ 1~65535] */    
	bool bCsEnable[4];					/* enable flag of center server, consider 4 bytes justification, using the first of the array [���ķ�����ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szCsIP[64];					/* IP of center server, string, contain '\0', total 16 bytes [���ķ�����IP��ַ, �ַ���, ����'\0'��������16byte] */
	unsigned short usCsPort[2];			/* port of center server, consider 4 bytes justification, using the first of the array [���ķ������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ��] */    
	bool bHsEnable[4];					/* enable flag of heart beat server, consider 4 bytes justification, using the first of the array [����������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szHsIP[64];					/* IP of heart beat server, string, contain '\0', total 16 bytes [����������IP��ַ, �ַ���, ����'\0'��������16byte] */
	unsigned short usHsPort[2];			/* port of heart beat server, consider 4 bytes justification, using the first of the array [�����������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ��] */ 
	int iHsIntervalTime;				/* time slice of heart beat server, value (unit : second) [�����������������,��ֵ(��λ:��)] */ 
	bool bRsEnable[4];					/* enable flag of registration server, consider 4 bytes justification, using the first of the array [ע�������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szRsIP[64];					/* IP of registration server, string, contain '\0', total 16 bytes [ע�������IP��ַ, �ַ���, ����'\0'��������16byte] */
	unsigned short usRsPort[2];			/* port of registratin server, value : 1~65535, consider 4 bytes justification, using the first of the array [ע��������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	int iRsAgedTime;					/* valid time of registration server, value (unit:hour) [ע���������Чʱ��,��ֵ(��λ:Сʱ)] */
	char szAuthorizeServerIp[64];		/* IP of authority server [��Ȩ������IP] */
	unsigned short usAuthorizePort[2];  /* port of authority server, consider 4 bytes justification, using the first of the array [��Ȩ�������˿�,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szAuthorizeUsername[32];		/* account of authority server [��Ȩ�������ʺ�] */
	char szAuthorizePassword[36];		/* passsword of authority server [��Ȩ����������] */

	char szIpACS[64];					/* ACS (auto registration server) IP [ACS(�Զ�ע�������) IP] */
	unsigned short usPortACS[2];		/* ACS port, consider 4 bytes justification, using the first of the array [ACS Port,����4�ֽڶ���,Ŀǰֻ�������һ��] */
	char szUsernameACS[32];				/* ACS user name [ACS�û���] */
	char szPasswordACS[36];				/* ACS password [ACS����] */
	bool bVideoMonitorEnabled[4];		/* if DVS timer to upload the watch information of front video signal, value: true enable, false disable [DVS�Ƿ����ϱ�ǰ����Ƶ�źż����Ϣ, ��ֵ: trueʹ��, false��ʹ��] */
	int iVideoMonitorInterval;			/* upload timer slice (minute) [�ϱ����ڣ����ӣ�] */

	char szCoordinateGPS[64];			/* GPS coordinate [GPS����] */
	char szPosition[32];				/* device position [�豸λ��] */
	char szConnPass[36];				/* device connection passport [�豸������] */
}RV_INTERVIDEO_BELL_CFG;
//platform of VS300 [VS300ƽ̨����]
typedef struct
{
	DWORD dwSize;
	BOOL    BEnalbe;		//enable, 4 bytes, 0:disable, 1:enable [ʹ�� 4�ֽ� 0 ��ʹ�� 1 ʹ��]
	char    acServerIp[32];	//server ip [������ip]
	long	iServerPort;	//listen port of server [�����������˿�]
	char    acUserName[32];	//user name [�û���]
	char    acPassWords[32];//password [����]
	long	iType;			//protocal type, 0:tcp, 1:udp [Э������ 0 tcp 1 udp]
	char    acReserve[80];	//reserved [����λ]
}RV_CONFIG_VS300_NET;
//platform of SHENYAN [����ƽ̨��������]
typedef struct
{ 	
	DWORD dwSize;
	BOOL Enable;		//enable [�Ƿ���]
	char ServerIp[64];	//IP of SHENYAN Sserver [���۷�����IP]
	int ServerPort;		//port on SHENYAN server [���۷������˿ں�]
	char PUId[32];		//device ID [�豸ID]
	int  usTcpPort;		/*TCP port, value:1~65535 [�����TCP �˿�,��ֵ: ��ֵ 1~65535] */    
	int  usUdpPort;		/*UDP port, value:1~65535 [�����UDP �˿�,��ֵ: ��ֵ 1~65535] */    
	char strUsr[16];
	char strPwd[16];    
	char strVer[16];
	char Reserved[16];
}RV_CONFIG_ZXSHENYAN_NET;
//////////////////////////////////////////////////////////////////////
//	disk configure [��������]
//////////////////////////////////////////////////////////////////////
typedef struct
{	
	unsigned char ucUse;			//enable [�˷����Ƿ���Ч]	
	unsigned char ucPartion;		//partion index [�����ţ�]	
	unsigned char ucFSType;			//partion supported file systems [����֧�ֵ��ļ�ϵͳ]	
									//0:WFS file system, max support 2 partions, and the partion is restrict to 3 types as bellow [0 WFS�ļ�ϵͳ  �������֧��2�������ҷ�����Լ���������ַ�ʽ]	
									//if WFS2 partion, default is that, the first partion is for snapshot, and the second is for recording [WFS2�����Ļ���Ĭ�ϵ�1����Ϊ���շ�������2����Ϊ¼�����]	
									//if it is only one partion under WFS file system, it is decided by ucPartType [�����WFS 1�����Ļ�������ucPartType����]	
									//ucPartType==0,record partion; ucPartType==1,snapshot partion [ucPartType==0��¼�������ucPartType==1���շ���]	
									//now snapshot (store pictures) and the next record, device can only save one type of media [��ʱ���գ��洢ͼƬ������¼���豸ֻ�ܽ���һ��ý��Ĵ洢]	
									//WFS file system only can be used as percet 2 partion mode [WFS�ļ�ϵͳԼ��ֻ���ٷֱ�2����ģʽ]	
									//1 FAT32	
									//2 EXT3	
	unsigned char ucPartType;		//this is used by WFS file system pnly, 0:record partion, 1:snapshot partion, standard file system, not need, no limit [WFS�ļ�ϵͳ����ר�� 0 ¼�����  1���շ�������׼�ļ�ϵͳ������Ҫ��������]	
	unsigned int uiTotalSpace;		//< total space, it's unit reference to ucSpaceType introduction [< ���������䵥λ�ο�ucSpaceType˵��]	
	unsigned int uiRemainSpace;		//< left space, it's unit reference to ucSpaceType introduction [< ʣ���������䵥λ�ο�ucSpaceType˵��]	
	unsigned char ucSpaceType;		//identify disk space unit, convenient to more correct statistic [��ʶӲ��������λ������Ƚ�׼ȷ��ͳ��]	
									//the next 4 bits (7 6 5 4) total space unit 0 KB��1MB��2GB��3TB [��4λ��7  6 5 4 �� �ܴ�С��λ  0 KB��1MB��2GB��3TB]								
									//the first 4 bits (3 2 1 0) left space unit 0 KB��1MB��2GB��3TB [ǰ4λ��3 2 1 0�� ʣ���С��λ  0 KB��1MB��2GB��3TB]
	unsigned char ucReserve[3];
}RV_DISK_PARTION_INFO;
typedef struct
{
	unsigned char ucDiskNo;				//disk No. max 255 [�̷�,�ڼ���Ӳ�� ���255��]
	unsigned char ucCurrentUse;			//if currently using work disk [�Ƿ�ǰʹ�ù�����]
	unsigned char ucLocalStorage;		//local store or remote store media, 0:local, 1:remote [���ش洢����Զ�̴洢���� 0���� 1Զ��]
	unsigned char ucDiskType;			//disk media type,0:sata disk, 1:U disk, 3:sd card, 4:removable disk, 5:dvd CD [Ӳ�̽������� 0 sataӲ�� 1��U�̣�3 sd����4���ƶ�Ӳ�̣�5��dvd����]
	unsigned char ucErrorFlag;			//flag work disk error [�����̴����־]
	unsigned char ucPartMethod;			//supported partion mode [֧�ַ���ģʽ]
										//bit0: if support partion 0 not support 1 support [��0λ��ʾ�Ƿ�֧�ַ��� 0 ��֧�� 1֧��]
										//next seven bits flag supported partion type [����λ ��λ��ʶ֧�ַ�����ʽ] 
										//bit1: partion by percent 0 not support 1 support [��1λ ���հٷֱȷ��� 0 ��֧�� 1֧��]
										//bit2: partion by space MB 0 not support 1 support [��2λ ������������ MB  0 ��֧�� 1֧��]
										//bit3:	partion by space GB 0 not support 1 support [��3λ ������������ GB  0 ��֧�� 1֧��]
										//bit4: partion by space TB 0 not support 1 support [��4λ ������������ TB 0 ��֧�� 1֧��]
	unsigned char ucSupportPartionMax;  //supported max partion number of disk [֧��Ӳ������������]
	unsigned char ucSupportFileSystem;  //supported file systems, 0:WFS, 1:FAT32, 2:EXT3 [֧�ֵ��ļ�ϵͳ0 WFS 1 FAT32 2 EXT3]
	unsigned int uiTotalSpace;			//< total space, it's unit reference to ucSpaceType introduction [< ���������䵥λ�ο�ucSpaceType˵��]
	unsigned int uiRemainSpace;			//< left space, it's unit reference to ucSpaceType introduction [< ʣ���������䵥λ�ο�ucSpaceType˵��]
	unsigned char ucSpaceType;			//identify disk space unit, convenient to more correct statistic [��ʶӲ��������λ������Ƚ�׼ȷ��ͳ��]
										//the next 4 bits (7 6 5 4) total space unit 0 KB��1MB��2GB��3TB [��4λ��7  6 5 4 �� �ܴ�С��λ  0 KB��1MB��2GB��3TB]
										//the first 4 bits (3 2 1 0) left space unit 0 KB��1MB��2GB��3TB [ǰ4λ��3 2 1 0�� ʣ���С��λ  0 KB��1MB��2GB��3TB]
	unsigned char ucAttr;				//0 read-write(default), 1:read-only, 2:redundancy back-up [0 �ɶ�д ��Ĭ�ϣ���1ֻ���� 2 ���౸��]
	unsigned char ucRes1[2];			//reserved [����]
	RV_DISK_PARTION_INFO szPartion[4];
	unsigned char ucRes2[64];			//reserved [����]
}RV_DISK_INFO;
#define RV_MAX_DISK_NUM	16
typedef struct
{
	DWORD dwSize;
	DWORD dwCount;
	RV_DISK_INFO stDiskInfo[RV_MAX_DISK_NUM];
}RV_DISKS;
//disk operation [Ӳ�̲���]
typedef struct
{
	unsigned char ucDiskNo;         //disk No. max 255 [�̷�,�ڼ���Ӳ�� ���255��]
	unsigned char ucCtrlType;       //0:read-write(default), 1:read-only, 2:redundancy back-up, 3:format [0 �ɶ�д ��Ĭ�ϣ���1ֻ���� 2 ���౸�� ��3 ��ʽ��] 
									//4:sector error detect and restore [4 ����������ָ�]
									//5:repartion, data bellow is valid after disk repartion [5���·��������·����������ݲ���Ч]
	unsigned char ucRes[2];  

	/////valid data after repartion [���·�����Ч����]----------------------
	unsigned char ucFSType;		//0:WFS file system, max support 2 partions, and the partion is restrict to 3 types as bellow [0 WFS�ļ�ϵͳ  �������֧��2�������ҷ�����Լ���������ַ�ʽ]
								//if WFS2 partion, default is that, the first partion is for snapshot, and the second is for recording [WFS2�����Ļ���Ĭ�ϵ�1����Ϊ���շ�������2����Ϊ¼�����]
								//if it is only one partion under WFS file system, it is decided by ucPartType [�����WFS 1�����Ļ���ucPartType��ʾ¼������Ϳ��գ��洢ͼƬ��]
								//now the next one record, device can only save one type od media [��ʱ����¼���豸ֻ�ܽ���һ��ý��Ĵ洢]
								//WFS file system is restrict to seperate 2 partion by percent [WFS�ļ�ϵͳԼ��ֻ���ٷֱ�2����ģʽ]
								//1 FAT32
								//2 EXT3
	unsigned char ucPartType;	//this is only used by WFS file system, and used when only one partion, 0:record partion, 1:snapshot partion [WFS�ļ�ϵͳ����ר�� ֻ��һ��������ʱ���ʹ�� 0 ¼�����  1���շ���]
								//when it is seperate to 2 partions, default is that, the first is snapshot partion, the second is record partion, this value is invalid [WFS  ������ʱ��Ĭ�ϵ�1����Ϊ���շ�������2����Ϊ¼���������ֵ��Ч]
	unsigned char ucPartNum;	//partion number [��������]
	unsigned char ucPartMethod;	//disk partion method, 0:percent, 1:KB, 2:MB, 3:GB, 4:TB [Ӳ�̷�����ʽ�� 0 �ٷֱȣ�1 KB 2MB 3 GB 4 TB]
	unsigned int uiPartSpace[4];//every partion used spaces by partion method [���շ�����ʽ�����η�����ʹ�õ�����]
								//if by percent, eg. 50%-50% 2 partions [������հٷֱȣ����� 50%-50% 2������ ]
								//inner fill : 50��50, 0, 0��ucPartCtrlType== 2 ��ucPartNo ==2 [�ڲ����50��50, 0, 0��ucPartCtrlType== 2 ��ucPartNo ==2]
								//if fill by space MB partion method, eg. 1G disk, 200MB-300MB-100MB-400MB [�����������MB������ʽ������1G��Ӳ�̣�200MB-300MB-100MB-400MB��]
								//fill : 200��300��100��400��ucPartCtrlType== 2 ��ucPartNo ==4 [��ô������� 200��300��100��400��ucPartCtrlType== 2 ��ucPartNo ==4]
	unsigned int uiRes[6];  
}RV_CTRL_DISK_INFO;
//disk partion , format and error correct operation [Ӳ�̷������и�ʽ���Լ��޸�����]
typedef struct
{
	unsigned char ucDiskNo;				//disk No. max 255 [�̷�,�ڼ���Ӳ�� ���255��]
	unsigned char ucPartCtrlType;		//0:format, 1 partion sector detect error correct [0 ��ʽ����1������������޸�]
	unsigned char ucPartNo;				//ucPartCtrlType==0,1 do format, sector detect restore with the ucPartNo partion [ucPartCtrlType==0��1���Ե�ucPartNo���������и�ʽ������������޸���]
	unsigned char ucRes;	
	unsigned int uiRes[7];				//reserved [����]
}RV_CTRL_DISK_PARTION_INFO;
typedef struct
{
	DWORD dwSize;
	RV_CTRL_DISK_INFO stDiskInfo;
}RV_CTRL_DISK_OP;
typedef struct
{
	DWORD dwSize;
	RV_CTRL_DISK_PARTION_INFO stDiskPartionInfo;
}RV_CTRL_DISK_PARTION_OP;
//////////////////////////////////////////////////////////////////////
//	channel configure [ͨ������]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int enable;		//enable [ʹ��]
	int startHour;	//start time : hour [��ʼʱ��:Сʱ]
	int	startMinute;//start time : minute [��ʼʱ��:����]
	int	startSecond;//start time : second [��ʼʱ��:����]
	int	endHour;	//end time : hour [����ʱ��:Сʱ]
	int	endMinute;	//end time : minute [����ʱ��:����]
	int	endSecond;	//end time : second [����ʱ��:����]
}RV_TIMESECTION;
//////////////////////////////////////////////////////////////////////
//	network configure [��������]
//////////////////////////////////////////////////////////////////////
#define RV_NAME_PASSWORD_LEN		64	
#define RV_EMAIL_ADDR_LEN  32
#define RV_N_MIN_TSECT 2
typedef struct
{
	char HostName[RV_NAME_PASSWORD_LEN];	//device name [�豸��]	
	int HttpPort;							//HTTP server port [HTTP����˿�]	
	int TCPPort;							//TCP listen port [TCP�����˿�]		
	int SSLPort;							//SSL listen port [SSL�����˿�]	
	int UDPPort;							//UDP listen port [UDP�����˿�]	
	int MaxConn;							//max connection number [���������]	
	unsigned char ucMonMode;				//watch protocal {"TCP","UDP","MCAST",��}  0|1|2 [����Э�� {"TCP","UDP","MCAST",��}  0|1|2]	
	unsigned char ucUseTransPlan;			//if enable network transport plot [�Ƿ��������紫�����]
	unsigned char ucTransPlan;				//transport plot 2 auto 1 fluency first 0 quality first, default 1 [������� 2�Զ� 1���������� 0�������ȣ�Ĭ��1]
	unsigned char ucHighSpeedDownload;		//if enable high speed download [�Ƿ����ø���¼�����ز���]
	int iRes[3];
}RV_CONFIG_NET_APP;
typedef struct
{
	char strEthName[16];			//different net card name, show by string "eth0", this can not be changed [��ͬ�������ƣ����ַ�����ʾ"eth0"; �˲����Ը�]
	char strMacAddr[32];			//xx.xx.xx.xx.xx.xx (string format) [xx.xx.xx.xx.xx.xx(�ַ�����ʽ)]
	char HostIP[20];				//host's IP [����IP]
	char Submask[20];				//sub net mask [��������]
	char Gateway[20];				//gateway IP [����IP]
	unsigned char  ucTranMedia;		//0:wired net, 1:wireless net [0�����ߣ�1������]
	unsigned char  ucDefaultEth;	//if it is default net card, 1:default, 0:not default [�Ƿ���ΪĬ�ϵ�����, 1��Ĭ�� 0����Ĭ��]
	unsigned char  ucValid;			//by bit, bit0 1:valid, 0:invalid [��λ��ʾ����һλ��1����Ч 0����Ч��]
									//bit1 0:DHCP closed, 1:DHCP enable [�ڶ�λ��0��DHCP�ر� 1��DHCPʹ�ܣ�]
									//bit2 0:not support DHCP, 1:support DHCP [����λ��0����֧��DHCP 1��֧��DHCP]
	unsigned char  ucReserve;	
	unsigned char  ucRes[16];		//reserved [������]
}RV_CONFIG_NET_ETH;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_NET_APP stNetApp;
	RV_CONFIG_NET_ETH stNetEth;
}RV_CONFIG_NET_COMM;
//server struct definition [�������ṹ����]
typedef struct
{	
	char ServerName[RV_NAME_PASSWORD_LEN];	//service name, ip domain format or xxx.xxx.xxx.xxx format, max 64 bytes [!������,ip������ʽ������xxx.xxx.xxx.xxx��ʽ���64�ֽ�]
	int iReserved;							//origin IP address, save this field for extend [!ԭʼΪIP��ַ��Ϊ����չ�������ֶΣ�]	
	int Port;								//port [!�˿ں�]
	char UserName[RV_NAME_PASSWORD_LEN];	//uer name [!�û���]	
	char Password[RV_NAME_PASSWORD_LEN];	//password [!����]	
	int  Anonymity;							//if anonimity [!�Ƿ�������¼]
}RV_REMOTE_SERVER;
typedef struct
{
	int Enable;								//enale [!�Ƿ��� 0 ��������1����]	
	int iKey;								//type name, if it is ddns, corresponding ddnskey, can extend server type for using [!�������ƣ������ddns����Ӧddnskey;������չ��������ʹ��]
	RV_REMOTE_SERVER Server;				//server information [!������ ��Ϣ]
}RV_IPADDR_SERVER;
#define  RV_MAX_EMAIL_TITLE_LEN 64
#define  RV_MAX_EMAIL_RECIEVERS  5
//email configure [EMAIL����]
typedef struct
{
	//can fill with ip, and can fill with domain [������ip,Ҳ����������]
	RV_IPADDR_SERVER Server;
	int bUseSSL;		
	char SendAddr[RV_EMAIL_ADDR_LEN];							//sender address [���͵�ַ]		
	char Recievers[RV_MAX_EMAIL_RECIEVERS][RV_EMAIL_ADDR_LEN];	//receiver address [�����˵�ַ]		
	char Title[RV_MAX_EMAIL_TITLE_LEN];							//emial title [�ʼ�����]
	RV_TIMESECTION Schedule[RV_N_MIN_TSECT];					//emial valid time [email��Чʱ��]	
}RV_CONFIG_EMAIL;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_EMAIL stEmail;
}RV_EMAIL;
//DNS
typedef struct
{
	char strPrimaryIp[16]; //xxx. xxx. xxx. xxx (string format) [xxx. xxx. xxx. xxx (�ַ�����ʽ)]
	char strSecondIp[16];
}RV_DNS_IP_LIST;
typedef struct
{
	DWORD dwSize;
	RV_DNS_IP_LIST stDNSIpList;
}RV_DNS;
//UPNP
typedef struct
{	
	int Enable;		//enable [�Ƿ���]	
	int WebPort;	//web port [web�˿�]	
	int TCPPort;	//tcp port [tcp�˿�]	
	int iRervered;
}RV_CONFIG_UPNP;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_UPNP stUpnp;
}RV_UPNP;
//PPPOE
typedef struct 
{
	int iEnable;		//0:disable, 1:enable [0 ��ʹ�ܣ�1 ʹ��]
	char strip[32];
	char strUser[64];
	char strPwd[64];
}RV_PPPOE_IP_SRV;		//remarks : only enable, ip(dial ip), user name, password are valid when dial to get configure [ע�������У����Ż�ȡ���õ�ʱ��ֻ��ʹ�ܣ�ip������ip�����û���������Ч��]
						//when setting, only enable, user name, password are valid [���õ�ʱ��ֻ��ʹ�ܣ��û���������Ч��]
typedef struct
{
	DWORD dwSize;
	RV_PPPOE_IP_SRV stPppoe;
}RV_PPPOE;
//DDNS
#define RV_MAX_DDNS_SERVER_NUM 16
typedef struct
{
	DWORD dwSize;
	int iCount;
	RV_IPADDR_SERVER stDDNSServer[RV_MAX_DDNS_SERVER_NUM];
}RV_MDDNS;
//////////////////////////////////////////////////////////////////////
//	code configure [��������]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int		iCompression;			/*!< compression mode [ѹ��ģʽ] */	
	int		iResolution;			/*!< resolve, reference to enum capture_size_t(DVRAPI.H) [�ֱ��� ����ö��capture_size_t(DVRAPI.H)] */	
	int		iBitRateControl;		/*!< bit-stream control, reference to enum capture_brc_t(DVRAPI.H) [�������� ����ö��capture_brc_t(DVRAPI.H)] */	
	int		iQuality;				/*!< picture quality, level 1~6 (corresponding worst,bad,common,good,better,best) [�����Ļ��� ����1-6����Ӧ�������һ�㣬�ã��ܺã����]*/	
	int		nFPS;					/*!< frame rate (0~30 ), (-n~0) means how many seconds per frame, NTSC and PAL are the same [֡��ֵ��0~30����-n~0��������ʾ����һ֡��NTSC/PAL������] */	
	int		nBitRate;				/*!< 0-4096k */
	int		iGOP;					/*!< descript time slice between two I frame, unit is second, 2-12 [��������I֮֡��ļ��ʱ��s��2-12] */
}RV_VIDEO_FORMAT;
typedef struct
{
	int		nBitRate;				/*!< bit-stream kbps [����kbps]*/	
	int		nFrequency;				/*!< sample rate [����Ƶ��]*/	
	//int		nMaxVolume;			/*!< max volume value [���������ֵ]*/
	unsigned char	ucLAudioVolumn;	//left audio channel volumn [����������]
	unsigned char	ucRAudioVolumn;	//right audio channel volumn [����������]
	unsigned char	ucRes[2];		//reserved [����]
}RV_AUDIO_FORMAT_T;
//media format [ý���ʽ]
typedef struct
{
	RV_VIDEO_FORMAT vfFormat;		/*!< video format definition [��Ƶ��ʽ����] */			
	RV_AUDIO_FORMAT_T afFormat;		/*!< audeo format definition [��Ƶ��ʽ����] */
	int	bVideoEnable;				/*!< open video code [������Ƶ����] */
	int	bAudioEnable;				/*!< open audio code [������Ƶ����] */	
}RV_MEDIA_FORMAT;
//code configure [��������]
typedef struct
{
	int iSteamIndex;				/*!<bit-stream format [������ʽ] 
										main bit-stream, reference to enum ENCODE_TYPE_BY_RECORD, default to only have one main stream, fill it to 0 [������ �ο�ö�ٲο�ENCODE_TYPE_BY_RECORD �����в�ƷĬ��ֻ��һ�������������Ϊ0��]
										assist bit-stream, reference to enum ENCODE_TYPE_BY_SUBSTREAM, max 4 assist bit-stream, max support one assist bit-stream now, fill it to 0 [������ �ο� ENCODE_TYPE_BY_SUBSTREAM�����4�������������ڲ�Ʒ���֧��һ�ָ����������Ϊ0��]
										snapshot bit-stream, reference to enum ENCODE_TYPE_BY_SUBSTREAM, config snapshot from max 4 assist bit-stream [׽ͼ���� �ο� ENCODE_TYPE_BY_SUBSTREAM������4�������н���׽ͼ����]
									*/	
	RV_MEDIA_FORMAT dstFmt;			/*!<bit-stream format [������ʽ] */	
}RV_NET_ENCODE;
//
#define RV_N_COLOR_SECTION 2
//video color struct [��Ƶ��ɫ�ṹ]
typedef struct
{
	int	nBrightness;				/*!< brightness 0-100 [����	0-100] */
	int	nContrast;					/*!< conrast 0-100 [�Աȶ�	0-100] */
	int	nSaturation;				/*!< saturation 0-100 [���Ͷ�	0-100] */
	int	nHue;						/*!< hue 0-100 [ɫ��	0-100] */
	int	mGain;						/*!< gain, 0-100, bit6 means auto gain [����	0-100 �ڣ�λ��1��ʾ�Զ�����]��*/		
	int	mWhitebalance;				/*!< auto white level control, bit7 means open auto control, 0x0,0x1,0x2 means low,middle,high level [�Զ��׵�ƽ���ƣ�bit7��λ��ʾ�����Զ�����.0x0,0x1,0x2�ֱ�����,��,�ߵȼ�]*/
}RV_VIDEOCOLOR_PARAM; 
typedef struct
{
	RV_TIMESECTION		TimeSection;		/*!< time slice [ʱ���] */
	RV_VIDEOCOLOR_PARAM	dstColor;			/*!< color definition [��ɫ����] */
	int					iEnable;            /*!< enable, there is no definition in sdk now, default is enable [ʹ�ܶ��� ����sdk��ʱû�д˲��֣�Ĭ��ʹ��]*/
}RV_VIDEOCOLOR;
typedef struct
{
	RV_VIDEOCOLOR dstVideoColor[RV_N_COLOR_SECTION];
}RV_CONFIG_VIDEOCOLOR;
//query video area shelter information [��ѯ��Ƶ�����ڵ�������Ϣ]
typedef void *						VD_HANDLE;
typedef int							VD_BOOL;
typedef unsigned int				VD_COLORREF;//0x00bbggrr
typedef unsigned int				VD_COLORDEV;//0x????????
//video object struct [��Ƶ����ṹ]
typedef struct
{
	VD_COLORREF rgbaFrontground;		/*!< object's front RGB and transparency [�����ǰ��RGB����͸����] */	
	VD_COLORREF rgbaBackground;			/*!< object's background RGB and transparency [����ĺ�RGB����͸����]*/	
	RV_VD_RECT	rcRelativePos;			/*!< object's edge distance / total length * 8191 [����߾��������ı���*8191] */	
	VD_BOOL	bPreviewBlend;				/*!< overprint in preview [Ԥ������] */	
	VD_BOOL	bEncodeBlend;				/*!< overprint in code [�������] */
}RV_VIDEO_WIDGET;
//area shelter [�����ڵ�]
#define RV_COVERNUM 8
typedef struct
{
	unsigned int	uiCoverNum;			//how many overprint areas in current channel [��ǰ��ͨ���м������ӵ�����]
	RV_VIDEO_WIDGET	dstCovers[RV_COVERNUM];
}RV_NET_VIDEO_COVER;
//
typedef struct  
{
	unsigned int  cSize;		//�����С��1��ʾ��׼������2��ʾ2����С  ��ֵȡֵ��Χ��1��ucZoomAbility֮��
	unsigned int  cRes[3];
}RV_OSD_ZOOM_PARAM;

typedef struct  
{
	DWORD	dwSize;
	RV_OSD_ZOOM_PARAM	stOSDZoom;
}RV_OSD_ZOOM_CFG;

#define RV_CHANNEL_NAME_SIZE 32
typedef struct
{
	DWORD dwSize;	
	char cName[RV_MAX_CHANNUM][RV_CHANNEL_NAME_SIZE];
	RV_NET_ENCODE stEncodeMain[RV_MAX_CHANNUM];
	RV_NET_ENCODE stEncodeAssist[RV_MAX_CHANNUM];
	RV_CONFIG_VIDEOCOLOR stColorCfg[RV_MAX_CHANNUM];
	RV_VIDEO_WIDGET stTimeOSD[RV_MAX_CHANNUM];
	RV_VIDEO_WIDGET stTitleOSD[RV_MAX_CHANNUM];
	RV_NET_VIDEO_COVER stCovor[RV_MAX_CHANNUM];
	RV_NET_GENERAL stGeneral;
	RV_OSD_ZOOM_PARAM stOSDZoom;
}RV_CODE_CFG;

typedef struct
{
	unsigned short 	iChannel;		//channel, start with 0 [ͨ�� ��0��ʼ]
	unsigned short	iIndex;			//preset or locus index , start with 1 [Ԥ�õ���߹켣�±�� ��1��ʼ]
}RV_PTZ_CHANNEL;

#define NAME_LEN			32		
#define PTZ_PRESETNUM		64
#define PTZ_CHANNELS		8

typedef struct 
{
	unsigned char 	ucChannel;					//channel [ͨ��]
	unsigned char 	ucPresetID;					//preset No. [Ԥ�õ��]
	unsigned char	iSpeed;						//preset speed speed 1~15 level [Ԥ�õ��ٶ� �ٶ�1~15�ȼ�]
	unsigned char	iDWellTime;					//preset delay time 1~255 [Ԥ�õ�ͣ��ʱ�� 1~255s]
	unsigned char	szPresetName[NAME_LEN];		//preset name [Ԥ�õ�����]
}RV_PRESET_INFO;

typedef struct
{
	unsigned char 	ucChannel;					//channel [ͨ��]
	unsigned char	ucTourIndex;				//tour No. [Ѳ����]
	unsigned char	ucPresetCnt;				//number of presets in one tour [һ��Ѳ�����е�Ԥ�õ��� 0~128]
	unsigned char	uRes;						//reserved [����]
	unsigned char	uiPresetNum[PTZ_PRESETNUM];	//preset No. in tour [Ѳ�����е�Ԥ�õ��]
}RV_TOUR_INFO;

typedef struct  
{
	DWORD dwSize;
	DWORD dwCount;
	RV_PRESET_INFO	struPreset[PTZ_PRESETNUM];
}RV_PTZ_PRESET_SCHEDULE;

typedef struct  
{
	DWORD dwsize;
	DWORD dwCount;
	RV_TOUR_INFO	struTour[PTZ_CHANNELS];
}RV_PTZ_TOUR_SCHEDULE;

typedef struct  
{
	RV_PTZ_CHANNEL struChannel;
	RV_PRESET_INFO	struPreset;
}RV_PTZ_TOUR_PRESET;
//NTP struct [NTP�ṹ��]
typedef struct
{	
	RV_IPADDR_SERVER szNtpServer;	//server [������]	
	int UpdatePeriod;				//update time slice [��������]	
	int TimeZone;					//time zone [ʱ��]
}RV_CONFIG_NTP;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_NTP stNtp;
}RV_NTP;

//////////////////////////////////////////////////////////////////////////
//	struct of output mode [���ģʽ�ṹ��]
typedef struct
{
	unsigned char ucOSDShow;//bit0:if show time, bit1:if show channel name [0λ �Ƿ���ʾʱ�� 1λ �Ƿ���ʾͨ����]
	unsigned char ucRes[15];//reserved [����]
}RV_OUT_MODE_OSD_CFG;
typedef struct
{
	DWORD dwSize;
	RV_OUT_MODE_OSD_CFG stOSD;
}RV_OUT_MODE_CFG;

//////////////////////////////////////////////////////////////////////////
//	ftp struct [ftp�ṹ��]
typedef struct
{
	RV_IPADDR_SERVER	stServer;				//ftp server [ftp������]
	char            cDirName[RV_FTP_MAX_PATH];  //FTP folder path, 240[FTPĿ¼·�� 240]
	int             iReserved;                   
	int             iFileLen;                   //file length, unit is M [�ļ����� MΪ��λ]
	int             iInterval;                  //time slice between files, unit is second [�����ļ�ʱ����    ��Ϊ��λ]
	char            cRev[128];
}RV_CONFIG_FTP_SERVER_SET;
typedef struct
{
	RV_TSECT				stSect[RV_N_WEEKS][RV_TIME_SECTION];
}RV_FTP_APP_TIME_SET;
typedef struct
{
	RV_CONFIG_FTP_SERVER_SET	stFtpServerSet;	
	RV_FTP_APP_TIME_SET			stFtpAppTimeSet[RV_MAX_CHANNUM];
}RV_FTP_SERVER;
typedef struct
{
	DWORD dwSize;
	RV_FTP_SERVER stFtpRecord;	//record [¼��]
	RV_FTP_SERVER stFtpPicture;	//picture [ͼƬ]
}RV_FTP;

/////////////////////////////////////////////////////////////////////////
//	rtsp struct [rtsp�ṹ��]
typedef struct
{
	unsigned short    usEnable;       //enable [ʹ��] 
	unsigned short    usListernPort;  //RTSP listen port [RTSP�����˿�]
	unsigned short    usUdpStartPort; //UDP start port [UDP��ʼ�˿�]
	unsigned short    usUdpPortNum;   //UDP port number [UDP�˿�����]
	unsigned short    usReserve[36];  //reserved [����]
}RV_CONFIG_RTSP_SET;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_RTSP_SET stRTSP;
}RV_RTSP;

//////////////////////////////////////////////////////////////////////
//	alarm struct of intelligent red [�ܺ�ɫ�����ṹ]
//////////////////////////////////////////////////////////////////////
//area shelter [�����ڵ�]
#define RV_REDREGIONNUM 8
typedef struct
{
	long lX;
	long lY;
}RV_POINT;
typedef struct
{
	int				iRectNum;							//how many areas in current channel [��ǰ��ͨ���м�������]
	RV_POINT		szPointArray[RV_REDREGIONNUM][4];
}RV_REDON_RECT;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [����ʽ]
	RV_REDON_RECT			stRedonRect;
} RV_INTERED_ALARM; 
typedef struct
{
	DWORD dwSize;		
	RV_INTERED_ALARM		struInteRedAlarm[RV_MAX_CHANNUM];
}RV_INTERED_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//record control [¼�����]
typedef struct
{
	unsigned char ucChannelCount;	//channel number [ͨ����Ŀ]
	unsigned char ucRes[3];
	unsigned char ucState[128];		//0~127 flag channel 1~128 (0:not record, 1:manual record, 2:auto record) [��0������127������Ϊ��1����128ͨ����0: Ϊ��¼��;1: �ֶ�¼��;2: Ϊ�Զ�¼��]
}RV_RECCTL; 
typedef struct
{
	DWORD dwSize;  
	RV_RECCTL struRecCtl;
}RV_RECCTL_CFG;

/* configure struct of serial port, more than 16 channnels [�������ýṹ�� ����16ͨ��] */
typedef struct
{
	DWORD			dwSize;
	//protocal of decoder [������Э��]
	DWORD			dwDecProListNum;										//number of protocal [Э�����]
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN];	//protocal list [Э�����б�]
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM_EX];						//current attributes of every decoder [����������ǰ����]

	DWORD			dw232FuncNameNum;										//number of 232 function [232���ܸ���]
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];			//function name list [�������б�]
	RV_RS232_CFG	st232[RV_MAX_232_NUM];									//current attrributes of every 232 serial port [��232���ڵ�ǰ����]
} DHDEV_COMM_CFG_EX;

typedef struct  
{
	int iChannel;
	char strChannelName[MAX_HHCHANNELNAME_LEN]; 
}RV_CHANNEL_NAME;

typedef struct  
{
	DWORD dwSize;
	RV_CHANNEL_NAME stChannelName[RV_MAX_DECODER_NUM_EX];		
}RV_CHANNELNAME_CFG;

//////////////////////////////////////////////////////////////////////////
//audio config [��Ƶ����]
typedef struct
{
	unsigned int uiTalkAudioSourceType; //audio source method, 0:liner input, 1:mic [����Դ��ʽ��0Ϊ�������룬1Ϊmic]
	unsigned int uiOutSilence;			//mute, 0:not mute, 1-mute [���� 0--�Ǿ��� 1--����]
	unsigned int uiOutLAudioVolumn;		//left audio channel volume [����������]
	unsigned int uiOutRAudioVolumn;		//right audio channel volume, left and right channel' value are the same for single audio channel device [���������������������豸����ֵһ��]
	unsigned int uiReserverd[32];		//[����]
}RV_DEV_AUDIO;
typedef struct  
{
	DWORD			dwSize;
	RV_DEV_AUDIO	stDevAudio;		
}RV_DEV_AUDIO_CFG;

//////////////////////////////////////////////////////////////////////////
// tour confgure for digital channel [����ͨ����ѵ����]
typedef struct
{
	BOOL			BEnable;                //enable [ʹ�ܿ���]
	char			cChName[32];            //name of this configure, for identify [����������,����ʶ��]
	char			cDeviceIP[64];          //ip of device for connection [�������豸��ip��ַ]
	LONG			iDevicePort;			//port of device for connection [�������豸�Ķ˿ں�]
	char			cDeviceUserName[32];	//user name [�û���]
	char			cDevicePassword[32];	//password [����]    
	LONG			iDevType;               //device type, by enum, protocal type, 0:tcp connection, 3:rtsp+udp, 4:vs300 [�豸���ͣ���ö�ٱ�ʾ����Э������,0��ʾtcpֱ����3 rtsp+udp 4 vs300.]
	LONG			iRemoteChannelNo;       //remote channel index, start with 0 [Զ��ͨ����,��0��ʼ����]
	LONG			iStreamType;            //which bit-stream, 0:main, 1:assist [Ҫ���ӵ���������?0:�������� 1:������]
	LONG			iRemotePtzPreset;		//remote preset [Զ��Ԥ�õ�]
	LONG			iRemotePtzPresetEnable;	//if set preset on connected [�Ƿ�һ�����Ͼ�����Զ��Ԥ�õ�]   
	LONG			reserverd[5];           //reserved [�����ֽ�]	
}RV_REMOTE_CH_CFG;
typedef struct
{
	BOOL			BEnable;			//enable [ʹ�ܿ���]
	LONG			iDeviceChannelType; //channel type, 0:digital channel, 1:analog channel, default is digital channel, can't switch now [ͨ�����ͣ�0��ʾ����ͨ����1��ʾģ��ͨ����Ĭ��Ϊ����ͨ��,��ʱ�������л�]
	LONG			iMode;				//0:single connection, 1:multi connection [0 ������ 1 ������]
	unsigned long   uiTourTime;			//multi connection tour time [��������Ѳʱ��]
	unsigned long   uiNotTourCfgIndex;	//channel configure on single connection, position in the tour list [������ʱ�Ĳ��õ�ͨ������,����Ѳ�б��е�λ��]
	LONG			iDecodePolicy;		//decode plot (-2:most real-time, -1:real-time, 0:default, 1:fluency, 2:most fluency) mayby extend to self definition [�������     (-2, ��ʵʱ -1 ʵʱ 0 Ĭ����� 1 ���� 2,    ������ ) �Ժ������չ���Զ���������ʱʱ��]
	LONG			iAVEnable;			//0:only decode video, 1:only decode audio, 2:decode audio and video [0,ֻ����Ƶ 1��ֻ����Ƶ ��2 ������Ƶ ]
	LONG			iReserverd[5];      //reserved [�����ֽ�]
}RV_LOCAL_CH_CFG;
typedef struct
{
	RV_LOCAL_CH_CFG		stLocalChCfg;			//channel configure [ͨ������]
	DWORD				dwRemoteChanCount;		//remote channel number [Զ��ͨ����Ŀ]
	RV_REMOTE_CH_CFG	stRemoteChanCfg[64];	//remote channel config [Զ��ͨ������]
}RV_LOCAL_CH;
typedef struct
{
	DWORD dwSize;
	RV_LOCAL_CH stLocalChan[64];
}RV_DIGI_CH_TOUR_CFG;

//////////////////////////////////////////////////////////////////////////
// key-board control configure [���Ƽ�������]
typedef struct 
{
	unsigned char Com_Version[8];	/*!< version number [�汾��] */
	unsigned char Function;			/*!< serial port function, reference to enum KBDFunc [���ڹ��� ����ö��KBDFunc]*/
	unsigned char DataBits;			/*!< data bit, values are 5,6,7,8 [����λ ȡֵΪ5,6,7,8] */
	unsigned char StopBits;			/*!< stop bit, reference to enum comm_stopbits_t(DVRAPI.H) [ֹͣλ ����comm_stopbits_t(DVRAPI.H)] */
	unsigned char Parity;			/*!< verify bit, reference to enum comm_parity_t(DVRAPI.H) [У��λ ����comm_parity_t(DVRAPI.H)] */
	unsigned int  BaudBase;			/*!< baudrate {300,600,1200,2400,4800,9600,19200,38400,57600,115200} [������ {300,600,1200,2400,4800,9600,19200,38400,57600,115200}]��*/
}RV_KBD;
typedef struct
{
	DWORD dwSize;
	RV_KBD stKBD;
}RV_KBD_CFG;
//////////////////////////////////////////////////////////////////////////
// configure of matrix (XINGHUO Corp.) [����(�ǻ�)����]
typedef struct
{
	unsigned int uiMap[16];//channel of visiondigi device corresponding channel of matrix input, 0xffffffff means not use matrix input of XINGHUO, eg. uiMap[0] = 100, means channel 1 use the channel 101 of XINGHUO matrix [��Ǭ�豸��ͨ����Ӧ�ľ��������ͨ���ţ�0xffffffff��ʾ��ʹ���ǻ�ľ������룬����uiMap[0] = 100����ʾ��1ͨ��ʹ���ǻ�ĵ�101·����]
	unsigned int uiRes[20];
}RV_MATRIX_XINGHUO;

typedef struct
{
	DWORD				dwSize;
	RV_MATRIX_XINGHUO	stMatrixXingHuo;
}RV_MATRIX_CFG;

typedef struct  
{
	int iMatrixInput;
	int iChannel;//ͨ����
	int iVideoEnable;
}RV_MATRIX_INPUT;

typedef struct  
{
	DWORD			dwSize;
	RV_MATRIX_INPUT	stMatrixInput[16];
}RV_MATRIX_CFG_EX;

//added by zhubo,CID-PID��Ӧ
typedef struct
{

int Cid0;//����ͨ�����ϵ�CID��û��ʱ��-1
int Pid0;//����ͨ�����ϵ�PID��û��ʱ��-1
int iRes1[2];

int Cid1;//����ͨ�����µ�CID
int Pid1;//����ͨ�����µ�PID������ʱ��-1
int iRes2[2];
}RV_MATRIX_PIDCID;

//SVAC����
typedef struct  
{
	unsigned char	ucEnable;		//ʹ��
	unsigned char	ucLevel;		//�ȼ�, ����
	unsigned char	ucRes[2];		//����
	RV_RECT			stArea;			//��������
}RV_SVAC_FOCUS_AREA, *pRV_SVAC_FOCUS_AREA;

typedef struct
{
	unsigned char	ucChannel;				//ͨ��
	unsigned char	ucRes[3];				//����
	RV_SVAC_FOCUS_AREA dstFocusAreas[8];	//��չ��8������ʱ��������һ�㣬ȡǰ4������
}RV_NET_SVAC_FOCUS_AREA, *pRV_NET_SVAC_FOCUS_AREA;

typedef struct  
{
	DWORD dwSize;
	RV_NET_SVAC_FOCUS_AREA	stSVACFocusArea[RV_MAX_CHANNUM];
}RV_NET_SVAC_AREA;




/******************************************************************************
* end of configure struct [end of ���ýṹ��]
*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif










































