#pragma once
#include "afxwin.h"


// MakeModelDlg dialog

class MakeModelDlg : public CDialog
{
	DECLARE_DYNAMIC(MakeModelDlg)

public:
	MakeModelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MakeModelDlg();

// Dialog Data
	enum { IDD = IDD_MAKEMODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
	afx_msg void OnBnClickedBtnSelmodinp2();
	afx_msg void OnBnClickedDepCmod2();
	afx_msg void OnBnClickedBtnSelmodinp3();
	afx_msg void OnBnClickedDepCmod3();
	afx_msg void OnBnClickedBtnSelmodout();
	afx_msg void OnBnClickedBtnCrcfg();
	afx_msg void OnBnClickedBtnEcfg();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
private:
	CEdit m_input1;
	CEdit m_size1;
	CEdit m_input2;
	CEdit m_size2;
	CEdit m_input3;
	CEdit m_size3;
	CEdit m_mode;
	CEdit m_output;
};
