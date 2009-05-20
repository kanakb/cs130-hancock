#pragma once


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
};
