// hancock.h : main header file for the hancock application
// Note: Extensively uses Microsoft example code for Fluent UI
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// ChancockApp:
// See hancock.cpp for the implementation of this class
//

class ChancockApp : public CWinAppEx
{
public:
	ChancockApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern ChancockApp theApp;
