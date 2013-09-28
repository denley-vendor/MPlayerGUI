#include "stdafx.h"
#include "MPlayerGUI.h"
#include "MyToolBar.h"

CMyToolBar::CMyToolBar()
{
}

CMyToolBar::~CMyToolBar()
{
}

BOOL CMyToolBar::Create(CWnd *pParentWnd)
{
  if (!CToolBar::Create(pParentWnd, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM | CBRS_TOOLTIPS))
  {
    return FALSE;
  }

  if (!LoadToolBar(IDR_MYTOOLBAR))
  {
    return FALSE;
  }
/*
  UINT styles[] = 
  {
    TBBS_CHECKGROUP, TBBS_CHECKGROUP, TBBS_CHECKGROUP,
    TBBS_SEPARATOR,
    TBBS_BUTTON,
    TBBS_SEPARATOR,
    TBBS_SEPARATOR,
    TBBS_CHECKBOX,
  };

  for (int i = 0; i < countof(styles); i++)
    SetButtonStyle(i, styles[i]);
*/


  ModifyStyle(0, TBSTYLE_FLAT);

  SetButtonStyle(0, TBBS_BUTTON); // PLAY
  SetButtonStyle(1, TBBS_BUTTON); // PAUSE
  SetButtonStyle(2, TBBS_BUTTON); // STOP
  SetButtonStyle(3, TBBS_SEPARATOR); // separator
  SetButtonStyle(4, TBBS_BUTTON); // PREVIOUS
  SetButtonStyle(5, TBBS_BUTTON); // NEXT
  SetButtonStyle(6, TBBS_SEPARATOR); // Separator
  SetButtonStyle(7, TBBS_BUTTON); // REPEAT
  SetButtonStyle(8, TBBS_SEPARATOR); // Separator
  SetButtonStyle(9, TBBS_BUTTON); // PLAYLIST
  SetButtonStyle(10, TBBS_SEPARATOR); // Separator
  SetButtonStyle(11, TBBS_BUTTON); // MUTE
  // SetButtonStyle(11, TBBS_SEPARATOR); // Separator
  SetButtonStyle(12, TBBS_CHECKBOX); // SLIDER

  if (!m_Slider_Volume.Create(WS_CHILD | WS_VISIBLE | TBS_HORZ,
       CRect(0, 0, 0, 0),
       this,
       IDC_SLIDER_VOLUME))
  {
    return FALSE;
  }

  // init the slider volume
  m_Slider_Volume.SetLineSize(1);
  m_Slider_Volume.SetPageSize(20);
  m_Slider_Volume.SetRange(0, 100);
  m_Slider_Volume.SetPos(100);

  return TRUE;
}

void CMyToolBar::ArrangeControls()
{
  if(!::IsWindow(m_Slider_Volume.m_hWnd))
    return;

  CRect r;
  GetClientRect(&r);

  m_Slider_Volume.MoveWindow(r.right - 50, r.top + 2, 50, r.bottom - 2);

  // Trying to set the Mute Button's Position
  // Get Button:Playlist information, especially i need the right edge of the rectangle
  CRect r9;
  GetItemRect(9, &r9);

  // Set Button:10 (Separator) 's Width, so the Mute will move also :)
  // r.right - 50    is the Volume Control's left edge
  // r9.right        is the Playlist Button's right edge
  // r9.Width()      is the Toolbar Button's Width
  // 8               is the space between two buttons on Toolbar
  SetButtonInfo(10, GetItemID(10), TBBS_SEPARATOR, r.right - 50 - r9.right - r9.Width() - 8);
}


BEGIN_MESSAGE_MAP(CMyToolBar, CToolBar)
  ON_WM_SIZE()
  ON_WM_HSCROLL()
END_MESSAGE_MAP()


void CMyToolBar::OnSize(UINT nType, int cx, int cy)
{
	CToolBar::OnSize(nType, cx, cy);

	ArrangeControls();
}


void CMyToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
		
  if ((CSliderCtrl*)pScrollBar == (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOLUME))
  {
    int nSliderPos;
    nSliderPos = m_Slider_Volume.GetPos();
/*
    CString strMessage;
    strMessage.Format("vol: %d", nSliderPos);
    AfxMessageBox(strMessage);
*/
    AfxGetApp()->m_pMainWnd->PostMessage(UWM_SLIDER_VOLUME, nSliderPos, 0);
  }

	CToolBar::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMyToolBar::SetSliderVolume(int nPos)
{
  if (GetDlgItem(IDC_SLIDER_VOLUME) != NULL)
  {
    if ((nPos < 0) || (nPos > 100))
    {
      nPos = 0;
    }

    m_Slider_Volume.SetPos(nPos);
  }
}

int CMyToolBar::GetSliderVolume(void)
{
  if (GetDlgItem(IDC_SLIDER_VOLUME) != NULL)
  {
    return m_Slider_Volume.GetPos();
  }
  else
  {
    return 0;
  }
}
