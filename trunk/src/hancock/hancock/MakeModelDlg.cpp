// MakeModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MakeModelDlg.h"
#include "FolderDlg.h"
#include "EditCFGDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

// MakeModelDlg dialog

IMPLEMENT_DYNAMIC(MakeModelDlg, CDialog)

MakeModelDlg::MakeModelDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(MakeModelDlg::IDD, pParent), m_sched(sched)
{

}

MakeModelDlg::~MakeModelDlg()
{
}

void MakeModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_input1);
	DDX_Control(pDX, IDC_EDIT2, m_size1);
	DDX_Control(pDX, IDC_EDIT5, m_input2);
	DDX_Control(pDX, IDC_EDIT6, m_size2);
	DDX_Control(pDX, IDC_EDIT7, m_input3);
	DDX_Control(pDX, IDC_EDIT8, m_size3);
	DDX_Control(pDX, IDC_EDIT3, m_mode);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_CHECK1, m_selTD2);
	DDX_Control(pDX, IDC_CHECK2, m_selTD3);
	DDX_Control(pDX, IDC_BTN_SELMODINP2, m_browseTD2);
	DDX_Control(pDX, IDC_DEP_CMOD2, m_depTD2);
	DDX_Control(pDX, IDC_BTN_SELMODINP3, m_browseTD3);
	DDX_Control(pDX, IDC_DEP_CMOD3, m_depTD3);
	DDX_Control(pDX, IDC_BTN_CRCFG, m_crCFG);
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
	DDX_Control(pDX, IDC_EDIT11, m_outSize);
	DDX_Control(pDX, IDC_CHECK3, m_selTS1);
	DDX_Control(pDX, IDC_CHECK4, m_selTS2);
	DDX_Control(pDX, IDC_CHECK5, m_selTS3);
}


BEGIN_MESSAGE_MAP(MakeModelDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &MakeModelDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &MakeModelDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELMODINP2, &MakeModelDlg::OnBnClickedBtnSelmodinp2)
	ON_BN_CLICKED(IDC_DEP_CMOD2, &MakeModelDlg::OnBnClickedDepCmod2)
	ON_BN_CLICKED(IDC_BTN_SELMODINP3, &MakeModelDlg::OnBnClickedBtnSelmodinp3)
	ON_BN_CLICKED(IDC_DEP_CMOD3, &MakeModelDlg::OnBnClickedDepCmod3)
	ON_BN_CLICKED(IDC_BTN_SELMODOUT, &MakeModelDlg::OnBnClickedBtnSelmodout)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &MakeModelDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &MakeModelDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDC_CHECK1, &MakeModelDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &MakeModelDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &MakeModelDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &MakeModelDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &MakeModelDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDOK, &MakeModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MakeModelDlg message handlers

void MakeModelDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	Action *act = new Action("C:\\sandbox\\CreateModel\\", "CreateModel.exe", m_cfgname);
	std::list<string> inputs;
	std::list<string> outputs;

	// Process inputs
	CString in;
	m_input1.GetWindowText(in);
	CT2CA asciiInp1(in);
	inputs.push_back(string(asciiInp1));

	m_input2.GetWindowText(in);
	BOOL checkState = m_selTD2.GetCheck();
	if (checkState)
	{
		CT2CA asciiInp3(in);
		inputs.push_back(string(asciiInp3));
	}

	m_input3.GetWindowText(in);
	checkState = m_selTD3.GetCheck();
	if (checkState)
	{
		CT2CA asciiInp4(in);
		inputs.push_back(string(asciiInp4));
	}

	//Process outputs
	CString out;
	m_output.GetWindowText(out);
	CT2CA asciiOut(out);
	outputs.push_back(string(asciiOut));

	// Schedule action
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void MakeModelDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input directory (#1)
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Training Directory 1"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_input1.SetWindowText(inDir1.GetFolderPath());
	}
}

void MakeModelDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (#1) (if applicable)
}

