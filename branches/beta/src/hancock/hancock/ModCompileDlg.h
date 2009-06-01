#pragma once
#include "afxwin.h"
#include "Scheduler.h"
#include <list>


// ModCompileDlg dialog

class ModCompileDlg : public CDialog
{
	DECLARE_DYNAMIC(ModCompileDlg)

public:
	ModCompileDlg(Scheduler *sched, CWnd* pParent = NULL);   // standard constructor
	virtual ~ModCompileDlg();

// Dialog Data
	enum { IDD = IDD_COMPILEMOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
private:
	CEdit m_input;
	Scheduler *m_sched;
	std::list<Scheduler::actData*> m_deps;
};
