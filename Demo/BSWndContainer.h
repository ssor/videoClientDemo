/*********************************************************************************
 *	���� :	CBSWndContainer
 *  class name : CBSWndContainer
 *
 *	���� :	��ͬһ������ͬʱ���Ŷ�·��Ƶʱ,��ɶര�ڽ����һЩ���ƿ��ơ�
 *	function :	used to control multi windows when playing multi videos in  one window
 *			
 *			[��/�ര���л�],[ȫ��],[�߿�],[���ڰ���������],[�Զ�������߱���]
 *			[single/multi windows switch],[full screen],[frame],[zoom window by rate],[auto adjust the rate of width:height]
 *		
 *	���� :	OLinS
 *	author :	OLinS
 *
 *	ʱ�� :	2003.1.15
 *	time :	2003.1.15
 *												
 *********************************************************************************
 */


#if !defined(AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_)
#define AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSWndContainer.h : header file
//
//��Ƶ����֮��ļ��
//time span between video windows
#define WINDOW_SPACE  1

/////////////////////////////////////////////////////////////////////////////
// CBSWndContainer window
#include <afxtempl.h>

class CBSWndContainer : public CWnd
{
// Construction
public:
	CBSWndContainer();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBSWndContainer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBSWndContainer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBSWndContainer)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////
// public interface member
public:

	///////////////////////////////////////////////////
	// ��������(Container)
	// create object(Container)
	BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	///////////////////////////////////////////////////
	// ��Ӵ���
	// add window
	BOOL AddPage(CWnd *pWnd, BOOL bRepaint = TRUE);

	///////////////////////////////////////////////////
	// ɾ������(ֻ�Ǵ�������ɾ��,ʵ�ʶ���ı����ⲿɾ��) 
	// delete window(just delete it from list, and delete it from out if you want to delete the real object) 
	CWnd *DelPage(CWnd *pWnd);

	///////////////////////////////////////////////////
	// ɾ�������
	// delete actived window
	CWnd *DelPage();

	///////////////////////////////////////////////////
	// ���ü����
	// set actived window
	void SetActivePage(CWnd *pWnd, BOOL bRepaint = TRUE);

	///////////////////////////////////////////////////
	// �õ������
	// get actived window
	CWnd *GetActivePage();

	///////////////////////////////////////////////////
	// �õ���һ������
	// get the next window
	CWnd *GetNextPage(CWnd *pWnd);

	///////////////////////////////////////////////////
	// �õ�ǰһ������
	// get the previous window
	CWnd *GetPrevPage(CWnd *pWnd);

	///////////////////////////////////////////////////
	//	�õ�ָ����ŵĴ���
	//	get the specify index window
	CWnd *GetPage(int nIndex);

	///////////////////////////////////////////////////
	//	�õ���������
	//	get the total number of windows
	int GetCount() const;

	///////////////////////////////////////////////////
	//	�õ���󴰿�
	//	get the last window
	CWnd *GetTailPage();

	///////////////////////////////////////////////////
	// ���´���
	// update window
	virtual void UpdateWnd();

	///////////////////////////////////////////////////
	//	ȫ����ʾ
	//	display full screen
	void SetFullScreen(BOOL bFlag);
	BOOL GetFullScreen();

	///////////////////////////////////////////////////
	//	������ʾ
	//	multi screens display
	void SetMultiScreen(BOOL bFlag);
	BOOL GetMultiScreen();

	//////////////////////////////////////////////////
	//	�Զ����ڳߴ�
	//	auto adjust dimension
	void SetAutoAdjustPos(BOOL bFlag);
	BOOL GetAutoAdjustPos();

	//////////////////////////////////////////////////
	//	����ڱ߿�
	//	activate window frame
	void SetDrawActivePage(BOOL bFlag,COLORREF clrTopLeft=RGB(255, 0, 0), COLORREF clrBottomRight=RGB(255, 0, 0));
	BOOL GetDrawActivePage();

	//////////////////////////////////////////////////
	//	��ʾ�ٷֱ�
	//	display percent
	//	40 <= nPortion <=100
	void SetShowPortion(int nPortion=100);
	int  GetShowPortion();

//////////////////////////////////////////////////////////////////////////////////////////////////////
// protected member for derived class
protected:
	
	///////////////////////////////////////////////////
	// ֮��������
	// sub windows list
	CList<CWnd *,CWnd *> m_PageList;

	///////////////////////////////////////////////////
	// �����ָ��
	// activate window pointer
	CWnd *m_pActivePage;

	///////////////////////////////////////////////////
	// ȫ�����
	// full screen mark
	BOOL m_bFullScreen;

	///////////////////////////////////////////////////
	// �������
	// multi screen mark
	BOOL m_bMultiScreen;	

	///////////////////////////////////////////////////
	// �Զ��������
	// auto adjust mark
	BOOL m_bAutoAdjustPos;

	///////////////////////////////////////////////////
	// �߿���
	// frame mark
	BOOL m_bDrawActive;

	///////////////////////////////////////////////////
	// ��ʾ����ٷֱ�(40-100)
	// display area percent(40-100)
	int	m_nShowPortion; 

////////////////////////////////////////////////////////////////////////////////////////////////////////
// private member for inter user
private:

	///////////////////////////////////////////////////
	//	��������,ɾ�����е���Ч�ڵ�,���ؽڵ����
	//	update list,delete unavlid nodes,return node number
	int UpdateList();

	///////////////////////////////////////////////////
	//	�����Ӵ��ڵ���� �� ��ʾ��Χ ,�õ����ڵ�λ��
	//	get position of the window by the index of sub window and display bound 
	virtual void CalcPageRect(LPRECT lpRect,int nIndex,int nPageCount);

	///////////////////////////////////////////////////
	//	����Ԥ����ı����õ���ʾ����(11/8)
	//  get display areas by pre-defined rate(11/8)
	void AdjustRect(LPRECT lpRect);

	///////////////////////////////////////////////////
	//	�������õ���ʾ����
	//  get display areas by rate
	void GetShowRect(LPRECT lpRect);

	///////////////////////////////////////////////////
	//	������ڱ߿�
	//  paint actived window frame
	void DrawActivePage(BOOL bFlag);

	///////////////////////////////////////////////////
	//	���ڱ߿���ɫ
	//  color of window frame
	COLORREF m_clrTopLeft;
	COLORREF m_clrBottomRight;

	///////////////////////////////////////////////////
	//	ȫ��ʱ����ԭ������Ϣ,�����ָ�����
	//  used to restore window when saving primary window infomation on full screen
	WINDOWPLACEMENT _temppl;		//window's placement
	CWnd *			_tempparent;	//window's parent
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_)
