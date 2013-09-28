// MPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "MPlayer.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// TIMER
#define TIMER_HALF_SECOND          1
#define TIMER_ONE_SECOND           2
// #define TIMER_FULLSCREENMOUSEHIDER 3
#define TIMER_MPLAYER_STARTING     4
// #define TIMER_EIGHT_SECOND         5


#define MAX_VIDEO_WIDTH  9999
#define MAX_VIDEO_HEIGHT 9999


/////////////////////////////////////////////////////////////////////////////
// CMPlayer

BEGIN_MESSAGE_MAP(CMPlayer, CStatic)
	//{{AFX_MSG_MAP(CMPlayer)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPlayer message handlers

// Construction of CMPlayer class
CMPlayer::CMPlayer()
{
  Init();
}

// Deconstruction of CMPlayer class
CMPlayer::~CMPlayer()
{
  Stop();

  TerminateThread(m_piProcessInfo.hThread, 0);
  TerminateProcess(m_piProcessInfo.hProcess, 0);

  DestroyCmdPipe();

  // Do not call CleanUp() here, it will call KillTimer() which will cause
  // an exception in debug version
  // CleanUp();
  TerminateSendCmdThread();
  TerminateMPlayerMonitorThread();

  // TerminateSendCmdThread();
  // will cause vc debugger rise a
  // First-chance exception in MPlayerGUI.exe (NTDLL.DLL): 0xC0000008: (no name).
  // ::CloseHandle(m_piProcessInfo.hThread);
  // ::CloseHandle(m_piProcessInfo.hProcess);
}

// Initialization code (run once) for CMPlayer class
int CMPlayer::Init(void)
{
  m_nOSMajorVersion = 0; // os major version
  m_strMPlayerPathName = ""; // path name
  // m_strMPlayerConfig = ""; // config switch
  m_strMPlayerUserConfig = ""; // user additional config
  m_strSource = ""; // source file name, for play
  m_strCmdLn = ""; // command line

  m_bAllowSendCmdWhilePaused = FALSE;

  m_strMPlayerOutputOld = ""; // for compare

  SetVideoOutputDriver(0);
  SetAudioOutputDriver(0);
  SetVideoBrightness(0);
  SetVideoContrast(0);
  SetVideoSaturation(0);
  SetVideoHue(0);
  SetDoubleBuffering(FALSE);
  SetAutoloadSubtitles(FALSE);
  SetMPlayerPriority(2); // normal priority
  SetSubtitleFont("");
  SetSubCP(0);
  SetPlaybackPosition(0);
  SetPipeBufferSize(8192);

  m_hReadFromChild = NULL;
  m_hWriteToParent = NULL;
  m_hWriteToChild = NULL;
  m_hReadFromParent = NULL;

  m_nStatus = MPLAYER_STOPPED; // current status, play, stop, pause, ...
  // m_hMPlayerProcess = NULL; // handle of MPlayer process
  m_hVideoPanel = NULL;
  m_nVolume = 100; // full volume

  m_pThreadSendCmd = NULL;
  m_pThreadMPlayerMonitor = NULL;

  m_bEnableMPlayerMonitor = TRUE;
  SetMPlayerMonitorThreshold(10);
  m_bEnableLogging = FALSE;
  m_bEnableArgumentVolume = FALSE;

  Reset();

  return 1;
}


void CMPlayer::SetMPlayerMonitorThreshold(int nMPlayerMonitorThreshold)
{
  if (nMPlayerMonitorThreshold > 0)
  {
    m_nMPlayerMonitorThreshold = nMPlayerMonitorThreshold;
  }
}

int CMPlayer::GetMPlayerMonitorThreshold(void) const
{
  return m_nMPlayerMonitorThreshold;
}


// Set the embedded video window handle (see MPlayer doc: slave.txt)
// Parameters:
//  [in]  HWND : handle of the video panel window
void CMPlayer::SetVideoPanelHandle(HWND hVideoPanel)
{
  m_hVideoPanel = hVideoPanel;
}

// Set MPlayer video output driver paramter
// Parameters:
//  [in] int : video output driver id number
void CMPlayer::SetVideoOutputDriver(int nVideoOutputDriver)
{
  m_nVideoOutputDriver = nVideoOutputDriver;
}

int CMPlayer::GetVideoOutputDriver(void) const
{
  return m_nVideoOutputDriver;
}

// Set MPlayer audio output driver parameter
// Parameters:
//  [in] int : audio output driver id number
void CMPlayer::SetAudioOutputDriver(int nAudioOutputDriver)
{
  m_nAudioOutputDriver = nAudioOutputDriver;
}

int CMPlayer::GetAudioOutputDriver(void) const
{
  return m_nAudioOutputDriver;
}

void CMPlayer::SetDoubleBuffering(BOOL bDoubleBuffering)
{
  m_bDoubleBuffering = bDoubleBuffering;
}

BOOL CMPlayer::GetDoubleBuffering(void) const
{
  return m_bDoubleBuffering;
}

void CMPlayer::SetAutoloadSubtitles(BOOL bAutoloadSubtitles)
{
  m_bAutoloadSubtitles = bAutoloadSubtitles;
}

BOOL CMPlayer::GetAutoloadSubtitles(void) const
{
  return m_bAutoloadSubtitles;
}

void CMPlayer::SetSubCP(int nSubCP)
{
  if ((nSubCP >= 0) && (nSubCP <= 24))
  {
    m_nSubCP = nSubCP;
  }
  else
  {
    m_nSubCP = 0;
  }
}

int CMPlayer::GetSubCP(void) const
{
  return m_nSubCP;
}

void CMPlayer::SetPlaybackPosition(int nPlaybackPosition)
{
  m_nPlaybackPosition = nPlaybackPosition;
}

void CMPlayer::SetMPlayerPriority(int nPriority)
{
  if ((nPriority >= 0) && (nPriority <= 5))
  {
    m_nMPlayerPriority = nPriority;
  }
  else
  {
    m_nMPlayerPriority = 2; // normal
  }
}

void CMPlayer::SetVideoBrightness(int nBrightness)
{
  if ((nBrightness < -100) || (nBrightness > 100))
    m_nVideoBrightness = 0;
  else
    m_nVideoBrightness = nBrightness;
}

void CMPlayer::SetVideoHue(int nHue)
{
  if ((nHue < -100) || (nHue > 100))
    m_nVideoHue = 0;
  else
    m_nVideoHue = nHue;
}

void CMPlayer::SetVideoContrast(int nContrast)
{
  if ((nContrast < -100) || (nContrast > 100))
    m_nVideoContrast = 0;
  else
    m_nVideoContrast = nContrast;
}

void CMPlayer::SetVideoSaturation(int nSaturation)
{
  if ((nSaturation < -100) || (nSaturation > 100))
    m_nVideoSaturation = 0;
  else
    m_nVideoSaturation = nSaturation;
}

int CMPlayer::GetVideoBrightness(void)
{
  return m_nVideoBrightness;
}

int CMPlayer::GetVideoContrast(void)
{
  return m_nVideoContrast;
}

int CMPlayer::GetVideoHue(void)
{
  return m_nVideoHue;
}

int CMPlayer::GetVideoSaturation(void)
{
  return m_nVideoSaturation;
}


int CMPlayer::GetMPlayerPriority(void) const
{
  return m_nMPlayerPriority;
}

// Set the operating system major version number
// so i can determine to send pipe command or not
// Parameters:
//  [in]  int : operating system major version number
void CMPlayer::SetOSMajorVersion(int nOSMajorVersion)
{
  m_nOSMajorVersion = nOSMajorVersion;
}

