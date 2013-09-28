#if !defined(AFX_PPAGECOMMANDS_H__D3B2C966_BF46_4C8C_9651_448703483944__INCLUDED_)
#define AFX_PPAGECOMMANDS_H__D3B2C966_BF46_4C8C_9651_448703483944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageCommands.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageCommands dialog

class CPPageCommands : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageCommands)

// Construction
public:
	CPPageCommands();
	~CPPageCommands();

// Dialog Data
	//{{AFX_DATA(CPPageCommands)
	enum { IDD = IDD_PROPPAGE_COMMANDS };
	CString	m_strF1CMD;
	CString	m_strF2CMD;
	CString	m_strF3CMD;
	CString	m_strF4CMD;
	CString	m_strF5CMD;
	CString	m_strF6CMD;
	CString	m_strF7CMD;
	CString	m_strF8CMD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageCommands)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageCommands)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGECOMMANDS_H__D3B2C966_BF46_4C8C_9651_448703483944__INCLUDED_)
