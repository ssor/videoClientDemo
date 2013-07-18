
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
** constant define  [常量定义]
***********************************************************************/
#define RV_SERIALNO_LEN 		48		//max size of device serial number [设备序列号字符长度]
#define RV_MAX_DISKNUM 			32		//max number of disk [最大硬盘个数]
#define RV_MAX_SDCARDNUM		32		//max number of SD card [最大SD卡个数]
#define RV_MAX_BURNING_DEV_NUM	32		//max number of imprinting device [最大刻录设备个数]
#define RV_BURNING_DEV_NAMELEN	32		//max size of device name [刻录设备名字最大长度]
#define RV_MAX_LINK 			6		
#define RV_MAX_CHANNUM 			16		//max number of channel [最大通道个数]
#define RV_MAX_ALARMIN 			128		//max number of alarm-in [最大报警输入个数]
#define RV_MAX_ALARMOUT 		64		//max number of alarm-out [最大报警输出个数]

#define RV_MAX_RIGHT_NUM		100		//max number of usr authority [用户权限个数上限]
#define RV_MAX_GROUP_NUM		20		//max number of user group [用户组个数上限]
#define RV_MAX_USER_NUM			200		//max number of user [用户个数上限]
#define RV_RIGHT_NAME_LENGTH	32		//max size of authority name [权限名长度]
#define RV_USER_NAME_LENGTH		8		//max size of user name [用户名长度]
#define RV_USER_PSW_LENGTH		8		//max size of user password [用户密码长度]
#define RV_MEMO_LENGTH			32		//max size of memo [备注长度]

#define RV_MAX_STRING_LEN		128
#define RV_DEF_REALPLAY_BUF_NUM (3) 
#define RV_MIN_REALPLAY_BUF_NUM (1) 
#define RV_MAX_REALPLAY_BUF_NUM (50) 

//callback type of listen from device [侦听设备回调类型]
#define RV_DVR_SERIAL_RETURN 1   //the callback of sending serial number by device [设备发送序列号回调]
#define RV_DVR_DISCONNECT -1     //the callback of disconnect from device during verify period [验证期间设备断线回调]

//constant for overprint character on picture [通道画面字符叠加相关常量]
#define MAX_STRING_LINE_LEN	6		//max six lines [最多六行]
#define MAX_PER_STRING_LEN  20		//max length per line [每行最大长度]

//number of DDNS [DDNS数目定义]
#define MAX_DDNS_COUNT 16

//the types of alarm message callbacked, corresponding CLIENT_StartListen [回调报警信息类型，对应CLIENT_StartListen]
#define RV_COMM_ALARM			0x1100	//common alarm infomation (include:out-alarm, video lost, motion detect) [常规报警信息(包括外部报警，视频丢失，动态检测)]
#define RV_SHELTER_ALARM		0x1101	//video shelter alarm [视频遮挡报警]
#define RV_DISK_FULL_ALARM		0x1102	//disk full alarm [硬盘满报警]
#define RV_DISK_ERROR_ALARM		0x1103	//disk error alarm [硬盘故障报警]
#define RV_SOUND_DETECT_ALARM	0x1104	//audio detect alarm [音频检测报警]
#define RV_ALARM_DECODER_ALARM	0x1105	//decoder alarm [报警解码器报警]

//extended types of alarm message callabcked, corresponding CLIENT_StartListenEx [扩展回调报警信息类型，对应CLIENT_StartListenEx]
//seperate alarm types detailly [各报警类型详细分开]
#define RV_ALARM_ALARM_EX			0x2101	//out-alarm [外部报警]
#define RV_MOTION_ALARM_EX			0x2102	//motion detect alarm [动态检测报警]
#define RV_VIDEOLOST_ALARM_EX		0x2103	//video lost alarm [视频丢失报警]
#define RV_SHELTER_ALARM_EX			0x2104	//shelter alarm [遮挡报警]
#define RV_SOUND_DETECT_ALARM_EX	0x2105	//audio detect alarm [音频检测报警]
#define RV_DISKFULL_ALARM_EX		0x2106	//disk full alarm [硬盘满报警]
#define RV_DISKERROR_ALARM_EX		0x2107	//disk error alarm [坏硬盘报警]
#define RV_ENCODER_ALARM_EX			0x210A	//coder alarm [编码器报警]
#define RV_URGENCY_ALARM_EX			0x210B	//urgent alarm [紧急报警]
#define RV_WIRELESS_ALARM_EX		0x210C	//wireless alarm [无线报警]
#define RV_NEW_SOUND_DETECT_ALARM_EX 0x210D //new audio detect alarm, the struct reference to RV_NEW_SOUND_ALARM_STATE [新音频检测报警报警信息的结构体见RV_NEW_SOUND_ALARM_STATE]
#define RV_DECODER_ALARM_EX			0x210E	//decoder alarm [解码器报警]

#define RV_SAVIA_ALARM_TRACK		0x210F	//intelligent:track arithmatic alarm [智能：跟踪算法报警]
#define RV_SAVIA_ALARM_CROSSLINE	0x2110	//intelligent:cross-line arithmatic alarm [智能：越线算法报警]
#define RV_SAVIA_ALARM_CROSSNET		0x2111	//intelligent:invade arithmatic alarm [智能：入侵算法报警]
#define RV_SAVIA_ALARM_WANDER		0x2112	//intelligent:wander arithmatic alarm [智能：徘徊算法报警]
#define RV_SAVIA_ALARM_CONVERSE		0x2113	//intelligent:thrash arithmatic alarm [智能：逆行算法报警]
#define RV_SAVIA_ALARM_STATIC		0x2114	//intelligent:left alone arithmatic alarm [智能：遗留算法报警]
#define RV_SAVIA_ALARM_LOST			0x2115	//intelligent:lost arithmatic alarm [智能：遗失算法报警]
#define RV_SAVIA_ALARM_DAMAGE		0x2116	//intelligent:spray finishing arithmatic alarm [智能：喷涂算法报警]
#define RV_INTE_ALARM_SMOKEFIRE		0x2117	//intelligent:fireworks arithmatic alarm [智能：烟火算法报警]

#define RV_INTE_ALARM_RED_LEVEL_1	0x2118	//intelligent:red detect level-1 [智能：智能红色检测告警1档]
#define RV_INTE_ALARM_RED_LEVEL_2	0x2119	//intelligent:red detect level-2 [智能：智能红色检测告警2档]
#define RV_INTE_ALARM_RED_LEVEL_3	0x211a	//intelligent:red detect level-3 [智能：智能红色检测告警3档]
#define RV_INTE_ALARM_RED_LEVEL_4	0x211b	//intelligent:red detect level-4 [智能：智能红色检测告警4档]
#define RV_INTE_ALARM_RED_LEVEL_5	0x211c	//intelligent:red detect level-5 [智能：智能红色检测告警5档]
#define RV_INTE_ALARM_RED_LEVEL_6	0x211d	//intelligent:red detect level-6 [智能：智能红色检测告警6档]


#define RV_CONFIG_RESULT_EVENT_EX	0X3000  //the returned value code for modify configure, reference to DEV_SET_RESULT [修改配置的返回码返回结构见DEV_SET_RESULT]
#define RV_REBOOT_EVENT_EX			0x3001	//event of device reboot [设备重启事件]
#define RV_AUTO_TALK_START_EX		0x3002  //device start talk [设备主动开始语音对讲]
#define RV_AUTO_TALK_STOP_EX		0x3003  //device stop talk [设备主动停止语音对讲]

//interface params of query device status : query type used in CLIENT_QueryDevState [查询设备状态接口参数：查询类型 用于CLIENT_QueryDevState参数]
#define RV_DEVSTATE_COMM_ALARM		0x0001	//query common alarm (include:out-alarm, video lost, motion detect) [查询普通报警(包括外部报警，视频丢失，动态检测)]
#define RV_DEVSTATE_SHELTER_ALARM	0x0002	//query shelter alarm [查询遮挡报警]
#define RV_DEVSTATE_RECORDING		0x0003	//query record status [查询录象状态]
#define RV_DEVSTATE_DISK			0x0004	//query disk status [查询硬盘状态]
#define RV_DEVSTATE_RESOURCE		0x0005	//system resource status [系统资源状态]
#define RV_DEVSTATE_BITRATE			0x0006	//get channel bit-stream [获取通道码流]
#define RV_DEVSTATE_CONN			0x0007	//get connection status to device [获取设备连接状态]
#define RV_DEVSTATE_PROTOCAL_VER	0x0008	//get version of network protocal, pBuf = int* [获取网络协议版本号,	pBuf = int*]
#define RV_DEVSTATE_TALK_ECTYPE		0x0009	//get format list of audio talk supported by device, reference to struct DHDEV_TALKFORMAT_LIST [获取设备支持的语音对讲格式列表，见结构体DHDEV_TALKFORMAT_LIST]
#define RV_DEVSTATE_SD_CARD			0x000A	//get SD card infomation(products as IPC,etc...) [获取SD卡信息（IPC类产品）]
#define RV_DEVSTATE_BURNING_DEV			0x000B	//query infomation of imprinting machine[查询刻录机信息]
#define RV_DEVSTATE_BURNING_PROGRESS	0x000C	//query imprinting process [查询刻录进度]
#define RV_DEVSTATE_PLATFORM		0x000D	//get supported platform [获取设备支持的接入平台]
#define RV_DEVSTATE_CAMERA			0x000E	//get attributes of cameral, pBuf = DHDEV_CAMERA_INFO *, can have many bojects [获取摄像头属性信息，pBuf = DHDEV_CAMERA_INFO *，可以有多个结构体]
#define RV_DEVSTATE_SOFTWARE		0x000F	//software version infomation of device [设备软件版本信息]
#define RV_DEVSTATE_LANGUAGE        0x0010  //audio types supported by device [设备支持的语音种类]
#define RV_DEVSTATE_DSP				0x0011	//ability description of DSP [DSP能力描述]
#define	RV_DEVSTATE_OEM				0x0012	//OEM
#define	RV_DEVSTATE_NET				0x0013  //running infomation of network [网络运行状态信息]
#define RV_DEVSTATE_TYPE			0x0014  //devive type [设备类型]
#define RV_DEVSTATE_SNAP			0x0015	 //query ability of snapshot function [抓图功能能力查询]

//snapshot and video code mode type [抓图视频编码类型]
#define CODETYPE_MPEG4   0
#define CODETYPE_H264    1
#define CODETYPE_JPG     2

//error type code, returned by CLIENT_GetLastError [错误类型代号，CLIENT_GetLastError函数的返回]
#define _EC(x)						(0x80000000|x)
#define NET_NOERROR 				0				//no error [没有错误]
#define NET_ERROR					-1				//unknown error [未知错误]
#define NET_SYSTEM_ERROR			_EC(1)			//error in Windows system [Windows系统出错]
#define NET_NETWORK_ERROR			_EC(2)			//net error, maybe because net timeout [网络错误，可能是因为网络超时]
#define NET_DEV_VER_NOMATCH			_EC(3)			//device protocal not mathched [设备协议不匹配]
#define NET_INVALID_HANDLE			_EC(4)			//invalid handle [句柄无效]
#define NET_OPEN_CHANNEL_ERROR		_EC(5)			//fail to open channel [打开通道失败]
#define NET_CLOSE_CHANNEL_ERROR		_EC(6)			//fail to close channel [关闭通道失败]
#define NET_ILLEGAL_PARAM			_EC(7)			//user params not valid [用户参数不合法]
#define NET_SDK_INIT_ERROR			_EC(8)			//error occur while initializing SDK [SDK初始化出错]
#define NET_SDK_UNINIT_ERROR		_EC(9)			//error occur while cleanuping SDK [SDK清理出错]
#define NET_RENDER_OPEN_ERROR		_EC(10)			//error occur while applying render resource [申请render资源出错]
#define NET_DEC_OPEN_ERROR			_EC(11)			//error occur while opening decode library [打开解码库出错]
#define NET_DEC_CLOSE_ERROR			_EC(12)			//error occur while closing decode library [关闭解码库出错]
#define NET_MULTIPLAY_NOCHANNEL		_EC(13)			//detect that the channel number is 0 in multi-view previewing [多画面预览中检测到通道数为0]
#define NET_TALK_INIT_ERROR			_EC(14)			//fail to initialize audio record library [录音库初始化失败]
#define NET_TALK_NOT_INIT			_EC(15)			//audio record library not inialized [录音库未经初始化]
#define	NET_TALK_SENDDATA_ERROR		_EC(16)			//error occur while sending audio data [发送音频数据出错]
#define NET_REAL_ALREADY_SAVING		_EC(17)			//real-time data is in saving status [实时数据已经处于保存状态]
#define NET_NOT_SAVING				_EC(18)			//not saved real-time data [未保存实时数据]
#define NET_OPEN_FILE_ERROR			_EC(19)			//open file fail [打开文件出错]
#define NET_PTZ_SET_TIMER_ERROR		_EC(20)			//fail to lauch PTZ control timer [启动云台控制定时器失败]
#define NET_RETURN_DATA_ERROR		_EC(21)			//check returned value unvalid [对返回数据的校验出错]
#define NET_INSUFFICIENT_BUFFER		_EC(22)			//not enough buffer [没有足够的缓存]
#define NET_NOT_SUPPORTED			_EC(23)			//not support the function in this SDK [当前SDK未支持该功能]
#define NET_NO_RECORD_FOUND			_EC(24)			//can't find out the record [查询不到录象]
#define NET_NOT_AUTHORIZED			_EC(25)			//don't have operation authority [无操作权限]
#define NET_NOT_NOW					_EC(26)			//can't comit now [暂时无法执行]
#define NET_NO_TALK_CHANNEL			_EC(27)			//don't find out talk channel [未发现对讲通道]
#define NET_NO_AUDIO				_EC(28)			//don't find out audio [未发现音频]
#define NET_NO_INIT					_EC(29)			//CLientSDK not initialize [CLientSDK未经初始化]
#define NET_DOWNLOAD_END			_EC(30)			//download over [下载已结束]
#define NET_EMPTY_LIST				_EC(31)			//the result list of query is empty [查询结果为空]

#define NET_ERROR_GETCFG_SYSATTR	_EC(32)			//fail position while getting configure : system attributes [获取配置失败位置：系统属性]
#define NET_ERROR_GETCFG_SERIAL		_EC(33)			//fail position while getting configure : serial number [获取配置失败位置：序列号]
#define NET_ERROR_GETCFG_GENERAL	_EC(34)			//fail position while getting configure : common attributes [获取配置失败位置：常规属性]
#define NET_ERROR_GETCFG_DSPCAP		_EC(35)			//fail position while getting configure : ability description of DSP [获取配置失败位置：DSP能力描述]
#define NET_ERROR_GETCFG_NETCFG		_EC(36)			//fail position while getting configure : network attributes [获取配置失败位置：网络属性]
#define NET_ERROR_GETCFG_CHANNAME	_EC(37)			//fail position while getting configure : channel name [获取配置失败位置：通道名称]
#define NET_ERROR_GETCFG_VIDEO		_EC(38)			//fail position while getting configure : video attributes [获取配置失败位置：视频属性]
#define NET_ERROR_GETCFG_RECORD		_EC(39)			//fail position while getting configure : configure of timer record [获取配置失败位置：录象定时配置]
#define NET_ERROR_GETCFG_PRONAME	_EC(40)			//fail position while getting configure : protocal name of decoder [获取配置失败位置：解码器协议名称]
#define NET_ERROR_GETCFG_FUNCNAME	_EC(41)			//fail position while getting configure : function name of 232 serial port [获取配置失败位置：232串口功能名称]
#define NET_ERROR_GETCFG_485DECODER	_EC(42)			//fail position while getting configure : attributes of decoder [获取配置失败位置：解码器属性]
#define NET_ERROR_GETCFG_232COM		_EC(43)			//fail position while getting configure : attributes of 232 serial port [获取配置失败位置：232串口属性]
#define NET_ERROR_GETCFG_ALARMIN	_EC(44)			//fail position while getting configure : attributes of alarm-in [获取配置失败位置：外部报警输入属性]
#define NET_ERROR_GETCFG_ALARMDET	_EC(45)			//fail position while getting configure : attributes of picture detect [获取配置失败位置：图像检测报警属性]
#define NET_ERROR_GETCFG_SYSTIME	_EC(46)			//fail position while getting configure : device time [获取配置失败位置：设备时间]
#define NET_ERROR_GETCFG_PREVIEW	_EC(47)			//fail position while getting configure : params of preview [获取配置失败位置：预览参数]
#define NET_ERROR_GETCFG_AUTOMT		_EC(48)			//fail position while getting configure : configure of auto-mantance [获取配置失败位置：自动维护配置]
#define NET_ERROR_GETCFG_VIDEOMTRX	_EC(49)			//fail position while getting configure : configure of video matrix [获取配置失败位置：视频矩阵配置]
#define NET_ERROR_GETCFG_COVER		_EC(50)			//fail position while getting configure : video area shelter [获取配置失败位置：视频区域遮挡]
#define NET_ERROR_GETCFG_WATERMAKE	_EC(51)			//fail position while getting configure : configure of watermask [获取配置失败位置：图象水印配置]
#define NET_ERROR_GETCFG_ETHERNET	_EC(300)		//fail position while getting configure : network card configure [获取配置失败位置：网卡配置]
#define NET_ERROR_GETCFG_WLAN		_EC(301)		//fail position while getting configure : wireless card infomation [获取配置失败位置：无线网络信息]
#define NET_ERROR_GETCFG_WLANDEV	_EC(302)		//fail position while getting configure : search wireless network device [获取配置失败位置：搜索无线网络设备]
#define NET_ERROR_GETCFG_REGISTER	_EC(303)		//fail position while getting configure : configure of auto-register params [获取配置失败位置：主动注册参数配置]
#define NET_ERROR_GETCFG_CAMERA		_EC(304)		//fail position while getting configure : configure of cameral attributes [获取配置失败位置：摄像头属性配置]
#define NET_ERROR_GETCFG_INFRARED	_EC(305)		//fail position while getting configure : configure of infrared ray alarm [获取配置失败位置：红外报警配置]
#define NET_ERROR_GETCFG_SOUNDALARM	_EC(306)		//fail position while getting configure : configure of audio alarm [获取配置失败位置：音频报警配置]
#define NET_ERROR_GETCFG_STORAGE    _EC(307)		//fail position while getting configure : configure of store position [获取配置失败位置：存储位置配置]
#define NET_ERROR_GETCFG_MAIL		_EC(308)		//fail to get email configure [获取邮件配置失败]


#define NET_ERROR_SETCFG_GENERAL	_EC(55)			//fail position while setting configure : common attributes [设置配置失败位置：常规属性]
#define NET_ERROR_SETCFG_NETCFG		_EC(56)			//fail position while setting configure : network attributes [设置配置失败位置：网络属性]
#define NET_ERROR_SETCFG_CHANNAME	_EC(57)			//fail position while setting configure : channel name [设置配置失败位置：通道名称]
#define NET_ERROR_SETCFG_VIDEO		_EC(58)			//fail position while setting configure : video attributes [设置配置失败位置：视频属性]
#define NET_ERROR_SETCFG_RECORD		_EC(59)			//fail position while setting configure : configure of timer record [设置配置失败位置：录象定时配置]
#define NET_ERROR_SETCFG_485DECODER	_EC(60)			//fail position while setting configure : attributes of decoder [设置配置失败位置：解码器属性]
#define NET_ERROR_SETCFG_232COM		_EC(61)			//fail position while setting configure : attributes of 232 serial port [设置配置失败位置：232串口属性]
#define NET_ERROR_SETCFG_ALARMIN	_EC(62)			//fail position while setting configure : attributes of alarm-in [设置配置失败位置：外部报警输入属性]
#define NET_ERROR_SETCFG_ALARMDET	_EC(63)			//fail position while setting configure : attributes of picture detect [设置配置失败位置：图像检测报警属性]
#define NET_ERROR_SETCFG_SYSTIME	_EC(64)			//fail position while setting configure : device time [设置配置失败位置：设备时间]
#define NET_ERROR_SETCFG_PREVIEW	_EC(65)			//fail position while setting configure : preview params [设置配置失败位置：预览参数]
#define NET_ERROR_SETCFG_AUTOMT		_EC(66)			//fail position while setting configure : configure of auto-mantance [设置配置失败位置：自动维护配置]
#define NET_ERROR_SETCFG_VIDEOMTRX	_EC(67)			//fail position while setting configure : configure of video matrix [设置配置失败位置：视频矩阵配置]
#define NET_ERROR_SETCFG_COVER		_EC(69)			//fail position while setting configure : video area shelter [设置配置失败位置：视频区域遮挡]
#define NET_ERROR_SETCFG_WATERMAKE	_EC(60)			//fail position while setting configure : configure of picture watermark [设置配置失败位置：图象水印配置]
#define NET_ERROR_SETCFG_WLAN		_EC(61)			//fail position while setting configure : wireless network information [设置配置失败位置：无线网络信息]
#define NET_ERROR_SETCFG_WLANDEV	_EC(62)			//fail position while setting configure : select wireless network device [设置配置失败位置：选择无线网络设备]
#define NET_ERROR_SETCFG_REGISTER	_EC(63)			//fail position while setting configure : configure of auto-register params [设置配置失败位置：主动注册参数配置]
#define NET_ERROR_SETCFG_CAMERA		_EC(64)			//fail position while setting configure : configure of cameral attributes [设置配置失败位置：摄像头属性配置]
#define NET_ERROR_SETCFG_INFRARED	_EC(65)			//fail position while setting configure : configure of infrared ray alarm [设置配置失败位置：红外报警配置]
#define NET_ERROR_SETCFG_SOUNDALARM	_EC(66)			//fail position while setting configure : configure of audio alarm [设置配置失败位置：音频报警配置]
#define NET_ERROR_SETCFG_STORAGE    _EC(67)			//fail position while setting configure : configure of store position [设置配置失败位置：存储位置配置]

#define NET_AUDIOENCODE_NOTINIT		_EC(70)			//interface of audio code not initialized success [音频编码接口没有成功初始化]
#define NET_DATA_TOOLONGH			_EC(71)			//data too long [数据过长]

#define NET_UNSUPPORTED				_EC(72)			//device don't support this operation [设备不支持该操作]
#define NET_DEVICE_BUSY				_EC(73)			//resource of device not enough [设备资源不足]
#define NET_SERVER_STARTED			_EC(74)			//server had been lauched [服务器已经启动]
#define NET_SERVER_STOPPED			_EC(75)			//server had not been lauched [服务器尚未成功启动]

#define NET_LISTER_INCORRECT_SERIAL	_EC(80)			//inputed serial number is incorrect [输入序列号有误]
#define NET_QUERY_DISKINFO_FAILED	_EC(81)			//fail to get disk infomation [获取硬盘信息失败]

#define NET_LOGIN_ERROR_PASSWORD	_EC(100)		//passwork not correct [密码不正确]
#define NET_LOGIN_ERROR_USER		_EC(101)		//account not exist [帐户不存在]
#define NET_LOGIN_ERROR_TIMEOUT		_EC(102)		//wait to login timeout [等待登录返回超时]
#define NET_LOGIN_ERROR_RELOGGIN	_EC(103)		//account had logined [帐号已登录]
#define NET_LOGIN_ERROR_LOCKED		_EC(104)		//account had been locked [帐号已被锁定]
#define NET_LOGIN_ERROR_BLACKLIST	_EC(105)		//account had been add to black ip list [帐号已被列为黑名单]
#define NET_LOGIN_ERROR_BUSY		_EC(106)		//resource is not enough, system is busy [资源不足，系统忙]
#define NET_LOGIN_ERROR_CONNECT		_EC(107)		//fail to connect to host [连接主机失败"]
#define NET_LOGIN_ERROR_NETWORK		_EC(108)		//fail to connect to network [网络连接失败"]

#define NET_RENDER_SOUND_ON_ERROR	_EC(120)		//Render Library open audio error [Render库打开音频出错]
#define NET_RENDER_SOUND_OFF_ERROR	_EC(121)		//Render Library close audio error [Render库关闭音频出错]
#define NET_RENDER_SET_VOLUME_ERROR	_EC(122)		//Render Library control volumn error [Render库控制音量出错]
#define NET_RENDER_ADJUST_ERROR		_EC(123)		//Render Library set picture param error [Render库设置画面参数出错]
#define NET_RENDER_PAUSE_ERROR		_EC(124)		//Render Library pause error [Render库暂停播放出错]
#define NET_RENDER_SNAP_ERROR		_EC(125)		//Render Library snapshot error [Render库抓图出错]
#define NET_RENDER_STEP_ERROR		_EC(126)		//Render Library step error [Render库步进出错]
#define NET_RENDER_FRAMERATE_ERROR	_EC(127)		//Render Library set frame rate error [Render库设置帧率出错]

#define NET_GROUP_EXIST				_EC(140)		//group name is exist already [组名已存在]
#define	NET_GROUP_NOEXIST			_EC(141)		//group name is not exist [组名不存在]
#define NET_GROUP_RIGHTOVER			_EC(142)		//authorities of the group exceed range of the authority list [组的权限超出权限列表范围]
#define NET_GROUP_HAVEUSER			_EC(143)		//can't delete the group because there are users belong to this group [组下有用户，不能删除]
#define NET_GROUP_RIGHTUSE			_EC(144)		//some authority of the group is using by some user [组的某个权限被用户使用，不能出除]
#define NET_GROUP_SAMENAME			_EC(145)		//new group name is duplicate to some exist group name [新组名同已有组名重复]
#define	NET_USER_EXIST				_EC(146)		//user exist [用户已存在]
#define NET_USER_NOEXIST			_EC(147)		//user not exist [用户不存在]
#define NET_USER_RIGHTOVER			_EC(148)		//the authorities of user excceed to the authorities of group [用户权限超出组权限]
#define NET_USER_PWD				_EC(149)		//reserved account, can't be modified [保留帐号，不容许修改密码]
#define NET_USER_FLASEPWD			_EC(150)		//incorrect password [密码不正确]
#define NET_USER_NOMATCHING			_EC(151)		//password not matched [密码不匹配]


#define NET_CONFIG_DEVBUSY			_EC(999)		//can't set now [暂时无法设置]
#define NET_CONFIG_DATAILLEGAL		_EC(1000)		//data for configure is invalid [配置数据不合法]

//interface for remote configure : CLIENT_GetDEVConfig,CLIENT_GetDEVConfig, their params and commands define [远程配置接口CLIENT_GetDEVConfig,CLIENT_GetDEVConfig参数：命令定义]
#define RV_DEV_DEVICECFG			1		//get device params [获取设备参数]
#define RV_DEV_NETCFG				2		//get network params [获取网络参数]
#define RV_DEV_CHANNELCFG			3		//get channel configure - picture and compress params, etc... [获取通道配置－图像及压缩参数等]
#define RV_DEV_PREVIEWCFG 			4		//get preview params [获取预览参数]
#define RV_DEV_RECORDCFG			5		//get record time params [获取录像时间参数]
#define RV_DEV_COMMCFG				6		//get serial port params [获取串口参数]
#define RV_DEV_ALARMCFG 			7		//get alarm params [获取报警参数]
#define RV_DEV_TIMECFG 				8		//get DVR time [获取DVR时间]
#define RV_DEV_TALKCFG				9		//talk params [对讲参数]
#define RV_DEV_AUTOMTCFG			10		//auto-mantance configure [自动维护配置]		
#define	RV_DEV_VEDIO_MARTIX			11		//configure of local matrix control plot [本机矩阵控制策略配置]	
#define RV_DEV_MULTI_DDNS			12		//configure of multi-DDNS server [多ddns服务器配置]
#define RV_DEV_SNAP_CFG				13		//configure about snapshot [抓图相关配置]
#define RV_DEV_WEB_URL_CFG			14		//configure of HTTP path [HTTP路径配置]
#define RV_DEV_FTP_PROTO_CFG		15		//configure of FTP [FTP上传配置]
#define RV_DEV_INTERVIDEO_CFG		16		//configure of platform connection, param channel means platform type now [平台接入配置，此时channel参数代表平台类型，]
#define RV_DEV_VIDEO_COVER			17		//configure of area shelter [区域遮挡配置]
#define RV_DEV_TRANS_STRATEGY		18		//configure of transport plot, picture quality first / fluency first [传输策略配置，画质优先\流畅性优先]
#define RV_DEV_DOWNLOAD_STRATEGY	19		//configure of record download plot, high download / common download [录象下载策略配置，高速下载\普通下载]
#define RV_DEV_WATERMAKE_CFG		20		//configure of picture watermark [图象水印配置]
#define RV_DEV_WLAN_CFG				21		//configure of wireless network [无线网络配置]
#define RV_DEV_WLAN_DEVICE_CFG		22		//configure of search wireless device [搜索无线设备配置]
#define RV_DEV_REGISTER_CFG			23		//configure of auto-register params [主动注册参数配置]
#define RV_DEV_CAMERA_CFG			24		//configure of cameral attributes [摄像头属性配置]
#define RV_DEV_INFRARED_CFG 		25		//get infrared ray alarm params [获取红外报警参数]
#define RV_DEV_SNIFFER_CFG			26		//configure of capture packet by Sniffer [Sniffer抓包配置]
#define RV_DEV_MAIL_CFG				27		//configure of email, recommend to use this type of configure [邮件配置,建议以后采用此类型配置]
#define RV_DEV_DNS_CFG				28		//configure of DNS server [DNS服务器配置]
#define RV_DEV_NTP_CFG				29		//configure of NTP [NTP配置]
#define RV_DEV_AUDIO_DETECT_CFG		30		//configure of audio detect [音频检测配置]
#define RV_DEV_STORAGE_STATION_CFG  31      //configure of store position [存储位置配置]
#define RV_DEV_PTZ_OPT_CFG			32		//attributes of PTZ operation [云台操作属性]
#define RV_DEV_DDNS_CFG				33		//configure of DDNS [DDNS配置]
#define RV_DEV_UPNP_CFG				34		//configure of UPNP [UPNP配置]
#define RV_DEV_SAVIA_ALARM_CFG		35		//configure of SAVIA alarm params [SAVIA报警参数配置]
#define RV_DEV_SAVIA_COUNT_CFG		36		//SAVIA count [SAVIA数目]
#define RV_DEV_BLACKWHITE_CFG		37		//params of black and white ip list [黑白名单参数]
#define RV_DEV_DDNS_CFG_EX			38		//configure of DDNS [DDNS配置]
#define RV_DEV_DECODER_CFG			39		//configure of decoder [解码器配置]
#define RV_DEV_REG_SERVER_CFG		40		//configure of auto-register [主动注册配置]
#define RV_DEV_DISPLAY_SPLIT		41		//configure of views combine and split [画面分割通道组合配置]
#define RV_DEV_DISPLAY_TOUR			42		//configure of tour [轮巡配置]
#define RV_DEV_DISPLAY_SPLITTOUR	43		//configure of views combine adn split tour [画面分割通道组合轮巡配置]
#define RV_DEV_SNAP_CFG_NEW			44		//configure of snapshot [抓图相关配置]
#define RV_DEV_DECODER_ALARM_CFG	45		//configure of decoder alarm [解码器告警配置]
#define RV_DEV_MARGIN_CFG			46		//configure of TV adjust [TV调节配置]
#define RV_DEV_IPCONFLICT_CFG		47		//configure of IP conflict [IP冲突配置]
#define RV_DEV_MAIL_CFG_EX			48		//new configure of email [新邮箱配置]
#define RV_DEV_DEV_CFG				49		//device name (use new protocal) [设备信息(使用TLV协议)]
#define RV_DEV_CHANNEL_ENC_CFG		50		//code infomation of channel (use new protocal) [设备通道编码信息(使用TLV协议)]
#define RV_DEV_NET_BASE_CFG			51		//basic network configure (use new protocal) [基本网络配置(使用TLV协议)]
#define RV_DEV_NET_APP_CFG			52		//application network configure (use new protocal) [应用网络配置(使用TLV协议)]
#define RV_DEV_ALARM_CFG			53		//get all alarm configure (use new protocal) [获取所有报警配置(使用TLV协议)]
#define RV_DEV_ALARM_IN_CFG			54		//set alarm-in alarm configure (use new protocal) [设置报警输入报警配置(使用TLV协议)]
#define RV_DEV_ALARM_MOTION_CFG		55		//set video detect alarm configure (use new protocal) [设置视频动检报警配置(使用TLV协议)]
#define RV_DEV_ALARM_LOSS_CFG		56		//set video lost alarm configure (use new protocal) [设置视频视频丢失报警配置(使用TLV协议)]
#define RV_DEV_ALARM_BIND_CFG		57		//set video shelter alarm configure (use new protocal) [设置视频视频遮挡报警配置(使用TLV协议)]
#define RV_DEV_ALARM_NODISK_CFG		58		//set no disk alarm configure (use new protocal) [设置无硬盘报警配置(使用TLV协议)]
#define RV_DEV_ALARM_ERRDISK_CFG	59		//set disk error alarm configure (use new protocal) [设置硬盘错误报警配置(使用TLV协议)]
#define RV_DEV_ALARM_FULLDISK_CFG	60		//set disk full alarm configure (use new protocal) [设置硬盘满报警配置(使用TLV协议)]
#define RV_DEV_ALARM_NETBROKEN_CFG	61		//set network disconnect alarm configure (use new protocal) [设置断网报警配置(使用TLV协议)]
#define RV_DEV_ALARM_IPCONFLICT_CFG	62		//set IP conflict alarm configure (use new protocal) [设置IP冲突报警配置(使用TLV协议)]

