#if !defined(AFX_MPLAYER_H__ACA77059_9806_4137_A0A6_572C37B770B5__INCLUDED_)
#define AFX_MPLAYER_H__ACA77059_9806_4137_A0A6_572C37B770B5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MPlayer.h : header file
//

// MPlayer status
enum MPLAYER_STATUS
{
  MPLAYER_STARTING,
  MPLAYER_PLAYING,
  MPLAYER_STOPPING,
  MPLAYER_STOPPED,
  MPLAYER_PAUSED,
  MPLAYER_ERROR,
};

/////////////////////////////////////////////////////////////////////////////
// CMPlayer window

// CMPlayer is inherited from CStatic, so i can use the TIMER now
class CMPlayer : public CStatic
{
// Construction
public:
	CMPlayer();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPlayer)
	//}}AFX_VIRTUAL
private:

  // essential member variables
  CString m_strCmdLn; // command line
  CString m_strMPlayerPathName; // MPlayer Binary file path name
  // CString m_strMPlayerConfig; // config switch
  CString m_strMPlayerUserConfig; // user additional config
  CString m_strSource;  // source filename, media clip filename
  HWND m_hVideoPanel; // handle of the embedded video panel
  int m_nVideoOutputDriver, m_nAudioOutputDriver;
  BOOL m_bDoubleBuffering;
  BOOL m_bAutoloadSubtitles;
  int m_nMPlayerPriority;
  int m_nSubCP; // Subtitle CodePage
  int m_nPlaybackPosition; // Playback Position (use -ss)
  BOOL m_bAllowSendCmdWhilePaused; // Allow send command while puased ? Support MPlayer2?

  CString m_strSubtitleFont; // Subtitle font pathname

  int m_nVideoBrightness, m_nVideoContrast, m_nVideoHue, m_nVideoSaturation;

  // MPlayer information (general)
  int m_nStatus; // current status, play, stop, pause, ...
  long m_lTimePos; // current time position
  int m_nVolume; // MPlayer volume
  BOOL m_bHaveVideo; // clip have video or not

  float m_fCacheFill; // cache fill

  // MPlayer information, these values will be set when MPlayer.exe is starting
  // via the pipe.
  // MPlayer information (clip information)
  CString m_strClipInfo_Clip;
  CString m_strClipInfo_Author;
  CString m_strClipInfo_Copyright;
  CString m_strClipInfo_Rating;
  long m_lClipInfo_Length;

  // New version
  CString m_strClipInfo_Title;
  CString m_strClipInfo_Artist;
  CString m_strClipInfo_Album;
  CString m_strClipInfo_Genre;

  // MPlayer information (audio information)
  CString m_strAudioInfo_Codec;
  CString m_strAudioInfo_Format;
  long m_lAudioInfo_Bitrate;
  long m_lAudioInfo_Rate;
  int m_nAudioInfo_NCH;

  // MPlayer information (video information)
  CString m_strVideoInfo_Codec;
  long m_lVideoInfo_Bitrate;
  float m_fVideoInfo_FPS;
  int m_nVideoInfo_Width;
  int m_nVideoInfo_Height;
  
  // Command pipe related member variables
  SECURITY_ATTRIBUTES m_saAttr;
  HANDLE m_hReadFromChild;
  HANDLE m_hWriteToParent;
  HANDLE m_hWriteToChild;
  HANDLE m_hReadFromParent;

  // MPlayer process related member variables
  STARTUPINFO m_siStartupInfo;
  PROCESS_INFORMATION m_piProcessInfo;

  // miscelleanous member variables
  int m_nOSMajorVersion; // os major version

  CString m_strMPlayerLog;

  // Trying to avoid flooded by Pipe crap
  BOOL m_bPipeFull; // Pipe is full previously
  int m_nPipeFullCount; // Number of times pipe is full

  int m_nPipeBufferSize;

