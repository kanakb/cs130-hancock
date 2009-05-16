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
#include <map>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CChildView

CChildView::CChildView(HancockLog *log, RPane *rPane, MPane *mPane)
: m_log(log), m_rPane(rPane), m_mPane(mPane)
{
	m_curDir = _T("");
	m_curFile = _T("");
	m_relabeled = TRUE;
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
	m_wndWatch.ModifyStyle(0, LVS_SINGLESEL);
	m_wndWatch.InsertColumn(0, _T("File/Folder"), LVCFMT_LEFT, 200);
	m_wndWatch.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 200);

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
void CChildView::updateFolder(const CString &newFolder)
{
	if (newFolder == _T(""))
		return;

	m_curDir = newFolder;
	CT2CA dir(newFolder);
	m_mPane->AssocToDir(std::string(dir));
	recalcList();
	//MessageBox(newFolder);
}

// Gets currently selected item (if changed) and gets cnf data (if available)
void CChildView::OnChangeFileList(NMHDR * pNotifyStruct, LRESULT * result)
{
	POSITION pos = m_wndWatch.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_wndWatch.GetNextSelectedItem(pos);
		CString itemText = m_wndWatch.GetItemText(nItem, 0);
		if ((m_curFile != itemText || m_relabeled) && itemText != _T(""))
		{
			m_relabeled = FALSE;
			m_curFile = itemText;
			CT2CA filename(itemText);
			std::string data = m_mPane->getCnfData(std::string(filename));
			m_rPane->setText(data);
		}
	}
	*result = 0;
}

void CChildView::recalcList()
{
	// clear the file list
	m_wndWatch.DeleteAllItems();

	// get map containing all files
	std::map<int,set<string>*>* pMap = m_mPane->getFileList();

	// iterate by file type
	std::map<int,set<string>*>::iterator map_it = pMap->begin();
	for (; map_it != pMap->end(); map_it++)
	{
		// iterate by file
		std::set<string>::iterator set_it = map_it->second->begin();
		for (int i = 0; set_it != map_it->second->end(); set_it++)
		{
			CString temp(set_it->c_str());
			m_wndWatch.InsertItem(i, temp);
			setFileType(i, map_it->first);
			i++;
		}
	}
}

// Helper function to fill in types of each file
void CChildView::setFileType(int index, int type)
{
	CString fileType;
	getTypeFromCode(type, fileType);
	m_wndWatch.SetItemText(index, 1, fileType);
}

// Wrapper function for labelFileAsFlag
void CChildView::updateFile(int type)
{
	POSITION pos = m_wndWatch.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_wndWatch.GetNextSelectedItem(pos);
		CString itemText = m_wndWatch.GetItemText(nItem, 0);
		//MessageBox(itemText);
		CT2CA filename(itemText);
		m_mPane->labelFileAsFlag(type, std::string(filename));
		m_relabeled = TRUE;
		recalcList();
		m_rPane->clear();

		// Log action
		CString logLabel;
		getTypeFromCode(type, logLabel);
		logLabel = _T("Labeled ") + itemText + _T(" as ") + logLabel;
		CT2CA asciilog(logLabel);
		m_log->write(std::string(asciilog));
	}
}

void CChildView::setRelabeled(BOOL status)
{
	m_relabeled = status;
}

// This function gets the string associated with a type ID
void CChildView::getTypeFromCode(int type, CString &name)
{
	switch(type)
	{
	case UNKNOWN:
		name = _T("Unclassified");
		break;
	case GOODWARE:
		name = _T("Goodware");
		break;
	case MALWARE:
		name = _T("Malware");
		break;
	case PPM:
		name = _T("Preprocessed Malware");
		break;
	case MODEL:
		name = _T("Model");
		break;
	case SIGNATURE:
		name = _T("Find Signatures Output");
		break;
	case STUBMAP:
		name = _T("Stub Map");
		break;
	case CLUSTER:
		name = _T("Cluster");
		break;
	case INDEX:
		name = _T("Index");
		break;
	default:
		name = _T("");
		break;
	}
}