// Reset some member variables, called before start playing everytime
void CMPlayer::Reset(void)
{
  m_lTimePos = 0;
  // m_nVolume = 100;
  m_bHaveVideo = TRUE;

  m_fCacheFill = 0;

  // Clip information (MP3 ID3 or something)
  m_strClipInfo_Clip = "-";
  m_strClipInfo_Author = "-";
  m_strClipInfo_Copyright = "-";
  m_strClipInfo_Rating = "-";
  m_lClipInfo_Length = 0;

  m_strClipInfo_Title = "-";
  m_strClipInfo_Artist = "-";
  m_strClipInfo_Album = "-";
  m_strClipInfo_Genre = "-";

  // Audio information
  m_strAudioInfo_Codec = "";
  m_strAudioInfo_Format = "";
  m_lAudioInfo_Bitrate = 0;
  m_lAudioInfo_Rate = 0;
  m_nAudioInfo_NCH = 0;

  // Video information
  m_strVideoInfo_Codec = "";
  m_lVideoInfo_Bitrate = 0;
  m_fVideoInfo_FPS = 0.0;
  m_nVideoInfo_Width = 320;
  m_nVideoInfo_Height = 240;

  strcpy(m_chCmdString, "");
  m_bAllowToSendCmd = TRUE;

  // We must GetCurrentTimer here, or the MPlayerMonitor will call Stop() immediately
  m_timeLastReadCmd = CTime::GetCurrentTime();

  m_bPipeFull = FALSE;
  m_nPipeFullCount = 0;
}

// Set the source (media clip filename) for CMPlayer
// Parameters:
//  [in]  CString : source path name
void CMPlayer::SetSource(CString strSource)
{
  m_strSource = strSource;
}

// Get the source (media filename) of CMPlayer
// Parameters:
//  [out] CString & : source path name
void CMPlayer::GetSource(CString &strSource) const
{
  strSource = m_strSource;
}

// Set MPlayer Binary file path name
void CMPlayer::SetMPlayerPathName(CString strMPlayerPathName)
{
  m_strMPlayerPathName = strMPlayerPathName;
}

// Get MPlayer Binary file path name
void CMPlayer::GetMPlayerPathName(CString &strMPlayerPathName) const
{
  strMPlayerPathName = m_strMPlayerPathName;
}

// Set MPlayer startup parameter (config)
// Parameters:
//  [in]  CString : MPlayer startup parameter
// void CMPlayer::SetMPlayerConfig(CString strMPlayerConfig)
// {
//   m_strMPlayerConfig = strMPlayerConfig;
// }

// Set MPlayer User Specified startup parameters
// Paramters:
//  [in] CString : User specified additional MPlayer startup parameters
void CMPlayer::SetMPlayerUserConfig(CString strMPlayerUserConfig)
{
  m_strMPlayerUserConfig = strMPlayerUserConfig;
}

// Get MPlayer startup parameter (config)
// Parameters:
//  [out] CString & : MPlayer startup parameter
// void CMPlayer::GetMPlayerConfig(CString &strMPlayerConfig) const
// {
//   strMPlayerConfig = m_strMPlayerConfig;
// }

// Get MPlayer User Specified startup parameters
// Parameters:
//  [out] CString & : User specified additional MPlayer startup paramters
void CMPlayer::GetMPlayerUserConfig(CString &strMPlayerUserConfig) const
{
  strMPlayerUserConfig = m_strMPlayerUserConfig;
}

void CMPlayer::GetSubtitleFont(CString &strSubtitleFont) const
{
  strSubtitleFont = m_strSubtitleFont;
}

void CMPlayer::SetSubtitleFont(CString strSubtitleFont)
{
  m_strSubtitleFont = strSubtitleFont;
}


// Check if MPlayer binary file exist
BOOL CMPlayer::CheckEngine(void)
{
  CFileFind fFind;
  CString strMPlayerBinaryFile;

  strMPlayerBinaryFile = m_strMPlayerPathName;

  if (!fFind.FindFile(strMPlayerBinaryFile))
  {
    return FALSE;
  }

  return TRUE;
}

// Create the command pipe, to communite with MPlayer process
// Return values:
//  int : non-zero means sucess, zero means failure or already created
int CMPlayer::CreateCmdPipe(void)
{
  if (m_hReadFromChild != NULL)
  {
    // already created
    return 0;
  }

  // create pipe

  // The SECURITY_ATTRIBUTES is used to create inheritable handles
  // the last member of the structure is set to TRUE so that the handle
  // will be inheritable.
  m_saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  m_saAttr.lpSecurityDescriptor = NULL;
  m_saAttr.bInheritHandle = TRUE;

  HANDLE hReadFromChild;
  // The CreatePipe operation creates a single unidirectional anonymous pipe,
  // and returns handles to its read and write ends. They are, by the
  // SECURITY_ATTRIBUTES, inheritable handles.
  if (!::CreatePipe(&hReadFromChild, &m_hWriteToParent, &m_saAttr, m_nPipeBufferSize))
  {
    // pipe failed
    return 0;
  }

  if (!::DuplicateHandle(::GetCurrentProcess(),
                         hReadFromChild,
                         ::GetCurrentProcess(),
                         &m_hReadFromChild,
                         0,
                         TRUE,
                         DUPLICATE_SAME_ACCESS))
  {
    // duplicate failed
    ::CloseHandle(hReadFromChild);
    ::CloseHandle(m_hWriteToParent);
    return 0;
  }
  ::CloseHandle(hReadFromChild);

  HANDLE hWriteToChild;
  if (!::CreatePipe(&m_hReadFromParent, &hWriteToChild, &m_saAttr, 0))
  {
    // pipe failed
    return 0;
  }

  if (!::DuplicateHandle(::GetCurrentProcess(),
                         hWriteToChild,
                         ::GetCurrentProcess(),
                         &m_hWriteToChild,
                         0,
                         TRUE,
                         DUPLICATE_SAME_ACCESS))
  {
    ::CloseHandle(m_hReadFromParent);
    ::CloseHandle(hWriteToChild);
    return 0;
  }
  ::CloseHandle(hWriteToChild);


  return 1;
}

HANDLE CMPlayer::GetWriteToChildHandle(void)
{
  return m_hWriteToChild;
}

// Destroy the command pipe
// Return values:
//  int : -1 means no command pipe to be destroyed
//         0 means sucess
int CMPlayer::DestroyCmdPipe(void)
{
  if (m_hReadFromChild == NULL)
  {
    return -1;
  }

  // also will cause VC debugger rise an exception
  // ::CloseHandle(m_hReadFromChild);
  // ::CloseHandle(m_hWriteToParent);
  // ::CloseHandle(m_hWriteToChild);
  // ::CloseHandle(m_hReadFromParent);

  m_hReadFromChild = NULL;
  m_hWriteToParent = NULL;
  m_hWriteToChild = NULL;
  m_hReadFromParent = NULL;

  return 0;
}

// Send command to MPlayer process by using pipe
// Parameters:
//  [in]  CString : command
// Return values:
//  int : 0 means successed
//        -1 means failed
int CMPlayer::Command(CString strCommand)
{
  // If we are not running Windows 2000 (or above), return immediately
  if (m_nOSMajorVersion < 5)
  {
    return -1;
  }

  if (m_hWriteToChild == NULL)
  {
    return -1;
  }

  // return if MPlayer is not running
  if (CheckActivate() != 0)
  {
    return -1;
  }

  strCommand = strCommand + "\n";

  if ((m_nStatus == MPLAYER_PAUSED) && (!m_bAllowSendCmdWhilePaused))
  {
    if ((strCommand.Find("pause") != 0) && (strCommand.Find("quit") != 0))
    {
      return -1; // For MPlayer 1 engine, don't send command while paused, unless going to resume it or stop it on purpose
    }
  }

  if (WaitForSingleObject(m_hEventSendCmdDone, 0) == WAIT_OBJECT_0)
  {
    m_bAllowToSendCmd = TRUE;
  }

  if (m_bAllowToSendCmd)
  {
    m_bAllowToSendCmd = FALSE;

    // limit to 39 characters maximum
    strncpy(m_chCmdString, (LPSTR)(LPCTSTR)strCommand, 39);
    m_chCmdString[39] = '\x0';

    SetEvent(m_hEventSendCmdStart);
    // Inform Main Window that we are writing the pipe
    // AfxGetApp()->m_pMainWnd->PostMessage(UWM_MPLAYER_INDICATORWRITEPIPE, 0, 0);
  }

  return 0;
}

