
#ifndef VD_CLIENT_SYSABLE_H
#define VD_CLIENT_SYSABLE_H


//////////////////////////////////////////////////////////////////////////
//	type for query [查询类型]
typedef enum
{
	ABILITY_WATERMARK_CFG = 17,			//ability of configure watermark [水印配置能力]
	ABILITY_WIRELESS_CFG = 18,			//ability of configure wireless [wireless配置能力]
	ABILITY_DEVALL_INFO = 26,			//abblities of device [设备的能力列表]
	ABILITY_CARD_QUERY = 0x0100,		//ability of query by card No. [卡号查询能力]
	ABILITY_MULTIPLAY = 0x0101,			//ability of multi-view preview [多画面预览能力]
	ABILITY_INFRARED = 0X0121,			//ability of wireless alarm [无线报警能力]
	ABILITY_TRIGGER_MODE = 0x0131,
	ABILITY_SAVIA_COUNT = 33,			//number of SAVIA [SAVIA数目]
	ABILITY_STR_LEN_EN = 35,			//length of string (not 98 serial device) [字符串长度(非98设备)]
	ABBI_TLV = 40,				//using new network protocal ? [是否使用新网络协议]
	ABBI_DECODER,				//ability of decoder [解码器能力]
	ABBI_AUTOREGISTER,			//ability of auto-register [主动注册能力]
	ABBI_SAVIA,					//ability of SAVIA [SAVIA能力]
	ABBI_AUDIOIN,				//ability of audio input [音频输入]
	ABBI_PTZTOUR,				//ability of PTZ soft tour [云台软巡航能力]
	ABBI_TALK,					//ability of talk [对讲能力]
	ABBI_MVIEW,					//ability of combining and spliting views for multi-view preview [多画面预览画面分割组合能力]
	ABBI_SNAP,					//ability of snapshot [抓拍能力]
	ABBI_DEVID,					//device ID [设备ID]
	ABBI_VERSION,				//software version [软件版本]
	ABBI_AUTH_LIST,				//previleges of the current logined user [当前登录用户权限]
	ABBI_SYS_ATTR_EX,			//device attributes [设备属性]
	ABBI_ISTLVPROTOCAL,			//using new network protocal ? [是否使用新网络协议]
	ABBI_IVIDEO,				//ability of platform connection [平台接入能力]
	ABBI_ENCODE,				//ability of code [编码能力]
	ABBI_TIME,					//ability of time [时间能力]
	ABBI_FTP,					//ability of ftp [ftp能力]
	ABBI_WHITEBLACK,			//ability of black and white ip list [黑白名单能力]
	ABBI_DEVTYPE,				//device type [设备类型]
	ABBI_RTSP,					//ability of RTSP [RTSP能力]
	ABBI_AUDIOVALUE,			//ability of audio volumn adjusting [音频音量调节]
	ABBI_RECORD,				//ability of recording [录像能力]
	ABBI_KBD,					//ability of key-board for control [控制键盘能力]
	ABBI_MATRIX_XINGHUO,		//ability of matrix(for XINGHUO Corp.) [矩阵(星火)能力]
	ABBI_OSD_ZOOM,				//ability of OSD FONT ZOOM [OSD字体大小]
} RV_SYS_ABILITY;

