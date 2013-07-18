
#ifndef VD_CLIENT_SYSABLE_H
#define VD_CLIENT_SYSABLE_H


//////////////////////////////////////////////////////////////////////////
//	type for query [��ѯ����]
typedef enum
{
	ABILITY_WATERMARK_CFG = 17,			//ability of configure watermark [ˮӡ��������]
	ABILITY_WIRELESS_CFG = 18,			//ability of configure wireless [wireless��������]
	ABILITY_DEVALL_INFO = 26,			//abblities of device [�豸�������б�]
	ABILITY_CARD_QUERY = 0x0100,		//ability of query by card No. [���Ų�ѯ����]
	ABILITY_MULTIPLAY = 0x0101,			//ability of multi-view preview [�໭��Ԥ������]
	ABILITY_INFRARED = 0X0121,			//ability of wireless alarm [���߱�������]
	ABILITY_TRIGGER_MODE = 0x0131,
	ABILITY_SAVIA_COUNT = 33,			//number of SAVIA [SAVIA��Ŀ]
	ABILITY_STR_LEN_EN = 35,			//length of string (not 98 serial device) [�ַ�������(��98�豸)]
	ABBI_TLV = 40,				//using new network protocal ? [�Ƿ�ʹ��������Э��]
	ABBI_DECODER,				//ability of decoder [����������]
	ABBI_AUTOREGISTER,			//ability of auto-register [����ע������]
	ABBI_SAVIA,					//ability of SAVIA [SAVIA����]
	ABBI_AUDIOIN,				//ability of audio input [��Ƶ����]
	ABBI_PTZTOUR,				//ability of PTZ soft tour [��̨��Ѳ������]
	ABBI_TALK,					//ability of talk [�Խ�����]
	ABBI_MVIEW,					//ability of combining and spliting views for multi-view preview [�໭��Ԥ������ָ��������]
	ABBI_SNAP,					//ability of snapshot [ץ������]
	ABBI_DEVID,					//device ID [�豸ID]
	ABBI_VERSION,				//software version [����汾]
	ABBI_AUTH_LIST,				//previleges of the current logined user [��ǰ��¼�û�Ȩ��]
	ABBI_SYS_ATTR_EX,			//device attributes [�豸����]
	ABBI_ISTLVPROTOCAL,			//using new network protocal ? [�Ƿ�ʹ��������Э��]
	ABBI_IVIDEO,				//ability of platform connection [ƽ̨��������]
	ABBI_ENCODE,				//ability of code [��������]
	ABBI_TIME,					//ability of time [ʱ������]
	ABBI_FTP,					//ability of ftp [ftp����]
	ABBI_WHITEBLACK,			//ability of black and white ip list [�ڰ���������]
	ABBI_DEVTYPE,				//device type [�豸����]
	ABBI_RTSP,					//ability of RTSP [RTSP����]
	ABBI_AUDIOVALUE,			//ability of audio volumn adjusting [��Ƶ��������]
	ABBI_RECORD,				//ability of recording [¼������]
	ABBI_KBD,					//ability of key-board for control [���Ƽ�������]
	ABBI_MATRIX_XINGHUO,		//ability of matrix(for XINGHUO Corp.) [����(�ǻ�)����]
	ABBI_OSD_ZOOM,				//ability of OSD FONT ZOOM [OSD�����С]
} RV_SYS_ABILITY;

