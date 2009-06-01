// ThresholdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ThresholdDlg.h"
#include "log.h"
#include <string>
#include <cstdlib>


// ThresholdDlg dialog

IMPLEMENT_DYNAMIC(ThresholdDlg, CDialog)

ThresholdDlg::ThresholdDlg(Scheduler *sched, HancockLog *log, CWnd* pParent /*=NULL*/)
	: CDialog(ThresholdDlg::IDD, pParent), m_log(log), m_sched(sched)
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
	// Tell scheduler to update threshold
	CString wtext;
	m_val.GetWindowText(wtext);
	CT2CA asciiText(wtext);
	std::string text(asciiText);
	if (text != "")
	{
		m_sched->SetThreshold(atoi(text.c_str()));
		text = "Changed schedule threshold to " + text;
		m_log->write(text);
	}
	OnOK();
}

void ThresholdDlg::OnBnClickedCancel()
{
	OnCancel();
}
