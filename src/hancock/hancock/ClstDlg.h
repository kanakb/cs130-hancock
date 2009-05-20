#pragma once


// ClstDlg dialog

class ClstDlg : public CDialog
{
	DECLARE_DYNAMIC(ClstDlg)

public:
	ClstDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ClstDlg();

// Dialog Data
	enum { IDD = IDD_CLSTFILES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
