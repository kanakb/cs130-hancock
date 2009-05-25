// FindSigsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "FindSigsDlg.h"
#include "EditCFGDlg.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// FindSigsDlg dialog

IMPLEMENT_DYNAMIC(FindSigsDlg, CDialog)

FindSigsDlg::FindSigsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FindSigsDlg::IDD, pParent)
{

}

FindSigsDlg::~FindSigsDlg()
{
}

void FindSigsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_inpStubMap);
	DDX_Control(pDX, IDC_EDIT9, m_inpClst1);
	DDX_Control(pDX, IDC_EDIT10, m_inpInd1);
	DDX_Control(pDX, IDC_EDIT_SMIM2, m_inpInd2);
	DDX_Control(pDX, IDC_EDIT7, m_inpClst2);
	DDX_Control(pDX, IDC_EDIT3, m_mode);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_BTN_ECFG, m_eCFG);
	DDX_Control(pDX, IDOK, m_start);
	DDX_Control(pDX, IDC_CHECK1, m_selI2);
	DDX_Control(pDX, IDC_CHECK2, m_selC2);
	DDX_Control(pDX, IDC_BTN_SELINP4, m_browseI2);
	DDX_Control(pDX, IDC_SELDEP5, m_depI2);
	DDX_Control(pDX, IDC_BTN_SELINP5, m_browseC2);
	DDX_Control(pDX, IDC_SELDEP6, m_depC2);
	DDX_Control(pDX, IDC_EDIT11, m_minCov);
	DDX_Control(pDX, IDC_EDIT12, m_stdev);
}


BEGIN_MESSAGE_MAP(FindSigsDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CRCFG, &FindSigsDlg::OnBnClickedBtnCrcfg)
	ON_BN_CLICKED(IDC_BTN_ECFG, &FindSigsDlg::OnBnClickedBtnEcfg)
	ON_BN_CLICKED(IDOK, &FindSigsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &FindSigsDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &FindSigsDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELINP2, &FindSigsDlg::OnBnClickedBtnSelinp2)
	ON_BN_CLICKED(IDC_SELDEP3, &FindSigsDlg::OnBnClickedSeldep2)
	ON_BN_CLICKED(IDC_BTN_SELINP3, &FindSigsDlg::OnBnClickedBtnSelinp3)
	ON_BN_CLICKED(IDC_SELDEP4, &FindSigsDlg::OnBnClickedSeldep3)
	ON_BN_CLICKED(IDC_BTN_SELINP4, &FindSigsDlg::OnBnClickedBtnSelinp4)
	ON_BN_CLICKED(IDC_SELDEP5, &FindSigsDlg::OnBnClickedSeldep4)
	ON_BN_CLICKED(IDC_BTN_SELINP5, &FindSigsDlg::OnBnClickedBtnSelinp5)
	ON_BN_CLICKED(IDC_SELDEP6, &FindSigsDlg::OnBnClickedSeldep5)
	ON_BN_CLICKED(IDC_BTN_SELFSOUT, &FindSigsDlg::OnBnClickedBtnSelfsout)
	ON_BN_CLICKED(IDC_CHECK1, &FindSigsDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &FindSigsDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// FindSigsDlg message handlers

void FindSigsDlg::OnBnClickedBtnCrcfg()
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
		m_inpStubMap.GetWindowText(param);
		CT2CA asciiParam(param);
		string sParam(asciiParam);
		fout << "stubMap = " << sParam << endl;

		m_inpClst1.GetWindowText(param);
		CT2CA asciiParam2(param);
		sParam = asciiParam2;
		fout << "fileGroupFile = " << sParam << endl;
		fout << "#groupThresholdRatio  = 0.1" << endl;
		fout << "#groupCountThreshold  = 4" << endl;

		m_inpInd1.GetWindowText(param);
		CT2CA asciiParam3(param);
		sParam = asciiParam3;
		fout << "fpIndexFile = " << sParam << endl;

		if (m_selI2.GetCheck())
		{
			m_inpInd2.GetWindowText(param);
			CT2CA asciiParam4(param);
			sParam = asciiParam4;
			fout << "fpIndexFile2 = " << sParam << endl;
		}
		else
			fout << "#fpIndexFile2 = " << endl;

		m_minCov.GetWindowText(param);
		CT2CA asciiParam5(param);
		sParam = asciiParam5;
		fout << "sigMinCoverage = " << sParam << endl;

		m_stdev.GetWindowText(param);
		CT2CA asciiParam6(param);
		sParam = asciiParam6;
		fout << "StDevFileOffset = " << sParam << endl;

		m_mode.GetWindowText(param);
		CT2CA asciiParam7(param);
		sParam = asciiParam7;
		fout << "fileBufferMode = " << sParam << endl;
		fout << "#dualSigs" << endl;
		fout << "#triSigs" << endl;
		fout << "#findRedundantSigs" << endl;
		fout << "#queueSize = 10" << endl;

		if (m_selC2.GetCheck())
		{
			m_inpClst2.GetWindowText(param);
			CT2CA asciiParam8(param);
			sParam = asciiParam8;
			fout << "superGroupFile = " << sParam << endl;
		}
		else
			fout << "#superGroupFile = " << endl;
		
		fout << "#groupThresholdRatioOutsideSuperGroup = 0.5" << endl;

		fout.close();
		m_eCFG.EnableWindow(TRUE);
		m_start.EnableWindow(TRUE);
	}
}