#define RV_DEV_INTERVIDEO_BELL_CFG	64		//configure of bell platform connection [bell平台接入配置]
#define RV_DEV_INTERVIDEO_MEGA_CFG	65		//configure of HXHT platform connection [互信互通平台接入配置]
#define RV_DEV_INTERVIDEO_VS300_CFG	66		//configure of VS300 platform connection [VS300平台接入配置]
#define RV_DEV_INTERVIDEO_ZXSHENYAN_CFG	67	//configure of SHENYAN platform connection [神眼平台接入配置]

#define RV_DEV_DISK_CFG				80		//configure of disk (use new protocal) [磁盘配置(使用TLV协议)]
#define RV_DEV_NET_COMM_CFG			81		//network common configure (use new protocal) [网络通用配置(使用TLV协议)]
#define RV_DEV_EMAIL_CFG			82		//email configure (use new protocal) [EMAIL配置(使用TLV协议)]
#define RV_DEV_DNS_CFG_TLV			83		//dns configure (use new protocal) [dns配置(使用TLV协议)]
#define RV_DEV_UPNP_CFG_TLV			84		//upnp cpnfigure (use new protocal) [upnp配置(使用TLV协议)]
#define RV_DEV_PPPOE_CFG			85		//pppoe configure (use new protocal) [pppoe配置(使用TLV协议)]
#define RV_DEV_MDDNS_CFG			86		//ddns configure (use new protocal) [DDNS配置(使用TLV协议)]
#define RV_DEV_CODE_CFG				87		//code configure (use new protocal) [编码配置(使用TLV协议)]
#define RV_DEV_NTP_CFG_TLV			88		//NTP configure (use new protocal) [NTP配置(使用TLV协议)]
#define RV_DEV_OUT_MODE_CFG			89		//output mode configure (use new protocal) [输出模式配置(使用TLV协议)]
#define	RV_DEV_PRESET_CFG			90		//configure of PTZ preset [云台预置点配置]
#define RV_DEV_TOUR_CFG				91		//configure of PTZ tour in prestes [云台点间巡航配置]
#define RV_DEV_ADDPRESET_CFG		92		//add preset operation [增加预置点操作]
#define RV_DEV_DELETEPRESET_CFG		93		//delete preset operation [删除预置点操作]
#define	RV_DEV_ADDTOURPRESET_CFG	94		//add preset to tour operation [增加巡航预置点操作]
#define RV_DEV_DELTOURPRESET_CFG	95		//delete preset from tour operation [删除巡航预置点操作]
#define	RV_DEV_CLEARTOUR_CFG		96		//delete tour [删除巡航线路]
#define	RV_DEV_FTP_CFG				97		//FTP configure [FTP设置]
#define	RV_DEV_RTSP_CFG				98		//RTSP configure [RTSP设置]
#define	RV_DEV_INTERED_CFG			99		//configure of intelligent red detect alarm [智能红色检测报警设置]
#define RV_DEV_NETCFG_RHEX			100		//get network params (not 98 serial device remotehost's legth is 64 bytes) [获取网络参数(非98设备remotehost长度64字节)]
#define	RV_DEV_RECCTL_CFG			101		//record control params (use new protocal) [录像控制参数(使用TLV协议)]
#define RV_DEV_COMMCFG_EX			102		//get serial port params (more than 16 channels) [获取串口参数(超过16通道)]
#define RV_DEV_CHANNEL_NAME			103		//get channel name (use new protocal) [获取通道名(使用TLV协议)]
#define RV_DEV_AUDIO_T				104		//audio configure (use new protocal) [音频配置(使用TLV协议)]
#define RV_DEV_DIGICHAN_TOUR		105		//digital channel tour configure (use new protocal) [数字通道轮训配置(使用TLV协议)]
#define RV_DEV_KBD					106		//protocal of control key-board (use new protocal) [控制键盘协议(使用TLV协议)]
#define RV_DEV_MATRIX_XINGHUO		107		//matrix (for XINGHUO Corp.) configure (use new protocal) [矩阵(星火)配置(使用TLV协议)]
#define RV_DEV_RTSP_CFGEX			108		//get RTSP infomation (not use new protocal) [获取RTSP信息(使用非TLV协议)]
#define RV_DEV_NTP_CFGEX			109		//get NTP infomation (not use new protocal) [获取NTP信息(使用非TLV协议)]
#define RV_DEV_OSDZOOM_CFG			110		//Get OSD zoom infomation(use new protocal)	[获取OSD zoom信息(使用TLV协议)]
//added by zhubo 
#define RV_DEV_MATRIX_CIDPID        111     //Get the CID and PID relation (use new protocol)[获取矩阵配置中通道与矩阵号的对应关系]
#define RV_DEV_SVAC_CFG				112		//Get SVAC infomation(use new protocal) [获取SVAC设置信息(使用TLV协议)]

#define RV_DEV_USER_END_CFG			1000

////////////////constant abount remote configure struct [远程配置结构体相关常量]///////////////////////
#define RV_MAX_MAIL_ADDR_LEN		128	//max length of email sender's or receiver's address [邮件发(收)人地址最大长度]
#define RV_MAX_MAIL_SUBJECT_LEN		64	//max length of email title [邮件主题最大长度]
#define RV_MAX_IPADDR_LEN			16	//max length of IP address [IP地址字符串长度]
#define RV_MACADDR_LEN				40	//max length of MAC address [MAC地址字符串长度]
#define RV_MAX_URL_LEN				128	//max length of URL [URL字符串长度]
#define RV_MAX_DEV_ID_LEN			48	//max length of code number of machine [机器编号最大长度]
#define	RV_MAX_HOST_NAMELEN			64  //max length of host name [主机名字符串长度]
#define RV_MAX_HOST_PSWLEN			32	//max length of password [长度]
#define RV_MAX_HOST_PSWLEN_EX		64	//max length of password extend [长度]
#define RV_MAX_NAME_LEN				16	//max length of common name [通用名字字符串长度]
#define RV_MAX_NAME_LEN_EX			32	//max length of email user name [邮箱用户名字符串长度]	
#define RV_MAX_ETHERNET_NUM			2	//max number of ethernet interface 以太网口最大个数]
#define	RV_DEV_SERIALNO_LEN			48	//max length of serial number string [序列号字符串长度]
#define RV_DEV_TYPE_LEN				32	//max length of device type string [设备类型字符串长度]
#define RV_N_WEEKS					7	//number of days per week [一周的天数]
#define RV_N_TSECT					6	//number of common time slice [通用时间段个数]
#define RV_N_REC_TSECT				6	//number of record time slice [录像时间段个数]
#define RV_N_COL_TSECT				2	//number of color time slice [颜色时间段个数]	
#define RV_CHAN_NAME_LEN			32	//channel name length, limit to dvr DSP ability, max 32 bytes [通道名长度,dvr DSP能力限制，最多32字节]		
#define RV_N_ENCODE_AUX				3	//number of assist bit-stream [扩展码流个数]
#define RV_N_TALK					1	//max talk channel number [最多对讲通道个数]
#define RV_N_COVERS					1	//number of shelter area [遮挡区域个数]	
#define RV_N_CHANNEL				16	//max number of channel [最大通道个数]	
#define RV_N_ALARM_TSECT			2	//number of alarm prompt time slice [报警提示时间段个数]
#define RV_MAX_ALARMOUT_NUM			16	//upper limit of number of alarm-out interface [报警输出口个数上限]
#define RV_MAX_VIDEO_IN_NUM			16	//upper limit of number of video input interface [视频输入口个数上限]
#define RV_MAX_ALARM_IN_NUM			16	//upper limit of number of alarm-in interface [报警输入口个数上限]
#define RV_MAX_DISK_NUM				16	//upper limit of number of disk, be 16 now[硬盘个数上限，暂定为16]
#define RV_MAX_DECODER_NUM			16	//upper limit of number of decoder(485) [解码器（485）个数上限]	
#define RV_MAX_DECODER_NUM_EX		32	//upper limit of number of decoder [解码器个数上限]	
#define RV_MAX_232FUNCS				10	//upper limit of number of function of 232 serial port [232串口功能个数上限]
#define RV_MAX_232_NUM				2	//upper limit of number of 232 serial port [232串口个数上限]
#define RV_MAX_DECPRO_LIST_SIZE		100	//upper limit of number of protocal of decoder [解码器协议列表个数上限]
#define RV_FTP_MAXDIRLEN			240	//max length of FTP file path [FTP文件目录最大长度]
#define RV_MATRIX_MAXOUT			16	//upper limit of number of matrix output interface [矩阵输出口最大个数]
#define RV_TOUR_GROUP_NUM			6	//upper limit of number of matrix output group [矩阵输出组最大个数]
#define RV_MAX_DDNS_NUM				10	//upper limit of number of ddns server supported by device [设备支持的ddns服务器最大个数]
#define RV_MAX_SERVER_TYPE_LEN		32	//max length of ddns server type string [ddns服务器类型 最大字符串长度]
#define RV_MAX_DOMAIN_NAME_LEN		256	//max length of ddns server domain [ddns域名 最大字符串长度]
#define RV_MAX_DDNS_ALIAS_LEN		32	//max length of ddns server other name [ddns服务器别名 最大字符串长度]
#define RV_MOTION_ROW				32	//row number of motion detect [动态检测区域的行数]
#define RV_MOTION_COL				32	//collumn number of moton detect [动态检测区域的列数]
#define	RV_FTP_USERNAME_LEN			64  //FTP configure : max size of user name [FTP配置，用户名最大长度]
#define	RV_FTP_PASSWORD_LEN			64  //FTP configure : max size of password [FTP配置，密码最大长度]
#define	RV_TIME_SECTION				2	//FTP configure : max size of time slice per day [FTP配置，每天时间段个数]
#define RV_FTP_MAX_PATH				240	//FTP configure : max size of file path name [FTP配置，文件路径名最大长度]
#define RV_INTERVIDEO_UCOM_CHANID	32	//platform connection configure : U WANGTONG channel ID [平台接入配置，U网通通道ID]
#define RV_INTERVIDEO_UCOM_DEVID	32	//platform connection configure : U WANGTONG device ID [平台接入配置，U网通设备ID]
#define RV_INTERVIDEO_UCOM_REGPSW	16	//platform connection configure : U WANGTONG password of registration [平台接入配置，U网通注册密码]
#define RV_INTERVIDEO_UCOM_USERNAME	32	//platform connection configure : U WANGTONG user name [平台接入配置，U网通用户名]
#define RV_INTERVIDEO_UCOM_USERPSW	32	//platform connection configure : U WANGTONG password [平台接入配置，U网通密码]
#define RV_INTERVIDEO_NSS_IP		32	//platform connection configure : ZHONGXINGLIWEI IP [平台接入配置，中兴力维IP]
#define RV_INTERVIDEO_NSS_SERIAL	32	//platform connection configure : ZHONGXINGLIWEI serial [平台接入配置，中兴力维serial]
#define RV_INTERVIDEO_NSS_USER		32	//platform connection configure : ZHONGXINGLIWEI user [平台接入配置，中兴力维user]
#define RV_INTERVIDEO_NSS_PWD		50	//platform connection configure : ZHONGXINGLIWEI password [平台接入配置，中兴力维password]

#define RV_MAX_VIDEO_COVER_NUM		16	//max number of area shelter [遮挡区域最大个数]
#define RV_MAX_WATERMAKE_DATA		4096//max length of watermark picture data [水印图片数据最大长度]
#define RV_MAX_WATERMAKE_LETTER		128	//max length of watermark text [水印文字最大长度]
#define RV_MAX_WLANDEVICE_NUM		10	//max number of searched wireless device [最多搜索出的无线设备个数]
#define RV_MAX_ALARM_NAME			64	//address length [地址长度]
#define RV_MAX_REGISTER_SERVER_NUM	10	//number of auto-register sever [主动注册服务器个数]
#define RV_SNIFFER_FRAMEID_NUM		6   //6 FRAME ID options [6个FRAME ID 选项]
#define RV_SNIFFER_CONTENT_NUM		4   //4 captured package content per FRAME [每个FRAME对应的4个抓包内容]
#define RV_MAX_PROTOCOL_NAME_LENGTH 20
#define RV_SNIFFER_GROUP_NUM		4   //4 groups capture package configure [4组抓包设置]
#define MAX_PATH_STOR				240 //length of remnote folder [远程目录的长度]
#define MAX_HHCHANNELNAME_LEN		32	//digital channel name length [数字通道名称长度]
#define RV_MAX_SAVIA_NUM			16	//max number of savia count [savia数目最大值]
#define RV_MAX_BLACK_IP_NUM			128	//max number of black ip [黑名单数目最大值]
#define RV_MAX_WHITE_IP_NUM			128	//max number of white ip [白名单数目最大值]
#define RV_MAX_DECODER_CHAN_NUM		32	//max number of dcoder channel [解码器通道数目最大值]


//resolve list, be used to very bit-mask with resolve mask value [分辨率列表，用于与分辨率掩码进行与、或操作]
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

//attributes of PTZ [云台属性列表]
//lowMask
#define PTZ_DIRECTION				0x00000001				//direction [/*!< 方向 */]
#define PTZ_ZOOM					0x00000002	   			//zoom [/*!< 变倍 */]
#define PTZ_FOCUS					0x00000004				//focus [/*!< 聚焦 */]
#define PTZ_IRIS					0x00000008				//aperture [/*!< 光圈 */]
#define PTZ_ALARM					0x00000010				//alarm function [/*!< 报警功能 */]
#define PTZ_LIGHT					0x00000020				//lamp [/*!< 灯光 */]
#define PTZ_SETPRESET				0x00000040				//set preset [/*!< 设置预置点 */]
#define PTZ_CLEARPRESET				0x00000080				//clear preset [/*!< 清除预置点 */]
#define PTZ_GOTOPRESET				0x00000100				//move to preset [/*!< 转至预置点 */]
#define PTZ_AUTOPANON				0x00000200				//horizontal start [/*!< 水平开始 */]
#define PTZ_AUTOPANOFF				0x00000400				//horizontal stop [/*!< 水平结束 */]
#define PTZ_SETLIMIT				0x00000800				//set bound [/*!< 设置边界 */]
#define PTZ_AUTOSCANON				0x00001000				//auto scan start [/*!< 自动扫描开始 */]
#define PTZ_AUTOSCANOFF				0x00002000				//auto scan stop [/*!< 自动扫描开停止 */]
#define PTZ_ADDTOUR					0x00004000				//add preset to tour [/*!< 增加巡航点 */]
#define PTZ_DELETETOUR				0x00008000				//delete preset from tour [/*!< 删除巡航点 */]
#define PTZ_STARTTOUR				0x00010000				//start tour [/*!< 开始巡航 */]
#define PTZ_STOPTOUR				0x00020000				//end tour [/*!< 结束巡航 */]
#define PTZ_CLEARTOUR				0x00040000				//clear tour [/*!< 删除巡航 */]
#define PTZ_SETPATTERN				0x00080000				//set mode [/*!< 设置模式 */]
#define PTZ_STARTPATTERN			0x00100000				//start mode [/*!< 开始模式 */]
#define PTZ_STOPPATTERN				0x00200000				//stop mode [/*!< 停止模式 */]
#define PTZ_CLEARPATTERN			0x00400000				//clear mode [/*!< 清除模式 */]
#define PTZ_POSITION				0x00800000				//fast locate [/*!< 快速定位 */]
#define PTZ_AUX						0x01000000				//assist switch [/*!< 辅助开关 */]
#define PTZ_MENU					0x02000000				//menu of PTZ cameral [/*!< 球机菜单 */]
#define PTZ_EXIT					0x04000000				//exit from menu of PTZ cameral [/*!< 退出球机菜单 */]
#define PTZ_ENTER					0x08000000				//confirm [/*!< 确认 */]
#define PTZ_ESC						0x10000000				//cancel [/*!< 取消 */]
#define PTZ_MENUUPDOWN				0x20000000				//up and down menu [/*!< 菜单上下操作 */]
#define PTZ_MENULEFTRIGHT			0x40000000				//left and right operation of menu [/*!< 菜单左右操作 */]
#define PTZ_OPT_NUM					0x80000000				//number of operation [/*< 操作的个数 */]

//hiMask
#define PTZ_DEV						0x00000001				//PTZ control [/*!< 云台控制 */]
#define PTZ_MATRIX					0x00000002				//matrix control [/*!< 矩阵控制 */]

//code mode list, can be used to very bit-mask with code mode mask value [编码模式列表，用于与编码模式掩码进行与、或操作]
#define RV_CAPTURE_COMP_DIVX_MPEG4	0x00000001
#define RV_CAPTURE_COMP_MS_MPEG4 	0x00000002
#define RV_CAPTURE_COMP_MPEG2		0x00000004
#define RV_CAPTURE_COMP_MPEG1		0x00000008
#define RV_CAPTURE_COMP_H263		0x00000010
#define RV_CAPTURE_COMP_MJPG		0x00000020
#define RV_CAPTURE_COMP_FCC_MPEG4	0x00000040
#define RV_CAPTURE_COMP_H264		0x00000080

//bit-stream control list [码流控制列表]
#define RV_CAPTURE_BRC_CBR			0
#define RV_CAPTURE_BRC_VBR			1
//#define RV_CAPTURE_BRC_MBR			2

//alarm linkage, be used to very bit-mask with linkage mask value [报警联动动作，用于与报警联动动作掩码进行与、或操作]
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

//"restore default configure" mask, several value can or ["恢复默认设置"掩码，多个设置可用或操作]
#define RV_RESTORE_COMMON			0x00000001	//common configure [普通设置]
#define RV_RESTORE_CODING			0x00000002	//code configure [编码设置]
#define RV_RESTORE_VIDEO			0x00000004	//record configure [录像设置]
#define RV_RESTORE_COMM				0x00000008	//serial port configure [串口设置]
#define RV_RESTORE_NETWORK			0x00000010	//network configure [网络设置]
#define RV_RESTORE_ALARM			0x00000020	//alarm configure [报警设置]
#define RV_RESTORE_VIDEODETECT		0x00000040	//video detect [视频检测]
#define RV_RESTORE_PTZ				0x00000080	//PTZ control [云台控制]
#define RV_RESTORE_OUTPUTMODE		0x00000100	//output mode [输出模式]
#define RV_RESTORE_CHANNELNAME		0x00000200	//channel name [通道名称]
#define RV_RESTORE_ALL				0x80000000	//all reset [全部重置]


////////////////end of constant abount remote configure struct [end of远程配置结构体相关常量]///////////////////////


/************************************************************************
** enum define [枚举定义]
***********************************************************************/
//device type [设备类型]
enum NET_DEVICE_TYPE 
{
	NET_PRODUCT_NONE = 0,
	NET_DVR_NONREALTIME_MACE, //not real-time MACE [/*!< 非实时MACE */]
	NET_DVR_NONREALTIME, //not real-time [/*!< 非实时 */]
	NET_NVS_MPEG1, //network video server [/*!< 网络视频服务器 */]
	NET_DVR_MPEG1_2, //MPEG1 two channel recoder [/*!< MPEG1二路录像机 */]
	NET_DVR_MPEG1_8, //MPEG1 eight channel recoder [/*!< MPEG1八路录像机 */]
	NET_DVR_MPEG4_8, //MPEG4 eight channel recoder [/*!< MPEG4八路录像机 */]
	NET_DVR_MPEG4_16, //MPEG4 sixteen channel recoder [/*!< MPEG4十六路录像机 */]
	NET_DVR_MPEG4_SX2, //LB serial recoder [/*!< LB系列录像机 */]
	NET_DVR_MEPG4_ST2, //GB serial recoder [/*!< GB系列录像机 */]
	NET_DVR_MEPG4_SH2, //HB serial recoder [/*!< HB系列录像机 */]
	NET_DVR_MPEG4_GBE, //GBE serial recoder [/*!< GBE系列录像机 */]
	NET_DVR_MPEG4_NVSII, //the II genaration of network vider server [/*!< II代网络视频服务器 */]
	NET_DVR_STD_NEW, //new standard configure protocal [/*!< 新标准配置协议 */]
	NET_DVR_DDNS, //DDNS server [/*DDNS服务器*/]
	NET_DVR_ATM,  //ATM machine [/* ATM机 */]
	NET_NB_SERIAL, //the II genaration not real-time NB serial machine [/* 二代非实时NB系列机器 */]
	NET_LN_SERIAL, //LN serial products [/* LN系列产品 */]
	NET_BAV_SERIAL, //BAV serial products [/* BAV系列产品 */]
	NET_SDIP_SERIAL, //SDIP serial products [/* SDIP系列产品 */]
	NET_IPC_SERIAL, //IPC serial products [/* IPC系列产品 */]
	NET_NVS_B,		//NVS B serial products [/* NVS B系列 */]
	NET_NVS_C,		//NVS H serial products [/* NVS H系列 */]
	NET_NVS_S,		//NVS S serial products [/* NVS S系列 */]
	NET_NVS_E,		//NVS E serial products [/* NVS E系列 */]
	NET_DVR_NEW_PROTOCOL //query device type form QueryDevState, format it as string [/*从QueryDevState中查询设备类型,以字符串格式*/]
};

#define DH_MAX_IPADDR_LEN			16			//max size of IP address string [IP地址字符串长度]
#define DH_MACADDR_LEN				40			//max size of MAC address string [MAC地址字符串长度]
#define DH_DEV_TYPE_LEN				32			//max size of device type string [设备类型字符串长度]

//configure file type, for CLIENT_ExportConfigFile interface [配置文件类型，供CLIENT_ExportConfigFile接口使用]
typedef enum __DH_CONFIG_FILE_TYPE
{
	DH_CONFIGFILE_ALL = 0,						//all configure file [全部配置文件]
	DH_CONFIGFILE_LOCAL,						//local configure file [本地配置文件]
	DH_CONFIGFILE_NETWORK,						//network configure file [网络配置文件]
	DH_CONFIGFILE_USER,							//user configure file [用户配置文件]
} DH_CONFIG_FILE_TYPE;

//corresponding CLIENT_SearchDevices interface [对应CLIENT_SearchDevices接口]
typedef struct 
{
	char				szIP[DH_MAX_IPADDR_LEN];		//IP [IP]
	int					nPort;							//port [端口]
	char				szSubmask[DH_MAX_IPADDR_LEN];	//sub net mask [子网掩码]
	char				szGateway[DH_MAX_IPADDR_LEN];	//gateway [网关]
	char				szMac[DH_MACADDR_LEN];			//MAC address [MAC地址]
	char				szDeviceType[DH_DEV_TYPE_LEN];	//device type [设备类型]
	BYTE				bReserved[32];					//reserved [保留字节]
} DEVICE_NET_INFO;

//set params on logining [设置登入时的相关参数]
typedef struct  
{
	int					nWaittime;				//wait time-out time (unit:millisecond), 0 means default 500ms [等待超时时间(毫秒为单位)，为0默认5000ms]
	int					nConnectTime;			//connect time-out time (unit:millisecond), 0 means default 1500ms [连接超时时间(毫秒为单位)，为0默认1500ms]
	int					nConnectTryNum;			//try to connect times, 0 means 1 time [连接尝试次数，为0默认1次]
	int					nSubConnectSpaceTime;	//wait time between sub connection (unit:millisecond), 0 means default 10ms [子连接之间的等待时间(毫秒为单位),为0默认10ms]
	int					nGetDevInfoTime;		//get device info time-out time (unit:millisecond), 0 means default 500ms [获取设备信息超时时间，为0默认500ms.]
	int					nConnectBufSize;		//buffer size per connection (unit:byte), 0 means default 250*1024 [每个连接接收数据缓冲大小(字节为单位)，为0默认250*1024]
	BYTE				bReserved[28];			//reserved [保留字段]
} NET_PARAM;

//common PTZ control commands [通用云台控制命令]
typedef enum _PTZ_ControlType
{
	RV_PTZ_UP_CONTROL = 0,			//up [上]
	RV_PTZ_DOWN_CONTROL,			//down [下]
	RV_PTZ_LEFT_CONTROL,			//left [左]
	RV_PTZ_RIGHT_CONTROL,			//right [右]
	RV_PTZ_ZOOM_ADD_CONTROL,		//zoom+ [变倍+]
	RV_PTZ_ZOOM_DEC_CONTROL,		//zoom- [变倍-]
	RV_PTZ_FOCUS_ADD_CONTROL,		//focus+ [调焦+]
	RV_PTZ_FOCUS_DEC_CONTROL,		//focus- [调焦-]
	RV_PTZ_APERTURE_ADD_CONTROL,	//aperture+ [光圈+]
	RV_PTZ_APERTURE_DEC_CONTROL,    //aperture- [光圈-]
	RV_PTZ_POINT_MOVE_CONTROL,      //move to preset [转至预置点]
	RV_PTZ_POINT_SET_CONTROL,       //set [设置]
	RV_PTZ_POINT_DEL_CONTROL,       //delete [删除]
	RV_PTZ_POINT_LOOP_CONTROL,      //tour in presets [点间巡航]
	RV_PTZ_LAMP_CONTROL             //lamp and wiper [灯光雨刷]
}RV_PTZ_ControlType;

//common PTZ control extended commands [云台控制扩展命令]
typedef enum _EXTPTZ_ControlType
{
	RV_EXTPTZ_LEFTTOP = 0X20,		//left-up [左上]
	RV_EXTPTZ_RIGHTTOP ,			//right-up [右上]
	RV_EXTPTZ_LEFTDOWN ,			//left-down [左下]
	RV_EXTPTZ_RIGHTDOWN,			//right-down [右下]
	RV_EXTPTZ_ADDTOLOOP,			//add preset to tour : tour : preset [加入预置点到巡航	巡航线路	预置点值]	
	RV_EXTPTZ_DELFROMLOOP,			//delete preset from tour : tour : preset [删除巡航中预置点	巡航线路	预置点值]	
	RV_EXTPTZ_CLOSELOOP,			//cleat tour : tour [清除巡航	巡航线路]
	RV_EXTPTZ_STARTPANCRUISE,		//start horizontal rotate [开始水平旋转]			
	RV_EXTPTZ_STOPPANCRUISE,		//stop horizontal rotate [停止水平旋转]			
	RV_EXTPTZ_SETLEFTBORDER,		//set left bound [设置左边界]			
	RV_EXTPTZ_SETRIGHTBORDER,		//set right bound [设置右边界]			
	RV_EXTPTZ_STARTLINESCAN,		//start line scan [开始线扫]			
	RV_EXTPTZ_CLOSELINESCAN,		//stop line scan [停止线扫]			
	RV_EXTPTZ_SETMODESTART,			//start set mode : mode [设置模式开始	模式线路]		
	RV_EXTPTZ_SETMODESTOP,			//stop set mode : mode [设置模式结束	模式线路]		
	RV_EXTPTZ_RUNMODE,				//run mode : mode [运行模式	模式线路]		
	RV_EXTPTZ_STOPMODE,				//stop mode : mode [停止模式	模式线路]		
	RV_EXTPTZ_DELETEMODE,			//cleat mode : mode [清除模式	模式线路]		
	RV_EXTPTZ_REVERSECOMM,			//overturn command [翻转命令]			
	RV_EXTPTZ_FASTGOTO,				//fast locate : horizontal coordinate (8192) : vertical coordinate (8192) : zoom (4) [快速定位	水平坐标(8192)	垂直坐标(8192)	变倍(4)]
	RV_EXTPTZ_AUXIOPEN,				//assist switch open : assist point [辅助开关开	辅助点]	
	RV_EXTPTZ_AUXICLOSE,			//assist switch close : assist point [辅助开关关	辅助点]
	RV_EXTPTZ_OPENMENU = 0X36,		//open menu of PTZ cameral [打开球机菜单]
	RV_EXTPTZ_CLOSEMENU ,			//close menu [关闭菜单]
	RV_EXTPTZ_MENUOK,				//confirm on menu [菜单确定]
	RV_EXTPTZ_MENUCANCEL,			//cancel on menu [菜单取消]
	RV_EXTPTZ_MENUUP,				//up on menu [菜单上]
	RV_EXTPTZ_MENUDOWN,				//down on menu [菜单下]
	RV_EXTPTZ_MENULEFT,				//left on menu [菜单左]
	RV_EXTPTZ_MENURIGHT,			//right on menu [菜单右]
	RV_EXTPTZ_ALARMHANDLE = 0x40,	//alarm linkage PTZ, param1:alarm-in channel, param2:alarm linkage type, 1-preset,2-line scan,3-tour, param3:linkage value, for example:preset number [报警联动云台 parm1:报警输入通道 parm2:报警联动类型1-预置点2-线扫3-巡航 parm3:联动值，如预置点号]
	RV_EXTPTZ_MATRIXSWITCH = 0x41,	//matrix switch, patam1:watcher number(video out number), param2:(video in number), param3:matrix number [矩阵切换 parm1:监视器号(视频输出号) parm2:(视频输入号) parm3:矩阵号]
	RV_EXTPTZ_LIGHTCONTROL,			//lamp controler [灯光控制器]
	RV_EXTPTZ_UP_TELE = 0x70,		//up + TELE, param1=speed(1-8), the same as next [上 + TELE，param1=速度（1-8），下同]
	RV_EXTPTZ_DOWN_TELE,			//down + TELE [下 + TELE]
	RV_EXTPTZ_LEFT_TELE,			//left + TELE [左 + TELE]
	RV_EXTPTZ_RIGHT_TELE,			//right + TELE [右 + TELE]
	RV_EXTPTZ_LEFTUP_TELE,			//left-up + TELE [左上 + TELE]
	RV_EXTPTZ_LEFTDOWN_TELE,		//left-down + TELE [左下 + TELE]
	RV_EXTPTZ_TIGHTUP_TELE,			//right-up + TELE [右上 + TELE]
	RV_EXTPTZ_RIGHTDOWN_TELE,		//right-down + TELE [右下 + TELE]
	RV_EXTPTZ_UP_WIDE,				//up + WIDE,param1=speed(1-8), the same as next [上 + WIDE，param1=速度（1-8），下同]
	RV_EXTPTZ_DOWN_WIDE,			//down + WIDE [下 + WIDE]
	RV_EXTPTZ_LEFT_WIDE,			//left + WIDE [左 + WIDE]
	RV_EXTPTZ_RIGHT_WIDE,			//right + WIDE [右 + WIDE]
	RV_EXTPTZ_LEFTUP_WIDE,			//left-up + WIDE [左上 + WIDE]
	RV_EXTPTZ_LEFTDOWN_WIDE,		//left-down + WIDE [左下 + WIDE]
	RV_EXTPTZ_TIGHTUP_WIDE,			//right-up + WIDE [右上 + WIDE]
	RV_EXTPTZ_RIGHTDOWN_WIDE,		//right-down + WIDE [右下 + WIDE]
	RV_EXTPTZ_TOTAL,				//max command value [最大命令值]
	RV_EXTPTZ_RESET,				//reset [复位]
}RV_EXTPTZ_ControlType;

