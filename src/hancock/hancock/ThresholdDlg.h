#pragma once
#include "afxwin.h"
#include "log.h"


// ThresholdDlg dialog

class ThresholdDlg : public CDialog
{
	DECLARE_DYNAMIC(ThresholdDlg)

public:
	ThresholdDlg(HancockLog *log, CWnd* pParent = NULL);   // standard constructor
	virtual ~ThresholdDlg();

// Dialog Data
	enum { IDD = IDD_THRESHOLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_val;
	HancockLog *m_log;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
