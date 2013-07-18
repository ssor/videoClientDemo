 // TransCom.cpp : implementation file
//

#include "stdafx.h"
#include "netsdkdemo.h"
#include "TransCom.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransCom dialog


CTransCom::CTransCom(CWnd* pParent /*=NULL*/)
	: CDialog(CTransCom::IDD, pParent)
{
	m_devHandle = 0;
	//{{AFX_DATA_INIT(CTransCom)
	m_recievestring = _T("");
	m_sendstring = _T("");
	//}}AFX_DATA_INIT
	m_count = 0;
	m_iChannelNO = -1;
}


void CTransCom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransCom)
	DDX_Control(pDX, IDC_COMSTOPBIT, m_stopbit);
	DDX_Control(pDX, IDC_COMSEL, m_comsel);
	DDX_Control(pDX, IDC_COMPARITY, m_parity);
	DDX_Control(pDX, IDC_COMDATABIT, m_databit);
	DDX_Control(pDX, IDC_BAUDRATE, m_baudrate);
	DDX_Text(pDX, IDC_RECIEVERANGE, m_recievestring);
	DDX_Text(pDX, IDC_EDITCOMSEND, m_sendstring);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransCom, CDialog)
	//{{AFX_MSG_MAP(CTransCom)
	ON_BN_CLICKED(IDC_OPENCLOSE, OnOpenclose)
	ON_BN_CLICKED(IDC_COMSEND, OnComsend)
	ON_BN_CLICKED(IDC_DELETEREVICE, OnDeleterevice)
	ON_BN_CLICKED(IDC_DELETESEND, OnDeletesend)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransCom message handlers
#define  BAUDRATE_NUM  8
unsigned int Tbaudrate[BAUDRATE_NUM] = {1200,2400,4800,9600,19200,38400,57600,115200};

BOOL CTransCom::OnInitDialog() 
{
	g_SetWndStaticText(this);
	int i;
	CString strTemp;
	
	CDialog::OnInitDialog();

	//初始化com选择
	//initialize com selection
	m_comsel.InsertString(0, "com");
	m_comsel.InsertString(1, "485");
	m_comsel.InsertString(2, "232");
	m_comsel.SetItemData(0, 0);
	m_comsel.SetItemData(1, 1);
	m_comsel.SetItemData(2, 2);
	m_comsel.SetCurSel(0);

	//初始化波特率
	//initialize baudrate
	for(i = 0; i < BAUDRATE_NUM; i++)
	{
		strTemp.Format(" %d",Tbaudrate[i]);
		m_baudrate.InsertString(i, strTemp.GetBuffer(0));
		m_baudrate.SetItemData(i, i +1);   //set value to 1~8 //设置值为1~8
	}
	m_baudrate.SetCurSel(3);  //default 9600 //默认9600

	//初始化数据位
	//initialize data bit
	for(i = 0; i < 5; i ++)
	{
		strTemp.Format(" %d ",i+4);
		strTemp += ConvertString(MSG_TRANSCOM_DATABIT_BITS);
		m_databit.InsertString(i,strTemp );
		m_databit.SetItemData(i, (DWORD)(i+4));
	}
	m_databit.SetCurSel(4);

	//初始化停止位
	//initialize stop bit
	m_stopbit.InsertString(0, ConvertString(MSG_TRANSCOM_STOPBIT_1BIT ));
	m_stopbit.InsertString(1, ConvertString(MSG_TRANSCOM_STOPBIT_15BITS ));
	m_stopbit.InsertString(2, ConvertString(MSG_TRANSCOM_STOPBIT_2BITS ));
	m_stopbit.SetItemData(0, 1);
	m_stopbit.SetItemData(1, 2);
	m_stopbit.SetItemData(2, 3);
	m_stopbit.SetCurSel(0);


	//初始化奇偶检验
	//initialize odd or even verify
	m_parity.InsertString(0, ConvertString(MSG_TRANSCOM_PARITY_NO));
	m_parity.InsertString(1, ConvertString(MSG_TRANSCOM_PARITY_ODD));
	m_parity.InsertString(2, ConvertString(MSG_TRANSCOM_PARITY_EVEN));
	m_parity.SetItemData(0, 3);
	m_parity.SetItemData(1, 1);
	m_parity.SetItemData(2, 2);
	m_parity.SetCurSel(0);
	
	m_isComOpen = FALSE;
	m_comHandle = 0;

	UpdataOpenCloseState();
	
	return TRUE; 
}

void CTransCom::UpdataOpenCloseState()
{
	if(m_isComOpen)
	{
		GetDlgItem(IDC_OPENCLOSE)->SetWindowText(ConvertString(MSG_TRANSCOM_CLOSECOM));
	}
	else
	{
		GetDlgItem(IDC_OPENCLOSE)->SetWindowText(ConvertString(MSG_TRANSCOM_OPENCOM));
	}
}

void CALLBACK TransComCB(LONG lLoginID, LONG lTransComChannel, char *pBuffer, DWORD dwBufSize, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CTransCom *dlg = (CTransCom *)dwUser;
	dlg->ComRecieveData(lLoginID, lTransComChannel,pBuffer, dwBufSize);

}

short __stdcall hex_asc(unsigned char *hex, char *asc, long length)
{
    UCHAR hLowbit,hHighbit; 
	long i; 
	for(i=0; i < length*2 ; i=i+2) 
	{ 
		hLowbit=hex[i/2]&0x0f; 
		hHighbit=hex[i/2]/16; 
		if(hHighbit>=10) 
			asc[i]=hHighbit+ '7'; 
		else 
			asc[i]=hHighbit+ '0'; 
		if(hLowbit>=10) 
			asc[i+1]=hLowbit+ '7'; 
		else 
			asc[i+1]=hLowbit+ '0'; 
	} 
	asc[length*2] = '\0'; 
	return 0; 	
}

