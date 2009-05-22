// MakeIndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MakeIndexDlg.h"


// MakeIndexDlg dialog

IMPLEMENT_DYNAMIC(MakeIndexDlg, CDialog)

MakeIndexDlg::MakeIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MakeIndexDlg::IDD, pParent)
{

}

MakeIndexDlg::~MakeIndexDlg()
{
}

void MakeIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAKEIND_INP, m_input);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_COMBO_INDMODE, m_mode);
}


BEGIN_MESSAGE_MAP(MakeIndexDlg, CDialog)
	ON_BN_CLICKED(IDOK, &MakeIndexDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &MakeIndexDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &MakeIndexDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELOUT1, &MakeIndexDlg::OnBnClickedBtnSelout1)
END_MESSAGE_MAP()


// MakeIndexDlg message handlers

void MakeIndexDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void MakeIndexDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory
}

void MakeIndexDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}

void MakeIndexDlg::OnBnClickedBtnSelout1()
{
	// TODO: Add code for picking an input file
}
