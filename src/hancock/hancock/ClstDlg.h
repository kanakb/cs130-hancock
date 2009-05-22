#pragma once
#include "afxwin.h"


// ClstDlg dialog

class ClstDlg : public CDialog
{
	DECLARE_DYNAMIC(ClstDlg)

public:
	ClstDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ClstDlg();

// Dialog Data
	enum { IDD = IDD_CLSTFILES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCrcfg();
	afx_msg void OnBnClickedBtnEcfg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
private:
	CEdit m_input;
	CEdit m_type;
	CEdit m_maxDiff;
};
