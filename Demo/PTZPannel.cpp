// PTZPannel.cpp : implementation file
//

#include "stdafx.h"
#include "netsdkdemo.h"
#include "PTZPannel.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTZPannel dialog


CPTZPannel::CPTZPannel(CWnd* pParent /*=NULL*/)
	: CDialog(CPTZPannel::IDD, pParent)
{
//	m_myBrush.CreateSolidBrush(RGB(140,140,255));
	m_myBrush.CreateSolidBrush(RGB(100,130,100));
	//{{AFX_DATA_INIT(CPTZPannel)
	m_ptz_data = 0;
	//}}AFX_DATA_INIT
}


void CPTZPannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPTZPannel)
	DDX_Control(pDX, IDC_ZOOM_WIDE, m_zoom_wide);
	DDX_Control(pDX, IDC_ZOOM_TELE, m_zoom_tele);
	DDX_Control(pDX, IDC_PTZ_UP, m_ptz_up);
	DDX_Control(pDX, IDC_PTZ_RIGHTUP, m_ptz_rightup);
	DDX_Control(pDX, IDC_PTZ_RIGHTDOWN, m_ptz_rightdown);
	DDX_Control(pDX, IDC_PTZ_RIGHT, m_ptz_right);
	DDX_Control(pDX, IDC_PTZ_LEFTUP, m_ptz_leftup);
	DDX_Control(pDX, IDC_PTZ_LEFTDOWN, m_ptz_leftdown);
	DDX_Control(pDX, IDC_PTZ_LEFT, m_ptz_left);
	DDX_Control(pDX, IDC_PTZ_DOWN, m_ptz_down);
	DDX_Control(pDX, IDC_IRIS_OPEN, m_iris_open);
	DDX_Control(pDX, IDC_IRIS_CLOSE, m_iris_close);
	DDX_Control(pDX, IDC_FOCUS_NEAR, m_focus_near);
	DDX_Control(pDX, IDC_FOCUS_FAR, m_focus_far);
	DDX_Text(pDX, IDC_PTZ_DATA, m_ptz_data);
	DDV_MinMaxUInt(pDX, m_ptz_data, 1, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPTZPannel, CDialog)
	//{{AFX_MSG_MAP(CPTZPannel)
	ON_BN_CLICKED(IDC_DHPTZCTRL, OnDhptzctrl)
	ON_BN_CLICKED(IDC_EXTPTZCTRL, OnExtptzctrl)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZPannel message handlers

BOOL CPTZPannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	//云台控制控件的命令定义设置
	//the configure of PTZ control commands
	m_ptz_up.SetButtonCommand(RV_PTZ_UP_CONTROL);
	m_ptz_down.SetButtonCommand(RV_PTZ_DOWN_CONTROL);
	m_ptz_left.SetButtonCommand(RV_PTZ_LEFT_CONTROL);
	m_ptz_right.SetButtonCommand(RV_PTZ_RIGHT_CONTROL);
	m_zoom_wide.SetButtonCommand(RV_PTZ_ZOOM_DEC_CONTROL);
	m_zoom_tele.SetButtonCommand(RV_PTZ_ZOOM_ADD_CONTROL);
	m_focus_near.SetButtonCommand(RV_PTZ_FOCUS_DEC_CONTROL);
	m_focus_far.SetButtonCommand(RV_PTZ_FOCUS_ADD_CONTROL);
	m_iris_open.SetButtonCommand(RV_PTZ_APERTURE_ADD_CONTROL);
	m_iris_close.SetButtonCommand(RV_PTZ_APERTURE_DEC_CONTROL);
	
	m_ptz_rightup.SetButtonCommand(RV_EXTPTZ_RIGHTTOP);
	m_ptz_rightdown.SetButtonCommand(RV_EXTPTZ_RIGHTDOWN);
	m_ptz_leftup.SetButtonCommand(RV_EXTPTZ_LEFTTOP);
	m_ptz_leftdown.SetButtonCommand(RV_EXTPTZ_LEFTDOWN);
	
	m_bPTZCtrl = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPTZPannel::SendPtzControl(int type, BOOL stop)
{
	BOOL b = FALSE;
	int nParam = GetDlgItemInt(IDC_PTZ_DATA, &b, FALSE);
	if (b && nParam > 0 && nParam < 9)
	{
		((CNetSDKDemoDlg *)GetParent())->PtzControl(type, stop, nParam);
	}
	else
	{
		((CNetSDKDemoDlg *)GetParent())->PtzControl(type, stop, 5);
	}
}

void CPTZPannel::OnDhptzctrl() 
{
	((CNetSDKDemoDlg *)GetParent())->Dhptzctrl();
}

void CPTZPannel::OnExtptzctrl() 
{
	((CNetSDKDemoDlg *)GetParent())->Extptzctrl();
}

HBRUSH CPTZPannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() == IDC_PARAM ||
		pWnd->GetDlgCtrlID() == IDC_ZOOM ||
		pWnd->GetDlgCtrlID() == IDC_FOCUS ||
		pWnd->GetDlgCtrlID() == IDC_IRIS) 
	{
		pDC->SetBkMode(TRANSPARENT);
	}

	if (pWnd->GetDlgCtrlID() != IDC_PTZ_DATA)
	{	
		pDC->SetBkMode(TRANSPARENT);
		return m_myBrush;
	}
	return hbr;
}

BOOL CPTZPannel::PreTranslateMessage(MSG* pMsg) 
{
	if (WM_KEYDOWN == pMsg->message && 
		(VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
