// ModCompileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ModCompileDlg.h"


// ModCompileDlg dialog

IMPLEMENT_DYNAMIC(ModCompileDlg, CDialog)

ModCompileDlg::ModCompileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ModCompileDlg::IDD, pParent)
{

}

ModCompileDlg::~ModCompileDlg()
{
}

void ModCompileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPILE_INP, m_input);
}


BEGIN_MESSAGE_MAP(ModCompileDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ModCompileDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &ModCompileDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &ModCompileDlg::OnBnClickedSeldep1)
END_MESSAGE_MAP()


// ModCompileDlg message handlers

void ModCompileDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void ModCompileDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory
}

void ModCompileDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}
