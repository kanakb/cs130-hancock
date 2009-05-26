// ExtrBuffersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ExtrBuffersDlg.h"
#include "FolderDlg.h"
#include "EditCFGDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;


// ExtrBuffersDlg dialog

IMPLEMENT_DYNAMIC(ExtrBuffersDlg, CDialog)

ExtrBuffersDlg::ExtrBuffersDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(ExtrBuffersDlg::IDD, pParent), m_sched(sched)
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
		fout << "outputDir = " << sParam << endl;

		m_mode.GetWindowText(param);
		CT2CA asciiParam3(param);
		sParam = asciiParam3;
		fout << "fileBufferMode = " << sParam << endl;

		fout << "//preprocessor = foo.exe" << endl;
		fout << "//codeWindowLength = 48" << endl;

		fout.close();
		m_eCFG.EnableWindow(TRUE);
		m_start.EnableWindow(TRUE);
	}
}

void ExtrBuffersDlg::OnBnClickedBtnEcfg()
{
	// code for editing a cfg file
	EditCFGDlg ecfg(m_cfgname);
	ecfg.DoModal();
}

void ExtrBuffersDlg::OnBnClickedOk()
{
	// code for starting the action
	Action *act = new Action("C:\\sandbox\\GetPEBuffers\\", "GetPEBuffers.exe", m_cfgname);
	std::list<string> inputs;
	std::list<string> outputs;

	// Process inputs
	CString inDir;
	m_input.GetWindowText(inDir);
	CT2CA asciiInp(inDir);
	inputs.push_back(string(asciiInp));

	//Process outputs
	CString outDir;
	m_output.GetWindowText(outDir);
	CT2CA asciiOut(outDir);
	outputs.push_back(string(asciiOut));

	// Schedule action
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void ExtrBuffersDlg::OnBnClickedBtnSelinp1()
{
	// code for picking an input directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Input Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_input.SetWindowText(inDir1.GetFolderPath());
	}
}

void ExtrBuffersDlg::OnBnClickedBtnSelout1()
{
	// code for picking an output directory
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
