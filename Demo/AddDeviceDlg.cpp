// AddDeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetSDKDemo.h"
#include "AddDeviceDlg.h"
#include "NetSDKDemoDlg.h"
#include "g_res.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//添加设备页面的处理
//Deal Of Add Device Page
/////////////////////////////////////////////////////////////////////////////
// AddDeviceDlg dialog

UserInfo *g_userinfo[10];
CString strPath;

inline void dbg_print_ex(int level, const char *msg, ...)
{
	char buf[256];
	
	va_list ap;
	va_start(ap, msg); // use variable arg list
	vsprintf(buf, msg, ap);
	va_end( ap );
}

AddDeviceDlg::AddDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddDeviceDlg)
	m_devicename = _T("test");
	m_deviceusername = _T("1");
	m_deviceuserpsw = _T("");
	m_deviceport = 37777;
	m_IPstr = _T("");
	//}}AFX_DATA_INIT
}


void AddDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddDeviceDlg)
	DDX_Control(pDX, IDC_COMBO_NETSTATE, m_ctlNetState);
	DDX_Control(pDX, IDC_IPSELECTION, m_ipsel);
	DDX_Text(pDX, IDC_DEVICE_NAME, m_devicename);
	DDV_MaxChars(pDX, m_devicename, 20);
	DDX_Text(pDX, IDC_DEVICE_USERNAME, m_deviceusername);
	DDV_MaxChars(pDX, m_deviceusername, 20);
	DDX_Text(pDX, IDC_DEVICE_USERPSW, m_deviceuserpsw);
	DDV_MaxChars(pDX, m_deviceuserpsw, 20);
	DDX_Text(pDX, IDC_DEVICE_PORT, m_deviceport);
	DDX_CBString(pDX, IDC_IPSELECTION, m_IPstr);
	DDV_MaxChars(pDX, m_IPstr, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(AddDeviceDlg)
	ON_BN_CLICKED(IDC_CONNECT_DEVICE, OnConnectDevice)
	ON_BN_CLICKED(IDC_CANCEL_ADDDEVICE, OnCancelAdddevice)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_IPSELECTION, OnSelchangeIpselection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddDeviceDlg message handlers

//连接失败的类型
//Type of connection fail
void AddDeviceDlg::GetConnectError(int error)
{
//	char tmpchar[100];
	//	memset ((char *)tmpchar, 0, 100);
	//	sprintf(tmpchar,"%d", error);
	//	MessageBox(tmpchar);
	//	return;
	
	//根据返回值不同判断错误类型
	//judge the error type by return value
	switch(error) 
	{
	case 1://password not correct//密码不正确
		MessageBox(ConvertString(MSG_ERROR_PASSWORD));
		break;
	case 2://user name not exist//用户名不存在
		MessageBox(ConvertString(MSG_ERROR_USER));
		break;
	case 3://login timeout//登录超时
		MessageBox(ConvertString(MSG_ERROR_TIMEOUT));
		break;
	case 4://already logined//重复登录
		MessageBox(ConvertString(MSG_ERROR_RELOGGIN));
		break;
	case 5://account locked//帐号被锁定
		MessageBox(ConvertString(MSG_ERROR_LOCKED), "VisionDigi SDK Client");
		break;
	case 6://account is in black name list//帐号被列入黑名单
		MessageBox(ConvertString(MSG_ERROR_BLACKLIST), "VisionDigi SDK Client");
		break;
	case 7://system busy (resource not enough)//系统忙，资源不足
		MessageBox(ConvertString(MSG_ERROR_BUSY),"VisionDigi SDK Client");
		break;
	case 8://version not mathced//版本不匹配
		MessageBox(ConvertString("server version doesn't match !"));
		break;
	case 9://can't find the host//找不到主机
		MessageBox(ConvertString(MSG_ERROR_CONNECT),"VisionDigi SDK Client");
		break;
	case 0:
	default:
		MessageBox(ConvertString(MSG_ERROR_NETWORK));
		break;
	}
}


//增加连接设备,连接成功增加到g_ptrdevicelist中
//add connected device, and add it to g_ptrdevicelist if connection success
void AddDeviceDlg::OnConnectDevice() 
{
	//CString
	int err;	//store returned error code//存储可能的错误返回值
	DeviceNode *inode;//temprary node of device info//临时设备信息节点

	UpdateData(TRUE);	//get inputed value on UI//获取界面输入

	int nNetStateSel = m_ctlNetState.GetCurSel();
	CLIENT_SetNetworkParam(&stuParam[nNetStateSel]);
	inode = new DeviceNode;
	memset((char *)inode, 0, sizeof(DeviceNode));
	
	//将页面信息写入节点
	//write infoamation on page to node
	sprintf(inode->IP, "%s", m_IPstr);
	memcpy(inode->Name,m_devicename.GetBuffer(0),m_devicename.GetLength()+1);
	memcpy(inode->UserNanme, m_deviceusername.GetBuffer(0), m_deviceusername.GetLength()+1);

	cameraID = inode->Name;
	//调用登录接口
	//call login interface
  	inode->LoginID = CLIENT_Login(inode->IP, (WORD)m_deviceport, 
                  m_deviceusername.GetBuffer(0), m_deviceuserpsw.GetBuffer(0), &inode->Info,&err);
// 	inode->LoginID = CLIENT_LoginEx(inode->IP, (WORD)m_deviceport,  
// 		m_deviceusername.GetBuffer(0), m_deviceuserpsw.GetBuffer(0), 4, NULL, &inode->Info,&err);
	
	if(inode->LoginID > 0)
	{
		inode->bIsOnline = TRUE;

		//HY test begin
		//CLIENT_ImportConfigFile(inode->LoginID, "d:\\tt.rr", NULL, NULL, 0);
		//CLIENT_ExportConfigFile(inode->LoginID, DH_CONFIGFILE_ALL, "d:\\tt.rr", NULL, 0);
		PTZ_OPT_ATTR *attr;
		attr = (PTZ_OPT_ATTR*)malloc(sizeof(PTZ_OPT_ATTR) * 80);
		DWORD len = 0;
		bool b = CLIENT_GetPtzOptAttr(inode->LoginID, 1, attr, 80*sizeof(PTZ_OPT_ATTR), &len, 50000);
		//HY test end
		
		//登录成功，临时节点生效
		//login success, temprary node is valable
		//g_ptrdevicelist->AddTail(inode);
		int r = CDevMgr::GetDevMgr().PushBack(inode);
		if (r < 0)
		{
			AfxMessageBox(ConvertString("device's node add to list failed"));
		}

		//开始侦听设备回调信息
		//start to listen callback messaged of device
		//BOOL ret = CLIENT_StartListen(inode->LoginID);
		BOOL ret = CLIENT_StartListenEx(inode->LoginID);
		if(!ret)
		{
			((CNetSDKDemoDlg *)GetParent())->LastError();
			MessageBox(ConvertString(MSG_ERROR_LISTEN));
		}

		//刷新内存和配置文件里的列表
		//refresh the list of memory and config files
		bool bIsnew = true;
		int counter;
		CString strKey;
		for (counter = 0; counter < m_ipsel.GetCount(); counter++)
		{
			CString strtemp;
			m_ipsel.GetLBText(counter, strtemp);
			if (strcmp(m_IPstr, g_userinfo[counter]->ip) == 0)
			{
				bIsnew = false;
				UserInfo tmpnode;
				strcpy (tmpnode.devicename, m_devicename.GetBuffer(0));
				strcpy (tmpnode.ip, m_IPstr.GetBuffer(0));
				tmpnode.port = m_deviceport;
				strcpy (tmpnode.username, m_deviceusername.GetBuffer(0));
				strcpy (tmpnode.userpsw, m_deviceuserpsw.GetBuffer(0));
				strKey.Format("%d", counter);
				BOOL ret = WritePrivateProfileStruct("UserInfo" , strKey , (LPVOID)&tmpnode, sizeof(UserInfo), strPath);
			}
		}
		//新的节点
		//new node
		if (bIsnew) 
		{
			if (counter >= 10) 
			{
				counter = 9;
			}
			UserInfo tmpnode;
			strcpy (tmpnode.devicename, m_devicename.GetBuffer(0));
			strcpy (tmpnode.ip, m_IPstr.GetBuffer(0));
			tmpnode.port = m_deviceport;
			strcpy (tmpnode.username, m_deviceusername.GetBuffer(0));
			strcpy (tmpnode.userpsw, m_deviceuserpsw.GetBuffer(0));
			strKey.Format("%d", counter);
			BOOL ret = WritePrivateProfileStruct("UserInfo" , strKey , (LPVOID)&tmpnode, sizeof(UserInfo), strPath);
		}
		for (int j = 0; j < 10; j++)
		{
			if (g_userinfo[j]) 
			{
				delete g_userinfo[j];
			}
		}

		CDialog ::OnOK();
	}
	else
	{
		//登录失败的情况
		//the case of login fail
		((CNetSDKDemoDlg *)GetParent())->LastError();
		GetConnectError(err);
		delete inode;
	}
}

//取消
//cancel
void AddDeviceDlg::OnCancelAdddevice() 
{
	for (int j = 0; j < 10; j++)
	{
		if (g_userinfo[j]) 
		{
			delete g_userinfo[j];
		}
	}
	CDialog::OnCancel();
}

//初始化页面
//initialize page
BOOL AddDeviceDlg::OnInitDialog() 
{
	g_SetWndStaticText(this);
	CDialog::OnInitDialog();

	UserInfo tmpinfo;
	for (int i = 0; i < 10; i++)
	{
		g_userinfo[i] = NULL;
		CString strKey;
		strKey.Format("%d", i);
		strPath = g_strWorkDir + "\\userinfo.ini";
		if (GetPrivateProfileStruct("UserInfo", strKey, (LPVOID)&tmpinfo, sizeof(UserInfo), strPath))
		{
			g_userinfo[i] = new UserInfo;
			memcpy(g_userinfo[i], &tmpinfo, sizeof(UserInfo));
			m_ipsel.InsertString(i,tmpinfo.ip);
		}
	}
	
	if (m_ipsel.GetCount() > 0) 
	{
		m_devicename.Format("%s", g_userinfo[0]->devicename);
		m_deviceport = g_userinfo[0]->port;
		m_deviceusername.Format("%s", g_userinfo[0]->username);
		m_deviceuserpsw.Format("%s", g_userinfo[0]->userpsw);
		UpdateData(FALSE);
		m_ipsel.SetCurSel(0);
	}
	
	memset(stuParam, 0 ,sizeof(NET_PARAM)*5);
	//很好
	//best
	stuParam[0].nWaittime = 3000;
	stuParam[0].nConnectTime =1500;
	stuParam[0].nConnectTryNum = 1;
	stuParam[0].nSubConnectSpaceTime = 10;

	//较好
	//better
	stuParam[1].nWaittime = 5000;
	stuParam[1].nConnectTime =2000;
	stuParam[1].nConnectTryNum = 2;
	stuParam[1].nSubConnectSpaceTime = 50;

	//一般
	//common
	stuParam[2].nWaittime = 8000;
	stuParam[2].nConnectTime =3000;
	stuParam[2].nConnectTryNum = 3;
	stuParam[2].nSubConnectSpaceTime = 100;

	//较差
	//worse
	stuParam[3].nWaittime = 13000;
	stuParam[3].nConnectTime =5000;
	stuParam[3].nConnectTryNum = 5;
	stuParam[3].nSubConnectSpaceTime = 1000;

	//很差
	//worst
	stuParam[4].nWaittime = 21000;
	stuParam[4].nConnectTime =8000;
	stuParam[4].nConnectTryNum = 8;
	stuParam[4].nSubConnectSpaceTime = 2000;

	m_ctlNetState.InsertString(0, "best");
	m_ctlNetState.InsertString(1, "better");
	m_ctlNetState.InsertString(2, "common");
	m_ctlNetState.InsertString(3, "worse");
	m_ctlNetState.InsertString(4, "worst");


	ConvertComboBox(m_ctlNetState);
	m_ctlNetState.SetCurSel(0);
	return TRUE;  
}

void AddDeviceDlg::OnClose() 
{
	for (int j = 0; j < 10; j++)
	{
		if (g_userinfo[j]) 
		{
			delete g_userinfo[j];
		}
	}
	CDialog::OnClose();
}

void AddDeviceDlg::OnSelchangeIpselection() 
{
	m_IPstr.Format("%s", g_userinfo[m_ipsel.GetCurSel()]->ip);
	m_devicename.Format("%s", g_userinfo[m_ipsel.GetCurSel()]->devicename);
	m_deviceport = g_userinfo[m_ipsel.GetCurSel()]->port;
	m_deviceusername.Format("%s", g_userinfo[m_ipsel.GetCurSel()]->username);
	m_deviceuserpsw.Format("%s", g_userinfo[m_ipsel.GetCurSel()]->userpsw);
	UpdateData(FALSE);
}