//////////////////////////////////////////////////////////////////////////
//	function list supported by device [�豸֧�ֹ����б�]
enum 
{
	EN_FTP = 0,							//FTP by bit, 1:send record file 2:send picture file [FTP ��λ��1������¼���ļ� 2������ץͼ�ļ�]
	EN_SMTP,							//SMTP by bit, 1:send text e-mail for alarm 2:send picture e-mail for alarm [SMTP ��λ��1�����������ı��ʼ� 2����������ͼƬ]
	EN_NTP,								//NTP by bit, 1:adjust system time [NTP	��λ��1������ϵͳʱ��]
	EN_AUTO_MAINTAIN,					//auto mantance by bit, 1:reboot 2:shutdown 3:delete files [�Զ�ά�� ��λ��1������ 2���ر� 3:ɾ���ļ�]
	EN_VIDEO_COVER,						//area shelter by bit, 1:multi-area shelter [�����ڵ� ��λ��1���������ڵ�]
	EN_AUTO_REGISTER,					//auto register by bit, 1:sdk login device by initiative after registration [����ע��	��λ��1��ע���sdk������½]
	EN_DHCP,							//DHCP by bit, 1:DHCP [DHCP	��λ��1��DHCP]
	EN_UPNP,							//UPNP by bit, 1:UPNP [UPNP	��λ��1��UPNP]
	EN_COMM_SNIFFER,					//serial port capture package by bit, 1:CommATM [����ץ�� ��λ��1:CommATM]
	EN_NET_SNIFFER,						//network capture package by bit, 1:NetSniffer [����ץ�� ��λ�� 1��NetSniffer]
	EN_BURN,							//function of imprinting by bit, 1:query status of recording [��¼���� ��λ��1����ѯ��¼״̬]
	EN_VIDEO_MATRIX,					//video matrix by bit, 1:surport video matrix ? [��Ƶ���� ��λ��1���Ƿ�֧����Ƶ����]
	EN_AUDIO_DETECT,					//audio detect by bit, 1:support audio detect ? [��Ƶ��� ��λ��1���Ƿ�֧����Ƶ���]
	EN_STORAGE_STATION,					//store position by bit, 1:Ftp server(Ips) 2:Usb storage 3:NFS 4:DISK 5:SBM [�洢λ�� ��λ��1��Ftp������(Ips) 2��U�� 3��NFS 4��DISK 5��SBM]
	EN_IPSSEARCH,						//IPS store query by bit, 1:IPS store query [IPS�洢��ѯ ��λ��1��IPS�洢��ѯ]
	EN_SNAP,							//snapshot by bit, 1:resolve 2:frame rate 3:snapshot method 4:file format of snapshot 5:quality of picture [ץͼ  ��λ��1���ֱ���2��֡��3��ץͼ��ʽ4��ץͼ�ļ���ʽ5��ͼ������]
	EN_DEFAULTNIC,						//query for default net card supported by bit, 1:support [֧��Ĭ��������ѯ ��λ 1��֧��]
	EN_SHOWQUALITY,						//configure item of picture's display quality under CBR mode, 1:support  [CBRģʽ����ʾ���������� ��λ 1:֧��]
	EN_RTSP,							//RTSP [RTSP]
};

typedef struct 
{
	DWORD IsFucEnable[512];				//abbility array of function, and subscript corresponding to enum value above, and sub functions are flags by bits [�����б�������,�±��Ӧ������ö��ֵ,��λ��ʾ�ӹ���]
} RV_DEV_ENABLE_INFO;

//////////////////////////////////////////////////////////////////////////
//	ability struct of query by card No. [���Ų�ѯ�����ṹ��]
typedef struct 
{
	char		IsCardQueryEnable;
	char		iRev[3];
} RV_CARD_QUERY_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of configure wireless [wireless�����ṹ��]
typedef struct 
{
	char		IsWirelessEnable;
	char		iRev[3];
} RV_WIRELESS_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of configure watermark [ͼ��ˮӡ�����ṹ��]
typedef struct 
{
	char		isSupportWM;	//1:support 0:not support [1 ֧�֣�0 ��֧��]
	char		supportWhat;	//0:text watermark 1:picture watermark 2:surport both text and picture watermark [0������ˮӡ��1��ͼƬˮӡ��2��ͬʱ֧������ˮӡ��ͼƬˮӡ]
	char		reserved[2];
} RV_WATERMAKE_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of multi-view preview [�໭��Ԥ�������ṹ��]
typedef struct  
{
	int			nEnable;			//1:support 0:not support [1 ֧�֣�0 ��֧��]
	DWORD		dwMultiPlayMask;	//reserved [����]
	char		reserved[4];
} RV_MULTIPLAY_EN;

