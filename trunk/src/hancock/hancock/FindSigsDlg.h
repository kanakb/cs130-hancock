#pragma once


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
};
