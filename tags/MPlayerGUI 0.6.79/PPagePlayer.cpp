// PPagePlayer.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPagePlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPagePlayer property page

IMPLEMENT_DYNCREATE(CPPagePlayer, CPropertyPage)

CPPagePlayer::CPPagePlayer() : CPropertyPage(CPPagePlayer::IDD)
{
	//{{AFX_DATA_INIT(CPPagePlayer)
	m_bShowToolbar = FALSE;
	m_bShowStatusBar = FALSE;
	m_bShowProgressBar = FALSE;
	m_bShowPlaylist = FALSE;
	m_nSSDisableMode = -1;
	m_bAllowMultipleInstances = FALSE;
	m_bAutoShuffle = FALSE;
	m_bStartupAlwaysOnTop = FALSE;
	m_bLaunchInFullscreen = FALSE;
	m_nPresetZoom = 0;
	m_bRememberLastPlaybackPosition = FALSE;
	m_bShowControlsInFullscreen = FALSE;
	//}}AFX_DATA_INIT
}

CPPagePlayer::~CPPagePlayer()
{
}

void CPPagePlayer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPagePlayer)
	DDX_Check(pDX, IDC_CHECK_SHOW_TOOLBAR, m_bShowToolbar);
	DDX_Check(pDX, IDC_CHECK_SHOW_STATUSBAR, m_bShowStatusBar);
	DDX_Check(pDX, IDC_CHECK_SHOW_PROGRESSBAR, m_bShowProgressBar);
	DDX_Check(pDX, IDC_CHECK_SHOW_PLAYLIST, m_bShowPlaylist);
	DDX_CBIndex(pDX, IDC_COMBO_SSDISABLEMODE, m_nSSDisableMode);
	DDX_Check(pDX, IDC_CHECK_ALLOWMULTIPLEINSTANCES, m_bAllowMultipleInstances);
	DDX_Check(pDX, IDC_CHECK_AUTOSHUFFLE, m_bAutoShuffle);
	DDX_Check(pDX, IDC_CHECK_STARTUP_AOT, m_bStartupAlwaysOnTop);
	DDX_Check(pDX, IDC_CHECK_LAUNCHINFULLSCREEN, m_bLaunchInFullscreen);
	DDX_Text(pDX, IDC_EDIT_PRESETZOOM, m_nPresetZoom);
	DDV_MinMaxInt(pDX, m_nPresetZoom, 10, 1000);
	DDX_Check(pDX, IDC_CHECK_REMEMBERLASTPLAYBACKPOSITION, m_bRememberLastPlaybackPosition);
	DDX_Check(pDX, IDC_CHECK_SHOWCONTROLSINFULLSCREEN, m_bShowControlsInFullscreen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPagePlayer, CPropertyPage)
	//{{AFX_MSG_MAP(CPPagePlayer)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPagePlayer message handlers