//////////////////////////////////////////////////////////////////////////
//	number of SAVIA struct [SAVIA��Ŀ�����ṹ��]
typedef struct 
{
	DWORD		dwCount;
} RV_SAVIA_COUNT;

typedef struct  
{
	BOOL bSupport;			//support ? [�Ƿ�֧��]
	int	 nAlarmInCount;		//number of alarm in [�������]
	int  nAlarmOutCount;	//number of alarm out [�������]
	int  nRemoteAddrCount;	//number of remote-control unit [ң��������]
	BYTE reserved[32];
}RV_WIRELESS_ALARM_INFO;

//////////////////////////////////////////////////////////////////////////
//	ability struct of PTZ soft tour [��̨��Ѳ�������ṹ��]
typedef  struct
{
	unsigned short usPresetNums ;	//max number of presets for every channel [ÿ��ͨ��Ԥ�õ�������]
	unsigned short usTourNums;		//max number of tours for every channel [ÿ��ͨ�����Ѳ���켣����]
    int iRes [4];					//reserved [����]
}RV_PTZ_TOUR_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of auto-register [����ע�������ṹ��]
typedef  struct
{
	unsigned short usRegServerNums ;	//number of auto-regiser server, just one now [����ע����������� ����ʵ��Ϊ1��]
	unsigned short usNetMode;			//auto-register mode [����ע��ģʽ]
										//support multiple network mode, every bit flags support : 1:support 0:not support [֧�ֶ�������ģʽ ÿһλ��ʶ�Ƿ�֧�� 0��ʶ��֧�֣�1��ʶ֧��]
										//bit 0 : single connection of video and commands [��0λ ��Ƶ���������]
										//bit 1 : multi-connection(multi-connection of multimedia, support that device connects server to send video data forwardly) [��1λ �����ӣ�ý������ӣ�֧���豸�������ӷ�����������Ƶ��]
    int iRes [4];						//reserved [����]
}RV_AUTO_REGISTER_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of decoder [�����������ṹ��]
typedef  struct
{
	unsigned short usDecoderNums ;  //max number of channles [���������·��]
	unsigned short usNetMode;		//support multiple network mode, every bit flags support : 1:support 0:not support [֧�ֶ�������ģʽ ÿһλ��ʶ�Ƿ�֧�� 0��ʶ��֧�֣�1��ʶ֧��]
									//bit 0 : common network vs100,vs200, default setted to 1 [��0λ ͨ������vs100��vs200��Ĭ�ϴ�Ϊ֧�� ��1]
									//bit 1 : support rtsp Client [��1λ ֧��rtsp Client]
									//bit 2 : support vs300  [��2λ ֧��vs300��]
	int iAbilityMask;				//decode abbility for every channel, max 16 channels now, so every 2 bits mark 1 channel in 32 bits [ÿ·�������������� ���������16ͨ����32λÿ2λ��ʶһ��ͨ��]
									//00:max support to CIF, 01:max support to D1, 10:max support to 720p, 11:more [00 ���֧��CIF��01 ���֧��D1��10�����֧��720p, 11 ����]
	unsigned char ucDecoderType; 	//type of decoder [��������ʽ]
									//0:mixed type of DVR (both contain analog channels and digital channels), 1:pure decoder(only digital channels) [0���dvr������ģ��Ҳ�������֣���1����������ֻ�����֣�]
	unsigned char ucModeAblity;		//bit 0 : support multi-connection tour ? [��0λ �Ƿ�֧�ֶ�������Ѳ�ķ�ʽ]
	unsigned short  usMaxChNum;		//max number of channels for every supported tour when support multi-connection tour [֧�ֶ����ӷ�ʽʱ,ÿ·֧�ֵ���Ѳ�б��ͨ���������Ŀ]
	int iRes [3];					//reserved [����]
}RV_DECODE_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of snapshot [ץ�������ṹ��]
typedef struct
{	
    unsigned long type_mask;			//flag by bits : 0-trigger to snapshot 1-timer to snapshot 2-alarm to snapshot [��λ��ʾ 0-����ץ��, 1-��ʱץ��, 2-�澯ץ��]
	unsigned long uiSnapMaxCount;		//max number of snapshot per second supported [���֧��ץ������]
	unsigned long uiCountsPerSecond;	/*how many pictures per second, flag by bits	[1s����ͼƬ����λ��ʾ]
										bit0:1 picture per second [��0λ 1s1��]
										bit1:2 picture per second [��1λ 1s2��]
										bit2:3 picture per second [��2λ 1s3��]
										bit3:4 picture per second [��3λ 1s4��]
										bit4:5 picture per second [��4λ 1s5��]
										*/					
	unsigned long uiMaxSeconds;			/*max number of seconds per picture supported [���֧�ּ���1��]*/
	unsigned long uiRes[28];
}RV_ABILITY_SNAP_T;

