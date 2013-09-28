#if !defined(AFX_PPAGEASSOCIATION_H__88A3F629_59B0_478B_8DD8_8537A1223B50__INCLUDED_)
#define AFX_PPAGEASSOCIATION_H__88A3F629_59B0_478B_8DD8_8537A1223B50__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageAssociation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageAssociation dialog

class CPPageAssociation : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageAssociation)

private:
  CString m_strApp;

  BOOL AssociateWithExtension(CString strExtension);

// Construction
public:
	CPPageAssociation();
	~CPPageAssociation();

// Dialog Data
	//{{AFX_DATA(CPPageAssociation)
	enum { IDD = IDD_PROPPAGE_ASSOCIATION };
	CEdit	m_Edit_Extensions;
	CString	m_strExtensions;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageAssociation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageAssociation)
	afx_msg void OnButtonExtLoad();
	afx_msg void OnButtonExtAssociate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEASSOCIATION_H__88A3F629_59B0_478B_8DD8_8537A1223B50__INCLUDED_)
