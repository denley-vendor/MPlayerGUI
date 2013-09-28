// MPlayerGUI.h : main header file for the MPLAYERGUI application
//

#if !defined(AFX_MPLAYERGUI_H__FCB864A9_6CB7_4D98_9D29_5A5A99D204C7__INCLUDED_)
#define AFX_MPLAYERGUI_H__FCB864A9_6CB7_4D98_9D29_5A5A99D204C7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define MPLAYERGUI_WND_CLASS_NAME "MPlayerGUIUniqueClassName"

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIApp:
// See MPlayerGUI.cpp for the implementation of this class
//

class CMPlayerGUIApp : public CWinApp
{
public:
	CMPlayerGUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPlayerGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMPlayerGUIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPLAYERGUI_H__FCB864A9_6CB7_4D98_9D29_5A5A99D204C7__INCLUDED_)
