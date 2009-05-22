#pragma once
#include "afxwin.h"


// FindSigsDlg dialog

class FindSigsDlg : public CDialog
{
	DECLARE_DYNAMIC(FindSigsDlg)

public:
	FindSigsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~FindSigsDlg();

// Dialog Data
	enum { IDD = IDD_FINDSIGS };

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
	afx_msg void OnBnClickedSeldep2();
	afx_msg void OnBnClickedBtnSelinp3();
	afx_msg void OnBnClickedSeldep3();
	afx_msg void OnBnClickedBtnSelinp4();
	afx_msg void OnBnClickedSeldep4();
	afx_msg void OnBnClickedBtnSelinp5();
	afx_msg void OnBnClickedSeldep5();
	afx_msg void OnBnClickedBtnSelfsout();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
private:
	CEdit m_inpStubMap;
	CEdit m_inpClst1;
	CEdit m_inpInd1;
	CEdit m_inpInd2;
	CEdit m_inpClst2;
	CEdit m_mode;
	CEdit m_output;
};
