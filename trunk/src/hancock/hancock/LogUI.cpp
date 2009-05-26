// LogUI.cpp : implementation file
//

#include "stdafx.h"
#include "hancock.h"
#include <string>
#include "LogUI.h"
#include <windows.h>
#include <io.h>






// LogUI dialog

//returns the older of two filenames
bool cmpFileNames(const CString& cs2, const CString& cs1);

IMPLEMENT_DYNAMIC(LogUI, CDialog)

LogUI::LogUI(HancockLog *hlog, CWnd* pParent /*=NULL*/)
	: CDialog(LogUI::IDD, pParent), m_log(hlog)
{

}

LogUI::~LogUI()
{
}

void LogUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_closeBtn);
	DDX_Control(pDX, IDC_LOGLIST, m_logList);
	DDX_Control(pDX, IDC_LOGTEXT, m_logText);

	//Populates Left Pane with files in log folder
	list<CString> names;
	list<CString>::iterator it;
	this->getLogFiles(&names);
	names.sort(cmpFileNames);
	int i=0;
	for (it=names.begin(); it!=names.end(); ++it){
		CString cs = *it;
		m_logList.InsertString(i,cs);
		m_logList.SetCurSel(i);
		i++;
	}
	
	//Populates Main Pane with Current Log File
	CString currLog(m_log->dispCurrLog().c_str());
	m_logText.SetWindowText(currLog);

}


BEGIN_MESSAGE_MAP(LogUI, CDialog)
	ON_LBN_SELCHANGE(IDC_LOGLIST, &LogUI::OnLbnSelchangeLoglist)
	ON_BN_CLICKED(IDOK, &LogUI::OnBnClickedOk)
END_MESSAGE_MAP()


// LogUI message handlers

void LogUI::OnLbnSelchangeLoglist()
{
	CString csBuff;
	int i = m_logList.GetCurSel();
	m_logList.GetText(i,csBuff);
	
	CT2CA buff1(csBuff);

	string path (buff1);
	path = m_log->getDir() + path;
	const char * fname = path.c_str();
	CString logText(m_log->dispLog(fname).c_str());
	m_logText.SetWindowText(logText);

}

void LogUI::OnBnClickedOk()
{
	OnOK();
	DestroyWindow();
}

BOOL LogUI::Create(UINT nID, CWnd * pWnd)
{
	return CDialog::Create(nID,pWnd);
}

void LogUI::PostNcDestroy() {
	//delete this;
}

void LogUI::getLogFiles(list<CString>* fileList){
	
	struct _finddatai64_t data;
	// First create the filename that will be use to initialize the find.
	// "*.*" are wild card characters that tells the find function to return a
	// list of all the files and directories.  You can limit this if you wish
	// to just file with specific extensions, for example "*.txt".  If you do that
	// then finder will not return any directory names.
	string fname = m_log->getDir() + "\\*.txt";
	
	

	// start the finder -- on error _findfirsti64() will return -1, otherwise if no
	// error it returns a handle greater than -1.
	long h = _findfirsti64(fname.c_str(),&data);
	if (h>0){
		
		do{
			const CString cs(data.name);
			fileList->push_back(cs);
		}while( _findnexti64(h,&data) == 0);
		
		_findclose(h);
	
	}


}
bool cmpFileNames(const CString& cs2, const CString& cs1){
	//compares year
	for (int i = 6; i < 10; i++){
		if (cs1[i]>cs2[i])
			return true;
		else if (cs1[i]<cs2[i])
			return false;
	}

	//compares month, day
	for (int i = 0; i < 6; i++){
		if (cs1[i]>cs2[i])
			return true;
		else if (cs1[i]<cs2[i])
			return false;
	}

	//compares hours, minutes, milliseconds
	for (int i = 11; i < 20; i++){
		if (cs1[i]>cs2[i])
			return true;
		else if (cs1[i]<cs2[i])
			return false;
	}
	
	return true;
}
	