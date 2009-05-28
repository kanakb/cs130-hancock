#pragma once
#include "afxwin.h"
#include "Scheduler.h"
#include <list>


// PruneDlg dialog

class PruneDlg : public CDialog
{
	DECLARE_DYNAMIC(PruneDlg)

public:
	PruneDlg(Scheduler *sched, CWnd* pParent = NULL);   // standard constructor
	virtual ~PruneDlg();

// Dialog Data
	enum { IDD = IDD_PRUNEMOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
private:
	CEdit m_input;
	CEdit m_thresholds;
	Scheduler *m_sched;
	std::list<Scheduler::actData*> m_deps;
};