//////////////////////////////////////////////////////////////////////////
//	ability struct of intelligent [����ģ�������ṹ��]
typedef struct
{
	unsigned char ucSaviaNums ;		//number of savia [savia��Ŀ]
	unsigned char ucSurportAl;		//surpported arithmetics [֧�ֵ��㷨]
	unsigned char ucRes[22];		//reserved [����]
}RV_SAVIA_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of talk(audio in and audio out) [�Խ����Խ���Ƶ����+��Ƶ����������ṹ��]
typedef struct
{
	unsigned char ucSurportTalkIn ;  	//audio input for talk (device has individual audio capture) [�Խ���Ƶ���루�豸���ڵ�������Ƶ�ɼ��� 1:֧�֣�0����֧��]
	unsigned char ucTalkInMask;     	//code type of audio input supported, flag by bits [�豸��Ƶ��������ʽ����  ��λ��ʶ�Ƿ�֧�ֱ����ʽ]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [��0λ �Ƿ�֧��g711a�� ��1λ pcm8k16b ��2λ g711u��]
	unsigned char ucSurportTalkOut;		//audio output for talk, 1:support,0:not support [�Խ���Ƶ���   1:֧�֣�0����֧��]
	unsigned char ucTalkOutMask;     	//decode type of audio supported, flag by bits [�豸��Ƶ�����ʽ����  ��λ��ʶ�Ƿ�֧�ֽ����ʽ]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [��0λ �Ƿ�֧��g711a�� ��1λ pcm8k16b  ��2λ g711u��]
}RV_TALK_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of audio input [��Ƶ���������ṹ��]
typedef struct
{
	unsigned long uiAudio ;				//bit 0~31 : flag that there are audio input in channel 1~32, 1:input 0:no input [0~31Ϊ���α�ʾͨ��1~ͨ��32����Ƶ���� 1��ʶ�У�0��ʶ]
	unsigned long uiAudioMask ;  		//code type of accompanying sound input, flag by bits [�豸���������ʽ����  ��λ��ʶ�Ƿ�֧�ֱ����ʽ]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [��0λ �Ƿ�֧��g711a�� ��1λ pcm8k16b  ��2λ g711u��]
}RV_AUDIO_IN_EN;

