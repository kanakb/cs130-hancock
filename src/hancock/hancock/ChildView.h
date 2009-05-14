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

// ChildView.h : interface of the CChildView class
//


#pragma once

#include "log.h"
#include "RPane.h"

#define ID_LIST_1 (WM_USER + 300)
#define ID_RPANE_1 (WM_USER + 301)

//next = 302

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView(HancockLog *log, RPane *rPane);

// Attributes
public:

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeFileList(NMHDR * pNotifyStruct, LRESULT * result);

// Implementation
public:
	void updateFolder(CString newFolder);
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	CMFCListCtrl m_wndWatch;
	HancockLog *m_log;
	RPane *m_rPane;
	CString m_curDir;
	CString m_curFile;
};

