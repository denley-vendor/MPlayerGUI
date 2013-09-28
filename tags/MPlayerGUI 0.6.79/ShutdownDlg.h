#if !defined(AFX_SHUTDOWNDLG_H__51311E56_090D_4E96_BC1F_92FF0CAF276A__INCLUDED_)
#define AFX_SHUTDOWNDLG_H__51311E56_090D_4E96_BC1F_92FF0CAF276A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShutdownDlg.h : header file
//

#include "Logoff.h"

/////////////////////////////////////////////////////////////////////////////
// CShutdownDlg dialog

class CShutdownDlg : public CDialog
{
// Construction
public:
	CShutdownDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShutdownDlg)
	enum { IDD = IDD_SHUTDOWN };
	CString	m_strShutdownCounter;
	//}}AFX_DATA

  int m_nCounter;
  CLogoff m_Logoff;

  void DoShutdown(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShutdownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShutdownDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUTDOWNDLG_H__51311E56_090D_4E96_BC1F_92FF0CAF276A__INCLUDED_)