//////////////////////////////////////////////////////////////////////////
//	ability of combining and spliting views [����ָ���������ṹ��]
#define MAX_SPLIT_COMINE_NUMS 32
#define MAX_SPLITCOMBINE_NUMBER 32
typedef struct
{
	unsigned int iChMask;		 //channel mask, flag by bits, total 32 bits (4 byts)(max 32 types) [ͨ�����룬��λ��ʶ����32λ4�ֽ�,���32����ʽ]
								 /*for example : 4 views, support mode (1,2,3,4channel)(1,3,4,5channel) [4���� ��֧�� ģʽ��1��2��3��4ͨ������1��3��4��5��]
								 corresponding mask is 0000 0000 0000 0000 0000 0000 0000 1111=0x0F [��Ӧ������Ϊ  0000 0000 0000 0000 0000 0000 0000 1111=0x0F]
								 0000 0000 0000 0000 0000 0000 0001 1101=0x1D [0000 0000 0000 0000 0000 0000 0001 1101=0x1D]
								 if 9 views, support mode (1,2,4,5,6,7,8,9,10channel) [���9���� ֧�֣�1��2��4��5��6��7��8��9��10ͨ����]
								 corresponding mask is 0000 0000 0000 0000 0000 0011 1111 1011=0x3FB [��Ӧ������Ϊ0000 0000 0000 0000 0000 0011 1111 1011=0x3FB]
								 the mask content here, need to decide by uiSplitType in  SPLIT_MODE, and there has include or exclude relation now [�˴��������ݣ�����Ҫ���� SPLIT_MODE��uiSplitType�����������ƶ��ǰ�����ϵ�����ų���ϵ]
								 */
	unsigned char ucSpecialCh;	 /*special channel (restrict to be show in the first view or the biggest view) [����ͨ����Լ��Ϊ�Զ�������ǰ���ߴ󴰿���ʾ��]*/
	unsigned char ucRes[3];
}RV_SPLIT_COMBINE_CH;
typedef struct
{
	unsigned char ucSplitMode;	/*mode of multi-view preview, reference to enum split_combine_t [�໭��Ԥ��ģʽ���ο�ö��split_combine_t]*/
	unsigned char ucSplitType;  /*supported split views type, every two bits corresponding one bit in iSplitMode [֧�ַ�����ϵ����� ��ÿ��λ��Ӧ����Ԥ��ģʽiSplitModeһλ]
								0 : all random combine [0 ȫ��������ϣ� ]
								if random [���Ϊ����]
								1 : include relation, just some combines supported, limit to max 64 now [1 ������ϵ��ֻ���ٲ������������㣬����Լ�����64����]
								2 : exclude relation, max 64 combines to exclude [2 �ų���ϵ�����64���ų���ϣ�]
								if it is include or exclude method, the subscript of SPLIT_COMBINE array flag detail infomation [����ǰ��������ų���ʽ��SPLIT_COMBINE�����ʾ������Ϣ]
								other : not defined now, reserved [���� ���޶��壬������չʹ��]
								*/
	unsigned char ucCombinNums;	/*the total number of combine, max to N_SPLIT_COMINE_NUMS 32 now [������ܸ������������N_SPLIT_COMINE_NUMS 32��]*/
	unsigned char ucRes;
	RV_SPLIT_COMBINE_CH stCombineCh[MAX_SPLIT_COMINE_NUMS];
}RV_SPLIT_COMBINE;

typedef struct
{
	unsigned int iSplitMode;	//supported types of multi-view preview, flag by bits, reference to enum split_combine_t [֧�ֶ��ֻ���Ԥ��ģʽ����λ��ʶ���ο�ö��split_combine_t]
	//bit 0 : SPLIT1 , this is single view and full screen, default supported by all devices [��0λ SPLIT1 ��Ĭ�϶�֧�֣���Ϊ�����棬ȫ��]
	//bit 1 : SPLIT2 [��1λ SPLIT2] 
	//bit 2 : SPLIT4 [��2λ SPLIT4]
	//bit 3 : SPLIT8 [��3λ SPLIT8] 
	//bit 4 : SPLIT9 [��4λ SPLIT9]
	//bit 5 : SPLIT16 [��5λ SPLIT16] 
	//bit 6 : SPLITIP [��6λ SPLITIP]
	//bit 7 : SPLIT6 [��7λ SPLIT6]
	//bit 8 : SPLIT12 [��8λ SPLIT12]
	//bit 9 : SPLIT13
	//bit 10 : SPLIT20
	//bit 11 : SPLIT25
	//bit 12 : SPLIT33
	// bit13 : SPLIT5
	long lCount;				//number of SPLIT_COMBINE [SPLIT_COMBINE����Ŀ]
	RV_SPLIT_COMBINE m_stSplitCombi[MAX_SPLITCOMBINE_NUMBER];//SPLIT_COMBINE����
}RV_SPLIT_EN;

