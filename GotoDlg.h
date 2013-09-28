#if !defined(AFX_GOTODLG_H__68F87D68_7241_493A_88D8_781A3C0B82F4__INCLUDED_)
#define AFX_GOTODLG_H__68F87D68_7241_493A_88D8_781A3C0B82F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GotoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg dialog

class CGotoDlg : public CDialog
{
// Construction
public:
	CGotoDlg(CWnd* pParent = NULL);   // standard constructor

  int GetHours(void);
  int GetMinutes(void);
  int GetSeconds(void);

public:
// Dialog Data
	//{{AFX_DATA(CGotoDlg)
	enum { IDD = IDD_GOTO };
	CSpinButtonCtrl	m_Spin_S;
	CSpinButtonCtrl	m_Spin_M;
	CSpinButtonCtrl	m_Spin_H;
	CString	m_strGoto_Hours;
	CString	m_strGoto_Minutes;
	CString	m_strGoto_Seconds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTODLG_H__68F87D68_7241_493A_88D8_781A3C0B82F4__INCLUDED_)