// for SendCmd Thread to get member variable: m_chCmdString
void CMPlayer::GetCmdString(char chCmdString[])
{
  strncpy(chCmdString, m_chCmdString, 39);
  chCmdString[39] = '\x0';
}

// Starting play back, create MPlayer.exe process, set MPLAYER_STARTING state
void CMPlayer::Play(void)
{
  if (m_nStatus != MPLAYER_STOPPED)
  {
    return;
  }

  if (CreateCmdPipe() != 1)
  {
    return;
  }

  Reset();

  if (StartSendCmdThread() != 1)
  {
    return;
  }

  if (m_bEnableMPlayerMonitor)
  {
    // Start MPlayerMonitor Thread
    if (StartMPlayerMonitorThread() != 1)
    {
      return;
    }
  }

  // MPlayer process return code
  int nReturnCode = 0;

  memset(&m_piProcessInfo, 0, sizeof(m_piProcessInfo));
  memset(&m_siStartupInfo, 0, sizeof(m_siStartupInfo));

  m_siStartupInfo.cb = sizeof(m_siStartupInfo);
  m_siStartupInfo.hStdError = m_hWriteToParent;
  m_siStartupInfo.hStdOutput = m_hWriteToParent;
  m_siStartupInfo.hStdInput = m_hReadFromParent;
  m_siStartupInfo.wShowWindow = SW_HIDE;
  m_siStartupInfo.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

  // Makeup Command Line
  MakeupCmdLn();

  CString strTmp;
  strTmp.Format("Pipe buffer size: %ld byte(s)", m_nPipeBufferSize);
  if (m_bEnableLogging)
  {
    LogFilter(m_strCmdLn);
    LogFilter(strTmp);
  }

  // We need a writeable buffer for the command (silly Windows restriction)
  LPTSTR cmd = m_strCmdLn.GetBuffer(m_strCmdLn.GetLength() + 1);
  BOOL bStarted;
  bStarted = ::CreateProcess(NULL,                                // command is part of input string
                             cmd,                                 // (writeable) command string
                             NULL,                                // process security
                             NULL,                                // thread security
                             TRUE,                                // inherit handles flag
                             CREATE_NO_WINDOW | DETACHED_PROCESS | CREATE_SUSPENDED, // flags
                             NULL,                                // inherit environment
                             NULL,                                // inherit directory
                             &m_siStartupInfo,                    // STARTUPINFO
                             &m_piProcessInfo);                   // PROCESS_INFORMATION
  m_strCmdLn.ReleaseBuffer();

  // ::CloseHandle(m_piProcessInfo.hThread); // ?

  if (bStarted)
  {
    // AfxMessageBox("successfully created");

    // Now close the output pipes so we get true EOF/broken pipe
    ::CloseHandle(m_hWriteToParent);
    ::CloseHandle(m_hReadFromParent);
    
    // m_hMPlayerProcess = pi.hProcess;
    /* causes MPlayer.exe failed to start on Win9x randomly
    if (!WaitForInputIdle(m_piProcessInfo.hProcess, 5000))
    {
      // send messages
      // SetThreadPriority(m_piProcessInfo.hThread, THREAD_PRIORITY_ABOVE_NORMAL);
    }
    */
    // cheating, so GetMPlayerStartupInfo() can get result
    // m_nStatus = MPLAYER_PLAYING;
    // get MPlayer startup information
    // nReturnCode = GetMPlayerStartupInfo();
    //  1 MPlayer started :)
    // -1 MPlayer exited, failed to start :(
    // -2 MPlayer interrupted ?
    // -3 MPlayer is too slow, no responce :(

    // Set MPLAYER_STARTING state
		m_nStatus = MPLAYER_STARTING;
    ResumeThread(m_piProcessInfo.hThread);
		// Start timer, read MPlayer.exe output via pipe in OnTimer()
		SetTimer(TIMER_MPLAYER_STARTING, 200, NULL);
		// Post a message to mainframe
    AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_STARTING, 0, 0);
  }
  else
  {
    // Failed to start
    DestroyCmdPipe();
    // Stop timer, terminate thread
    CleanUp();
    AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_FAILEDTOSTART, 0, 0);
  }
}

void CMPlayer::AddArgument(CString strArgument)
{
  m_strCmdLn += strArgument;
  m_strCmdLn += _T(" ");
}

