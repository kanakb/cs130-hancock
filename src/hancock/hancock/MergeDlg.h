#pragma once
#include "afxwin.h"
#include "Scheduler.h"
#include <string>
#include <list>


// MergeDlg dialog

class MergeDlg : public CDialog
{
	DECLARE_DYNAMIC(MergeDlg)

public:
	MergeDlg(Scheduler *sched, CWnd* pParent = NULL);   // standard constructor
	virtual ~MergeDlg();

// Dialog Data
	enum { IDD = IDD_MERGEMODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCrcfg();
	afx_msg void OnBnClickedBtnEcfg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSelinp1();
	afx_msg void OnBnClickedSeldep1();
	afx_msg void OnBnClickedBtnSelinp2();
	afx_msg void OnBnClickedSeldep2();
	afx_msg void OnBnClickedBtnSelmodout();
private:
	CEdit m_input1;
	CEdit m_path1;
	CEdit m_input2;
	CEdit m_path2;
	CEdit m_output;
	CButton m_eCFG;
	CButton m_start;
	std::string m_cfgname;
	Scheduler *m_sched;
	std::list<Scheduler::actData*> m_deps;
};
