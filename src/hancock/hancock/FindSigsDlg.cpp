// FindSigsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "FindSigsDlg.h"


// FindSigsDlg dialog

IMPLEMENT_DYNAMIC(FindSigsDlg, CDialog)

FindSigsDlg::FindSigsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FindSigsDlg::IDD, pParent)
{

}

FindSigsDlg::~FindSigsDlg()
{
}

void FindSigsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_inpStubMap);
	DDX_Control(pDX, IDC_EDIT9, m_inpClst1);
	DDX_Control(pDX, IDC_EDIT10, m_inpInd1);
	DDX_Control(pDX, IDC_EDIT_SMIM2, m_inpInd2);
	DDX_Control(pDX, IDC_EDIT7, m_inpClst2);
	DDX_Control(pDX, IDC_EDIT3, m_mode);
	DDX_Control(pDX, IDC_EDIT4, m_output);
}


BEGIN_MESSAGE_MAP(FindSigsDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &FindSigsDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &FindSigsDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &FindSigsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &FindSigsDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &FindSigsDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELINP2, &FindSigsDlg::OnBnClickedBtnSelinp2)
	ON_BN_CLICKED(IDC_SELDEP3, &FindSigsDlg::OnBnClickedSeldep2)
	ON_BN_CLICKED(IDC_BTN_SELINP3, &FindSigsDlg::OnBnClickedBtnSelinp3)
	ON_BN_CLICKED(IDC_SELDEP4, &FindSigsDlg::OnBnClickedSeldep3)
	ON_BN_CLICKED(IDC_BTN_SELINP4, &FindSigsDlg::OnBnClickedBtnSelinp4)
	ON_BN_CLICKED(IDC_SELDEP5, &FindSigsDlg::OnBnClickedSeldep4)
	ON_BN_CLICKED(IDC_BTN_SELINP5, &FindSigsDlg::OnBnClickedBtnSelinp5)
	ON_BN_CLICKED(IDC_SELDEP6, &FindSigsDlg::OnBnClickedSeldep5)
	ON_BN_CLICKED(IDC_BTN_SELFSOUT, &FindSigsDlg::OnBnClickedBtnSelfsout)
	ON_BN_CLICKED(IDC_CHECK1, &FindSigsDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &FindSigsDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// FindSigsDlg message handlers

void FindSigsDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
}

void FindSigsDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void FindSigsDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void FindSigsDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input stub map
}

void FindSigsDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies for an input stub map (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp2()
{
	// TODO: Add code for picking an input cluster (#1)
}

void FindSigsDlg::OnBnClickedSeldep2()
{
	// TODO: Add code for dependencies for an input cluster (#1) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp3()
{
	// TODO: Add code for picking an input index (#1)
}

void FindSigsDlg::OnBnClickedSeldep3()
{
	// TODO: Add code for dependencies for an input index (#1) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp4()
{
	// TODO: Add code for picking an input index (#2)
}

void FindSigsDlg::OnBnClickedSeldep4()
{
	// TODO: Add code for dependencies for an input index (#2) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp5()
{
	// TODO: Add code for picking an input cluster (#2)
}

void FindSigsDlg::OnBnClickedSeldep5()
{
	// TODO: Add code for dependencies for an input cluster (#2) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelfsout()
{
	// TODO: Add code for selecting output
}

void FindSigsDlg::OnBnClickedCheck1()
{
	// TODO: Add code for enabling input index 2
}

void FindSigsDlg::OnBnClickedCheck2()
{
	// TODO: Add code for enabling input cluster 2
}
