#if !defined(AFX_PPAGEPLAYER_H__674FF938_7C17_4837_B43A_1EA4716612F6__INCLUDED_)
#define AFX_PPAGEPLAYER_H__674FF938_7C17_4837_B43A_1EA4716612F6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPagePlayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPagePlayer dialog

class CPPagePlayer : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPagePlayer)

// Construction
public:
	CPPagePlayer();
	~CPPagePlayer();

// Dialog Data
	//{{AFX_DATA(CPPagePlayer)
	enum { IDD = IDD_PROPPAGE_PLAYER };
	BOOL	m_bShowToolbar;
	BOOL	m_bShowStatusBar;
	BOOL	m_bShowProgressBar;
	BOOL	m_bShowPlaylist;
	int		m_nSSDisableMode;
	BOOL	m_bAllowMultipleInstances;
	BOOL	m_bAutoShuffle;
	BOOL	m_bStartupAlwaysOnTop;
	BOOL	m_bLaunchInFullscreen;
	int		m_nPresetZoom;
	BOOL	m_bRememberLastPlaybackPosition;
	BOOL	m_bShowControlsInFullscreen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPagePlayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPagePlayer)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEPLAYER_H__674FF938_7C17_4837_B43A_1EA4716612F6__INCLUDED_)
