#pragma once
#include <string>

// RPane

class RPane : public CDockablePane
{
	DECLARE_DYNAMIC(RPane)

public:
	RPane();
	virtual ~RPane();
	void setText(const std::string &text);
	void clear();

protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnSize(UINT nType, int cx, int cy);
	void OnPaint();
	void OnSetFocus(CWnd* pOldWnd);
	DECLARE_MESSAGE_MAP()

private:
	CListBox m_text;
	CFont m_Font;
};


