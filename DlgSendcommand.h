#if !defined(AFX_DLGSENDCOMMAND_H__4FBE0D99_CAE0_4624_8FAE_A58FE9C16E9B__INCLUDED_)
#define AFX_DLGSENDCOMMAND_H__4FBE0D99_CAE0_4624_8FAE_A58FE9C16E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSendcommand.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSendcommand dialog

class CDlgSendcommand : public CDialog
{
// Construction
public:
	CDlgSendcommand(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSendcommand)
	enum { IDD = IDD_SENDCOMMAND };
	CString	m_strSendCommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSendcommand)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSendcommand)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSENDCOMMAND_H__4FBE0D99_CAE0_4624_8FAE_A58FE9C16E9B__INCLUDED_)
