// PruneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "PruneDlg.h"


// PruneDlg dialog

IMPLEMENT_DYNAMIC(PruneDlg, CDialog)

PruneDlg::PruneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PruneDlg::IDD, pParent)
{

}

PruneDlg::~PruneDlg()
{
}

void PruneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PRUNE_INP, m_input);
	DDX_Control(pDX, IDC_EDIT4, m_thresholds);
}


BEGIN_MESSAGE_MAP(PruneDlg, CDialog)
	ON_BN_CLICKED(IDOK, &PruneDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &PruneDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &PruneDlg::OnBnClickedSeldep1)
END_MESSAGE_MAP()


// PruneDlg message handlers

void PruneDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void PruneDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models(*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_input.SetWindowText(fullFilePath);
	}
}

void PruneDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}
