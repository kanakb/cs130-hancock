// PruneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "PruneDlg.h"
#include "Action.h"
#include "Scheduler.h"
#include <string>
#include <list>
#include <vector>
using namespace std;


// PruneDlg dialog

IMPLEMENT_DYNAMIC(PruneDlg, CDialog)

PruneDlg::PruneDlg(Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(PruneDlg::IDD, pParent), m_sched(sched)
{

}

PruneDlg::~PruneDlg()
{
}

void PruneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PRUNE_INP, m_input);
	DDX_Control(pDX, IDC_EDIT4, m_thresholds);
}


BEGIN_MESSAGE_MAP(PruneDlg, CDialog)
	ON_BN_CLICKED(IDOK, &PruneDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELINP1, &PruneDlg::OnBnClickedBtnSelinp1)
	ON_BN_CLICKED(IDC_SELDEP1, &PruneDlg::OnBnClickedSeldep1)
END_MESSAGE_MAP()


// PruneDlg message handlers

void PruneDlg::OnBnClickedOk()
{
	// TODO: Add code for starting the action
	std::list<string> inputs;
	std::list<string> outputs;
	std::vector<string> vParam;

	// Process inputs
	CString in;
	m_input.GetWindowText(in);
	CT2CA asciiInp1(in);
	inputs.push_back(string(asciiInp1));
	vParam.push_back(string(asciiInp1));

	CString thresholds;
	m_thresholds.GetWindowText(thresholds);
	CT2CA asciiThresh(thresholds);
	vParam.push_back(string(asciiThresh));

	//Process outputs (none at the moment)

	// Schedule action
	Action *act = new Action("C:\\sandbox\\PruneModel\\", "PruneModel.exe", vParam);
	m_sched->addAction(act, m_deps, inputs, outputs);
	OnOK();
}

void PruneDlg::OnBnClickedBtnSelinp1()
{
	// code for picking an input file
	CFileDialog inBox1(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Models(*.mdl)|*.mdl|All Files(*.*)|*.*||"));
	if (inBox1.DoModal() == IDOK)
	{
		CString fullFilePath = inBox1.GetFolderPath() + _T("\\") + inBox1.GetFileName();
		m_input.SetWindowText(fullFilePath);
	}
}

void PruneDlg::OnBnClickedSeldep1()
{
	// TODO: Add code for dependencies (if applicable)
}