//IO control command [IO控制命令]
typedef enum _IOTYPE
{
	RV_ALARMINPUT = 1,			//alarm input [报警输入]
	RV_ALARMOUTPUT = 2,			//alarm output [报警输出]

	RV_DECODER_ALARMOUT = 3,	//alarm decoder output [报警解码器输出]
	RV_WIRELESS_ALARMOUT =5,    //wireless alarm output [无线报警输出]
	RV_ALARM_TRIGGER_MODE = 7,
}RV_IOTYPE;

//params of extended interface for query log : log type [查询日志扩展接口参数：设备日志类型]
typedef enum _RV_LOG_QUERY_TYPE
{
	DHLOG_ALL = 0,		//all log [所有日志]
	DHLOG_SYSTEM,		//system log [系统日志]
	DHLOG_CONFIG,		//configure log [配置日志]
	DHLOG_STORAGE,		//store log [存储相关]
	DHLOG_ALARM,		//alarm log [报警日志]
	DHLOG_RECORD,		//record log [录象相关]
	DHLOG_ACCOUNT,		//account log [帐号相关]
	DHLOG_CLEAR,		//clear log [清除日志]
	DHLOG_PLAYBACK		//replay log [回放相关]
}RV_LOG_QUERY_TYPE;

//log infomation struct returned - log type [返回的日志信息结构体－日志类型]
typedef enum _RV_LOG_TYPE
{
	//system logs
	RV_LOG_REBOOT = 0x0000,
	RV_LOG_SHUT,
	//config logs
	RV_LOG_CONFSAVE = 0x0100,
	RV_LOG_CONFLOAD,
	//fs logs
	RV_LOG_FSERROR = 0x0200,   //error in file system [文件系统错误]
	RV_LOG_HDD_WERR,           //error in disk writing [硬盘写错误]
	RV_LOG_HDD_RERR,           //error in disk reading[硬盘读错误]
	RV_LOG_HDD_TYPE,           //set disk type [设置硬盘类型]
	RV_LOG_HDD_FORMAT,         //format disk [格式化硬盘]
	//alarm logs
	RV_LOG_ALM_IN = 0x0300,
	RV_LOG_ALM_END = 0x0302,
	RV_LOG_INFRAREDALM_IN = 0x03a0, //wireless alarm input [无线报警输入]
	RV_LOG_INFRAREDALM_END,			//wireless alarm end [无线报警结束]
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

//log infomation struct returned by interface CLIENT_QueryLogEx - log type [接口CLIENT_QueryLogEx返回的日志信息结构体－日志类型]
//condition:int nType = 1;param reserved = &nType. [条件：int nType = 1;参数reserved = &nType.]
typedef enum _RV_NEWLOG_TYPE
{
	//system logs
	RV_NEWLOG_REBOOT	 = 0x0000,		//system reboot [系统重启]
	RV_NEWLOG_SHUT,						//system shutdown [系统关机]

	//config logs
	RV_NEWLOG_CONFSAVE = 0x0100,
	RV_NEWLOG_CONFLOAD,

	//fs logs
	RV_NEWLOG_FSERROR	 = 0x0200,		//error in file system [文件系统错误]
	RV_NEWLOG_HDD_WERR,					//error in disk writing [硬盘写错误]
	RV_NEWLOG_HDD_RERR,					//error in disk reading [硬盘读错误]
	RV_NEWLOG_HDD_TYPE,					//set disk type [设置硬盘类型]
	RV_NEWLOG_HDD_FORMAT,				//format disk [格式化硬盘]
	RV_NEWLOG_HDD_NOSPACE,				//current work space not enough [当前工作盘空间不足]

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
	RV_NEWLOG_SEARCHLOG,				//query log [查询日志]

	//record operation
	RV_NEWLOG_SEARCH	 = 0x0700,		//record query [录像查询]
	RV_NEWLOG_DOWNLOAD,					//record download [录像下载]
	RV_NEWLOG_PLAYBACK,					//record replay [录像回放]
	RV_NEWLOG_BACKUP,					//backup record file [/*!< 备份录像文件 */]
	RV_NEWLOG_BACKUPERROR,				//backup record file fail [/*!< 备份录像文件失败 */]

	RV_NEWLOG_TYPE_NR = 8,		
}RV_NEWLOG_TYPE;


//added params of extended interface for real-time preview : preview type [实时预览扩展接口增加的参数：预览类型]
typedef enum _RealPlayType
{
	RV_RType_Realplay = 0,	//real-time preview [实时预览]
	RV_RType_Multiplay,		//multi-views preview [多画面预览]

	RV_RType_Realplay_0,	//real-time watch - main stream, the same as RV_RType_Realplay [实时监视-主码流，等同于RV_RType_Realplay]
	RV_RType_Realplay_1,	//real-time watch - assist stream1 [实时监视-从码流1]
	RV_RType_Realplay_2,	//real-time watch - assist stream2 [实时监视-从码流2]
	RV_RType_Realplay_3,	//real-time watch - assist stream3 [实时监视-从码流3]

	RV_RType_Multiplay_1,	//multi-views preview : 1 view[多画面预览－1画面]
	RV_RType_Multiplay_4,	//multi-views preview : 4 view[多画面预览－4画面]
	RV_RType_Multiplay_8,	//multi-views preview : 8 view[多画面预览－8画面]
	RV_RType_Multiplay_9,	//multi-views preview : 6 view[多画面预览－9画面]
	RV_RType_Multiplay_16,	//multi-views preview : 16 view[多画面预览－16画面]

	RV_RType_Multiplay_6,	//multi-views preview : 6 view[多画面预览－6画面]
	RV_RType_Multiplay_12,	//multi-views preview : 12 view[多画面预览－12画面]
} RV_RealPlayType;

//params of interface for device control : control type define [设备控制接口参数：控制类型定义]
typedef enum _CtrlType
{
	RV_CTRL_REBOOT = 0,	//reboot device [重启设备]
	RV_CTRL_SHUTDOWN,	//shutdown device [关闭设备]
	RV_CTRL_DISK,		//disk manage [硬盘管理]
	//network key-board [网络键盘]
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
	//trigger alarm [触发报警]
	RV_TRIGGER_ALARM_IN = 100,
	RV_TRIGGER_ALARM_OUT,
	//matrix control [矩阵控制]
	RV_CTRL_MATRIX,
	//SD card control(ipc products), params are same as disk control [SD卡控制（ipc产品）参数同硬盘控制]
	RV_CTRL_SDCARD,
	//imprinting control [刻录机控制]
	RV_BURNING_START,		//start imprinting [开始刻录]
	RV_BURNING_STOP,		//stop imprinting [结束刻录]

	RV_BURNING_ADDPWD,	//overprint password (string end with 0, max size 8 bytes) [叠加密码(以0为结尾的字符串,最大长度8位)]
	RV_BURNING_ADDHEAD,	//overprint head leader (string end with 0, max size 1024 bytes, support multi-lines, line seperator is '\n') [叠加片头(以0为结尾的字符串,最大长度1024字节,支持分行,行分隔符'\n')，]
	RV_BURNING_ADDSIGN,	//overprint dot to imprinting (no params) [叠加打点到刻录信息(参数无)]
	RV_BURNING_ADDCURSTOMINFO,	//self define overprint (string end with 0, max size 1024 bytes, support multi-lines, line seperator is '\n') [自定义叠加(以0为结尾的字符串,最大长度1024字节,支持分行,行分隔符'\n')]

	//restore device's efault configure [恢复设备的默认设置]
	RV_CTRL_RESTOREDEFAULT,

	//device tigger DSP snapshot [设备触发DSP抓图]
	RV_CTRL_CAPTURE_START,		//trigger device snapshot [触发设备抓图]

	//cleat log [清除日志]
	RV_CTRL_CLEARLOG,
	//wireless alarm [无线报警]
	RV_TRIGGER_ALARM_WIRELESS = 200,
}CtrlType;

//configure type, the interface which using this enum has been die out, not use please [配置类型，目前使用该枚举的接口已淘汰，请不要使用]
typedef enum _CFG_INDEX
{
	CFG_GENERAL =  0,		//common [普通]
	CFG_COMM   		,		//serial port [串口]
	CFG_NET    		,		//network [网络]
	CFG_RECORD 		,		//record [录像]
	CFG_CAPTURE		,		//picture configure [图像设置]
	CFG_PTZ    		,		//PTZ [云台]
	CFG_DETECT 		,		//motion detect [动态检测]
	CFG_ALARM  		,		//alarm [报警]
	CFG_DISPLAY		,		//display [显示]
	CFG_RESERVED	,		//reserved,  for continuity [保留，使类型连贯]
	CFG_TITLE  		=10,	//channel title [通道标题]
	CFG_MAIL  		=11,	//emial function [邮件功能]
	CFG_EXCAPTURE	=12,	//preview picture configure [预览图像设置]
	CFG_PPPOE		=13,	//pppoe configure [pppoe设置]
	CFG_DDNS		=14,	//DDNS configure [DDNS设置]
	CFG_SNIFFER		=15,	//network watch capture configure [网络监视捕获设置]
	CFG_DSPINFO		=16,	//code ability infomation [编码能力信息]
	CFG_COLOR		=126,	//color cofigure infomation [颜色配置信息]
	CFG_ALL,				//reserved [保留]
} CFG_INDEX;

typedef enum _SNAP_TYPE
{
	SNAP_TYP_TIMING = 0,
	SNAP_TYP_ALARM,
	SNAP_TYP_NUM,
} SNAP_TYPE;

//resolve enum, for RV_DSP_ENCODECAP using [分辨率枚举，供RV_DSP_ENCODECAP使用]
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
	CAPTURE_SIZE_XVGA,				// <  1024*768	VGA input code, 2800 serial device need [VGA输入编码，2800需要]
	CAPTURE_SIZE_WXGA,				// <  1280*800
	CAPTURE_SIZE_SXGA,				// <  1280*1024  
	CAPTURE_SIZE_WSXGA,				// <  1600*1024  
	CAPTURE_SIZE_UXGA,				// <  1600*1200
	CAPTURE_SIZE_WUXGA,				// <  1920*1200
	CAPTURE_SIZE_NR  
} CAPTURE_SIZE;

typedef enum __EM_USEDEV_MODE
{
	RV_TALK_CLIENT_MODE,		//set the type of client to start talk [设置客户端方式进行语音对讲]
	RV_TALK_SERVER_MODE,		//set the type of server to start talk [设置服务器方式进行语音对讲]
	RV_TALK_ENCODE_TYPE,		//set the code format of audio talk [设置语音对讲编码格式]
	RV_ALARM_LISTEN_MODE        //set the type of alarm information subscibe [设置报警订阅方式]

} EM_USEDEV_MODE;

typedef enum __EM_UPGRADE_TYPE
{
	RV_UPGRADE_BIOS_TYPE=1,		//BIOS upgrade [BIOS升级]
	RV_UPGRADE_WEB_TYPE,		//WEB upgrade [WEB升级]
	RV_UPGRADE_BOOT_YPE,		//BOOT upgrade [BOOT升级]
	RV_UPGRADE_CHARACTER_TYPE,	//the library of Chinese characters [汉字库]
	RV_UPGRADE_LOGO_TYPE,		//LOGO
	RV_UPGRADE_EXE_TYPE,		//EXE eg. player etc... [EXE 例如播放器等]
} EM_UPGRADE_TYPE;

//types of language [语言种类]
typedef enum __LANGUAGE_TYPE
{
	RV_LANGUAGE_ENGLISH,				//English [英文]	
	RV_LANGUAGE_CHINESE_SIMPLIFIED,		//Simplified Chinese [简体中文]	
	RV_LANGUAGE_CHINESE_TRADITIONAL,	//Chinese-traditional [繁体中文]	
	RV_LANGUAGE_ITALIAN,				//Italian [意大利文]	
	RV_LANGUAGE_SPANISH,				//Spanish [西班牙文]
	RV_LANGUAGE_JAPANESE,				//Japanese [日文版]	
	RV_LANGUAGE_RUSSIAN,				//Russian [俄文版]		
	RV_LANGUAGE_FRENCH,					//French [法文版]		
	RV_LANGUAGE_GERMAN, 				//German [德文版]		
	RV_LANGUAGE_PORTUGUESE,				//Portuguese [葡萄牙语]	
	RV_LANGUAGE_TURKEY,					//Turkey [土尔其语]	
	RV_LANGUAGE_POLISH,					//Polish [波兰语]	
	RV_LANGUAGE_ROMANIAN,				//Romanian [罗马尼亚]	
	RV_LANGUAGE_HUNGARIAN,              //Hungarian [匈牙利语]	
	RV_LANGUAGE_FINNISH,				//Finnish [芬兰语]	
	RV_LANGUAGE_ESTONIAN,				//Estonian [爱沙尼亚语]	
	RV_LANGUAGE_KOREAN,					//Korean [韩语]	
	RV_LANGUAGE_FARSI,					//Bosnian [波斯语]	
	RV_LANGUAGE_DANSK,					//Denish [丹麦语]
	RV_LANGUAGE_CZECHISH,				//Czech [捷克文]
	RV_LANGUAGE_BULGARIA,				//Bulgarian [保加利亚文]
} RV_LANGUAGE_TYPE;

//audio data format of audio talk [语音对讲格式]
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
** definition of struct [结构体定义]
***********************************************************************/
typedef struct
{	
	BOOL	bEnable;
	int		dwWebPort;
	int		dwTCPPort;
	DWORD	dwReserved;	
}NET_UPNP;

//time [时间]
typedef struct 
{
	DWORD dwYear;		//year [年]
	DWORD dwMonth;		//month [月]
	DWORD dwDay;		//day [日]
	DWORD dwHour;		//hour [时]
	DWORD dwMinute;		//minute [分]
	DWORD dwSecond;		//second [秒]
} NET_TIME,*LPNET_TIME;

//information of device [设备信息]
typedef struct {
	BYTE sSerialNumber[RV_SERIALNO_LEN];	//serial number [序列号]
	BYTE byAlarmInPortNum;					//alarm input number of DVR [DVR报警输入个数]
	BYTE byAlarmOutPortNum;					//alarm output number of DVR [DVR报警输出个数]
	BYTE byDiskNum;							//disk number of DVR [DVR 硬盘个数]
	BYTE byDVRType;							//DVR type, reference to enum DHDEV_DEVICE_TYPE [DVR类型, 见枚举DHDEV_DEVICE_TYPE]
	BYTE byChanNum;							//channel number of DVR [DVR 通道个数]
} NET_DEVICEINFO, *LPNET_DEVICEINFO;

//common alarm information [普通报警信息]
typedef struct {
	int channelcount;
	int alarminputcount;
	unsigned char alarm[16];			//out alarm [外部报警]
	unsigned char motiondection[16];	//motion detect [动态检测]
	unsigned char videolost[16];		//video lost [视频丢失]
} NET_CLIENT_STATE;

//query disk information of device in working state [查询设备工作状态硬盘信息]
typedef struct {
	DWORD		dwVolume;		//space of disk [硬盘的容量]
	DWORD		dwFreeSpace;	//left space of disk [硬盘的剩余空间]
	BYTE		dwStatus;		//state of disk, 0-dormancy, 1-activity, 2-error; seperate DWORD to 4 parts [硬盘的状态,0-休眠,1-活动,2-故障等；将DWORD拆成四个BYTE]
	BYTE		bDiskNum;		//disk index [硬盘号]
	BYTE		bSubareaNum;	//partion index [分区号]
	BYTE		bSignal;		//flag, 0-local, 1-remote [标识，0为本地 1为远程]
}NET_DEV_DISKSTATE,*LPNET_DEV_DISKSTATE;

//query disk type of device [查询设备硬盘类型]
typedef struct {
	int Type[32];
}NET_DEV_DISKTYPE;

//information of record file [录像文件信息]
typedef struct {
	unsigned int     ch;              //channel index [通道号]
	char             filename[128];   //file name [文件名]
	unsigned int     size;            //file length [文件长度]
	NET_TIME         starttime;       //start time [开始时间]
	NET_TIME         endtime;         //end time [结束时间]
	unsigned int     driveno;         //disk index [磁盘号]
	unsigned int     startcluster;    //start cluster index [起始簇号]
	int				 nRecordFileType; //record file type, 0-common record; 1-alarm record; 2-motion detect; 3-record for card [录象文件类型  0：普通录象；1：报警录象；2：移动检测；3：卡号录象]
} NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;

//record file information [录像文件信息]
typedef struct {
	unsigned int     ch;              //channel index [通道号]
	char             filename[128];   //file name [文件名]
	unsigned int     size;            //file length [文件长度]
	NET_TIME         starttime;       //start time [开始时间]
	NET_TIME         endtime;         //end time [结束时间]
	unsigned int     driveno;         //disk index [磁盘号]
	unsigned int     startcluster;    //start cluster index [起始簇号]
	int				 nRecordFileType; //record file type, 0-common record; 1-alarm record; 2-motion detect; 3-record for card [录象文件类型  0：普通录象；1：报警录象；2：移动检测；3：卡号录象]
	unsigned int	 partno;		  //partion index [分区号]
	unsigned int	 hint;			  
} NET_RECORDFILE_INFO_EX, *LPNET_RECORDFILE_INFO_EX;

//alarm IO control [报警IO控制]
typedef struct 
{
	unsigned short index;	//port index [端口序号]
	unsigned short state;	//port state [端口状态]
}ALARM_CONTROL;


typedef struct
{
	unsigned short		index;					//port index [端口序号]
	unsigned short		mode;					//port mode [端口模式]
	BYTE				bReserved[28];			
} TRIGGER_MODE_CONTROL;

typedef struct 
{
	int	decoderNo;					//alarming decoder index, start with 0 [报警解码器号,从0开始]
	unsigned short  alarmChn;		//alarming output channel, start with 0 [报警输出口,从0开始]
	unsigned short  alarmState;		//alarming output state, 1-opened, 0-closed [报警输出状态,1-打开　0-关闭]
}DECODER_ALARM_CONTROL;

///////////////////structs of user account management [用户帐号管理相关结构体]/////////////////////////////////
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
	DWORD		dwReusable;		//if this account can be used duplicated, 1-allow, 0-forbid [本用户是否允许复用 1-复用，0-不复用]

}USER_INFO;

typedef struct _USER_GROUP_INFO
{
	DWORD		dwID;
	char		name[RV_USER_NAME_LENGTH];
	DWORD		dwRightNum;
	DWORD		rights[RV_MAX_RIGHT_NUM];
	char		memo[RV_MEMO_LENGTH];
}USER_GROUP_INFO;

//struct of user information configure [用户信息配置结构]
typedef struct _USER_MANAGE_INFO
{
	DWORD				dwRightNum;
	OPR_RIGHT			rightList[RV_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;
	USER_GROUP_INFO		groupList[RV_MAX_GROUP_NUM];
	DWORD				dwUserNum;
	USER_INFO			userList[RV_MAX_USER_NUM];
	DWORD				dwSpecial; //special information, 1-support account be used duplicated, 1-not support account be used duplicated [特殊信息， 1-支持用户复用，　0-不支持用户复用]
}USER_MANAGE_INFO;

//////////////////////////////////////////////////////////////////////////////
///////////////////extened structs of user account management [用户帐号管理扩展相关结构体]/////////////////////////////////
#define RV_USER_NAME_LENGTH_EX  16  //user name length [用户名长度]
#define RV_USER_PSW_LENGTH_EX   16  //password length [密码]
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
	DWORD   dwFouctionMask;//mask code [掩码]

	/* mask code, include [掩码,包括]
	* 0x00000001 - support account be used duplicated [支持用户复用]
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

//struct user information configure [用户信息配置结构]
typedef struct _USER_MANAGE_INFO_EX
{

	DWORD				dwRightNum;
	OPR_RIGHT_EX		rightList[RV_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;
	USER_GROUP_INFO_EX  groupList[RV_MAX_GROUP_NUM];
	DWORD				dwUserNum;
	USER_INFO_EX		userList[RV_MAX_USER_NUM];
	DWORD				dwFouctionMask;//mask code [掩码]    
	/* mask code, include [掩码,包括]
	* 0x00000001 - support account be used dupliceted [支持用户复用]
	* 0x00000002 - password modify need verify [密码修改需要校验]
	*/
	BYTE  byNameMaxLength;			//max length of user name supported [支持用户名的最大长度]
	BYTE  byPSWMaxLength;			//max length of password supported [支持的密码最大长度]
	BYTE  byReserve[254];
}USER_MANAGE_INFO_EX;
///////////////////end of extened structs of user account management [end of 用户帐号管理扩展相关结构体]////////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////structs of log [日志结构体相关]///////////////////////////
//struct of log time [日志时间结构]
typedef struct _DHDEVTIME
{
	DWORD second		:6;					//second 1-60 [秒 1-60]		
	DWORD minute		:6;					//minute 1-60 [分 1-60]		
	DWORD hour			:5;					//hour 1-24	[时 1-24]		
	DWORD day			:5;					//day 1-31 [日 1-31]		
	DWORD month			:4;					//month 1-12 [月 1-12]		
	DWORD year			:6;					//year 2000-2063 [年 2000-2063]	
}DHDEVTIME, *LPDHDEVTIME;

typedef struct _RV_LOG_ITEM
{
	DHDEVTIME time;					//date [日期]
	unsigned short type;			//type [类型]
	unsigned char reserved;			//reserved [保留]
	unsigned char data;				//data [数据]
	unsigned char context[8];		//content [内容]
}RV_LOG_ITEM, *LPRV_LOG_ITEM;

//log information structs returned by interface CLIENT_QueryLogEx [接口CLIENT_QueryLogEx返回的日志信息结构体]
//situation : int nType = 1; param : reserved = &nType. [条件：int nType = 1;参数reserved = &nType.]
typedef struct _RV_NEWLOG_ITEM
{
	DHDEVTIME	time; 				//date [日期]
	WORD	type;					//type [类型]
	WORD	data;					//data [数据]
	char  	szOperator[8]; 			//user name [用户名]
	BYTE	context[16];		    //content [内容]	
}RV_NEWLOG_ITEM, *LPRV_NEWLOG_ITEM;

typedef struct _LOG_ITEM_RECORD
{
	DHDEVTIME	time;		//time [时间]
	BYTE	channel;		//channel [通道]
	BYTE	type;			//record type [录像类型]
	BYTE	reserved[2];
}LOG_ITEM_RECORD, *LPLOG_ITEM_RECORD;
////////////////////end of structs of log [end of 日志结构体相关]///////////////////////////

//frame param struct on video data fram callback [回调视频数据帧的帧参数结构体]
typedef struct _tagVideoFrameParam
{
	BYTE encode;		//code type [编码类型]
	BYTE frametype;		//I = 0, P = 1, B = 2...
	BYTE format;		//PAL - 0, NTSC - 1
	BYTE size;			//CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
						//SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15,
	DWORD fourcc;		//if H264 code is always 0, MPEG4 here always fill with FOURCC('X','V','I','D'); [如果是H264编码则总为0，MPEG4这里总是填写FOURCC('X','V','I','D');]
	DWORD reserved;		//reserved [保留]
	NET_TIME struTime;	//time information [时间信息]
}tagVideoFrameParam;

//frame param struct on audio data frame callback [回调音频数据帧的帧参数结构体]
typedef struct _tagCBPCMDataParam
{
	BYTE channels;		//audio channel number [声道数]
	BYTE samples;		//sample 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000 [采样 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000]
	BYTE depth;			//sample depth, 8 or 16, directly show [采样深度 取值8或者16等。直接表示]
	BYTE param1;		//0-indicate no symbol, 1-indicate has symbol [0 - 指示无符号，1-指示有符号]
	DWORD reserved;		//reserved [保留]
}tagCBPCMDataParam;

//data struct for channel picture title overprinting [通道画面字幕叠加的数据结构]
typedef struct _RV_CHANNEL_OSDSTRING
{
	BOOL bEnable;												//enable [使能]
	DWORD dwPosition[MAX_STRING_LINE_LEN];						//position of every character line, use 1-9, corresponding to little key-board position [各行字符的位置　用1-9整数表示，与小键盘位置对应]
																//7 left-up		8 up		9 right-up		[7左上	8上		9右上]
																//4 left		5 middle	6 right			[4左	5中		6右]
																//1 left-down	2 down		3 right-down	[1左下	2下		3右下]
	char szStrings[MAX_STRING_LINE_LEN][MAX_PER_STRING_LEN];	//max 6 character lines, max 20 bytes per line [最多六行字符，每行最多20个字节]
}RV_CHANNEL_OSDSTRING;

////////////////////control param definition for device control interface [设备控制接口的控制参数定义]//////////////////////
typedef struct _DISKCTRL_PARAM
{
	DWORD dwSize;		//size of this structure, for version control
	int nIndex;			//index of stDisks array of disk information struct RV_HARDDISK_STATE, start with 0 [为硬盘信息结构体RV_HARDDISK_STATE里的数组stDisks下标，从0开始]
	int ctrlType;		//control type.
						//0-clear data, 1-set read-write disk, 2-set read-only disk [0 - 清除数据,	1 - 设为读写盘, 2 - 设为只读盘]
						//3-set redundancy disk, 4-error restore, 5-set snapshot disk [3 - 设为冗余盘, 4 - 恢复错误,	5 - 设为快照盘]
}DISKCTRL_PARAM;

typedef struct _ALARMCTRL_PARAM
{
	DWORD dwSize;
	int nAlarmNo;		//alarm channel index, start with 0 [报警通道号，从0开始]
	int nAction;		//0-triggrt to alarm, 1-stop alarm [0-触发报警，1-停止报警]
}ALARMCTRL_PARAM;

typedef struct _MATRIXCTRL_PARAM
{
	DWORD dwSize;
	int nChannelNo;		//video input index, start with 0 [视频输入号，从0开始]
	int nMatrixNo;		//matrix output index, start with 0 [矩阵输出号，从0开始]
}MATRIXCTRL_PARAM;

typedef struct _BURNING_PARM
{
	int channelMask;	//channel index mask, flag one channel per bit [通道号掩码，每位表示一个通道]
	int	devMask;		//device mask, flag one device per bit [设备掩码，每位表示一台设备]
}BURNNG_PARM;

////////////////////end of control param definition for device control interface [end of设备控制接口的控制参数定义]//////////////////////

////////////////////params definition of query device state [查询设备状态的参数定义]////////////////////////////////
typedef struct _RV_HARDDISK_STATE
{
	DWORD	dwDiskNum;								//number [个数]
	NET_DEV_DISKSTATE	stDisks[RV_MAX_DISKNUM];	//every disk or partion information [各硬盘或分区信息]
}RV_HARDDISK_STATE,*LPRV_HARDDISK_STATE;

typedef RV_HARDDISK_STATE  RV_SDCARD_STATE;	//SD card, data struct is the same as disk information [SD卡，数据结构同硬盘信息]

typedef struct _NET_DEV_BURNING
{
	DWORD dwDriverType;							//imprinting driver type, 0-DHFS, 1-DISK, 2-CDRW [刻录驱动器类型 0 -	DHFS, 1 - DISK, 2- CDRW]
	DWORD dwBusType;							//bus type, 0-USB, 1-1394, 2-IDE [总线类型　0- USB, 1-1394, 2-IDE]
	DWORD dwTotalSpace;							//total space(KB) [总容量(KB)]
	DWORD dwRemainSpace;						//left space(KB) [剩余容量(KB)]
	BYTE  dwDriverName[RV_BURNING_DEV_NAMELEN]; //imprinting driver name [刻录驱动器名称]
}NET_DEV_BURNING,*LPNET_DEV_BURNING;

typedef struct _RV_BURNING_DEVINFO
{
	DWORD	dwDevNum;								//imprinting device number [刻录设备个数]
	NET_DEV_BURNING	stDevs[RV_MAX_BURNING_DEV_NUM]; //every imprinting device information [各刻录设备信息]
}RV_BURNING_DEVINFO, *LPRV_BURNING_DEVINFO;

typedef struct _RV_BURNING_PROGRESS
{
	BYTE	bBurning;		//old impriting means if it is imprintinging now [旧刻录机表示是否正在刻录]
	/*
	* new imprinting values : [新刻录机的值：]
	*0; can imprinting [0;   可以刻录]
	*1; not CD device, device type incorrect [1;   非光盘设备,设备类型不正确]
	*2; no valid device, namely left space is 0 [2;   没有有效的设备,即剩余空间为0]
	*3; there is other CD imprintinging now [3;   有其他光盘在刻录]
	*4; device is not idle, namely it is backuping, imprintinging or relaying now [4;   设备为非空闲状态,即在备份、刻录或回放中]
	*/
	BYTE	bRomType;		//CD type(new imprinting has this value)(0:RV file system; 1:removable disk or U disk; 2:CD) [才有盘片类型(新刻录机才有这个值)(0:RV文件系统；1：移动硬盘或u盘；2：光盘)]
	BYTE	bOperateType;   //operation type(new imprinting has this value)(0:idle; 1:back uping; 2:imprintinging; 3:replaying in CD) [操作类型(新刻录机才有这个值)(0：空闲；1：正在备份中；2：正在刻录中；3：正在进行光盘回放)]
	BYTE	bType;			//state of back up or imprinting(new imprinting has this value)(0:stop or end; 1:start; 2:error; 3:full; 4:initializing) [备份或刻录得过程状态(新刻录机才有这个值)(0：停止或结束 ；1：开始；2：出错；3：满;4：正在初始化)	]
	//**************************
	NET_TIME stTimeStart;	//start time [开始时间]
	DWORD	dwTimeElapse;	//already imprintinged time(second) [已刻录时间(秒)]
	DWORD	dwTotalSpace;	//CD total space [光盘总容量]
	DWORD	dwRemainSpace;	//CD left space [光盘剩余容量]
	DWORD	dwBurned;		//already imprintinged space [已刻录容量]
	DWORD	dwStatus;		/*
							for compatible old device, resered, new imprinting has no real using [为了兼容老设备，保留起来的，新刻录机没有实际用处]
							-1:flag new imprinting device. if it is not -1, flag old imprinting device [-1：表示新刻录机。如果不为-1，表示旧刻录机]
							down is imprinting state of old device(old device using) if it is not -1, flag old imprinting device [下面是老设备的刻录状态（老设备用的）如果不为-1，表示旧刻录机：]
							0-initializing [0-正在初始化，]
							1-imprintinging, variables above are valid [1-正在刻录，以上各变量有效]
							2-imprinting error [2-刻录出错]
							3-stoped because CD was full [3-盘满停止]
							*/
}RV_BURNING_PROGRESS, *LPRV_BURNING_PROGRESS;

//language structs device supported [设备支持语言结构体]
typedef struct _RV_LANGUAGE_DEVINFO
{
	DWORD	dwLanguageNum;		    //number of language type supported [支持语言个数]
	BYTE    byLanguageType[252];    //enum valus, detail to RV_LANGUAGE_TYPE [枚举值,详见RV_LANGUAGE_TYPE]
}RV_DEV_LANGUAGE_INFO, *LPRV_DEV_LANGUAGE_INFO;


typedef struct  
{
	RV_TALK_CODING_TYPE		encodeType;		//code type [编码类型]
	int						nAudioBit;		//using real value, eg. fill it with 8 if 8 bits [用实际的值表示，如8位 则填值为8]
	DWORD					dwSampleRate;	//sample rate, eg. fill it with 16000 if 16k [采样率，如16k 则填值为16000]
	char					reserved[64];
}DHDEV_TALKDECODE_INFO;