public:
  int Init(void);

  // interface
  void SetOSMajorVersion(int nOSMajorVersion);
  void SetSource(CString strSource);
  void GetSource(CString &strSource) const;
  void SetMPlayerPathName(CString strMPlayerPathName);
  void GetMPlayerPathName(CString &strMPlayerPathName) const;
  // void SetMPlayerConfig(CString strMPlayerConfig);
  // void GetMPlayerConfig(CString &strMPlayerConfig) const;
  void SetMPlayerUserConfig(CString strMPlayerUserConfig);
  void GetMPlayerUserConfig(CString &strMPlayerUserConfig) const;
  void SetDoubleBuffering(BOOL bDoubleBuffering);
  BOOL GetDoubleBuffering(void) const;
  void SetAutoloadSubtitles(BOOL bAutoloadSubtitles);
  BOOL GetAutoloadSubtitles(void) const;
  void SetMPlayerPriority(int nPriority);
  int  GetMPlayerPriority(void) const;
  void SetSubCP(int nSubCP);
  int  GetSubCP(void) const;
  void SetPlaybackPosition(int nPlaybackPosition);
  void SetAllowSendCmdWhilePaused(BOOL bAllowSendCmdWhenPaused);
  BOOL GetAllowSendCmdWhilePaused(void) const;

  void GetSubtitleFont(CString &strSubtitleFont) const;
  void SetSubtitleFont(CString strSubtitleFont);

  void LogFilter(CString strLog);
  void GetMPlayerLog(CString &strLog) const;

  BOOL CheckEngine(void);

  // essential interface
  void Play(void);
  void Pause(BOOL bPause);
  void Mute(void);
  void Stop(void);
  void SetVolume(int nVolume); // set absolute volume
  int  GetVolume(void); // get absolute volume
  void SetVolumeRelative(int nVolume); // (obsoleted)
  void ReWind(void); // (not in use)

  void SetVideoBrightness(int nBrightness);
  void SetVideoContrast(int nContrast);
  void SetVideoHue(int nHue);
  void SetVideoSaturation(int nSaturation);

  int GetVideoBrightness(void);
  int GetVideoContrast(void);
  int GetVideoHue(void);
  int GetVideoSaturation(void);

  void AutoStop(void); // called after MPlayer process ends
  int GetStatus(void);

  void Reset(void); // when user start play a clip, reset media clip related info

  void RequireTimePos(void); // send a get_time_pos command to MPlayer
  long GetTimePos(void); // get current playing time
  void SeekTime(DWORD dwSeekTime); // seek to an absolute position of <value> seconds.
  void SeekRelativeTime(int nRelativeTime); // seek relative time

  int Command(CString strCommand); // send command to MPlayer via pipe
  int CreateCmdPipe(void); // create the command pipe
  int DestroyCmdPipe(void); // destroy the command pipe
  int CheckActivate(void); // check if MPlayer process is still running

  void SetVideoPanelHandle(HWND hInnerPanel); // set embedded video panel
  void SetVideoOutputDriver(int nVideoOutputDriver);
  int  GetVideoOutputDriver(void) const;
  void SetAudioOutputDriver(int nAudioOutputDriver);
  int  GetAudioOutputDriver(void) const;

  BOOL HaveVideo(void); // return if media clip has video stream

  void MakeupCmdLn(void);
  void AddArgument(CString strArgument);

  // clip information interface (should be const)
  CString GetClipInfo_Clip(void) const;
  CString GetClipInfo_Author(void) const;
  CString GetClipInfo_Copyright(void) const;
  CString GetClipInfo_Rating(void) const;
  long    GetClipInfo_Length(void) const;

  CString GetClipInfo_Title(void) const;
  CString GetClipInfo_Artist(void) const;
  CString GetClipInfo_Album(void) const;
  CString GetClipInfo_Genre(void) const;

  // audio information interface (should be const)
  CString GetAudioInfo_Codec(void) const;
  CString GetAudioInfo_Format(void) const;
  long GetAudioInfo_Bitrate(void) const;
  long GetAudioInfo_Rate(void) const;
  int  GetAudioInfo_NCH(void) const;

  // video information interface (should be const)
  CString GetVideoInfo_Codec(void) const;
  long GetVideoInfo_Bitrate(void);
  float GetVideoInfo_FPS(void) const;
  int GetVideoInfo_Width(void) const;
  int GetVideoInfo_Height(void) const;

  void CalculateVideoBitrate(void);

  void ReadMPlayerOutput(void); // Read MPlayer output via pipe
  void ParseMPlayerOutput(CString strMPlayerOutput); // Parse MPlayer Output
	void ConfirmMPlayerPlaying(int nStatus);

  CString m_strMPlayerOutputOld;

  // void UpdateTimePos(void); // post message to CMainFrame to update timer
	void CheckAutoStop(void); // check if MPlayer is stopped and post message to CMainFrame
	// void UpdateProgress(void); // post message to CMainFrame to update progress
  void CleanUp(void); // cleanup something after playback
  // void UpdateCacheFill(void);
  float GetCacheFill(void);

  // thread related
  static UINT SendCmd(LPVOID p);
  void SendCmd();
  char m_chCmdString[40];
  CWinThread *m_pThreadSendCmd;
  HANDLE m_hEventSendCmdStart, m_hEventSendCmdDone; // m_hEventSendCmdQuit;
  BOOL m_bAllowToSendCmd;
  void GetCmdString(char[]);
  HANDLE GetWriteToChildHandle(void);
  int StartSendCmdThread(void);
  void TerminateSendCmdThread(void);

  // MPlayer Monitor
  static UINT MPlayerMonitor(LPVOID p);
  void MPlayerMonitor();
  CWinThread *m_pThreadMPlayerMonitor;
  HANDLE m_hEventMPlayerMonitorQuit;
  int StartMPlayerMonitorThread(void);
  void TerminateMPlayerMonitorThread(void);
  CTime m_timeLastReadCmd;
  BOOL m_bEnableMPlayerMonitor;
  void SetEnableMPlayerMonitor(BOOL bEnableMPlayerMonitor);
  BOOL GetEnableMPlayerMonitor(void) const;
  int m_nMPlayerMonitorThreshold;
  void SetMPlayerMonitorThreshold(int nMPlayerMonitorThreshold);
  int GetMPlayerMonitorThreshold(void) const;

  // Logging
  BOOL m_bEnableLogging;
  void SetEnableLogging(BOOL bEnableLogging);
  BOOL GetEnableLogging(void) const;
  // Argument "-volume"
  BOOL m_bEnableArgumentVolume;
  void SetEnableArgumentVolume(BOOL bEnableArgumentVolume);
  BOOL GetEnableArgumentVolume(void) const;

  void SetPipeBufferSize(int nPipeBufferSize);

// Implementation
public:
	virtual ~CMPlayer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMPlayer)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPLAYER_H__ACA77059_9806_4137_A0A6_572C37B770B5__INCLUDED_)
