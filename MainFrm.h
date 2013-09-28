// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A154A451_51C5_4DFF_82E1_137B439B6ED1__INCLUDED_)
#define AFX_MAINFRM_H__A154A451_51C5_4DFF_82E1_137B439B6ED1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MPlayer.h"
#include "ProgressDlgBar.h"
#include "ssdisabler.h"
#include "PlaylistDlg.h"
#include "MyToolBar.h"
#include "PlayerStatusbar.h"
#include "LogDlg.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

private:
  // MPlayerGUI config, some will be saved to MPlayerGUI.ini
  typedef struct
  {
    BOOL bMPlayerPathName;         // use user specified MPlayer binary path name?
    BOOL bShowToolbar;             // show Toolbar on startup?
    BOOL bShowStatusBar;           // show Status Bar on startup?
    BOOL bShowProgressBar;         // show Progress Bar on startup?
    BOOL bShowPlaylist;            // show Playlist Dialog on startup?
    BOOL bAllowMultipleInstances;  // allow multiple instances?
    CString strDefaultMPlayerPathName; // default MPlayer binary path name
    CString strMPlayerPathName;    // user specified MPlayer binary path name
    int nSSDisableMode;            // Screen Saver Disable Mode
    BOOL bAutoShuffle;             // auto shuffle playlist?
    // BOOL bEnableMPlayerMonitor;    // enable MPlayerMonitor Thread? ====No need to be here, deleted
    // BOOL bEnableLogging;           // Enable/Disable Logging System? ====No need to be here, deleted
    BOOL bStartupAlwaysOnTop;      // 'Always on Top' on startup?
    BOOL bLaunchInFullscreen;      // Launch files in fullscreen?
    BOOL bShowControlsInFullscreen;
    // int nMPlayerMonitorThreshold; // ====No need to be here, deleted
    BOOL bRememberLastPlaybackPosition; // Remember last playback position?
    int nVolumeLoaded;             // Volume loaded from MPlayerGUI.ini
    int nAfterplayback;            // Action after playback
    int nPresetZoom;               // Preset Zoom by user
    // BOOL bEnableArgumentVolume;    // Enable Argument "-volume"? ====No need to be here, deleted
    CString strF1CMD;
    CString strF2CMD;
    CString strF3CMD;
    CString strF4CMD;
    CString strF5CMD;
    CString strF6CMD;
    CString strF7CMD;
    CString strF8CMD;
		// int nLogoID;                // Logo ID
  } MPlayerGUI_CONFIG;

  MPlayerGUI_CONFIG m_MPlayerGUICfg;

  // MPlayerGUI running status
  typedef struct
  {
    long lTimePosOld;            // for comparison
    int nSeekToPercent;          // for comparison
    int nZoomMode;               // current zoom mode
    float fCacheFill;            // for comparison
    BOOL bTopMostWindow;         // is the top most window?
    BOOL bKeepAspectRatio;       // keep video aspect ratio when zoom?
    BOOL bRepeatMode;            // current repeat mode
    CString strSource;           // MPlayer source media filename (to play)
    int nPercent;                // for comparison
    BOOL bFullScreen;            // is full screen?
    BOOL bToolbarVisible;        // tool bar visible?
    BOOL bStatusBarVisible;      // status bar visible?
    BOOL bProgressBarVisible;    // progress bar visible?
    BOOL bPlaylistVisible;       // playlist visible?
    CRect rFullScreenWindowRect;
    CRect rLastWindowRect;
    BOOL bBypassWinVersionCheck; // bypass windows version check, always send cmd
    int nSkipOneUpdateOfProgressBar; // skip one update message
    BOOL bBarsOnFullScreen;      // toolbars shown on fullscreen?
  } MPlayerGUI_STATUS;

  MPlayerGUI_STATUS m_MPlayerGUIStatus;

  CMPlayer m_MPlayer; // The MPlayer Core Interface
  CSSDisabler m_SSDisabler; // Screen Saver Disabler
  HWND m_hVideoPanel; // Handle of MPlayer Video Window (Embedded)

  CString m_strAppDirectory; // module path
  CPlaylistDlg *m_pPlaylistDlg; // play list modaless dialog
  CLogDlg *m_pLogDlg; // log modaless dialog

