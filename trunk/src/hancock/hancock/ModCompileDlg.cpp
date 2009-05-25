// ModCompileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ModCompileDlg.h"
#include "Action.h"
#include "Scheduler.h"
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
	// TODO: Add code for starting the action
	std::list<string> inputs;
	std::list<string> outputs;
	std::vector<string> vParam;

	// Process inputs
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
		}
	}

	//Process outputs (none at the moment)

	// Schedule action
	Action *act = new Action("C:\\sandbox\\CompileModel\\", "CompileModel.exe", vParam);
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void ModCompileDlg::OnBnClickedBtnSelinp1()
{
	// TODO: Add code for picking input files
	CString fileList;
	m_input.GetWindowText(fileList);
	CFileDialog inBox(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models (*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (inBox.DoModal() == IDOK)
	{
		CString fullFilePath = inBox.GetFolderPath() + _T("\\") + inBox.GetFileName();
		if (fileList == _T(""))
			fileList += fullFilePath;
		else
			fileList += _T("\r\n") + fullFilePath;
		m_input.SetWindowText(fileList);
	}
}

void ModCompileDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}
