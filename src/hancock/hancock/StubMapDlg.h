#pragma once
#include "afxwin.h"


// StubMapDlg dialog

class StubMapDlg : public CDialog
{
	DECLARE_DYNAMIC(StubMapDlg)

public:
	StubMapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~StubMapDlg();

// Dialog Data
	enum { IDD = IDD_STUBMAP };

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
	afx_msg void OnBnClickedBtnSelsminp3();
	afx_msg void OnBnClickedDepCsm3();
	afx_msg void OnBnClickedBtnSelsminp4();
	afx_msg void OnBnClickedDepCsm4();
	afx_msg void OnBnClickedBtnSelinp3();
	afx_msg void OnBnClickedBtnSelmodout();
private:
	CEdit m_inpClst;
	CEdit m_inpMod1;
	CEdit m_inpMod2;
	CEdit m_inpIndex;
	CEdit m_inpIMM;
	CEdit m_output;
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
private:
	CButton m_eCFG;
	CButton m_start;
	CButton m_selM2;
	CButton m_selI1;
	CButton m_browseM2;
	CButton m_depM2;
	CButton m_browseI1;
	CButton m_depI1;
};
