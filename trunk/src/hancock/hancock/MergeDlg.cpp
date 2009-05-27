// MergeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MergeDlg.h"
#include "EditCFGDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include "ScheduleUI.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;


// MergeDlg dialog

IMPLEMENT_DYNAMIC(MergeDlg, CDialog)

MergeDlg::MergeDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(MergeDlg::IDD, pParent), m_sched(sched)
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
		m_input1.GetWindowText(param);
		CT2CA asciiParam(param);
		string sParam(asciiParam);
		fout << "model1 = " << sParam << endl;

		m_path1.GetWindowText(param);
		CT2CA asciiParam2(param);
		sParam = asciiParam2;
		fout << "model1Path = " << sParam << endl;

		m_input2.GetWindowText(param);
		CT2CA asciiParam3(param);
		sParam = asciiParam3;
		fout << "model2 = " << sParam << endl;

		m_path2.GetWindowText(param);
		CT2CA asciiParam4(param);
		sParam = asciiParam4;
		fout << "model2Path = " << sParam << endl;

		m_output.GetWindowText(param);
		CT2CA asciiParam5(param);
		sParam = asciiParam5;
		fout << "outputModel = " << sParam << endl;
		fout << "#nonPruned" << endl;

		fout.close();
		m_eCFG.EnableWindow(TRUE);
		m_start.EnableWindow(TRUE);
	}
}

void MergeDlg::OnBnClickedBtnEcfg()
{
	// code for editing a cfg file
	EditCFGDlg ecfg(m_cfgname);
	ecfg.DoModal();
}

void MergeDlg::OnBnClickedOk()
{
	// code for starting the action
	Action *act = new Action("executables\\", "MergeModels.exe", m_cfgname);
	std::list<string> inputs;
	std::list<string> outputs;

	// Process inputs
	CString in;
	m_input1.GetWindowText(in);
	CT2CA asciiInp1(in);
	inputs.push_back(string(asciiInp1));

	m_input2.GetWindowText(in);
	CT2CA asciiInp2(in);
	inputs.push_back(string(asciiInp2));

	//Process outputs
	CString out;
	m_output.GetWindowText(out);
	CT2CA asciiOut(out);
	outputs.push_back(string(asciiOut));

	// Schedule action
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void MergeDlg::OnBnClickedBtnSelinp1()
{
	// code for picking an input model (#1)
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
	// code for dependencies (#1) (if applicable)
	ScheduleUI depui(TRUE, m_sched);
	if (depui.DoModal() == IDOK)
	{
		CString depName;
		depui.getFileString(depName);
		if (depName != _T(""))
		{
			m_deps.push_back(depui.getCurAct());
			m_input1.SetWindowText(depName);
		}
	}
}

void MergeDlg::OnBnClickedBtnSelinp2()
{
	// code for picking an input model (#2)
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
	// code for dependencies (#2) (if applicable)
	ScheduleUI depui(TRUE, m_sched);
	if (depui.DoModal() == IDOK)
	{
		CString depName;
		depui.getFileString(depName);
		if (depName != _T(""))
		{
			m_deps.push_back(depui.getCurAct());
			m_input2.SetWindowText(depName);
		}
	}
}

void MergeDlg::OnBnClickedBtnSelmodout()
{
	// code for picking an output model
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models (*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetFolderPath() + _T("\\") + outBox.GetFileName();
		if (outBox.GetFileExt() == _T(""))
			fullFilePath += _T(".mdl");
		m_output.SetWindowText(fullFilePath);
	}
}
