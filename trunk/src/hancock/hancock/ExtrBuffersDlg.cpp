// ExtrBuffersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ExtrBuffersDlg.h"
#include "FolderDlg.h"


// ExtrBuffersDlg dialog

IMPLEMENT_DYNAMIC(ExtrBuffersDlg, CDialog)

ExtrBuffersDlg::ExtrBuffersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ExtrBuffersDlg::IDD, pParent)
{

}

ExtrBuffersDlg::~ExtrBuffersDlg()
{
}

void ExtrBuffersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP, m_input);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_EDIT_MODE, m_mode);
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
}


BEGIN_MESSAGE_MAP(ExtrBuffersDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &ExtrBuffersDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &ExtrBuffersDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &ExtrBuffersDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &ExtrBuffersDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_BTN_SELOUT1, &ExtrBuffersDlg::OnBnClickedBtnSelout1)
	ON_BN_CLICKED(IDC_SELDEP1, &ExtrBuffersDlg::OnBnClickedSeldep1)
END_MESSAGE_MAP()


// ExtrBuffersDlg message handlers

void ExtrBuffersDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
	m_eCFG.EnableWindow(TRUE);
	m_start.EnableWindow(TRUE);
}

void ExtrBuffersDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void ExtrBuffersDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void ExtrBuffersDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Input Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_input.SetWindowText(inDir1.GetFolderPath());
	}
}

void ExtrBuffersDlg::OnBnClickedBtnSelout1()
{
	// TODO: Add code for picking an output directory
	CString defPath = _T("");
	CFolderDialog outDir1(_T("Output Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (outDir1.DoModal() == IDOK)
	{
		m_output.SetWindowText(outDir1.GetFolderPath());
	}
}

void ExtrBuffersDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}
