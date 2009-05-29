// ClstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ClstDlg.h"
#include "FolderDlg.h"
#include "EditCFGDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include "ScheduleUI.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// ClstDlg dialog

IMPLEMENT_DYNAMIC(ClstDlg, CDialog)

ClstDlg::ClstDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(ClstDlg::IDD, pParent), m_sched(sched)
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
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
	DDX_Control(pDX, IDC_EDIT_EXTRBUF_INP2, m_output);
}


BEGIN_MESSAGE_MAP(ClstDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &ClstDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &ClstDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &ClstDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &ClstDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &ClstDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELOUT, &ClstDlg::OnBnClickedBtnSelout)
END_MESSAGE_MAP()


// ClstDlg message handlers

void ClstDlg::OnBnClickedBtnCrcfg()
{
	// code for creating a cfg file
	CFileDialog cfgBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Configuration Files(*.cfg)|*.cfg|All Files(*.*)|*.*||"));
	if (cfgBox.DoModal() == IDOK)
	{
		// Get file path from dialog
		CString fullFilePath = cfgBox.GetPathName();
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
		fout << "sampleDir = " << sParam << endl;

		m_type.GetWindowText(param);
		CT2CA asciiParam2(param);
		sParam = asciiParam2;
		fout << "testType = " << sParam << endl;

		m_maxDiff.GetWindowText(param);
		CT2CA asciiParam3(param);
		sParam = asciiParam3;
		fout << "maxDiff = " << sParam << endl;

		fout << "#findBestCluster" << endl;
		fout << "#useCentroid" << endl;
		fout << "#minFiles" << endl;

		fout.close();
		m_eCFG.EnableWindow(TRUE);
		m_start.EnableWindow(TRUE);
	}
}

void ClstDlg::OnBnClickedBtnEcfg()
{
	// code for editing a cfg file
	EditCFGDlg ecfg(m_cfgname);
	ecfg.DoModal();
}

void ClstDlg::OnBnClickedOk()
{
	// code for starting the action
	std::list<string> inputs;
	std::list<string> outputs;

	// Process inputs
	CString inDir;
	m_input.GetWindowText(inDir);
	CT2CA asciiInp(inDir);
	inputs.push_back(string(asciiInp));

	//Process outputs
	CString out;
	m_output.GetWindowText(out);
	CT2CA asciiOut(out);
	string outfilename(asciiOut);
	if (outfilename != "")
		outputs.push_back(outfilename);

	// Schedule action
	Action *act = new Action("executables\\", "FileClust.exe", m_cfgname, outfilename);
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void ClstDlg::OnBnClickedBtnSelinp1()
{
	// code for picking an input directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Input Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_input.SetWindowText(inDir1.GetFolderPath());
	}
}

void ClstDlg::OnBnClickedSeldep1()
{
	// code for dependencies (if applicable)
	ScheduleUI depui(TRUE, m_sched);
	if (depui.DoModal() == IDOK)
	{
		CString depName;
		depui.getFileString(depName);
		if (depName != _T(""))
		{
			m_deps.push_back(depui.getCurAct());
			m_input.SetWindowText(depName);
		}
	}
}

void ClstDlg::OnBnClickedBtnSelout()
{
	// code for picking an output file
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Clusterings(*.txt)|*.txt|All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetPathName();
		if (outBox.GetFileExt() == _T(""))
			fullFilePath += _T(".txt");
		m_output.SetWindowText(fullFilePath);
	}
}
