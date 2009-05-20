// MakeModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "MakeModelDlg.h"


// MakeModelDlg dialog

IMPLEMENT_DYNAMIC(MakeModelDlg, CDialog)

MakeModelDlg::MakeModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MakeModelDlg::IDD, pParent)
{

}

MakeModelDlg::~MakeModelDlg()
{
}

void MakeModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MakeModelDlg, CDialog)
END_MESSAGE_MAP()


// MakeModelDlg message handlers

void MakeModelDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
