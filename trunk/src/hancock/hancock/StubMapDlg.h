#pragma once


// StubMapDlg dialog

class StubMapDlg : public CDialog
{
	DECLARE_DYNAMIC(StubMapDlg)

public:
	StubMapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~StubMapDlg();

// Dialog Data
	enum { IDD = IDD_STUBMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
