// RPane.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "RPane.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


// RPane

IMPLEMENT_DYNAMIC(RPane, CDockablePane)

RPane::RPane()
{

}

RPane::~RPane()
{
}


BEGIN_MESSAGE_MAP(RPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// RPane message handlers

int RPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);
	CRect rectClient(0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	// Create output pane:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_text.Create(dwStyle, rectClient, this, 1))
	{
		TRACE0("Failed to create RPane text\n");
		return -1;      // fail to create
	}

	m_text.SetFont(&m_Font);

	return 0;
}

void RPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	m_text.SetWindowPos(NULL, rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER );
}

void RPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_text.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void RPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_text.SetFocus();
}


void RPane::setText(const string &text)
{
	// First, empty current file data
	m_text.ResetContent();

	// Now parse cnf data line by line and write to RPane
	stringstream ss(text);
	while (ss)
	{
		string temp;
		getline(ss, temp);
		CString tempW(temp.c_str());
		//MessageBox(tempW);

		m_text.AddString(tempW);
	}
}

void RPane::clear()
{
	m_text.ResetContent();
}
