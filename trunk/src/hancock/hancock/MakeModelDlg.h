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
	afx_msg void OnBnClickedBtnSelmodinp();
	afx_msg void OnBnClickedBtnSelmodout();
	afx_msg void OnBnClickedBtnCmodelcfg();
	afx_msg void OnBnClickedBtnCmodelecfg();
	afx_msg void OnBnClickedOk();
private:
	CEdit m_trainDir;
	CEdit m_trainSize;
	CEdit m_inpMode;
	CEdit m_outputFile;
};