//////////////////////////////////////////////////////////////////////////
//	function list supported by device [设备支持功能列表]
enum 
{
	EN_FTP = 0,							//FTP by bit, 1:send record file 2:send picture file [FTP 按位，1：传送录像文件 2：传送抓图文件]
	EN_SMTP,							//SMTP by bit, 1:send text e-mail for alarm 2:send picture e-mail for alarm [SMTP 按位，1：报警传送文本邮件 2：报警传送图片]
	EN_NTP,								//NTP by bit, 1:adjust system time [NTP	按位：1：调整系统时间]
	EN_AUTO_MAINTAIN,					//auto mantance by bit, 1:reboot 2:shutdown 3:delete files [自动维护 按位：1：重启 2：关闭 3:删除文件]
	EN_VIDEO_COVER,						//area shelter by bit, 1:multi-area shelter [区域遮挡 按位：1：多区域遮挡]
	EN_AUTO_REGISTER,					//auto register by bit, 1:sdk login device by initiative after registration [主动注册	按位：1：注册后sdk主动登陆]
	EN_DHCP,							//DHCP by bit, 1:DHCP [DHCP	按位：1：DHCP]
	EN_UPNP,							//UPNP by bit, 1:UPNP [UPNP	按位：1：UPNP]
	EN_COMM_SNIFFER,					//serial port capture package by bit, 1:CommATM [串口抓包 按位：1:CommATM]
	EN_NET_SNIFFER,						//network capture package by bit, 1:NetSniffer [网络抓包 按位： 1：NetSniffer]
	EN_BURN,							//function of imprinting by bit, 1:query status of recording [刻录功能 按位：1：查询刻录状态]
	EN_VIDEO_MATRIX,					//video matrix by bit, 1:surport video matrix ? [视频矩阵 按位：1：是否支持视频矩阵]
	EN_AUDIO_DETECT,					//audio detect by bit, 1:support audio detect ? [音频检测 按位：1：是否支持音频检测]
	EN_STORAGE_STATION,					//store position by bit, 1:Ftp server(Ips) 2:Usb storage 3:NFS 4:DISK 5:SBM [存储位置 按位：1：Ftp服务器(Ips) 2：U盘 3：NFS 4：DISK 5：SBM]
	EN_IPSSEARCH,						//IPS store query by bit, 1:IPS store query [IPS存储查询 按位：1：IPS存储查询]
	EN_SNAP,							//snapshot by bit, 1:resolve 2:frame rate 3:snapshot method 4:file format of snapshot 5:quality of picture [抓图  按位：1：分辨率2：帧率3：抓图方式4：抓图文件格式5：图画质量]
	EN_DEFAULTNIC,						//query for default net card supported by bit, 1:support [支持默认网卡查询 按位 1：支持]
	EN_SHOWQUALITY,						//configure item of picture's display quality under CBR mode, 1:support  [CBR模式下显示画质配置项 按位 1:支持]
	EN_RTSP,							//RTSP [RTSP]
};

typedef struct 
{
	DWORD IsFucEnable[512];				//abbility array of function, and subscript corresponding to enum value above, and sub functions are flags by bits [功能列表能力集,下标对应上述的枚举值,按位表示子功能]
} RV_DEV_ENABLE_INFO;

//////////////////////////////////////////////////////////////////////////
//	ability struct of query by card No. [卡号查询能力结构体]
typedef struct 
{
	char		IsCardQueryEnable;
	char		iRev[3];
} RV_CARD_QUERY_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of configure wireless [wireless能力结构体]
typedef struct 
{
	char		IsWirelessEnable;
	char		iRev[3];
} RV_WIRELESS_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of configure watermark [图象水印能力结构体]
typedef struct 
{
	char		isSupportWM;	//1:support 0:not support [1 支持；0 不支持]
	char		supportWhat;	//0:text watermark 1:picture watermark 2:surport both text and picture watermark [0：文字水印；1：图片水印；2：同时支持文字水印和图片水印]
	char		reserved[2];
} RV_WATERMAKE_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of multi-view preview [多画面预览能力结构体]
typedef struct  
{
	int			nEnable;			//1:support 0:not support [1 支持；0 不支持]
	DWORD		dwMultiPlayMask;	//reserved [保留]
	char		reserved[4];
} RV_MULTIPLAY_EN;

//////////////////////////////////////////////////////////////////////////
//	number of SAVIA struct [SAVIA数目能力结构体]
typedef struct 
{
	DWORD		dwCount;
} RV_SAVIA_COUNT;

typedef struct  
{
	BOOL bSupport;			//support ? [是否支持]
	int	 nAlarmInCount;		//number of alarm in [输入个数]
	int  nAlarmOutCount;	//number of alarm out [输出个数]
	int  nRemoteAddrCount;	//number of remote-control unit [遥控器个数]
	BYTE reserved[32];
}RV_WIRELESS_ALARM_INFO;

