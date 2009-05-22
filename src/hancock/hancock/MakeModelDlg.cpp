// MakeModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MakeModelDlg.h"
#include "FolderDlg.h"


// MakeModelDlg dialog

IMPLEMENT_DYNAMIC(MakeModelDlg, CDialog)

MakeModelDlg::MakeModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MakeModelDlg::IDD, pParent)
{

}

MakeModelDlg::~MakeModelDlg()
{
}

void MakeModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_input1);
	DDX_Control(pDX, IDC_EDIT2, m_size1);
	DDX_Control(pDX, IDC_EDIT5, m_input2);
	DDX_Control(pDX, IDC_EDIT6, m_size2);
	DDX_Control(pDX, IDC_EDIT7, m_input3);
	DDX_Control(pDX, IDC_EDIT8, m_size3);
	DDX_Control(pDX, IDC_EDIT3, m_mode);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_CHECK1, m_selTD2);
	DDX_Control(pDX, IDC_CHECK2, m_selTD3);
	DDX_Control(pDX, IDC_BTN_SELMODINP2, m_browseTD2);
	DDX_Control(pDX, IDC_DEP_CMOD2, m_depTD2);
	DDX_Control(pDX, IDC_BTN_SELMODINP3, m_browseTD3);
	DDX_Control(pDX, IDC_DEP_CMOD3, m_depTD3);
}


BEGIN_MESSAGE_MAP(MakeModelDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &MakeModelDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &MakeModelDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELMODINP2, &MakeModelDlg::OnBnClickedBtnSelmodinp2)
	ON_BN_CLICKED(IDC_DEP_CMOD2, &MakeModelDlg::OnBnClickedDepCmod2)
	ON_BN_CLICKED(IDC_BTN_SELMODINP3, &MakeModelDlg::OnBnClickedBtnSelmodinp3)
	ON_BN_CLICKED(IDC_DEP_CMOD3, &MakeModelDlg::OnBnClickedDepCmod3)
	ON_BN_CLICKED(IDC_BTN_SELMODOUT, &MakeModelDlg::OnBnClickedBtnSelmodout)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &MakeModelDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &MakeModelDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDC_CHECK1, &MakeModelDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &MakeModelDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// MakeModelDlg message handlers

void MakeModelDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void MakeModelDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory (#1)
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Training Directory 1"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);;
	if (inDir1.DoModal() == IDOK)
	{
		m_input1.SetWindowText(inDir1.GetFolderPath());
	}
}

void MakeModelDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (#1) (if applicable)
}

void MakeModelDlg::OnBnClickedBtnSelmodinp2()
{
	// TODO: Add code for picking an input directory (#2)
	CString defPath = _T("");
	CFolderDialog inDir2(_T("Training Directory 2"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);;
	if (inDir2.DoModal() == IDOK)
	{
		m_input2.SetWindowText(inDir2.GetFolderPath());
	}
}

void MakeModelDlg::OnBnClickedDepCmod2()
{
	// TODO: Add code for dependencies (#2) (if applicable)
}

void MakeModelDlg::OnBnClickedBtnSelmodinp3()
{
	// TODO: Add code for picking an input directory (#3)
	CString defPath = _T("");
	CFolderDialog inDir3(_T("Training Directory 3"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);;
	if (inDir3.DoModal() == IDOK)
	{
		m_input3.SetWindowText(inDir3.GetFolderPath());
	}
}

void MakeModelDlg::OnBnClickedDepCmod3()
{
	// TODO: Add code for dependencies (#3) (if applicable)
}

void MakeModelDlg::OnBnClickedBtnSelmodout()
{
	// TODO: Add code for picking an output file
}

void MakeModelDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
}

void MakeModelDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void MakeModelDlg::OnBnClickedCheck1()
{
	// TODO: Add code for enabling input 2
	BOOL checkState = m_selTD2.GetCheck();
	m_input2.EnableWindow(checkState);
	m_size2.EnableWindow(checkState);
	m_browseTD2.EnableWindow(checkState);
	m_depTD2.EnableWindow(checkState);
}

void MakeModelDlg::OnBnClickedCheck2()
{
	// TODO: Add code for enabling input 3
	BOOL checkState = m_selTD3.GetCheck();
	m_input3.EnableWindow(checkState);
	m_size3.EnableWindow(checkState);
	m_browseTD3.EnableWindow(checkState);
	m_depTD3.EnableWindow(checkState);
}
