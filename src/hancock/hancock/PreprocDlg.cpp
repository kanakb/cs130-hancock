// PreprocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "PreprocDlg.h"
#include "FolderDlg.h"


// PreprocDlg dialog

IMPLEMENT_DYNAMIC(PreprocDlg, CDialog)

PreprocDlg::PreprocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PreprocDlg::IDD, pParent)
{

}

PreprocDlg::~PreprocDlg()
{
}

void PreprocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP, m_input);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP2, m_inpMD5);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP3, m_inpIDA);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP4, m_inpIDAScr);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP5, m_inpDefs);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
}


BEGIN_MESSAGE_MAP(PreprocDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &PreprocDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &PreprocDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &PreprocDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &PreprocDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &PreprocDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELINP2, &PreprocDlg::OnBnClickedBtnSelinp2)
	ON_BN_CLICKED(IDC_BTN_SELINP6, &PreprocDlg::OnBnClickedBtnSelinp3)
	ON_BN_CLICKED(IDC_BTN_SELINP7, &PreprocDlg::OnBnClickedBtnSelinp4)
	ON_BN_CLICKED(IDC_BTN_SELINP8, &PreprocDlg::OnBnClickedBtnSelinp5)
	ON_BN_CLICKED(IDC_BTN_SELOUT1, &PreprocDlg::OnBnClickedBtnSelout1)
END_MESSAGE_MAP()


// PreprocDlg message handlers

void PreprocDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
	m_eCFG.EnableWindow(TRUE);
	m_start.EnableWindow(TRUE);
}

void PreprocDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
}

void PreprocDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void PreprocDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Input Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_input.SetWindowText(inDir1.GetFolderPath());
	}
}

void PreprocDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}

void PreprocDlg::OnBnClickedBtnSelinp2()
{
	// TODO: Add code for picking an MD5 file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("MD5 List Files(*.bin)|*.bin|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpMD5.SetWindowText(fullFilePath);
	}
}

void PreprocDlg::OnBnClickedBtnSelinp3()
{
	// TODO: Add code for picking an IDA file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Executables(*.exe)|*.exe|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpIDA.SetWindowText(fullFilePath);
	}
}

void PreprocDlg::OnBnClickedBtnSelinp4()
{
	// TODO: Add code for picking an IDA script file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("IDA Scripts(*.idc)|*.idc|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpIDAScr.SetWindowText(fullFilePath);
	}
}

void PreprocDlg::OnBnClickedBtnSelinp5()
{
	// TODO: Add code for picking the defs directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Defs Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_inpDefs.SetWindowText(inDir1.GetFolderPath());
	}
}

void PreprocDlg::OnBnClickedBtnSelout1()
{
	// TODO: Add code for picking the output directory
	CString defPath = _T("");
	CFolderDialog outDir1(_T("Output Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (outDir1.DoModal() == IDOK)
	{
		m_output.SetWindowText(outDir1.GetFolderPath());
	}
}