//////////////////////////////////////////////////////////////////////////
//	ability struct of PTZ soft tour [云台软巡航能力结构体]
typedef  struct
{
	unsigned short usPresetNums ;	//max number of presets for every channel [每个通道预置点最大个数]
	unsigned short usTourNums;		//max number of tours for every channel [每个通道最大巡航轨迹个数]
    int iRes [4];					//reserved [保留]
}RV_PTZ_TOUR_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of auto-register [主动注册能力结构体]
typedef  struct
{
	unsigned short usRegServerNums ;	//number of auto-regiser server, just one now [主动注册服务器个数 现有实现为1个]
	unsigned short usNetMode;			//auto-register mode [主动注册模式]
										//support multiple network mode, every bit flags support : 1:support 0:not support [支持多种网络模式 每一位标识是否支持 0标识不支持，1标识支持]
										//bit 0 : single connection of video and commands [第0位 视频和信令单连接]
										//bit 1 : multi-connection(multi-connection of multimedia, support that device connects server to send video data forwardly) [第1位 多连接（媒体多连接，支持设备主动连接服务器发送视频）]
    int iRes [4];						//reserved [保留]
}RV_AUTO_REGISTER_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of decoder [解码器能力结构体]
typedef  struct
{
	unsigned short usDecoderNums ;  //max number of channles [解码器最大路数]
	unsigned short usNetMode;		//support multiple network mode, every bit flags support : 1:support 0:not support [支持多种网络模式 每一位标识是否支持 0标识不支持，1标识支持]
									//bit 0 : common network vs100,vs200, default setted to 1 [第0位 通用网络vs100，vs200；默认此为支持 置1]
									//bit 1 : support rtsp Client [第1位 支持rtsp Client]
									//bit 2 : support vs300  [第2位 支持vs300；]
	int iAbilityMask;				//decode abbility for every channel, max 16 channels now, so every 2 bits mark 1 channel in 32 bits [每路解码器解码能力 ，现有最大16通道，32位每2位标识一个通道]
									//00:max support to CIF, 01:max support to D1, 10:max support to 720p, 11:more [00 最大支持CIF，01 最大支持D1，10，最大支持720p, 11 更高]
	unsigned char ucDecoderType; 	//type of decoder [解码器形式]
									//0:mixed type of DVR (both contain analog channels and digital channels), 1:pure decoder(only digital channels) [0混合dvr（既有模拟也可以数字），1纯解码器（只有数字）]
	unsigned char ucModeAblity;		//bit 0 : support multi-connection tour ? [第0位 是否支持多连接轮巡的方式]
	unsigned short  usMaxChNum;		//max number of channels for every supported tour when support multi-connection tour [支持多连接方式时,每路支持的轮巡列表的通道的最大数目]
	int iRes [3];					//reserved [保留]
}RV_DECODE_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of snapshot [抓拍能力结构体]
typedef struct
{	
    unsigned long type_mask;			//flag by bits : 0-trigger to snapshot 1-timer to snapshot 2-alarm to snapshot [按位表示 0-触发抓拍, 1-定时抓拍, 2-告警抓拍]
	unsigned long uiSnapMaxCount;		//max number of snapshot per second supported [最大支持抓拍张数]
	unsigned long uiCountsPerSecond;	/*how many pictures per second, flag by bits	[1s几张图片，按位表示]
										bit0:1 picture per second [第0位 1s1张]
										bit1:2 picture per second [第1位 1s2张]
										bit2:3 picture per second [第2位 1s3张]
										bit3:4 picture per second [第3位 1s4张]
										bit4:5 picture per second [第4位 1s5张]
										*/					
	unsigned long uiMaxSeconds;			/*max number of seconds per picture supported [最大支持几秒1张]*/
	unsigned long uiRes[28];
}RV_ABILITY_SNAP_T;

