// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MPlayerGUI.h"

#include "MainFrm.h"
#include "MPlayerGUIView.h"
#include "MPlayerGUIDoc.h"

// clip properties dialog class
// #include "ClipPropertyDlg.h"

#include "OpenURLDlg.h"
#include "GotoDlg.h"

#include "PPageAdvanced.h"
#include "PPageOutput.h"
#include "PPagePath.h"
#include "PPagePlayer.h"
#include "PPageSubtitles.h"
#include "PPageVideo.h"
#include "PPageAssociation.h"
#include "PPageCommands.h"

#include "PPageFile.h"
#include "PPageContent.h"

#include "ShutdownDlg.h"

// AppSettings
#ifndef APPSETTINGS_H
#include "AppSettings.h"
#endif
// general functions
#include "functions.h"
// CSplitPath class
// #include "splitpath.h"
#include "PathInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MINIMUM_WINDOW_WIDTH 300

#define MPLAYER_CFG_bMPlayerPathName           "bMPlayerPathName"
#define MPLAYER_CFG_strMPlayerPathName         "strMPlayerPathName"
#define MPLAYER_CFG_bShowToolbar               "bShowToolbar"
#define MPLAYER_CFG_bShowStatusBar             "bShowStatusBar"
#define MPLAYER_CFG_bShowProgressBar           "bShowProgressBar"
#define MPLAYER_CFG_bShowPlaylist              "bShowPlaylist"
#define MPLAYER_CFG_nSSDisableMode             "nSSDisableMode"
#define MPLAYER_CFG_nPresetZoom                "nPresetZoom"
#define MPLAYER_CFG_bAllowMultipleInstances    "bAllowMultipleInstances"
#define MPLAYER_CFG_nVideoOutputDriver         "nVideoOutputDriver"
#define MPLAYER_CFG_nAudioOutputDriver         "nAudioOutputDriver"
#define MPLAYER_CFG_bDoubleBuffering           "bDoubleBuffering"
#define MPLAYER_CFG_bAutoShuffle               "bAutoShuffle"
#define MPLAYER_CFG_bAutoloadSubtitles         "bAutoloadSubtitles"
#define MPLAYER_CFG_strMPlayerUserConfig       "strMPlayerUserConfig"
#define MPLAYER_CFG_nMPlayerPriority           "nMPlayerPriority"
#define MPLAYER_CFG_bDisableMPlayerMonitor     "bDisableMPlayerMonitor"
#define MPLAYER_CFG_bEnableLogging             "bEnableLogging"
#define MPLAYER_CFG_bBypassWinVersionCheck     "bBypassWinVersionCheck"
#define MPLAYER_CFG_nVideoBrightness           "nVideoBrightness"
#define MPLAYER_CFG_nVideoContrast             "nVideoContrast"
#define MPLAYER_CFG_nVideoHue                  "nVideoHue"
#define MPLAYER_CFG_nVideoSaturation           "nVideoSaturation"
#define MPLAYER_CFG_bStartupAlwaysOnTop        "bStartupAlwaysOnTop"
#define MPLAYER_CFG_bLaunchInFullscreen        "bLaunchInFullscreen"
#define MPLAYER_CFG_strSubtitleFont            "strSubtitleFont"
#define MPLAYER_CFG_nSubCP                     "nSubtitleCodePage"
#define MPLAYER_CFG_nVolume                    "nVolume"
#define MPLAYER_CFG_strF1CMD                   "strF1CMD"
#define MPLAYER_CFG_strF2CMD                   "strF2CMD"
#define MPLAYER_CFG_strF3CMD                   "strF3CMD"
#define MPLAYER_CFG_strF4CMD                   "strF4CMD"
#define MPLAYER_CFG_strF5CMD                   "strF5CMD"
#define MPLAYER_CFG_strF6CMD                   "strF6CMD"
#define MPLAYER_CFG_strF7CMD                   "strF7CMD"
#define MPLAYER_CFG_strF8CMD                   "strF8CMD"



// TIMER
#define TIMER_HALF_SECOND          1
#define TIMER_ONE_SECOND           2
#define TIMER_CACHEFILL            3
#define TIMER_FULLSCREENMOUSEHIDER 4

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_PLAY_PLAY, OnPlayPlay)
	ON_COMMAND(ID_PLAY_STOP, OnPlayStop)
	ON_COMMAND(ID_PLAY_PAUSE, OnPlayPause)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_FILE_CLOSE_FILE, OnFileCloseFile)
	ON_COMMAND(ID_FILE_CLIPPROPERTY, OnFileClipproperty)
	ON_COMMAND(ID_VIEW_ALWAYSONTOP, OnViewAlwaysontop)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALWAYSONTOP, OnUpdateViewAlwaysontop)
	ON_COMMAND(ID_VIEW_KEEPASPECTRATIO, OnViewKeepaspectratio)
	ON_UPDATE_COMMAND_UI(ID_VIEW_KEEPASPECTRATIO, OnUpdateViewKeepaspectratio)
	ON_COMMAND(ID_VIEW_PROGRESS_BAR, OnViewProgressBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROGRESS_BAR, OnUpdateViewProgressBar)
	ON_COMMAND(ID_VOLUME_MUTE, OnVolumeMute)
	ON_COMMAND(ID_OPTIONS_PREFERENCES, OnOptionsPreferences)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_COMMAND(ID_PLAY_REPEAT, OnPlayRepeat)
	ON_UPDATE_COMMAND_UI(ID_PLAY_REPEAT, OnUpdatePlayRepeat)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_PLAYLIST, OnViewPlaylist)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYLIST, OnUpdateViewPlaylist)
	ON_COMMAND(ID_VIEW_MYTOOLBAR, OnViewMytoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MYTOOLBAR, OnUpdateViewMytoolbar)
	ON_UPDATE_COMMAND_UI(ID_PLAY_PLAY, OnUpdatePlayPlay)
	ON_UPDATE_COMMAND_UI(ID_PLAY_PAUSE, OnUpdatePlayPause)
	ON_COMMAND(ID_PLAY_NEXT, OnPlayNext)
	ON_COMMAND(ID_PLAY_PREVIOUS, OnPlayPrevious)
	ON_COMMAND(ID_FILE_OPENURL, OnFileOpenurl)
	ON_COMMAND(ID_PLAY_GOTO, OnPlayGoto)
	ON_WM_COPYDATA()
	ON_COMMAND(ID_VIEW_STATUSBAR, OnViewStatusbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUSBAR, OnUpdateViewStatusbar)
	ON_WM_TIMER()
	ON_COMMAND(ID_HELP_HOMEPAGE, OnHelpHomepage)
	ON_COMMAND(ID_VIEW_LOG, OnViewLog)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOG, OnUpdateViewLog)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
  ON_COMMAND_RANGE(ID_VIEW_ZOOMHALF, ID_VIEW_ZOOMPRESET, OnZoomSet)
  ON_COMMAND_RANGE(ID_PLAY_FF10S, ID_PLAY_REW10M, OnPlayForwardRewind)
  ON_COMMAND_RANGE(ID_VOLUME_100, ID_VOLUME_25, OnVolumeSet)

  ON_COMMAND_RANGE(ID_PLAY_AFTERPLAYBACK_SHUTDOWN, ID_PLAY_AFTERPLAYBACK_DONOTHING, OnAfterplayback)
  ON_UPDATE_COMMAND_UI_RANGE(ID_PLAY_AFTERPLAYBACK_SHUTDOWN, ID_PLAY_AFTERPLAYBACK_DONOTHING, OnUpdateAfterplayback)

  ON_COMMAND(ID_F1CMD, OnF1CMD)
  ON_COMMAND(ID_F2CMD, OnF2CMD)
  ON_COMMAND(ID_F3CMD, OnF3CMD)
  ON_COMMAND(ID_F4CMD, OnF4CMD)
  ON_COMMAND(ID_F5CMD, OnF5CMD)
  ON_COMMAND(ID_F6CMD, OnF6CMD)
  ON_COMMAND(ID_F7CMD, OnF7CMD)
  ON_COMMAND(ID_F8CMD, OnF8CMD)

  ON_MESSAGE(UWM_MPLAYER_STARTING, OnMPlayerStarting)
  ON_MESSAGE(UWM_MPLAYER_STARTPLAYING, OnMPlayerStartPlaying)
	ON_MESSAGE(UWM_MPLAYER_FAILEDTOSTART, OnMPlayerFailedToStart)
	ON_MESSAGE(UWM_MPLAYER_AUTOSTOPPED, OnMPlayerAutoStopped)
  ON_MESSAGE(UWM_MPLAYER_STOPPED, OnMPlayerStopped)

  ON_MESSAGE(UWM_SLIDER_PROGRESS, OnSliderProgress)
  ON_MESSAGE(UWM_SLIDER_VOLUME, OnSliderVolume)
  ON_MESSAGE(UWM_PLAYLIST_PLAY, OnPlayListPlay)
  ON_MESSAGE(UWM_PLAYLIST_DLG_HIDE, OnPlaylistDlgHide)
  ON_MESSAGE(UWM_LOG_DLG_HIDE, OnLogDlgHide)
  ON_MESSAGE(UWM_STARTUP_OPENFILE, OnStartupOpenfile)
  ON_MESSAGE(UWM_VIEW_MPLAYER_PAUSE, OnViewMPlayerPause)
  ON_MESSAGE(UWM_VIEW_MPLAYER_FULLSCREEN, OnViewMPlayerFullScreen)
  ON_MESSAGE(UWM_MPLAYER_LOG, OnMPlayerLog)
  ON_WM_DROPFILES()
END_MESSAGE_MAP()

// status bar indicators
static UINT indicators[] =
{
	// ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_STATUS, // status
  // ID_INDICATOR_PERCENT, // percent progress
  ID_INDICATOR_ABPS, // audio bps
  ID_INDICATOR_TIME,   // current time
  // ID_INDICATOR_LENGTH, // clip length
	// ID_INDICATOR_CAPS,
	// ID_INDICATOR_NUM,
	// ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
  Init();
}

