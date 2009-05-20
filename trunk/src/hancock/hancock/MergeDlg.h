#pragma once


// MergeDlg dialog

class MergeDlg : public CDialog
{
	DECLARE_DYNAMIC(MergeDlg)

public:
	MergeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MergeDlg();

// Dialog Data
	enum { IDD = IDD_MERGEMODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
