#pragma once


// PruneDlg dialog

class PruneDlg : public CDialog
{
	DECLARE_DYNAMIC(PruneDlg)

public:
	PruneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~PruneDlg();

// Dialog Data
	enum { IDD = IDD_PRUNEMOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
