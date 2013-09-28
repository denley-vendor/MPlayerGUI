#if !defined(AFX_PPAGECONTENT_H__DDBE5F47_7E53_4E9A_B529_A2B23371F60C__INCLUDED_)
#define AFX_PPAGECONTENT_H__DDBE5F47_7E53_4E9A_B529_A2B23371F60C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageContent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageContent dialog

class CPPageContent : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageContent)

// Construction
public:
	CPPageContent();
	~CPPageContent();

// Dialog Data
	//{{AFX_DATA(CPPageContent)
	enum { IDD = IDD_PROPPAGE_CONTENT };
	CString	m_strAlbum;
	CString	m_strArtist;
	CString	m_strComments;
	CString	m_strComposer;
	CString	m_strCopyright;
	CString	m_strGenre;
	CString	m_strTitle;
	CString	m_strRating;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageContent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageContent)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGECONTENT_H__DDBE5F47_7E53_4E9A_B529_A2B23371F60C__INCLUDED_)