//audio talk format device supported [设备支持的语音对讲格式]
typedef struct 
{
	int						nSupportNum;	//number [个数]
	DHDEV_TALKDECODE_INFO	type[64];		//code format [编码格式]
	char					reserved[64];
}DHDEV_TALKFORMAT_LIST;

////////////////////end of params definition of query device state [end of 查询设备状态的参数定义]////////////////////////////////

//DDNS configure [DDNS 配置]
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

//struct of GPS information [GPS信息结构体]
typedef struct _GPS_Info
{
	NET_TIME revTime;        //locate time [定位时间]
	char DvrSerial[50];      //device serial number [设备序列号]
	double longitude;        //longitude [经度]
	double latidude;         //latitude [纬度]
	double height;           //height(minute) [高度（米）]
	double angle;            //direction angle(north direction is origin point, clockwise is positive) [方向角（正北方向为原点，顺时针为正）]
	double speed;            //speed(kilometers per hour) [速度（公里/小时）]
	WORD starCount;          //locate star number [定位星数]
	BOOL antennaState;       //antenna state(true good, false bad) [天线状态(true 好，false 坏)]
	BOOL orientationState;   //locate state(true good, false bad) [定位状态（true 定位，false 不定位）]
}GPS_Info,*LPGPS_Info;

//snapshot param struct [抓图参数结构体]
typedef struct _snap_param
{
	UINT Channel;				//snapshot channel [抓图的通道]
	UINT Quality;				//picture quality 1~6, this param is valid only for DVR on vehicle [画质1~6, 此参数只针对车载DVR设备有效]
	UINT ImageSize;				//picture size 0:QCIF, 1:CIF, 2:D1, this param is valid only for DVR on vehicle [画面大小 0:QCIF,1:CIF,2:D1, 此参数只针对车载DVR设备有效]
	UINT mode;					//snapshot mode, 0:means request one frame; 1:means request timer sendding; 2:means continues request, this param is valid only for DVR on vehicle [抓图模式 0：表示请求一帧; 1：表示定时发送请求; 2：表示连续请求,车载DVR设备有效。]
	UINT InterSnap;				//time unit second, if mode=1(means timer sending), this time is valid, this param is valid only for DVR on vehicle [时间单位秒 若mode=1表示定时发送请求时，此时间有效，并且只有车载DVR有效。]
	UINT CmdSerial;				//request serial number [请求序列号]
	UINT Reserved[4];
}SNAP_PARAMS,*LPSNAP_PARAMS;

//snapshot struct for network trigger device [网络触发设备抓图结构体]
typedef struct __NET_SNAP_COMMANDINFO 
{
	char			szCardInfo[16];		//card information [卡号信息]
	char			reserved[64];		//reserved [保留]
} NET_SNAP_COMMANDINFO, LPNET_SNAP_COMMANDINFO;

//protocal information [协议信息]
typedef struct 
{
	char            protocolname[12]; //protocal name [协议名]
	unsigned int	baudbase;	      //baudrate [波特率]
	unsigned char	databits; 	      //data bit [数据位]
	unsigned char	stopbits;	      //stop bit [停止位]
	unsigned char	parity;		      //veryfy bit [校验位]
	unsigned char   reserve;
} PROTOCOL_INFO, *LPPROTOCOL_INFO;

//audio format information [音频格式信息]
typedef struct {
	BYTE	byFormatTag;			//code type, 0-PCM [编码类型，如0-PCM]
	WORD	nChannels;				//audio channel number [声道数]
	WORD	wBitsPerSample;			//sample depth [采样深度]			
	DWORD	nSamplesPerSec;			//sample rate [采样率]
} RV_AUDIO_FORMAT, *LPRV_AUDIO_FORMAT;

//query device work state channel information:interface is invalid now, don't use it [查询设备工作状态通道信息:相关接口已淘汰，请不要使用]
typedef struct {
	BYTE byRecordStatic;			//channel is recrding, 0-no record, 1-manual record, 2-auto record [通道是否在录像,0-不录像,1-手动录像，2-自动录象]
	BYTE bySignalStatic;			//signal state of connection, 0-normal, 1-signal lost [连接的信号状态,0-正常,1-信号丢失]
	BYTE byHardwareStatic;			//hardware state of channel, 0-normal, 1-except, eg.DSP is dead [通道硬件状态,0-正常,1-异常,例如DSP死掉]
	char reserve;
	DWORD dwBitRate;				//real bit-rate [实际码率]
	DWORD dwLinkNum;				//cnnection number of client [客户端连接的个数]
	DWORD dwClientIP[RV_MAX_LINK];	//IP address of client [客户端的IP地址]
}NET_DEV_CHANNELSTATE,*LPNET_DEV_CHANNELSTATE;

//auery device work state:interface is invalid now, don't use it [查询设备工作状态:相关接口已淘汰，请不要使用]
typedef struct{
	DWORD dwDeviceStatic; 									//device state, 0x00 noamal, 0x01 CPU usage is high, 0x02 hardware error [设备的状态,0x00 正常,0x01 CPU占用过高,0x02 硬件错误]
	NET_DEV_DISKSTATE  stHardDiskStatic[RV_MAX_DISKNUM]; 
	NET_DEV_CHANNELSTATE stChanStatic[RV_MAX_CHANNUM];		//channel state [通道的状态]
	BYTE  byAlarmInStatic[RV_MAX_ALARMIN];					//alarm port state, 0-no alarm, 1-alarm [报警端口的状态,0-没有报警,1-有报警]
	BYTE  byAlarmOutStatic[RV_MAX_ALARMOUT];				//state of alarm output port, 0-no output, 1-output [报警输出端口的状态,0-没有输出,1-有报警输出]
	DWORD  dwLocalDisplay;									//local display status, 0-normal, 1-unnormal [本地显示状态,0-正常,1-不正常]
} NET_DEV_WORKSTATE,*LPNET_DEV_WORKSTATE;

/************************************************************************
** callback function prototype of listen server [侦听服务器回调原形]
***********************************************************************/
typedef int (CALLBACK *fServiceCallBack)(LONG lHandle, char *pIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, DWORD dwUserData);

