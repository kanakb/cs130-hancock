#pragma once
#include "afxwin.h"
#include "log.h"
#include "Scheduler.h"


// ThresholdDlg dialog

class ThresholdDlg : public CDialog
{
	DECLARE_DYNAMIC(ThresholdDlg)

public:
	ThresholdDlg(Scheduler *sched, HancockLog *log, CWnd* pParent = NULL);   // standard constructor
	virtual ~ThresholdDlg();

// Dialog Data
	enum { IDD = IDD_THRESHOLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_val;
	HancockLog *m_log;
	Scheduler *m_sched;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