// Initialization
void CMainFrame::Init(void)
{
  char szAppPath[MAX_PATH] = "";

  // Get the Module pathname
  ::GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);

  // Extract directory
  m_strAppDirectory = szAppPath;
  m_strAppDirectory = m_strAppDirectory.Left(m_strAppDirectory.ReverseFind('\\'));

  // Initialization
  m_MPlayerGUIStatus.strSource = "";
  m_MPlayerGUIStatus.nPercent = -1;
  m_MPlayerGUIStatus.lTimePosOld = -1;
  m_MPlayerGUIStatus.fCacheFill = 0;
  m_MPlayerGUIStatus.nSeekToPercent = 0;
  m_MPlayerGUIStatus.nZoomMode = 1; // 1: original; 2: double; 3: half; 4: preset
  m_MPlayerGUIStatus.bTopMostWindow = FALSE;
  m_MPlayerGUIStatus.bKeepAspectRatio = TRUE;
  m_MPlayerGUIStatus.bRepeatMode = FALSE;
  m_MPlayerGUIStatus.bFullScreen = FALSE;
  m_MPlayerGUIStatus.bToolbarVisible = FALSE;
  m_MPlayerGUIStatus.bStatusBarVisible = FALSE;
  m_MPlayerGUIStatus.bProgressBarVisible = FALSE;
  m_MPlayerGUIStatus.bPlaylistVisible = FALSE;
  m_MPlayerGUIStatus.bBypassWinVersionCheck = FALSE;
  m_MPlayerGUIStatus.nSkipOneUpdateOfProgressBar = 0;

  // Initialization, actually these values will be set again in ReadIniSettings()
  m_MPlayerGUICfg.bMPlayerPathName = FALSE;
  m_MPlayerGUICfg.bShowToolbar = FALSE;
  m_MPlayerGUICfg.bShowStatusBar = FALSE;
  m_MPlayerGUICfg.bShowProgressBar = FALSE;
  m_MPlayerGUICfg.bShowPlaylist = FALSE;
  m_MPlayerGUICfg.nSSDisableMode = 0;
  m_MPlayerGUICfg.nPresetZoom = 100;
  m_MPlayerGUICfg.bAllowMultipleInstances = FALSE;
  m_MPlayerGUICfg.bAutoShuffle = FALSE;
  m_MPlayerGUICfg.bDisableMPlayerMonitor = FALSE;
  m_MPlayerGUICfg.bEnableLogging = FALSE;
  m_MPlayerGUICfg.nAfterplayback = 0;
  m_MPlayerGUICfg.bStartupAlwaysOnTop = FALSE;
  m_MPlayerGUICfg.bLaunchInFullscreen = FALSE;
  m_MPlayerGUICfg.nVolumeLoaded = 0;
  m_MPlayerGUICfg.strF1CMD = "";
  m_MPlayerGUICfg.strF2CMD = "";
  m_MPlayerGUICfg.strF3CMD = "";
  m_MPlayerGUICfg.strF4CMD = "";
  m_MPlayerGUICfg.strF5CMD = "";
  m_MPlayerGUICfg.strF6CMD = "";
  m_MPlayerGUICfg.strF7CMD = "";
  m_MPlayerGUICfg.strF8CMD = "";

  // Setup the default MPlayer binary pathname
  m_MPlayerGUICfg.strDefaultMPlayerPathName.Format("%s\\mplayer\\mplayer.exe", _T(m_strAppDirectory));

  // Read MPlayerGUI.ini
  ReadIniSettings();

  // set MPlayer binary pathname according to m_MPlayerGUICfg.bMPlayerPathName
  SetMPlayerPathName();

  // Get OS major version number
  // Check if we are running Windows 2000 (or above)
  if (m_MPlayerGUIStatus.bBypassWinVersionCheck)
  {
    m_MPlayer.SetOSMajorVersion(5); // Assume we are running on Windows 2000 (or above)
    TRACE("OS Version Check bypassed.\n");
  }
  else
  {
    m_MPlayer.SetOSMajorVersion(OS_GetMajorVersion());
  }

  // Restore first, i will call disable on play and restore on stop/autostop
  m_SSDisabler.Restore();

  // Set pointer to playlist dialog (modaless) to null
  m_pPlaylistDlg = NULL;
  m_pLogDlg = NULL;
}


