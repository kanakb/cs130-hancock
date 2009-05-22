// MergeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MergeDlg.h"


// MergeDlg dialog

IMPLEMENT_DYNAMIC(MergeDlg, CDialog)

MergeDlg::MergeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MergeDlg::IDD, pParent)
{

}

MergeDlg::~MergeDlg()
{
}

void MergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INP1, m_input1);
	DDX_Control(pDX, IDC_EDIT2, m_path1);
	DDX_Control(pDX, IDC_EDIT_INP2, m_input2);
	DDX_Control(pDX, IDC_EDIT3, m_path2);
	DDX_Control(pDX, IDC_EDIT_OUT1, m_output);
}


BEGIN_MESSAGE_MAP(MergeDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &MergeDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &MergeDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &MergeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &MergeDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &MergeDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELINP2, &MergeDlg::OnBnClickedBtnSelinp2)
	ON_BN_CLICKED(IDC_SELDEP2, &MergeDlg::OnBnClickedSeldep2)
	ON_BN_CLICKED(IDC_BTN_SELMODOUT, &MergeDlg::OnBnClickedBtnSelmodout)
END_MESSAGE_MAP()


// MergeDlg message handlers

void MergeDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
}

void MergeDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void MergeDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void MergeDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input model (#1)
}

void MergeDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (#1) (if applicable)
}

void MergeDlg::OnBnClickedBtnSelinp2()
{
	// TODO: Add code for picking an input model (#2)
}

void MergeDlg::OnBnClickedSeldep2()
{
	// TODO: Add code for dependencies (#2) (if applicable)
}

void MergeDlg::OnBnClickedBtnSelmodout()
{
	// TODO: Add code for picking an output model
}
