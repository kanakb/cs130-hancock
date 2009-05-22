#pragma once
#include "afxwin.h"


// MakeIndexDlg dialog

class MakeIndexDlg : public CDialog
{
	DECLARE_DYNAMIC(MakeIndexDlg)

public:
	MakeIndexDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MakeIndexDlg();

// Dialog Data
	enum { IDD = IDD_MAKEINDEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
	afx_msg void OnBnClickedBtnSelout1();
private:
	CEdit m_input;
	CEdit m_output;
	CComboBox m_mode;
};
