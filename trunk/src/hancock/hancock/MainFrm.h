// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "log.h"
#include "ChildView.h"
#include "CalendarBar.h"
#include "Resource.h"
#include <map>

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); }
};

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutlookBar       m_wndNavigationBar;
	CMFCShellTreeCtrl m_wndTree;
	CCalendarBar      m_wndCalendar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);

	// Action handling functions
	afx_msg void OnViewGoodware();
	afx_msg void OnViewModel();
	afx_msg void OnViewIndex();
	afx_msg void OnViewMalware();
	afx_msg void OnViewPreMalware();
	afx_msg void OnViewCluster();
	afx_msg void OnViewStubMap();
	afx_msg void OnViewFindSigs();
	afx_msg void OnViewOther();
	afx_msg void OnMakeModel();
	afx_msg void OnExtractBuffers();
	afx_msg void OnMakeIndex();
	afx_msg void OnLabelGood();
	afx_msg void OnPrune();
	afx_msg void OnMerge();
	afx_msg void OnModelCompile();
	afx_msg void OnMakeStub();
	afx_msg void OnLabelModel();
	afx_msg void OnFindSigs();
	afx_msg void OnLabelIndex();
	afx_msg void OnPreprocess();
	afx_msg void OnLabelMalware();
	afx_msg void OnClusterFiles();
	afx_msg void OnLabelPreMalware();
	afx_msg void OnLabelCluster();
	afx_msg void OnLabelStubMap();
	afx_msg void OnLabelFindSigs();
	afx_msg void OnViewScheduler();
	afx_msg void OnViewLogger();
	afx_msg void OnSaveLog();
	afx_msg void OnViewType(UINT nID);
	afx_msg void OnUpdateViewFiles(CCmdUI* pCmdUI);
	afx_msg void OnChangeFolder(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();
	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth);

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
private:
	std::map<UINT, BOOL> m_selectedItems;
	HancockLog m_log;
};


