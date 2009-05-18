// MakeModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MakeModelDlg.h"


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
	DDX_Control(pDX, IDC_EDIT1, m_trainDir);
	DDX_Control(pDX, IDC_EDIT2, m_trainSize);
	DDX_Control(pDX, IDC_EDIT3, m_inpMode);
	DDX_Control(pDX, IDC_EDIT4, m_outputFile);
}


BEGIN_MESSAGE_MAP(MakeModelDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SELMODINP, &MakeModelDlg::OnBnClickedBtnSelmodinp)
	ON_BN_CLICKED(IDC_BTN_SELMODOUT, &MakeModelDlg::OnBnClickedBtnSelmodout)
	ON_BN_CLICKED(IDC_BTN_CMODELCFG, &MakeModelDlg::OnBnClickedBtnCmodelcfg)
	ON_BN_CLICKED(IDC_BTN_CMODELECFG, &MakeModelDlg::OnBnClickedBtnCmodelecfg)
	ON_BN_CLICKED(IDOK, &MakeModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MakeModelDlg message handlers

void MakeModelDlg::OnBnClickedBtnSelmodinp()
{
	// TODO: Add your control notification handler code here
}

void MakeModelDlg::OnBnClickedBtnSelmodout()
{
	// TODO: Add your control notification handler code here
}

void MakeModelDlg::OnBnClickedBtnCmodelcfg()
{
	// TODO: Add your control notification handler code here
}

void MakeModelDlg::OnBnClickedBtnCmodelecfg()
{
	// TODO: Add your control notification handler code here
}

void MakeModelDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
