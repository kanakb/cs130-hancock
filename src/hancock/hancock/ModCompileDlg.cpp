// ModCompileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ModCompileDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include "ScheduleUI.h"
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


// ModCompileDlg dialog

IMPLEMENT_DYNAMIC(ModCompileDlg, CDialog)

ModCompileDlg::ModCompileDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(ModCompileDlg::IDD, pParent), m_sched(sched)
{

}

ModCompileDlg::~ModCompileDlg()
{
}

void ModCompileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPILE_INP, m_input);
}


BEGIN_MESSAGE_MAP(ModCompileDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ModCompileDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &ModCompileDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &ModCompileDlg::OnBnClickedSeldep1)
END_MESSAGE_MAP()


// ModCompileDlg message handlers

void ModCompileDlg::OnBnClickedOk()
{
	// code for starting the action
	std::list<string> inputs;
	std::list<string> outputs;
	std::vector<string> vParam;

	// Process inputs and outputs
	CString models;
	m_input.GetWindowText(models);
	CT2CA aModels(models);
	string text(aModels);
	stringstream ss(text);

	while (ss)
	{
		string in;
		getline(ss, in);
		if (in != "")
		{
			inputs.push_back(in);
			vParam.push_back(in);
			size_t charIndex = in.find_last_of('.');
			if (charIndex != std::string::npos)
				in = in.substr(0, charIndex);
			in += "_Compiled.mdl";
			string out = in;
			outputs.push_back(out);
		}
	}

	//Process outputs (none at the moment)

	// Schedule action
	Action *act = new Action("executables\\", "CompileModel.exe", vParam);
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void ModCompileDlg::OnBnClickedBtnSelinp1()
{
	// code for picking input files
	CString fileList;
	m_input.GetWindowText(fileList);
	CFileDialog inBox(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models (*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (inBox.DoModal() == IDOK)
	{
		CString fullFilePath = inBox.GetPathName();
		if (fileList == _T(""))
			fileList += fullFilePath;
		else
			fileList += _T("\r\n") + fullFilePath;
		m_input.SetWindowText(fileList);
	}
}

void ModCompileDlg::OnBnClickedSeldep1()
{
	// code for dependencies (if applicable)
	CString fileList;
	m_input.GetWindowText(fileList);

	// This is somewhat different from other EXEs: need to add to current list instead of setting directly
	ScheduleUI depui(TRUE, m_sched);
	if (depui.DoModal() == IDOK)
	{
		CString depName;
		depui.getFileString(depName);
		if (depName != _T(""))
		{
			m_deps.push_back(depui.getCurAct());
			if (fileList == _T(""))
				fileList += depName;
			else
				fileList += _T("\r\n") + depName;
			m_input.SetWindowText(fileList);
		}
	}
}
