#pragma once


// ModCompileDlg dialog

class ModCompileDlg : public CDialog
{
	DECLARE_DYNAMIC(ModCompileDlg)

public:
	ModCompileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ModCompileDlg();

// Dialog Data
	enum { IDD = IDD_COMPILEMOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
