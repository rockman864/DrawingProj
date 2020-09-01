
// DrawingProj.h : main header file for the DrawingProj application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDrawingProjApp:
// See DrawingProj.cpp for the implementation of this class
//

class CDrawingProjApp : public CWinApp
{
public:
	CDrawingProjApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawingProjApp theApp;
