
// Clickomania.h : main header file for the Clickomania application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CClickomaniaApp:
// See Clickomania.cpp for the implementation of this class
//

class CClickomaniaApp : public CWinApp
{
public:
	CClickomaniaApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CClickomaniaApp theApp;
