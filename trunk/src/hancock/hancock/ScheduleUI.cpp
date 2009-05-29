// ScheduleUI.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ScheduleUI.h"
#include "Scheduler.h"
#include "SelDepDlg.h"
#include <list>
#include <string>
using namespace std;


// ScheduleUI dialog

IMPLEMENT_DYNAMIC(ScheduleUI, CDialog)

ScheduleUI::ScheduleUI(BOOL dep, Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(ScheduleUI::IDD, pParent), m_sched(sched), m_dep(dep), m_curAct(NULL), m_depFile(_T(""))
{
}

ScheduleUI::~ScheduleUI()
{
}

void ScheduleUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_taskList);
	DDX_Control(pDX, IDC_EDIT1, m_depText);
	DDX_Control(pDX, IDOK, m_btnSave);

	// Show save button if selecting dependencies
	m_btnSave.ShowWindow(m_dep);

	m_taskList.InsertColumn(0, _T("Task"), LVCFMT_LEFT, 150);
	m_taskList.InsertColumn(1, _T("Time Started"), LVCFMT_LEFT, 100);
	m_taskList.InsertColumn(2, _T("Time Ended"), LVCFMT_LEFT, 100);
	m_taskList.InsertColumn(3, _T("Status"), LVCFMT_LEFT, 90);

	list<Scheduler::actData *> *actList = m_sched->getActList();
	m_actions = actList;
	list<Scheduler::actData *>::iterator it = actList->begin();
	int row = 0;
	for (; it != actList->end(); it++)
	{
		// Get all tasks, start times, statuses
		string aName = (*it)->m_action->getName();
		string aTime = (*it)->startTime;
		string aETime = (*it)->endTime;
		int aStatus = (*it)->status;
		CString taskName(aName.c_str());
		CString taskTime(aTime.c_str());
		CString endTime(aETime.c_str());
		CString taskStatus;

		if (aStatus == WAITING)
			taskStatus = _T("Waiting");
		else if (aStatus == RUNNING)
			taskStatus = _T("Running");
		else if (aStatus == COMPLETED)
			taskStatus = _T("Completed");
		else if (aStatus == UNSUCCESSFUL)
			taskStatus = _T("Failed");
		else
			taskStatus = _T("Unknown");
		m_taskList.InsertItem(row, taskName);
		m_taskList.SetItemText(row, 1, taskTime);
		m_taskList.SetItemText(row, 2, endTime);
		m_taskList.SetItemText(row, 3, taskStatus);
	}
}


BEGIN_MESSAGE_MAP(ScheduleUI, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &ScheduleUI::OnLvnItemchangedList3)
	ON_BN_CLICKED(IDCANCEL, &ScheduleUI::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &ScheduleUI::OnBnClickedOk)
END_MESSAGE_MAP()


// ScheduleUI message handlers

void ScheduleUI::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	POSITION pos = m_taskList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_taskList.GetNextSelectedItem(pos);
		int nSize = m_taskList.GetItemCount();
		list<Scheduler::actData *>::iterator it = m_actions->begin();
		int index = 0;
		for (; it != m_actions->end() && (nSize - index - 1) != nItem; it++)
			index++;
		// Get selected action, list dependencies, inputs, outputs
		if (it != m_actions->end())
		{
			m_curAct = *it;
			// list dependencies
			list<Scheduler::actData *> deps = (*it)->dependencies;
			CString depText = _T("Dependencies:");
			list<Scheduler::actData *>::iterator it2 = deps.begin();
			if (it2 == deps.end())
				depText += _T(" None");
			depText += _T("\r\n");
			for (; it2 != deps.end(); it2++)
			{
				CString name((*it2)->m_action->getName().c_str());
				depText = depText + name + _T("\r\n");
			}

			// list inputs
			depText += _T("\r\nInputs:");
			list<string>::iterator itIn = (*it)->inputs.begin();
			if (itIn == (*it)->inputs.end())
				depText += _T(" None");
			depText += _T("\r\n");
			for (; itIn != (*it)->inputs.end(); itIn++)
			{
				CString inp(itIn->c_str());
				depText += inp + _T("\r\n");
			}

			//list outputs
			depText += _T("\r\nOutputs:");
			list<string>::iterator itOut = (*it)->outputs.begin();
			if (itOut == (*it)->outputs.end())
				depText += _T(" None");
			depText += _T("\r\n");
			for (; itOut != (*it)->outputs.end(); itOut++)
			{
				CString out(itOut->c_str());
				depText += out + _T("\r\n");
			}
			// display everything
			m_depText.SetWindowText(depText);
		}
	}
	*pResult = 0;
}

void ScheduleUI::OnBnClickedCancel()
{
	OnCancel();
}

void ScheduleUI::OnBnClickedOk()
{
	// This button only shows up when picking dependencies
	// Given a selected dependency, spawn a new UI to query for the specific filename
	if (m_curAct != NULL)
	{
		if (m_curAct->status == RUNNING || m_curAct->status == WAITING)
		{
			SelDepDlg chooser(m_curAct);
			if (chooser.DoModal() == IDOK)
			{
				chooser.getFileString(m_depFile);
			}
		}
		else
			MessageBox(_T("Dependencies can only be selected for queued or running actions."));
	}
	OnOK();
}

void ScheduleUI::getFileString(CString &file)
{
	file = m_depFile;
}

Scheduler::actData* ScheduleUI::getCurAct()
{
	return m_curAct;
}