CMainFrame::~CMainFrame()
{
  // KillTimer(TIMER_HALF_SECOND);
  // KillTimer(TIMER_ONE_SECOND);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

  // the original toolbar has been dumpped
  /*
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  */

  /*
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
  */

  if (!m_wndStatusBar.Create(this, IDD_PLAYER_STATUSBAR, CBRS_ALIGN_BOTTOM, IDD_PLAYER_STATUSBAR))
  {
    TRACE0("Failed to create xxx dialogbar\n");
    return -1;
  }

  if (!m_wndMyToolBar.Create(this))
  {
    return -1;
  }

  if (!m_wndProgressDlgBar.Create(this, IDD_PROGRESS_DLGBAR, CBRS_ALIGN_BOTTOM, IDD_PROGRESS_DLGBAR))
  {
    TRACE0("Failed to create progress dialogbar\n");
    return -1;
  }

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	// m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
	//	CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	// m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
	// 	CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	// m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	// EnableDocking(CBRS_ALIGN_ANY);
	// DockControlBar(&m_wndToolBar);

  // Create the playlist dialog
  m_pPlaylistDlg = new CPlaylistDlg;
  m_pPlaylistDlg->Create(IDD_PLAYLIST, this); // GetDesktopWindow());
  m_pPlaylistDlg->ShowWindow(SW_HIDE);

  // Create the log dialog
  m_pLogDlg = new CLogDlg;
  m_pLogDlg->Create(IDD_LOG, this);
  m_pLogDlg->ShowWindow(SW_HIDE);

  // Set status pane stretch and 75 pixel wide minial
  // m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_STATUS, SBPS_STRETCH, 75);
  // Reset Statusbar
  m_wndStatusBar.Reset();

  // Show/Hide Toolbar
  ShowControlBar(&m_wndMyToolBar, m_MPlayerGUICfg.bShowToolbar, TRUE);
  // Show/Hide status bar
  ShowControlBar(&m_wndStatusBar, m_MPlayerGUICfg.bShowStatusBar, TRUE);
  // Show/Hide progress dlgbar
  ShowControlBar(&m_wndProgressDlgBar, m_MPlayerGUICfg.bShowProgressBar, TRUE);

  if (m_MPlayerGUICfg.bStartupAlwaysOnTop)
  {
    OnViewAlwaysontop();
  }

  // Show/Hide playlist dlg
  if (m_MPlayerGUICfg.bShowPlaylist)
  {
    m_pPlaylistDlg->ShowWindow(SW_SHOW);
  }

  // Create the m_MPlayer
  if (!m_MPlayer.Create(_T(""), WS_CHILD, CRect(0, 0, 0, 0), this))
	{
	  return -1;
	}

  // Load Volume from MPlayerGUI.ini
  CAppSettings MyAppSettings;
  m_MPlayerGUICfg.nVolumeLoaded = MyAppSettings.ReadInteger(MPLAYER_CFG_nVolume, 100);
  m_MPlayer.SetVolume(m_MPlayerGUICfg.nVolumeLoaded);
  m_wndMyToolBar.SetSliderVolume(m_MPlayerGUICfg.nVolumeLoaded);

  DragAcceptFiles(TRUE); // Accept user dropped file

  // Move the MainFrame Window to the center of desktop
  CenterWindow();

  // MyUpdateStatusBar(1, ""); // Clear the Kbps display
  // UpdateStatusbarTimer(0, 0, 1); // Reset the timer display

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

  // set the window's initial size to 200x20 (actually it will be limited by
	//   OnGetMinMaxInfo())
  cs.cx = 200;
  cs.cy = 20;

  // TODO: Find a way to disable/enable Tilte
  // No Title
  cs.style &= ~FWS_ADDTOTITLE;

	// return CFrameWnd::PreCreateWindow(cs);
  if (!CFrameWnd::PreCreateWindow(cs))
    return FALSE;

  // This is the Class Name to prevent multi-instance
  cs.lpszClass = MPLAYERGUI_WND_CLASS_NAME;

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// Call from CView, i must wait until the VideoPanel object in CView is created
void CMainFrame::SetMPlayerVideoWindow(void)
{
  CMPlayerGUIView *pView;
  pView = (CMPlayerGUIView*)GetActiveView();

  m_hVideoPanel = pView->GetMPlayerVideoWindow();
  m_MPlayer.SetVideoPanelHandle(m_hVideoPanel);

  // Pre-arrange panels
  pView->PreparePanels(FALSE);
}

// File->Open handler
void CMainFrame::OnFileOpen() 
{
  const char fileDialogFilter[] = "all files (*.*)|*.*||";
  const char fileDialogExt[] = "rm";
  CString strFilename, strPathName;

  // Popup the File Open dialog box
  CFileDialog fileDialog(TRUE,
    fileDialogExt,
    NULL,
    OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_READONLY,
    fileDialogFilter);

  // Call DoFileOpen() if user picked a file
  if (fileDialog.DoModal() == IDOK)
  {
    strFilename = fileDialog.GetPathName();
    DoFileOpen(_T(strFilename));
  }
}

// Play->Play handler
void CMainFrame::OnPlayPlay() 
{
  int nStatus = m_MPlayer.GetStatus();

  // Return if .strSource is empty (not set yet)
  if (m_MPlayerGUIStatus.strSource == "")
  {
    return;
  }

  // Action to do if the current status is STOP
  if (nStatus == MPLAYER_STOPPED)
  {
    // Since this is the situation that STOP -> PLAY, by PLAY button
    // Call DoPlayPlay()
    DoPlayPlay();
  }
  else if (nStatus == MPLAYER_PAUSED) // Action to do if the current status is PAUSE
  {
    OnPlayPause(); // Toggle PLAY/PAUSE mode
  }	
}

// ?
void CMainFrame::OnUpdatePlayPlay(CCmdUI* pCmdUI) 
{
  int nStatus = m_MPlayer.GetStatus();

  if ((nStatus == MPLAYER_PLAYING) || (nStatus == MPLAYER_PAUSED))
  {
    pCmdUI->SetCheck(TRUE);
  }
  else
  {
    pCmdUI->SetCheck(FALSE);
  }
}

// Actually do the play action
void CMainFrame::DoPlayPlay(void)
{
  int nStatus;

  nStatus = m_MPlayer.GetStatus();

  // Return if .strSource is empty
  if (m_MPlayerGUIStatus.strSource == "")
  {
    return;
  }

  // Check if the MPlayer engine is available
  if (!m_MPlayer.CheckEngine())
  {
    m_wndStatusBar.SetMessage(_T("Engine not found!"));
    return;
  }

  if (nStatus == MPLAYER_STOPPED)
  {
    // Ask MPlayer to start, and let it to get startup information
    m_MPlayer.Play();
  }
}

// Play->Stop handler
void CMainFrame::OnPlayStop() 
{
  int nStatus = m_MPlayer.GetStatus();

  // Do action when status is PLAYING or PAUSE or STARTING
  if ((nStatus == MPLAYER_PLAYING) || (nStatus == MPLAYER_PAUSED) || (nStatus == MPLAYER_STARTING))
  {
    // Turn off full screen
    if (m_MPlayerGUIStatus.bFullScreen)
    {
      OnViewFullscreen();
    }

    DoPlayStop();
  }	
}

void CMainFrame::DoPlayStop(void)
{
  int nStatus = m_MPlayer.GetStatus();

  // Do action when status is PLAYING or PAUSE or STARTING
  if ((nStatus == MPLAYER_PLAYING) || (nStatus == MPLAYER_PAUSED) || (nStatus == MPLAYER_STARTING))
  {
    // Ask MPlayer to stop
    m_MPlayer.Stop();

    // Clean up status variables
    PlayerCleanUp();

    // Restore screen saver status
    m_SSDisabler.Restore();
  }
}


// Clean up status variables after stop
void CMainFrame::PlayerCleanUp(void)
{
  // Stop Timers
  KillTimer(TIMER_HALF_SECOND);
  KillTimer(TIMER_ONE_SECOND);
  KillTimer(TIMER_CACHEFILL);
  // KillTimer(TIMER_FULLSCREENMOUSEHIDER);

  // Turn off full screen
  /*
  if (m_MPlayerGUIStatus.bFullScreen)
  {
    OnViewFullscreen();
  }
  */

  // Turn back to logo panel
  FitWindow(FALSE, 320, 240);

  // Reset status
  m_MPlayerGUIStatus.fCacheFill = 0;
  m_MPlayerGUIStatus.nSeekToPercent = 0;
  // m_MPlayerGUIStatus.nZoomMode = 1; // dont reset zoom mode
  m_MPlayerGUIStatus.nPercent = -1;
  m_MPlayerGUIStatus.lTimePosOld = -1;
  m_MPlayerGUIStatus.nSkipOneUpdateOfProgressBar = 0;

  m_wndStatusBar.Reset();

  // Disable progress bar
  m_wndProgressDlgBar.EnableProgressBar(FALSE);

  // Status bar: Stop
  m_wndStatusBar.SetMessage(_T("Stopped"));
}

// After starting play back, get MPlayer reported clip duration
void CMainFrame::GetTimeLength(void)
{
  int nStatus = m_MPlayer.GetStatus();
  long lDuration;

  if ((nStatus == MPLAYER_PLAYING) || (nStatus == MPLAYER_PAUSED))
  {
    lDuration = m_MPlayer.GetClipInfo_Length();

    // -1 means MPlayer don't respond me :(
    if (lDuration != -1)
    {
      m_wndStatusBar.SetDuration(lDuration);
    }
  }
}

// Play->Pause handler
void CMainFrame::OnPlayPause() 
{
  int nStatus = m_MPlayer.GetStatus();

  if (nStatus == MPLAYER_PLAYING)
  {
    m_MPlayer.Pause(TRUE);

    m_wndStatusBar.StopFlipInfo();
    // Status bar: Paused
    m_wndStatusBar.SetMessage(_T("Paused"));
  }
  else if (nStatus == MPLAYER_PAUSED)
  {
    m_MPlayer.Pause(FALSE);

    // Status bar: Playing... or Playing... (list)
    m_wndStatusBar.SetMessage(_T("Playing"));
    m_wndStatusBar.StartFlipInfo();
  }	
}

void CMainFrame::OnUpdatePlayPause(CCmdUI* pCmdUI) 
{
  int nStatus = m_MPlayer.GetStatus();

  if (nStatus == MPLAYER_PAUSED)
  {
    pCmdUI->SetCheck(TRUE);
  }
  else
  {
    pCmdUI->SetCheck(FALSE);
  }
}

// ?
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
  if (m_MPlayerGUIStatus.bFullScreen)
  {
    lpMMI->ptMaxSize.y = m_MPlayerGUIStatus.rFullScreenWindowRect.Height();
    lpMMI->ptMaxSize.x = m_MPlayerGUIStatus.rFullScreenWindowRect.Width();
    lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
    lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
  }
  else
  {
    lpMMI->ptMinTrackSize.x = MINIMUM_WINDOW_WIDTH;
    lpMMI->ptMinTrackSize.y = GetFrameMinusViewHeight();
  }

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

// File->Close handler
void CMainFrame::OnFileCloseFile() 
{
  DoPlayStop();
  m_MPlayerGUIStatus.strSource = "";
  ChangeTitle("");

  // Set Labels in View
  CMPlayerGUIView *pView;
  pView = (CMPlayerGUIView*)GetActiveView();
  pView->SetLabelInfo("", "");
}

// Change Frame-Window size according to Clip video size
void CMainFrame::FitWindow(BOOL bHaveVideo, int nVideoWidth, int nVideoHeight)
{
  CRect rFrame, rView;

  CMPlayerGUIView *pView;
  pView = (CMPlayerGUIView*)GetActiveView();
  DWORD dwViewExStyle = pView->GetExStyle();

  if ((m_MPlayerGUIStatus.bFullScreen) || (IsWindowMax()))
  {
    // Do not resize window anymore, but let view resize its video panel
    // CView, show/hide video panels
    pView->PreparePanels(bHaveVideo);

    // Tell view the video width/height for keep aspect ratio
    pView->SetVideoWidth(nVideoWidth);
    pView->SetVideoHeight(nVideoHeight);

    // Tell view to resize once to keep aspect ratio (if)
    pView->PostMessage(WM_SIZE);
    return;
  }

  if (bHaveVideo)
  {
    // Turn Window to normal status
    RestoreFromMaxMin(); // actually this is needless

    // Get Frame-Window rectangle
    GetWindowRect(&rFrame);

    CPoint pointCenter;
    pointCenter = rFrame.CenterPoint();

    int nVideoWidthTemp;

    nVideoWidthTemp = nVideoWidth;

    if (nVideoWidthTemp < MINIMUM_WINDOW_WIDTH)
      nVideoWidthTemp = MINIMUM_WINDOW_WIDTH;

    int nWidth, nHeight;
    nWidth = nVideoWidthTemp + GetFrameMinusViewWidth();
    if (dwViewExStyle & WS_EX_CLIENTEDGE)
    {
      nWidth += 2 * GetSystemMetrics(SM_CXEDGE);
    }

    nHeight = nVideoHeight + GetFrameMinusViewHeight();
    if (dwViewExStyle & WS_EX_CLIENTEDGE)
    {
      nHeight += 2 * GetSystemMetrics(SM_CYEDGE);
    }

    rFrame.left = pointCenter.x - nWidth / 2;
    rFrame.top = pointCenter.y - nHeight / 2;

    // if (rFrame.left < 0)
    //   rFrame.left = 0;

    // Pull back the Window a little bit
    if (rFrame.top < 0)
      rFrame.top = 0;

    rFrame.right = rFrame.left + nWidth;
    rFrame.bottom = rFrame.top + nHeight;

    // Set to new rectangle
    MoveWindow(rFrame);
  }

  // CView, show/hide video panels
  pView->PreparePanels(bHaveVideo);

  // Tell view the video width/height for keep aspect ratio
  pView->SetVideoWidth(nVideoWidth);
  pView->SetVideoHeight(nVideoHeight);

  // Tell view to do 'one-time' force video panel resize
  // pView->ForceVideoSize();
  // Tell view to resize once to keep aspect ratio (if)
  pView->PostMessage(WM_SIZE);
}

// File->Property handler
void CMainFrame::OnFileClipproperty() 
{
/*
  CClipPropertyDlg PropertyDlg;

  PropertyDlg.m_strClipInfo_Title = m_MPlayer.GetClipInfo_Title();
  PropertyDlg.m_strClipInfo_Artist = m_MPlayer.GetClipInfo_Artist();
  PropertyDlg.m_strClipInfo_Album = m_MPlayer.GetClipInfo_Album();
  PropertyDlg.m_strClipInfo_Genre = m_MPlayer.GetClipInfo_Genre();
  PropertyDlg.m_strClipInfo_Length.Format("%ld", m_MPlayer.GetClipInfo_Length());

  PropertyDlg.m_strAudioInfo_Codec = m_MPlayer.GetAudioInfo_Codec();
  PropertyDlg.m_strAudioInfo_Format = m_MPlayer.GetAudioInfo_Format();
  PropertyDlg.m_strAudioInfo_Bitrate.Format("%ld", m_MPlayer.GetAudioInfo_Bitrate());
  PropertyDlg.m_strAudioInfo_NCH.Format("%d", m_MPlayer.GetAudioInfo_NCH());
  PropertyDlg.m_strAudioInfo_Rate.Format("%ld", m_MPlayer.GetAudioInfo_Rate());

  PropertyDlg.m_strVideoInfo_Codec = m_MPlayer.GetVideoInfo_Codec();
  PropertyDlg.m_strVideoInfo_Bitrate.Format("%ld", m_MPlayer.GetVideoInfo_Bitrate());
  PropertyDlg.m_strVideoInfo_FPS.Format("%.1f", m_MPlayer.GetVideoInfo_FPS());
  PropertyDlg.m_strVideoInfo_Width.Format("%d", m_MPlayer.GetVideoInfo_Width());
  PropertyDlg.m_strVideoInfo_Height.Format("%d", m_MPlayer.GetVideoInfo_Height());

  if (PropertyDlg.DoModal() == IDOK)
  {
  }
*/

  CPPageFile PageFile;
  CPPageContent PageContent;

  CPropertySheet MySheet;
  MySheet.SetTitle("Properties");

  // ------------------- File Page -------------------
  // get Length (start)
  int nHoursT, nMinutesT, nSecondsT;
  long lTotalTime;

  lTotalTime = m_MPlayer.GetClipInfo_Length();

  CTimeSplitter MyTimeSplitter;
  MyTimeSplitter.SetTime(lTotalTime);
  nHoursT = MyTimeSplitter.GetHours();
  nMinutesT = MyTimeSplitter.GetMinutes();
  nSecondsT = MyTimeSplitter.GetSeconds();

  if (nHoursT > 99)
  {
    nHoursT = 99;
  }

  if (nHoursT == 0)
  {
    // short mode ("05:22")
    PageFile.m_strLength.Format("%02d:%02d", nMinutesT, nSecondsT);
  }
  else
  {
    // long mode ("02:04:21")
    PageFile.m_strLength.Format("%02d:%02d:%02d", nHoursT, nMinutesT, nSecondsT);
  }
  // get Length (done)

  // get Bitrate (start)
  // this Bitrate is the total bitrate = Audio + Video
  long lBitRate;

  lBitRate = m_MPlayer.GetAudioInfo_Bitrate() + m_MPlayer.GetVideoInfo_Bitrate();

  lBitRate = lBitRate / 1000;

  PageFile.m_strBitRate.Format("%ld Kbps", lBitRate);
  // get Bitrate (done)

  BOOL bHaveVideo = m_MPlayer.HaveVideo();

  // get MediaType (start)
  if (bHaveVideo == TRUE)
  {
    PageFile.m_strMediaType = _T("Video");
  }
  else
  {
    PageFile.m_strMediaType = _T("Audio");
  }
  // get MediaType (done)

  // get Video size
  if (bHaveVideo == TRUE)
  {
    PageFile.m_strVideoSize.Format("%d x %d",
      m_MPlayer.GetVideoInfo_Width(),
      m_MPlayer.GetVideoInfo_Height());
  }
  else
  {
    PageFile.m_strVideoSize = _T("-");
  }

  // get Aspect Ratio
  // just "-" for now
  PageFile.m_strAspectRatio = _T("-");

  // get Audio Codec + Kbps + Hz + Mono/Stereo
  PageFile.m_strAudioCodec.Format("%s\r\n%ld Kbps, %ld Hz, %d Channel(s)",
    m_MPlayer.GetAudioInfo_Codec(),
    m_MPlayer.GetAudioInfo_Bitrate() / 1000,
    m_MPlayer.GetAudioInfo_Rate(),
    m_MPlayer.GetAudioInfo_NCH());

  // get Video Codec + Kbps + FPS
  if (bHaveVideo == TRUE)
  {
    PageFile.m_strVideoCodec.Format("%s\r\n%ld Kbps, %.1f FPS",
      m_MPlayer.GetVideoInfo_Codec(),
      m_MPlayer.GetVideoInfo_Bitrate() / 1000,
      m_MPlayer.GetVideoInfo_FPS());
  }
  else
  {
    PageFile.m_strVideoCodec = _T("-");
  }

  // get Location
  PageFile.m_strLocation = m_MPlayerGUIStatus.strSource;

  // ------------------- Content Page -------------------
  // get Title
  PageContent.m_strTitle = m_MPlayer.GetClipInfo_Title();

  // get Artist
  PageContent.m_strArtist = m_MPlayer.GetClipInfo_Artist();

  // get Album
  PageContent.m_strAlbum = m_MPlayer.GetClipInfo_Album();

  // get Composer // TODO: Get real composer here
  PageContent.m_strComposer = _T("-");

  // get Genre
  PageContent.m_strGenre = m_MPlayer.GetClipInfo_Genre();

  // get Copyright
  PageContent.m_strCopyright = m_MPlayer.GetClipInfo_Copyright();

  // get Rating
  PageContent.m_strRating = m_MPlayer.GetClipInfo_Rating();

  // get Comments // TODO: Get real comments here
  PageContent.m_strComments = _T("-");


  // Add pages to sheet
  MySheet.AddPage(&PageFile);
  MySheet.AddPage(&PageContent);

  // Hide 'Apply' button...
  MySheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

  if (MySheet.DoModal() == IDOK)
  {
  }
}

// handle the UWM_SLIDER_PROGRESS message
CMainFrame::OnSliderProgress(WPARAM wParam, LPARAM lParam)
{
  int nStatus = m_MPlayer.GetStatus();
  long lDuration;

  if (nStatus == MPLAYER_PLAYING)
  {
    // Seek if new position is required
    if (m_MPlayerGUIStatus.nSeekToPercent != (int)wParam)
    {
      m_MPlayerGUIStatus.nSeekToPercent = (int)wParam;
      lDuration = m_MPlayer.GetClipInfo_Length();

      DWORD dwSeekTime;
      // Calculate where to seek
      dwSeekTime = (DWORD)lDuration *
        m_MPlayerGUIStatus.nSeekToPercent / 100;
      m_MPlayer.SeekTime(dwSeekTime);

      // Skip once in UpdateProgress()  avoid jummpy
      m_MPlayerGUIStatus.nSkipOneUpdateOfProgressBar = 2;
    }
  }

  return 1;
}

// handle the UWM_SLIDER_VOLUME message
CMainFrame::OnSliderVolume(WPARAM wParam, LPARAM lParam)
{
  int nStatus = m_MPlayer.GetStatus();
  int nVolume = m_MPlayer.GetVolume();

  if (nVolume != (int)wParam)
  {
    nVolume = (int)wParam;

    // if (nStatus == MPLAYER_PLAYING)
    {
      m_MPlayer.SetVolume(nVolume);
    }
  }

  return 1;
}

// View->Always On Top handler, toggle always on top
void CMainFrame::OnViewAlwaysontop() 
{
  m_MPlayerGUIStatus.bTopMostWindow = !m_MPlayerGUIStatus.bTopMostWindow;

  DoAlwaysOnTop(m_MPlayerGUIStatus.bTopMostWindow);
}

void CMainFrame::DoAlwaysOnTop(BOOL bTop)
{
  if (bTop)
  {
    SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }
  else
  {
    SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }
}

void CMainFrame::OnUpdateViewAlwaysontop(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_MPlayerGUIStatus.bTopMostWindow);
}