//////////////////////////////////////////////////////////////////////////
//	the authorities returned by success login [��½���ص��û�Ȩ��]
typedef struct
{
	unsigned long uiMonitorMask;
	unsigned long uiPlayMask;
	unsigned long uiNetPreviewMask;
	unsigned long uiControlConfigMask;
	unsigned long uiReserved[4];
}RV_USER_AUTH_LIST;

//////////////////////////////////////////////////////////////////////////
//	attributes of device returned by success login [��½���ص��豸����]
typedef struct
{
	unsigned char iVideoInCaps;			//number of video input [��Ƶ����ӿ�����]
	unsigned char iVideoOutCaps;		//number of video output [��Ƶ����ӿ�����]
	unsigned char iAudioInCaps;			//number of audio input  [��Ƶ����ӿ�����]
	unsigned char iAudioOutCaps;		//number of video output  [��Ƶ����ӿ�����]	
	unsigned char iAlarmInCaps;			//number of alarm input  [��������ӿ���] 
	unsigned char iAlarmOutCaps;		//number of alarm output  [��������ӿ���]
	unsigned char iDiskNum;				//number of used disk  [ʵ��ʹ��Ӳ����]
	unsigned char iAetherNetPortNum;	//number of network interface [����ӿ���]	
	unsigned char iUsbPortNum;          //number of USB interface [USB�ӿ���]
	unsigned char iDecodeChanNum;		//number of local decode(replay) [���ؽ���(�ط�)·��] 
	unsigned char iComPortNum;			//number of serial port [������]
	unsigned char iParallelPortNum;		//number of parallel port [���ڿ���]	
	unsigned char iSpeechInCaps;		//number of talk input [�Խ�����ӿ�����]
	unsigned char iSpeechOutCaps;		//number of talk output [�Խ�����ӿ�����]
	unsigned char bRes[2];				//reserved [����]
}RV_SYSATTR_EX_T;

