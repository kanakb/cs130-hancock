// SelDepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "SelDepDlg.h"
#include "Scheduler.h"
#include <list>
#include <string>
using namespace std;


// SelDepDlg dialog

IMPLEMENT_DYNAMIC(SelDepDlg, CDialog)

SelDepDlg::SelDepDlg(Scheduler::actData *action, CWnd* pParent /*=NULL*/)
	: CDialog(SelDepDlg::IDD, pParent), m_actData(action)
{

}

SelDepDlg::~SelDepDlg()
{
}

void SelDepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_fileList);

	// Populate ListBox with action outputs
	list<string>::iterator it = m_actData->outputs.begin();
	for (; it != m_actData->outputs.end(); it++)
	{
		CString act(it->c_str());
		m_fileList.AddString(act);
	}
}


BEGIN_MESSAGE_MAP(SelDepDlg, CDialog)
	ON_BN_CLICKED(IDOK, &SelDepDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SelDepDlg message handlers

void SelDepDlg::OnBnClickedOk()
{
	// set file string to the selected one
	int nIndex = m_fileList.GetCurSel();
	if (nIndex != LB_ERR)
		m_fileList.GetText(nIndex, m_filename);
	else
		MessageBox(_T("No dependency selected."));
	OnOK();
}

void SelDepDlg::getFileString(CString &file)
{
	file = m_filename;
}
