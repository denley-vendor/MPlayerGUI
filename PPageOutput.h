#if !defined(AFX_PPAGEOUTPUT_H__E6DB019A_52D3_46F2_B3CA_5F4755A95214__INCLUDED_)
#define AFX_PPAGEOUTPUT_H__E6DB019A_52D3_46F2_B3CA_5F4755A95214__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageOutput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageOutput dialog

class CPPageOutput : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageOutput)

// Construction
public:
	CPPageOutput();
	~CPPageOutput();

// Dialog Data
	//{{AFX_DATA(CPPageOutput)
	enum { IDD = IDD_PROPPAGE_OUTPUT };
	int		m_nAudioOutputDriver;
	int		m_nVideoOutputDriver;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageOutput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEOUTPUT_H__E6DB019A_52D3_46F2_B3CA_5F4755A95214__INCLUDED_)