void MakeModelDlg::OnBnClickedBtnSelmodinp2()
{
	// TODO: Add code for picking an input directory (#2)
	CString defPath = _T("");
	CFolderDialog inDir2(_T("Training Directory 2"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir2.DoModal() == IDOK)
	{
		m_input2.SetWindowText(inDir2.GetFolderPath());
	}
}

void MakeModelDlg::OnBnClickedDepCmod2()
{
	// TODO: Add code for dependencies (#2) (if applicable)
}

void MakeModelDlg::OnBnClickedBtnSelmodinp3()
{
	// TODO: Add code for picking an input directory (#3)
	CString defPath = _T("");
	CFolderDialog inDir3(_T("Training Directory 3"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir3.DoModal() == IDOK)
	{
		m_input3.SetWindowText(inDir3.GetFolderPath());
	}
}

void MakeModelDlg::OnBnClickedDepCmod3()
{
	// TODO: Add code for dependencies (#3) (if applicable)
}

void MakeModelDlg::OnBnClickedBtnSelmodout()
{
	// TODO: Add code for picking an output file
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models (*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetFolderPath() + _T("\\") + outBox.GetFileName();
		if (outBox.GetFileExt() == _T(""))
			fullFilePath += _T(".mdl");
		m_output.SetWindowText(fullFilePath);
	}
}

void MakeModelDlg::OnBnClickedBtnCrcfg()
{
	// TODO: Add code for creating a cfg file
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
		m_output.GetWindowText(param);
		CT2CA asciiParam(param);
		string sParam(asciiParam);
		fout << "modelFilename = " << sParam << endl;

		m_outSize.GetWindowText(param);
		CT2CA asciiParam2(param);
		sParam = asciiParam2;
		fout << "totalTrainingSize = " << sParam << endl;

		m_input1.GetWindowText(param);
		CT2CA asciiParam3(param);
		sParam = asciiParam3;
		fout << "trainingDir0 = " << sParam << endl;

		if (m_selTS1.GetCheck())
		{
			m_size1.GetWindowText(param);
			CT2CA asciiParam4(param);
			sParam = asciiParam4;
			fout << "trainingSize0 = " << sParam << endl;
		}
		else
			fout << "#trainingSize0 = " << endl;

		if (m_selTD2.GetCheck())
		{
			m_input2.GetWindowText(param);
			CT2CA asciiParam5(param);
			sParam = asciiParam5;
			fout << "trainingDir1 = " << sParam << endl;
		}
		else
			fout << "#trainingDir1 = " << endl;

		if (m_selTS2.GetCheck())
		{
			m_size2.GetWindowText(param);
			CT2CA asciiParam6(param);
			sParam = asciiParam6;
			fout << "trainingSize1 = " << sParam << endl;
		}
		else
			fout << "#trainingSize1 = " << endl;

		if (m_selTD3.GetCheck())
		{
			m_input3.GetWindowText(param);
			CT2CA asciiParam7(param);
			sParam = asciiParam7;
			fout << "trainingDir2 = " << sParam << endl;
		}
		else
			fout << "#trainingDir2 = " << endl;

		if (m_selTS3.GetCheck())
		{
			m_size3.GetWindowText(param);
			CT2CA asciiParam8(param);
			sParam = asciiParam8;
			fout << "trainingSize2 = " << sParam << endl;
		}
		else
			fout << "#trainingSize2 = " << endl;
		
		m_mode.GetWindowText(param);
		CT2CA asciiParam9(param);
		sParam = asciiParam9;
		fout << "inputFileMode = " << sParam << endl;
		fout << "#bufferMode = whole" << endl;
		fout << "#modelDepth = 5" << endl;
		fout << "#fileCountMax = 1" << endl;

		fout.close();
		m_eCFG.EnableWindow(TRUE);
		m_start.EnableWindow(TRUE);
	}
}

void MakeModelDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
	EditCFGDlg ecfg(m_cfgname);
	ecfg.DoModal();
}

void MakeModelDlg::OnBnClickedCheck1()
{
	// TODO: Add code for enabling input 2
	BOOL checkState = m_selTD2.GetCheck();
	m_input2.EnableWindow(checkState);
	m_browseTD2.EnableWindow(checkState);
	m_depTD2.EnableWindow(checkState);
}

void MakeModelDlg::OnBnClickedCheck2()
{
	// TODO: Add code for enabling input 3
	BOOL checkState = m_selTD3.GetCheck();
	m_input3.EnableWindow(checkState);
	m_browseTD3.EnableWindow(checkState);
	m_depTD3.EnableWindow(checkState);
}

void MakeModelDlg::OnBnClickedCheck3()
{
	// TODO: Add code for entering size 1
	BOOL checkState = m_selTS1.GetCheck();
	m_size1.EnableWindow(checkState);
}

void MakeModelDlg::OnBnClickedCheck4()
{
	// TODO: Add code for entering size 2
	BOOL checkState = m_selTS2.GetCheck();
	m_size2.EnableWindow(checkState);
}

void MakeModelDlg::OnBnClickedCheck5()
{
	// TODO: Add code for entering size 3
	BOOL checkState = m_selTS3.GetCheck();
	m_size3.EnableWindow(checkState);
}
