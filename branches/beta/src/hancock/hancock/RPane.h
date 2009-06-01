#pragma once
#include "HScrollListBox.h"
#include <string>

// RPane

#define ID_RPANE_BOX (WM_USER + 400)

class RPane : public CDockablePane
{
	DECLARE_DYNAMIC(RPane)

public:
	RPane();
	virtual ~RPane();
	virtual void DoDataExchange(CDataExchange* pDX);
	void setText(const std::string &text);
	void clear();

protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnSize(UINT nType, int cx, int cy);
	void OnPaint();
	void OnSetFocus(CWnd* pOldWnd);
	DECLARE_MESSAGE_MAP()

private:
	CHScrollListBox m_text; // horizontal scroll list box from CodeGuru
	CFont m_Font;
};