//////////////////////////////////////////////////////////////////////////
//	ability struct of intelligent [智能模块能力结构体]
typedef struct
{
	unsigned char ucSaviaNums ;		//number of savia [savia数目]
	unsigned char ucSurportAl;		//surpported arithmetics [支持的算法]
	unsigned char ucRes[22];		//reserved [保留]
}RV_SAVIA_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of talk(audio in and audio out) [对讲（对讲音频输入+音频输出）能力结构体]
typedef struct
{
	unsigned char ucSurportTalkIn ;  	//audio input for talk (device has individual audio capture) [对讲音频输入（设备存在单独的音频采集） 1:支持：0：不支持]
	unsigned char ucTalkInMask;     	//code type of audio input supported, flag by bits [设备音频输入编码格式类型  按位标识是否支持编码格式]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [第0位 是否支持g711a， 第1位 pcm8k16b 第2位 g711u等]
	unsigned char ucSurportTalkOut;		//audio output for talk, 1:support,0:not support [对讲音频输出   1:支持：0：不支持]
	unsigned char ucTalkOutMask;     	//decode type of audio supported, flag by bits [设备音频解码格式类型  按位标识是否支持解码格式]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [第0位 是否支持g711a， 第1位 pcm8k16b  第2位 g711u等]
}RV_TALK_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of audio input [音频输入能力结构体]
typedef struct
{
	unsigned long uiAudio ;				//bit 0~31 : flag that there are audio input in channel 1~32, 1:input 0:no input [0~31为依次表示通道1~通道32有音频输入 1标识有，0标识]
	unsigned long uiAudioMask ;  		//code type of accompanying sound input, flag by bits [设备伴音编码格式类型  按位标识是否支持编码格式]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [第0位 是否支持g711a， 第1位 pcm8k16b  第2位 g711u等]
}RV_AUDIO_IN_EN;

//////////////////////////////////////////////////////////////////////////
//	ability of combining and spliting views [画面分割组合能力结构体]
#define MAX_SPLIT_COMINE_NUMS 32
#define MAX_SPLITCOMBINE_NUMBER 32
typedef struct
{
	unsigned int iChMask;		 //channel mask, flag by bits, total 32 bits (4 byts)(max 32 types) [通道掩码，按位标识，总32位4字节,最大32种形式]
								 /*for example : 4 views, support mode (1,2,3,4channel)(1,3,4,5channel) [4画面 ，支持 模式（1，2，3，4通道）（1，3，4，5）]
								 corresponding mask is 0000 0000 0000 0000 0000 0000 0000 1111=0x0F [对应的掩码为  0000 0000 0000 0000 0000 0000 0000 1111=0x0F]
								 0000 0000 0000 0000 0000 0000 0001 1101=0x1D [0000 0000 0000 0000 0000 0000 0001 1101=0x1D]
								 if 9 views, support mode (1,2,4,5,6,7,8,9,10channel) [如果9画面 支持（1，2，4，5，6，7，8，9，10通道）]
								 corresponding mask is 0000 0000 0000 0000 0000 0011 1111 1011=0x3FB [对应的掩码为0000 0000 0000 0000 0000 0011 1111 1011=0x3FB]
								 the mask content here, need to decide by uiSplitType in  SPLIT_MODE, and there has include or exclude relation now [此处掩码内容，是需要根据 SPLIT_MODE中uiSplitType来定，现有制定是包含关系还是排除关系]
								 */
	unsigned char ucSpecialCh;	 /*special channel (restrict to be show in the first view or the biggest view) [特殊通道（约束为自动排在最前或者大窗口显示）]*/
	unsigned char ucRes[3];
}RV_SPLIT_COMBINE_CH;
typedef struct
{
	unsigned char ucSplitMode;	/*mode of multi-view preview, reference to enum split_combine_t [多画面预览模式，参考枚举split_combine_t]*/
	unsigned char ucSplitType;  /*supported split views type, every two bits corresponding one bit in iSplitMode [支持分屏组合的类型 ，每两位对应画面预览模式iSplitMode一位]
								0 : all random combine [0 全部任意组合， ]
								if random [如果为任意]
								1 : include relation, just some combines supported, limit to max 64 now [1 包含关系，只有少部分组合组合满足，现有约束最大64个；]
								2 : exclude relation, max 64 combines to exclude [2 排除关系，最大64个排除组合；]
								if it is include or exclude method, the subscript of SPLIT_COMBINE array flag detail infomation [如果是包含或者排除方式，SPLIT_COMBINE数组标示具体信息]
								other : not defined now, reserved [其他 暂无定义，后续扩展使用]
								*/
	unsigned char ucCombinNums;	/*the total number of combine, max to N_SPLIT_COMINE_NUMS 32 now [组合中总个数，现有最大N_SPLIT_COMINE_NUMS 32个]*/
	unsigned char ucRes;
	RV_SPLIT_COMBINE_CH stCombineCh[MAX_SPLIT_COMINE_NUMS];
}RV_SPLIT_COMBINE;

