// LogUI.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "LogUI.h"


// LogUI dialog

IMPLEMENT_DYNAMIC(LogUI, CDialog)

LogUI::LogUI(CWnd* pParent /*=NULL*/)
	: CDialog(LogUI::IDD, pParent)
{

}

LogUI::~LogUI()
{
}

void LogUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_closeBtn);
	DDX_Control(pDX, IDC_LOGLIST, m_logList);
	DDX_Control(pDX, IDC_LOGTEXT, m_logText);
}


BEGIN_MESSAGE_MAP(LogUI, CDialog)
	ON_EN_CHANGE(IDC_LOGTEXT, &LogUI::OnEnChangeLogtext)
	ON_LBN_SELCHANGE(IDC_LOGLIST, &LogUI::OnLbnSelchangeLoglist)
	ON_BN_CLICKED(IDOK, &LogUI::OnBnClickedOk)
END_MESSAGE_MAP()


// LogUI message handlers

void LogUI::OnEnChangeLogtext()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void LogUI::OnLbnSelchangeLoglist()
{
	// TODO: Add your control notification handler code here
}

void LogUI::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
