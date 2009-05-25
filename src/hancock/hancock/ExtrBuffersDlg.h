#pragma once
#include "afxwin.h"
#include <string>


// ExtrBuffersDlg dialog

class ExtrBuffersDlg : public CDialog
{
	DECLARE_DYNAMIC(ExtrBuffersDlg)

public:
	ExtrBuffersDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ExtrBuffersDlg();

// Dialog Data
	enum { IDD = IDD_EXTRBUFFERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCrcfg();
	afx_msg void OnBnClickedBtnEcfg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedBtnSelout1();
	afx_msg void OnBnClickedSeldep1();
private:
	CEdit m_input;
	CEdit m_output;
	CEdit m_mode;
	CButton m_eCFG;
	CButton m_start;
	std::string m_cfgname;
};
