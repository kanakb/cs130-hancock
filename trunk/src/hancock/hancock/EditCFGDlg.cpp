// EditCFGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include "EditCFGDlg.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


// EditCFGDlg dialog

IMPLEMENT_DYNAMIC(EditCFGDlg, CDialog)

EditCFGDlg::EditCFGDlg(string filename, CWnd* pParent /*=NULL*/)
	: m_filename(filename), CDialog(EditCFGDlg::IDD, pParent)
{
}

EditCFGDlg::~EditCFGDlg()
{
}

void EditCFGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_text);

	// Read in configuration file, place on text box
	ifstream fin(m_filename.c_str());
	string line;
	string text = "";
	while(fin)
	{
		getline(fin, line);
		if (line != "")
			text += line + "\r\n";
	}
	CString wtext(text.c_str());
	m_text.SetWindowText(wtext);
	fin.close();
}


BEGIN_MESSAGE_MAP(EditCFGDlg, CDialog)
	ON_BN_CLICKED(IDOK, &EditCFGDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &EditCFGDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// EditCFGDlg message handlers

void EditCFGDlg::OnBnClickedOk()
{
	// Get everything in text box, write to file
	CString wtext;
	m_text.GetWindowText(wtext);
	CT2CA asciiText(wtext);
	string text(asciiText);
	string textOut = "";

	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] != '\r')
			textOut += text[i];
	}

	ofstream fout(m_filename.c_str());
	fout << textOut;
	fout.close();

	OnOK();
}

void EditCFGDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