void FindSigsDlg::OnBnClickedBtnEcfg()
{
	// TODO: Add code for editing a cfg file
	EditCFGDlg ecfg(m_cfgname);
	ecfg.DoModal();
}

void FindSigsDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	OnOK();
}

void FindSigsDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking an input stub map
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Stub Maps(*.bin)|*.bin|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_inpStubMap.SetWindowText(fullFilePath);
	}
}

void FindSigsDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies for an input stub map (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp2()
{
	// TODO: Add code for picking an input cluster (#1)
	CFileDialog inBox2(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Clusterings(*.txt)|*.txt|All Files(*.*)|*.*||"));
	if (inBox2.DoModal() == IDOK)
	{
		CString fullFilePath = inBox2.GetFolderPath() + _T("\\") + inBox2.GetFileName();
		m_inpClst1.SetWindowText(fullFilePath);
	}
}

void FindSigsDlg::OnBnClickedSeldep2()
{
	// TODO: Add code for dependencies for an input cluster (#1) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp3()
{
	// TODO: Add code for picking an input index (#1)
	CFileDialog inBox3(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*||"));
	if (inBox3.DoModal() == IDOK)
	{
		CString fullFilePath = inBox3.GetFolderPath() + _T("\\") + inBox3.GetFileName();
		m_inpInd1.SetWindowText(fullFilePath);
	}
}

void FindSigsDlg::OnBnClickedSeldep3()
{
	// TODO: Add code for dependencies for an input index (#1) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp4()
{
	// TODO: Add code for picking an input index (#2)
	CFileDialog inBox3(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*||"));
	if (inBox3.DoModal() == IDOK)
	{
		CString fullFilePath = inBox3.GetFolderPath() + _T("\\") + inBox3.GetFileName();
		m_inpInd2.SetWindowText(fullFilePath);
	}
}

void FindSigsDlg::OnBnClickedSeldep4()
{
	// TODO: Add code for dependencies for an input index (#2) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelinp5()
{
	// TODO: Add code for picking an input cluster (#2)
	CFileDialog inBox2(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Clusterings(*.txt)|*.txt|All Files(*.*)|*.*||"));
	if (inBox2.DoModal() == IDOK)
	{
		CString fullFilePath = inBox2.GetFolderPath() + _T("\\") + inBox2.GetFileName();
		m_inpClst2.SetWindowText(fullFilePath);
	}
}

void FindSigsDlg::OnBnClickedSeldep5()
{
	// TODO: Add code for dependencies for an input cluster (#2) (if applicable)
}

void FindSigsDlg::OnBnClickedBtnSelfsout()
{
	// TODO: Add code for selecting output
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetFolderPath() + _T("\\") + outBox.GetFileName();
		m_output.SetWindowText(fullFilePath);
	}
}

void FindSigsDlg::OnBnClickedCheck1()
{
	// TODO: Add code for enabling input index 2
	BOOL checkState = m_selI2.GetCheck();
	m_inpInd2.EnableWindow(checkState);
	m_browseI2.EnableWindow(checkState);
	m_depI2.EnableWindow(checkState);
}

void FindSigsDlg::OnBnClickedCheck2()
{
	// TODO: Add code for enabling input cluster 2
	BOOL checkState = m_selC2.GetCheck();
	m_inpClst2.EnableWindow(checkState);
	m_browseC2.EnableWindow(checkState);
	m_depC2.EnableWindow(checkState);
}