/************************************************************************
**callback function prototype of disconnect from server [服务器断开回调原形]
***********************************************************************/
typedef void (CALLBACK *fDisConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

//	callback function prototype of reconnect to server after disconnection [断线重连成功回调函数]
typedef void (CALLBACK *fHaveReConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

/************************************************************************
** callback function prototype of real-time preview [实时预览回调原形]
***********************************************************************/
typedef void(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of origin data [原始数据回调原形]
***********************************************************************/
typedef int(CALLBACK *fDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of messasge(alarm) [消息（报警）回调原形]
***********************************************************************/
typedef BOOL (CALLBACK *fMessCallBack)(LONG lCommand, LONG lLoginID, char *pBuf,
	DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

/************************************************************************
** callback function prototype of screen overprint [屏幕叠加回调原形]
***********************************************************************/
typedef void (CALLBACK *fDrawCallBack)(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);

/************************************************************************
** callback function prototype of real-time preview extend [实时预览回调原形-扩展]
***********************************************************************/
typedef void(CALLBACK *fRealDataCallBackEx) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, DWORD dwUser);

/************************************************************************
** callback function prototype of replay process [回放录像进度回调原形]
***********************************************************************/
typedef void(CALLBACK *fDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

/************************************************************************
** callback function prototype of downloading process by time [通过时间下载录像进度回调原形]
not used now, using callback function prototype of replay process [现在按时间下载没有使用这个回调函数，使用的是回放录像进度回调原形. ]
***********************************************************************/
typedef void(CALLBACK *fTimeDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser);

/************************************************************************
** callback function prototype of downloading process by time [通过时间下载录像进度回调原形]
not used now, using callback function prototype of replay process [现在按时间下载没有使用这个回调函数，使用的是回放录像进度回调原形. ]
***********************************************************************/
typedef void(CALLBACK *fTimeDownLoadPosCallBackNew) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO_EX recordfileinfo, DWORD dwUser);

/************************************************************************
** callback function prototype of query device log data [查询设备日志数据回调原形]
***********************************************************************/
typedef void(CALLBACK *fLogDataCallBack) (LONG lLoginID, char *pBuffer, DWORD dwBufSize, DWORD nTotalSize, BOOL bEnd, DWORD dwUser);

/************************************************************************
** callback function prototype of clarity serial port [透明串口回调原形]
***********************************************************************/
typedef void(CALLBACK *fTransComCallBack) (LONG lLoginID, LONG lTransComChannel, char *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of upgrade device [升级设备程序回调原形]
***********************************************************************/
typedef void(CALLBACK *fUpgradeCallBack) (LONG lLoginID, LONG lUpgradechannel, int nTotalSize, int nSendSize, DWORD dwUser);

/************************************************************************
** callback function prototype of audio data of audio talk [语音对讲的音频数据回调原形]
***********************************************************************/
typedef void(CALLBACK *pfAudioDataCallBack) (LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);

/***********************************************************************
** callback function prototype of snapshot [抓图回调原形]
***********************************************************************/
typedef void( CALLBACK *fSnapRev)(LONG lLoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, DWORD CmdSerial, DWORD dwUser);

/************************************************************************
** SDK initialization [SDK初始化]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_Init(fDisConnect cbDisConnect, DWORD dwUser);

/************************************************************************
** SDK cleanup [SDK退出清理]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_Cleanup();

/************************************************************************
** set the callback function of successfulllu reconnection to server after disconnection, SDK will auto reconnect to server after disconnected from server [设置断线重连成功回调函数，设置后SDK内部断线自动重连]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetAutoReconnect(fHaveReConnect cbAutoConnect, DWORD dwUser);

/************************************************************************
** return error code for function comminting failed [返回函数执行失败代码]
***********************************************************************/
CLIENT_API DWORD CALL_METHOD CLIENT_GetLastError(void);

/************************************************************************
** set the timeout and try-times of conncting to server [设置连接服务器超时时间和尝试次数]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetConnectTime(int nWaitTime, int nTryTimes);


/************************************************************************
** get version info of SDK [获取SDK的版本信息]
***********************************************************************/
CLIENT_API DWORD CALL_METHOD CLIENT_GetSDKVersion();


/************************************************************************
** register to device [向设备注册]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_Login(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

//	nSpecCap = 0 is login by TCP; nSpecCap = 2 is login by auto-register; nSpecCap = 3 is login by group cast; nSpecCap = 4 is login by UDP [nSpecCap = 0为TCP方式下的登入；nSpecCap = 2为主动注册的登入；nSpecCap = 3为组播方式下的登入；nSpecCap = 4为UDP方式下的登入]
CLIENT_API LONG CALL_METHOD CLIENT_LoginEx(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, int nSpecCap, void* pCapParam, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

/************************************************************************
** logout from device [向设备注销]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_Logout(LONG lLoginID);

/************************************************************************
** 
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetDVRMessCallBack(fMessCallBack cbMessage,DWORD dwUser);


/************************************************************************
** set audio talk mode [设置语音对讲模式]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetDeviceMode(LONG lLoginID, EM_USEDEV_MODE emType, void* pValue);


/************************************************************************
** start listen to device [开始帧听设备]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StartListen(LONG lLoginID);

//corresponding to LB device's software version [对应LB设备程序版本]
CLIENT_API BOOL CALL_METHOD CLIENT_StartListenEx(LONG lLoginID);

/************************************************************************
** stop listrn to device [停止帧听设备]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopListen(LONG lLoginID);

/************************************************************************
** start to listrn to server, listen mobile DVR connection [开始侦听服务器，侦听移动DVR连接]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_ListenServer(char* ip, WORD port, int nTimeout, fServiceCallBack cbListen, DWORD dwUserData);

/************************************************************************
** stop listen server, stop listen mobile DVR connection [停止侦听服务器，停止侦听移动DVR连接]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopListenServer(LONG lServerHandle);

/************************************************************************
** respond to register device request [响应设备的注册请求]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ResponseDevReg(char *devSerial, char* ip, WORD port, BOOL bAccept);

/************************************************************************
** start service port [启动服务端口]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_StartService(WORD wPort, char *pIp = NULL, fServiceCallBack pfscb = NULL, 
	DWORD dwTimeOut = 0xffffffff, DWORD dwUserData = 0);

/************************************************************************
** stop service port [停止服务端口]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopService(LONG lHandle);

/************************************************************************
** set screen overprint callback [设置屏幕叠加回调]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_RigisterDrawFun(fDrawCallBack cbDraw, DWORD dwUser);


/************************************************************************
** start real-time preview [开始实时预览]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_RealPlay(LONG lLoginID, int nChannelID, HWND hWnd);
CLIENT_API LONG CALL_METHOD CLIENT_RealPlayEx(LONG lLoginID, int nChannelID, HWND hWnd, RV_RealPlayType rType = RV_RType_Realplay);

CLIENT_API BOOL	CALL_METHOD CLIENT_AdjustFluency(LONG lRealHandle, int nLevel);

/************************************************************************
** stop real-time preview [停止实时预览]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlay(LONG lRealHandle);

/************************************************************************
** stop real-time preview extend [停止实时预览_扩展]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlayEx(LONG lRealHandle);

/************************************************************************
** save data to file [保存数据为文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SaveRealData(LONG lRealHandle, const char *pchFileName);


/************************************************************************
** stop saving data to file [结束保存数据为文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopSaveRealData(LONG lRealHandle);


/************************************************************************
** set picture attributes [设置图像属性]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffect(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

/************************************************************************
** set picture attributes new [设置图像属性]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffectNew(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

/************************************************************************
** get picture attributes [获取图像属性]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffect(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

/************************************************************************
**  get picture attributes new [获取图像属性]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffectNew(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

/************************************************************************
** open audio [打开声音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSound(LONG hPlayHandle);

/************************************************************************
** open audio new [打开声音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSoundNew(LONG hPlayHandle);

/************************************************************************
** close audio [关闭声音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSound();

/************************************************************************
** close audio new [关闭声音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSoundNew();

/************************************************************************
** open audio talk [打开语音对讲]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_StartTalkEx(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser);

/************************************************************************
** set the volumn of audio talk [设置语音对讲的音量]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetAudioClientVolume(LONG lTalkHandle, WORD wVolume);

/************************************************************************
** send audio dta to device [发送语音数据到设备]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);

/************************************************************************
** start audio recording on PC [开始PC端录音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStart();

/************************************************************************
** stop audio recording on PC [结束PC端录音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStop();

/************************************************************************
** decode audio data [解码音频数据]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_AudioDec(char *pAudioDataBuf, DWORD dwBufSize);

/************************************************************************
** stop audio talk [停止语音对讲]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalkEx(LONG lTalkHandle);

/************************************************************************
** add device to broadcast group [添加设备到广播组]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastAddDev(LONG lLoginID);

/************************************************************************
** delete device from broadcast group [从广播组中删除设备]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastDelDev(LONG lLoginID);

/************************************************************************
** set the volumn [设置音量]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetVolume(LONG lPlayHandle, int nVolume);

/************************************************************************
** audio code--initialize (specal standard format->RV format) [音频编码--初始化(特定标准格式->RV格式)]
***********************************************************************/
CLIENT_API int  CALL_METHOD CLIENT_InitAudioEncode(RV_AUDIO_FORMAT aft);

/************************************************************************
** audio code--data code [音频编码--数据编码]
***********************************************************************/
CLIENT_API int	CALL_METHOD	CLIENT_AudioEncode(LONG lTalkHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);

/************************************************************************
** audio code--quit after complete [音频编码--完成退出]
***********************************************************************/
CLIENT_API int	CALL_METHOD	CLIENT_ReleaseAudioEncode();

/************************************************************************
** set the callback function of real-time preview [设置实时预览回调]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBack(LONG lRealHandle, fRealDataCallBack cbRealData, DWORD dwUser);

/************************************************************************
** set the callback function of real-time preview extend [设置实时预览回调-扩展]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBackEx(LONG lRealHandle, fRealDataCallBackEx cbRealData, DWORD dwUser, DWORD dwFlag);

/************************************************************************
** snapshot [抓图]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CapturePicture(LONG hPlayHandle, const char *pchPicFileName);

/************************************************************************
** snapshot new [抓图]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_CapturePictureNew(LONG hPlayHandle, const char *pchPicFileName);

/************************************************************************
** query that if it has record in some time slice [查询某段时间内是否有录像]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime=1000);

/************************************************************************
** query record file by time [通过时间查询录像文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFile(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

/************************************************************************
** query record file by time new [通过时间查询录像文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFileNew(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO_EX nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

/************************************************************************
** replay record file [回放录像文件]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFile(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** replay record file extend, added data callback params [回放录像文件扩展_增加了数据回调参数]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileEx(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** replay record file extend, added dta callback params new [回放录像文件扩展_增加了数据回调参数]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileExNew(LONG lLoginID, LPNET_RECORDFILE_INFO_EX lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** replay record file new [回放录像文件]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileNew(LONG lLoginID, LPNET_RECORDFILE_INFO_EX lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** pause record replay [暂停录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBack(LONG lPlayHandle, BOOL bPause);

/************************************************************************
** pause record replay new [暂停录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBackNew(LONG lPlayHandle, BOOL bPause);

/************************************************************************
** locate record replay start point [定位录像回放起始点]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBack(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

/************************************************************************
** locate record replay start point new [定位录像回放起始点]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBackNew(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

/************************************************************************
** stop record replay [停止录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBack(LONG lPlayHandle);

/************************************************************************
** stop record replay new [停止录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBackNew(LONG lPlayHandle);

/************************************************************************
** step record replay [步进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBack(LONG lPlayHandle, BOOL bStop);

/************************************************************************
** step record replay new [步进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBackNew(LONG lPlayHandle, BOOL bStop);

/************************************************************************
** fast record replay [快进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBack(LONG lPlayHandle);

/************************************************************************
** fast record replay new [快进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBackNew(LONG lPlayHandle);

/************************************************************************
** slow record replay [慢进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBack(LONG lPlayHandle);

/************************************************************************
** slow record replay new [慢进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBackNew(LONG lPlayHandle);

/************************************************************************
** restore normal replay speed [恢复正常回放速度]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBack(LONG lPlayHandle);

/************************************************************************
** restore normal replay speed new [恢复正常回放速度]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBackNew(LONG lPlayHandle);

/************************************************************************
** set the replay frame rate [设置回放帧速]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetFramePlayBack(LONG lPlayHandle, int framerate);

/************************************************************************
** get the replay frame rate [获取回放帧速]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetFramePlayBack(LONG lPlayHandle, int *fileframerate, int *playframerate);

/************************************************************************
** get replay OSD time [获取回放OSD时间]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetPlayBackOsdTime(LONG lPlayHandle, LPNET_TIME lpOsdTime, LPNET_TIME lpStartTime, LPNET_TIME lpEndTime);

/************************************************************************
** download record file [下载录像文件]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFile(LONG lLoginID,LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record file new [下载录像文件]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFileNew(LONG lLoginID,LPNET_RECORDFILE_INFO_EX lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record by time [通过时间下载录像]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record by time new [通过时间下载录像]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTimeNew(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBackNew cbTimeDownLoadPos, DWORD dwUserData);

/************************************************************************
** stop downloading record [停止录像下载]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownload(LONG lFileHandle);

/************************************************************************
** stop downloading record new [停止录像下载]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownloadNew(LONG lFileHandle);

/************************************************************************
** query process of downloading record [查询录像下载进度]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPos(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

/************************************************************************
** query process of downloading record new [查询录像下载进度]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPosNew(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

/************************************************************************
** multi-views real-time preview [多画面实时预览]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_MultiPlay(LONG lLoginID, HWND hWnd);

/************************************************************************
** stop multi-views real-time preview [停止多画面实时预览]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopMultiPlay(LONG lMultiHandle);

/************************************************************************
** query system server configure-not valid now, please use CLIENT_GetDevConfig [查询系统服务器配置 －该接口已淘汰，请使用CLIENT_GetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int maxlen, int *nConfigbuflen, int waittime=1000);

/************************************************************************
** set system server configure-not valid now, please use CLIENT_SetDevConfig [设置系统服务器配置 －该接口已淘汰，请使用CLIENT_SetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetupConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int nConfigbuflen, int waittime=1000);

/************************************************************************
** query device channel name [查询设备通道名称]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryChannelName(LONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime=1000);

/************************************************************************
** set device channel name [设置设备通道名称]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelName(LONG lLoginID,char *pbuf, int nbuflen);

/************************************************************************
** set device channel charater overprint [设置设备通道字符叠加]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelOsdString(LONG lLoginID, int nChannelNo, RV_CHANNEL_OSDSTRING* struOsdString, int nbuflen);

/************************************************************************
** common PTZ control [通用云台控制]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

/************************************************************************
** RV PTZ control [RV云台控制]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
	unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop);

/************************************************************************
** RV PTZ control extend interface, support 3D fast location [RV云台控制扩展接口，支持三维快速定位]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControlEx(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
	LONG lParam1, LONG lParam2, LONG lParam3, BOOL dwStop);

/************************************************************************
** query device log asynchronously [异步查询设备日志]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogCallback(LONG lLoginID, fLogDataCallBack cbLogData, DWORD dwUser);

/************************************************************************
** query device log synchronously [同步查询设备日志]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLog(LONG lLoginID, char *pLogBuffer, int maxlen, int *nLogBufferlen, int waittime=3000);

CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogEx(LONG lLoginID, RV_LOG_QUERY_TYPE logType, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime=3000);

/************************************************************************
** create clarity serial port channel [创建透明串口通道]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_CreateTransComChannel(LONG lLoginID, int TransComType, 
	unsigned int baudrate, unsigned int databits,
	unsigned int stopbits, unsigned int parity,
	fTransComCallBack cbTransCom, DWORD dwUser);

/************************************************************************
** send data by clarity serial port [透明串口发送数据]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SendTransComData(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

/************************************************************************
** release clarity serial port channel [释放通明串口通道]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_DestroyTransComChannel(LONG lTransComChannel);

/************************************************************************
** this interface is invalid now, please don't use it [该接口已淘汰，请不要使用]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_Reset(LONG lLoginID, BOOL bReset);

// set the network evironment for login  [设置登陆网络环境]
CLIENT_API void CALL_METHOD CLIENT_SetNetworkParam(NET_PARAM *pNetParam);

// import configure file [导入配置文件]
CLIENT_API LONG CALL_METHOD CLIENT_ImportConfigFile(LONG lLoginID, char *szFileName, fDownLoadPosCallBack cbUploadPos, DWORD dwUserData, DWORD param=0);

// stop importing configure file [停止导入配置文件]
CLIENT_API BOOL CALL_METHOD CLIENT_StopImportCfgFile(LONG lImportHandle);

// outport configure file [导出配置文件]
CLIENT_API LONG CALL_METHOD CLIENT_ExportConfigFile(LONG lLoginID, DH_CONFIG_FILE_TYPE emConfigFileType, char *szSavedFilePath, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

// stop outputing configure file [停止导出配置文件]
CLIENT_API BOOL CALL_METHOD CLIENT_StopExportCfgFile(LONG lExportHandle);

// search IPC, NVS, etc... devices in local network [搜索局域网内IPC、NVS等设备]
CLIENT_API BOOL CALL_METHOD CLIENT_SearchDevices(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime);

CLIENT_API BOOL CALL_METHOD CLIENT_GetDiskType(LONG lLoginID, NET_DEV_DISKTYPE* Type, DWORD dwSearchTime = 2000);

/************************************************************************
** start to upgrade software of device [开始升级设备程序]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_StartUpgrade(LONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

CLIENT_API LONG CALL_METHOD CLIENT_StartUpgradeEx(LONG lLoginID, EM_UPGRADE_TYPE emType, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);


/************************************************************************
** send data [发送数据]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SendUpgrade(LONG lUpgradeID);

/************************************************************************
** end upgrading software of device [结束升级设备程序]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopUpgrade(LONG lUpgradeID);

/************************************************************************
** query record state of channel [查道通道录像状态]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordState(LONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, int waittime=1000);

/************************************************************************
** set record state of channel [设置通道录像状态]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetupRecordState(LONG lLoginID, char *pRSBuffer, int nRSBufferlen);

/************************************************************************
** query current time of device [查询设备当前时间]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime, int waittime=1000);

/************************************************************************
** set current time of device [设置设备当前时间]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetupDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime);

/************************************************************************
** query serial port protocal - not invalid now, please use CLIENT_GetDevConfig [查询串口协议 － 该接口已淘汰，请使用CLIENT_GetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryComProtocol(LONG lLoginID, int nProtocolType, char *pProtocolBuffer, int maxlen, int *nProtocollen, int waittime=1000);

/************************************************************************
** set serial port protocal - not invalid now, please use CLIENT_SetDevConfig [查询系统信息 － 该接口已淘汰，请使用CLIENT_GetDevConfig]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QuerySystemInfo(LONG lLoginID, int nSystemType, char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime=1000);

/************************************************************************
auery lock state of account [查询用户锁定状态]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetUserLockState(LONG lLoginID, char* UserName, bool *bstate);

/************************************************************************
release lock state of account [解除用户锁定状态]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_UnlockUserLockState(LONG lLoginID, char* UserName);

/************************************************************************
recommend to use extended interface(the max length of user name of some devices is 16 bytes) from now on[建议以后用扩展接口(有些设备用户名最大长度是16个字节的)]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfoEx(LONG lLoginID, USER_MANAGE_INFO_EX *info, int waittime=1000);

/************************************************************************
** query device user (old interface, support 8 bit user name length) [查询设备用户(老接口。支持8位用户名长度。)]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfo(LONG lLoginID, USER_MANAGE_INFO *info, int waittime=1000);

/************************************************************************
** operate account of device [操作设备用户]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfo(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);
/************************************************************************
** operate account of device (new interface, support 8 bits and 16 bits user name and password) [操作设备用户（新接口，支持8位和16位的用户名密码长度）。]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfoEx(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

/************************************************************************
** start to talk - invalid now, please use CLIENT_StartTalkEx [开始对讲 － 该接口已淘汰，请使用CLIENT_StartTalkEx]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StartTalk(LONG lRealHandle, BOOL bCustomSend=false);

/************************************************************************
** stop talk - invalid now, please use CLIENT_StopTalkEx [结束对讲 － 该接口已淘汰，请使用CLIENT_StopTalkEx]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalk(LONG lRealHandle);

/************************************************************************
** send self defined talk data - invalid now, please use CLIENT_TalkSendData [发送自定义对讲数据 － 该接口已淘汰，请使用CLIENT_TalkSendData]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SendTalkData_Custom(LONG lRealHandle, char *pBuffer, DWORD dwBufSize);

/************************************************************************
** get channel bit-stream [获取通道码流]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

/************************************************************************
** query IO state [查询IO状态]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_QueryIOControlState(LONG lLoginID, RV_IOTYPE emType, 
	void *pState, int maxlen, int *nIOCount, int waittime=1000);

/************************************************************************
** IO control [IO控制]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_IOControl(LONG lLoginID, RV_IOTYPE emType, void *pState, int maxlen);

/************************************************************************
** query device work state, invalid now, please use CLIENT_QueryDevState [查询设备工作状态 该接口已淘汰，请使用CLIENT_QueryDevState]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDEVWorkState(LONG lLoginID, LPNET_DEV_WORKSTATE lpWorkState, int waittime=1000);

/************************************************************************
** force I Frame [强制I帧]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_MakeKeyFrame(LONG lLoginID, int nChannelID, int nSubChannel=0);

/************************************************************************
** set limit bit-stream of device [设置设备限制码流]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetMaxFlux(LONG lLoginID, WORD wFlux);

/************************************************************************
** qury device IP from DDNS server by device name or device serial number [通过设备名字或者设备序列号向DDNS服务器查询设备IP]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetDVRIPByResolveSvr(char *pchDVRIP, WORD wDVRPort, 
	BYTE *sDVRName, WORD wDVRNameLen, 
	BYTE *sDVRSerialNumber, WORD wDVRSerialLen, 
	char* sGetIP);

/************************************************************************
** replay record by time [通过时间回放录像]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTime(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

/************************************************************************
** replay record by time new [通过时间回放录像]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeNew(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

/************************************************************************
** replay record by time extend, added data callback params [通过时间回放录像扩展_增加了数据回调参数]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeEx(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser,
	fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** replay record by time extend, added data callback params new [通过时间回放录像扩展_增加了数据回调参数]
***********************************************************************/
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeExNew(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser,
	fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

/************************************************************************
** start to find record files [开始查找录像文件]
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
** find record file [查找录像文件]
***********************************************************************/
CLIENT_API int	CALL_METHOD CLIENT_FindNextFile(LONG lFindHandle,LPNET_RECORDFILE_INFO lpFindData);

/************************************************************************
** end finding record file [结束录像文件查找]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FindClose(LONG lFindHandle);

/************************************************************************
** start to find record files new [开始查找录像文件]
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
** find record file new [查找录像文件]
***********************************************************************/
CLIENT_API int	CALL_METHOD CLIENT_FindNextFileNew(LONG lFindHandle,LPNET_RECORDFILE_INFO_EX lpFindData);

/************************************************************************
** end finding record file new [结束录像文件查找]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_FindCloseNew(LONG lFindHandle);

/************************************************************************
** reboot device : returned TRUE success, FALSE fail [重启设备：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_RebootDev(LONG lLoginID);

/************************************************************************
** reset : returned TRUE success, FALSE fail [恢复出厂设置：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ResetDeafault(LONG lLoginID, unsigned long type);

/************************************************************************
** shutdown device : returned TRUE success, FALSE fail [关闭设备：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ShutDownDev(LONG lLoginID);

/************************************************************************
** control device : returned TRUE success, FALSE fail [设备控制：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_ControlDevice(LONG lLoginID, CtrlType type, void *param, int waittime = 1000);

/************************************************************************
** auto query device state, include alarm, disk, record state, etc... [主动查询设备状态，包括报警、硬盘、录象状态等。]
***********************************************************************/
//if nType  = RV_DEVSTATE_BURNING_PROGRESS, *pRetLen means query device's ID No. The reason of dealing as this is that there is no other suction parameter to use [当 nType  = RV_DEVSTATE_BURNING_PROGRESS 时,*pRetLen表示查询设备的id号.这样做的原因是没有其它可以使用的入口参数。]
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDevState(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

///////////////it is function interfaces for dvr on vehicle bellow [以下是车载dvr相关的功能接口] /////////////////////////
/************************************************************************
** set the callback function for snapshot [设置抓图回调函数]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, DWORD dwUser);

/************************************************************************
** snapshot request [抓图请求]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SnapPicture(LONG lLoginID, SNAP_PARAMS par);

/************************************************************************
** callback function prototype of GPS information subscription [GPS信息订阅回调]
***********************************************************************/
typedef void( CALLBACK *fGPSRev)(LONG lLoginID,           //device handle [设备句柄]
	GPS_Info  GpsInfo,       //GPS information [GPS信息]
	DWORD dwUserData);       //user data [用户数据]

/************************************************************************
** set tje callback function of GPS information subscription [设置GPS订阅回调函数]
***********************************************************************/
CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSCallBack(fGPSRev OnGPSMessage, DWORD dwUser);

/************************************************************************
** GPS information subscription [GPS信息订阅]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SubcribeGPS (
	LONG lLoginID,        //device handle [设备句柄]
	BOOL bStart,		  //if lauch [是否启动]
	LONG KeepTime,        //subscription duration (unit:second) [订阅持续时间（单位秒）]
	LONG InterTime);      //subscription GPS send frequency in duration (unit:second) [订阅时间内GPS发送频率（单位秒）]  

/////////////////////////end of function interfaces for dvr on vehicle [end of 车载dvr相关的功能] ///////////////////////////////


/////////////////////////unfulfilment [未实现]//////////////////////////
/************************************************************************
** set the huffer size of real-time preview [设置实时预览缓冲大小]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlayerBufNumber(LONG lRealHandle, DWORD dwBufNum);

/************************************************************************
** download file by time, CLIENT_DownloadByTime has implemented this function [通过时间下载文件，CLIENT_DownloadByTime已实现该功能]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_GetFileByTime(LONG lLoginID, int nChannelID, 
	LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, char *sSavedFileName);

/************************************************************************
** network replay control, it has been detail to several control interfaces [网络回放控制，已细化为各控制接口了]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD CLIENT_PlayBackControl(LONG lPlayHandle, 
	DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

//////////////////////////end of unfulfilment [end of 未实现]//////////////////////


/************************************************************************
** device interfaces of remote configure, configure type showed in the MACRO RV_DEV_DEVICECFG [远程配置设备接口 配置类型见RV_DEV_DEVICECFG 各宏]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
CLIENT_API BOOL  CALL_METHOD CLIENT_SetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);


/************************************************************************
** platform connection interfaces [平台接入接口]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
CLIENT_API BOOL  CALL_METHOD CLIENT_SetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);

/************************************************************************
**  get PTZ information [获取云台信息]	
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPtzOptAttr(LONG lLoginID,DWORD dwProtocolIndex,LPVOID lpOutBuffer,DWORD dwBufLen,DWORD *lpBytesReturned,int waittime=500);

/************************************************************************
**  get decode handle of remote replay [获取远程回放解码句柄]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPlayBackPlayerIndex(LONG lPlayHandle);

/************************************************************************
**  get decode handle of preview [获取预览解码句柄]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD CLIENT_GetRealPlayerIndex(LONG lPlayHandle);

/******************************************************************************
** configure structs [以下是各部分配置结构体]
*****************************************************************************/

/************************************************************************
*	system information [系统信息]
************************************************************************/

/*version information:the high 16 bits is main version number, the low 16 bits is minor version number [版本信息:高16位表示主版本号，低16位表示次版本号]
*data format of time : yyyymmdd [关于时间的数据组织是：yyyymmdd] */
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

/* ability description of DSP (in CLIENT_GetDevConfig), recommend to use CLIENT_QueryDevState [DSP能力描述(CLIENT_GetDevConfig里的)，以后建议用CLIENT_QueryDevState接口] */
typedef struct 
{
	DWORD	dwVideoStandardMask;	//mask of video standard, flag device supported standard by bits [视频制式掩码，按位表示设备能够支持的视频制式]
	DWORD	dwImageSizeMask;		//mask of resolver, flag device supported resolve configure by bits [分辨率掩码，按位表示设备能够支持的分辨率设置]
	DWORD	dwEncodeModeMask;		//mask of code mode, flag device supported code mode by bits [编码模式掩码，按位表示设备能够支持的编码模式设置]	

	DWORD	dwStreamCap;			//flag device supported multimedia function by bits [按位表示设备支持的多媒体功能，]
									//bit0:support main stream [第一位表示支持主码流]
									//bit1:support assist stream1 [第二位表示支持辅码流1]
									//bit2:support assist stream2 [第三位表示支持辅码流2]
									//bit4:support jpg snapshot [第五位表示支持jpg抓图]
	DWORD	dwImageSizeMask_Assi[8];//flag resolve mask of assisit stream according to main stream's reslove [表示主码流为各分辨率时，支持的辅码流分辨率掩码。]

	DWORD	dwMaxEncodePower;		//the highest code ability of DSP [DSP 支持的最高编码能力 ]
	WORD	wMaxSupportChannel;		//the max video input channel number per DSP [每块 DSP 支持最多输入视频通道数 ]
	WORD	wChannelMaxSetSync;		//if the max code configure per DSP channel is synchonous, 0-not be synchonous, 1-be synchonous [DSP 每通道的最大编码设置是否同步 0-不同步, 1-同步]
} RV_DSP_ENCODECAP, *LPRV_DSP_ENCODECAP;

/* struct of device information configure [设备信息配置结构] */
typedef struct 
{
	DWORD dwSize;
	/*these are read-only of device bellow [下面是设备的只读部分]*/
	RV_VERSION_INFO			stVersion;
	RV_DSP_ENCODECAP		stDspEncodeCap;		//ability description of DSP [DSP能力描述]
	BYTE	szDevSerialNo[RV_DEV_SERIALNO_LEN];	//serial number [序列号]
	BYTE	byDevType;							//device type, reference to enum DHDEV_DEVICE_TYPE [设备类型，见枚举DHDEV_DEVICE_TYPE]
	BYTE	szDevType[RV_DEV_TYPE_LEN];			//device's detail types, string format, maybe null [设备详细型号，字符串格式，可能为空]
	BYTE	byVideoCaptureNum;					//video port number [视频口数量]
	BYTE	byAudioCaptureNum;					//audio port number [音频口数量]
	BYTE	byTalkInChanNum;					//NSP
	BYTE	byTalkOutChanNum;					//NSP
	BYTE	byDecodeChanNum;					//NSP
	BYTE	byAlarmInNum;						//alarm input port number [报警输入口数]
	BYTE	byAlarmOutNum;						//alarm output port number [报警输出口数]
	BYTE	byNetIONum;							//network port number [网络口数]
	BYTE	byUsbIONum;							//USB port number [USB口数量]
	BYTE	byIdeIONum;							//IDE number [IDE数量]
	BYTE	byComIONum;							//serial port number [串口数量]
	BYTE	byLPTIONum;							//parallel port number [并口数量]
	BYTE	byVgaIONum;							//NSP
	BYTE	byIdeControlNum;					//NSP
	BYTE	byIdeControlType;					//NSP
	BYTE	byCapability;						//NSP, extended description [NSP，扩展描述]
	BYTE	byMatrixOutNum;						//output-port number of video matrix [视频矩阵输出口数]

	/*these are writable parts bellow of device [下面是设备的可写部分]*/
	BYTE	byOverWrite;						//deal method on disk full (overwrite, stop) [硬盘满处理方式（覆盖、停止）]
	BYTE	byRecordLen;						//package size of record [录象打包长度]
	BYTE	byStartChanNo;						//NSP
	WORD	wDevNo;								//device No. for remote control [设备编号，用于遥控]
	BYTE	byVideoStandard;					//video sandard [视频制式]
	BYTE	byDateFormat;						//date format [日期格式]
	BYTE	byDateSprtr;						//date seperate (0-"."， 1-"-"， 2-"/") [日期分割符(0-"."， 1-"-"， 2-"/")]
	BYTE	byTimeFmt;							//time format (0-24 hours, 1-12 hours) [时间格式 (0-24小时，1－12小时)]
	BYTE	byLanguage;						    //enum values, detail in RV_LANGUAGE_TYPE [枚举值详见RV_LANGUAGE_TYPE]
} DHDEV_SYSTEM_ATTR_CFG, *LPDHDEV_SYSTEM_ATTR_CFG;

/************************************************************************
*	picture channel [图像通道]
************************************************************************/

/* record type - timer, motion detect, alarm [录象类型－定时、动态检测、报警] */
typedef enum _REC_TYPE
{
	RV_REC_TYPE_TIM = 0,
	RV_REC_TYPE_MTD,
	RV_REC_TYPE_ALM,
	RV_REC_TYPE_NUM,
}REC_TYPE;

/* struct of time slice [时间段结构] */															    
typedef struct 
{
	BOOL	bEnable;	//if it is meaning record time slice, flag three enable by bits, they are motion detect record, alarm record, common record from low bit to high bit [当表示录像时间段时，按位表示三个使能，从低位到高位分别表示动检录象、报警录象、普通录象]
	int		iBeginHour;
	int		iBeginMin;
	int		iBeginSec;
	int		iEndHour;
	int		iEndMin;
	int		iEndSec;
} RV_TSECT, *LPRV_TSECT;

/* area:every edge by 8192 rate [区域:各边距按整长8192的比例] */
typedef struct {
	long		left;
	long		top;
	long		right;
	long		bottom;
} RV_RECT,*LPRV_RECT;

/* attributes struct of OSD [OSD属性结构] */
typedef struct  tagENCODE_WIDGET
{
	DWORD		rgbaFrontground;		/*!< object's fore RGB and transparency [物件的前景RGB，和透明度] */
	DWORD		rgbaBackground;			/*!< object's back RGB and transparency [物件的后景RGB，和透明度] */
	RV_RECT		rcRect;					/*!< position [位置] */
	BYTE		bShow;					/*!< show object [物件显示] */
	BYTE		byReserved[3];
} RV_ENCODE_WIDGET, *LPRV_ENCODE_WIDGET;

/* attributes of channel's audio and video [通道音视频属性] */
typedef struct 
{
	//video params [视频参数]
	BYTE	byVideoEnable;				/* videl enable : 1-open; 0-close [视频使能:1－打开，0－关闭] */
	BYTE	byBitRateControl;			/* bit-stream control, reference to constant definition [码流控制,参照常量定义] */
	BYTE	byFramesPerSec;				/* frame rate [帧率] */
	BYTE	byEncodeMode;				/* code mode, reference to constant definition [编码模式,参照常量定义] */
	BYTE	byImageSize;				/* resolve params, reference to constant definition [分辨率参,参照常量定义] */
	BYTE	byImageQlty;				/* level 1-6 [档次1-6] */
	WORD	wLimitStream;				/* limit stream params, range: 50~4*1024 (k) [限码流参数, 范围：50~4*1024 (k)] */

	//audio params [音频参数]
	BYTE	byAudioEnable;				/* audio enable : 1-open, 0-close [音频使能:1－打开，0－关闭] */
	BYTE	wFormatTag;					/* code type, eg. PCM [编码类型，如PCM] */
	WORD	nChannels;					/* audio channel number [声道数] */
	WORD	wBitsPerSample;				/* sample depth [采样深度] */		
	DWORD	nSamplesPerSec;				/* sample rate [采样率] */

	BYTE	bIFrameInterval;			/* frame number between I Frame, descripte the P frame number between two I frame, 0-149 [I帧间隔帧数量，描述两个I帧之间的P帧个数，0-149]*/
	char	reserved;
} RV_VIDEOENC_OPT, *LPRV_VIDEOENC_OPT;

/* attributes of picture color [画面颜色属性] */
typedef struct 
{
	RV_TSECT	stSect;
	BYTE		byBrightness;			/*! brightness 0-100 [亮度	0-100]*/
	BYTE		byContrast;				/*! contrast 0-100 [对比度	0-100]*/
	BYTE		bySaturation;			/*!	saturation 0-100 [饱和度	0-100]*/
	BYTE		byHue;					/*!	hue 0-100 [色度	0-100]*/
	BYTE		byGainEn;				/*! gain enable [增益使能]	 */ 
	BYTE		byGain;					/*! gain 0-100 [增益	0-100]*/
	BYTE		byReserved[2];
} RV_COLOR_CFG, *LPRV_COLOR_CFG;

/* attibutes struct of picture channel [图像通道属性结构体] */
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
	BYTE				byBlindEnable;			/*! switch of area shelter 0x00 not enable shelter, 0x01 only shlter device local preview, 0x10 only shelter record(and network preview), 0x11 both shelter [区域遮盖开关　0x00不使能遮盖，0x01仅遮盖设备本地预览，0x10仅遮盖录像（及网络预览），0x11都遮盖]	*/
	BYTE				byBlindMask;			/*! mask of area shelter bit0:device local preview, bit1:record(and network preview) [区域遮盖掩码  第一位：设备本地预览；第二位：录像(及网络预览)] */
	BYTE				byReserved[2];
} DHDEV_CHANNEL_CFG, *LPDHDEV_CHANNEL_CFG;


/************************************************************************
*	configure of area shelter [区域遮挡配置]
************************************************************************/
typedef struct __VIDEO_COVER_ATTR
{
	RV_RECT				rcBlock;			// overwritten area coordinate [覆盖的区域坐标]
	int					nColor;				// overwritten color [覆盖的颜色]
	BYTE				bBlockType;			// overwritten method:0-black block,1-mosaic [覆盖方式：0-黑块，1-马赛克]
	BYTE				bEncode;			// shelter in code level,1-valid,0-invalid [编码级遮挡, 1—生效, 0—不生郊]
	BYTE				bPriview;           // preview shelter,1-valid,0-invalid [预览遮挡, 1—生效, 0—不生效]
	char				reserved[29];		// reserved [保留]
}VIDEO_COVER_ATTR;

typedef struct __DHDEV_VIDEOCOVER_CFG 
{
	DWORD				dwSize;
	char				szChannelName[RV_CHAN_NAME_LEN];		//read-only [只读]
	BYTE				bTotalBlocks;							//supported shelter block number [支持的遮挡块数]
	BYTE				bCoverCount;							//setted shelter block number [已设置的遮挡块数]
	VIDEO_COVER_ATTR	CoverBlock[RV_MAX_VIDEO_COVER_NUM];		//overwritten area [覆盖的区域]	
	char				reserved[30];							//reserved [保留]
}DHDEV_VIDEOCOVER_CFG;


/************************************************************************
*	preview picture params [预览图像参数]
************************************************************************/

/* preview picture params [预览图像参数] */
typedef struct 
{
	DWORD dwSize;
	RV_VIDEOENC_OPT	stPreView;
	RV_COLOR_CFG  stColorCfg[RV_N_COL_TSECT];
}DHDEV_PREVIEW_CFG;

/************************************************************************
* audio attributes struct of audio talk - invalid, wait to be extended [语音对讲音频属性结构体－未实现，待扩展] *
************************************************************************/

typedef struct 
{
	//params for audio input [音频输入参数]
	BYTE	byInFormatTag;					//code type, eg.PCM [编码类型，如PCM]
	BYTE	byInChannels;					//audio channel number [声道数]
	WORD	wInBitsPerSample;				//sample depth [采样深度]					
	DWORD	dwInSamplesPerSec;				//sample rate [采样率]

	//params for audio output [音频输出参数]
	BYTE	byOutFormatTag;					//code type, eg.PCM [编码类型，如PCM]
	BYTE	byOutChannels;					//audio channel number [声道数]
	WORD	wOutBitsPerSample;				//sample depth [采样深度]				
	DWORD	dwOutSamplesPerSec;				//sample rate [采样率]
} DHDEV_TALK_CFG, *LPDHDEV_TALK_CFG;

/************************************************************************
*	timer record [定时录象]
************************************************************************/

typedef struct 
{
	DWORD		dwSize;
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];
	BYTE		byPreRecordLen;					/*! pre-record time, unit is second, 0 means not pre-record [预录时间,单位是s,0表示不预录]*/
	BYTE		byRedundancyEn;					/*! record redundancy switch [录像冗余开关]*/
	BYTE		byReserved[2];
} DHDEV_RECORD_CFG, *LPRV_RECORD_CFG;

/************************************************************************
*	alarm configure [报警配置]
************************************************************************/

typedef struct 
{
	int iType;
	int iValue;
} RV_PTZ_LINK, LPRV_PTZ_LINK;

typedef struct 
{
	/******************************************************************************
	** configure of message trigger [消息触发配置]
	**
	** if device occur messages, eg. occuer one input-alarm message, or video lost message, need to deal it [当设备产生消息,譬如产生一个输入报警,或者视频丢失时,需要做相应的处理.]
	** here we define how to deal with one message [此处定义如何处理一个消息]
	*****************************************************************************/

	/* deal method for messages, can combine these values, include [消息处理方式,可以同时多种处理方式,包括]
	* 0x00000001 - network:send to manage server [网络:上传管理服务器]
	* 0x00000002 - record:trigger [录像:触发]
	* 0x00000004 - PTZ lingage [云台联动]
	* 0x00000008 - send email [发送邮件]
	* 0x00000010 - device local alarm tour [设备本地报警轮巡]
	* 0x00000020 - device prompt enable [设备提示使能]
	* 0x00000040 - device alarm output enable [设备报警输出使能]
	* 0x00000080 - Ftp upload enable [Ftp上传使能]
	* 0x00000100 - beep [蜂鸣]
	* 0x00000200 - audio prompt [语音提示]
	* 0x00000400 - snapshot enable [抓图使能]*/

	/*supported deal method for current alarm message, mark by bits [当前报警所支持的处理方式，按位掩码表示]*/
	DWORD		dwActionMask;

	/*trigger action, by bit mask, real action needed params stored in every configure [触发动作，按位掩码表示，具体动作所需要的参数在各自的配置中体现]*/
	DWORD		dwActionFlag;

	/*triggered output ports, alarm message triggered output, 1 means trigger this output [报警触发的输出通道,报警触发的输出,为 1 表示触发该输出]  */ 
	BYTE		byRelAlarmOut[RV_MAX_ALARMOUT_NUM];
	DWORD		dwDuration;		/* alarm duration [报警持续时间] */

	/*linage to record [联动录象]*/
	BYTE		byRecordChannel[RV_MAX_VIDEO_IN_NUM];		/*alarm triggered record channel, 1 means trigger this channel [报警触发的录象通道,为1表示触发该通道] */
	DWORD		dwRecLatch;		/*record duration [录象持续时间] */

	/*snapshot channels [抓图通道]*/
	BYTE		bySnap[RV_MAX_VIDEO_IN_NUM];
	/*tour channels [轮巡通道]*/
	BYTE		byTour[RV_MAX_VIDEO_IN_NUM];

	/*PTZ linkage [云台联动]*/
	RV_PTZ_LINK	struPtzLink[RV_MAX_VIDEO_IN_NUM];
	DWORD		dwEventLatch;   /*!<linkage started delay time, unit is second, range is 0-15, default is 0 [联动开始延时时间，s为单位 范围是0－－15 默认值是0]*/
	/*alarm message triggered wireless output channel, alarm triggered output, 1 means triggered this output [报警触发的无线输出通道,报警触发的输出,为 1 表示触发该输出]  */ 
	BYTE		byRelWIAlarmOut[RV_MAX_ALARMOUT_NUM];
	BYTE		bMessageToNet;	//message upload network enable [消息上传给网络使能]
	BYTE		byReserved[111];       
} RV_MSG_HANDLE;

/* out-alarm [外部报警] */
typedef struct
{
	BYTE		byAlarmType;							/*alarm type, 0:always closed;1:always opened [报警器类型,0：常闭,1：常开]  */
	BYTE		byAlarmEn;								/*alarm enable [报警使能]*/
	BYTE		byReserved[2];						
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;							/*deal method [处理方式]  */
} RV_ALARMIN_CFG,*LPDHDEV_ALARMIN_CFG; 

/* motion detect alarm [动态检测报警] */
typedef struct 
{
	BYTE			byMotionEn;									/*motin detect alarm enable [动态检测报警使能]*/
	BYTE			byReserved;
	WORD			wSenseLevel;								/*sensitivity [灵敏度]*/
	WORD			wMotionRow;									/*line number of motion detect [动态检测区域的行数] */
	WORD			wMotionCol;									/*column number of motion detect [动态检测区域的列数] */
	BYTE			byDetected[RV_MOTION_ROW][RV_MOTION_COL];	/*detect area, max 32*32 areas [检测区域，最多32*32块区域]*/
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];			//NSP
	RV_MSG_HANDLE	struHandle;									/*deal method [处理方式]*/
}RV_MOTION_DETECT_CFG;

/*video lost alarm [视频丢失报警] */
typedef struct
{
	BYTE			byAlarmEn;								/*video lost alarm enable [视频丢失报警使能]*/
	BYTE			byReserved[3];
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;								/*deal method [处理方式]  */
} RV_VIDEO_LOST_CFG;

/*picture shelter alarm [图像遮挡报警] */
typedef struct
{
	BYTE			byBlindEnable;						/*enable [使能] */
	BYTE			byBlindLevel;						/*sensitivity 1-6 [灵敏度1-6] */
	BYTE			byReserved[2];
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;							/*deal method [处理方式]  */
} RV_BLIND_CFG;

/*disk message(inner alarm) [硬盘消息(内部报警)] */
typedef struct 
{
	BYTE				byNoDiskEn;									/*alarm on no disk [无硬盘时报警] */
	BYTE				byReserved_1[3];
	RV_TSECT			stNDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struNDHandle;								/*deal method [处理方式]  */

	BYTE				byLowCapEn;									/*alarm on low disk space [硬盘低容量时报警]*/
	BYTE				byLowerLimit;								/*space threshold value [容量阀值 0-99]*/
	BYTE				byReserved_2[2];
	RV_TSECT			stLCSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struLCHandle;								/*deal method [处理方式]  */

	BYTE				byDiskErrEn;								/*alarm on disk error [硬盘故障报警]*/
	BYTE				byReserved_3[3];
	RV_TSECT			stEDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struEDHandle;								/*deal method [处理方式]  */

} RV_DISK_ALARM_CFG;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	RV_MSG_HANDLE		struHandle;
} RV_NETBROKEN_ALARM_CFG;

//struct of IP conflict [IP冲突报警结构体]
typedef struct  
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	RV_MSG_HANDLE		struHandle;
}RV_IPCONFLICT_ALARM_CFG;

/*alarm guard [报警布防] */
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
	//maybe there are other device exceptions [可能还有设备异常]
} DHDEV_ALARM_SCHEDULE;

typedef struct  
{
	DWORD dwSize;
	RV_IPCONFLICT_ALARM_CFG	struIPConflict;
} DHDEV_ALARM_IPCONFLICT;

/*intelligent DVR SAVIA alarm [智能DVR SAVIA报警] */
typedef struct
{
	long			iIntelEnable;							/*enable [使能] */
	unsigned long	iIntelIPaddr;							/*ip address [ip地址] */
	BYTE			byReserved[4];
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;								/*deal method [处理方式]  */
} RV_SAVIA_ALARM;
typedef struct
{
	long			iSaviaNum;							//Savia number [Savia数目]
	RV_SAVIA_ALARM	stSaviaAlarm[RV_MAX_SAVIA_NUM];		//Savia alarm configure [Savia报警设置]
} RV_SAVIA_ALARM_SCHEDULE;

/*nlack and white ip list [黑白名单] */
typedef struct
{
	DWORD			dwSize;								//size of struct [结构体大小]
	BOOL			bEnable;							//IP authority configure enable [IP权限设置使能]
	LONG			iBlackCount;						//black IP number [黑名单数目]
	DWORD			dwBlackIP[RV_MAX_BLACK_IP_NUM];		//black IPs [黑名单IP]
	LONG			iWhiteCount;						//white IP number [白名单数目]
	DWORD			dwWhiteIP[RV_MAX_WHITE_IP_NUM];		//white IPs [白名单IP]
} RV_BLACKWHITE_CFG;

/*decoder configure [解码器配置] */
typedef struct
{
	int				channel;					//local decode channel index, start with 0 [本地解码通道号, 从0开始]
	unsigned short	device_type;				//device type, 0-visiondigi device, 4-VS300 connection, 3-RTSP [设备类型, 0-威乾设备 ,4-VS300接入,3-RTSP]
	unsigned short	device_port;				//front device's port [连接前端设备端口]
	unsigned int	device_ip;					//front device's ip, stored in network bytes storage [网络字节序储存, 连接的前端设备ip]
	unsigned int	device_channel;				//remote channel index [远程通道号]
	unsigned int	enable;						//enable switch [使能开关]
	unsigned int	stream_type;				//type of connection type, 0-main stream [连接码流类型,0-主码流]
	char			username[128];				//front device's user name [连接前端用户名]
	char			password[128];				//connection password [连接密码]
	//
	unsigned char	ucAVEnable;					//0:only decode video, 1:only decode audio, 2:decode audio and video, decode none is not allowed [0,只解视频 1，只解音频 ，2 解音视频 ，不允许什么都不解]
	unsigned char	ucRemotePtzPreset;			//remote preset [远程预置点]
	unsigned char	ucRemotePtzPresetEnable;	//if set remote preset on connected [是否一连接上就设置远程预置点]   
	unsigned char	ucRes;
	unsigned char	ucUrl[256];					//this is valid in rtsp mode, eg. rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx [rtsp模式下此配置有效,格式如：rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx]
	int				iDecodePolicy;				//decode plot (-2:most real-time; -1:real-time; 0:default; 1:fluency; 2:most fluency) it will extend to self define delay time [解码策略 	(-2, 最实时 -1 实时 0 默认情况 1 流畅 2,	最流畅 ) 以后可能扩展到自定义具体的延时时间]
	unsigned char	ucRes1[124];
}RV_CFG_DECODE_T;
typedef struct
{
	DWORD			dwSize;
	long			iDecoderNumber;
	RV_CFG_DECODE_T	struDecoder[RV_MAX_DECODER_CHAN_NUM];
}RV_DECODER_CFG;

/************************************************************************
*	network configure [网络配置]
************************************************************************/
/*                                                                      */
/*ethernet configure [以太网配置]*/
typedef struct 
{
	char	sDevIPAddr[RV_MAX_IPADDR_LEN];			/* DVR IP address [DVR IP 地址]  */ 
	char	sDevIPMask[RV_MAX_IPADDR_LEN];			/* DVR IP address mask [DVR IP 地址掩码]  */ 
	char	sGatewayIP[RV_MAX_IPADDR_LEN];			/* gateway address [网关地址]  */ 

	/* 10M/100M [10M/100M self adapting, index [自适应,索引] 
	* 1-10MBase - T [1-10MBase - T]
	* 2-10MBase-T FDX [2-10MBase-T 全双工] 
	* 3-100MBase - TX [3-100MBase - TX]
	* 4-100M  FDX [4-100M 全双工]
	* 5-10M/100M self adapting [5-10M/100M  自适应] 
	*/
	//seperate DWORD to four for extend [为了扩展将DWORD拆成四个]
	BYTE	dwNetInterface;							/* NSP */
	BYTE	bTranMedia;								/* 0:wired;1:wireless [0：有线 1：无线] */
	BYTE	bValid;									/* flag by bits, bit0:valid; 0:invalid, bit1:0:DHCP closed;1:DHCP enable, bit2:0:not support DHCP;1:support DHCP [按位表示，第一位：1：有效 0：无效；第二位：0：DHCP关闭 1：DHCP使能；第三位：0：不支持DHCP 1：支持DHCP] */
	BYTE	bDefaultEth;							/* if treat it as the default net-card, 1:default;0:not default [是否作为默认的网卡 1：默认 0：非默认] */
	char	byMACAddr[RV_MACADDR_LEN];				/* MAC address, read-only [MAC地址，只读] */
} RV_ETHERNET; 

/* remote host configure [远程主机配置] */
typedef struct 
{
	BYTE	byEnable;								/* connection enable [连接使能]  */
	BYTE	byReserved;
	WORD	wHostPort;								/* remote host : port [远程主机 端口]  */
	char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* remote host : IP address [远程主机 IP 地址]  */ 		
	char	sHostUser[RV_MAX_HOST_NAMELEN];			/* remote host : user name [远程主机 用户名] */ 
	char	sHostPassword[RV_MAX_HOST_PSWLEN];		/* remote host : password [远程主机 密码] */ 
}RV_REMOTE_HOST;

/* remote host configure (length of password is 64 bytes) [远程主机配置(密码64字节)] */
typedef struct 
{
	BYTE	byEnable;								/* connection enable [连接使能]  */
	BYTE	byReserved;
	WORD	wHostPort;								/* remote host : port [远程主机 端口]  */
	char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* remote host : IP address [远程主机 IP 地址]  */ 		
	char	sHostUser[RV_MAX_HOST_NAMELEN];			/* remote host : user name [远程主机 用户名] */ 
	char	sHostPassword[RV_MAX_HOST_PSWLEN_EX];	/* remote host : password [远程主机 密码] */ 
}RV_REMOTE_HOST_EX;

/* email configure [邮件配置] */
typedef struct 
{
	char	sMailIPAddr[RV_MAX_IPADDR_LEN];			/*IP address of email server [邮件服务器IP地址]*/
	WORD	wMailPort;								/*port of email server [邮件服务器端口]*/
	WORD	wReserved;								/*reserved [保留]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender address [发送地址]*/
	char	sUserName[RV_MAX_NAME_LEN];				/*user name [用户名]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user password [用户密码]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*Dest address [目的地址]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*Cc address [抄送地址]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*Bcc address [暗抄地址]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*title [标题]*/
}RV_MAIL_CFG;

/*struct of network configure [网络配置结构体]*/
typedef struct
{ 
	DWORD				dwSize; 

	char				sDevName[RV_MAX_NAME_LEN];				/* device host name [设备主机名]*/

	WORD				wTcpMaxConnectNum;						/* max TCP connection number (generaly means video data request number) [TCP最大连接数(一般指视频数据请求数)]*/
	WORD				wTcpPort;								/* TCP listen port [TCP帧听端口]*/
	WORD				wUdpPort;								/* UDP listen port [UDP侦听端口]*/
	WORD				wHttpPort;								/* HTTP port [HTTP端口号]*/
	WORD				wHttpsPort;								/* HTTPS port [HTTPS端口号]*/
	WORD				wSslPort;								/* SSL port [SSL端口号]*/
	RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];		/* ethernet port [以太网口]*/ 

	RV_REMOTE_HOST		struAlarmHost;							/* alarm server [报警服务器]*/
	RV_REMOTE_HOST		struLogHost;							/* log server [日志服务器]*/
	RV_REMOTE_HOST		struSmtpHost;							/* SMTP server [SMTP服务器]*/
	RV_REMOTE_HOST		struMultiCast;							/* multicast group [多播组]*/
	RV_REMOTE_HOST		struNfs;								/* NFS server [NFS服务器]*/
	RV_REMOTE_HOST		struPppoe;								/* PPPoE server [PPPoE服务器]*/
	char				sPppoeIP[RV_MAX_IPADDR_LEN];			/* returned IP by PPPOE register [PPPoE注册返回的IP]*/
	RV_REMOTE_HOST		struDdns;								/* DDNS server [DDNS服务器]*/
	char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS host [DDNS主机名]*/
	RV_REMOTE_HOST		struDns;								/* DNS server [DNS服务器]*/
	RV_MAIL_CFG			struMail;								/* email configure [邮件配置] */
} DHDEV_NET_CFG;

/*struct of network configure [网络配置结构体]*/
typedef struct
{ 
	DWORD				dwSize; 
	
	char				sDevName[RV_MAX_NAME_LEN];				/* device host name [设备主机名] */
	
	WORD				wTcpMaxConnectNum;						/* max TCP connection number (generaly means video data request number) [TCP最大连接数(一般指视频数据请求数)] */
	WORD				wTcpPort;								/* TCP listen port [TCP帧听端口] */
	WORD				wUdpPort;								/* UDP listen port [UDP侦听端口] */
	WORD				wHttpPort;								/* HTTP port [HTTP端口号] */
	WORD				wHttpsPort;								/* HTTPS port [HTTPS端口号] */
	WORD				wSslPort;								/* SSL port [SSL端口号]*/
	RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];		/* ethernet port [以太网口]  */ 
	
	RV_REMOTE_HOST_EX		struAlarmHost;						/* alarm server [报警服务器] */
	RV_REMOTE_HOST_EX		struLogHost;						/* log server [日志服务器] */
	RV_REMOTE_HOST_EX		struSmtpHost;						/* SMTP server [SMTP服务器] */
	RV_REMOTE_HOST_EX		struMultiCast;						/* multicast group [多播组] */
	RV_REMOTE_HOST_EX		struNfs;							/* NFS server [NFS服务器] */
	RV_REMOTE_HOST_EX		struPppoe;							/* PPPPoE server [PPPoE服务器] */
	char				sPppoeIP[RV_MAX_IPADDR_LEN];			/* returned IP by PPPOE register [PPPoE注册返回的IP] */
	RV_REMOTE_HOST_EX		struDdns;							/* DDNS server [DDNS服务器] */
	char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS host [DDNS主机名]*/
	RV_REMOTE_HOST_EX		struDns;							/* DNS server [DNS服务器]*/
	RV_MAIL_CFG			struMail;								/* email configure [邮件配置] */
} DHDEV_NET_CFG_RHEX;

/************************************************************************
*	serial port configure [串口配置]
************************************************************************/

