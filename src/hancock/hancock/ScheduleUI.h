#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Scheduler.h"
#include <list>


// ScheduleUI dialog

class ScheduleUI : public CDialog
{
	DECLARE_DYNAMIC(ScheduleUI)

public:
	ScheduleUI(BOOL dep, Scheduler *sched, CWnd* pParent = NULL);   // standard constructor
	virtual ~ScheduleUI();

// Dialog Data
	enum { IDD = IDD_SCHEDUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_taskList;
	CEdit m_depText;
	Scheduler *m_sched;
	std::list<Scheduler::actData *> *m_actions;

public:
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
private:
	CButton m_btnSave;
	BOOL m_dep;
};
