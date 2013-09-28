#if !defined(AFX_PPAGESUBTITLES_H__65577831_86D7_449F_8215_868C3E8B032B__INCLUDED_)
#define AFX_PPAGESUBTITLES_H__65577831_86D7_449F_8215_868C3E8B032B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageSubtitles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageSubtitles dialog

class CPPageSubtitles : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageSubtitles)

// Construction
public:
	CPPageSubtitles();
	~CPPageSubtitles();

// Dialog Data
	//{{AFX_DATA(CPPageSubtitles)
	enum { IDD = IDD_PROPPAGE_SUBTITLES };
	BOOL	m_bAutoloadSubtitles;
	CString	m_strSubtitleFont;
	int		m_nSubCP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSubtitles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageSubtitles)
	afx_msg void OnButtonPickfont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESUBTITLES_H__65577831_86D7_449F_8215_868C3E8B032B__INCLUDED_)