//////////////////////////////////////////////////////////////////////////
//ability struct of platform connection [ƽ̨���������ṹ��]
typedef struct
{
	int iIVideoMask;//mask of supported platform, bit0-BELL,bit1-HXHT,bit2-VS300, device maybe support mutiple platform [֧��ƽ̨������ ��0λ BELL ��1λ HXHT ��2λ VS300 .�����豸֧�ֶ��ƽ̨����]
	int iRes[3];
}RV_IVIDEO_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of code [���������ṹ��]
typedef struct
{
	unsigned int	uiMaxEncodePower;				//highest code ability supported [��Ʒ֧�ֵ���߱�������]
	unsigned short	usSupportChannel;				//max number of video input supported per DSP [ÿ�� DSP ֧�����������Ƶͨ���� ]
	unsigned short	usChannelSetSync;				//congiure of max code is or isn't be sync per DSP, 0-not be sync, 1-be sync [DSP ÿͨ���������������Ƿ�ͬ�� 0-��ͬ��, 1-ͬ��]
													//bit-stream situation supported per channel [ÿһͨ��֧���������]
	unsigned char	ucVideoStandardMask;			//video standard mask, flag by bits that it supports which standard, bit0-PAL, bit1-NTSC [��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ 0 PAL 1 NTSC]
	unsigned char	ucEncodeModeMask;				//mask of code mode, flag by bits that the code modes device supported, 0-VBR,1-CBR [����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ���� ��0 VBR��1 CBR]
	unsigned short	usStreamCap;					//flag by bits that the media functions device supported [��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�]
													//bit0 : support main stream [��һλ��ʾ֧��������]
													//bit1 : support assist stream-1 [�ڶ�λ��ʾ֧�ָ�����1]
													//bit2 : support snapshot jpg file, and the snapshot function is defined in other place, so not add it here [����λ��ʾ֧��jpgץͼ��׽ͼ�������ⶨ�壬�ڴ˲�����]
	unsigned int	uiImageSizeMask;				//mask of main stream, the enum reference to capture_size_t [�������������� ö�ٰ���capture_size_t ]
	unsigned int	uiImageSizeMask_Assi[32];		//code modes supported by assist stream while main stream is diffrent code mode, for example [������ȡ��ͬ�ı���ʱ�򣬸�����֧�ֵı����ʽ������, ]
													//uiImageSizeMask_Assi��0��is that, the code modes supported by assist stream when code mode of main stream is CAPTURE_SIZE_D1 [uiImageSizeMask_Assi��0����ʾ��������CAPTURE_SIZE_D1ʱ��������֧�ֵı����ʽ��]
													//uiImageSizeMask_Assi��1��is that, the code modes supported by assist stream when code mode of main stream is CAPTURE_SIZE_HD1 [uiImageSizeMask_Assi��1����ʾ��������CAPTURE_SIZE_HD1ʱ��������֧�ֵı����ʽ������]
	unsigned char	ucSupportPolicy;				//if support special code mode, 0-not support 1-support [�Ƿ�֧������������ 0 ��֧�� 1 ֧��]
	unsigned char	ucRes[11];						//reserved [����]
}RV_ENCODE_CAPS_NET_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of time [ʱ�������ṹ��]
typedef struct
{
	unsigned char ucSupTimeAdjust;  //if support timing function [�Ƿ�֧��Уʱ����]
									//operate by bits [��λ����]
									//bit0 : Dst support daylight saving time [��0λ Dst ֧������ʱ]
									//bit1 : SNTP(udp:123), default is this ntp now [��һλ SNTP��udp ��123���� ����Ĭ���Ǵ�ntp]
									//bit2 : NTP(udp:37,tcp:37) [�ڶ�λ NTP��udp��37��tcp��37��]
	unsigned char ucRes[11];		//reserved [����]
}RV_TIME_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of ftp [ftp�����ṹ��]
typedef struct
{
	unsigned char ucSupFtp; //operate by bits [��λ����]
							//bit0 : support upload record file by ftp [֧��ftp¼���ϴ�]
							//bit1 : support upload picture file by ftp [֧��ftpͼƬ�ϴ�]							
	unsigned char ucRes[15];//reserved [����]
}RV_FTP_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of black and white ip list [�ڰ����������ṹ��]
typedef struct  
{
	unsigned short	usMaxBlackNums;	//max number of black ip [����������Ŀ]
	unsigned short	usMaxWhiteNums;	//max number of white ip [����������Ŀ]
	unsigned long	res[12];		//reserved [����]
}RV_WHITEBLACK_EN;