// View->Keep Aspect Ratio handler
void CMainFrame::OnViewKeepaspectratio() 
{
  CMPlayerGUIView *pView;
  pView = (CMPlayerGUIView*)GetActiveView();

  m_MPlayerGUIStatus.bKeepAspectRatio = !m_MPlayerGUIStatus.bKeepAspectRatio;

  // Inform the View
  pView->SetKeepAspectRatio(m_MPlayerGUIStatus.bKeepAspectRatio);

  // Post a WM_SIZE to view, CView.OnSize() will be called :)
  pView->PostMessage(WM_SIZE);
}

void CMainFrame::OnUpdateViewKeepaspectratio(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_MPlayerGUIStatus.bKeepAspectRatio);
}

// View->Progress Bar handler
void CMainFrame::OnViewProgressBar() 
{
  ShowControlBar(&m_wndProgressDlgBar, !m_wndProgressDlgBar.IsWindowVisible(), TRUE);
}

void CMainFrame::OnUpdateViewProgressBar(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_wndProgressDlgBar.IsWindowVisible());	
}

// View->Zoom Half, Zoom Original, Zoom Double handler
void CMainFrame::OnZoomSet(UINT nID)
{
  int nVideoWidth, nVideoHeight;

  nVideoWidth = m_MPlayer.GetVideoInfo_Width();
  nVideoHeight = m_MPlayer.GetVideoInfo_Height();

  switch (nID)
  {
  case ID_VIEW_ZOOM1X:
    // nVideoWidth = nVideoWidth;
    // nVideoHeight = nVideoHeight;
    m_MPlayerGUIStatus.nZoomMode = 1;
    break;
  case ID_VIEW_ZOOMHALF:
    nVideoWidth = nVideoWidth / 2;
    nVideoHeight = nVideoHeight / 2;
    m_MPlayerGUIStatus.nZoomMode = 3;
    break;
  case ID_VIEW_ZOOM2X:
    nVideoWidth = nVideoWidth * 2;
    nVideoHeight = nVideoHeight * 2;
    m_MPlayerGUIStatus.nZoomMode = 2;
    break;
  case ID_VIEW_ZOOMPRESET:
    nVideoWidth = nVideoWidth * m_MPlayerGUICfg.nPresetZoom / 100;
    nVideoHeight = nVideoHeight * m_MPlayerGUICfg.nPresetZoom / 100;
    m_MPlayerGUIStatus.nZoomMode = 4;
    break;
  default:
    // nVideoWidth = nVideoWidth;
    // nVideoHeight = nVideoHeight;
    m_MPlayerGUIStatus.nZoomMode = 1;
    break;
  }
  
  BOOL bHaveVideo = m_MPlayer.HaveVideo();

  if (bHaveVideo == TRUE)
  {
    FitWindow(TRUE, nVideoWidth, nVideoHeight);
  }
}

// Set the View size regarding to Video Size
void CMainFrame::PresetVideoSize(void)
{
  switch(m_MPlayerGUIStatus.nZoomMode)
  {
  case 1:
    OnZoomSet(ID_VIEW_ZOOM1X);
    break;
  case 2:
    OnZoomSet(ID_VIEW_ZOOM2X);
    break;
  case 3:
    OnZoomSet(ID_VIEW_ZOOMHALF);
    break;
  case 4:
    OnZoomSet(ID_VIEW_ZOOMPRESET);
    break;
  default:
    OnZoomSet(ID_VIEW_ZOOM1X);
    break;
  }
}

// Play->FF10S, REW10S, FF1M, REW1M, FF10M, REW10M handler
void CMainFrame::OnPlayForwardRewind(UINT nID)
{
  int nTime;

  switch (nID)
  {
  case ID_PLAY_FF10S:
    nTime = 10;
    break;
  case ID_PLAY_REW10S:
    nTime = -10;
    break;
  case ID_PLAY_FF1M:
    nTime = 60;
    break;
  case ID_PLAY_REW1M:
    nTime = -60;
    break;
  case ID_PLAY_FF10M:
    nTime = 600;
    break;
  case ID_PLAY_REW10M:
    nTime = -600;
    break;
  default:
    nTime = 0;
    break;
  }

  int nStatus = m_MPlayer.GetStatus();

  if (nStatus == MPLAYER_PLAYING)
  {
    m_MPlayer.SeekRelativeTime(nTime);

    // Avoid the jummpy progress bar
    m_MPlayerGUIStatus.nSkipOneUpdateOfProgressBar = 2;
  }
}

// Play->Volume->100%, 75%, 50%, 25% handler
void CMainFrame::OnVolumeSet(UINT nID)
{
  int nVolume;

  switch (nID)
  {
  case ID_VOLUME_100:
    nVolume = 100;
    break;
  case ID_VOLUME_75:
    nVolume = 75;
    break;
  case ID_VOLUME_50:
    nVolume = 50;
    break;
  case ID_VOLUME_25:
    nVolume = 25;
    break;
  default:
    nVolume = 0;
    break;
  }

  // Whatever is playing or not, set the value
  m_wndMyToolBar.SetSliderVolume(nVolume);

  int nStatus = m_MPlayer.GetStatus();

  // TODO: bug, if the Player is paused, no volume is set
  // if (nStatus == MPLAYER_PLAYING)
  {
    m_MPlayer.SetVolume(nVolume);
  }
}

// Play->Value->Mute handler
void CMainFrame::OnVolumeMute() 
{
  int nStatus;

  nStatus = m_MPlayer.GetStatus();

  if (nStatus == MPLAYER_PLAYING)
  {
    m_MPlayer.Mute();	
  }	
}

// Options->Preferences handler
void CMainFrame::OnOptionsPreferences() 
{
  CPPagePath PagePath;
	CPPageOutput PageOutput;
	CPPagePlayer PagePlayer;
  CPPageSubtitles PageSubtitles;
	CPPageAdvanced PageAdvanced;
  CPPageVideo PageVideo;
  CPPageAssociation PageAssociation;
  CPPageCommands PageCommands;

  CPropertySheet MySheet;
  MySheet.SetTitle("Preferences");

  if (m_MPlayerGUICfg.bMPlayerPathName == FALSE)
  {
    PagePath.m_nUseDefault = 0;
  }
  else
  {
    PagePath.m_nUseDefault = 1;
  }

  PagePath.m_strMPlayerPathName = m_MPlayerGUICfg.strMPlayerPathName;
  PagePath.m_strAppDirectory = m_strAppDirectory; // For generate relative pathname

  PagePlayer.m_bShowToolbar = m_MPlayerGUICfg.bShowToolbar;
  PagePlayer.m_bShowStatusBar = m_MPlayerGUICfg.bShowStatusBar;
  PagePlayer.m_bShowProgressBar = m_MPlayerGUICfg.bShowProgressBar;
  PagePlayer.m_bShowPlaylist = m_MPlayerGUICfg.bShowPlaylist;
  PagePlayer.m_nSSDisableMode = m_MPlayerGUICfg.nSSDisableMode;
  PagePlayer.m_nPresetZoom = m_MPlayerGUICfg.nPresetZoom;
  PagePlayer.m_bAllowMultipleInstances = m_MPlayerGUICfg.bAllowMultipleInstances;
  PagePlayer.m_bAutoShuffle = m_MPlayerGUICfg.bAutoShuffle;
  PagePlayer.m_bStartupAlwaysOnTop = m_MPlayerGUICfg.bStartupAlwaysOnTop;
  PagePlayer.m_bLaunchInFullscreen = m_MPlayerGUICfg.bLaunchInFullscreen;
  PageOutput.m_nVideoOutputDriver = m_MPlayer.GetVideoOutputDriver();
  PageOutput.m_nAudioOutputDriver = m_MPlayer.GetAudioOutputDriver();
  PageSubtitles.m_bAutoloadSubtitles = m_MPlayer.GetAutoloadSubtitles();
  PageSubtitles.m_nSubCP = m_MPlayer.GetSubCP();
  m_MPlayer.GetSubtitleFont(PageSubtitles.m_strSubtitleFont);
  m_MPlayer.GetMPlayerUserConfig(PageAdvanced.m_strMPlayerUserConfig);
  PageAdvanced.m_nMPlayerPriority = m_MPlayer.GetMPlayerPriority();
  PageAdvanced.m_bDisableMPlayerMonitor = m_MPlayerGUICfg.bDisableMPlayerMonitor;
  PageAdvanced.m_bEnableLogging = m_MPlayerGUICfg.bEnableLogging;

  PageVideo.SetVideoBrightness(m_MPlayer.GetVideoBrightness());
  PageVideo.SetVideoContrast(m_MPlayer.GetVideoContrast());
  PageVideo.SetVideoHue(m_MPlayer.GetVideoHue());
  PageVideo.SetVideoSaturation(m_MPlayer.GetVideoSaturation());
  PageVideo.m_bDoubleBuffering = m_MPlayer.GetDoubleBuffering();

  PageCommands.m_strF1CMD = m_MPlayerGUICfg.strF1CMD;
  PageCommands.m_strF2CMD = m_MPlayerGUICfg.strF2CMD;
  PageCommands.m_strF3CMD = m_MPlayerGUICfg.strF3CMD;
  PageCommands.m_strF4CMD = m_MPlayerGUICfg.strF4CMD;
  PageCommands.m_strF5CMD = m_MPlayerGUICfg.strF5CMD;
  PageCommands.m_strF6CMD = m_MPlayerGUICfg.strF6CMD;
  PageCommands.m_strF7CMD = m_MPlayerGUICfg.strF7CMD;
  PageCommands.m_strF8CMD = m_MPlayerGUICfg.strF8CMD;

	MySheet.AddPage(&PagePath);
	MySheet.AddPage(&PageOutput);
  MySheet.AddPage(&PageVideo);
	MySheet.AddPage(&PagePlayer);
  MySheet.AddPage(&PageSubtitles);
  MySheet.AddPage(&PageAssociation);
  MySheet.AddPage(&PageCommands);
	MySheet.AddPage(&PageAdvanced);

  // Hide 'Apply' button
  MySheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

  if (MySheet.DoModal() == IDOK)
  {
    if (PagePath.m_nUseDefault == 0)
    {
      m_MPlayerGUICfg.bMPlayerPathName = FALSE;
    }
    else
    {
      m_MPlayerGUICfg.bMPlayerPathName = TRUE;
    }

    m_MPlayerGUICfg.strMPlayerPathName = PagePath.m_strMPlayerPathName;
    m_MPlayerGUICfg.bShowToolbar = PagePlayer.m_bShowToolbar;
    m_MPlayerGUICfg.bShowStatusBar = PagePlayer.m_bShowStatusBar;
    m_MPlayerGUICfg.bShowProgressBar = PagePlayer.m_bShowProgressBar;
    m_MPlayerGUICfg.bShowPlaylist = PagePlayer.m_bShowPlaylist;
    m_MPlayerGUICfg.nSSDisableMode = PagePlayer.m_nSSDisableMode;
    m_MPlayerGUICfg.nPresetZoom = PagePlayer.m_nPresetZoom;
    m_MPlayerGUICfg.bAllowMultipleInstances = PagePlayer.m_bAllowMultipleInstances;
    m_MPlayerGUICfg.bAutoShuffle = PagePlayer.m_bAutoShuffle;
    m_MPlayerGUICfg.bStartupAlwaysOnTop = PagePlayer.m_bStartupAlwaysOnTop;
    m_MPlayerGUICfg.bLaunchInFullscreen = PagePlayer.m_bLaunchInFullscreen;
    m_MPlayer.SetVideoOutputDriver(PageOutput.m_nVideoOutputDriver);
    m_MPlayer.SetAudioOutputDriver(PageOutput.m_nAudioOutputDriver);
    m_MPlayer.SetAutoloadSubtitles(PageSubtitles.m_bAutoloadSubtitles);
    m_MPlayer.SetSubCP(PageSubtitles.m_nSubCP);
    m_MPlayer.SetSubtitleFont(PageSubtitles.m_strSubtitleFont);
    m_MPlayer.SetMPlayerUserConfig(PageAdvanced.m_strMPlayerUserConfig);
    m_MPlayer.SetMPlayerPriority(PageAdvanced.m_nMPlayerPriority);
    m_MPlayerGUICfg.bDisableMPlayerMonitor = PageAdvanced.m_bDisableMPlayerMonitor;
    m_MPlayer.SetDisableMPlayerMonitor(m_MPlayerGUICfg.bDisableMPlayerMonitor);
    m_MPlayerGUICfg.bEnableLogging = PageAdvanced.m_bEnableLogging;
    m_MPlayer.SetEnableLogging(m_MPlayerGUICfg.bEnableLogging);

    // Video Settings (directly pass to CMPlayer)
    m_MPlayer.SetVideoBrightness(PageVideo.GetVideoBrightness());
    m_MPlayer.SetVideoContrast(PageVideo.GetVideoContrast());
    m_MPlayer.SetVideoHue(PageVideo.GetVideoHue());
    m_MPlayer.SetVideoSaturation(PageVideo.GetVideoSaturation());
    m_MPlayer.SetDoubleBuffering(PageVideo.m_bDoubleBuffering);

    m_MPlayerGUICfg.strF1CMD = PageCommands.m_strF1CMD;
    m_MPlayerGUICfg.strF2CMD = PageCommands.m_strF2CMD;
    m_MPlayerGUICfg.strF3CMD = PageCommands.m_strF3CMD;
    m_MPlayerGUICfg.strF4CMD = PageCommands.m_strF4CMD;
    m_MPlayerGUICfg.strF5CMD = PageCommands.m_strF5CMD;
    m_MPlayerGUICfg.strF6CMD = PageCommands.m_strF6CMD;
    m_MPlayerGUICfg.strF7CMD = PageCommands.m_strF7CMD;
    m_MPlayerGUICfg.strF8CMD = PageCommands.m_strF8CMD;

    // Set MPlayer path according to m_MPlayerGUICfg.bMPlayerPath
    SetMPlayerPathName();

    // Save all config settings
    WriteIniSettings();
  }
}

