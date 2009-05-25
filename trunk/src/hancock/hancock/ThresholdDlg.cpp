// ThresholdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ThresholdDlg.h"
#include "log.h"
#include <string>


// ThresholdDlg dialog

IMPLEMENT_DYNAMIC(ThresholdDlg, CDialog)

ThresholdDlg::ThresholdDlg(HancockLog *log, CWnd* pParent /*=NULL*/)
	: CDialog(ThresholdDlg::IDD, pParent), m_log(log)
{

}

ThresholdDlg::~ThresholdDlg()
{
}

void ThresholdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_val);
}


BEGIN_MESSAGE_MAP(ThresholdDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ThresholdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ThresholdDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ThresholdDlg message handlers

void ThresholdDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString wtext;
	m_val.GetWindowText(wtext);
	CT2CA asciiText(wtext);
	std::string text(asciiText);
	text = "Changed schedule threshold to " + text;
	m_log->write(text);
	OnOK();
}

void ThresholdDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
