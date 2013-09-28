// PlayerStatusbar.cpp : implementation file
//

#include "stdafx.h"
#include "MPlayerGUI.h"
// #include "MyStatusBar.h"
#include "PlayerStatusbar.h"
#include "functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerStatusbar dialog

#define TIMER_FLIPINFO            0
#define TIMER_BUFFERING           1

CPlayerStatusbar::CPlayerStatusbar(CWnd* pParent /*=NULL*/)
	: CDialogBar(/*CPlayerStatusbar::IDD, pParent*/)
{
	//{{AFX_DATA_INIT(CPlayerStatusbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPlayerStatusbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerStatusbar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayerStatusbar, CDialogBar)
	//{{AFX_MSG_MAP(CPlayerStatusbar)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerStatusbar message handlers

BOOL CPlayerStatusbar::Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID) 
{
  BOOL bRes= CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
  InitDialogBar();
  return bRes;
}

BOOL CPlayerStatusbar::InitDialogBar(void)
{
  UpdateData(FALSE);
  // add your initialization code here

  CRect r;
  r.SetRectEmpty();

  m_IconStatus.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_ICON, r, this, NULL);
  m_IconSpeakerL.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_ICON, r, this, NULL);
  m_IconSpeakerR.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_ICON, r, this, NULL);

  m_StatusLabel.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_ENDELLIPSIS,
      CRect(26, 5, 200, 20), this);
  m_StatusLabel.SetFontName("MS Sans Serif");
  // m_StatusLabel.SetFontBold(FW_NORMAL);
  m_StatusLabel.SetFontSize(9);
  m_StatusLabel.SetFontBold(FALSE);
  m_StatusLabel.SetTextColor(RGB(255, 255, 255));
  // m_StatusLabel.SetBkColor(RGB(200, 0, 0));
  m_StatusLabel.SetBkColor(RGB(0, 0, 0));
  m_StatusLabel.SetTransparent(FALSE);
  m_StatusLabel.SetTextEllipsis(TRUE);
  m_StatusLabel.SetText(_T("Playing"));

  m_TimerLabel.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_RIGHT,
      CRect(26, 5, 200, 20), this);
  m_TimerLabel.SetFontName("MS Sans Serif");
  // m_StatusLabel.SetFontBold(FW_NORMAL);
  m_TimerLabel.SetFontSize(9);
  m_TimerLabel.SetFontBold(FALSE);
  m_TimerLabel.SetTextColor(RGB(255, 255, 255));
  // m_TimerLabel.SetBkColor(RGB(0, 0, 200));
  m_TimerLabel.SetBkColor(RGB(0, 0, 0));
  m_TimerLabel.SetTransparent(FALSE);
  m_TimerLabel.SetText(_T("00:00 / 00:00"));

  m_strDuration = _T("");
  // 1 - Short, 2 - Full, 3 - Basic (No duration)
  m_nTimeDisplayMode = 1;

  Relayout();

  return TRUE;
}

BOOL CPlayerStatusbar::OnEraseBkgnd(CDC* pDC) 
{
	CRect r;
	GetClientRect(&r);

  // r.InflateRect(0, 0, 0, 1);
  // r.InflateRect(1, 0, 1, 0);
  pDC->Draw3dRect(&r, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
	r.DeflateRect(1, 1);
	pDC->FillSolidRect(&r, 0);

  return TRUE;
  // return CDialogBar::OnEraseBkgnd(pDC);
}

void CPlayerStatusbar::Relayout(void)
{
  CRect r, r2, r3;
  int nOffset = 0;

  // Set Status Icon's Position
  GetClientRect(r);
  r.SetRect(6, r.top + 4, 6 + 16, r.bottom - 4);
  m_IconStatus.MoveWindow(r);

  // Set Audio Mode's Position
  GetClientRect(r);
  if ((m_nAudioMode == 2) || (m_nAudioMode == -1))
  {
    // For "Stereo" and "Unknown" mode, set the left icon's position
    r.SetRect(r.right - 35, r.top + 4, r.right - 35 + 16, r.bottom - 4);
    m_IconSpeakerL.MoveWindow(r);
  }
  else
  {
    // Otherwise, 'hide' it
    r.SetRect(r.right - 35, r.top + 4, 0, 0);
    m_IconSpeakerL.MoveWindow(r);
    nOffset = 8;
  }
  GetClientRect(r);
  r.SetRect(r.right - 19, r.top + 4, r.right - 19 + 16, r.bottom - 4);
  m_IconSpeakerR.MoveWindow(r);

  // Set Time Label's Position
  GetClientRect(r);
  r.DeflateRect(27, 5, 39 - nOffset, 4);
  r2 = r;
  
  switch (m_nTimeDisplayMode)
  {
  case 1:
    // Short Mode
    r2.left = r2.right - 68;
    break;
  case 2:
    // Full Mode
    r2.left = r2.right - 98;
    break;
  case 3:
    // Basic Mode
    r2.left = r2.right - 30;
    break;
  default:
    // ERROR
    r2.left = r2.right - 98;
    break;
  }

  m_TimerLabel.MoveWindow(r2);

  // Set Status Label's Position
  r3 = r;
  r3.right = r2.left;
  m_StatusLabel.MoveWindow(r3);

  Invalidate();
}

void CPlayerStatusbar::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);

  if(::IsWindow(m_IconStatus.m_hWnd))
  {
    Relayout();
  }
}

