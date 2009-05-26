// PreprocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "PreprocDlg.h"
#include "FolderDlg.h"
#include "EditCFGDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;


// PreprocDlg dialog

IMPLEMENT_DYNAMIC(PreprocDlg, CDialog)

PreprocDlg::PreprocDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(PreprocDlg::IDD, pParent), m_sched(sched)
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
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP6, m_maxProcs);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP7, m_timeOut);
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
	// code for creating a cfg file
	CFileDialog cfgBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Configuration Files(*.cfg)|*.cfg|All Files(*.*)|*.*||"));
	if (cfgBox.DoModal() == IDOK)
	{
		// Get file path from dialog
		CString fullFilePath = cfgBox.GetFolderPath() + _T("\\") + cfgBox.GetFileName();
		if (cfgBox.GetFileExt() == _T(""))
			fullFilePath += _T(".cfg");

		// Open file for writing
		CT2CA asciiPath(fullFilePath);
		string sPath(asciiPath);
		m_cfgname = sPath;
		ofstream fout(sPath.c_str());

		// Write each parameter
		CString param;
		m_input.GetWindowText(param);
		CT2CA asciiParam(param);
		string sParam(asciiParam);
		fout << "inputDir = " << sParam << endl;

		m_output.GetWindowText(param);
		CT2CA asciiParam2(param);
		sParam = asciiParam2;
		fout << "outputDirBase = " << sParam << endl;

		m_inpMD5.GetWindowText(param);
		CT2CA asciiParam3(param);
		sParam = asciiParam3;
		fout << "MD5ListFile = " << sParam << endl;

		m_maxProcs.GetWindowText(param);
		CT2CA asciiParam4(param);
		sParam = asciiParam4;
		fout << "maxIdaProcs = " << sParam << endl;

		m_timeOut.GetWindowText(param);
		CT2CA asciiParam5(param);
		sParam = asciiParam5;
		fout << "procTimeOut = " << sParam << endl;

		m_inpIDA.GetWindowText(param);
		CT2CA asciiParam6(param);
		sParam = asciiParam6;
		fout << "IdaPath = " << sParam << endl;

		m_inpIDAScr.GetWindowText(param);
		CT2CA asciiParam7(param);
		sParam = asciiParam7;
		fout << "IdaScriptPath = " << sParam << endl;

		m_inpDefs.GetWindowText(param);
		CT2CA asciiParam8(param);
		sParam = asciiParam8;
		fout << "elegharnDefs = " << sParam << endl;
		fout << "#skipToStage = 3" << endl;

		fout.close();
		m_eCFG.EnableWindow(TRUE);
		m_start.EnableWindow(TRUE);
	}
}

void PreprocDlg::OnBnClickedBtnEcfg()
{
	// code for editing a cfg file
	EditCFGDlg ecfg(m_cfgname);
	ecfg.DoModal();
}

void PreprocDlg::OnBnClickedOk()
{
	// code for starting the action
	Action *act = new Action("C:\\sandbox\\PreProcMalware\\", "PreProcMalware.exe", m_cfgname);
	std::list<string> inputs;
	std::list<string> outputs;

	// Process inputs
	CString in;
	m_input.GetWindowText(in);
	CT2CA asciiInp1(in);
	inputs.push_back(string(asciiInp1));

	//Process outputs
	CString out;
	m_output.GetWindowText(out);
	CT2CA asciiOut(out);
	outputs.push_back(string(asciiOut));

	// Schedule action
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void PreprocDlg::OnBnClickedBtnSelinp1()
{
	// code for picking an input directory
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
	// code for picking an MD5 file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("MD5 List Files(*.bin)|*.bin|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpMD5.SetWindowText(fullFilePath);
	}
}

void PreprocDlg::OnBnClickedBtnSelinp3()
{
	// code for picking an IDA file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Executables(*.exe)|*.exe|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpIDA.SetWindowText(fullFilePath);
	}
}

void PreprocDlg::OnBnClickedBtnSelinp4()
{
	// code for picking an IDA script file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("IDA Scripts(*.idc)|*.idc|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpIDAScr.SetWindowText(fullFilePath);
	}
}

void PreprocDlg::OnBnClickedBtnSelinp5()
{
	// code for picking the defs directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Defs Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_inpDefs.SetWindowText(inDir1.GetFolderPath());
	}
}

void PreprocDlg::OnBnClickedBtnSelout1()
{
	// code for picking the output directory
	CString defPath = _T("");
	CFolderDialog outDir1(_T("Output Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (outDir1.DoModal() == IDOK)
	{
		m_output.SetWindowText(outDir1.GetFolderPath());
	}
}