protected:
  void Init(void);

  void PlayerCleanUp(void);
  void GetTimeLength(void);
  void FitWindow(BOOL bHaveVideo, int nVideoWidth, int nVideoHeight);
  void PresetVideoSize(void);
  void DoAlwaysOnTop(BOOL bTop);

  int GetFrameMinusViewHeight(void);
  int GetFrameMinusViewWidth(void);

  void DoFileOpen(CString strFileName);
  void DoPlayPlay(void);
  void DoPlayStop(void);
  void PlayListTryNextFile(void);

  void ReadIniSettings(void);
  void WriteIniSettings(void);
  void SetMPlayerPathName(void);

  void UpdateTimePos(void);
  void UpdateProgress(void);
  void UpdateCacheFill(void);

  void ChangeTitle(CString strTitle);
  BOOL IsWindowMinOrMax(void);
  BOOL IsWindowMax(void);
  void RestoreFromMaxMin(void);

  void DoLastMinuteCleanUp(void);

  void ShowControlsInFullscreen(void);

  afx_msg void OnZoomSet(UINT nID);
  afx_msg void OnPlayForwardRewind(UINT nID);
  afx_msg void OnVolumeSet(UINT nID);
  afx_msg LRESULT OnSliderProgress(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSliderVolume(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnPlayListPlay(WPARAM wParam, LPARAM lParam);
  afx_msg void OnDropFiles(HDROP hDropInfo);
  afx_msg LRESULT OnPlaylistDlgHide(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnLogDlgHide(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnStartupOpenfile(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnViewMPlayerPause(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnViewMPlayerFullScreen(WPARAM wParam, LPARAM lParam);

  afx_msg void OnF1CMD();
  afx_msg void OnF2CMD();
  afx_msg void OnF3CMD();
  afx_msg void OnF4CMD();
  afx_msg void OnF5CMD();
  afx_msg void OnF6CMD();
  afx_msg void OnF7CMD();
  afx_msg void OnF8CMD();

  afx_msg LRESULT OnMPlayerStarting(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnMPlayerStartPlaying(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMPlayerFailedToStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMPlayerAutoStopped(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnMPlayerStopped(WPARAM wParam, LPARAM lParam);
	// afx_msg OnMPlayerUpdateProgress(WPARAM wParam, LPARAM lParam);
	// afx_msg OnMPlayerUpdateCacheFill(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnMPlayerLog(WPARAM wParam, LPARAM lParam);

	afx_msg void OnAfterplayback(UINT nID);
	afx_msg void OnUpdateAfterplayback(CCmdUI* pCmdUI);


public:
  void SetMPlayerVideoWindow(void);
	// int GetLogoID(void);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	// CStatusBar  m_wndStatusBar;
  CPlayerStatusbar m_wndStatusBar;
	// CToolBar    m_wndToolBar;
  CProgressDlgBar m_wndProgressDlgBar;
  CMyToolBar  m_wndMyToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
	afx_msg void OnPlayPlay();
	afx_msg void OnPlayStop();
	afx_msg void OnPlayPause();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnFileCloseFile();
	afx_msg void OnFileClipproperty();
	afx_msg void OnViewAlwaysontop();
	afx_msg void OnUpdateViewAlwaysontop(CCmdUI* pCmdUI);
	afx_msg void OnViewKeepaspectratio();
	afx_msg void OnUpdateViewKeepaspectratio(CCmdUI* pCmdUI);
	afx_msg void OnViewProgressBar();
	afx_msg void OnUpdateViewProgressBar(CCmdUI* pCmdUI);
	afx_msg void OnVolumeMute();
	afx_msg void OnOptionsPreferences();
	afx_msg void OnViewFullscreen();
	afx_msg void OnPlayRepeat();
	afx_msg void OnUpdatePlayRepeat(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnViewPlaylist();
	afx_msg void OnUpdateViewPlaylist(CCmdUI* pCmdUI);
	afx_msg void OnViewMytoolbar();
	afx_msg void OnUpdateViewMytoolbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlayPlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlayPause(CCmdUI* pCmdUI);
	afx_msg void OnPlayNext();
	afx_msg void OnPlayPrevious();
	afx_msg void OnFileOpenurl();
	afx_msg void OnPlayGoto();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnViewStatusbar();
	afx_msg void OnUpdateViewStatusbar(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHelpHomepage();
	afx_msg void OnViewLog();
	afx_msg void OnUpdateViewLog(CCmdUI* pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPlaySendcommand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A154A451_51C5_4DFF_82E1_137B439B6ED1__INCLUDED_)
