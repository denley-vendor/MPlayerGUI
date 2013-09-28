#if !defined(AFX_PPAGEPATH_H__F185FAAF_DC32_49DA_8B4F_34722F30490B__INCLUDED_)
#define AFX_PPAGEPATH_H__F185FAAF_DC32_49DA_8B4F_34722F30490B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPagePath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPagePath dialog

class CPPagePath : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPagePath)

// Construction
public:
	CPPagePath();
	~CPPagePath();

  CString m_strAppDirectory;

// Dialog Data
	//{{AFX_DATA(CPPagePath)
	enum { IDD = IDD_PROPPAGE_PATH };
	int		m_nUseDefault;
	CString	m_strMPlayerPathName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPagePath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPagePath)
	afx_msg void OnButtonPathnamebrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEPATH_H__F185FAAF_DC32_49DA_8B4F_34722F30490B__INCLUDED_)