void CMPlayer::MakeupCmdLn(void)
{
  CString strTemp;

  // Initialization
  m_strCmdLn = _T("");

  // MPlayer Exe Pathname
  strTemp.Format("\"%s\"", m_strMPlayerPathName);
  AddArgument(strTemp);

  // Video Panel Handler
  strTemp.Format("-wid %d", m_hVideoPanel);
  AddArgument(strTemp);

  // MPlayer Process Priority
  switch (m_nMPlayerPriority)
  {
  case 0:
    AddArgument(_T("-priority idle"));
    break;
  case 1:
    AddArgument(_T("-priority belownormal"));
    break;
  case 2:
    AddArgument(_T("-priority normal"));
    break;
  case 3:
    AddArgument(_T("-priority abovenormal"));
    break;
  case 4:
    AddArgument(_T("-priority high"));
    break;
  case 5:
    AddArgument(_T("-priority realtime"));
    break;
  default:
    AddArgument(_T("-priority normal"));
    break;
  }

  // These are must have config settings
  // m_strMPlayerConfig = _T("-quiet -slave -identify -colorkey 0x000012");
  AddArgument(_T("-quiet"));
  AddArgument(_T("-slave"));
  AddArgument(_T("-identify"));
  AddArgument(_T("-colorkey 0x000012"));

  // Double Buffering
  if (m_bDoubleBuffering)
  {
    AddArgument(_T("-double"));
  }
  else
  {
    AddArgument(_T("-nodouble"));
  }

  // Autoload Subtitles
  if (m_bAutoloadSubtitles)
  {
    AddArgument(_T("-autosub"));
  }
  else
  {
    AddArgument(_T("-noautosub"));
  }

  // Subtitle Font
  if (m_bAutoloadSubtitles)
  {
    strTemp.Format("-font \"%s\"", _T(m_strSubtitleFont));
    AddArgument(strTemp);
  }

  // Subtitle CodePage (Encoding)
  switch (m_nSubCP)
  {
  case 1:
    AddArgument(_T("-subcp Unicode"));
    break;
  case 2:
    AddArgument(_T("-subcp UTF-8"));
    break;
  case 3:
    AddArgument(_T("-subcp ISO-8859-1"));
    break;
  case 4:
    AddArgument(_T("-subcp ISO-8859-15"));
    break;
  case 5:
    AddArgument(_T("-subcp ISO-8859-2"));
    break;
  case 6:
    AddArgument(_T("-subcp ISO-8859-3"));
    break;
  case 7:
    AddArgument(_T("-subcp ISO-8859-4"));
    break;
  case 8:
    AddArgument(_T("-subcp ISO-8859-5"));
    break;
  case 9:
    AddArgument(_T("-subcp ISO-8859-6"));
    break;
  case 10:
    AddArgument(_T("-subcp ISO-8859-7"));
    break;
  case 11:
    AddArgument(_T("-subcp ISO-8859-9"));
    break;
  case 12:
    AddArgument(_T("-subcp ISO-8859-13"));
    break;
  case 13:
    AddArgument(_T("-subcp ISO-8859-14"));
    break;
  case 14:
    AddArgument(_T("-subcp ISO-8859-8"));
    break;
  case 15:
    AddArgument(_T("-subcp KOI8-R"));
    break;
  case 16:
    AddArgument(_T("-subcp KOI8-U/RU"));
    break;
  case 17:
    AddArgument(_T("-subcp CP936"));
    break;
  case 18:
    AddArgument(_T("-subcp BIG5"));
    break;
  case 19:
    AddArgument(_T("-subcp SHIFT-JIS"));
    break;
  case 20:
    AddArgument(_T("-subcp CP949"));
    break;
  case 21:
    AddArgument(_T("-subcp CP874"));
    break;
  case 22:
    AddArgument(_T("-subcp CP1251"));
    break;
  case 23:
    AddArgument(_T("-subcp CP1250"));
    break;
  case 24:
    AddArgument(_T("-subcp CP1256"));
    break;
  case 0:
  default:
    break;
  }

  // Playback Position
  if (m_nPlaybackPosition > 0)
  {
    strTemp.Format("-ss %d", m_nPlaybackPosition);
    AddArgument(strTemp);
  }

  // Video Output Driver
  switch (m_nVideoOutputDriver)
  {
  case 1:
    AddArgument(_T("-vo null"));
    break;
  case 2:
    AddArgument(_T("-vo directx"));
    break;
  case 3:
    AddArgument(_T("-vo directx:noaccel"));
    break;
  case 4:
    AddArgument(_T("-vo gl"));
    break;
  case 5:
    AddArgument(_T("-vo gl2"));
    break;
  case 6:
    AddArgument(_T("-vo direct3d"));
    break;
  case 0:
  default:
    AddArgument(_T("-novideo"));
    break;
  }

  // Audio Output Driver
  switch (m_nAudioOutputDriver)
  {
  case 1:
    AddArgument(_T("-ao null"));
    break;
  case 2:
    AddArgument(_T("-ao dsound"));
    break;
  case 3:
    AddArgument(_T("-ao win32"));
    break;
  case 0:
  default:
    AddArgument(_T("-nosound"));
    break;
  }

  // Video Brightness
  if (m_nVideoBrightness != 0)
  {
    strTemp.Format("-brightness %d", m_nVideoBrightness);
    AddArgument(strTemp);
  }

  // Video Contrast
  if (m_nVideoContrast != 0)
  {
    strTemp.Format("-contrast %d", m_nVideoContrast);
    AddArgument(strTemp);
  }

  // Video Hue
  if (m_nVideoHue != 0)
  {
    strTemp.Format("-hue %d", m_nVideoHue);
    AddArgument(strTemp);
  }

  // Video Saturation
  if (m_nVideoSaturation != 0)
  {
    strTemp.Format("-saturation %d", m_nVideoSaturation);
    AddArgument(strTemp);
  }

  if (m_bEnableArgumentVolume)
  {
    // Startup Volume
    if (m_nVolume != 100)
    {
      strTemp.Format("-volume %d", m_nVolume);
      AddArgument(strTemp);
    }
  }

  // User Config
  AddArgument(m_strMPlayerUserConfig);

  // Source (Clip to be play)
  strTemp.Format("\"%s\"", _T(m_strSource));
  AddArgument(strTemp);

  // Debug
  // TRACE("MPlayer CmdLn: %s\n", m_strCmdLn);
}


// After get enough info in OnTimer() -> GetMPlayerStartupInfo(), confirm MPlayer
// is actually started or just failed 
void CMPlayer::ConfirmMPlayerPlaying(int nStatus)
{
  // MPlayer is actually started
  if (nStatus == 1)
	{
    if (CheckActivate() == 0)
	  {
		  // Stop the needless timer
		  KillTimer(TIMER_MPLAYER_STARTING);
			// Start the routine timer
			SetTimer(TIMER_HALF_SECOND, 500, NULL);
      SetTimer(TIMER_ONE_SECOND, 1000, NULL);
      // SetTimer(TIMER_EIGHT_SECOND, 8000, NULL);

	    m_nStatus = MPLAYER_PLAYING;
			AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_STARTPLAYING, 0, 0);
  	}
	}

	// MPlayer failed to start (various reasons)
	if ((nStatus == -1) || (nStatus == -2) || (nStatus == -5))
	{
	  // if (CheckActivate() != 0) // stop MPlayer.exe anyway, or get crash here
		{
      KillTimer(TIMER_MPLAYER_STARTING); // stop the needless timer
		  // Cheating...
      m_nStatus = MPLAYER_PLAYING;
      // Called to cleanup
      AutoStop();
		  m_nStatus = MPLAYER_STOPPED;
			AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_FAILEDTOSTART, 0, 0);
		}
	}
}

// Pause/Resume the playback
// Parameters:
//  [in]  BOOL : TRUE pause, FALSE resume
void CMPlayer::Pause(BOOL bPause)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
  {
    if (bPause == TRUE)
    {
      Command("pause");
      m_nStatus = MPLAYER_PAUSED;
    }
    else
    {
      Command("pause");
      m_nStatus = MPLAYER_PLAYING;
    }
  }
}

// Rewind to the beginning of the playing file
void CMPlayer::ReWind(void)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
  {
    Command("seek 0 2");
  }
}

// Mute/Unmute the MPlayer
void CMPlayer::Mute(void)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
  {
    Command("mute");
  }
}

// Stop the playback, abort the starting up
void CMPlayer::Stop(void)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED) || (m_nStatus == MPLAYER_STARTING))
  {
    CWaitCursor wait;

    int nCounter;
    BOOL bCheckMPlayerQuit;

    if (m_nOSMajorVersion < 5) // Below Windows 2000
    {
      bCheckMPlayerQuit = FALSE; // Needless to check MPlayer output, because there is no ouput
      Sleep(200); // Wait a little bit
    }
    else
    {
      bCheckMPlayerQuit = TRUE; // Check MPlayer output
    }

    nCounter = 0;

    // Check MPlayer quit message can avoid noise when TerminateProcess
    while (bCheckMPlayerQuit)
    {
      Command("quit");
      Sleep(100);
      nCounter++;

      // ParseMPlayerOutput will set m_nStatus...
      if (m_nStatus == MPLAYER_STOPPED)
      {
        break;
      }

      // Return if MPlayer is not running
      if (CheckActivate() != 0)
      {
        break;
      }

      // 50 for 5 seconds
      if (nCounter > 50)
      {
        // Waited too long, and nothing can be read, stop it
        break;
      }
    }

    TerminateThread(m_piProcessInfo.hThread, 0);
    TerminateProcess(m_piProcessInfo.hProcess, 0);
    // ExitProcess(m_piProcessInfo.hProcess);

    DestroyCmdPipe();
		CleanUp();

    AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_STOPPED, 0, 0);
    m_nStatus = MPLAYER_STOPPED;
  }
}

// Terminate MPlayer process, destroy command pipe
//  Called when MPlayer is terminated itself (usually the end of play)
void CMPlayer::AutoStop(void)
{
  if (m_nStatus == MPLAYER_PLAYING)
  {
    TerminateThread(m_piProcessInfo.hThread, 0);
    TerminateProcess(m_piProcessInfo.hProcess, 0);
    // ExitProcess(m_piProcessInfo.hProcess);

    DestroyCmdPipe();
		CleanUp();

    m_nStatus = MPLAYER_STOPPED;
  }
}

// Set absolute volume
// Parameters:
//  [in]  int : volume to be set
void CMPlayer::SetVolume(int nVolume)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED) || (m_nStatus == MPLAYER_STOPPED) || (m_nStatus == MPLAYER_STARTING))
  {
    CString strVolume;

    if ((nVolume < 0) || (nVolume > 100))
    {
      nVolume = 100;
    }

    m_nVolume = nVolume; // save

    if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
    {
      strVolume.Format("volume %d 1", nVolume);
      Command(strVolume);
    }
  }
}

