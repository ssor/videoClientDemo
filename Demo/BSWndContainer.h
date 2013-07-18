/*********************************************************************************
 *	类名 :	CBSWndContainer
 *  class name : CBSWndContainer
 *
 *	功能 :	在同一个窗口同时播放多路视频时,完成多窗口界面的一些控制控制。
 *	function :	used to control multi windows when playing multi videos in  one window
 *			
 *			[单/多窗口切换],[全屏],[边框],[窗口按比例缩放],[自动调整宽高比例]
 *			[single/multi windows switch],[full screen],[frame],[zoom window by rate],[auto adjust the rate of width:height]
 *		
 *	作者 :	OLinS
 *	author :	OLinS
 *
 *	时间 :	2003.1.15
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
//视频窗口之间的间隔
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
	// 创建对象(Container)
	// create object(Container)
	BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	///////////////////////////////////////////////////
	// 添加窗口
	// add window
	BOOL AddPage(CWnd *pWnd, BOOL bRepaint = TRUE);

	///////////////////////////////////////////////////
	// 删除窗口(只是从链表中删除,实际对象的必须外部删除) 
	// delete window(just delete it from list, and delete it from out if you want to delete the real object) 
	CWnd *DelPage(CWnd *pWnd);

	///////////////////////////////////////////////////
	// 删除激活窗口
	// delete actived window
	CWnd *DelPage();

	///////////////////////////////////////////////////
	// 设置激活窗口
	// set actived window
	void SetActivePage(CWnd *pWnd, BOOL bRepaint = TRUE);

	///////////////////////////////////////////////////
	// 得到激活窗口
	// get actived window
	CWnd *GetActivePage();

	///////////////////////////////////////////////////
	// 得到后一个窗口
	// get the next window
	CWnd *GetNextPage(CWnd *pWnd);

	///////////////////////////////////////////////////
	// 得到前一个窗口
	// get the previous window
	CWnd *GetPrevPage(CWnd *pWnd);

	///////////////////////////////////////////////////
	//	得到指定序号的窗口
	//	get the specify index window
	CWnd *GetPage(int nIndex);

	///////////////////////////////////////////////////
	//	得到窗口总数
	//	get the total number of windows
	int GetCount() const;

	///////////////////////////////////////////////////
	//	得到最后窗口
	//	get the last window
	CWnd *GetTailPage();

	///////////////////////////////////////////////////
	// 更新窗口
	// update window
	virtual void UpdateWnd();

	///////////////////////////////////////////////////
	//	全屏显示
	//	display full screen
	void SetFullScreen(BOOL bFlag);
	BOOL GetFullScreen();

	///////////////////////////////////////////////////
	//	多屏显示
	//	multi screens display
	void SetMultiScreen(BOOL bFlag);
	BOOL GetMultiScreen();

	//////////////////////////////////////////////////
	//	自动调节尺寸
	//	auto adjust dimension
	void SetAutoAdjustPos(BOOL bFlag);
	BOOL GetAutoAdjustPos();

	//////////////////////////////////////////////////
	//	激活窗口边框
	//	activate window frame
	void SetDrawActivePage(BOOL bFlag,COLORREF clrTopLeft=RGB(255, 0, 0), COLORREF clrBottomRight=RGB(255, 0, 0));
	BOOL GetDrawActivePage();

	//////////////////////////////////////////////////
	//	显示百分比
	//	display percent
	//	40 <= nPortion <=100
	void SetShowPortion(int nPortion=100);
	int  GetShowPortion();

//////////////////////////////////////////////////////////////////////////////////////////////////////
// protected member for derived class
protected:
	
	///////////////////////////////////////////////////
	// 之窗口链表
	// sub windows list
	CList<CWnd *,CWnd *> m_PageList;

	///////////////////////////////////////////////////
	// 激活窗口指针
	// activate window pointer
	CWnd *m_pActivePage;

	///////////////////////////////////////////////////
	// 全屏标记
	// full screen mark
	BOOL m_bFullScreen;

	///////////////////////////////////////////////////
	// 多屏标记
	// multi screen mark
	BOOL m_bMultiScreen;	

	///////////////////////////////////////////////////
	// 自动调整标记
	// auto adjust mark
	BOOL m_bAutoAdjustPos;

	///////////////////////////////////////////////////
	// 边框标记
	// frame mark
	BOOL m_bDrawActive;

	///////////////////////////////////////////////////
	// 显示区域百分比(40-100)
	// display area percent(40-100)
	int	m_nShowPortion; 

////////////////////////////////////////////////////////////////////////////////////////////////////////
// private member for inter user
private:

	///////////////////////////////////////////////////
	//	更新链表,删除其中的无效节点,返回节点个数
	//	update list,delete unavlid nodes,return node number
	int UpdateList();

	///////////////////////////////////////////////////
	//	根据子窗口的序号 和 显示范围 ,得到窗口的位置
	//	get position of the window by the index of sub window and display bound 
	virtual void CalcPageRect(LPRECT lpRect,int nIndex,int nPageCount);

	///////////////////////////////////////////////////
	//	根据预定义的比例得到显示区域(11/8)
	//  get display areas by pre-defined rate(11/8)
	void AdjustRect(LPRECT lpRect);

	///////////////////////////////////////////////////
	//	按比例得到显示区域
	//  get display areas by rate
	void GetShowRect(LPRECT lpRect);

	///////////////////////////////////////////////////
	//	画激活窗口边框
	//  paint actived window frame
	void DrawActivePage(BOOL bFlag);

	///////////////////////////////////////////////////
	//	窗口边框颜色
	//  color of window frame
	COLORREF m_clrTopLeft;
	COLORREF m_clrBottomRight;

	///////////////////////////////////////////////////
	//	全屏时保存原窗口信息,用来恢复窗口
	//  used to restore window when saving primary window infomation on full screen
	WINDOWPLACEMENT _temppl;		//window's placement
	CWnd *			_tempparent;	//window's parent
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_)