void CPlayerStatusbar::SetStatusIcon(WORD wIcon)
{
  HICON hIcon;

  hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
                             MAKEINTRESOURCE(wIcon),
                             IMAGE_ICON,
                             GetSystemMetrics(SM_CXSMICON),
                             GetSystemMetrics(SM_CYSMICON),
                             LR_DEFAULTCOLOR);

  SetStatusIcon2(hIcon);
}

void CPlayerStatusbar::SetStatusIcon2(HICON hIcon)
{
	if(m_hIconStatus == hIcon) return;

	if(m_hIconStatus) DestroyIcon(m_hIconStatus);
	m_IconStatus.SetIcon(m_hIconStatus = hIcon);

	// Relayout();
}

void CPlayerStatusbar::SetSpeakerLIcon(WORD wIcon)
{
  HICON hIcon;

  hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
                             MAKEINTRESOURCE(wIcon),
                             IMAGE_ICON,
                             GetSystemMetrics(SM_CXSMICON),
                             GetSystemMetrics(SM_CYSMICON),
                             LR_DEFAULTCOLOR);

  SetSpeakerLIcon2(hIcon);
}

void CPlayerStatusbar::SetSpeakerLIcon2(HICON hIcon)
{
	if(m_hIconSpeakerL == hIcon) return;

	if(m_hIconSpeakerL) DestroyIcon(m_hIconSpeakerL);
	m_IconSpeakerL.SetIcon(m_hIconSpeakerL = hIcon);

	// Relayout();
}

void CPlayerStatusbar::SetSpeakerRIcon(WORD wIcon)
{
  HICON hIcon;

  hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
                             MAKEINTRESOURCE(wIcon),
                             IMAGE_ICON,
                             GetSystemMetrics(SM_CXSMICON),
                             GetSystemMetrics(SM_CYSMICON),
                             LR_DEFAULTCOLOR);

  SetSpeakerRIcon2(hIcon);
}

void CPlayerStatusbar::SetSpeakerRIcon2(HICON hIcon)
{
	if(m_hIconSpeakerR == hIcon) return;

	if(m_hIconSpeakerR) DestroyIcon(m_hIconSpeakerR);
	m_IconSpeakerR.SetIcon(m_hIconSpeakerR = hIcon);

	// Relayout();
}

void CPlayerStatusbar::SetAudioMode(int nMode)
{
  m_nAudioMode = nMode;

  switch (nMode)
  {
  case -1: // Unknown, no file is open
    SetSpeakerLIcon(IDI_FILE_BLANK);
    SetSpeakerRIcon(IDI_FILE_BLANK);
    break;
  case 0: // No Audio
    SetSpeakerLIcon(IDI_FILE_BLANK);
    SetSpeakerRIcon(IDI_AUDIO_NO_AUDIO);
    break;
  case 1: // Mono
    SetSpeakerLIcon(IDI_FILE_BLANK);
    SetSpeakerRIcon(IDI_AUDIO_MONO);
    break;
  case 2: // Stereo
    SetSpeakerLIcon(IDI_AUDIO_STEREOL);
    SetSpeakerRIcon(IDI_AUDIO_STEREOR);
    break;
  default:
    SetSpeakerLIcon(IDI_FILE_BLANK);
    SetSpeakerRIcon(IDI_FILE_BLANK);
    m_nAudioMode = -1;
    break;
  }

  Relayout();
}


void CPlayerStatusbar::SetStatusMode(int nMode)
{
  switch (nMode)
  {
  case 0: // Idle
    SetStatusIcon(IDI_FILE_BLANK);
    break;
  case 1: // Local Media
    SetStatusIcon(IDI_FILE_LOCALMEDIA);
    break;
  case 2: // Net Media
    SetStatusIcon(IDI_NET_OK);
    break;
  case 3: // Buffering
    SetStatusIcon(IDI_NET_BUFFERING);
    break;
  case 4: // Failed
    SetStatusIcon(IDI_NET_REC_020);
    break;
  default:
    SetStatusIcon(IDI_FILE_BLANK);
    break;
  }
}

void CPlayerStatusbar::SetMessage(CString strMessage)
{
  m_StatusLabel.SetText(_T(strMessage));
}

void CPlayerStatusbar::SetDuration(long lDuration)
{
  int nHours, nMinutes, nSeconds;
  CString strTime;

  CTimeSplitter MyTimeSplitter;
  MyTimeSplitter.SetTime(lDuration);
  nHours = MyTimeSplitter.GetHours();
  nMinutes = MyTimeSplitter.GetMinutes();
  nSeconds = MyTimeSplitter.GetSeconds();

  if (nHours > 99)
  {
    nHours = 99;
  }

  if (nHours == 0)
  {
    m_strDuration.Format("/ %02d:%02d", nMinutes, nSeconds);
    m_nTimeDisplayMode = 1; // Short Mode
  }
  else
  {
    m_strDuration.Format("/ %02d:%02d:%02d", nHours, nMinutes, nSeconds);
    m_nTimeDisplayMode = 2; // Full Mode
  }

  if (lDuration <= 0)
  {
    m_strDuration = _T("");
    m_nTimeDisplayMode = 3; // Basic Mode
  }

  Relayout();
}