// Get current absolute volume
// Return values:
//  int : current absolute volume
int CMPlayer::GetVolume(void)
{
  return m_nVolume;
}

// Set relative volume
// Parameters:
//  [in]  int : higher or lower the volume
void CMPlayer::SetVolumeRelative(int nVolume)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
  {
    int i;

    if (nVolume > 0)
    {
      for (i = 0; i < 10; i++)
      {
        Command("volume 1");
      }
    }
    else
    {
      for (i = 0; i < 10; i++)
      {
        Command("volume -1");
      }
    }
  }
}

// Seek to an absolute time position
// Parameters:
//  [in]  DWORD : time position to be seek
void CMPlayer::SeekTime(DWORD dwSeekTime)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
  {
    CString strSeek;

    strSeek.Format("seek %ul 2", dwSeekTime);
    Command(strSeek);
  }
}

// Seek relative time
// Parameters:
//  [in]  int : relative time position
//  [out] 
void CMPlayer::SeekRelativeTime(int nRelativeTime)
{
  if ((m_nStatus == MPLAYER_PLAYING) || (m_nStatus == MPLAYER_PAUSED))
  {
    CString strSeek;

    strSeek.Format("seek %d 0", nRelativeTime);
    Command(strSeek);
  }
}

// Get current MPlayer status
// Return values:
//  int : one of the MPlayer's status (ie: MPLAYER_PLAYING, MPLAYER_STOPPED)
int CMPlayer::GetStatus(void)
{
  return m_nStatus;
}

// Read MPlayer's output via pipe and call ParseMPlayerOutput()
void CMPlayer::ReadMPlayerOutput(void)
{
  DWORD lBytesRemain;
  DWORD nRead;
  DWORD i;
  char chTestBuffer[100], chBuffer[5];
  CString strMPlayerOutput;
  int nCounter;

  // while (TRUE)
  for (nCounter = 0; nCounter < 100; nCounter++) // Avoid 100% CPU
  {
    // Return if Pipe not available
    if (m_hReadFromChild == NULL)
    {
      break;
    }

    // Return if MPlayer is not running
    if (CheckActivate() != 0)
    {
      if (m_nStatus == MPLAYER_STARTING) // At STARTING period, MPlayer process is terminated already
      {
        ConfirmMPlayerPlaying(-5); // MPlayer failed to start
      }
      break;
    }

    strMPlayerOutput = "";

    PeekNamedPipe(m_hReadFromChild, chTestBuffer, 80, &lBytesRemain, 0, 0);
    m_timeLastReadCmd = CTime::GetCurrentTime();

    // Only call ReadFile() if lBytesRemain is in range
    if ((lBytesRemain > 0) && (lBytesRemain < 100))
    {
      // Detect Pipe Fulled how many times in a row
      if (lBytesRemain >= 80)
      {
        if (m_bPipeFull)
        {
          m_nPipeFullCount++;

          if (m_nPipeFullCount >= 500)
          {
            Stop();
            break;
          }

          /*
          CString strPipeFullCount;
          strPipeFullCount.Format("PipeFullCount: %d", m_nPipeFullCount);
          LogFilter(strPipeFullCount);
          */
        }
        m_bPipeFull = TRUE;
      }
      else
      {
        m_bPipeFull = FALSE;
        m_nPipeFullCount = 0;
      }


      strMPlayerOutput = "";

      for (i = 0; i < lBytesRemain; i++)
      {
        chBuffer[0] = '\x0';
        ReadFile(m_hReadFromChild, chBuffer, 1, &nRead, NULL);

        if ((chBuffer[0] == '\n') || (chBuffer[0] == '\r')) // newline, return
        {
          break;
        }

        strMPlayerOutput = strMPlayerOutput + chBuffer[0];
      }

      strMPlayerOutput.TrimRight();

      if (strMPlayerOutput.GetLength() > 0)
      {
        // Process only if necessary...
        if (m_strMPlayerOutputOld != strMPlayerOutput)
        {
          m_strMPlayerOutputOld = strMPlayerOutput;

          // Parse it...
          ParseMPlayerOutput(strMPlayerOutput);
          // Log it...
          if (m_bEnableLogging)
          {
            LogFilter(strMPlayerOutput);
          }
        }
      }
    }
    else
    {
      break;
    }

    Sleep(0);
  } // while (TRUE)
}

