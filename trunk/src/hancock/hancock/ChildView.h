// ChildView.h : interface of the CChildView class
//


#pragma once

#include "log.h"
#include "RPane.h"
#include "MPane.h"

#define ID_LIST_1 (WM_USER + 300)
#define ID_RPANE_1 (WM_USER + 301)

//next = 302

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView(HancockLog *log, RPane *rPane, MPane *mPane);

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
	void updateFolder(const CString &newFolder);
	void updateFile(int type);
	void recalcList();
	void setRelabeled(BOOL status);
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	void setFileType(int index, int type);
	void getTypeFromCode(int type, CString &name);
	CListCtrl m_wndWatch;
	HancockLog *m_log;
	RPane *m_rPane;
	MPane *m_mPane;
	CString m_curDir;
	CString m_curFile;
	BOOL m_relabeled;
};