void CPlayerStatusbar::SetTime(long lCurTime)
{
  int nHours, nMinutes, nSeconds;
  CString strTime;

  CTimeSplitter MyTimeSplitter;
  MyTimeSplitter.SetTime(lCurTime);
  nHours = MyTimeSplitter.GetHours();
  nMinutes = MyTimeSplitter.GetMinutes();
  nSeconds = MyTimeSplitter.GetSeconds();

  if (nHours > 99)
  {
    nHours = 99;
  }

  switch (m_nTimeDisplayMode)
  {
  case 1:
    // Short Mode ("01:34 / 05:22")
    strTime.Format("%02d:%02d %s", nMinutes, nSeconds, m_strDuration);
    break;
  case 2:
    // Full Mode ("00:50:35 / 02:04:21")
    strTime.Format("%02d:%02d:%02d %s", nHours, nMinutes, nSeconds, m_strDuration);
    break;
  case 3:
    // Basic Mode ("01:23")
    strTime.Format("%02d:%02d", nMinutes, nSeconds);
    break;
  default:
    strTime.Format(_T("ERROR"));
    break;
  }

  m_TimerLabel.SetText(_T(strTime));
}

// User must call this function in order to work properly
void CPlayerStatusbar::Reset(void)
{
  SetDuration(0);
  SetTime(0);
  SetStatusMode(0);
  SetAudioMode(-1); // Unknown audio mode, show 2 blank
  StopFlipInfo();
  SetFlipInfo0(_T(""));
  SetFlipInfo1(_T(""));
  SetFlipInfo2(_T(""));
  SetFlipInfo3(_T(""));
  SetFlipInfo4(_T(""));
  m_nFlipInfoCounter = 0;

  StopBuffering();
  m_nBufferingCounter = 0;

  SetMessage(_T("Ready"));
}

void CPlayerStatusbar::SetFlipInfo0(CString strFlipInfo0)
{
  m_strFlipInfo0 = strFlipInfo0;
}

void CPlayerStatusbar::SetFlipInfo1(CString strFlipInfo1)
{
  m_strFlipInfo1 = strFlipInfo1;
}

void CPlayerStatusbar::SetFlipInfo2(CString strFlipInfo2)
{
  m_strFlipInfo2 = strFlipInfo2;
}

void CPlayerStatusbar::SetFlipInfo3(CString strFlipInfo3)
{
  m_strFlipInfo3 = strFlipInfo3;
}

void CPlayerStatusbar::SetFlipInfo4(CString strFlipInfo4)
{
  m_strFlipInfo4 = strFlipInfo4;
}

void CPlayerStatusbar::StartFlipInfo(void)
{
  SetTimer(TIMER_FLIPINFO, 8000, NULL);
}

void CPlayerStatusbar::StopFlipInfo(void)
{
  KillTimer(TIMER_FLIPINFO);
}

void CPlayerStatusbar::DoFlipInfo(void)
{
  switch (m_nFlipInfoCounter)
  {
  case 0:
    SetMessage(m_strFlipInfo0);
    break;
  case 1:
    SetMessage(m_strFlipInfo1);
    break;
  case 2:
    SetMessage(m_strFlipInfo2);
    break;
  case 3:
    SetMessage(m_strFlipInfo3);
    break;
  case 4:
    SetMessage(m_strFlipInfo4);
    break;
  default:
    SetMessage(_T("-"));
    break;
  }

  m_nFlipInfoCounter++;

  if (m_nFlipInfoCounter > 4)
    m_nFlipInfoCounter = 0;
}

void CPlayerStatusbar::DoBuffering(void)
{
  switch (m_nBufferingCounter)
  {
  case 0:
    // SetMessage(_T("Buffering."));
    SetStatusIcon(IDI_FILE_BLANK);
    break;
  case 1:
    // SetMessage(_T("Buffering.."));
    SetStatusIcon(IDI_NET_INOUT);
    break;
  default:
    SetMessage(_T(""));
    break;
  }

  m_nBufferingCounter++;

  if (m_nBufferingCounter > 1)
    m_nBufferingCounter = 0;
}

void CPlayerStatusbar::StartBuffering(void)
{
  SetStatusIcon(IDI_NET_INOUT);
  SetTimer(TIMER_BUFFERING, 1000, NULL);
}

void CPlayerStatusbar::StopBuffering(void)
{
  KillTimer(TIMER_BUFFERING);
}


void CPlayerStatusbar::OnTimer(UINT nIDEvent) 
{
  switch (nIDEvent)
  {
  case TIMER_FLIPINFO:
    DoFlipInfo();
    break;
  case TIMER_BUFFERING:
    DoBuffering();
    break;
  default:
    break;
  }

	CDialogBar::OnTimer(nIDEvent);
}
