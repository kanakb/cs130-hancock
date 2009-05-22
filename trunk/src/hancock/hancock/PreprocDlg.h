#pragma once
#include "afxwin.h"


// PreprocDlg dialog

class PreprocDlg : public CDialog
{
	DECLARE_DYNAMIC(PreprocDlg)

public:
	PreprocDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~PreprocDlg();

// Dialog Data
	enum { IDD = IDD_PREPROC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCrcfg();
	afx_msg void OnBnClickedBtnEcfg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
	afx_msg void OnBnClickedBtnSelinp2();
	afx_msg void OnBnClickedBtnSelinp3();
	afx_msg void OnBnClickedBtnSelinp4();
	afx_msg void OnBnClickedBtnSelinp5();
	afx_msg void OnBnClickedBtnSelout1();
private:
	CEdit m_input;
public:
	CEdit m_inpMD5;
private:
	CEdit m_inpIDA;
	CEdit m_inpIDAScr;
	CEdit m_inpDefs;
	CEdit m_output;
};