// Parse MPlayer output and store information to member variables
void CMPlayer::ParseMPlayerOutput(CString strMPlayerOutput)
{
  if (strMPlayerOutput.Find("ANS_TIME_POSITION") != -1)
  {
    long lTimePos;

    if (strMPlayerOutput.GetLength() > 18)
      strMPlayerOutput = strMPlayerOutput.Mid(18); // To avoid assertion error: strex.cpp line 332
    sscanf(strMPlayerOutput, "%ld", &lTimePos);

    // Only update m_lTimePos when legal (in range)
    if (lTimePos >= 0) // && (lTimePos <= m_lClipInfo_Length))
    {
      // m_lTimePos = lTimePos;
      // Plus one second to compensate slow update
      m_lTimePos = lTimePos + 1;
    }

    // hard limit (99:59:59)
    if (m_lTimePos >= 359999L)
    {
      m_lTimePos = 359999L;
    }

    return;
  }

  // Parse only when MPlayer is starting up...
  if (m_nStatus == MPLAYER_STARTING)
  {
    // Cache fill: 12.50% (131072 bytes)
    if (strMPlayerOutput.Find("Cache fill:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 12)
        strMPlayerOutput = strMPlayerOutput.Mid(12); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%f", &m_fCacheFill);

      if (m_fCacheFill > 100)
      {
        m_fCacheFill = 100;
      }

      return;
    }

    // Check if no video
    if (strMPlayerOutput.Find("Video: no video") != -1)
    {
      m_bHaveVideo = FALSE;
      return;
    }

    if (strMPlayerOutput.Find("ID_CLIP_INFO_name") != -1)
    {
      if (strMPlayerOutput.GetLength() > 18)
        m_strClipInfo_Clip = strMPlayerOutput.Mid(18); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find("ID_CLIP_INFO_author") != -1)
    {
      if (strMPlayerOutput.GetLength() > 20)
        m_strClipInfo_Author = strMPlayerOutput.Mid(20); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find("ID_CLIP_INFO_copyright") != -1)
    {
      if (strMPlayerOutput.GetLength() > 23)
        m_strClipInfo_Copyright = strMPlayerOutput.Mid(23); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find(" Title:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 8)
        m_strClipInfo_Title = strMPlayerOutput.Mid(8); // To avoid assertion error: strex.cpp line 332
      return;
    }

    // treat " name:" in WMA/WMV as "Title"
    if (strMPlayerOutput.Find(" name:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 7)
        m_strClipInfo_Title = strMPlayerOutput.Mid(7); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find(" Artist:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 9)
        m_strClipInfo_Artist = strMPlayerOutput.Mid(9); // To avoid assertion error: strex.cpp line 332
      return;
    }

    // treat " author:" in WMA/WMV as "Artist"
    if (strMPlayerOutput.Find(" author:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 9)
        m_strClipInfo_Artist = strMPlayerOutput.Mid(9); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find(" Album:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 8)
        m_strClipInfo_Album = strMPlayerOutput.Mid(8); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find(" Genre:") != -1)
    {
      if (strMPlayerOutput.GetLength() > 8)
        m_strClipInfo_Genre = strMPlayerOutput.Mid(8); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find("ID_LENGTH") != -1)
    {
      if (strMPlayerOutput.GetLength() > 10)
        strMPlayerOutput = strMPlayerOutput.Mid(10); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%ld", &m_lClipInfo_Length);

      // hard limit (99:59:59)
      if (m_lClipInfo_Length >= 359999L)
      {
        m_lClipInfo_Length = 359999L;
      }
      return;
    }

    if (strMPlayerOutput.Find("ID_AUDIO_CODEC") != -1)
    {
      if (strMPlayerOutput.GetLength() > 15)
        m_strAudioInfo_Codec = strMPlayerOutput.Mid(15); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find("ID_AUDIO_FORMAT") != -1)
    {
      if (strMPlayerOutput.GetLength() > 16)
        m_strAudioInfo_Format = strMPlayerOutput.Mid(16); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find("ID_AUDIO_BITRATE") != -1)
    {
      if (strMPlayerOutput.GetLength() > 17)
        strMPlayerOutput = strMPlayerOutput.Mid(17); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%ld", &m_lAudioInfo_Bitrate);
      return;
    }

    if (strMPlayerOutput.Find("ID_AUDIO_RATE") != -1)
    {
      if (strMPlayerOutput.GetLength() > 14)
        strMPlayerOutput = strMPlayerOutput.Mid(14); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%ld", &m_lAudioInfo_Rate);
      return;
    }

    if (strMPlayerOutput.Find("ID_AUDIO_NCH") != -1)
    {
      if (strMPlayerOutput.GetLength() > 13)
        strMPlayerOutput = strMPlayerOutput.Mid(13); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%d", &m_nAudioInfo_NCH);
      return;
    }

    if (strMPlayerOutput.Find("ID_VIDEO_CODEC") != -1)
    {
      if (strMPlayerOutput.GetLength() > 15)
        m_strVideoInfo_Codec = strMPlayerOutput.Mid(15); // To avoid assertion error: strex.cpp line 332
      return;
    }

    if (strMPlayerOutput.Find("ID_VIDEO_BITRATE") != -1)
    {
      if (strMPlayerOutput.GetLength() > 17)
        strMPlayerOutput = strMPlayerOutput.Mid(17); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%ld", &m_lVideoInfo_Bitrate);
      return;
    }

    if (strMPlayerOutput.Find("ID_VIDEO_FPS") != -1)
    {
      if (strMPlayerOutput.GetLength() > 13)
        strMPlayerOutput = strMPlayerOutput.Mid(13); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%f", &m_fVideoInfo_FPS);
      return;
    }

    if (strMPlayerOutput.Find("ID_VIDEO_WIDTH") != -1)
    {
      if (strMPlayerOutput.GetLength() > 15)
        strMPlayerOutput = strMPlayerOutput.Mid(15); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%d", &m_nVideoInfo_Width);
      return;
    }

    if (strMPlayerOutput.Find("ID_VIDEO_HEIGHT") != -1)
    {
      if (strMPlayerOutput.GetLength() > 16)
        strMPlayerOutput = strMPlayerOutput.Mid(16); // To avoid assertion error: strex.cpp line 332
      sscanf(strMPlayerOutput, "%d", &m_nVideoInfo_Height);
      return;
    }

    // for Audio-Only stream, wait for "Starting" signal
    // if (m_bHaveVideo == FALSE)
    {
      if (strMPlayerOutput.Find("Starting") != -1)
      {
        // MPlayer finally starting playback the clip, return
        // nReturnCode = 1;
        ConfirmMPlayerPlaying(1);
        return;
      }
    }

    // for A/V stream (or Video-Only), wait for "VO: [" signal
    // or you will crash MPlayerGUI in CMainFrame::RestoreFromMaxMin() if pipe buffer
    // is small and have some delay when empty the reading pipe, very weird!
    /*
    if (m_bHaveVideo == TRUE)
    {
      if (strMPlayerOutput.Find("VO: [") == 0)
      {
        // MPlayer finally starting playback, return
        // nReturnCode = 1;
        ConfirmMPlayerPlaying(1);
        return;
      }
    }
    */

    // MPlayer failed to play the clip, return
    if (strMPlayerOutput.Find("Exiting") != -1)
    {
      // nReturnCode = -1;
      ConfirmMPlayerPlaying(-1);
      return;
    }

    // Interrupted?
    if (strMPlayerOutput.Find("interrupted") != -1)
    {
      // nReturnCode = -2;
      ConfirmMPlayerPlaying(-2);
      return;
    }
  }

/*
  // Do not catch "Exit", not stable
  if (strMPlayerOutput.Find("Exit") != -1)
  {
    Stop();
    m_nStatus = MPLAYER_STOPPED;
    return;
  }
*/

  // ICY Info: StreamTitle='Bach - Concerto for 4 Harpsichords in Amin';StreamUrl='';
  /*
  if (strOutput.Find("ICY Info:") != -1)
  {
    int nBegin, nEnd;

    nBegin = strOutput.Find("StreamTitle=");
    nEnd = strOutput.Find(";");

    if ((nBegin != -1) && (nEnd != -1))
    {
      strOutput = strOutput.Mid(nBegin, nEnd - nBegin);
      AfxMessageBox(strOutput);
    }
    continue;
  }
  */

  // Add more entries
  // Sleep(10);
}


void CMPlayer::LogFilter(CString strLog)
{
  // Filter Log
  if (strLog.Find("ANS_TIME_POSITION") != -1)
    return;

  if (strLog.GetLength() < 1)
    return;

  m_strMPlayerLog = strLog;
  AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_LOG, 0, 0);
}


void CMPlayer::GetMPlayerLog(CString &strLog) const
{
  strLog = m_strMPlayerLog;
}

// Send command to MPlayer to get current time position
void CMPlayer::RequireTimePos(void)
{
  // Return if MPlayer is not running
  if (CheckActivate() != 0)
  {
    return;
  }

  // Don't send command when MPlayer is paused, or you will resume it?
	// if (m_nStatus == MPLAYER_PAUSED)
	//  return;

  Command("get_time_pos");
}

// Get MPlayer current time position
// Return values:
//  long : MPlayer current time position
long CMPlayer::GetTimePos(void)
{
  return m_lTimePos;
}

// Check MPlayer process activate state
// Return values:
//  int :  0 MPlayer process is actived
//        -1 MPlayer process is terminated
int CMPlayer::CheckActivate(void)
{
  DWORD nExitCode;

  if (GetExitCodeProcess(m_piProcessInfo.hProcess, &nExitCode))
  {
    if (nExitCode == STILL_ACTIVE)
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }

  return -2;
}

// Return if current media file has video stream
// Return values:
//  BOOL : media file has video or not
BOOL CMPlayer::HaveVideo(void)
{
  return m_bHaveVideo;
}

// Get clip information: clip
// Return values:
//  CString : ClipInfo Clip
CString CMPlayer::GetClipInfo_Clip(void) const
{
  return m_strClipInfo_Clip;
}

// Get clip information: author
// Return values:
//  CString : ClipInfo Author
CString CMPlayer::GetClipInfo_Author(void) const
{
  return m_strClipInfo_Author;
}

// Get clip information: Copyright
// Return values:
//  CString : ClipInfo Copyright
CString CMPlayer::GetClipInfo_Copyright(void) const
{
  return m_strClipInfo_Copyright;
}

// Get clip information: Rating
// Return values:
//  CString : ClipInfo Rating
CString CMPlayer::GetClipInfo_Rating(void) const
{
  return m_strClipInfo_Rating;
}

// Get clip information: Length
// Return values:
//  long : ClipInfo Length
long CMPlayer::GetClipInfo_Length(void) const
{
  return m_lClipInfo_Length;
}

CString CMPlayer::GetClipInfo_Title(void) const
{
  return m_strClipInfo_Title;
}

CString CMPlayer::GetClipInfo_Artist(void) const
{
  return m_strClipInfo_Artist;
}

CString CMPlayer::GetClipInfo_Album(void) const
{
  return m_strClipInfo_Album;
}

CString CMPlayer::GetClipInfo_Genre(void) const
{
  return m_strClipInfo_Genre;
}

// Get audio information: Codec
// Return values:
//  CString : AudioInfo Codec
CString CMPlayer::GetAudioInfo_Codec(void) const
{
  return m_strAudioInfo_Codec;
}

// Get audio information: Format
// Return values:
//  CString : AudioInfo Format
CString CMPlayer::GetAudioInfo_Format(void) const
{
  return m_strAudioInfo_Format;
}

// Get audio information: Bitrate
// Return values:
//  long : AudioInfo Bitrate
long CMPlayer::GetAudioInfo_Bitrate(void) const
{
  return m_lAudioInfo_Bitrate;
}

// return Audio Channel info
int CMPlayer::GetAudioInfo_NCH(void) const
{
  return m_nAudioInfo_NCH;
}

// Get audio information: Rate
// Return values:
//  long : AudioInfo Rate
long CMPlayer::GetAudioInfo_Rate(void) const
{
  return m_lAudioInfo_Rate;
}

// Get video information: Codec
// Return values:
//  CString : VideoInfo Codec
CString CMPlayer::GetVideoInfo_Codec(void) const
{
  return m_strVideoInfo_Codec;
}

// Get video information: Bitrate
// Return values:
//  long : VideoInfo Bitrate
long CMPlayer::GetVideoInfo_Bitrate(void)
{
  // Just in case, calculate video bitrate
  CalculateVideoBitrate();

  return m_lVideoInfo_Bitrate;
}

// Calculate Video Birate by myself, just in case
void CMPlayer::CalculateVideoBitrate(void)
{
  if (m_bHaveVideo)
  {
    if (m_lVideoInfo_Bitrate == 0)
    {
      // Clip has video stream, but MPlayer gives me 0 as video bitrate
      // Calculate it by myself

      // long lFileSize = 0;
      ULONGLONG lFileSize = 0;
      CFileFind finder;

      if (finder.FindFile(m_strSource))
      {
        finder.FindNextFile();
        lFileSize = finder.GetLength();
        finder.Close();
      }

      if (m_lClipInfo_Length != 0)
      {
        m_lVideoInfo_Bitrate = (long) lFileSize / m_lClipInfo_Length * 8;
        m_lVideoInfo_Bitrate -= m_lAudioInfo_Bitrate;
      }
      else
      {
        m_lVideoInfo_Bitrate = 0;
      }
    }
  }
}



// Get video information: FPS
// Return values:
//  float : VideoInfo FPS
float CMPlayer::GetVideoInfo_FPS(void) const
{
  return m_fVideoInfo_FPS;
}

// Get video information: Width
// Return values:
//  int : VideoInfo Width
int CMPlayer::GetVideoInfo_Width(void) const
{
  if (m_nVideoInfo_Width > MAX_VIDEO_WIDTH)
    return MAX_VIDEO_WIDTH;
  else
    return m_nVideoInfo_Width;
}

// Get video information: Height
// Return values:
//  int : VideoInfo Height
int CMPlayer::GetVideoInfo_Height(void) const
{
  if (m_nVideoInfo_Height > MAX_VIDEO_HEIGHT)
    return MAX_VIDEO_HEIGHT;
  else  
    return m_nVideoInfo_Height;
}

// WM_TIMER message handler
void CMPlayer::OnTimer(UINT nIDEvent) 
{
  switch (nIDEvent)
  {
	  case TIMER_MPLAYER_STARTING:
		{
		  ReadMPlayerOutput();
		  break;
		}
    case TIMER_HALF_SECOND:
    {
		  RequireTimePos(); // Requiest time position
			ReadMPlayerOutput();
      break;
    }
    case TIMER_ONE_SECOND:
    {
      CheckAutoStop(); // Check if MPlayer is stopped (end of play)
      break;
    }
    /*
    case TIMER_EIGHT_SECOND:
    {
      // AfxGetApp()->m_pMainWnd->PostMessage(UWM_STATUSBAR_INFO_SWAP, 0, 0);
      break;
    }
    */
    /*
    case TIMER_FULLSCREENMOUSEHIDER:
    {
      CPoint p;
      GetCursorPos(&p);
      CRect r;
      GetWindowRect(r);

      // only SetCursor to NULL if in rect and cursor is not null
		  if ((r.PtInRect(p)) && (GetCursor() != NULL))
      {
        SetCursor(NULL);
      }

      break;
    }
    */
    default:
    {
      break;
    }
  }

	CStatic::OnTimer(nIDEvent);
}

float CMPlayer::GetCacheFill(void)
{
  return m_fCacheFill;
}

// Check if MPlayer is stopped (by itself)
// Post a message to CMainFrame if MPlayer is stopped
void CMPlayer::CheckAutoStop(void)
{
  if (m_nStatus == MPLAYER_PLAYING)
	{
    if (CheckActivate() != 0)
    {
      AutoStop();
      AfxGetApp()->m_pMainWnd->SendMessage(UWM_MPLAYER_AUTOSTOPPED, 0, 0);
    }
	}
}

// After ::Stop ::AutoStop do some cleanup job
void CMPlayer::CleanUp(void)
{
  // Stop timers
  KillTimer(TIMER_HALF_SECOND);
  KillTimer(TIMER_ONE_SECOND);
  // KillTimer(TIMER_FULLSCREENMOUSEHIDER);
  KillTimer(TIMER_MPLAYER_STARTING);
  // KillTimer(TIMER_EIGHT_SECOND);

  SetPlaybackPosition(0);

  TerminateSendCmdThread();
  TerminateMPlayerMonitorThread();
}


UINT CMPlayer::SendCmd(LPVOID p)
{
  CMPlayer *me = (CMPlayer*)p;
  me->SendCmd();
  return 0;
}

void CMPlayer::SendCmd()
{
  DWORD nWritten;
  char chCmdString[40];
  HANDLE hWriteToChild;

  while (TRUE)
  {
    /*
    if (WaitForSingleObject(m_hEventSendCmdQuit, 100) == WAIT_OBJECT_0)
    {
      TRACE("*** Thread: m_hEventSendCmdQuit\n");
      break;
    }
    */

    if (WaitForSingleObject(m_hEventSendCmdStart, INFINITE) == WAIT_OBJECT_0)
    {
      TRACE("*** Thread: SendCmdStart\n");
      hWriteToChild = GetWriteToChildHandle();

      // terminate thread if the hWriteToChild is NULL
      //  which means MPlayer.exe process has already terminated, and pipe is closed
      if (hWriteToChild == NULL)
      {
        break;
      }

      // strcpy(chBuffer, m_chBuffer);
      GetCmdString(chCmdString);
      WriteFile(hWriteToChild, chCmdString, strlen(chCmdString), &nWritten, NULL);
      SetEvent(m_hEventSendCmdDone);
    }
    /*
    else
    {
      if (WaitForSingleObject(m_hEventSendCmdQuit, INFINITE) == WAIT_OBJECT_0)
      {
        break;
      }
    }
    */
  }
}

// Start (Create) the SendCmdThread
//  return code:
//    int : 0, already created
//          1, success
//         -1, failed
int CMPlayer::StartSendCmdThread(void)
{
  if (m_pThreadSendCmd == NULL)
  {
    // CreateEvent(lpEventAttributes, // null, gets a default security descriptor
    //             bManualReset, // TRUE, use ResetEvent() to set nonsiginaled
    //             bInitialState, // TRUE, initial state of the event object is signaled
    //                            // FALSE, initial state nonsignaled
    //             lpName, // name of the event object
    m_hEventSendCmdStart = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_hEventSendCmdDone = CreateEvent(NULL, FALSE, FALSE, NULL);
    // m_hEventSendCmdQuit = CreateEvent(NULL, FALSE, FALSE, NULL);

    m_pThreadSendCmd = AfxBeginThread(SendCmd,
                                      this,
                                      0,
                                      CREATE_SUSPENDED);

    if (!m_pThreadSendCmd)
    {
      // thread failed to create, close events and return
      CloseHandle(m_hEventSendCmdStart);
      CloseHandle(m_hEventSendCmdDone);
      m_hEventSendCmdStart = NULL;
      m_hEventSendCmdDone = NULL;
      return -1;
    }

    m_pThreadSendCmd->m_bAutoDelete = FALSE;
    m_pThreadSendCmd->ResumeThread();
    TRACE("Thread SendCmd created.\n");
    return 1;
  }
  return 0;
}

// Try to terminate the SendCmdThread
//  by repeatly SetEvent(m_hEventSendCmdStart), the SendCmdThread will realize the
//  hWriteToChild is NULL and terminate itself automaticlly
void CMPlayer::TerminateSendCmdThread(void)
{
  if (m_pThreadSendCmd != NULL)
  {
    TRACE("try to terminate thread: SendCmd\n");
    DWORD dwExitCode;

    while (TRUE)
    {
      SetEvent(m_hEventSendCmdStart);
      ::GetExitCodeThread(m_pThreadSendCmd->m_hThread, &dwExitCode);
      if (dwExitCode != STILL_ACTIVE)
      {
        break;
      }

      if (WaitForSingleObject(m_pThreadSendCmd->m_hThread, 100) == WAIT_OBJECT_0)
      {
        break;
      }
    }

    delete m_pThreadSendCmd;
    m_pThreadSendCmd = NULL;

    CloseHandle(m_hEventSendCmdStart);
    CloseHandle(m_hEventSendCmdDone);
    // CloseHandle(m_hEventSendCmdQuit);
    m_hEventSendCmdStart = NULL;
    m_hEventSendCmdDone = NULL;
    // m_hEventSendCmdQuit = NULL;

    TRACE("Thread: SendCmd terminated normally.\n");
  }
}



UINT CMPlayer::MPlayerMonitor(LPVOID p)
{
  CMPlayer *me = (CMPlayer*)p;
  me->MPlayerMonitor();
  return 0;
}

void CMPlayer::MPlayerMonitor()
{
  // HANDLE hWriteToChild;
  CTime timeCurrent;

  while (TRUE)
  {
    if (WaitForSingleObject(m_hEventMPlayerMonitorQuit, 1000) == WAIT_OBJECT_0)
    {
      TRACE("*** Thread: m_hEventMPlayerMonitorQuit\n");
      break;
    }

    // hWriteToChild = GetWriteToChildHandle();
    // terminate thread if the hWriteToChild is NULL
    //  which means MPlayer.exe process has already terminated, and pipe is closed
    // if (hWriteToChild == NULL)
    // {
    //   break;
    // }

    // Compare time, if more than (m_nMPlayerMonitorThreshold) seconds the ReadMPlayerOutput() is not called
    // terminate the MPlayer process
    timeCurrent = CTime::GetCurrentTime();

    // m_timeLastReadCmd is set in ReadMPlayerOutput()
    if ((timeCurrent - m_timeLastReadCmd) > m_nMPlayerMonitorThreshold)
    {
      // Stop(); // don't call Stop() here, or we will crash the application
      // TODO: analyze the reason why Stop() crash the app here?
      // Terminate MPlayer process by use the TerminateProcess(), die hard!
      TerminateThread(m_piProcessInfo.hThread, 0);
      TerminateProcess(m_piProcessInfo.hProcess, 0);
    }

    TRACE("MPlayerMonitor running... Check: %d\n", timeCurrent - m_timeLastReadCmd);
  }

  TRACE("Yes, MPlayerMonitor thread terminated!\n");
}

int CMPlayer::StartMPlayerMonitorThread(void)
{
  if (m_pThreadMPlayerMonitor == NULL)
  {
    // CreateEvent(lpEventAttributes, // null, gets a default security descriptor
    //             bManualReset,      // TRUE, use ResetEvent() to set nonsiginaled
    //             bInitialState,     // TRUE, initial state of the event object is signaled
    //                                // FALSE, initial state nonsignaled
    //             lpName,            // name of the event object
    m_hEventMPlayerMonitorQuit = CreateEvent(NULL, FALSE, FALSE, NULL);

    m_pThreadMPlayerMonitor = AfxBeginThread(MPlayerMonitor,
                                             this,
                                             0,
                                             CREATE_SUSPENDED);

    if (!m_pThreadMPlayerMonitor)
    {
      // thread failed to create, close events and return
      CloseHandle(m_hEventMPlayerMonitorQuit);
      m_hEventMPlayerMonitorQuit = NULL;
      return -1;
    }

    m_pThreadMPlayerMonitor->m_bAutoDelete = FALSE;
    m_pThreadMPlayerMonitor->ResumeThread();
    TRACE("MPlayerMonitor Thread created.\n");
    return 1;
  }

  return 0;
}

void CMPlayer::TerminateMPlayerMonitorThread(void)
{
  if (m_pThreadMPlayerMonitor != NULL)
  {
    TRACE("try to terminate thread: MPlayerMonitor\n");
    DWORD dwExitCode;

    // To terminate MPlayerMonitor thread...
    while (TRUE)
    {
      SetEvent(m_hEventMPlayerMonitorQuit);
      ::GetExitCodeThread(m_pThreadMPlayerMonitor->m_hThread, &dwExitCode);
      if (dwExitCode != STILL_ACTIVE)
      {
        TRACE("MPlayerMonitor Terminated: STILL_ACTIVE\n");
        break;
      }

      if (WaitForSingleObject(m_pThreadMPlayerMonitor->m_hThread, 1000) == WAIT_OBJECT_0)
      {
        TRACE("MPlayerMonitor Terminated: WAIT_OBJECT_0\n");
        break;
      }

      TRACE("Waiting for termination of MPlayerMonitor...\n");
    }

    // Release memory
    delete m_pThreadMPlayerMonitor;
    m_pThreadMPlayerMonitor = NULL;

    // Close handle
    CloseHandle(m_hEventMPlayerMonitorQuit);
    m_hEventMPlayerMonitorQuit = NULL;

    TRACE("MPlayerMonitor Thread terminated normally.\n");
  }
}

void CMPlayer::SetEnableMPlayerMonitor(BOOL bEnableMPlayerMonitor)
{
  m_bEnableMPlayerMonitor = bEnableMPlayerMonitor;
}

BOOL CMPlayer::GetEnableMPlayerMonitor(void) const
{
  return m_bEnableMPlayerMonitor;
}

void CMPlayer::SetEnableLogging(BOOL bEnableLogging)
{
  m_bEnableLogging = bEnableLogging;
}

BOOL CMPlayer::GetEnableLogging(void) const
{
  return m_bEnableLogging;
}

void CMPlayer::SetEnableArgumentVolume(BOOL bEnableArgumentVolume)
{
  m_bEnableArgumentVolume = bEnableArgumentVolume;
}

BOOL CMPlayer::GetEnableArgumentVolume(void) const
{
  return m_bEnableArgumentVolume;
}

void CMPlayer::SetPipeBufferSize(int nPipeBufferSize)
{
  if (nPipeBufferSize > 0)
  {
    m_nPipeBufferSize = nPipeBufferSize;
  }
  else
  {
    m_nPipeBufferSize = 8192; // default
  }
}

void CMPlayer::SetAllowSendCmdWhilePaused(BOOL bAllowSendCmdWhilePaused)
{
  m_bAllowSendCmdWhilePaused = bAllowSendCmdWhilePaused;
}

BOOL CMPlayer::GetAllowSendCmdWhilePaused(void) const
{
  return m_bAllowSendCmdWhilePaused;
}

