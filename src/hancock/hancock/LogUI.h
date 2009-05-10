#pragma once
#include "afxwin.h"


// LogUI dialog

class LogUI : public CDialog
{
	DECLARE_DYNAMIC(LogUI)

public:
	LogUI(CWnd* pParent = NULL);   // standard constructor
	virtual ~LogUI();

// Dialog Data
	enum { IDD = IDD_LOGUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnEnChangeLogtext();
	afx_msg void OnLbnSelchangeLoglist();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()
private:
	CButton m_closeBtn;
	CListBox m_logList;
	CEdit m_logText;
};