typedef struct
{
	unsigned int iSplitMode;	//supported types of multi-view preview, flag by bits, reference to enum split_combine_t [支持多种画面预览模式，按位标识，参考枚举split_combine_t]
	//bit 0 : SPLIT1 , this is single view and full screen, default supported by all devices [第0位 SPLIT1 此默认都支持，此为单画面，全屏]
	//bit 1 : SPLIT2 [第1位 SPLIT2] 
	//bit 2 : SPLIT4 [第2位 SPLIT4]
	//bit 3 : SPLIT8 [第3位 SPLIT8] 
	//bit 4 : SPLIT9 [第4位 SPLIT9]
	//bit 5 : SPLIT16 [第5位 SPLIT16] 
	//bit 6 : SPLITIP [第6位 SPLITIP]
	//bit 7 : SPLIT6 [第7位 SPLIT6]
	//bit 8 : SPLIT12 [第8位 SPLIT12]
	//bit 9 : SPLIT13
	//bit 10 : SPLIT20
	//bit 11 : SPLIT25
	//bit 12 : SPLIT33
	// bit13 : SPLIT5
	long lCount;				//number of SPLIT_COMBINE [SPLIT_COMBINE的数目]
	RV_SPLIT_COMBINE m_stSplitCombi[MAX_SPLITCOMBINE_NUMBER];//SPLIT_COMBINE数组
}RV_SPLIT_EN;

//////////////////////////////////////////////////////////////////////////
//	the authorities returned by success login [登陆返回的用户权限]
typedef struct
{
	unsigned long uiMonitorMask;
	unsigned long uiPlayMask;
	unsigned long uiNetPreviewMask;
	unsigned long uiControlConfigMask;
	unsigned long uiReserved[4];
}RV_USER_AUTH_LIST;

//////////////////////////////////////////////////////////////////////////
//	attributes of device returned by success login [登陆返回的设备属性]
typedef struct
{
	unsigned char iVideoInCaps;			//number of video input [视频输入接口数量]
	unsigned char iVideoOutCaps;		//number of video output [视频输出接口数量]
	unsigned char iAudioInCaps;			//number of audio input  [音频输入接口数量]
	unsigned char iAudioOutCaps;		//number of video output  [音频输出接口数量]	
	unsigned char iAlarmInCaps;			//number of alarm input  [报警输入接口数] 
	unsigned char iAlarmOutCaps;		//number of alarm output  [报警输出接口数]
	unsigned char iDiskNum;				//number of used disk  [实际使用硬盘数]
	unsigned char iAetherNetPortNum;	//number of network interface [网络接口数]	
	unsigned char iUsbPortNum;          //number of USB interface [USB接口数]
	unsigned char iDecodeChanNum;		//number of local decode(replay) [本地解码(回放)路数] 
	unsigned char iComPortNum;			//number of serial port [串口数]
	unsigned char iParallelPortNum;		//number of parallel port [并口口数]	
	unsigned char iSpeechInCaps;		//number of talk input [对讲输入接口数量]
	unsigned char iSpeechOutCaps;		//number of talk output [对讲输出接口数量]
	unsigned char bRes[2];				//reserved [保留]
}RV_SYSATTR_EX_T;