// Read config settings from .ini file
// All default values goes here
void CMainFrame::ReadIniSettings(void)
{
  CAppSettings MyAppSettings;

  CString strMPlayerPathName;
  CString strMPlayerUserConfig;
  CString strSubtitleFont;

  m_MPlayerGUICfg.bMPlayerPathName = MyAppSettings.ReadBoolean(MPLAYER_CFG_bMPlayerPathName, FALSE);
  MyAppSettings.ReadString(MPLAYER_CFG_strMPlayerPathName, strMPlayerPathName, "");
  m_MPlayerGUICfg.strMPlayerPathName = strMPlayerPathName;
  m_MPlayerGUICfg.bShowToolbar = MyAppSettings.ReadBoolean(MPLAYER_CFG_bShowToolbar, TRUE);
  m_MPlayerGUICfg.bShowStatusBar = MyAppSettings.ReadBoolean(MPLAYER_CFG_bShowStatusBar, TRUE);
  m_MPlayerGUICfg.bShowProgressBar = MyAppSettings.ReadBoolean(MPLAYER_CFG_bShowProgressBar, TRUE);
  m_MPlayerGUICfg.bShowPlaylist = MyAppSettings.ReadBoolean(MPLAYER_CFG_bShowPlaylist, FALSE);
  m_MPlayerGUICfg.nSSDisableMode = MyAppSettings.ReadInteger(MPLAYER_CFG_nSSDisableMode, 2);
  m_MPlayerGUICfg.nPresetZoom = MyAppSettings.ReadInteger(MPLAYER_CFG_nPresetZoom, 100);
  m_MPlayerGUICfg.bAllowMultipleInstances = MyAppSettings.ReadBoolean(MPLAYER_CFG_bAllowMultipleInstances, FALSE);
  m_MPlayer.SetVideoOutputDriver(MyAppSettings.ReadInteger(MPLAYER_CFG_nVideoOutputDriver, 2));
  m_MPlayer.SetAudioOutputDriver(MyAppSettings.ReadInteger(MPLAYER_CFG_nAudioOutputDriver, 2));
  m_MPlayerGUICfg.bAutoShuffle = MyAppSettings.ReadBoolean(MPLAYER_CFG_bAutoShuffle, FALSE);
  m_MPlayerGUICfg.bStartupAlwaysOnTop = MyAppSettings.ReadBoolean(MPLAYER_CFG_bStartupAlwaysOnTop, FALSE);
  m_MPlayerGUICfg.bLaunchInFullscreen = MyAppSettings.ReadBoolean(MPLAYER_CFG_bLaunchInFullscreen, FALSE);
  m_MPlayer.SetAutoloadSubtitles(MyAppSettings.ReadBoolean(MPLAYER_CFG_bAutoloadSubtitles, FALSE));
  m_MPlayer.SetSubCP(MyAppSettings.ReadInteger(MPLAYER_CFG_nSubCP, 0));
  MyAppSettings.ReadString(MPLAYER_CFG_strSubtitleFont, strSubtitleFont, "");
  m_MPlayer.SetSubtitleFont(strSubtitleFont);
  MyAppSettings.ReadString(MPLAYER_CFG_strMPlayerUserConfig, strMPlayerUserConfig, "");
  m_MPlayer.SetMPlayerUserConfig(strMPlayerUserConfig);
  m_MPlayer.SetMPlayerPriority(MyAppSettings.ReadInteger(MPLAYER_CFG_nMPlayerPriority, 2));
  m_MPlayerGUICfg.bDisableMPlayerMonitor = MyAppSettings.ReadBoolean(MPLAYER_CFG_bDisableMPlayerMonitor, FALSE);
  m_MPlayer.SetDisableMPlayerMonitor(m_MPlayerGUICfg.bDisableMPlayerMonitor);
  m_MPlayerGUICfg.bEnableLogging = MyAppSettings.ReadBoolean(MPLAYER_CFG_bEnableLogging);
  m_MPlayer.SetEnableLogging(m_MPlayerGUICfg.bEnableLogging);

  m_MPlayerGUIStatus.bBypassWinVersionCheck = MyAppSettings.ReadBoolean(MPLAYER_CFG_bBypassWinVersionCheck, FALSE);

  m_MPlayer.SetVideoBrightness(MyAppSettings.ReadInteger(MPLAYER_CFG_nVideoBrightness, 0));
  m_MPlayer.SetVideoContrast(MyAppSettings.ReadInteger(MPLAYER_CFG_nVideoContrast, 0));
  m_MPlayer.SetVideoHue(MyAppSettings.ReadInteger(MPLAYER_CFG_nVideoHue, 0));
  m_MPlayer.SetVideoSaturation(MyAppSettings.ReadInteger(MPLAYER_CFG_nVideoSaturation, 0));
  m_MPlayer.SetDoubleBuffering(MyAppSettings.ReadBoolean(MPLAYER_CFG_bDoubleBuffering, FALSE));

  MyAppSettings.ReadString(MPLAYER_CFG_strF1CMD, m_MPlayerGUICfg.strF1CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF2CMD, m_MPlayerGUICfg.strF2CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF3CMD, m_MPlayerGUICfg.strF3CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF4CMD, m_MPlayerGUICfg.strF4CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF5CMD, m_MPlayerGUICfg.strF5CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF6CMD, m_MPlayerGUICfg.strF6CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF7CMD, m_MPlayerGUICfg.strF7CMD, "");
  MyAppSettings.ReadString(MPLAYER_CFG_strF8CMD, m_MPlayerGUICfg.strF8CMD, "");
}

// Write config settings to .ini file
void CMainFrame::WriteIniSettings(void)
{
  BOOL bSuccess;
  CAppSettings MyAppSettings;

  CString strMPlayerPathName;
  CString strMPlayerUserConfig;
  CString strSubtitleFont;

  m_MPlayer.GetMPlayerUserConfig(strMPlayerUserConfig);
  m_MPlayer.GetSubtitleFont(strSubtitleFont);

  MyAppSettings.WriteBoolean(MPLAYER_CFG_bMPlayerPathName, m_MPlayerGUICfg.bMPlayerPathName);
  MyAppSettings.WriteString(MPLAYER_CFG_strMPlayerPathName, m_MPlayerGUICfg.strMPlayerPathName);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bShowToolbar, m_MPlayerGUICfg.bShowToolbar);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bShowStatusBar, m_MPlayerGUICfg.bShowStatusBar);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bShowProgressBar, m_MPlayerGUICfg.bShowProgressBar);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bShowPlaylist, m_MPlayerGUICfg.bShowPlaylist);
  MyAppSettings.WriteInteger(MPLAYER_CFG_nSSDisableMode, m_MPlayerGUICfg.nSSDisableMode);
  MyAppSettings.WriteInteger(MPLAYER_CFG_nPresetZoom, m_MPlayerGUICfg.nPresetZoom);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bAllowMultipleInstances, m_MPlayerGUICfg.bAllowMultipleInstances);
  MyAppSettings.WriteInteger(MPLAYER_CFG_nVideoOutputDriver, m_MPlayer.GetVideoOutputDriver());
  MyAppSettings.WriteInteger(MPLAYER_CFG_nAudioOutputDriver, m_MPlayer.GetAudioOutputDriver());
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bAutoloadSubtitles, m_MPlayer.GetAutoloadSubtitles());
  MyAppSettings.WriteInteger(MPLAYER_CFG_nSubCP, m_MPlayer.GetSubCP());
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bAutoShuffle, m_MPlayerGUICfg.bAutoShuffle);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bStartupAlwaysOnTop, m_MPlayerGUICfg.bStartupAlwaysOnTop);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bLaunchInFullscreen, m_MPlayerGUICfg.bLaunchInFullscreen);
  bSuccess = MyAppSettings.WriteString(MPLAYER_CFG_strMPlayerUserConfig, strMPlayerUserConfig);
  MyAppSettings.WriteString(MPLAYER_CFG_strSubtitleFont, strSubtitleFont);
  MyAppSettings.WriteInteger(MPLAYER_CFG_nMPlayerPriority, m_MPlayer.GetMPlayerPriority());
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bDisableMPlayerMonitor, m_MPlayerGUICfg.bDisableMPlayerMonitor);
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bEnableLogging, m_MPlayerGUICfg.bEnableLogging);
  MyAppSettings.WriteInteger(MPLAYER_CFG_nVideoBrightness, m_MPlayer.GetVideoBrightness());
  MyAppSettings.WriteInteger(MPLAYER_CFG_nVideoContrast, m_MPlayer.GetVideoContrast());
  MyAppSettings.WriteInteger(MPLAYER_CFG_nVideoHue, m_MPlayer.GetVideoHue());
  MyAppSettings.WriteInteger(MPLAYER_CFG_nVideoSaturation, m_MPlayer.GetVideoSaturation());
  MyAppSettings.WriteBoolean(MPLAYER_CFG_bDoubleBuffering, m_MPlayer.GetDoubleBuffering());

  MyAppSettings.WriteString(MPLAYER_CFG_strF1CMD, m_MPlayerGUICfg.strF1CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF2CMD, m_MPlayerGUICfg.strF2CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF3CMD, m_MPlayerGUICfg.strF3CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF4CMD, m_MPlayerGUICfg.strF4CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF5CMD, m_MPlayerGUICfg.strF5CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF6CMD, m_MPlayerGUICfg.strF6CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF7CMD, m_MPlayerGUICfg.strF7CMD);
  MyAppSettings.WriteString(MPLAYER_CFG_strF8CMD, m_MPlayerGUICfg.strF8CMD);

  if (bSuccess == TRUE)
  {
    // Dont inform user, or it will getting annoying
    // MessageBox("Settings Saved.");
  }
  else
  {
    MessageBox("Failed to Save Settings!");
  }
}

