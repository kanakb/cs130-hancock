#pragma once
#include "afxwin.h"
#include "log.h"
#include <list>



// LogUI dialog

class LogUI : public CDialog
{
	DECLARE_DYNAMIC(LogUI)

public:
	LogUI(HancockLog *hlog, CWnd* pParent = NULL);   // standard constructor
	BOOL Create(UINT nID, CWnd * pWnd);
	virtual ~LogUI();

// Dialog Data
	enum { IDD = IDD_LOGUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnLbnSelchangeLoglist();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()
private:
	CButton m_closeBtn;
	CListBox m_logList;
	CEdit m_logText;
	HancockLog *m_log;

	void getLogFiles(list<CString>* fileList); //Populates CString array with
	//contents of Log folder. Returns number of files.


};