//////////////////////////////////////////////////////////////////////////
//ability struct of platform connection [平台接入能力结构体]
typedef struct
{
	int iIVideoMask;//mask of supported platform, bit0-BELL,bit1-HXHT,bit2-VS300, device maybe support mutiple platform [支持平台的掩码 第0位 BELL 第1位 HXHT 第2位 VS300 .可能设备支持多个平台接入]
	int iRes[3];
}RV_IVIDEO_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of code [编码能力结构体]
typedef struct
{
	unsigned int	uiMaxEncodePower;				//highest code ability supported [产品支持的最高编码能力]
	unsigned short	usSupportChannel;				//max number of video input supported per DSP [每块 DSP 支持最多输入视频通道数 ]
	unsigned short	usChannelSetSync;				//congiure of max code is or isn't be sync per DSP, 0-not be sync, 1-be sync [DSP 每通道的最大编码设置是否同步 0-不同步, 1-同步]
													//bit-stream situation supported per channel [每一通道支持码流情况]
	unsigned char	ucVideoStandardMask;			//video standard mask, flag by bits that it supports which standard, bit0-PAL, bit1-NTSC [视频制式掩码，按位表示设备能够支持的视频制式 0 PAL 1 NTSC]
	unsigned char	ucEncodeModeMask;				//mask of code mode, flag by bits that the code modes device supported, 0-VBR,1-CBR [编码模式掩码，按位表示设备能够支持的编码模式设置 ，0 VBR，1 CBR]
	unsigned short	usStreamCap;					//flag by bits that the media functions device supported [按位表示设备支持的多媒体功能，]
													//bit0 : support main stream [第一位表示支持主码流]
													//bit1 : support assist stream-1 [第二位表示支持辅码流1]
													//bit2 : support snapshot jpg file, and the snapshot function is defined in other place, so not add it here [第三位表示支持jpg抓图，捉图功能另外定义，在此不加入]
	unsigned int	uiImageSizeMask;				//mask of main stream, the enum reference to capture_size_t [主码流编码掩码 枚举按照capture_size_t ]
	unsigned int	uiImageSizeMask_Assi[32];		//code modes supported by assist stream while main stream is diffrent code mode, for example [主码流取不同的编码时候，辅码流支持的编码格式，例如, ]
													//uiImageSizeMask_Assi【0】is that, the code modes supported by assist stream when code mode of main stream is CAPTURE_SIZE_D1 [uiImageSizeMask_Assi【0】表示主码流是CAPTURE_SIZE_D1时，辅码流支持的编码格式，]
													//uiImageSizeMask_Assi【1】is that, the code modes supported by assist stream when code mode of main stream is CAPTURE_SIZE_HD1 [uiImageSizeMask_Assi【1】表示主码流是CAPTURE_SIZE_HD1时，辅码流支持的编码格式。。。]
	unsigned char	ucSupportPolicy;				//if support special code mode, 0-not support 1-support [是否支持特殊编码策略 0 不支持 1 支持]
	unsigned char	ucRes[11];						//reserved [保留]
}RV_ENCODE_CAPS_NET_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of time [时间能力结构体]
typedef struct
{
	unsigned char ucSupTimeAdjust;  //if support timing function [是否支持校时功能]
									//operate by bits [按位操作]
									//bit0 : Dst support daylight saving time [第0位 Dst 支持夏令时]
									//bit1 : SNTP(udp:123), default is this ntp now [第一位 SNTP（udp ：123）， 现在默认是此ntp]
									//bit2 : NTP(udp:37,tcp:37) [第二位 NTP（udp：37，tcp：37）]
	unsigned char ucRes[11];		//reserved [保留]
}RV_TIME_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of ftp [ftp能力结构体]
typedef struct
{
	unsigned char ucSupFtp; //operate by bits [按位操作]
							//bit0 : support upload record file by ftp [支持ftp录像上传]
							//bit1 : support upload picture file by ftp [支持ftp图片上传]							
	unsigned char ucRes[15];//reserved [保留]
}RV_FTP_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of black and white ip list [黑白名单能力结构体]
typedef struct  
{
	unsigned short	usMaxBlackNums;	//max number of black ip [最大黑名单数目]
	unsigned short	usMaxWhiteNums;	//max number of white ip [最大白名单数目]
	unsigned long	res[12];		//reserved [保留]
}RV_WHITEBLACK_EN;