/* basic attributs of serial port [串口基本属性] */
typedef struct
{
	BYTE	byDataBit;		//data bit 0-5,1-6,2-7,3-8 [数据位 0-5,1-6,2-7,3-8]
	BYTE	byStopBit;		//stop bit 0-1bit, 1-1.5bits, 2-2bits [停止位 0-1位, 1-1.5位, 2-2位] 
	BYTE	byParity;		//verify bit 0-no, 1-odd, 2-even [校验位 0-no, 1-odd, 2-even] 
	BYTE	byBaudRate;		//{0-300,1-600,2-1200,3-2400,4-4800
							// 5-9600,6-19200,7-38400,8-57600,9-115200} 
} RV_COMM_PROP;

/* 485 decoder configure [485解码器配置] */
typedef struct
{ 
	RV_COMM_PROP	struComm;

	BYTE			wProtocol;			/*protocal type, save the index of protocal, dynamicly change [协议类型 保存协议的下标，动态变化] */
	BYTE			byReserved;			/*reserved [保留]  */	
	BYTE			wDecoderAddress;	/*decoder address : 0 - 255 [解码器地址:0 - 255]*/ 
	BYTE 			byMartixID;			/*matrix No. [矩阵号]*/
} RV_485_CFG; 

/* 232 seial port configure [232串口配置] */
typedef struct
{
	RV_COMM_PROP	struComm;
	BYTE			byFunction;/*serial port function, corresponding function name list got from serial port configure [串口功能，对应串口配置取到的功能名列表]*/
	BYTE			byReserved[3];
} RV_RS232_CFG;

/* struct of serial port configure [串口配置结构体] */
typedef struct
{
	DWORD			dwSize;
	//decoder protocal [解码器协议]
	DWORD			dwDecProListNum;										//number of protocal [协议个数]
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN];	//protocal name list [协议名列表]
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM];							//current attributs of every decoder [各解码器当前属性]

	DWORD			dw232FuncNameNum;										//number of 232 function [232功能个数]
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];			//function name list [功能名列表]
	RV_RS232_CFG	st232[RV_MAX_232_NUM];									//current attributs of every 232 serial port [各232串口当前属性]
} DHDEV_COMM_CFG;


/************************************************************************
*	auto mantance configure [自动维护配置]
***********************************************************************/
/* attributes of auto mantance [自动维护属性] */
typedef struct
{
	DWORD dwSize;

	//auto reboot [自动重启]
	BYTE byAutoRebootDay;		// 0-never, 1-every day, 2-every sunday, 3-every monday, etc... [0-从不, 1-每天, 2-每星期日, 3-每星期一,.....]
	BYTE byAutoRebootTime;		// 0-0:00 1-1:00,........23-:23:00 */
	//autoly delete files [自动删除文件]
	BYTE byAutoDeleteFilesTime; // 0-never, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH [0-从不, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH] */

	BYTE reserved[13];			// reserved [保留位]
} DHDEV_AUTOMT_CFG;

/************************************************************************
* configure of local machine's matrix control plot [本机矩阵控制策略配置]
************************************************************************/

typedef struct
{
	BOOL		bTourEnable;			//	tour enable [轮巡使能]
	int			nTourPeriod;			//	tour time slice, unit is second, 5-300 [轮巡间隔，单位秒, 5-300] 
	DWORD		dwChannelMask;			//	tour channel, by mask [轮巡的通道，掩码形式表示]
	char		reserved[64];
}RV_VIDEOGROUP_CFG;

typedef struct
{
	DWORD	dwSize;
	int		nMatrixNum;									//matrix number (read-only) [矩阵个数(注：不允许修改)]
	RV_VIDEOGROUP_CFG struVideoGroup[RV_MATRIX_MAXOUT];
	char	reserved[32];
}DHDEV_VIDEO_MATRIX_CFG;   

/************************************************************************
*	multi DDNS configure struct [多ddns配置结构体]
************************************************************************/

typedef struct
{
	DWORD	dwId;									//ddns server's id No. [ddns服务器id号]
	BOOL	bEnable;								//enable, only one ddns server can be enabled in the same time [使能，同一时间只能有一个ddns服务器处于使能状态]
	char	szServerType[RV_MAX_SERVER_TYPE_LEN];	//server type [服务器类型，希网..]
	char	szServerIp[RV_MAX_DOMAIN_NAME_LEN];		//server ip or domain [服务器ip或者域名]
	DWORD	dwServerPort;							//server port [服务器端口]
	char	szDomainName[RV_MAX_DOMAIN_NAME_LEN];	//dvr domain, eg. jeckean.3322.org [dvr域名，如jeckean.3322.org]
	char	szUserName[RV_MAX_HOST_NAMELEN];		//user name [用户名]
	char	szUserPsw[RV_MAX_HOST_PSWLEN];			//password [密码]
	char	szAlias[RV_MAX_DDNS_ALIAS_LEN];			//server's other name, eg. "RV inter ddns" [服务器别名，如"RV inter ddns"]
	DWORD	dwAlivePeriod;							//DDNS alive time slice [DDNS 保活时间]
	char	reserved[256];
}RV_DDNS_SERVER_CFG;

typedef struct
{
	DWORD	dwSize;
	DWORD	dwDdnsServerNum;	
	RV_DDNS_SERVER_CFG struDdnsServer[RV_MAX_DDNS_NUM];	
}DHDEV_MULTI_DDNS_CFG;


/************************************************************************
*   struct of email [邮件配置结构体]
************************************************************************/
typedef struct 
{
	char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*email server address (IP or domain) [邮件服务器地址(IP或者域名)]*/
	char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
	WORD	wMailPort;								/*email server port [邮件服务器端口]*/
	WORD	wSubMailPort;
	WORD	wReserved;								/*reserved [保留]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender's address [发送地址]*/
	char	sUserName[RV_MAX_NAME_LEN];				/*user name [用户名]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user's password [用户密码]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*dest address [目的地址]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*cc address [抄送地址]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*bcc address [暗抄地址]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*subject [标题]*/
	BYTE	bEnable;//使能0:false,	1:true
	char	reserved[255];
} DHDEV_MAIL_CFG;

/************************************************************************
*   extend struct of email [邮件配置结构体扩展]
************************************************************************/
typedef struct 
{
	char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*email server address (IP or domain) [邮件服务器地址(IP或者域名)]*/
	char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
	WORD	wMailPort;								/*emial server's port [邮件服务器端口]*/
	WORD	wSubMailPort;
	WORD	wReserved;								/*reserved [保留]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender's address [发送地址]*/
	char	sUserName[RV_MAX_NAME_LEN_EX];			/*user name [用户名]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user's password [用户密码]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*dest address [目的地址]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*cc address [抄送地址]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*bcc address [暗抄地址]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*subject [标题]*/
	BYTE	bEnable;								//enalbe, 0:dalse, 1:true [使能0:false,	1:true]
	char	reserved[255];
} DHDEV_MAIL_CFG_EX;

/************************************************************************
*   version information of device's software [设备软件版本信息]
************************************************************************/
typedef struct  
{
	char	szDevSerialNo[RV_DEV_SERIALNO_LEN];		//serial number [序列号]
	char	byDevType;								//device type, reference to enum DHDEV_DEVICE_TYPE [设备类型，见枚举DHDEV_DEVICE_TYPE]
	char	szDevType[RV_DEV_TYPE_LEN];				//device's detail type, string fromat, maybe null [设备详细型号，字符串格式，可能为空]
	int		nProtocalVer;							//protocal version [协议版本号]
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
*   ability description of DSP [DSP能力描述]
************************************************************************/
typedef struct 
{
	DWORD	dwVideoStandardMask;		//mask of video sandard, flag supported video standard by bits [视频制式掩码，按位表示设备能够支持的视频制式]
	DWORD	dwImageSizeMask;			//mask of resolve, flag supported resolve by bits [分辨率掩码，按位表示设备能够支持的分辨率设置]
	DWORD	dwEncodeModeMask;			//mask of code mode, flag supported code mode by bits [编码模式掩码，按位表示设备能够支持的编码模式设置	]

	DWORD	dwStreamCap;				//flag supported multivideo by bits [按位表示设备支持的多媒体功能，]
										//bit0:support main stream [第一位表示支持主码流]
										//bit1:support assist stream1 [第二位表示支持辅码流1]
										//bit2:support assist stream2 [第三位表示支持辅码流2]
										//bit4:support snapshot by jpg [第五位表示支持jpg抓图]
	DWORD	dwImageSizeMask_Assi[32];	//mask of assist stream's supported resolve, corresponding every resolve of main stream [表示主码流为各分辨率时，支持的辅码流分辨率掩码。]

	DWORD	dwMaxEncodePower;			//max code ability of DSP [DSP 支持的最高编码能力 ]
	WORD	wMaxSupportChannel;			//max video channel number of every DSP [每块 DSP 支持最多输入视频通道数 ]
	WORD	wChannelMaxSetSync;			//if the max code configure be synchonous, 0-be not synchonous, 1-be synchonous [DSP 每通道的最大编码设置是否同步 0-不同步, 1-同步]

	BYTE	bMaxFrameOfImageSize[32];	//max sample rate in every resolve, corresponding dwVideoStandardMask by bits [不同分辨率下的最大采集帧率，与dwVideoStandardMask按位对应]
	BYTE	bEncodeCap;					//0:code ability of main stream + code ability of assist stream <= code ability of device [0：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力；]
										//1:code ability of main stream + code ability of assist stream <= code ability of device [1：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，]
										//code ability of assist stream <= code ability of main stream [辅码流的编码能力 <= 主码流的编码能力，]
										//resolve of assist stream < resolve of main stream [辅码流的分辨率 <= 主码流的分辨率，]
										//frame rate of main stream and assist stream <= sample rate of front device [主码流和辅码流的帧率 <= 前端视频采集帧率]

	char	reserved[95];
} DHDEV_DSP_ENCODECAP, *LPDHDEV_DSP_ENCODECAP;


/************************************************************************
*   configure of snapshot fucntion [抓图功能配置]
************************************************************************/
typedef struct 
{
	DWORD	dwSize;
	BOOL	bTimingEnable;						//switch of timer snapshot (switch of timer snapshot for alarm is showed in alarm linkage) [定时抓图开关（报警抓图开关在各报警联动配置中体现）]
	RV_VIDEOENC_OPT struSnapEnc[SNAP_TYP_NUM];	//snapshot code configure, support it's resolve, picture quality, frame rate is negtive here to mean how many pictures snapshoted once [抓图编码配置，现支持其中的分辨率、画质、帧率设置，帧率在这里是负数，表示一秒抓图的次数。]
}DHDEV_SNAP_CFG;

/************************************************************************
*   web path configure [web路径配置]
************************************************************************/
typedef struct 
{
	DWORD	dwSize;
	BOOL	bSnapEnable;					//if snapshot [是否抓图]
	int		iSnapInterval;					//snapshot timer [抓图周期]
	char	szHostIp[RV_MAX_IPADDR_LEN];	//HTTP host's IP [HTTP主机IP]
	WORD	wHostPort;
	int		iMsgInterval;					//state messgae sending time slice [状态消息发送间隔]
	char	szUrlState[RV_MAX_URL_LEN];		//state message upload URL [状态消息上传URL]
	char	szUrlImage[RV_MAX_URL_LEN];		//picture upload Url [图片上传Url]
	char	szDevId[RV_MAX_DEV_ID_LEN];		//local machine's web No. [机器的web编号]
	BYTE	byReserved[2];
}DHDEV_URL_CFG;

/************************************************************************
*   picture watermark configure [图象水印配置]
************************************************************************/
typedef struct __DHDEV_WATERMAKE_CFG 
{
	DWORD				dwSize;
	int					nEnable;								//	enable [使能]
	int					nStream;								//	bit stream (1~n) 0-all stream [码流（1～n）0-所有码流]
	int					nKey;									//	data type (1-text, 2-picture) [数据类型(1-文字，2-图片)]
	char				szLetterData[RV_MAX_WATERMAKE_LETTER];	//	text [文字]
	char				szData[RV_MAX_WATERMAKE_DATA];			//	picture data [图片数据]
	BYTE				bReserved[512];							//	reserved [保留]
} DHDEV_WATERMAKE_CFG;

/************************************************************************
*   FTP upload configure [FTP上传配置]
************************************************************************/
typedef struct
{
	struct
	{
		RV_TSECT	struSect;	//"enable" is invalid in this time slice, can be ignored [该时间段内的“使能”无效，可忽略]
		BOOL		bMdEn;		//upload motion detect record [上传动态检测录象]
		BOOL		bAlarmEn;	//upload out-alarm record [上传外部报警录象]
		BOOL		bTimerEn;	//upload common timer record [上传普通定时录像]
		DWORD		dwRev[4];
	} struPeriod[RV_TIME_SECTION];
}RV_FTP_UPLOAD_CFG;

typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;									//enable [是否启用]
	char				szHostIp[RV_MAX_IPADDR_LEN];				//host's IP [主机IP]
	WORD				wHostPort;									//host's port [主机端口]
	char				szDirName[RV_FTP_MAX_PATH];					//FTP folder path [FTP目录路径]
	char				szUserName[RV_FTP_USERNAME_LEN];			//usr name [用户名]
	char				szPassword[RV_FTP_PASSWORD_LEN];			//password [密码]
	int					iFileLen;									//file length [文件长度]
	int					iInterval;									//time slice between files [相邻文件时间间隔]
	RV_FTP_UPLOAD_CFG	struUploadCfg[RV_MAX_CHANNUM][RV_N_WEEKS];
	char 				protocol;									//0-FTP 1-SMB
	char				NASVer;										//version of network store server, 0-old FTP(show time slice in UI), 1-NAS store(hidden time slice in UI) [网络存储服务器版本0=老的FTP（界面上显示时间段）,1=NAS存储（界面上屏蔽时间段）]
	BYTE 				reserved[128];
}DHDEV_FTP_PROTO_CFG;

// DNS server configure [DNS服务器配置]
typedef struct  
{
	char				szPrimaryIp[RV_MAX_IPADDR_LEN];
	char				szSecondaryIp[RV_MAX_IPADDR_LEN];
	char				reserved[256];
}DHDEV_DNS_CFG;


/************************************************************************
*   record download plot configure [录象下载策略配置]
************************************************************************/
typedef struct
{
	DWORD dwSize;

	BOOL bEnable;	//TRUE - high speed download, FALSE - common download [TRUE－高速下载，FALSE-普通下载]
}DHDEV_DOWNLOAD_STRATEGY_CFG;

/************************************************************************
*   network transport plot configure [网络传输策略配置]
************************************************************************/
typedef struct
{
	DWORD dwSize;

	BOOL bEnable;
	int  iStrategy;	//picture quality first, 1-fluency first, 2-auto [0-画质优先， 1-流畅性优先， 2-自动。]
}DHDEV_TRANSFER_STRATEGY_CFG;


/************************************************************************
*	configure of IPC [IPC的一些配置]
************************************************************************/
//	configure of wireless network [配置无线网络信息]
typedef struct 
{
	int					nEnable;			// enable wireless [无线使能]
	char				szSSID[36];			// SSID
	int					nLinkMode;			// connection mode 0:adhoc 1:Infrastructure [连接模式 0:auto 1:adhoc 2:Infrastructure]
	int					nEncryption;		// encrypt 0: off  2:WEP64bit 3: WEP128bit [加密 0: off 2:WEP64bit 3: WEP128bit]
	int					nKeyType;			// 0:Hex 1:ASCII
	int					nKeyID;				// serial number [序号]
	char				szKeys[4][32];		// four group password [四组密码]
	int					nKeyFlag;
	char				reserved[12];
} DHDEV_WLAN_INFO;

//	select some wireless device [选择使用某个无线设备]
typedef struct  
{
	char				szSSID[36];
	int					nLinkMode;			// connection mode 0:adhoc 1:Infrastructure [连接模式 0:adhoc 1:Infrastructure]
	int 				nEncryption;		// encrypt 0: off  2:WEP64bit 3: WEP128bit [加密 0: off  2:WEP64bit 3: WEP128bit]
	char				reserved[48];
} DHDEV_WLAN_DEVICE;

//	found wireless device list [搜索到的无线设备列表]
typedef struct  
{
	DWORD				dwSize;
	BYTE				bWlanDevCount;		// number of found wireless device [搜索到的无线设备个数]
	DHDEV_WLAN_DEVICE	lstWlanDev[RV_MAX_WLANDEVICE_NUM];
	char				reserved[255];
} DHDEV_WLAN_DEVICE_LIST;

//	configure params of auto registration [主动注册参数配置]
typedef struct  
{
	char				szServerIp[32];		//auto register server's IP [注册服务器IP]
	int					nServerPort;		//port [端口号]
	char				reserved[64];
} DHDEV_SERVER_INFO;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bServerNum;         //supported max ip number [支持的最大ip数]
	DHDEV_SERVER_INFO	lstServer[RV_MAX_REGISTER_SERVER_NUM];
	BYTE				bEnable;			//enable [使能]
	char				szDeviceID[32];		//device's id [设备id。]
	char				reserved[94];
} DHDEV_REGISTER_SERVER;

//	attributs of cameral [摄像头属性]
typedef struct __DHDEV_CAMERA_INFO
{
	BYTE				bBrightnessEn;		// if brightness can be adjusted, 1:can, 0:can't [亮度可调 1：可；0：不可]
	BYTE				bContrastEn;		// if contrast can be adjusted[对比度可调]
	BYTE				bColorEn;			// if hue can be adjusted[色度可调]
	BYTE				bGainEn;			// if gain can be adjusted[增益可调]
	BYTE				bSaturationEn;		// if saturation can be adjusted[饱和度可调]
	BYTE				bBacklightEn;		// if backlight compensation can be adjusted[背光补偿可调]
	BYTE				bExposureEn;		// if exposure selection can be adjusted[曝光选择可调]
	BYTE				bColorConvEn;		// if auto transform between "multi color" and "black and white"  can be adjusted[自动彩黑转换可调]
	BYTE				bAttrEn;			// attributs option, 1:can, 0:can't [属性选项 1：可；0：不可]
	BYTE				bMirrorEn;			// mirrorimage, 1:support, 0:not support [镜像 1：支持；0：不支持]
	BYTE				bFlipEn;			// reversal, 1:support, 0:not support [翻转 1：支持；0：不支持]
	BYTE				bRev[125];			// reserved [保留]
} DHDEV_CAMERA_INFO;

//	attributes configure of cameral [摄像头属性配置]
typedef struct __DHDEV_CAMERA_CFG 
{
	DWORD				dwSize;
	BYTE				bExposure;			//exposure mode 1-9:manual exposure level; 0:auto exposure [曝光模式 1-9:手动曝光等级; 0:自动曝光]
	BYTE				bBacklight;			//backlight compensation 3:hard, 2:middle, 1:weak, 0:closed [背光补偿 3:强；2：中；1：弱； 0:关]
	BYTE				bAutoColor2BW;		//day/night mode 2:opened, 1:auto, 0:closed [日/夜模式 2:开；1：自动; 0:关]
	BYTE				bMirror;			//mirrorimage, 1:opened, 0:closed [镜像  1 开， 0关]
	BYTE				bFlip;				//reversal, 1:opened, 0:closed [翻转  1 开， 0关]
	char				bRev[123];			//reserved [保留]
} DHDEV_CAMERA_CFG;

#define ALARM_MAX_NAME 64
//(wireless) infrayed alarm configure [(无线)红外报警配置]
typedef struct
{
	BOOL				bEnable;							//alarm input enable [报警输入使能]
	char				szAlarmName[RV_MAX_ALARM_NAME];		//alarm input name [报警输入名称]
	int					nAlarmInPattern;					//alarm input wave [报警器输入波形]
	int					nAlarmOutPattern;					//alarm output wave [报警输出波形]
	char				szAlarmInAddress[RV_MAX_ALARM_NAME];//alarm input address [报警输入地址]
	int					nSensorType;						//out device's sensor type : always opened or always closed [外部设备传感器类型常开 or 常闭]
	int					nDefendEfectTime;					//ally delay time, alarm input is valid after this time [布撤防延时时间，在此时间后该报警输入有效]
	int					nDefendAreaType;					//area type [防区类型 ]
	int					nAlarmSmoothTime;					//alarm smooth time, means, if there are two alarm input occured in this time, ignored the second [报警平滑时间，即在此时间内如果只有一个报警输入连续输入两次则忽略掉后面一次]
	char				reserved[128];

	RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];
	RV_MSG_HANDLE		struHandle;							//deal method [处理方式]
} RV_INFRARED_INFO;

//wireless remote control configure [无线遥控器配置]
typedef struct 
{
	BYTE  address[ALARM_MAX_NAME];							// address of remote control [遥控器地址]
	BYTE  name[ALARM_MAX_NAME];								// name of remote control [遥控器名称]
	BYTE  reserved[32];										// reserved [保留字段]
}RV_WI_CONFIG_ROBOT;

//wireless alarm output configure [无线报警输出配置]
typedef struct 
{
	BYTE  address[ALARM_MAX_NAME];							//alarm output address [报警输出地址]
	BYTE  name[ALARM_MAX_NAME];								//alarm output name [报警输出名称]
	BYTE  reserved[32];										//reserved [保留字段]
}RV_WI_CONFIG_ALARM_OUT;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bAlarmInNum;						//number wireless alarm input [无线报警输入数]
	BYTE				bAlarmOutNum;						//number of wireless alarm out [无线报警输出数]
	RV_WI_CONFIG_ALARM_OUT AlarmOutAddr[16];				//address of alarm output [报警输出地址]
	BYTE				bRobotNum;							//number of remote control [遥控器个数]
	RV_WI_CONFIG_ROBOT RobotAddr[16];						//address of remote control [遥控器地址]
	RV_INFRARED_INFO	InfraredAlarm[16];
	char				reserved[256];
} RV_INFRARED_CFG;

//new audio detect alarm information [新音频检测报警信息]
typedef struct {
	int channel;						//alarm channel No. [报警通道号]
	int alarmType;						//alarm type,0-audio value low, 1-audio value high [报警类型0--音频值过低 1---音频值过高]
	unsigned int volume;				//audio value [音量值]
	char 	reserved[256];
} NET_NEW_SOUND_ALARM_STATE;

typedef struct  
{
	int channelcount;                   //channel number of alarm [报警的通道个数]
	NET_NEW_SOUND_ALARM_STATE  SoundAlarmInfo[RV_MAX_ALARM_IN_NUM];
}RV_NEW_SOUND_ALARM_STATE;

//new audio detect alarm configure [新音频检测报警配置]
typedef struct
{
	BOOL				bEnable;							//alarm input enable [报警输入使能]
	int					Volume_min;							//min audio volumn [音量的最小值]
	int					Volume_max;							//max audio volumn [音量的最大值]
	char				reserved[128];	
	RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];	
	RV_MSG_HANDLE		struHandle;							//deal method [处理方式]
} RV_AUDIO_DETECT_INFO;

typedef struct  
{
	DWORD					dwSize;
	int						AlarmNum;
	RV_AUDIO_DETECT_INFO	AudioDetectAlarm[RV_MAX_ALARM_IN_NUM];
	char					reserved[256];
} RV_AUDIO_DETECT_CFG;

//struct of store position, set stand alone per channel, every channel can select every store type, include local, removable, remote store, now [存储位置设置结构体，每通道独立设置,每通道可以选择各种存储类型, 目前包括本地, 可移动, 远程存储.]
typedef struct 
{
	DWORD 	dwSize;
	DWORD 	dwLocalMask;					//mask of local store, flag by bits : [本地存储掩码  按位表示：]
											//bit0:system pre-record [第一位	系统预录]
											//bit1:timer record [第二位	定时录像]
											//bit2:motion detect record [第三位	动检录像]
											//bit3:alarm record [第四位	报警录像]
											//bit4:card record [第五位	卡号录像]
											//bit5:manual record [第六位	手动录像]

	DWORD 	dwMobileMask;					//mask of removable store, store mask eg. local store mask [可移动存储掩码 存储掩码如本地存储掩码]
	int  	RemoteType;						//remote store type, 0:Ftp, 1:Smb [远程存储类型 0: Ftp  1: Smb ]
	DWORD 	dwRemoteMask;					//remote store mask, store mask eg. local store mask [远程存储掩码 存储掩码如本地存储掩码]
	DWORD 	dwRemoteSecondSelLocal;			//local store mask on remote exception [远程异常时本地存储掩码]
	DWORD 	dwRemoteSecondSelMobile;		//removable store mask on remote exception [远程异常时可移动存储掩码]
	char 	SubRemotePath[MAX_PATH_STOR];	//remote folder, the length is 260 [远程目录, 其中长度为260]
	char	reserved[128];
}RV_STORAGE_STATION_CFG;

/************************************************************************
*   network snapshot configure [网络抓包配置]
************************************************************************/
typedef struct
{
	int					Offset;			//bit offset of flag bit [标志位的位偏移]
	int					Length;			//length of flag bit [标志位的长度]
	char				Key[16];		//value of flag bit [标志位的值]
} RV_SNIFFER_FRAMEID;

typedef struct 
{
	int					Offset;			//bit offset of flag bit [标志位的位偏移]
	int					Offset2;		//invalid now [目前没有应用]
	int					Length;			//length of flag bit [标志位的长度]
	int					Length2;		//invalid now [目前没有应用]
	char				KeyTitle[24];	//value of title [标题的值]
} RV_SNIFFER_CONTENT;

typedef struct 
{
	RV_SNIFFER_FRAMEID	snifferFrameId;								//every FRAME's ID option [每个FRAME ID 选项]
	RV_SNIFFER_CONTENT	snifferContent[RV_SNIFFER_CONTENT_NUM];		//every FRAME's four capture package content [每个FRAME对应的4个抓包内容]
} RV_SNIFFER_FRAME;

//every captrue package corresponding configure struct [每组抓包对应的配置结构]
typedef struct
{
	char				SnifferSrcIP[RV_MAX_IPADDR_LEN];			//src IP address of sniffer [抓包源地址]		
	int					SnifferSrcPort;								//src port of sniffer [抓包源端口]
	char				SnifferDestIP[RV_MAX_IPADDR_LEN]; 			//dest IP address of sniffer [抓包目标地址]
	int					SnifferDestPort;							//dest port of sniffer [抓包目标端口]
	char				reserved[28];								//reserved [保留字段]
	RV_SNIFFER_FRAME	snifferFrame[RV_SNIFFER_FRAMEID_NUM];		//6 FRAME options [6个FRAME 选项]
	int					displayPosition;							//display position [显示位置]
	int					recdChannelMask;							//channel mask [通道掩码]
} RV_ATM_SNIFFER_CFG;

typedef struct  
{
	DWORD dwSize;
	RV_ATM_SNIFFER_CFG SnifferConfig[4];
	char	reserved[256];											//reserved [保留字段]
}DHDEV_SNIFFER_CFG;


/************************************************************************
*   OEM query [OEM查询]
************************************************************************/
typedef struct  
{
	char				szVendor[RV_MAX_STRING_LEN];
	char				szType[RV_MAX_STRING_LEN];
	char				reserved[128];
}DHDEV_OEM_INFO;


/************************************************************************
*   NTP configure [NTP配置]
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
	BOOL				bEnable;			//	enable [是否启用]
	int					nHostPort;			//	NTP server's default port is 123 [NTP服务器默认端口为123]
	char				szHostIp[32];		//	host's IP [主机IP]
	char				szDomainName[128];	//	domain [域名]
	int					nType;				//	can't set, 0:IP, 1:domain, 2:IP and domain [不可设置 0：表示IP，1：表示域名，2：表示IP和域名]
	int					nUpdateInterval;	//	update time (minute) [更新时间(分钟)]
	int					nTimeZone;			//	reference to RV_TIME_ZONE_TYPE [见RV_TIME_ZONE_TYPE]
	char				reserved[128];
}DHDEV_NTP_CFG;


/************************************************************************
*   platform connection configure - U WANAG TONG [平台接入配置 － U网通]
************************************************************************/
typedef struct
{
	BOOL bChnEn;
	char szChnId[RV_INTERVIDEO_UCOM_CHANID];
}RV_INTERVIDEO_UCOM_CHN_CFG;

typedef struct
{
	DWORD dwSize;
	BOOL bFuncEnable;										//function enable 0 - enable [接入功能使能与否 0 - 使能]
	BOOL bAliveEnable;										//alive enable [心跳使能与否]
	DWORD dwAlivePeriod;									//heart cycle, unit is second 0-3600 [心跳周期，单位秒，0-3600]
	char szServerIp[RV_MAX_IPADDR_LEN];						//CMS's IP [CMS的IP]
	WORD wServerPort;										//CMS's port [CMS的Port]
	char szRegPwd[RV_INTERVIDEO_UCOM_REGPSW];				//regiter password [注册密码]
	char szDeviceId[RV_INTERVIDEO_UCOM_DEVID];				//device's id [设备id]
	char szUserName[RV_INTERVIDEO_UCOM_USERNAME];
	char szPassWord[RV_INTERVIDEO_UCOM_USERPSW];
	RV_INTERVIDEO_UCOM_CHN_CFG  struChnInfo[RV_MAX_CHANNUM];//channel id,en [通道id,en]
}DHDEV_INTERVIDEO_UCOM_CFG;

/************************************************************************
*   platform connection configure - alcater [平台接入配置 － 阿尔卡特]
************************************************************************/
typedef struct
{
	DWORD dwSize;
	unsigned short usCompanyID[2];		/* Corp. ID, value, different three part service Corp. consider 4 bytes justification, only use the first in array now [公司ID,数值,不同的第三方服务公司,考虑4字节对齐,目前只用数组第一个] */
	char szDeviceNO[32];				/* serial number of front device, string, conrain '\0' total 32 bytes [前端设备序列号，字符串, 包括'\0'结束符共32byte] */
	char szVSName[32];					/* front device, string, contain '\0' total 16 bytes [前端设备名称，字符串, 包括'\0'结束符共16byte] */
	char szVapPath[32];					/* VAP path [VAP路径] */
	unsigned short usTcpPort;			/* TCP port, value : 1~65535 [TCP 端口,数值: 数值 1~65535] */    
	unsigned short usUdpPort;			/* UDP port, value : 1~65535 [UDP 端口,数值: 数值 1~65535] */    
	bool bCsEnable[4];					/* enable of center server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [中心服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szCsIP[16];					/* IP address of center server, string, contain '\0' total 16 bytes [中心服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usCsPort[2];			/* port of center server, value : 1~65535, consider 4 bytes justification, only use the first in array now [中心服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */    
	bool bHsEnable[4];					/* enable of heart beat server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [心跳服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szHsIP[16];					/* IP address of heart beat server, string, contain '\0' total 16 bytes [心跳服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usHsPort[2];			/* port of heart beat server, value : 1~65535, consider 4 bytes justification, only use the first in array now [心跳服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */ 
	int iHsIntervalTime;				/* time slice of heart beat server, value (unit:second) [心跳服务器间隔周期,数值(单位:秒)] */ 
	bool bRsEnable[4];					/* enable of registration server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [注册服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szRsIP[16];					/* IP address of registration server, string, contain '\0' total 16 bytes [注册服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usRsPort[2];			/* port of registration server, value : 1~65535, consider 4 bytes justification, only use the first in array now [注册服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */
	int iRsAgedTime;					/* valid time of registration server, value (unit:hour) [注册服务器有效时间,数值(单位:小时)] */
	char szAuthorizeServerIp[16];		/* IP address of authority server [鉴权服务器IP] */
	unsigned short usAuthorizePort[2];  /* port of authority server, value : 1~65535, consider 4 bytes justification, only use the first in array now [鉴权服务器端口,考虑4字节对齐,目前只用数组第一个] */
	char szAuthorizeUsername[32];		/* account of authority server [鉴权服务器帐号] */
	char szAuthorizePassword[36];		/* password of authority server [鉴权服务器密码] */

	char szIpACS[16];					/* ACS (auto registration server) IP [ACS(自动注册服务器) IP] */
	unsigned short usPortACS[2];		/* ACS port, consider 4 bytes justification, only use the first in array now [ACS Port,考虑4字节对齐,目前只用数组第一个] */
	char szUsernameACS[32];				/* ACS user name [ACS用户名] */
	char szPasswordACS[36];				/* ACS password [ACS密码] */
	bool bVideoMonitorEnabled[4];		/* if DVS timer to up-send message of fornt video signal watch, value : true enable, false not enable [DVS是否定期上报前端视频信号监控信息, 数值: true使能, false不使能] */
	int iVideoMonitorInterval;			/* up-send timer slice (minute) [上报周期（分钟）] */

	char szCoordinateGPS[64];			/* GPS coordinate [GPS坐标] */
	char szPosition[32];				/* device position [设备位置] */
	char szConnPass[36];				/* device connection passport [设备接入码] */
}DHDEV_INTERVIDEO_BELL_CFG;

