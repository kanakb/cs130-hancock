// StubMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "StubMapDlg.h"


// StubMapDlg dialog

IMPLEMENT_DYNAMIC(StubMapDlg, CDialog)

StubMapDlg::StubMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StubMapDlg::IDD, pParent)
{

}

StubMapDlg::~StubMapDlg()
{
}

void StubMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_inpClst);
	DDX_Control(pDX, IDC_EDIT9, m_inpMod1);
	DDX_Control(pDX, IDC_EDIT_SMIM2, m_inpMod2);
	DDX_Control(pDX, IDC_EDIT7, m_inpIndex);
	DDX_Control(pDX, IDC_EDIT2, m_inpIMM);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
	DDX_Control(pDX, IDC_CHECK1, m_selM2);
	DDX_Control(pDX, IDC_CHECK2, m_selI1);
	DDX_Control(pDX, IDC_BTN_SELSMINP3, m_browseM2);
	DDX_Control(pDX, IDC_DEP_CSM3, m_depM2);
	DDX_Control(pDX, IDC_BTN_SELSMINP4, m_browseI1);
	DDX_Control(pDX, IDC_DEP_CSM4, m_depI1);
}


BEGIN_MESSAGE_MAP(StubMapDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &StubMapDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &StubMapDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &StubMapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &StubMapDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &StubMapDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELINP2, &StubMapDlg::OnBnClickedBtnSelinp2)
	ON_BN_CLICKED(IDC_SELDEP3, &StubMapDlg::OnBnClickedSeldep2)
	ON_BN_CLICKED(IDC_BTN_SELSMINP3, &StubMapDlg::OnBnClickedBtnSelsminp3)
	ON_BN_CLICKED(IDC_DEP_CSM3, &StubMapDlg::OnBnClickedDepCsm3)
	ON_BN_CLICKED(IDC_BTN_SELSMINP4, &StubMapDlg::OnBnClickedBtnSelsminp4)
	ON_BN_CLICKED(IDC_DEP_CSM4, &StubMapDlg::OnBnClickedDepCsm4)
	ON_BN_CLICKED(IDC_BTN_SELINP3, &StubMapDlg::OnBnClickedBtnSelinp3)
	ON_BN_CLICKED(IDC_BTN_SELMODOUT, &StubMapDlg::OnBnClickedBtnSelmodout)
	ON_BN_CLICKED(IDC_CHECK1, &StubMapDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &StubMapDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// StubMapDlg message handlers

void StubMapDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
	m_eCFG.EnableWindow(TRUE);
	m_start.EnableWindow(TRUE);
}

void StubMapDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void StubMapDlg::OnBnClickedOk()
{
	// TODO: Add  code for starting the action
	OnOK();
}

void StubMapDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input cluster
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Clusterings(*.txt)|*.txt|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpClst.SetWindowText(fullFilePath);
	}
}

void StubMapDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies on the input cluster (if applicable)
}

void StubMapDlg::OnBnClickedBtnSelinp2()
{
	// TODO: Add code for picking an input model (#1)
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models(*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpMod1.SetWindowText(fullFilePath);
	}
}

void StubMapDlg::OnBnClickedSeldep2()
{
	// TODO: Add code for dependencies on the input model (#1) (if applicable)
}

void StubMapDlg::OnBnClickedBtnSelsminp3()
{
	// TODO: Add code for picking an input model (#2)
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models(*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpMod2.SetWindowText(fullFilePath);
	}
}

void StubMapDlg::OnBnClickedDepCsm3()
{
	// TODO: Add code for dependencies on the input model (#2) (if applicable)
}

void StubMapDlg::OnBnClickedBtnSelsminp4()
{
	// TODO: Add code for picking an input index
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpIndex.SetWindowText(fullFilePath);
	}
}

void StubMapDlg::OnBnClickedDepCsm4()
{
	// TODO: Add code for dependencies on the input index (if applicable)
}

void StubMapDlg::OnBnClickedBtnSelinp3()
{
	// TODO: Add code for picking an IMM counts file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("IMM Counts(*.bin)|*.bin|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpIMM.SetWindowText(fullFilePath);
	}
}

void StubMapDlg::OnBnClickedBtnSelmodout()
{
	// TODO: Add code for picking an output stub map
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Stub Maps(*.bin)|*.bin|All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetFolderPath() + _T("\\") + outBox.GetFileName();
		if (outBox.GetFileExt() == _T(""))
			fullFilePath += _T(".bin");
		m_output.SetWindowText(fullFilePath);
	}
}

void StubMapDlg::OnBnClickedCheck1()
{
	// TODO: Add code for enabling selection of model 2
	BOOL checkState = m_selM2.GetCheck();
	m_inpMod2.EnableWindow(checkState);
	m_browseM2.EnableWindow(checkState);
	m_depM2.EnableWindow(checkState);
}

void StubMapDlg::OnBnClickedCheck2()
{
	// TODO: Add code for enabling selection of an index
	BOOL checkState = m_selI1.GetCheck();
	m_inpIndex.EnableWindow(checkState);
	m_browseI1.EnableWindow(checkState);
	m_depI1.EnableWindow(checkState);
}
