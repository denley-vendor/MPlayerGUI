#if !defined(AFX_SENDCOMMANDDLG_H__6057610A_0B80_4A37_9839_166B3BCBA0DA__INCLUDED_)
#define AFX_SENDCOMMANDDLG_H__6057610A_0B80_4A37_9839_166B3BCBA0DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendCommandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendCommandDlg dialog

class CSendCommandDlg : public CDialog
{
// Construction
public:
	CSendCommandDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendCommandDlg)
	enum { IDD = IDD_SENDCOMMAND };
	CString	m_strCommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendCommandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
  void GetCommand(CString &strCommand);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendCommandDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDCOMMANDDLG_H__6057610A_0B80_4A37_9839_166B3BCBA0DA__INCLUDED_)
