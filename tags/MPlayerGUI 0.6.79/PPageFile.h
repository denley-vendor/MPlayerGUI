#if !defined(AFX_PPAGEFILE_H__983DA000_9A9D_4BF1_AFF7_993397F29B04__INCLUDED_)
#define AFX_PPAGEFILE_H__983DA000_9A9D_4BF1_AFF7_993397F29B04__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageFile dialog

class CPPageFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageFile)

// Construction
public:
	CPPageFile();
	~CPPageFile();

// Dialog Data
	//{{AFX_DATA(CPPageFile)
	enum { IDD = IDD_PROPPAGE_FILE };
	CString	m_strAspectRatio;
	CString	m_strAudioCodec;
	CString	m_strBitRate;
	CString	m_strLength;
	CString	m_strLocation;
	CString	m_strMediaType;
	CString	m_strVideoCodec;
	CString	m_strVideoSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageFile)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEFILE_H__983DA000_9A9D_4BF1_AFF7_993397F29B04__INCLUDED_)