// Set MPlayer binary path name according to m_MPlayerGUICfg.bMPlayerPathName
void CMainFrame::SetMPlayerPathName(void)
{
  if (m_MPlayerGUICfg.bMPlayerPathName == TRUE)
  {
    CString strAbsPathname;
    CString strRelPath;
    // If m_MPlayerGUICfg.strMPlayerPathName is relative, convert to absolute
    // find ":\" in m_MPlayerGUICfg.strMPlayerPathName, if not found, means relative path
    if (m_MPlayerGUICfg.strMPlayerPathName.Find(":\\") == -1)
    {
      // convert to absolute path
      strRelPath = m_strAppDirectory + _T("\\"); // for PathInfo
      strAbsPathname = PathInfo::getAbsPath(m_MPlayerGUICfg.strMPlayerPathName, strRelPath);
      m_MPlayer.SetMPlayerPathName(strAbsPathname);
      // AfxMessageBox(strAbsPathname);
    }
    else
    {
      m_MPlayer.SetMPlayerPathName(m_MPlayerGUICfg.strMPlayerPathName);
    }
    // AfxMessageBox(m_MPlayerGUICfg.strMPlayerPathName);
  }
  else
  {
    m_MPlayer.SetMPlayerPathName(m_MPlayerGUICfg.strDefaultMPlayerPathName);
    // AfxMessageBox(m_MPlayerGUICfg.strDefaultMPlayerPathName);
  }
}

// Change frame window title
void CMainFrame::ChangeTitle(CString strTitle)
{
  // CMPlayerGUIDoc *pDoc;
  // pDoc = (CMPlayerGUIDoc*)GetActiveDocument();
  // pDoc->SetTitle(_T(strTitle));

  // CString title(MAKEINTRESOURCE(IDR_MAINFRAME));
  CString title;
  // FIXME: Why can not i load the IDR_MAINFRAME? SDI bug
  title = "MPlayerGUI";

  if (strTitle.GetLength() > 0)
  {
    title = strTitle + _T(" - ") + title;
  }
  else
  {
    // keep title
  }

	SetWindowText(title);
}

// Dropped file handler
void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
  int i = 0;
  TCHAR szFileName[_MAX_PATH];
  UINT nFiles = ::DragQueryFile(hDropInfo, (UINT) -1, NULL, 0);

  // If there are more than 1 files has been dropped, call Playlist handle
  if (nFiles > 1)
  {
    // Stop the playback
    // DoPlayStop();
    // Clean the Playlist
    m_pPlaylistDlg->DoPlayListRemoveAll();
    // Add dropped files to Playlist
    m_pPlaylistDlg->OnDropFiles(hDropInfo);
    // Play from first
    m_pPlaylistDlg->PlayFromFirst();
  }
  else // If there is only 1 file has been dropped, pass it to the DoFileOpen()
  {
    // Only process one file (first one)
    ::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
    DoFileOpen(_T(szFileName));
  }

  ::DragFinish(hDropInfo);
}

// Reture if current window is minmal or maximal
BOOL CMainFrame::IsWindowMinOrMax(void)
{
  WINDOWPLACEMENT wp;
  wp.length = sizeof (WINDOWPLACEMENT);

  GetWindowPlacement(&wp);

  if ((wp.showCmd == SW_SHOWMAXIMIZED) || (wp.showCmd == SW_SHOWMINIMIZED))
  {
    return TRUE;
  }

  return FALSE;
}


BOOL CMainFrame::IsWindowMax(void)
{
  WINDOWPLACEMENT wp;
  wp.length = sizeof (WINDOWPLACEMENT);

  GetWindowPlacement(&wp);

  if (wp.showCmd == SW_SHOWMAXIMIZED)
  {
    return TRUE;
  }

  return FALSE;
}


// Restore to normal window if the current window is minimal/maximal
void CMainFrame::RestoreFromMaxMin(void)
{
  WINDOWPLACEMENT wp;

  if (IsWindowMinOrMax())
  {
    wp.showCmd = SW_RESTORE;
    SetWindowPlacement(&wp);
  }
}

// Toggle full screen mode
void CMainFrame::OnViewFullscreen() 
{
  CRect r;
  CMPlayerGUIView *pView;
  pView = (CMPlayerGUIView*)GetActiveView();

  if (m_MPlayerGUIStatus.bFullScreen == FALSE)
  {
    m_MPlayerGUIStatus.bFullScreen = TRUE;

    // Save the current window rect
    GetWindowRect(&m_MPlayerGUIStatus.rLastWindowRect);

    // Get current visible state of bars, and hide them
    m_MPlayerGUIStatus.bToolbarVisible = m_wndMyToolBar.IsWindowVisible();
    if (m_MPlayerGUIStatus.bToolbarVisible)
    {
      ShowControlBar(&m_wndMyToolBar, FALSE, FALSE);
    }
    m_MPlayerGUIStatus.bStatusBarVisible = m_wndStatusBar.IsWindowVisible();
    if (m_MPlayerGUIStatus.bStatusBarVisible)
    {
      ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
    }
    m_MPlayerGUIStatus.bProgressBarVisible = m_wndProgressDlgBar.IsWindowVisible();
    if (m_MPlayerGUIStatus.bProgressBarVisible)
    {
      ShowControlBar(&m_wndProgressDlgBar, FALSE, FALSE);
    }
    m_MPlayerGUIStatus.bPlaylistVisible = m_pPlaylistDlg->IsWindowVisible();
    if (m_MPlayerGUIStatus.bPlaylistVisible)
    {
      m_pPlaylistDlg->ShowWindow(SW_HIDE);
    }

    // Start full screen...

    // Get full screen rect
    GetDesktopWindow()->GetWindowRect(&m_MPlayerGUIStatus.rFullScreenWindowRect);
    // Hide caption, thickframe, ...
    ModifyStyle(WS_CAPTION | WS_THICKFRAME, NULL, SWP_NOZORDER);
    // Hide menu
    ::SetMenu(m_hWnd, NULL);
    // Turn off view client edge
    pView->EnableClientEdge(FALSE);
    // For convinence
    r = m_MPlayerGUIStatus.rFullScreenWindowRect;
    // Set window position
    SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER | SWP_NOSENDCHANGING /*SWP_FRAMECHANGED*/);

    // AlwaysOnTop
    DoAlwaysOnTop(TRUE);

    // Grab the input focus
    SetFocus();

    // start FULLSCREEN mouse cursor hider timer
    SetTimer(TIMER_FULLSCREENMOUSEHIDER, 1000, NULL);
  }
  else
  {
    m_MPlayerGUIStatus.bFullScreen = FALSE;

    // Turn on view client edge
    pView->EnableClientEdge(TRUE);

    // Restore bars to ex-full screen state
    if (m_MPlayerGUIStatus.bToolbarVisible)
    {
      ShowControlBar(&m_wndMyToolBar, TRUE, FALSE);
    }
    if (m_MPlayerGUIStatus.bStatusBarVisible)
    {
      ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
    }
    if (m_MPlayerGUIStatus.bProgressBarVisible)
    {
      ShowControlBar(&m_wndProgressDlgBar, TRUE, FALSE);
    }
    if (m_MPlayerGUIStatus.bPlaylistVisible)
    {
      m_pPlaylistDlg->ShowWindow(SW_SHOW);
    }

    // Show caption, thickframe, ...
    ModifyStyle(NULL, WS_CAPTION | WS_THICKFRAME, SWP_NOZORDER);
    // Show menu
    ::SetMenu(m_hWnd, m_hMenuDefault);
    // For convinence
    r = m_MPlayerGUIStatus.rLastWindowRect;
    // Set window position
    SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER | SWP_NOSENDCHANGING /*SWP_FRAMECHANGED*/);

    // Turns off AlwaysOnTop according to m_MPlayerGUIStatus.bTopMostWindow
    DoAlwaysOnTop(m_MPlayerGUIStatus.bTopMostWindow);

    // kill FULLSCREEN mouse cursor hider timer
    KillTimer(TIMER_FULLSCREENMOUSEHIDER);
  }
}

// UWM_PLAYLIST_PLAY message handler
CMainFrame::OnPlayListPlay(WPARAM wParam, LPARAM lParam)
{
  CString strPlayListName;

  // Get playlist filename from PlayListDlgBar
  m_pPlaylistDlg->GetFileToPlay(strPlayListName);
  m_MPlayerGUIStatus.strSource = strPlayListName;
  m_MPlayer.SetSource(m_MPlayerGUIStatus.strSource);

  DoPlayStop();
  DoPlayPlay();

  return 1;
}

// Try to play next in playlist
void CMainFrame::PlayListTryNextFile(void)
{
  int nPlayListReturn;
  CString strPlayListName;

  nPlayListReturn = m_pPlaylistDlg->RequestNextFile();

  if ((m_MPlayerGUIStatus.bRepeatMode == TRUE) && (nPlayListReturn == -1))
  {
    // Try to rewind and check if there is at least 1 file in playlist
    if (m_pPlaylistDlg->RewindPlayList() == 1)
    {
      nPlayListReturn = 1; // cheating

      // Shuffle playlist if bAutoShuffle is true
      if (m_MPlayerGUICfg.bAutoShuffle)
      {
        m_pPlaylistDlg->Shuffle();
        // Rewind
        m_pPlaylistDlg->RewindPlayList();
      }
    }
  }

  if (nPlayListReturn != -1)
  {
    // Get filename from PlayList
    m_pPlaylistDlg->GetFileToPlay(strPlayListName);
    m_MPlayerGUIStatus.strSource = strPlayListName;
    m_MPlayer.SetSource(m_MPlayerGUIStatus.strSource);

    DoPlayStop();
    DoPlayPlay();
  }
  else
  {
    // Otherwise there is no more file in playlist, and no repeat, keep in stop state
    // Turn off full screen
    if (m_MPlayerGUIStatus.bFullScreen)
    {
      OnViewFullscreen();
    }

    // If user want shutdown PC, show the dialog here
    if (m_MPlayerGUICfg.nAfterplayback == 1)
    {
      CShutdownDlg MyShutdownDlg;
      MyShutdownDlg.DoModal();
    }
  }
}

// Play->Repeat handler
void CMainFrame::OnPlayRepeat() 
{
  m_MPlayerGUIStatus.bRepeatMode = !m_MPlayerGUIStatus.bRepeatMode;
}

void CMainFrame::OnUpdatePlayRepeat(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_MPlayerGUIStatus.bRepeatMode);
}

// Say goodbye to MPlayerGUI, about to close
void CMainFrame::OnClose() 
{
  // About to terminate, do some last minute stuff
  DoLastMinuteCleanUp();

  // Save Volume
  CAppSettings MyAppSettings;
  int nVolume = m_wndMyToolBar.GetSliderVolume();
  if (m_MPlayerGUICfg.nVolumeLoaded != nVolume)
  {
    MyAppSettings.WriteInteger(MPLAYER_CFG_nVolume, nVolume);
  }

	CFrameWnd::OnClose();
}

