#pragma once
#include "afxwin.h"
#include <string>

// EditCFGDlg dialog

class EditCFGDlg : public CDialog
{
	DECLARE_DYNAMIC(EditCFGDlg)

public:
	EditCFGDlg(std::string filename, CWnd* pParent = NULL);   // standard constructor
	virtual ~EditCFGDlg();

// Dialog Data
	enum { IDD = IDD_CFGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	CEdit m_text;
	std::string m_filename;
};
