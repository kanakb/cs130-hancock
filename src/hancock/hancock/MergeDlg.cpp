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
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
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
	m_eCFG.EnableWindow(TRUE);
	m_start.EnableWindow(TRUE);
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
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models(*.mdl)|*.bin|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_input1.SetWindowText(fullFilePath);
		m_path1.SetWindowText(inBox1.GetFolderPath());
	}
}

void MergeDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (#1) (if applicable)
}

void MergeDlg::OnBnClickedBtnSelinp2()
{
	// TODO: Add code for picking an input model (#2)
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models(*.mdl)|*.bin|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_input2.SetWindowText(fullFilePath);
		m_path2.SetWindowText(inBox1.GetFolderPath());
	}
}

void MergeDlg::OnBnClickedSeldep2()
{
	// TODO: Add code for dependencies (#2) (if applicable)
}

void MergeDlg::OnBnClickedBtnSelmodout()
{
	// TODO: Add code for picking an output model
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models (*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetFolderPath() + _T("\\") + outBox.GetFileName();
		if (outBox.GetFileExt() == _T(""))
			fullFilePath += _T(".mdl");
		m_output.SetWindowText(fullFilePath);
	}
}