// Last minute clean up job
void CMainFrame::DoLastMinuteCleanUp(void)
{
  // Quitting...
  m_wndStatusBar.SetMessage(_T("Quitting..."));

  // Make sure that MPlayer is terminated
  m_MPlayer.Stop();
  // Cleanup
  PlayerCleanUp();
  // Restore screen saver status...
  m_SSDisabler.Restore();

  // Delete PlaylistDlg (modaless)
  if (m_pPlaylistDlg)
    delete m_pPlaylistDlg;

  if (m_pLogDlg)
    delete m_pLogDlg;
}

// UWM_PLAYLIST_DLG_HIDE handler
CMainFrame::OnPlaylistDlgHide(WPARAM wParam, LPARAM lParam)
{
  m_pPlaylistDlg->ShowWindow(SW_HIDE);
  return 1;
}

// View->PlayList handler
void CMainFrame::OnViewPlaylist() 
{
  if (m_pPlaylistDlg->IsWindowVisible())
  {
    m_pPlaylistDlg->ShowWindow(SW_HIDE);
  }
  else
  {
    CRect rc_this, rc_pl;

    m_pPlaylistDlg->GetWindowRect(&rc_pl);
    GetWindowRect(&rc_this);

    // Move playlist window to the bottom of this window (mainframe)
    m_pPlaylistDlg->MoveWindow(rc_this.left,
                               rc_this.bottom,
                               rc_pl.Width(),
                               rc_pl.Height(),
                               FALSE);

    m_pPlaylistDlg->ShowWindow(SW_SHOW);
  }
}

void CMainFrame::OnUpdateViewPlaylist(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_pPlaylistDlg->IsWindowVisible());
}

// View->ToolBar handler
void CMainFrame::OnViewMytoolbar() 
{
  ShowControlBar(&m_wndMyToolBar, !m_wndMyToolBar.IsWindowVisible(), TRUE);
}

void CMainFrame::OnUpdateViewMytoolbar(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_wndMyToolBar.IsWindowVisible());
}

/*
void CMainFrame::OnOptionsSavesettings() 
{
  // Save all config settings
  WriteIniSettings();
}
*/

// Called when user double clicked an assoicated file
CMainFrame::OnStartupOpenfile(WPARAM wParam, LPARAM lParam)
{
  // Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo cmdInfo;
  AfxGetApp()->ParseCommandLine(cmdInfo);

  if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
  {
    DoFileOpen(_T(cmdInfo.m_strFileName));
  }

  return 1;
}


// UWM_VIEW_MPLAYER_PAUSE handler
CMainFrame::OnViewMPlayerPause(WPARAM wParam, LPARAM lParam)
{
  OnPlayPause();
  return 1;
}

// UWM_VIEW_MPLAYER_FULLSCREEN handler
CMainFrame::OnViewMPlayerFullScreen(WPARAM wParam, LPARAM lParam)
{
  int nStatus = m_MPlayer.GetStatus();

  // if no file is playing popup the FileOpen dialog
  if (nStatus == MPLAYER_STOPPED)
  {
    OnFileOpen();
  }
  else
  {
    OnViewFullscreen();
  }

  return 1;
}

// Play->Next handler
void CMainFrame::OnPlayNext() 
{
  int nPlayListReturn;
  CString strPlayListName;
  int nStatus = m_MPlayer.GetStatus();

  if (nStatus != MPLAYER_PLAYING)
    return;

  nPlayListReturn = m_pPlaylistDlg->RequestNextFile();

  if (nPlayListReturn != -1)
  {
    // Get filename from PlayList
    m_pPlaylistDlg->GetFileToPlay(strPlayListName);
    m_MPlayerGUIStatus.strSource = strPlayListName;
    m_MPlayer.SetSource(m_MPlayerGUIStatus.strSource);

    DoPlayStop();
    DoPlayPlay();
  }
}

// Play->Previous handler
void CMainFrame::OnPlayPrevious() 
{
  int nPlayListReturn;
  CString strPlayListName;
  int nStatus = m_MPlayer.GetStatus();

  if (nStatus != MPLAYER_PLAYING)
    return;

  nPlayListReturn = m_pPlaylistDlg->RequestPreviousFile();

  if (nPlayListReturn != -1)
  {
    // Get filename from PlayList
    m_pPlaylistDlg->GetFileToPlay(strPlayListName);
    m_MPlayerGUIStatus.strSource = strPlayListName;
    m_MPlayer.SetSource(m_MPlayerGUIStatus.strSource);

    DoPlayStop();
    DoPlayPlay();
  }
}

void CMainFrame::DoFileOpen(CString strFileName)
{
  CString strExtension;

  strExtension = PathInfo::getExtension(_T(strFileName));

  // If user opened a playlist file, load it in the playlist and play from the first
  if ((strExtension.CompareNoCase(_T("txt")) == 0)
      || (strExtension.CompareNoCase(_T("pls")) == 0)
      || (strExtension.CompareNoCase(_T("m3u")) == 0)
      || (strExtension.CompareNoCase(_T("ram")) == 0))
  {
    DoPlayStop();
    m_pPlaylistDlg->LoadPlayList(strFileName);

    // Shuffle playlist if bAutoShuffle is true
    if (m_MPlayerGUICfg.bAutoShuffle)
    {
      m_pPlaylistDlg->Shuffle();
    }

    m_pPlaylistDlg->PlayFromFirst();
  }
  else // User opened a media file (i hope), add it to the playlist and play it
  {
    // Stop the playback
    // DoPlayStop();
    // Clean the Playlist
    m_pPlaylistDlg->DoPlayListRemoveAll();
    // Add the media file as one entry
    m_pPlaylistDlg->AddPlayListEntry(strFileName);
    // Play from first
    m_pPlaylistDlg->PlayFromFirst();
  }
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
  // ESC to quit FullScreen mode
  if(pMsg->message == WM_KEYDOWN)
  {
    if((pMsg->wParam == VK_ESCAPE) && (m_MPlayerGUIStatus.bFullScreen == TRUE))
    {
      OnViewFullscreen();
      return TRUE;
    }
  }

	return CFrameWnd::PreTranslateMessage(pMsg);
}

// File->Open URL handle
void CMainFrame::OnFileOpenurl() 
{
  COpenURLDlg OpenURLDlg;

	if (OpenURLDlg.DoModal() == IDOK)
	{
	  DoFileOpen(OpenURLDlg.m_strOpenURL);
	}
}


// Handlers for CMPlayer message

// Called when MPlayer is starting
CMainFrame::OnMPlayerStarting(WPARAM wParam, LPARAM lPARAM)
{
  // Starting...
  m_wndStatusBar.SetMessage(_T("Starting..."));

  SetTimer(TIMER_HALF_SECOND, 500, NULL);
  SetTimer(TIMER_ONE_SECOND, 1000, NULL);
  SetTimer(TIMER_CACHEFILL, 300, NULL);

  // StatusBar: Buffering
  // m_wndStatusBar.StartBuffering();
  // m_wndStatusBar.SetStatusMode(STATUSMODE_BUFFERING);
  m_wndStatusBar.SetStatusMode(STATUSMODE_IDLE);

  return 1;
}

// Called right after MPlayer started to play
CMainFrame::OnMPlayerStartPlaying(WPARAM wParam, LPARAM lParam)
{
  KillTimer(TIMER_CACHEFILL);
  // Pre-set volume
  // TODO: Should get volume from VolumeSlider
  // int nVolume = m_MPlayer.GetVolume();
  int nVolume = m_wndMyToolBar.GetSliderVolume();
  m_MPlayer.SetVolume(nVolume);

  // Update panel: Duration
  GetTimeLength();

  // Get video information
  BOOL bHaveVideo = m_MPlayer.HaveVideo();
  int nVideoWidth = m_MPlayer.GetVideoInfo_Width();
  int nVideoHeight = m_MPlayer.GetVideoInfo_Height();

  // Turn off full screen
  /*
  if (m_MPlayerGUIStatus.bFullScreen)
  {
    OnViewFullscreen();
  }
  */

  // Resize the main frame to video size
  if (bHaveVideo == TRUE)
  {
    if (m_MPlayerGUIStatus.bFullScreen == TRUE)
    {
      FitWindow(TRUE, nVideoWidth, nVideoHeight);
    }
    else
    {
      PresetVideoSize();

      if (m_MPlayerGUICfg.bLaunchInFullscreen)
      {
        OnViewFullscreen();
      }
    }
  }
  else
  {
    FitWindow(FALSE, nVideoWidth, nVideoHeight);
  }

  long lDuration = m_MPlayer.GetClipInfo_Length();
  // Enable progress bar (enable seek)
  if (lDuration > 0)
  {
    m_wndProgressDlgBar.EnableProgressBar(TRUE);
  }

  // Disable screen saver
  if ((m_MPlayerGUICfg.nSSDisableMode == 1)
    || ((m_MPlayerGUICfg.nSSDisableMode == 2) && (bHaveVideo)))
  {
    m_SSDisabler.Disable();
  }

  // Get title
  CString strTitle, strName;
  strTitle = PathInfo::getTitle(_T(m_MPlayerGUIStatus.strSource));
  strName = PathInfo::getName(_T(m_MPlayerGUIStatus.strSource));

  ChangeTitle(strName);

  // Set Labels in View
  CMPlayerGUIView *pView;
  pView = (CMPlayerGUIView*)GetActiveView();

  CString strLabelArtist, strLabelTitle;
  strLabelArtist = m_MPlayer.GetClipInfo_Artist();
  strLabelTitle = m_MPlayer.GetClipInfo_Title();

  if ((strLabelArtist == "-") && (strLabelTitle == "-"))
  {
    pView->SetLabelInfo("", strTitle);
  }
  else
  {
    pView->SetLabelInfo(strLabelArtist, strLabelTitle);
  }

  // m_wndStatusBar.StopBuffering();
  m_wndStatusBar.SetAudioMode(m_MPlayer.GetAudioInfo_NCH());
  m_wndStatusBar.SetStatusMode(STATUSMODE_LOCALMEDIA); // FIXME: set to corresponding media type
  m_wndStatusBar.SetMessage(_T("Playing"));

  // Fillup the flip info
  CString strFlipInfo;
  // Bitrate
  long lBitRate;
  lBitRate = m_MPlayer.GetAudioInfo_Bitrate() + m_MPlayer.GetVideoInfo_Bitrate();
  lBitRate = lBitRate / 1000;
  strFlipInfo.Format("Now Playing: %ld Kbps", lBitRate);
  m_wndStatusBar.SetFlipInfo0(strFlipInfo);

  if (bHaveVideo) // Audio and Video Clip
  {
    // Clip
    strFlipInfo.Format("Clip: %s", m_MPlayer.GetClipInfo_Title());
    m_wndStatusBar.SetFlipInfo1(strFlipInfo);
    // Author
    strFlipInfo.Format("Author: %s", m_MPlayer.GetClipInfo_Artist());
    m_wndStatusBar.SetFlipInfo2(strFlipInfo);
    // Copyright
    strFlipInfo.Format("Copyright: %s", m_MPlayer.GetClipInfo_Copyright());
    m_wndStatusBar.SetFlipInfo3(strFlipInfo);
    // Rating
    strFlipInfo.Format("Rating: %s", m_MPlayer.GetClipInfo_Rating());
    m_wndStatusBar.SetFlipInfo4(strFlipInfo);
  }
  else
  {
    // Album
    strFlipInfo.Format("Album: %s", m_MPlayer.GetClipInfo_Album());
    m_wndStatusBar.SetFlipInfo1(strFlipInfo);
    // Title
    strFlipInfo.Format("Title: %s", m_MPlayer.GetClipInfo_Title());
    m_wndStatusBar.SetFlipInfo2(strFlipInfo);
    // Artist
    strFlipInfo.Format("Artist: %s", m_MPlayer.GetClipInfo_Artist());
    m_wndStatusBar.SetFlipInfo3(strFlipInfo);
    // Genre
    strFlipInfo.Format("Genre: %s", m_MPlayer.GetClipInfo_Genre());
    m_wndStatusBar.SetFlipInfo4(strFlipInfo);
  }

  m_wndStatusBar.StartFlipInfo();

  return 1;
}

