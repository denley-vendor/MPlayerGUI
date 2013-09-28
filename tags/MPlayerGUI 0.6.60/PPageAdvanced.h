#if !defined(AFX_PPAGEADVANCED_H__E2A5C437_45A5_4E49_B767_A3808E5D5674__INCLUDED_)
#define AFX_PPAGEADVANCED_H__E2A5C437_45A5_4E49_B767_A3808E5D5674__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageAdvanced.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageAdvanced dialog

class CPPageAdvanced : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageAdvanced)

// Construction
public:
	CPPageAdvanced();
	~CPPageAdvanced();

// Dialog Data
	//{{AFX_DATA(CPPageAdvanced)
	enum { IDD = IDD_PROPPAGE_ADVANCED };
	CString	m_strMPlayerUserConfig;
	int		m_nMPlayerPriority;
	BOOL	m_bDisableMPlayerMonitor;
	BOOL	m_bEnableLogging;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageAdvanced)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageAdvanced)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEADVANCED_H__E2A5C437_45A5_4E49_B767_A3808E5D5674__INCLUDED_)