void CTransCom::ComRecieveData(LONG lLoginID, LONG lTransComChannel,char *pBuffer, DWORD dwBufSize)
{
	if(lLoginID != m_devHandle || lTransComChannel != m_comHandle )
	{
		return;
	}

// 	char *tmp = new char[dwBufSize + 1];
// 	memset(tmp, 0, dwBufSize + 1);
// 	memcpy(tmp, pBuffer, dwBufSize);
	char *pChar = new char[dwBufSize * 2 + 1];
	hex_asc((unsigned char*)pBuffer, pChar, dwBufSize);
 	CString strR;
 	strR.Format("%s", pChar);
	m_recievestring += strR;
	GetDlgItem(IDC_RECIEVERANGE)->SetWindowText(m_recievestring);
	if (m_recievestring.GetLength() > 255)
	{
		m_recievestring.Empty();
	}
	delete[] pChar;
}

void CTransCom::OnOpenclose() 
{
	BOOL nRet = TRUE;
	
	if(m_isComOpen)   //comit closing while opened //已打开时执行关闭
	{
		if(m_comHandle)
		{
			nRet = CLIENT_DestroyTransComChannel(m_comHandle);
			if(nRet)
			{	
				m_comHandle = 0;
			}
			else if(!nRet)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			}
		}
	}
	else    //open operation //打开操作
	{
		if(m_devHandle)
		{

			m_comHandle = CLIENT_CreateTransComChannel(m_devHandle,m_comsel.GetItemData(m_comsel.GetCurSel()),
				m_baudrate.GetItemData(m_baudrate.GetCurSel()),m_databit.GetItemData(m_databit.GetCurSel()),
				m_stopbit.GetItemData(m_stopbit.GetCurSel()),m_parity.GetItemData(m_parity.GetCurSel()),
				TransComCB,(DWORD)this);
			if(m_comHandle)
			{
				nRet = TRUE;
			}
			else
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
				MessageBox(MSG_TRANSCOM_OPENTRANSCOMFAILED);
			}
		}
	}
	if(nRet)
	{
		m_isComOpen = !m_isComOpen;
	}
	else if(!nRet)
	{
		((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
	}
	UpdataOpenCloseState();	
}

void CTransCom::SetDeviceId(LONG nDeviceId)
{
	m_devHandle = nDeviceId;
}

void CTransCom::SetChannelNO(int iChanNO)
{
	m_iChannelNO = iChanNO;
}

//发送
//send
short asc_hex(unsigned char *asc, unsigned char *hex, long pair_len) 
{ 
	char src1,src2,factor1,factor2; 
	long len; 
	factor1 = '7'; 
	factor2 = '7'; 
	
	for (len=0; len < pair_len; len++) 
	{ 
		src1 = *(asc+len*2); 
		src2 = *(asc+len*2+1); 
		
		if ((src1 >= 'a') && (src1 <= 'f'))
		{
			char *psrc;
			psrc = strupr(&src1);
			src1 = *psrc;
		}

		if ((src2 >= 'a') && (src2 <= 'f'))
		{
			src2 = (char)*strupr(&src2);
		}

		if ((src1 >= '0') && (src1 <= '9')) 
			factor1   =   '0'; 
        else if ((src1 >= 'A') && (src1 <= 'F')) 
			factor1 = '7'; 
        else 
			return 1; 

		if ((src2 >= '0') && (src2 <= '9')) 
			factor2 = '0'; 
        else if ((src2 >= 'A') && (src2 <= 'F')) 
			factor2 = '7'; 
        else 
			return 1; 

		src1 = src1 - factor1; 
		src2 = src2 - factor2; 
		*hex = (src1 << 4) | src2; 
		hex++;
	} 
	hex -= pair_len;
	return 0; 
}

void CTransCom::OnComsend() 
{
	UpdateData();

	if(m_isComOpen && m_comHandle)
	{
		RV_PTZ_RAW_DATA_H pComData = {0};
		char cData[32];	
		strcpy(cData, m_sendstring.GetBuffer(0));
		CString pData;
		for (int i = 0; i < m_sendstring.GetLength(); i++)
		{
			if (cData[i] == 0x20)
			{

			}
			else
			{
				pData += cData[i];
			}
		}
		short iRet = asc_hex((unsigned char*)pData.GetBuffer(0), (unsigned char*)pComData.acData, pData.GetLength() / 2);

		pComData.iLen = pData.GetLength() / 2;
		pComData.iChannel = m_iChannelNO;
		if (1 != iRet)
		{
			BOOL ret = CLIENT_SendTransComData(m_comHandle, (char*)&pComData, sizeof(pComData));
			if(!ret)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
				MessageBox(ConvertString(MSG_TRANSCOM_SENDDATAFAILED));
			}
		}
	}
}

void CTransCom::OnDeleterevice() 
{
	m_recievestring.Empty() ;
	UpdateData(FALSE);
}

void CTransCom::OnDeletesend() 
{
	m_sendstring.Empty();
	UpdateData(false);
}

void CTransCom::OnClose() 
{
	if(m_isComOpen)   //comit close while opened //已打开时执行关闭
	{
		if(m_comHandle)
		{
			int nRet = CLIENT_DestroyTransComChannel(m_comHandle);
			if(nRet)
			{	
				m_comHandle = 0;
			}
			else if(!nRet)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
			}
		}
	}
	
	CDialog::OnClose();
}