// Called after MPlayer failed to start
CMainFrame::OnMPlayerFailedToStart(WPARAM wParam, LPARAM lParam)
{
  PlayerCleanUp();

  m_wndStatusBar.SetMessage(_T("MPlayer failed to start"));
  // Failed to Start
  m_wndStatusBar.SetStatusMode(STATUSMODE_FAILED);

  // Try next in list after failed
  {
    PlayListTryNextFile();
  }

  return 1;
}

// Called after MPlayer is stopped (by user)
CMainFrame::OnMPlayerStopped(WPARAM wParam, LPARAM lParam)
{
  PlayerCleanUp();
  m_SSDisabler.Restore();
  return 1;
}

// Called after MPlayer is stopped (by itself, ex: Finished Playing)
CMainFrame::OnMPlayerAutoStopped(WPARAM wParam, LPARAM lParam)
{
  // Clean up status variables
  PlayerCleanUp();

  // Restore screen saver status...
  m_SSDisabler.Restore();

  // Since this is auto-stop, check if user want repeat or play next in play list
  {
    PlayListTryNextFile();
  }
  // else
  /*
  {
    if (m_MPlayerGUIStatus.bRepeatMode == TRUE)
    {
      DoPlayPlay();
    }
    else
    {
      // Turn off full screen
      if (m_MPlayerGUIStatus.bFullScreen)
      {
        OnViewFullscreen();
      }
    }
  }
  */

	return 1;
}

int CMainFrame::GetFrameMinusViewHeight(void)
{
  int nHeight;

  nHeight = 0;

  // the Menu height
  // (SM_CYMENU for menu bar height, SM_CYMENUSIZE for menu bar button height)
  nHeight += ::GetSystemMetrics(SM_CYMENU); // SM_CYMENUSIZE

  DWORD style = GetStyle();

  if (style & WS_CAPTION)
    nHeight += GetSystemMetrics(SM_CYCAPTION);

  if (style & WS_THICKFRAME)
    nHeight += GetSystemMetrics((style & WS_CAPTION) ? SM_CYSIZEFRAME:SM_CYFIXEDFRAME) * 2;

  if (IsWindow(m_wndMyToolBar.m_hWnd))
  {
    if (m_wndMyToolBar.IsWindowVisible())
    {
      nHeight += m_wndMyToolBar.CalcFixedLayout(FALSE, TRUE).cy;
    }
  }

  if (IsWindow(m_wndStatusBar.m_hWnd))
  {
    if (m_wndStatusBar.IsWindowVisible())
    {
      nHeight += m_wndStatusBar.CalcFixedLayout(FALSE, TRUE).cy;
    }
  }

  if (IsWindow(m_wndProgressDlgBar.m_hWnd))
  {
    if (m_wndProgressDlgBar.IsWindowVisible())
    {
      nHeight += m_wndProgressDlgBar.CalcFixedLayout(FALSE, TRUE).cy;
    }
  }

  return nHeight;
}


int CMainFrame::GetFrameMinusViewWidth(void)
{
  int nWidth;
  nWidth = 0;

  DWORD style = GetStyle();

  if (style & WS_THICKFRAME)
    nWidth += GetSystemMetrics(SM_CXSIZEFRAME) * 2;

  return nWidth;
}

// Play->Go To... handler
void CMainFrame::OnPlayGoto() 
{
  CGotoDlg GotoDlg;

  if (GotoDlg.DoModal() == IDOK)
  {
    int nStatus = m_MPlayer.GetStatus();

    if (nStatus == MPLAYER_PLAYING)
    {
      long lSeekTime;
      long lHours, lMinutes, lSeconds;

      lHours = GotoDlg.GetHours();
      lMinutes = GotoDlg.GetMinutes();
      lSeconds = GotoDlg.GetSeconds();

      // Calculate where to seek
      lSeekTime = (long)(lHours * 3600 + lMinutes * 60 + lSeconds);

      long lDuration = m_MPlayer.GetClipInfo_Length();

      if ((lSeekTime >= 0L) && (lSeekTime < lDuration))
      {
        m_MPlayer.SeekTime(lSeekTime);
      }
    }
  }
}

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
  CFrameWnd::RecalcLayout(bNotify);

  // Resize the framewindow after toggle the control bars
  CRect r;
  GetWindowRect(&r);
  MINMAXINFO mmi;
  memset(&mmi, 0, sizeof(mmi));
  SendMessage(WM_GETMINMAXINFO, 0, (LPARAM)&mmi);
  r |= CRect(r.TopLeft(), CSize(r.Width(), mmi.ptMinTrackSize.y));
  MoveWindow(&r);
}


BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
  CString strRecievedText = (LPCSTR) (pCopyDataStruct->lpData);
  
  // AfxMessageBox(strRecievedText);
  DoFileOpen(_T(strRecievedText));
	
	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}


void CMainFrame::OnViewStatusbar() 
{
  ShowControlBar(&m_wndStatusBar, !m_wndStatusBar.IsWindowVisible(), TRUE);
}


void CMainFrame::OnUpdateViewStatusbar(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_wndStatusBar.IsWindowVisible());
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
  switch (nIDEvent)
  {
    case TIMER_HALF_SECOND:
    {
      UpdateTimePos();
      break;
    }
    case TIMER_ONE_SECOND:
    {
      UpdateProgress();
      break;
    }
    case TIMER_CACHEFILL:
    {
      UpdateCacheFill();
      break;
    }
    case TIMER_FULLSCREENMOUSEHIDER:
    {
      CPoint p;
      GetCursorPos(&p);
      CRect r;
      GetWindowRect(r);

      CMPlayerGUIView *pView;
      pView = (CMPlayerGUIView*)GetActiveView();

      if (!pView->IsContextMenuShown())
      {
        // only SetCursor to NULL if in rect and cursor is not null
	      if ((r.PtInRect(p)) && (GetCursor() != NULL))
        {
          SetCursor(NULL);
        }
      }

      break;
    }
    default:
    {
      break;
    }
  }
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::UpdateTimePos(void)
{
  // Get MPlayer Time Position
  int nStatus = m_MPlayer.GetStatus();
  long lTimePos;

  if (nStatus == MPLAYER_PLAYING)
  {
    lTimePos = m_MPlayer.GetTimePos();

    // -1 means mplayer don't respond to me :(
    if (lTimePos != -1)
    {
      // Compare to determine if a refeash is needed
      if (m_MPlayerGUIStatus.lTimePosOld != lTimePos)
      {
        m_MPlayerGUIStatus.lTimePosOld = lTimePos;
        m_wndStatusBar.SetTime(lTimePos);
      }
    }
  }
}

void CMainFrame::UpdateProgress(void)
{
  int nPercent = 0;
  float fTimePos, fTimeLength;

  if (m_MPlayerGUIStatus.nSkipOneUpdateOfProgressBar > 0)
  {
    m_MPlayerGUIStatus.nSkipOneUpdateOfProgressBar--;
    return;
  }

  // Since the MPlayer gives me wrong percent value when playing RealMedia clip
  // calculate the percent by hand
  // nPercent = m_MPlayer.GetPercentPos();
  fTimePos = (float)m_MPlayer.GetTimePos();
  fTimeLength = (float)m_MPlayer.GetClipInfo_Length();

  if (fTimePos > fTimeLength)
    return;

  if (fTimeLength == 0)
    nPercent = 0;
  else
    nPercent = (int)(fTimePos * 100 / fTimeLength);

  // -1 means mplayer don't respond me :(
  if (nPercent != -1)
  {
    // Check if a refeash is needed
    if (m_MPlayerGUIStatus.nPercent != nPercent)
    {
      m_MPlayerGUIStatus.nPercent = nPercent;
      m_wndProgressDlgBar.SetSliderProgress(nPercent);
    }
  }
}

void CMainFrame::UpdateCacheFill(void)
{
  float fCacheFill;
  CString strStatus;

  fCacheFill = m_MPlayer.GetCacheFill();

  if (m_MPlayerGUIStatus.fCacheFill != fCacheFill)
  {
    m_MPlayerGUIStatus.fCacheFill = fCacheFill;
    strStatus.Format("Cache fill: %2.02f%%", fCacheFill);
    m_wndStatusBar.SetMessage(strStatus);
  }
}


void CMainFrame::OnHelpHomepage() 
{
  ShellExecute(NULL,
    _T("open"),
    _T("http://sourceforge.net/projects/mplayerguiwin"),
    NULL,
    NULL,
    SW_SHOWNORMAL);
}

void CMainFrame::OnViewLog() 
{
  if (m_pLogDlg->IsWindowVisible())
  {
    m_pLogDlg->ShowWindow(SW_HIDE);
  }
  else
  {
    m_pLogDlg->ShowWindow(SW_SHOW);
  }
}

void CMainFrame::OnUpdateViewLog(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_pLogDlg->IsWindowVisible());	
}

// UWM_LOG_DLG_HIDE handler
CMainFrame::OnLogDlgHide(WPARAM wParam, LPARAM lParam)
{
  m_pLogDlg->ShowWindow(SW_HIDE);
  return 1;
}

// UWM_MPLAYER_LOG handler
CMainFrame::OnMPlayerLog(WPARAM wParam, LPARAM lParam)
{
  if (m_pLogDlg)
  {
    CString strLog;

    m_MPlayer.GetMPlayerLog(strLog);
    m_pLogDlg->Log(strLog);
  }

  return 1;
}

void CMainFrame::OnAfterplayback(UINT nID)
{
  switch(nID)
  {
    case ID_PLAY_AFTERPLAYBACK_SHUTDOWN:
    {
      m_MPlayerGUICfg.nAfterplayback = 1;
      break;
    }
    case ID_PLAY_AFTERPLAYBACK_DONOTHING:
    {
      m_MPlayerGUICfg.nAfterplayback = 0;
      break;
    }
    default:
    {
      break;
    }
  }
}

void CMainFrame::OnUpdateAfterplayback(CCmdUI* pCmdUI)
{
	bool fChecked = false;

	switch(pCmdUI->m_nID)
	{
    case ID_PLAY_AFTERPLAYBACK_SHUTDOWN:
    {
      if (m_MPlayerGUICfg.nAfterplayback == 1)
        fChecked = true;
      break;
    }
    case ID_PLAY_AFTERPLAYBACK_DONOTHING:
    {
      if (m_MPlayerGUICfg.nAfterplayback == 0)
        fChecked = true;
      break;
    }
    default:
    {
      break;
    }
  }

	pCmdUI->SetRadio(fChecked);
}

BOOL CMainFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
  ScreenToClient(&pt);

  int nStatus = m_MPlayer.GetStatus();
  int nVolume = m_MPlayer.GetVolume();

	BOOL fRet =
    zDelta > 0 ? nVolume += 10 :
    zDelta < 0 ? nVolume -= 10 : 
    FALSE;

  if (nVolume < 0)
    nVolume = 0;

  if (nVolume > 100)
    nVolume = 100;

  // if (nStatus == MPLAYER_PLAYING)
  {
    // Whatever is playing or not, set the value
    m_wndMyToolBar.SetSliderVolume(nVolume);
    m_MPlayer.SetVolume(nVolume);
  }

  return fRet;
	// return CFrameWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CMainFrame::OnF1CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF1CMD));
}

void CMainFrame::OnF2CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF2CMD));
}

void CMainFrame::OnF3CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF3CMD));
}

void CMainFrame::OnF4CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF4CMD));
}

void CMainFrame::OnF5CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF5CMD));
}

void CMainFrame::OnF6CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF6CMD));
}

void CMainFrame::OnF7CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF7CMD));
}

void CMainFrame::OnF8CMD()
{
  m_MPlayer.Command(_T(m_MPlayerGUICfg.strF8CMD));
}

