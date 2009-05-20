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
};
