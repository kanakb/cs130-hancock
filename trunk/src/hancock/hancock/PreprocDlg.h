#pragma once


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
};
