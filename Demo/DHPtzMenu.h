#if !defined(AFX_DHPTZMENU_H__E69A7087_FF96_4279_914D_81B33D406B2B__INCLUDED_)
#define AFX_DHPTZMENU_H__E69A7087_FF96_4279_914D_81B33D406B2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DHPtzMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDHPtzMenu dialog

class CDHPtzMenu : public CDialog
{
	LONG m_DeviceID;
	int m_Channel;
// Construction
public:
	CDHPtzMenu(CWnd* pParent = NULL);   // standard constructor

	void SetPtzParam(LONG iHandle, int iChannel);
	void PtzMemuControl(DWORD dwCommand);
// Dialog Data
	//{{AFX_DATA(CDHPtzMenu)
	enum { IDD = IDD_DHPTZ_MENU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHPtzMenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDHPtzMenu)
	afx_msg void OnOprCancel();
	afx_msg void OnOprClosemenu();
	afx_msg void OnOprDown();
	afx_msg void OnOprLeft();
	afx_msg void OnOprOk();
	afx_msg void OnOprOpenmenu();
	afx_msg void OnOprRight();
	afx_msg void OnOprUp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DHPTZMENU_H__E69A7087_FF96_4279_914D_81B33D406B2B__INCLUDED_)
