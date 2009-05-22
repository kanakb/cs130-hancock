// lstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ClstDlg.h"


// ClstDlg dialog

IMPLEMENT_DYNAMIC(ClstDlg, CDialog)

ClstDlg::ClstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClstDlg::IDD, pParent)
{

}

ClstDlg::~ClstDlg()
{
}

void ClstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP, m_input);
	DDX_Control(pDX, IDC_EDIT4, m_type);
	DDX_Control(pDX, IDC_EDIT_MODE, m_maxDiff);
}


BEGIN_MESSAGE_MAP(ClstDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &ClstDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &ClstDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &ClstDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &ClstDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &ClstDlg::OnBnClickedSeldep1)
END_MESSAGE_MAP()


// ClstDlg message handlers

void ClstDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
}

void ClstDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void ClstDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void ClstDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory
}

void ClstDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}