/************************************************************************
*   configure of plartform connection - ZHONGXINGLIWEI [平台接入配置 － 中兴力维]
************************************************************************/
typedef struct  
{
	DWORD dwSize;
	unsigned short		nSevPort;								//server port, value 1~65535 [服务器端口, 数值, 数值1~65535]
	char				szSevIp[RV_INTERVIDEO_NSS_IP];			//server IP address, string, contain '\0', total 32 bytes [服务器IP地址, 字符串, 包括'\0'结束符共32byte]
	char				szDevSerial[RV_INTERVIDEO_NSS_SERIAL];	//serial number of front device, string, contain '\0', total 32 bytes [前端设备序列号，字符串,包括'\0'结束符共32byte]
	char				szUserName[RV_INTERVIDEO_NSS_USER];
	char				szPwd[RV_INTERVIDEO_NSS_PWD];
}DHDEV_INTERVIDEO_NSS_CFG;

/************************************************************************
*   state information of network running [网络运行状态信息]
************************************************************************/

typedef struct
{
	int					nChannelNum;	//channel No. [通道号]
	char				szUseType[32];	//channel usage [通道用途]
	DWORD				dwStreamSize;	//flow rate (unit is kb/s) [流量大小(单位:kb/s)]
	char				reserved[32];	//reserved [保留]
}DHDEV_USE_CHANNEL_STATE;

typedef struct 
{
	char						szUserName[32];				//user name [用户名]
	char						szUserGroup[32];			//user group [用户组]
	NET_TIME					time;						//logined time [登入时间]
	int							nOpenedChannelNum;			//opened channel number [开启的通道个数]
	DHDEV_USE_CHANNEL_STATE		channelInfo[RV_MAX_CHANNUM];
	char						reserved[64];
}DHDEV_USER_NET_INFO;

typedef	struct 
{
	int							nUserCount;		//user count [用户数量]
	DHDEV_USER_NET_INFO			stuUserInfo[32];
	char						reserved[256];
}DHDEV_TOTAL_NET_STATE;
/************************************************************************
*   attributes of PTZ [云台属性信息]
************************************************************************/
#define  NAME_MAX_LEN 16
typedef struct 
{
	DWORD		dwHighMask;				/*!< high bits of operation's mask [操作的掩码高位] */
	DWORD		dwLowMask;				/*!< low bits of operation's mask [操作的掩码低位] */
	char		szName[NAME_MAX_LEN];	/*!< operation's protocal name, NAME_MAX_LEN=16 [操作的协议名NAME_MAX_LEN=16] */
	WORD		wCamAddrMin;			/*!< channel address's min value [通道地址的最小值] */
	WORD		wCamAddrMax;			/*!< channel address's max value [通道地址的最大值] */
	WORD		wMonAddrMin;			/*!< watch address's min value [监视地址的最小值] */
	WORD		wMonAddrMax;			/*!< watch address's max value [监视地址的最大值] */
	BYTE		bPresetMin;				/*!< preset's min value [预置点的最小值] */
	BYTE		bPresetMax;				/*!< preset's max value [预置点的最大值] */
	BYTE		bTourMin;				/*!< auto tour's min value [自动巡航线路的最小值] */
	BYTE		bTourMax;				/*!< auto tour's max value [自动巡航线路的最大值] */
	BYTE		bPatternMin;			/*!< tour's min value [轨迹线路的最小值] */
	BYTE		bPatternMax;			/*!< tour's max value [轨迹线路的最大值] */
	BYTE		bTileSpeedMin;			/*!< vertical speed's min value [垂直速度的最小值] */
	BYTE		bTileSpeedMax;			/*!< vertical speed's max value [垂直速度的最大值] */
	BYTE		bPanSpeedMin;			/*!< horizontal speed's min value [水平速度的最小值] */
	BYTE		bPanSpeedMax;			/*!< horizontal speed's max value [水平速度的最大值] */
	BYTE		bAuxMin;				/*!< assist function's min value [辅助功能的最小值] */
	BYTE		bAuxMax;				/*!< assist function's max value [辅助功能的最大值] */
	int			nInternal;				/*!< send command's time slice [发送命令的时间间隔] */
	char		cType;					/*!< protocal's type [协议的类型] */
	char		Reserved[7];
}PTZ_OPT_ATTR;
/************************************************************************
*   returned information of setting device [设置设备返信息]
************************************************************************/
typedef struct
{
	DWORD		dwType;			//type, the same as type of GetDevConfig SetDevConfig [类型(即GetDevConfig SetDevConfig的类型)]
	WORD		wResultCode;	//recturned code [返回码：]
								/*		0:success [成功]
								*		1:fail [失败]
								*		2:data invalid [数据不合法]
								*		3:can't set now [暂时无法设置]	
								*		4:no authority [没有权限]
								*/

	WORD   		wRebootSign;	//reboot flag [重启标志：]
								/*
								*	0:no need to reboot, 1:need to reboot to make it valid [0:不需要重启 1:需要重启才生效]
								*/
	DWORD		dwReserved[2];	//reserved [保留]	
}DEV_SET_RESULT;

/******************************************************************************
* attributes struct of snapshot function [抓图功能属性结构体]
*****************************************************************************/

typedef struct 
{
	int			nChannelNum;			//channel index [通道号]

	DWORD		dwVideoStandardMask	;	//resolve (by bit) detail reference to enum CAPTURE_SIZE [分辨率(按位) 具体查看枚举 CAPTURE_SIZE]
	int			nFramesCount;			//valid length of [Frequence[128] array [Frequence[128]数组的有效长度]
	char 		Frames[128];			//frame rate (by value) [帧率（按数值）]
										//-25:25 seconds per frame [-25:25秒1帧]
										//-24:24 seconds per frame [-24:24秒1帧]
										//-23:23 seconds per frame [-23:23秒1帧]
										//-22:22 seconds per frame [-22:22秒1帧]
										//……
										//0:valid [0:无效]
										//1:1 frames per second [1：1秒1帧]
										//2:2 frames per second [2：1秒2帧]
										//3:3 frames per second [3：1秒3帧]
										//4:4 frames per second [4：1秒4帧]
										//5:5 frames per second [5：1秒5帧]
										//17:17 frames per second [17：1秒17帧]
										//18:18 frames per second [18：1秒18帧]
										//19:19 frames per second [19：1秒19帧]
										//20:20 frames per second [20：1秒20帧]
										//……
										//25:25 frames per second [25: 1秒25帧]
	int			nSnapModeCount;			//valid length of SnapMode[16] array [SnapMode[16]数组的有效长度]
	char		SnapMode[16];			//(by value) 0:timer snapshot 1:manual triggered snapshot [（按数值） 0：定时触发抓图 1：手动触发抓图]
	int			nPicFormatCount;		//valid length of Format[16] array [Format[16]数组的有效长度]
	char 		PictureFormat[16];		//by value 0:BMP format 1:JPG format [（按数值）0:BMP格式 1:JPG格式]
	int			nPicQualityCount;		//valid length of Quality[32] array [Quality[32]数组的有效长度]
	char 		PictureQuality[32];		//(by value) [（按数值）]
										//100:picture quality 100% [100:图象质量100%]
										//80:picture quality 80% [80:图象质量80%]
										//60:picture quality 60% [60:图象质量60%]
										//50:picture quality 50% [50:图象质量50%]
										//30:picture quality 30% [30:图象质量30%]
										//10:picture quality 10% [10:图象质量10%]
	char 		nReserved[128];			//reserved [保留]
} RV_QUERY_SNAP_INFO;

typedef struct 
{
	int			nChannelCount;					//channel number [通道个数]
	RV_QUERY_SNAP_INFO  stuSnap[RV_MAX_CHANNUM];
}RV_SNAP_ATTR_EN;

typedef struct  
{
	int	iLen;			//real data lenght [实际数据长度]
	int iChannel;		//channel index [通道号]
	char acData[32];	//real data [实际数据]
}RV_PTZ_RAW_DATA_H;

/******************************************************************************
* attributes struct of auto registration function [主动注册功能属性结构体]
*****************************************************************************/

typedef struct
{
	DWORD	 dwSize;
	LONG     iEnable;			//enable [使能]
	LONG     iConnectType;		//connection method, 0:single connection(using old command media single connection mode), 1:multi connections (commands auto register to server, media need to dynamicly reconnect to server under command control eg. case of video request) [连接方式，0：单连接（使用原有的信令媒体单一连接模式） 1：多连接 （采取信令为主动注册连接，媒体需要在信令控制如视频请求情况下进行新的动态连接方式）
	char	 strServerIp[16];	//ip of registration server [注册服务器ip]	
	LONG     iServerPort;		//port of registration server [注册服务器端口]
	char     strUsr[64];		//user name [用户名]
	char     strPwd[64];		//password [密码]
	char     strPuId[32];		//device identify, 32bits, recording to platform server definition [设备统一标识，32位标识，由平台服务器约定]
								/*
								rule of identify device [设备统一标识规则] 
								using 32 bytes now, details recording to platform server definition [现有使用了32字节，具体信息安排，由平台服务器约定规则]
								
								Xx							yy						zz											a      								b						cccccccc cccccccc ccccccccc
								2 bytes	[2字节]				2 bytes	[2字节]			2 bytes	[2字节]								1 byte [1字节]     					1 byte [1字节]			24 bytes [24字节] 
								No. in province [省级编号]	No. in city [市级编号]	reserved for No. in city [市级编号保留字]	front 0,client1 [前端 0，客户端1]	device type [设备类型]	device serial number [设备序号]
								
								values of device type : 01:DVR 02:IPC 03:NVS 04:decoder 05:DVR on vehicle [其中设备类型 01： DVR； 02 ：IPC ；03：NVS ； 04 ：解码器；05：车载DVR]
								*/
}RV_CONFIG_REG_SERVER;

/******************************************************************************
* attributes struct of tour function [轮巡功能属性结构体]
*****************************************************************************/
#define V_TOUR_COMBINE_NUM 10
typedef struct
{
	unsigned int iSplitMode;	//support many multi-views preview mode, flag by bits, reference to enum split_combine_t [支持多种画面预览模式，按位标识，参考枚举split_combine_t]
								//bit0 : SPLIT1, this is default in all devices, this is sinlg view and full screen [第0位 SPLIT1 此默认都支持，此为单画面，全屏]
								//bit1 : SPLIT2 [第1位 SPLIT2] 
								//bit2 : SPLIT4 [第2位 SPLIT4]
								//bit3 : SPLIT8 [第3位 SPLIT8] 
								//bit4 : SPLIT9 [第4位 SPLIT9]
								//bit5 : SPLIT16 [第5位 SPLIT16] 
								//bit6 : SPLITIP [第6位 SPLITIP]
								//bit7 : SPLIT6 [第7位 SPLIT6] 
								//bit8 : SPLIT12 [第8位 SPLIT12]
}RV_SPLIT_MODE;
typedef struct
{
	unsigned char bTourEnable;		//enable [使能]
	unsigned char ucRes;	
	unsigned short usIntervalTime;	//tour time slice [轮巡时间间隔]
}RV_DISPLAY_TOUR_CFG;
typedef struct
{
	DWORD	 dwSize;
	RV_DISPLAY_TOUR_CFG stDisplayTour;
	RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
}RV_DISPLAY_TOUR;

/******************************************************************************
* struct of views split function [画面分割功能属性结构体]
*****************************************************************************/
typedef struct
{
	RV_SPLIT_MODE stSplitMode;		//mode [模式]
	RV_SPLIT_COMBINE_CH stCombineCH;//channel combine [通道组合]
}RV_DISPLAY_SPLIT_CFG;

/******************************************************************************
* channel combine and tour struct of decoder views group [解码器画面分组通道组合以及轮询结构体]
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
* struct of snapshot [抓图配置结构体]
*****************************************************************************/
#define MAX_SNAP_COUNT 32
typedef struct
{   	    	
	int iChannel;
	int Enable;					/*enable of timer snapshot [定时抓拍使能]*/
	int SnapQuality;			/*picture quality of snapshot, 6 levels, 1:bad, 2:not bad, 3:common, 4:good, 5:better, 6:best [抓拍图像质量，初步分6档， 1 差 2 一般 3普通， 4好， 5很好， 6最好]*/
								/*snap plot [抓图策略]
								 usSnapMode : snapshot mode, 0 means mode of how many pictures per second [usSnapMode 抓拍模式， 0 表示1秒几张模式]
															 1 means mode of how many seconds per picture [1 表示几秒1张模式]
															 2 means mode of how many minutes per picture [2 表示几分钟1张模式]
								 usCounts : value corresponding snapshot mode [usCounts 对应抓拍模式下的数值]
								*/
	unsigned short usSnapMode;
	unsigned short usCounts;	/*snapshot picture number (under mode of how many pictures per second) or snapshot time (mode of how many seconds per picture) [抓拍张数（1秒几张模式）或者抓拍时间（几秒1张模式）]*/
	int SnapCount;
}RV_CONFIG_SNAP;
typedef struct
{
	DWORD dwSize;
	DWORD dwCount;								//on setting:==channel count is all, >=0&&<channel count is which channel configure [设置时：==通道数为所有，>=0&&<通道数为哪个通道配置]
												//on getting:returned number [读取时：返回个数]
	RV_CONFIG_SNAP stSnapCfg[MAX_SNAP_COUNT];
}RV_SNAP;

typedef struct
{
	unsigned short usTotal;  //total channel number [总通道数目]
	unsigned short usIndex;  //which channel's information [第几个通道信息]
}RV_DEV_CHANNEL;

/******************************************************************************
* struct of decoder [解码器报警配置结构体]
*****************************************************************************/
#define RV_N_UI_TSECT					6
#define RV_N_WEEKS						7
typedef struct
{
	int				enable;		    //enable [使能]
	unsigned char	startHour; 		//start time : hour [开始时间:小时]		
	unsigned char	startMinute;	//start time : minute [开始时间:分钟]		
	unsigned char	startSecond; 	//start time : second [开始时间:秒钟]		
	unsigned char	endHour;		//end time : hour [结束时间:小时]		
	unsigned char	endMinute; 		//end time : minute [结束时间:分钟]		
	unsigned char	endSecond; 		//end time : second [结束时间:秒钟]		
	unsigned char   ucReserved[2];  //reserved [保留]
}RV_NETSECTION;		
typedef struct
{
	int				iName;
	RV_NETSECTION	tsSchedule[RV_N_WEEKS][RV_N_UI_TSECT];	/*time slice [时间段]*/
}RV_NET_WORKSHEET;
#define RV_N_SYS_CH 16
typedef struct
{		
	unsigned int		dwRecord;				/* record mask [录象掩码] */
	int					iRecordLatch;			/* record delay : 10~300 second [录像延时：10～300 sec] */ 	
	unsigned int		dwTour;					/* tour mask [轮巡掩码] */	
	unsigned int		dwSnapShot;				/* snapshot mask [抓图掩码] */
	unsigned int		dwAlarmOut;				/* alarm output channel mask [报警输出通道掩码] */
	int					iAOLatch;				/* alarm output delay : 10~300 second [报警输出延时：10～300 sec] */ 
	RV_PTZ_LINK			PtzLink[RV_N_SYS_CH];	/* PTZ linkage items [云台联动项] */		
	int					bRecordEn;				/* record enable [录像使能] */
	int					bTourEn;				/* tour enable [轮巡使能] */
	int					bSnapEn;				/* snapshot enable [抓图使能] */	
	int					bAlarmOutEn;			/* alarm enable [报警使能] */
	int					bPtzEn;					/* PTZ linkage enable [云台联动使能] */
	int					bTip;					/* screen prompt enable [屏幕提示使能] */	
	int					bMail;					/* send email [发送邮件] */	
	int					bMessage;				/* send message to alarm center [发送消息到报警中心] */	
	int					bBeep;					/* beep [蜂鸣] */	
	int					bVoice;					/* audio prompt [语音提示] */		
	int					bFTP;					/* lauch FTP transport [启动FTP传输] */		
	int					iWsName;				/* time table selection, because it is using number as index in time table, and will not be changed [时间表的选择，由于时间表里使用数字做索引，且不会更改] */
	unsigned int		dwMatrix;				/* matrix mask [矩阵掩码] */
	int					bMatrixEn;				/* matrix enable [矩阵使能] */
	int					bLog;					/* log enable, it is just be using in WTN motion detect [日志使能，目前只有在WTN动态检测中使用] */
	int					iEventLatch;			/* linkage start delay time, second is unit [联动开始延时时间，s为单位] */
	int					bMessagetoNet;			/* send message to network enable [消息上传给网络使能] */
	unsigned int		dwReserved[7]; 			/* reserved [保留字节] */
}RV_EVENT_HANDLER;
typedef struct
{
	int iEnable;	//alarm guard enable, 0:disable, 1:enable [告警布防撤防 0撤防，1布防]
	int iReserved;	//common configure, details as bellow [通用配置信息，具体定义如下]
					//in alarm input, this means sensor type, 0:always opened, 1:always closed [告警输入标识传感器类型常开 or 常闭；0常开，1常闭]
					//in video lost and motion detect, this means sensitivity : 0~6 levels, level 6 is most sensitivity [视频丢失和动检为灵敏度；0~6档次，6档次为最灵敏]
					//in disk, this means the lowest limit of left space in disk, percent [磁盘为硬盘剩余容量下限, 百分数]
					//in intelligent red alarm, this means sensitivity : 0~6 levels, level 6 is most sensitivity [智能红色报警为灵敏度；0~6档次，6档次为最灵敏]
}RV_ALARM_GUARD;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
} RV_DECODER_ALARM,*LPRV_DECODER_ALARM;
 
typedef struct
{
	DWORD dwSize;		
	RV_DECODER_ALARM 		struDecoderAlarm[RV_MAX_DECODER_CHAN_NUM]; //16-32 最大通道数目 zb
}RV_DECODER_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//	other alarm structs [其他报警结构]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
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
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
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
//	TV adjuest struct [TV调节结构]
//////////////////////////////////////////////////////////////////////
typedef struct 
{
	int left;	//[0,100]
	int top;	//[0,100]
	int right;	//[0,100]
	int bottom;	//[0,100]
}RV_VD_RECT;
//TV adjust configure [TV调节设置]
typedef struct
{
	DWORD dwSize;
	RV_VD_RECT rctMargin;		//TV zoom out rate, every value's range are the same [0,100] [TV缩小比率，各分量取值相同   [0,100]]		
	int iBrightness;			//brightness [0,100] [亮度[0,100]]		
	int iContrast;				//contrast [0,100] [对比度[0,100]]	
	int iAntiDither;			//antidither [0,100] [去抖动[0,100]]
}RV_TVADJUST;

//////////////////////////////////////////////////////////////////////
//	common configure [普通配置]
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//	struct of daylight saving time [夏令时结构体]
typedef struct
{
	int Hour;
	int Minute;
}RV_DSTTIMES;
typedef struct
{
	int iYear;			//year [2000,2037]
	int iMonth;			//month from January=1 [1,12]
	int iWeek;			//week1:first  to2 3 4 -1:last one   0:calculate method by days [-1,4] [周1:first  to2 3 4 -1:last one   0:表示使用按日计算的方法[-1,4]]
	union
	{
		int iWeekDay;	//weekday from sunday=0 [0, 6]
		int iDays;		//day from one=1[0, 31]
	};	
	RV_DSTTIMES time;
}RV_DST_POINT;
//week mode selection [周模式选择]
//iMonth，iWeek(-1,1,2,3,4)， iWeekDay，Hour，Min
//day mode selection, iWeek=0 [日模式选择 iWeek=0]
//iYear ,iMonth,iDays，Hour，Min
typedef struct
{
	RV_DST_POINT iDST[2];
	unsigned char ucEnable;//0:disable, 1:enable [0,不使能，1使能]
	unsigned char ucRes[3];//reserved [保留] 
}RV_DST_TIME;
typedef struct
{ 		
	int  iCtrlMask;						/*flag by bit mask [按位掩码形式]
										0 : deal on disk full, 1:OverWrite, 0:StopRecord [0 硬盘满时处理 1覆盖"OverWrite", 0停止"StopRecord"] 
										1 : if mute [1 是否静音]
										2 : LCD screen auto close [2 LCD屏幕自动关闭]
										3 : if TV output [3 是否TV输出]
										4 : if VGA output [4 是否VGA输出]
										5 : if HDMI output [5 是否HDMI输出]
										*/		
	int iLocalNo;						//local machine No. : [0,?998]? [本机编号:[0,?998]? ]
	unsigned short usScreenSaveTime;	//screen protection (minute) [0,120] [屏保时间(分钟) [0, 120]	]
	unsigned short usAutoLogout;		//local menu auto logout (minute) [0, 120] [本地菜单自动注销(分钟) [0, 120]]
	unsigned char ucDateFormat;			//date format :"YYMMDD","MMDDYY","DDMMYY" [日期格式:“YYMMDD”, “MMDDYY”, “DDMMYY” ]
	unsigned char ucDateSprtr;			//date seperate : ".","-","/" [日期分割符:“.”, “-”, “/”] 
	unsigned char ucTimeFmt;			//time format : 1:12, 0:24 [时间格式:1：“12”, 0：“24”] 
	unsigned char ucRes;
	unsigned char ucSupportVideoFmt;	//device supported video standard, bit0:PAL, bit1:NTSC, bit2:SECAM [设备可以支持的制式 ， 第0位 PAL ，第1位 NTSC， 第2位 SECAM]
	unsigned char ucCurVideoFmt;		//device used video standard, 0:PAL, 1:NTSC, 2:SECAM [设备使用的制式 ，0 PAL ，1 NTSC， 2 SECAM]
	unsigned char ucRes1[2];
	unsigned int uiSupportLanguage;		//device supported languages [设备可以支持的语言 ， ]
										//bit0:English, bit1:SimpChinese, bit2:TradChinese [第0位 English，第1位 SimpChinese， 第2位 TradChinese，]
										//bit3:Italian, bit4:Spanish, bit5:Japanese, bit6:Russian, bit7:French, bit8:German [第3位 “Italian”,4 “Spanish”, 5“Japanese”, 6“Russian”, 7“French”, 8“German” ]
	unsigned int uiCurLanguage;			//device used languages [设备使用的语言 ，]
										//0:English, 1:SimpChinese, 2:TradChinese, 3:Italian, 4:Spanish [0 English，1 SimpChinese，2 TradChinese，3“Italian”,4 “Spanish”,] 
										//5:Japanese, 6:Russian, 7:French, 8:German [5“Japanese”, 6“Russian”, 7“French”, 8“German”] 
	unsigned int uiRes[3];				//reserved [保留字节]						
}RV_NET_GENERAL;

