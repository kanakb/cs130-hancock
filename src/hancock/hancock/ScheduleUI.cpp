// ScheduleUI.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "ScheduleUI.h"
#include "Scheduler.h"
#include <list>
#include <string>
using namespace std;


// ScheduleUI dialog

IMPLEMENT_DYNAMIC(ScheduleUI, CDialog)

ScheduleUI::ScheduleUI(BOOL dep, Scheduler *sched, CWnd* pParent /*=NULL*/)
	: CDialog(ScheduleUI::IDD, pParent), m_sched(sched), m_dep(dep)
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

	m_taskList.InsertColumn(0, _T("Task"), LVCFMT_LEFT, 200);
	m_taskList.InsertColumn(1, _T("Time Added"), LVCFMT_LEFT, 200);
	m_taskList.InsertColumn(2, _T("Status"), LVCFMT_LEFT, 200);

	list<Scheduler::actData *> *actList = m_sched->getActList();
	m_actions = actList;
	list<Scheduler::actData *>::iterator it = actList->begin();
	int row = 0;
	for (; it != actList->end(); it++)
	{
		// Get all tasks, start times, statuses
		string aName = (*it)->m_action->getName();
		string aTime = (*it)->startTime;
		int aStatus = (*it)->status;
		CString taskName(aName.c_str());
		CString taskTime(aTime.c_str());
		CString taskStatus;
		taskStatus.Format(_T("%d"), aStatus);
		m_taskList.InsertItem(row, taskName);
		m_taskList.SetItemText(row, 1, taskTime);
		m_taskList.SetItemText(row, 2, taskStatus);
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
		list<Scheduler::actData *>::iterator it = m_actions->begin();
		int index = 0;
		for (; it != m_actions->end() && index != nItem; it++)
			index++;
		// Get selected action, list dependencies
		if (it != m_actions->end())
		{
			list<Scheduler::actData *> deps = (*it)->dependencies;
			CString depText = _T("Dependencies:\n\r");
			list<Scheduler::actData *>::iterator it2 = deps.begin();
			for (; it2 != deps.end(); it++)
			{
				CString name((*it2)->m_action->getName().c_str());
				depText = depText + name + _T("\n\r");
			}
			m_depText.SetWindowText(depText);
		}
	}
	*pResult = 0;
}

void ScheduleUI::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void ScheduleUI::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
