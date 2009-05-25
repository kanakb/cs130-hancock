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
#include "LogUI.h"
#include "RPane.h"
#include "MPane.h"
#include "ChildView.h"
#include "CalendarBar.h"
#include "Resource.h"
#include <map>



// Message IDS for my custom actions
#define WM_GOODWARE (WM_USER + 100)
#define WM_MODEL (WM_USER + 101)
#define WM_INDEX (WM_USER + 102)
#define WM_MALWARE (WM_USER + 103)
#define WM_PREMALWARE (WM_USER + 121)
#define WM_CLUSTER (WM_USER + 104)
#define WM_STUBMAP (WM_USER + 105)
#define WM_FINDSIGS (WM_USER + 106)
#define WM_UNCLASSIFIED (WM_USER + 107)
#define WM_MAKEMODEL (WM_USER + 108)
#define WM_EXTRBUFFERS (WM_USER + 109)
#define WM_MAKEINDEX (WM_USER + 110)
#define WM_LABELGOOD (WM_USER + 111)
#define WM_PRUNE (WM_USER + 112)
#define WM_MERGE (WM_USER + 113)
#define WM_COMPILE (WM_USER + 114)
#define WM_MAKESTUB (WM_USER + 115)
#define WM_LABELMODEL (WM_USER + 116)
#define WM_LOCSIGS (WM_USER + 117)
#define WM_LABELINDEX (WM_USER + 118)
#define WM_PREPROC (WM_USER + 119)
#define WM_LABELMALWARE (WM_USER + 120)
#define WM_CLSTFILES (WM_USER + 122)
#define WM_LABELPREMALWARE (WM_USER + 123)
#define WM_LABELCLUSTER (WM_USER + 124)
#define WM_LABELSTUBMAP (WM_USER + 125)
#define WM_LABELFINDSIGS (WM_USER + 126)
#define WM_VIEWSCHED (WM_USER + 127)
#define WM_VIEWLOG (WM_USER + 128)
#define WM_LOGSAVE (WM_USER + 129)
#define ID_CMFCTREECTRL (WM_USER + 130)
#define ID_RPANE_A (WM_USER + 133)
#define WM_FILEDATA (WM_USER + 134)
#define WM_THRESHOLD (WM_USER + 135)

//next = 136

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
	COutlookBar       m_wndNavigationBar;
	CMFCShellTreeCtrl m_wndTree;
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
	afx_msg void OnViewRPane();
	afx_msg void OnSetThreshold();
	afx_msg void OnViewType(UINT nID);
	afx_msg void OnUpdateViewFiles(CCmdUI* pCmdUI);
	afx_msg void OnChangeFolder(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();
	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, int nInitialWidth);

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
private:
	std::map<UINT, BOOL> m_selectedItems;
	RPane m_rPane;
	MPane m_mPane;
	HancockLog m_log;
	LogUI *m_logUI;
};