//2010-10-12 luhj add
typedef struct  
{
	char	cSize;						//字体大小，1表示标准倍数，2表示2倍大小  该值取值范围在1到ucZoomAbility之间
	char	cRes[3];					//保留
}RV_OSDZOOM_PARAM;
//end
// system time struct [系统时间结构]
typedef struct
{
	int  year;	//year [2000,2037] [年。[2000,2037]]   
	int  month;	//month January = 1, February = 2, and so on. [月，January = 1, February = 2, and so on. ]  
	int  day;	//day [日。]   
	int  wday;	//week, Sunday = 0, Monday = 1, and so on [星期，Sunday = 0, Monday = 1, and so on]   
	int  hour;	//hour [时。]   
	int  minute;//minute [分。]  
	int  second;//second [秒。]   
	int  isdst;	//flag daylight saving time [夏令时标识。]   
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
//	platform connection configure [平台接入配置]
//////////////////////////////////////////////////////////////////////
//platform of HUXINGHUTONG [互信互通平台接入配置]
typedef struct
{
	DWORD dwSize;
	BOOL			Enable;			//enable [使能]
	int				MaxConn;		//max connection number of video connection [视频最大连接数]	
	char			ServerIp[40];	//server IP [服务器IP]	
	unsigned short	ServerPort;		//server Port [服务器端口]
	unsigned short	MegaPort;		//listen port [监听端口]	
	char			DeviceId[32];	//device ID [设备ID]	
	char			UserName[32];	//user name [用户名]
	char			PassWords[32];	//password [密码]
	unsigned short	DownLoadMode;	//record download method by bits, 0:TCP, 1:HTXT [录像下载方式按位0 TCP 1 HTXT]
	unsigned short	FunMask;		/*function mask, operate by bits [功能掩码，按位操作]
									bit0:if support prediction scheme [第0位是否支持预案]
									bit1:if support network management [第1位是否支持网管]
									bit2:if support pre-record [第2位是否支持预录]
									bit3:if support NAT [第3位是否支持NAT]
									*/	
	unsigned short	AlarmInterVal;	//alarm time slice [报警间隔]
	unsigned short	Reserve;
}RV_CONFIG_NET_MEGA;
/************************************************************************
*   platform of ALCATEL [平台接入配置 － 阿尔卡特]
************************************************************************/
typedef struct
{
	DWORD dwSize;
	unsigned short usCompanyID[2];		/* Corp.ID, value, different three part service Corp. consider 4 bytes justification, using the first of the array [公司ID,数值,不同的第三方服务公司,考虑4字节对齐,目前只用数组第一个] */
	char szDeviceNO[32];				/* serial number of front device, string, contain '\0', total 32 bytes [前端设备序列号，字符串, 包括'\0'结束符共32byte] */
	char szVSName[32];					/* name of front device, string, contain '\0', total 16 bytes [前端设备名称，字符串, 包括'\0'结束符共16byte] */
	char szVapPath[32];					/* VAP path [VAP路径] */
	unsigned short usTcpPort;			/* TCP port, value : 1~65535 [TCP 端口,数值: 数值 1~65535] */    
	unsigned short usUdpPort;			/* UDP port, value : 1~65535 [UDP 端口,数值: 数值 1~65535] */    
	bool bCsEnable[4];					/* enable flag of center server, consider 4 bytes justification, using the first of the array [中心服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szCsIP[64];					/* IP of center server, string, contain '\0', total 16 bytes [中心服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usCsPort[2];			/* port of center server, consider 4 bytes justification, using the first of the array [中心服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */    
	bool bHsEnable[4];					/* enable flag of heart beat server, consider 4 bytes justification, using the first of the array [心跳服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szHsIP[64];					/* IP of heart beat server, string, contain '\0', total 16 bytes [心跳服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usHsPort[2];			/* port of heart beat server, consider 4 bytes justification, using the first of the array [心跳服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */ 
	int iHsIntervalTime;				/* time slice of heart beat server, value (unit : second) [心跳服务器间隔周期,数值(单位:秒)] */ 
	bool bRsEnable[4];					/* enable flag of registration server, consider 4 bytes justification, using the first of the array [注册服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szRsIP[64];					/* IP of registration server, string, contain '\0', total 16 bytes [注册服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usRsPort[2];			/* port of registratin server, value : 1~65535, consider 4 bytes justification, using the first of the array [注册服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */
	int iRsAgedTime;					/* valid time of registration server, value (unit:hour) [注册服务器有效时间,数值(单位:小时)] */
	char szAuthorizeServerIp[64];		/* IP of authority server [鉴权服务器IP] */
	unsigned short usAuthorizePort[2];  /* port of authority server, consider 4 bytes justification, using the first of the array [鉴权服务器端口,考虑4字节对齐,目前只用数组第一个] */
	char szAuthorizeUsername[32];		/* account of authority server [鉴权服务器帐号] */
	char szAuthorizePassword[36];		/* passsword of authority server [鉴权服务器密码] */

	char szIpACS[64];					/* ACS (auto registration server) IP [ACS(自动注册服务器) IP] */
	unsigned short usPortACS[2];		/* ACS port, consider 4 bytes justification, using the first of the array [ACS Port,考虑4字节对齐,目前只用数组第一个] */
	char szUsernameACS[32];				/* ACS user name [ACS用户名] */
	char szPasswordACS[36];				/* ACS password [ACS密码] */
	bool bVideoMonitorEnabled[4];		/* if DVS timer to upload the watch information of front video signal, value: true enable, false disable [DVS是否定期上报前端视频信号监控信息, 数值: true使能, false不使能] */
	int iVideoMonitorInterval;			/* upload timer slice (minute) [上报周期（分钟）] */

	char szCoordinateGPS[64];			/* GPS coordinate [GPS坐标] */
	char szPosition[32];				/* device position [设备位置] */
	char szConnPass[36];				/* device connection passport [设备接入码] */
}RV_INTERVIDEO_BELL_CFG;
//platform of VS300 [VS300平台配置]
typedef struct
{
	DWORD dwSize;
	BOOL    BEnalbe;		//enable, 4 bytes, 0:disable, 1:enable [使能 4字节 0 不使能 1 使能]
	char    acServerIp[32];	//server ip [服务器ip]
	long	iServerPort;	//listen port of server [服务器侦听端口]
	char    acUserName[32];	//user name [用户名]
	char    acPassWords[32];//password [密码]
	long	iType;			//protocal type, 0:tcp, 1:udp [协议类型 0 tcp 1 udp]
	char    acReserve[80];	//reserved [保留位]
}RV_CONFIG_VS300_NET;
//platform of SHENYAN [神眼平台接入配置]
typedef struct
{ 	
	DWORD dwSize;
	BOOL Enable;		//enable [是否开启]
	char ServerIp[64];	//IP of SHENYAN Sserver [神眼服务器IP]
	int ServerPort;		//port on SHENYAN server [神眼服务器端口号]
	char PUId[32];		//device ID [设备ID]
	int  usTcpPort;		/*TCP port, value:1~65535 [对外的TCP 端口,数值: 数值 1~65535] */    
	int  usUdpPort;		/*UDP port, value:1~65535 [对外的UDP 端口,数值: 数值 1~65535] */    
	char strUsr[16];
	char strPwd[16];    
	char strVer[16];
	char Reserved[16];
}RV_CONFIG_ZXSHENYAN_NET;
//////////////////////////////////////////////////////////////////////
//	disk configure [磁盘配置]
//////////////////////////////////////////////////////////////////////
typedef struct
{	
	unsigned char ucUse;			//enable [此分区是否有效]	
	unsigned char ucPartion;		//partion index [分区号；]	
	unsigned char ucFSType;			//partion supported file systems [分区支持的文件系统]	
									//0:WFS file system, max support 2 partions, and the partion is restrict to 3 types as bellow [0 WFS文件系统  现有最大支持2分区，且分区又约束如下三种方式]	
									//if WFS2 partion, default is that, the first partion is for snapshot, and the second is for recording [WFS2分区的话，默认第1分区为快照分区，第2分区为录像分区]	
									//if it is only one partion under WFS file system, it is decided by ucPartType [如果是WFS 1分区的话，根据ucPartType决定]	
									//ucPartType==0,record partion; ucPartType==1,snapshot partion [ucPartType==0，录像分区；ucPartType==1快照分区]	
									//now snapshot (store pictures) and the next record, device can only save one type of media [此时快照（存储图片）后者录像，设备只能进行一种媒体的存储]	
									//WFS file system only can be used as percet 2 partion mode [WFS文件系统约束只作百分比2分区模式]	
									//1 FAT32	
									//2 EXT3	
	unsigned char ucPartType;		//this is used by WFS file system pnly, 0:record partion, 1:snapshot partion, standard file system, not need, no limit [WFS文件系统分区专用 0 录像分区  1快照分区；标准文件系统，不需要，无限制]	
	unsigned int uiTotalSpace;		//< total space, it's unit reference to ucSpaceType introduction [< 总容量，其单位参考ucSpaceType说明]	
	unsigned int uiRemainSpace;		//< left space, it's unit reference to ucSpaceType introduction [< 剩余容量，其单位参考ucSpaceType说明]	
	unsigned char ucSpaceType;		//identify disk space unit, convenient to more correct statistic [标识硬盘容量单位，方便比较准确的统计]	
									//the next 4 bits (7 6 5 4) total space unit 0 KB，1MB，2GB，3TB [后4位（7  6 5 4 ） 总大小单位  0 KB，1MB，2GB，3TB]								
									//the first 4 bits (3 2 1 0) left space unit 0 KB，1MB，2GB，3TB [前4位（3 2 1 0） 剩余大小单位  0 KB，1MB，2GB，3TB]
	unsigned char ucReserve[3];
}RV_DISK_PARTION_INFO;
typedef struct
{
	unsigned char ucDiskNo;				//disk No. max 255 [盘符,第几个硬盘 最多255个]
	unsigned char ucCurrentUse;			//if currently using work disk [是否当前使用工作盘]
	unsigned char ucLocalStorage;		//local store or remote store media, 0:local, 1:remote [本地存储还是远程存储介质 0本地 1远程]
	unsigned char ucDiskType;			//disk media type,0:sata disk, 1:U disk, 3:sd card, 4:removable disk, 5:dvd CD [硬盘介质类型 0 sata硬盘 1，U盘，3 sd卡，4，移动硬盘，5，dvd光盘]
	unsigned char ucErrorFlag;			//flag work disk error [工作盘错误标志]
	unsigned char ucPartMethod;			//supported partion mode [支持分区模式]
										//bit0: if support partion 0 not support 1 support [第0位表示是否支持分区 0 不支持 1支持]
										//next seven bits flag supported partion type [后七位 按位标识支持分区方式] 
										//bit1: partion by percent 0 not support 1 support [第1位 按照百分比分区 0 不支持 1支持]
										//bit2: partion by space MB 0 not support 1 support [第2位 按照容量分区 MB  0 不支持 1支持]
										//bit3:	partion by space GB 0 not support 1 support [第3位 按照容量分区 GB  0 不支持 1支持]
										//bit4: partion by space TB 0 not support 1 support [第4位 按照容量分区 TB 0 不支持 1支持]
	unsigned char ucSupportPartionMax;  //supported max partion number of disk [支持硬盘最大分区个数]
	unsigned char ucSupportFileSystem;  //supported file systems, 0:WFS, 1:FAT32, 2:EXT3 [支持的文件系统0 WFS 1 FAT32 2 EXT3]
	unsigned int uiTotalSpace;			//< total space, it's unit reference to ucSpaceType introduction [< 总容量，其单位参考ucSpaceType说明]
	unsigned int uiRemainSpace;			//< left space, it's unit reference to ucSpaceType introduction [< 剩余容量，其单位参考ucSpaceType说明]
	unsigned char ucSpaceType;			//identify disk space unit, convenient to more correct statistic [标识硬盘容量单位，方便比较准确的统计]
										//the next 4 bits (7 6 5 4) total space unit 0 KB，1MB，2GB，3TB [后4位（7  6 5 4 ） 总大小单位  0 KB，1MB，2GB，3TB]
										//the first 4 bits (3 2 1 0) left space unit 0 KB，1MB，2GB，3TB [前4位（3 2 1 0） 剩余大小单位  0 KB，1MB，2GB，3TB]
	unsigned char ucAttr;				//0 read-write(default), 1:read-only, 2:redundancy back-up [0 可读写 （默认），1只读， 2 冗余备份]
	unsigned char ucRes1[2];			//reserved [保留]
	RV_DISK_PARTION_INFO szPartion[4];
	unsigned char ucRes2[64];			//reserved [保留]
}RV_DISK_INFO;
#define RV_MAX_DISK_NUM	16
typedef struct
{
	DWORD dwSize;
	DWORD dwCount;
	RV_DISK_INFO stDiskInfo[RV_MAX_DISK_NUM];
}RV_DISKS;
//disk operation [硬盘操作]
typedef struct
{
	unsigned char ucDiskNo;         //disk No. max 255 [盘符,第几个硬盘 最多255个]
	unsigned char ucCtrlType;       //0:read-write(default), 1:read-only, 2:redundancy back-up, 3:format [0 可读写 （默认），1只读， 2 冗余备份 ，3 格式化] 
									//4:sector error detect and restore [4 扇区检测错误恢复]
									//5:repartion, data bellow is valid after disk repartion [5重新分区，重新分区后面数据才有效]
	unsigned char ucRes[2];  

	/////valid data after repartion [重新分区有效数据]----------------------
	unsigned char ucFSType;		//0:WFS file system, max support 2 partions, and the partion is restrict to 3 types as bellow [0 WFS文件系统  现有最大支持2分区，且分区又约束如下三种方式]
								//if WFS2 partion, default is that, the first partion is for snapshot, and the second is for recording [WFS2分区的话，默认第1分区为快照分区，第2分区为录像分区]
								//if it is only one partion under WFS file system, it is decided by ucPartType [如果是WFS 1分区的话，ucPartType标示录像分区和快照（存储图片）]
								//now the next one record, device can only save one type od media [此时后者录像，设备只能进行一种媒体的存储]
								//WFS file system is restrict to seperate 2 partion by percent [WFS文件系统约束只作百分比2分区模式]
								//1 FAT32
								//2 EXT3
	unsigned char ucPartType;	//this is only used by WFS file system, and used when only one partion, 0:record partion, 1:snapshot partion [WFS文件系统分区专用 只有一个分区的时候才使用 0 录像分区  1快照分区]
								//when it is seperate to 2 partions, default is that, the first is snapshot partion, the second is record partion, this value is invalid [WFS  两分区时候，默认第1分区为快照分区，第2分区为录像分区，此值无效]
	unsigned char ucPartNum;	//partion number [分区个数]
	unsigned char ucPartMethod;	//disk partion method, 0:percent, 1:KB, 2:MB, 3:GB, 4:TB [硬盘分区方式， 0 百分比，1 KB 2MB 3 GB 4 TB]
	unsigned int uiPartSpace[4];//every partion used spaces by partion method [按照分区方式，依次分区所使用的容量]
								//if by percent, eg. 50%-50% 2 partions [如果按照百分比，例如 50%-50% 2分区， ]
								//inner fill : 50，50, 0, 0；ucPartCtrlType== 2 ，ucPartNo ==2 [内部填充50，50, 0, 0；ucPartCtrlType== 2 ，ucPartNo ==2]
								//if fill by space MB partion method, eg. 1G disk, 200MB-300MB-100MB-400MB [如果按照容量MB分区方式，例如1G的硬盘，200MB-300MB-100MB-400MB，]
								//fill : 200，300，100，400；ucPartCtrlType== 2 ，ucPartNo ==4 [那么依次填充 200，300，100，400；ucPartCtrlType== 2 ，ucPartNo ==4]
	unsigned int uiRes[6];  
}RV_CTRL_DISK_INFO;
//disk partion , format and error correct operation [硬盘分区进行格式化以及修复操作]
typedef struct
{
	unsigned char ucDiskNo;				//disk No. max 255 [盘符,第几个硬盘 最多255个]
	unsigned char ucPartCtrlType;		//0:format, 1 partion sector detect error correct [0 格式化，1分区扇区检测修复]
	unsigned char ucPartNo;				//ucPartCtrlType==0,1 do format, sector detect restore with the ucPartNo partion [ucPartCtrlType==0、1，对第ucPartNo个分区进行格式化、扇区检测修复；]
	unsigned char ucRes;	
	unsigned int uiRes[7];				//reserved [保留]
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
//	channel configure [通道配置]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int enable;		//enable [使能]
	int startHour;	//start time : hour [开始时间:小时]
	int	startMinute;//start time : minute [开始时间:分钟]
	int	startSecond;//start time : second [开始时间:秒钟]
	int	endHour;	//end time : hour [结束时间:小时]
	int	endMinute;	//end time : minute [结束时间:分钟]
	int	endSecond;	//end time : second [结束时间:秒钟]
}RV_TIMESECTION;
//////////////////////////////////////////////////////////////////////
//	network configure [网络配置]
//////////////////////////////////////////////////////////////////////
#define RV_NAME_PASSWORD_LEN		64	
#define RV_EMAIL_ADDR_LEN  32
#define RV_N_MIN_TSECT 2
typedef struct
{
	char HostName[RV_NAME_PASSWORD_LEN];	//device name [设备名]	
	int HttpPort;							//HTTP server port [HTTP服务端口]	
	int TCPPort;							//TCP listen port [TCP侦听端口]		
	int SSLPort;							//SSL listen port [SSL侦听端口]	
	int UDPPort;							//UDP listen port [UDP侦听端口]	
	int MaxConn;							//max connection number [最大连接数]	
	unsigned char ucMonMode;				//watch protocal {"TCP","UDP","MCAST",…}  0|1|2 [监视协议 {"TCP","UDP","MCAST",…}  0|1|2]	
	unsigned char ucUseTransPlan;			//if enable network transport plot [是否启用网络传输策略]
	unsigned char ucTransPlan;				//transport plot 2 auto 1 fluency first 0 quality first, default 1 [传输策略 2自动 1流畅性优先 0质量优先，默认1]
	unsigned char ucHighSpeedDownload;		//if enable high speed download [是否启用高速录像下载测率]
	int iRes[3];
}RV_CONFIG_NET_APP;
typedef struct
{
	char strEthName[16];			//different net card name, show by string "eth0", this can not be changed [不同网卡名称，以字符串标示"eth0"; 此不可以改]
	char strMacAddr[32];			//xx.xx.xx.xx.xx.xx (string format) [xx.xx.xx.xx.xx.xx(字符串形式)]
	char HostIP[20];				//host's IP [主机IP]
	char Submask[20];				//sub net mask [子网掩码]
	char Gateway[20];				//gateway IP [网关IP]
	unsigned char  ucTranMedia;		//0:wired net, 1:wireless net [0：有线，1：无线]
	unsigned char  ucDefaultEth;	//if it is default net card, 1:default, 0:not default [是否作为默认的网卡, 1：默认 0：非默认]
	unsigned char  ucValid;			//by bit, bit0 1:valid, 0:invalid [按位表示，第一位：1：有效 0：无效；]
									//bit1 0:DHCP closed, 1:DHCP enable [第二位：0：DHCP关闭 1：DHCP使能；]
									//bit2 0:not support DHCP, 1:support DHCP [第三位：0：不支持DHCP 1：支持DHCP]
	unsigned char  ucReserve;	
	unsigned char  ucRes[16];		//reserved [保留字]
}RV_CONFIG_NET_ETH;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_NET_APP stNetApp;
	RV_CONFIG_NET_ETH stNetEth;
}RV_CONFIG_NET_COMM;
//server struct definition [服务器结构定义]
typedef struct
{	
	char ServerName[RV_NAME_PASSWORD_LEN];	//service name, ip domain format or xxx.xxx.xxx.xxx format, max 64 bytes [!服务名,ip域名形式或者是xxx.xxx.xxx.xxx形式，最长64字节]
	int iReserved;							//origin IP address, save this field for extend [!原始为IP地址，为了扩展保留此字段；]	
	int Port;								//port [!端口号]
	char UserName[RV_NAME_PASSWORD_LEN];	//uer name [!用户名]	
	char Password[RV_NAME_PASSWORD_LEN];	//password [!密码]	
	int  Anonymity;							//if anonimity [!是否匿名登录]
}RV_REMOTE_SERVER;
typedef struct
{
	int Enable;								//enale [!是否开启 0 不开启，1开启]	
	int iKey;								//type name, if it is ddns, corresponding ddnskey, can extend server type for using [!类型名称，如果是ddns，对应ddnskey;可以扩展服务类型使用]
	RV_REMOTE_SERVER Server;				//server information [!服务器 信息]
}RV_IPADDR_SERVER;
#define  RV_MAX_EMAIL_TITLE_LEN 64
#define  RV_MAX_EMAIL_RECIEVERS  5
//email configure [EMAIL设置]
typedef struct
{
	//can fill with ip, and can fill with domain [可以填ip,也可以填域名]
	RV_IPADDR_SERVER Server;
	int bUseSSL;		
	char SendAddr[RV_EMAIL_ADDR_LEN];							//sender address [发送地址]		
	char Recievers[RV_MAX_EMAIL_RECIEVERS][RV_EMAIL_ADDR_LEN];	//receiver address [接收人地址]		
	char Title[RV_MAX_EMAIL_TITLE_LEN];							//emial title [邮件主题]
	RV_TIMESECTION Schedule[RV_N_MIN_TSECT];					//emial valid time [email有效时间]	
}RV_CONFIG_EMAIL;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_EMAIL stEmail;
}RV_EMAIL;
//DNS
typedef struct
{
	char strPrimaryIp[16]; //xxx. xxx. xxx. xxx (string format) [xxx. xxx. xxx. xxx (字符串形式)]
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
	int Enable;		//enable [是否开启]	
	int WebPort;	//web port [web端口]	
	int TCPPort;	//tcp port [tcp端口]	
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
	int iEnable;		//0:disable, 1:enable [0 不使能，1 使能]
	char strip[32];
	char strUser[64];
	char strPwd[64];
}RV_PPPOE_IP_SRV;		//remarks : only enable, ip(dial ip), user name, password are valid when dial to get configure [注明：其中，拨号获取设置的时候只有使能，ip（拨号ip），用户名密码有效；]
						//when setting, only enable, user name, password are valid [设置的时候，只有使能，用户名密码有效；]
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
//	code configure [编码配置]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int		iCompression;			/*!< compression mode [压缩模式] */	
	int		iResolution;			/*!< resolve, reference to enum capture_size_t(DVRAPI.H) [分辨率 参照枚举capture_size_t(DVRAPI.H)] */	
	int		iBitRateControl;		/*!< bit-stream control, reference to enum capture_brc_t(DVRAPI.H) [码流控制 参照枚举capture_brc_t(DVRAPI.H)] */	
	int		iQuality;				/*!< picture quality, level 1~6 (corresponding worst,bad,common,good,better,best) [码流的画质 档次1-6（对应的是最差，差，一般，好，很好，最好]*/	
	int		nFPS;					/*!< frame rate (0~30 ), (-n~0) means how many seconds per frame, NTSC and PAL are the same [帧率值（0~30）（-n~0）负数表示多秒一帧，NTSC/PAL不区分] */	
	int		nBitRate;				/*!< 0-4096k */
	int		iGOP;					/*!< descript time slice between two I frame, unit is second, 2-12 [描述两个I帧之间的间隔时间s，2-12] */
}RV_VIDEO_FORMAT;
typedef struct
{
	int		nBitRate;				/*!< bit-stream kbps [码流kbps]*/	
	int		nFrequency;				/*!< sample rate [采样频率]*/	
	//int		nMaxVolume;			/*!< max volume value [最大音量阈值]*/
	unsigned char	ucLAudioVolumn;	//left audio channel volumn [左声道音量]
	unsigned char	ucRAudioVolumn;	//right audio channel volumn [右声道音量]
	unsigned char	ucRes[2];		//reserved [保留]
}RV_AUDIO_FORMAT_T;
//media format [媒体格式]
typedef struct
{
	RV_VIDEO_FORMAT vfFormat;		/*!< video format definition [视频格式定义] */			
	RV_AUDIO_FORMAT_T afFormat;		/*!< audeo format definition [音频格式定义] */
	int	bVideoEnable;				/*!< open video code [开启视频编码] */
	int	bAudioEnable;				/*!< open audio code [开启音频编码] */	
}RV_MEDIA_FORMAT;
//code configure [编码设置]
typedef struct
{
	int iSteamIndex;				/*!<bit-stream format [码流格式] 
										main bit-stream, reference to enum ENCODE_TYPE_BY_RECORD, default to only have one main stream, fill it to 0 [主码流 参考枚举参考ENCODE_TYPE_BY_RECORD ，现有产品默认只有一个主码流，填充为0；]
										assist bit-stream, reference to enum ENCODE_TYPE_BY_SUBSTREAM, max 4 assist bit-stream, max support one assist bit-stream now, fill it to 0 [副码流 参考 ENCODE_TYPE_BY_SUBSTREAM，最多4种子码流，现在产品最多支持一种副码流，填充为0；]
										snapshot bit-stream, reference to enum ENCODE_TYPE_BY_SUBSTREAM, config snapshot from max 4 assist bit-stream [捉图码流 参考 ENCODE_TYPE_BY_SUBSTREAM，最多从4种码流中进行捉图配置]
									*/	
	RV_MEDIA_FORMAT dstFmt;			/*!<bit-stream format [码流格式] */	
}RV_NET_ENCODE;
//
#define RV_N_COLOR_SECTION 2
//video color struct [视频颜色结构]
typedef struct
{
	int	nBrightness;				/*!< brightness 0-100 [亮度	0-100] */
	int	nContrast;					/*!< conrast 0-100 [对比度	0-100] */
	int	nSaturation;				/*!< saturation 0-100 [饱和度	0-100] */
	int	nHue;						/*!< hue 0-100 [色度	0-100] */
	int	mGain;						/*!< gain, 0-100, bit6 means auto gain [增益	0-100 第７位置1表示自动增益]　*/		
	int	mWhitebalance;				/*!< auto white level control, bit7 means open auto control, 0x0,0x1,0x2 means low,middle,high level [自动白电平控制，bit7置位表示开启自动控制.0x0,0x1,0x2分别代表低,中,高等级]*/
}RV_VIDEOCOLOR_PARAM; 
typedef struct
{
	RV_TIMESECTION		TimeSection;		/*!< time slice [时间段] */
	RV_VIDEOCOLOR_PARAM	dstColor;			/*!< color definition [颜色定义] */
	int					iEnable;            /*!< enable, there is no definition in sdk now, default is enable [使能定义 现有sdk暂时没有此部分，默认使能]*/
}RV_VIDEOCOLOR;
typedef struct
{
	RV_VIDEOCOLOR dstVideoColor[RV_N_COLOR_SECTION];
}RV_CONFIG_VIDEOCOLOR;
//query video area shelter information [查询视频区域遮挡属性信息]
typedef void *						VD_HANDLE;
typedef int							VD_BOOL;
typedef unsigned int				VD_COLORREF;//0x00bbggrr
typedef unsigned int				VD_COLORDEV;//0x????????
//video object struct [视频物件结构]
typedef struct
{
	VD_COLORREF rgbaFrontground;		/*!< object's front RGB and transparency [物件的前景RGB，和透明度] */	
	VD_COLORREF rgbaBackground;			/*!< object's background RGB and transparency [物件的后景RGB，和透明度]*/	
	RV_VD_RECT	rcRelativePos;			/*!< object's edge distance / total length * 8191 [物件边距与整长的比例*8191] */	
	VD_BOOL	bPreviewBlend;				/*!< overprint in preview [预览叠加] */	
	VD_BOOL	bEncodeBlend;				/*!< overprint in code [编码叠加] */
}RV_VIDEO_WIDGET;
//area shelter [区域遮挡]
#define RV_COVERNUM 8
typedef struct
{
	unsigned int	uiCoverNum;			//how many overprint areas in current channel [当前该通道有几个叠加的区域]
	RV_VIDEO_WIDGET	dstCovers[RV_COVERNUM];
}RV_NET_VIDEO_COVER;
//
typedef struct  
{
	unsigned int  cSize;		//字体大小，1表示标准倍数，2表示2倍大小  该值取值范围在1到ucZoomAbility之间
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
	unsigned short 	iChannel;		//channel, start with 0 [通道 从0开始]
	unsigned short	iIndex;			//preset or locus index , start with 1 [预置点或者轨迹下标号 从1开始]
}RV_PTZ_CHANNEL;

#define NAME_LEN			32		
#define PTZ_PRESETNUM		64
#define PTZ_CHANNELS		8

typedef struct 
{
	unsigned char 	ucChannel;					//channel [通道]
	unsigned char 	ucPresetID;					//preset No. [预置点号]
	unsigned char	iSpeed;						//preset speed speed 1~15 level [预置点速度 速度1~15等级]
	unsigned char	iDWellTime;					//preset delay time 1~255 [预置点停留时间 1~255s]
	unsigned char	szPresetName[NAME_LEN];		//preset name [预置点名称]
}RV_PRESET_INFO;

typedef struct
{
	unsigned char 	ucChannel;					//channel [通道]
	unsigned char	ucTourIndex;				//tour No. [巡航号]
	unsigned char	ucPresetCnt;				//number of presets in one tour [一个巡航组中的预置点数 0~128]
	unsigned char	uRes;						//reserved [保留]
	unsigned char	uiPresetNum[PTZ_PRESETNUM];	//preset No. in tour [巡航组中的预置点号]
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
//NTP struct [NTP结构体]
typedef struct
{	
	RV_IPADDR_SERVER szNtpServer;	//server [服务器]	
	int UpdatePeriod;				//update time slice [更新周期]	
	int TimeZone;					//time zone [时区]
}RV_CONFIG_NTP;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_NTP stNtp;
}RV_NTP;

//////////////////////////////////////////////////////////////////////////
//	struct of output mode [输出模式结构体]
typedef struct
{
	unsigned char ucOSDShow;//bit0:if show time, bit1:if show channel name [0位 是否显示时间 1位 是否显示通道名]
	unsigned char ucRes[15];//reserved [保留]
}RV_OUT_MODE_OSD_CFG;
typedef struct
{
	DWORD dwSize;
	RV_OUT_MODE_OSD_CFG stOSD;
}RV_OUT_MODE_CFG;

//////////////////////////////////////////////////////////////////////////
//	ftp struct [ftp结构体]
typedef struct
{
	RV_IPADDR_SERVER	stServer;				//ftp server [ftp服务器]
	char            cDirName[RV_FTP_MAX_PATH];  //FTP folder path, 240[FTP目录路径 240]
	int             iReserved;                   
	int             iFileLen;                   //file length, unit is M [文件长度 M为单位]
	int             iInterval;                  //time slice between files, unit is second [相邻文件时间间隔    秒为单位]
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
	RV_FTP_SERVER stFtpRecord;	//record [录像]
	RV_FTP_SERVER stFtpPicture;	//picture [图片]
}RV_FTP;

/////////////////////////////////////////////////////////////////////////
//	rtsp struct [rtsp结构体]
typedef struct
{
	unsigned short    usEnable;       //enable [使能] 
	unsigned short    usListernPort;  //RTSP listen port [RTSP侦听端口]
	unsigned short    usUdpStartPort; //UDP start port [UDP起始端口]
	unsigned short    usUdpPortNum;   //UDP port number [UDP端口数量]
	unsigned short    usReserve[36];  //reserved [保留]
}RV_CONFIG_RTSP_SET;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_RTSP_SET stRTSP;
}RV_RTSP;

//////////////////////////////////////////////////////////////////////
//	alarm struct of intelligent red [能红色报警结构]
//////////////////////////////////////////////////////////////////////
//area shelter [区域遮挡]
#define RV_REDREGIONNUM 8
typedef struct
{
	long lX;
	long lY;
}RV_POINT;
typedef struct
{
	int				iRectNum;							//how many areas in current channel [当前该通道有几个区域]
	RV_POINT		szPointArray[RV_REDREGIONNUM][4];
}RV_REDON_RECT;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
	RV_REDON_RECT			stRedonRect;
} RV_INTERED_ALARM; 
typedef struct
{
	DWORD dwSize;		
	RV_INTERED_ALARM		struInteRedAlarm[RV_MAX_CHANNUM];
}RV_INTERED_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//record control [录像控制]
typedef struct
{
	unsigned char ucChannelCount;	//channel number [通道数目]
	unsigned char ucRes[3];
	unsigned char ucState[128];		//0~127 flag channel 1~128 (0:not record, 1:manual record, 2:auto record) [第0个到第127个依次为第1到第128通道（0: 为不录像;1: 手动录像;2: 为自动录像）]
}RV_RECCTL; 
typedef struct
{
	DWORD dwSize;  
	RV_RECCTL struRecCtl;
}RV_RECCTL_CFG;

/* configure struct of serial port, more than 16 channnels [串口配置结构体 超过16通道] */
typedef struct
{
	DWORD			dwSize;
	//protocal of decoder [解码器协议]
	DWORD			dwDecProListNum;										//number of protocal [协议个数]
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN];	//protocal list [协议名列表]
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM_EX];						//current attributes of every decoder [各解码器当前属性]

	DWORD			dw232FuncNameNum;										//number of 232 function [232功能个数]
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];			//function name list [功能名列表]
	RV_RS232_CFG	st232[RV_MAX_232_NUM];									//current attrributes of every 232 serial port [各232串口当前属性]
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
//audio config [音频配置]
typedef struct
{
	unsigned int uiTalkAudioSourceType; //audio source method, 0:liner input, 1:mic [声音源方式，0为线性输入，1为mic]
	unsigned int uiOutSilence;			//mute, 0:not mute, 1-mute [静音 0--非静音 1--静音]
	unsigned int uiOutLAudioVolumn;		//left audio channel volume [左声道音量]
	unsigned int uiOutRAudioVolumn;		//right audio channel volume, left and right channel' value are the same for single audio channel device [右声道音量，单声道的设备左右值一样]
	unsigned int uiReserverd[32];		//[保留]
}RV_DEV_AUDIO;
typedef struct  
{
	DWORD			dwSize;
	RV_DEV_AUDIO	stDevAudio;		
}RV_DEV_AUDIO_CFG;

//////////////////////////////////////////////////////////////////////////
// tour confgure for digital channel [数字通道轮训配置]
typedef struct
{
	BOOL			BEnable;                //enable [使能开关]
	char			cChName[32];            //name of this configure, for identify [本配置名称,便于识别]
	char			cDeviceIP[64];          //ip of device for connection [待连接设备的ip地址]
	LONG			iDevicePort;			//port of device for connection [待连接设备的端口号]
	char			cDeviceUserName[32];	//user name [用户名]
	char			cDevicePassword[32];	//password [密码]    
	LONG			iDevType;               //device type, by enum, protocal type, 0:tcp connection, 3:rtsp+udp, 4:vs300 [设备类型，按枚举表示，即协议类型,0表示tcp直连，3 rtsp+udp 4 vs300.]
	LONG			iRemoteChannelNo;       //remote channel index, start with 0 [远程通道号,从0开始算起]
	LONG			iStreamType;            //which bit-stream, 0:main, 1:assist [要连接的码流类行?0:主码流， 1:辅码流]
	LONG			iRemotePtzPreset;		//remote preset [远程预置点]
	LONG			iRemotePtzPresetEnable;	//if set preset on connected [是否一连接上就设置远程预置点]   
	LONG			reserverd[5];           //reserved [保留字节]	
}RV_REMOTE_CH_CFG;
typedef struct
{
	BOOL			BEnable;			//enable [使能开关]
	LONG			iDeviceChannelType; //channel type, 0:digital channel, 1:analog channel, default is digital channel, can't switch now [通道类型，0表示数字通道，1表示模拟通道，默认为数字通道,暂时不可以切换]
	LONG			iMode;				//0:single connection, 1:multi connection [0 单连接 1 多连接]
	unsigned long   uiTourTime;			//multi connection tour time [多连接轮巡时间]
	unsigned long   uiNotTourCfgIndex;	//channel configure on single connection, position in the tour list [单连接时的采用的通道配置,在轮巡列表中的位置]
	LONG			iDecodePolicy;		//decode plot (-2:most real-time, -1:real-time, 0:default, 1:fluency, 2:most fluency) mayby extend to self definition [解码策略     (-2, 最实时 -1 实时 0 默认情况 1 流畅 2,    最流畅 ) 以后可能扩展到自定义具体的延时时间]
	LONG			iAVEnable;			//0:only decode video, 1:only decode audio, 2:decode audio and video [0,只解视频 1，只解音频 ，2 解音视频 ]
	LONG			iReserverd[5];      //reserved [保留字节]
}RV_LOCAL_CH_CFG;
typedef struct
{
	RV_LOCAL_CH_CFG		stLocalChCfg;			//channel configure [通道配置]
	DWORD				dwRemoteChanCount;		//remote channel number [远程通道数目]
	RV_REMOTE_CH_CFG	stRemoteChanCfg[64];	//remote channel config [远程通道配置]
}RV_LOCAL_CH;
typedef struct
{
	DWORD dwSize;
	RV_LOCAL_CH stLocalChan[64];
}RV_DIGI_CH_TOUR_CFG;

//////////////////////////////////////////////////////////////////////////
// key-board control configure [控制键盘配置]
typedef struct 
{
	unsigned char Com_Version[8];	/*!< version number [版本号] */
	unsigned char Function;			/*!< serial port function, reference to enum KBDFunc [串口功能 参照枚举KBDFunc]*/
	unsigned char DataBits;			/*!< data bit, values are 5,6,7,8 [数据位 取值为5,6,7,8] */
	unsigned char StopBits;			/*!< stop bit, reference to enum comm_stopbits_t(DVRAPI.H) [停止位 参照comm_stopbits_t(DVRAPI.H)] */
	unsigned char Parity;			/*!< verify bit, reference to enum comm_parity_t(DVRAPI.H) [校验位 参照comm_parity_t(DVRAPI.H)] */
	unsigned int  BaudBase;			/*!< baudrate {300,600,1200,2400,4800,9600,19200,38400,57600,115200} [波特率 {300,600,1200,2400,4800,9600,19200,38400,57600,115200}]　*/
}RV_KBD;
typedef struct
{
	DWORD dwSize;
	RV_KBD stKBD;
}RV_KBD_CFG;
//////////////////////////////////////////////////////////////////////////
// configure of matrix (XINGHUO Corp.) [矩阵(星火)配置]
typedef struct
{
	unsigned int uiMap[16];//channel of visiondigi device corresponding channel of matrix input, 0xffffffff means not use matrix input of XINGHUO, eg. uiMap[0] = 100, means channel 1 use the channel 101 of XINGHUO matrix [威乾设备的通道对应的矩阵输入的通道号，0xffffffff表示不使用星火的矩阵输入，比如uiMap[0] = 100，表示第1通道使用星火的第101路输入]
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
	int iChannel;//通道号
	int iVideoEnable;
}RV_MATRIX_INPUT;

typedef struct  
{
	DWORD			dwSize;
	RV_MATRIX_INPUT	stMatrixInput[16];
}RV_MATRIX_CFG_EX;

//added by zhubo,CID-PID对应
typedef struct
{

int Cid0;//请求通道的老的CID，没有时置-1
int Pid0;//请求通道的老的PID，没有时置-1
int iRes1[2];

int Cid1;//请求通道的新的CID
int Pid1;//请求通道的新的PID，请求时置-1
int iRes2[2];
}RV_MATRIX_PIDCID;

//SVAC配置
typedef struct  
{
	unsigned char	ucEnable;		//使能
	unsigned char	ucLevel;		//等级, 保留
	unsigned char	ucRes[2];		//保留
	RV_RECT			stArea;			//区域坐标
}RV_SVAC_FOCUS_AREA, *pRV_SVAC_FOCUS_AREA;

typedef struct
{
	unsigned char	ucChannel;				//通道
	unsigned char	ucRes[3];				//保留
	RV_SVAC_FOCUS_AREA dstFocusAreas[8];	//扩展到8个，暂时可以做少一点，取前4个处理
}RV_NET_SVAC_FOCUS_AREA, *pRV_NET_SVAC_FOCUS_AREA;

typedef struct  
{
	DWORD dwSize;
	RV_NET_SVAC_FOCUS_AREA	stSVACFocusArea[RV_MAX_CHANNUM];
}RV_NET_SVAC_AREA;




/******************************************************************************
* end of configure struct [end of 配置结构体]
*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif










































