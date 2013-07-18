// DHExtPtzCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "netsdkdemo.h"
#include "DHExtPtzCtrl.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHExtPtzCtrl dialog


CDHExtPtzCtrl::CDHExtPtzCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDHExtPtzCtrl::IDD, pParent)
{
	m_DeviceID = 0;
	m_Channel = 0;
	m_presetPoint = 0;
	m_cruiseGroup = 0;
	m_modeNo = 0;
	//{{AFX_DATA_INIT(CDHExtPtzCtrl)
	//}}AFX_DATA_INIT
}


void CDHExtPtzCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDHExtPtzCtrl)
	DDX_Control(pDX, IDC_COMBO_AUX_NO, m_auxNosel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDHExtPtzCtrl, CDialog)
	//{{AFX_MSG_MAP(CDHExtPtzCtrl)
	ON_BN_CLICKED(IDC_PRESET_ADD, OnPresetAdd)
	ON_BN_CLICKED(IDC_PRESET_DELE, OnPresetDele)
	ON_BN_CLICKED(IDC_PRESET_SET, OnPresetSet)
	ON_BN_CLICKED(IDC_CRUISE_ADD_POINT, OnCruiseAddPoint)
	ON_BN_CLICKED(IDC_CRUISE_DEL_POINT, OnCruiseDelPoint)
	ON_BN_CLICKED(IDC_CRUISE_DEL_GROUP, OnCruiseDelGroup)
	ON_BN_CLICKED(IDC_START_CRUISE, OnStartCruise)
	ON_BN_CLICKED(IDC_STOP_CRUISE, OnStopCruise)
	ON_BN_CLICKED(IDC_LAMP_ACTIVATE, OnLampActivate)
	ON_BN_CLICKED(IDC_LAMP_DEACTIVATE, OnLampDeactivate)
	ON_BN_CLICKED(IDC_ROTATE_START, OnRotateStart)
	ON_BN_CLICKED(IDC_ROTATE_STOP, OnRotateStop)
	ON_BN_CLICKED(IDC_LINE_SET_LEFT, OnLineSetLeft)
	ON_BN_CLICKED(IDC_LINE_SET_RIGHT, OnLineSetRight)
	ON_BN_CLICKED(IDC_LINE_START, OnLineStart)
	ON_BN_CLICKED(IDC_LINE_STOP, OnLineStop)
	ON_BN_CLICKED(IDC_MODE_SET_BEGIN, OnModeSetBegin)
	ON_BN_CLICKED(IDC_MODE_SET_DELETE, OnModeSetDelete)
	ON_BN_CLICKED(IDC_MODE_SET_END, OnModeSetEnd)
	ON_BN_CLICKED(IDC_MODE_START, OnModeStart)
	ON_BN_CLICKED(IDC_MODE_STOP, OnModeStop)
	ON_BN_CLICKED(IDC_QUERY_ALARM, OnQueryAlarm)
	ON_BN_CLICKED(IDC_FAST_GO, OnFastGo)
	ON_BN_CLICKED(IDC_AUX_OPEN, OnAuxOpen)
	ON_BN_CLICKED(IDC_AUX_CLOSE, OnAuxClose)
	ON_BN_CLICKED(IDC_LIGHT_OPEN, OnLightOpen)
	ON_BN_CLICKED(IDC_LIGHT_CLOSE, OnLightClose)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_TEST2, OnTest2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDHExtPtzCtrl message handlers

BOOL CDHExtPtzCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	SetDlgItemInt(IDC_PRESET_DATA,1);
	SetDlgItemInt(IDC_CRUISE_GROUP,1);
	SetDlgItemInt(IDC_MODE_NO, 1);
	SetDlgItemInt(IDC_POS_X, 0);
	SetDlgItemInt(IDC_POS_Y, 0);
	SetDlgItemInt(IDC_POS_ZOOM, 0);
	
	m_auxNosel.SetCurSel(0);
	return TRUE; 
}

void CDHExtPtzCtrl::SetExtPtzParam(LONG iHandle, int iChannel)
{
	m_DeviceID = iHandle;
	m_Channel = iChannel;
}


void CDHExtPtzCtrl::OnPresetAdd() 
{
	PtzExtControl(RV_PTZ_POINT_SET_CONTROL);
}

void CDHExtPtzCtrl::OnPresetDele() 
{
	PtzExtControl(RV_PTZ_POINT_DEL_CONTROL);
}

void CDHExtPtzCtrl::OnPresetSet() 
{
	PtzExtControl(RV_PTZ_POINT_MOVE_CONTROL);
}

