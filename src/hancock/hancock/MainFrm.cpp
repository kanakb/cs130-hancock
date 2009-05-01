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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "hancock.h"

#include "MainFrm.h"
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

//next = 127

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(WM_GOODWARE, &CMainFrame::OnViewGoodware)
	ON_COMMAND(WM_MODEL, &CMainFrame::OnViewModel)
	ON_COMMAND(WM_INDEX, &CMainFrame::OnViewIndex)
	ON_COMMAND(WM_MALWARE, &CMainFrame::OnViewMalware)
	ON_COMMAND(WM_PREMALWARE, &CMainFrame::OnViewPreMalware)
	ON_COMMAND(WM_CLUSTER, &CMainFrame::OnViewCluster)
	ON_COMMAND(WM_STUBMAP, &CMainFrame::OnViewStubMap)
	ON_COMMAND(WM_FINDSIGS, &CMainFrame::OnViewFindSigs)
	ON_COMMAND(WM_UNCLASSIFIED, &CMainFrame::OnViewOther)
	ON_UPDATE_COMMAND_UI(WM_GOODWARE, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_MODEL, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_INDEX, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_MALWARE, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_PREMALWARE, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_CLUSTER, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_STUBMAP, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_FINDSIGS, &CMainFrame::OnUpdateViewFiles)
	ON_UPDATE_COMMAND_UI(WM_UNCLASSIFIED, &CMainFrame::OnUpdateViewFiles)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

	// set the visual style to be used the by the visual manager
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// Create and setup "Outlook" navigation bar:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 250))
	{
		TRACE0("Failed to create navigation pane\n");
		return -1;      // fail to create
	}

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// Load panel images:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// Init main button:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, strTemp, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, strTemp, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, strTemp, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, strTemp, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

	// Add "Home" category with "File Types" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_ACTIONS);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// Add "Tools" category
	bNameValid = strTemp.LoadStringW(IDS_RIBBON_TOOLS);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryTools = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// Create "View" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelClipboard = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PASTE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPaste = new CMFCRibbonButton(ID_EDIT_PASTE, strTemp, 0, 0);
	pPanelClipboard->Add(pBtnPaste);

	bNameValid = strTemp.LoadString(IDS_RIBBON_CUT);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_CUT, strTemp, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_COPY);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_COPY, strTemp, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SELECTALL);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_SELECT_ALL, strTemp, -1));

	// Create and add a "File Types" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILETYPES);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));

	// Add goodware selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_GOODWARE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnGoodware = new CMFCRibbonButton(WM_GOODWARE, strTemp, 0, 1);

	// Can extract buffers from goodware
	bNameValid = strTemp.LoadString(IDS_RIBBON_EXTRBUFFERS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnExtractBuffers = new CMFCRibbonButton(WM_EXTRBUFFERS, strTemp);
	pBtnGoodware->AddSubItem(pBtnExtractBuffers);

	// Can make a model from goodware
	bNameValid = strTemp.LoadString(IDS_RIBBON_MAKEMODEL);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnMakeModel = new CMFCRibbonButton(WM_MAKEMODEL, strTemp);
	pBtnGoodware->AddSubItem(pBtnMakeModel);

	// Can make an index from goodware
	bNameValid = strTemp.LoadString(IDS_RIBBON_MAKEINDEX);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnMakeIndex = new CMFCRibbonButton(WM_MAKEINDEX, strTemp);
	pBtnGoodware->AddSubItem(pBtnMakeIndex);

	// Can label as goodware
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELGOOD);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelGood = new CMFCRibbonButton(WM_LABELGOOD, strTemp);
	pBtnGoodware->AddSubItem(pBtnLabelGood);

	// Add Goodware button to panel
	pPanelView->Add(pBtnGoodware);

	// Add Model selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_MODELS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnModels = new CMFCRibbonButton(WM_MODEL, strTemp, 0, 1);

	// Can prune a model
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRUNE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrune = new CMFCRibbonButton(WM_PRUNE, strTemp);
	pBtnModels->AddSubItem(pBtnPrune);

	// Can merge 2 models
	bNameValid = strTemp.LoadString(IDS_RIBBON_MERGE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnMerge = new CMFCRibbonButton(WM_MERGE, strTemp);
	pBtnModels->AddSubItem(pBtnMerge);

	// Can compile a model
	bNameValid = strTemp.LoadString(IDS_RIBBON_COMPILE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnCompile = new CMFCRibbonButton(WM_COMPILE, strTemp);
	pBtnModels->AddSubItem(pBtnCompile);

	// Can make a stub map
	bNameValid = strTemp.LoadString(IDS_RIBBON_MAKESTUB);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnMakeStubMap = new CMFCRibbonButton(WM_MAKESTUB, strTemp);
	pBtnModels->AddSubItem(pBtnMakeStubMap);

	// Can label as a model
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELMODEL);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelModel = new CMFCRibbonButton(WM_LABELMODEL, strTemp);
	pBtnModels->AddSubItem(pBtnLabelModel);

	// Add Model button to panel
	pPanelView->Add(pBtnModels);

	// Add index selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_INDECES);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnIndeces = new CMFCRibbonButton(WM_INDEX, strTemp, 1, 1);

	// Can find signatures from an index
	bNameValid = strTemp.LoadString(IDS_RIBBON_LOCSIGS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLocSigs = new CMFCRibbonButton(WM_LOCSIGS, strTemp);
	pBtnIndeces->AddSubItem(pBtnLocSigs);

	// Can label as an index
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELINDEX);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelIndex = new CMFCRibbonButton(WM_LABELINDEX, strTemp);
	pBtnIndeces->AddSubItem(pBtnLabelIndex);

	// Add index button to panel
	pPanelView->Add(pBtnIndeces);

	// Add malware selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_MALWARE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnMalware = new CMFCRibbonButton(WM_MALWARE, strTemp, 1, 1);

	// Can preprocess malware
	bNameValid = strTemp.LoadString(IDS_RIBBON_PREPROC);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPreprocess = new CMFCRibbonButton(WM_PREPROC, strTemp);
	pBtnMalware->AddSubItem(pBtnPreprocess);

	// Can label as malware
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELMALWARE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelMalware = new CMFCRibbonButton(WM_LABELMALWARE, strTemp);
	pBtnMalware->AddSubItem(pBtnLabelMalware);

	// Add malware button to panel
	pPanelView->Add(pBtnMalware);

	// Add preprocessed malware selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_PREMALWARE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPreMalware = new CMFCRibbonButton(WM_PREMALWARE, strTemp, 2, 1);

	// Can create a clustering
	bNameValid = strTemp.LoadString(IDS_RIBBON_CLSTFILES);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnClusterFiles = new CMFCRibbonButton(WM_CLSTFILES, strTemp);
	pBtnPreMalware->AddSubItem(pBtnClusterFiles);

	// Can label as preprocessed malware
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELPREMALWARE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelPreMalware = new CMFCRibbonButton(WM_LABELPREMALWARE, strTemp);
	pBtnPreMalware->AddSubItem(pBtnLabelPreMalware);

	// Add preprocessed malware button to panel
	pPanelView->Add(pBtnPreMalware);

	// Add clustering selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_CLUSTERINGS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnClusterings = new CMFCRibbonButton(WM_CLUSTER, strTemp, 2, 1);

	// Can create stub maps from clusterings
	bNameValid = strTemp.LoadString(IDS_RIBBON_MAKESTUB);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnMakeStubMapClst = new CMFCRibbonButton(WM_MAKESTUB, strTemp);
	pBtnClusterings->AddSubItem(pBtnMakeStubMapClst);

	// Can label as a clustering
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELCLUSTER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelCluster = new CMFCRibbonButton(WM_LABELCLUSTER, strTemp);
	pBtnClusterings->AddSubItem(pBtnLabelCluster);

	// Add clustering button to panel
	pPanelView->Add(pBtnClusterings);

	// Add stub map selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_STUBMAPS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnStubmaps = new CMFCRibbonButton(WM_STUBMAP, strTemp, 2, 1);

	// Can find signatures from stub maps
	bNameValid = strTemp.LoadString(IDS_RIBBON_LOCSIGS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLocSigsSM = new CMFCRibbonButton(WM_LOCSIGS, strTemp);
	pBtnStubmaps->AddSubItem(pBtnLocSigsSM);

	// Can label as a stub map
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELSTUBMAP);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelStubmap = new CMFCRibbonButton(WM_LABELSTUBMAP, strTemp);
	pBtnStubmaps->AddSubItem(pBtnLabelStubmap);

	// Add stub map button to panel
	pPanelView->Add(pBtnStubmaps);

	// Add find signature output selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_FINDOUTPUT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnFOutput = new CMFCRibbonButton(WM_FINDSIGS, strTemp, 3, 1);

	// Can label as find signatures output
	bNameValid = strTemp.LoadString(IDS_RIBBON_LABELFINDSIGS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLabelFindSigs = new CMFCRibbonButton(WM_LABELFINDSIGS, strTemp);
	pBtnFOutput->AddSubItem(pBtnLabelFindSigs);

	// Add find signature output button to panel
	pPanelView->Add(pBtnFOutput);

	// Add unclassified files selection button
	bNameValid = strTemp.LoadString(IDS_RIBBON_UNLABELED);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnUnlabeled = new CMFCRibbonButton(WM_UNCLASSIFIED, strTemp, 3, 1);
	pPanelView->Add(pBtnUnlabeled);

	// Add quick access toolbar commands:
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
{
	CWindowDC dc(NULL);

	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // fail to create
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	DWORD dwPaneStyle = AFX_DEFAULT_TOOLBAR_STYLE | CBRS_FLOAT_MULTI;

	// can float, can autohide, can resize, CAN NOT CLOSE
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	//pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

// Toggle viewing of Goodware files
void CMainFrame::OnViewGoodware()
{
	OnViewType(WM_GOODWARE);
}

void CMainFrame::OnViewModel()
{
	OnViewType(WM_MODEL);
}

void CMainFrame::OnViewIndex()
{
	OnViewType(WM_INDEX);
}

void CMainFrame::OnViewMalware()
{
	OnViewType(WM_MALWARE);
}

void CMainFrame::OnViewPreMalware()
{
	OnViewType(WM_PREMALWARE);
}

void CMainFrame::OnViewCluster()
{
	OnViewType(WM_CLUSTER);
}

void CMainFrame::OnViewStubMap()
{
	OnViewType(WM_STUBMAP);
}

void CMainFrame::OnViewFindSigs()
{
	OnViewType(WM_FINDSIGS);
}

void CMainFrame::OnViewOther()
{
	OnViewType(WM_UNCLASSIFIED);
}

void CMainFrame::OnViewType(UINT nID)
{
	if(m_selectedItems.find(nID) == m_selectedItems.end())
		m_selectedItems[nID] = TRUE;
	else
		m_selectedItems[nID] = !m_selectedItems[nID];
	//MessageBox(_T("Clicked!"));
}

// For now, this is responsible for keeping the boxes checked
void CMainFrame::OnUpdateViewFiles(CCmdUI* pCmdUI)
{
	if(m_selectedItems.find(pCmdUI->m_nID) != m_selectedItems.end())
		pCmdUI->SetCheck(m_selectedItems[pCmdUI->m_nID]);
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
