#pragma once
#include "afxwin.h"
#include "Scheduler.h"
#include <list>


// SelDepDlg dialog

class SelDepDlg : public CDialog
{
	DECLARE_DYNAMIC(SelDepDlg)

public:
	SelDepDlg(Scheduler::actData *action, CWnd* pParent = NULL);   // standard constructor
	void getFileString(CString &file);
	virtual ~SelDepDlg();

// Dialog Data
	enum { IDD = IDD_SELDEP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListBox m_fileList;
	CString m_filename;
	Scheduler::actData *m_actData;
public:
	afx_msg void OnBnClickedOk();
};