void CDHExtPtzCtrl::PtzExtControl(DWORD dwCommand, DWORD dwParam)
{
	BOOL ret = FALSE;
	BYTE bParam[3] = {0};
	DWORD dwPm[3] = {0};

	if(!m_DeviceID)
	{
		MessageBox(ConvertString(MSG_PTZCTRL_NOCHANNEL));
	}
	
	switch(dwCommand) 
	{
	case RV_PTZ_POINT_MOVE_CONTROL:     //move to //转至
    case RV_PTZ_POINT_SET_CONTROL:     //set //设置
    case RV_PTZ_POINT_DEL_CONTROL:      //delete //删除
		m_presetPoint = GetDlgItemInt(IDC_PRESET_DATA);
		bParam[1] = (BYTE)m_presetPoint;
		break;
	case RV_EXTPTZ_ADDTOLOOP:
	case RV_EXTPTZ_DELFROMLOOP:
		m_presetPoint = GetDlgItemInt(IDC_PRESET_DATA);
		m_cruiseGroup = GetDlgItemInt(IDC_CRUISE_GROUP);
		bParam[0] = (BYTE)m_cruiseGroup;
		bParam[1] = (BYTE)m_presetPoint;
		break;
	case RV_EXTPTZ_CLOSELOOP:
		m_cruiseGroup = GetDlgItemInt(IDC_CRUISE_GROUP);
		bParam[0] = (BYTE)m_cruiseGroup;
		break;
	case RV_PTZ_POINT_LOOP_CONTROL:
		if (0 == dwParam) 
		{
			m_cruiseGroup = GetDlgItemInt(IDC_CRUISE_GROUP);
			bParam[0] = (BYTE)m_cruiseGroup;
			bParam[2] = 76;
		}
		else
		{
			m_cruiseGroup = GetDlgItemInt(IDC_CRUISE_GROUP);
			bParam[0] = (BYTE)m_cruiseGroup;
			bParam[2] = 96;
		}
		break;
	case RV_PTZ_LAMP_CONTROL:
		if (0 == dwParam) 
		{
			//open
			bParam[0] = 0x01;
		}
		else
		{
			//close
			bParam[0] = 0x00;
		}
		break;
	case RV_EXTPTZ_LIGHTCONTROL:
		bParam[0] = GetDlgItemInt(IDC_LIGHT_CONTROLLER);
		bParam[1] = GetDlgItemInt(IDC_LIGHT_NO);
		if (0 == dwParam) 
		{
			//open
			bParam[2] = 1;
		}
		else
		{
			//close
			bParam[2] = 0;
		}
		break;
	case RV_EXTPTZ_STARTPANCRUISE:		//start horize rotate //开始水平旋转	
	case RV_EXTPTZ_STOPPANCRUISE:		//stop horize rotate //停止水平旋转
	case RV_EXTPTZ_SETLEFTBORDER:		//set the left boundary //设置左边界
	case RV_EXTPTZ_SETRIGHTBORDER:		//set right boundary //设置右边界
	case RV_EXTPTZ_STARTLINESCAN:		//start line scan //开始线扫
	case RV_EXTPTZ_CLOSELINESCAN:		//stop line scan //停止线扫	
	case RV_EXTPTZ_SETMODESTART:		//set mode start //设置模式开始	
		break;
	case RV_EXTPTZ_SETMODESTOP:		//sop set mode //设置模式结束
	case RV_EXTPTZ_RUNMODE:			//run mode //运行模式
	case RV_EXTPTZ_STOPMODE:			//stop mode//停止模式
	case RV_EXTPTZ_DELETEMODE:			//clear mode//清除模式
		m_modeNo = GetDlgItemInt(IDC_MODE_NO);
		bParam[0] = (BYTE)m_modeNo;
		break;
//	case DH_EXTPTZ_REVERSECOMM:
//		break;
	case RV_EXTPTZ_AUXIOPEN:
	case RV_EXTPTZ_AUXICLOSE:
		switch(m_auxNosel.GetCurSel())
		{
		case 0:
			m_auxNo = 23;
			break;
		case 1:
			m_auxNo = 24;
			break;
		case 2:
			m_auxNo = 27;
			break;
		case 3:
			m_auxNo = 41;
			break;
		case 4:
			m_auxNo = 43;
			break;
		default:
			return;		
		}
		bParam[0] = m_auxNo;
		break;
	case RV_EXTPTZ_FASTGOTO:
		{
			m_pos_x = GetDlgItemInt(IDC_POS_X);
			m_pos_y = GetDlgItemInt(IDC_POS_Y);
			m_pos_zoom = GetDlgItemInt(IDC_POS_ZOOM);
			dwPm[0] = m_pos_x;
			dwPm[1] = m_pos_y;
			dwPm[2] = m_pos_zoom;
			ret = CLIENT_DHPTZControlEx(m_DeviceID, m_Channel,dwCommand ,dwPm[0],dwPm[1],dwPm[2],FALSE);
			if(!ret)
			{
				((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
				MessageBox(ConvertString(MSG_PTZCTRL_CTRLFAILED));
			}
		}
		break;
	case RV_EXTPTZ_UP_TELE:
		bParam[0] = dwParam;
		break;
	default: 
		return;
	}
	ret = CLIENT_DHPTZControlEx(m_DeviceID, m_Channel,dwCommand ,bParam[0],bParam[1],bParam[2],FALSE);
	if(!ret)
	{
		((CNetSDKDemoDlg *)GetParent())->LastError();//Zhengdh 06.11.24
		MessageBox(ConvertString(MSG_PTZCTRL_CTRLFAILED));
	}
}

void CDHExtPtzCtrl::OnCruiseAddPoint() 
{
	PtzExtControl(RV_EXTPTZ_ADDTOLOOP);
}

void CDHExtPtzCtrl::OnCruiseDelPoint() 
{
	PtzExtControl(RV_EXTPTZ_DELFROMLOOP);
}

void CDHExtPtzCtrl::OnCruiseDelGroup() 
{
	PtzExtControl(RV_EXTPTZ_CLOSELOOP);
}

void CDHExtPtzCtrl::OnStartCruise() 
{
	PtzExtControl(RV_PTZ_POINT_LOOP_CONTROL, 0);
}

void CDHExtPtzCtrl::OnStopCruise() 
{
	PtzExtControl(RV_PTZ_POINT_LOOP_CONTROL, 1);
}

void CDHExtPtzCtrl::OnLampActivate() 
{
	PtzExtControl(RV_PTZ_LAMP_CONTROL, 0);
}

void CDHExtPtzCtrl::OnLampDeactivate() 
{
	PtzExtControl(RV_PTZ_LAMP_CONTROL, 1);
}

void CDHExtPtzCtrl::OnRotateStart() 
{
	PtzExtControl(RV_EXTPTZ_STARTPANCRUISE);
}

void CDHExtPtzCtrl::OnRotateStop() 
{
	PtzExtControl(RV_EXTPTZ_STOPPANCRUISE);
}

void CDHExtPtzCtrl::OnLineSetLeft() 
{
	PtzExtControl(RV_EXTPTZ_SETLEFTBORDER);
}

void CDHExtPtzCtrl::OnLineSetRight() 
{
	PtzExtControl(RV_EXTPTZ_SETRIGHTBORDER);
}

void CDHExtPtzCtrl::OnLineStart() 
{
	PtzExtControl(RV_EXTPTZ_STARTLINESCAN);	
}

void CDHExtPtzCtrl::OnLineStop() 
{
	PtzExtControl(RV_EXTPTZ_CLOSELINESCAN);
}

void CDHExtPtzCtrl::OnModeSetBegin() 
{
	PtzExtControl(RV_EXTPTZ_SETMODESTART);
}

void CDHExtPtzCtrl::OnModeSetDelete() 
{
	PtzExtControl(RV_EXTPTZ_DELETEMODE);
}

void CDHExtPtzCtrl::OnModeSetEnd() 
{
	PtzExtControl(RV_EXTPTZ_SETMODESTOP);
}

void CDHExtPtzCtrl::OnModeStart() 
{
	PtzExtControl(RV_EXTPTZ_RUNMODE);
}

void CDHExtPtzCtrl::OnModeStop() 
{
	PtzExtControl(RV_EXTPTZ_STOPMODE);
}

void CDHExtPtzCtrl::OnQueryAlarm() 
{
//	PtzExtControl(RV_EXTPTZ_REVERSECOMM);
}

void CDHExtPtzCtrl::OnFastGo() 
{
	PtzExtControl(RV_EXTPTZ_FASTGOTO);
}

void CDHExtPtzCtrl::OnAuxOpen() 
{
	PtzExtControl(RV_EXTPTZ_AUXIOPEN);
}

void CDHExtPtzCtrl::OnAuxClose() 
{
	PtzExtControl(RV_EXTPTZ_AUXICLOSE);
}

void CDHExtPtzCtrl::OnLightOpen() 
{
	PtzExtControl(RV_EXTPTZ_LIGHTCONTROL, 0);
}

void CDHExtPtzCtrl::OnLightClose() 
{
	PtzExtControl(RV_EXTPTZ_LIGHTCONTROL, 1);
}

void CDHExtPtzCtrl::OnTest() 
{
	PtzExtControl(RV_EXTPTZ_UP_TELE, 5);
}

void CDHExtPtzCtrl::OnTest2() 
{
	PtzExtControl(RV_PTZ_LAMP_CONTROL, 1);
}