//////////////////////////////////////////////////////////////////////////
//   ability struct of audio volumn [���������ṹ��]
typedef struct
{	
    unsigned long uiAudioVolumn ;   //bit 0~31 flag that if the channel support audio volumn adjust, and the ability of if the channel has audio input reference to AUDIO_IN_ABILITY [0~31Ϊ���α�ʾͨ��~ͨ����Ƶ����֧����������,��Ƶ����"����"�������ο�AUDIO_IN_ABILITY]
    unsigned char ucTalk;           //bit0 flag that if audio input of talk support volumn adjust, and the ability of if audio input of talk reference to TALK_ABILITY [��0λ��ʾ�Խ�������Ƶ֧����������,�Խ���Ƶ����"����"�������ο�TALK_ABILITY]
									//bit1 flag that if audio output of talk support volumn adjust, and the ability of if audio output of talk reference to TALK_ABILITY [��1λ��ʾ�Խ������Ƶ֧���������ƺ;���,�Խ���Ƶ���"����"�������ο�TALK_ABILITY]
									//bit2 flag that if audio input of talk support input by MIC [��2λ��ʾ�Խ�������Ƶ֧��MIC����]
									//bit3 flag that if audio input of talk support input by Liner [��3λ��ʾ�Խ�������Ƶ֧��Liner����]
    unsigned char ucAudioChannel;   //the channels of audio input, 1-single 2-double [��Ƶ�����������1����������2��˫���� ]
    unsigned char ucRes;			
    unsigned char ucAudioOutChannel;//the channels of audio output of talk, 1-single 2-double [��Ƶ���(�Խ����)��������1����������2��˫����] 
    unsigned long uiRes[14];	
}RV_AUDIOVALUE_EN;

/////////////////////////////////////////////////////////////////////////
//	ability struct of rtsp [rtsp�����ṹ��]
typedef struct  
{
	unsigned char ucAbilty;//bit0:if support real-time watch by rtsp; bit1:if support record replay by rtsp [��1λ��ʾ�Ƿ�֧��rtspʵʱ���ӣ���2λ��ʾ�Ƿ�֧��rtsp¼��ط�]
	unsigned char Res[31] ;//reserved [����]
}RV_RTSP_EN;

/////////////////////////////////////////////////////////////////////////
//	length of string struct (not 98 serial device) [��98�豸�ַ������������ṹ��]
typedef struct  
{
	unsigned short usPPPoeNameLen;	//user name length (contain null character) [�û������ȣ�����null�ַ���]
	unsigned short usPPPoePwdLen;	//password length (contain null character) [���볤�ȣ�����null�ַ���]
	unsigned short usRes[30] ;		//reserved [����]
}RV_STR_LEN_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of recording [¼����������ṹ��]
typedef struct
{
	unsigned long dwFlag;//bit0-support new "record control" protocal [��0λ��ʾ֧���µ�"¼�����"Э��]
	unsigned char ucRes[16];
}RV_RECORD_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of key-board for control [���Ƽ��������ṹ��]
enum
{
	KBDFunc_PTZ_RAW_DATA_IN = 0,	//clarity serial port, clarity tranport PTZ commands [͸������,��̨���������͸������]
	KBDFunc_DHKBD = 1,				//key-board protocal of visiondigi [��Ǭ����Э��]
};
typedef  struct
{
	unsigned char ucAbilty;		//if support key-board control [�Ƿ�֧�ֿ��Ƽ���]
	unsigned char ucSupport;	//supported protocals : bit0-PTZ clarity channel, bit1-key-board protocal of visiondigi, reference to KBDFunc [֧�ֵ�Э��:��0λ��ʾ��̨͸��ͨ��,��1λ��ʾ��Ǭ���Ƽ���,�ο�KBDFunc]
	unsigned char ucRes[14] ;	//reserved [����]
}RV_KBD_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of matrix(for XINGHUO Corp.) [����(�ǻ�)�����ṹ��]
typedef struct 
{
	unsigned int uiMatrixInNum;//max matrix input number, 128 now, if device not support maxtrix for XINGHUO, this value is 0 [֧�־�������·����ĿǰΪ128����֧���ǻ������豸����ֵΪ0]
	unsigned int reserve[3];
}RV_MATRIX_XINGHUO_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of OSD Zoom [OSD�����С�����ṹ��]
typedef struct  
{
	unsigned char ucZoomAbility;  //1��ʾ���֧��1�����ţ�2��ʾ���֧��2�����ţ��Դ����ƣ�������չ��Ŀǰ720P�豸Ϊ2�������豸Ϊ1
	unsigned char ucRes[3];
}RV_OSD_ZOOM_EN;

#endif

