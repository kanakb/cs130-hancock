// MakeIndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MakeIndexDlg.h"
#include "FolderDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include "ScheduleUI.h"
#include <list>
#include <string>
#include <vector>
using namespace std;


// MakeIndexDlg dialog

IMPLEMENT_DYNAMIC(MakeIndexDlg, CDialog)

MakeIndexDlg::MakeIndexDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(MakeIndexDlg::IDD, pParent), m_sched(sched)
{
}

MakeIndexDlg::~MakeIndexDlg()
{
}

void MakeIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAKEIND_INP, m_input);
	DDX_Control(pDX, IDC_EDIT4, m_output);
	DDX_Control(pDX, IDC_COMBO_INDMODE, m_mode);
}


BEGIN_MESSAGE_MAP(MakeIndexDlg, CDialog)
	ON_BN_CLICKED(IDOK, &MakeIndexDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &MakeIndexDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &MakeIndexDlg::OnBnClickedSeldep1)
	ON_BN_CLICKED(IDC_BTN_SELOUT1, &MakeIndexDlg::OnBnClickedBtnSelout1)
END_MESSAGE_MAP()


// MakeIndexDlg message handlers

void MakeIndexDlg::OnBnClickedOk()
{
	// code for starting the action
	std::vector<string> vParam;
	std::list<string> inputs;
	std::list<string> outputs;

	// Process inputs
	CString in;
	m_input.GetWindowText(in);
	CT2CA asciiInp1(in);
	inputs.push_back(string(asciiInp1));
	vParam.push_back(string(asciiInp1));

	//Process outputs
	CString out;
	m_output.GetWindowText(out);
	CT2CA asciiOut(out);
	string aOut(asciiOut);
	outputs.push_back(aOut + "0.txt");
	outputs.push_back(aOut + "1.bin");
	outputs.push_back(aOut + "2.bin");
	vParam.push_back(aOut);

	CString mode;
	int nIndex = m_mode.GetCurSel();
	if (nIndex != CB_ERR)
	{
		if (nIndex == 0)
			vParam.push_back("binBuffer");
		else
			vParam.push_back("textBuffer");
	}
	Action *act = new Action("executables\\", "CreateBinIndex.exe", vParam);

	// Schedule action
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void MakeIndexDlg::OnBnClickedBtnSelinp1()
{
	// code for picking an input directory
	CString defPath = _T("");
	CFolderDialog inDir1(_T("Input Directory"), defPath, this, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	if (inDir1.DoModal() == IDOK)
	{
		m_input.SetWindowText(inDir1.GetFolderPath());
	}
}

void MakeIndexDlg::OnBnClickedSeldep1()
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

void MakeIndexDlg::OnBnClickedBtnSelout1()
{
	// code for picking an input file
	CFileDialog outBox(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*||"));
	if (outBox.DoModal() == IDOK)
	{
		CString fullFilePath = outBox.GetPathName();
		m_output.SetWindowText(fullFilePath);
	}
}
