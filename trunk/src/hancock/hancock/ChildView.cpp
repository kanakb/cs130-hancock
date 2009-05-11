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

// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "hancock.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CChildView

CChildView::CChildView(HancockLog *log)
: m_log(log), m_curDir(_T("")), m_curFile(_T(""))
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, ID_LIST_1, &CChildView::OnChangeFileList)
END_MESSAGE_MAP()



// CChildView message handlers


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create MPane UI features
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;

	m_wndWatch.Create(dwStyle, rectDummy, this, ID_LIST_1);
	m_wndWatch.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndWatch.InsertColumn(0, _T("File/Folder"), LVCFMT_LEFT, 100);
	m_wndWatch.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 100);

	// TODO: get rid of this and replace with something that updates when the folder changes
	CString fn = _T("File");
	CString tp = _T("Type");
	for (int i = 0; i < 5; i++)
	{
		char ch = '0' + i;
		CString fntemp = fn + ch;
		CString tptemp = tp + ch;
		m_wndWatch.InsertItem(i, fntemp);
		m_wndWatch.SetItemText(i, 1, tptemp);
	}

	return 0;
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Update MPane list
	CRect rectTree;
	m_wndWatch.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	// Update MPane list
	CWnd::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	m_wndWatch.SetWindowPos(NULL, rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

// Update list of files with new folder name
void CChildView::updateFolder(CString newFolder)
{
	// TODO: replace with an actual list update
	m_curDir = newFolder;
	//MessageBox(newFolder);
}

void CChildView::OnChangeFileList(NMHDR * pNotifyStruct, LRESULT * result)
{
	// TODO: replace with an actual file update
	//MessageBox(_T("Test"));
	*result = 0;
}