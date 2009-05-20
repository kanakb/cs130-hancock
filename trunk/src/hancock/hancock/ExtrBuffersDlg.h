#pragma once


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
};