//////////////////////////////////////////////////////////////////////////
//   ability struct of audio volumn [音量能力结构体]
typedef struct
{	
    unsigned long uiAudioVolumn ;   //bit 0~31 flag that if the channel support audio volumn adjust, and the ability of if the channel has audio input reference to AUDIO_IN_ABILITY [0~31为依次表示通道~通道音频输入支持音量控制,音频输入"有无"能力集参考AUDIO_IN_ABILITY]
    unsigned char ucTalk;           //bit0 flag that if audio input of talk support volumn adjust, and the ability of if audio input of talk reference to TALK_ABILITY [第0位表示对讲输入音频支持音量控制,对讲音频输入"有无"能力集参考TALK_ABILITY]
									//bit1 flag that if audio output of talk support volumn adjust, and the ability of if audio output of talk reference to TALK_ABILITY [第1位表示对讲输出音频支持音量控制和静音,对讲音频输出"有无"能力集参考TALK_ABILITY]
									//bit2 flag that if audio input of talk support input by MIC [第2位表示对讲输入音频支持MIC输入]
									//bit3 flag that if audio input of talk support input by Liner [第3位表示对讲输入音频支持Liner输入]
    unsigned char ucAudioChannel;   //the channels of audio input, 1-single 2-double [音频输入的声道，1：单声道；2：双声道 ]
    unsigned char ucRes;			
    unsigned char ucAudioOutChannel;//the channels of audio output of talk, 1-single 2-double [音频输出(对讲输出)的声道，1：单声道；2：双声道] 
    unsigned long uiRes[14];	
}RV_AUDIOVALUE_EN;

/////////////////////////////////////////////////////////////////////////
//	ability struct of rtsp [rtsp能力结构体]
typedef struct  
{
	unsigned char ucAbilty;//bit0:if support real-time watch by rtsp; bit1:if support record replay by rtsp [第1位表示是否支持rtsp实时监视，第2位表示是否支持rtsp录像回放]
	unsigned char Res[31] ;//reserved [保留]
}RV_RTSP_EN;

/////////////////////////////////////////////////////////////////////////
//	length of string struct (not 98 serial device) [非98设备字符串长度能力结构体]
typedef struct  
{
	unsigned short usPPPoeNameLen;	//user name length (contain null character) [用户名长度（包括null字符）]
	unsigned short usPPPoePwdLen;	//password length (contain null character) [密码长度（包括null字符）]
	unsigned short usRes[30] ;		//reserved [保留]
}RV_STR_LEN_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of recording [录像相关能力结构体]
typedef struct
{
	unsigned long dwFlag;//bit0-support new "record control" protocal [第0位表示支持新的"录像控制"协议]
	unsigned char ucRes[16];
}RV_RECORD_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of key-board for control [控制键盘能力结构体]
enum
{
	KBDFunc_PTZ_RAW_DATA_IN = 0,	//clarity serial port, clarity tranport PTZ commands [透明串口,云台控制命令的透明传输]
	KBDFunc_DHKBD = 1,				//key-board protocal of visiondigi [威乾键盘协议]
};
typedef  struct
{
	unsigned char ucAbilty;		//if support key-board control [是否支持控制键盘]
	unsigned char ucSupport;	//supported protocals : bit0-PTZ clarity channel, bit1-key-board protocal of visiondigi, reference to KBDFunc [支持的协议:第0位表示云台透明通道,第1位表示威乾控制键盘,参考KBDFunc]
	unsigned char ucRes[14] ;	//reserved [保留]
}RV_KBD_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of matrix(for XINGHUO Corp.) [矩阵(星火)能力结构体]
typedef struct 
{
	unsigned int uiMatrixInNum;//max matrix input number, 128 now, if device not support maxtrix for XINGHUO, this value is 0 [支持矩阵输入路数，目前为128，不支持星火矩阵的设备，该值为0]
	unsigned int reserve[3];
}RV_MATRIX_XINGHUO_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of OSD Zoom [OSD字体大小能力结构体]
typedef struct  
{
	unsigned char ucZoomAbility;  //1表示最大支持1倍缩放，2表示最大支持2倍缩放，以此类推，便于扩展。目前720P设备为2，其他设备为1
	unsigned char ucRes[3];
}RV_OSD_ZOOM_EN;

#endif

