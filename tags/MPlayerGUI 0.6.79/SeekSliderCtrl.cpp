// SeekSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
// #include "test_slider.h"
#include "MPlayerGUI.h"
#include "SeekSliderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeekSliderCtrl

CSeekSliderCtrl::CSeekSliderCtrl() : m_knMin(0), m_knMax(100), m_knThumbWidth(25)
{
  m_bDragging = FALSE;
  m_bEnable = FALSE;
  m_nY = 0;
}

CSeekSliderCtrl::~CSeekSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CSeekSliderCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CSeekSliderCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeekSliderCtrl message handlers

void CSeekSliderCtrl::OnPaint() 
{
	CPaintDC dc0(this); // device context for painting
  CMemDC dc(&dc0); // flickless drawing, see memdc.h for details

  COLORREF 
    colorWhite   = GetSysColor(COLOR_WINDOW),
    colorShadow  = GetSysColor(COLOR_3DSHADOW), 
    colorLight   = GetSysColor(COLOR_3DHILIGHT), 
    colorBKG     = GetSysColor(COLOR_BTNFACE),
    colorHilight = GetSysColor(COLOR_HIGHLIGHT),
    color3dface  = GetSysColor(COLOR_3DFACE),
    color3DDKShadow = GetSysColor(COLOR_3DDKSHADOW);

  // get old pen/brush for restore
  CBrush *pOldBrush = dc.GetCurrentBrush();;
  CPen *pOldPen = dc.GetCurrentPen();

  CBrush Brush3DFACE(color3dface);
  CPen PenBlack(PS_SOLID, 0, color3DDKShadow);

  // client
  {
    CRect rcClient;
    GetClientRect(&rcClient);
    // dc.SelectStockObject(LTGRAY_BRUSH);
    dc.FillSolidRect(rcClient, color3dface);
  }

  // channel
  {
    CRect rcChannel;
    rcChannel = GetChannelRect();
    // dc.Draw3dRect(rcChannel, colorShadow, colorWhite);
    dc.Draw3dRect(rcChannel, colorShadow, colorLight);
    rcChannel.DeflateRect(1, 1);
    dc.Draw3dRect(rcChannel, 0, color3dface);
    rcChannel.DeflateRect(1, 1);

    if (m_bEnable)
    {
      // fill shadow color if enabled
      dc.FillSolidRect(rcChannel, colorShadow);
      // dc.FillSolidRect(rcChannel, color3dface);
    }
  }

  // thumb
  if (m_bEnable)
  {
    CRect rcThumb;
    CPoint ptThumb1, ptThumb2;

    rcThumb = GetThumbRect();
    dc.FillSolidRect(rcThumb, color3dface);
    dc.Draw3dRect(rcThumb, colorLight, color3DDKShadow);
    rcThumb.DeflateRect(1, 1, 1, 1);
    dc.Draw3dRect(rcThumb, color3dface, colorShadow);

    ptThumb1.x = rcThumb.CenterPoint().x;
    ptThumb2.x = rcThumb.CenterPoint().x;
    ptThumb1.y = rcThumb.top + 2;
    ptThumb2.y = rcThumb.bottom - 2;

    pOldPen = dc.SelectObject(&PenBlack);
    dc.MoveTo(ptThumb1);
    dc.LineTo(ptThumb2);
    dc.SelectObject(pOldPen);
  }

  // realplayer like channel (left, played)
  if (1)
  {
    CRect rcPlayed;
    CRect rcThumb;
    CRect rcChannel;

    rcChannel = GetChannelRect();
    rcThumb = GetThumbRect();

    rcPlayed.left = 0;
    rcPlayed.top = rcChannel.top;
    rcPlayed.bottom = rcChannel.bottom;
    rcPlayed.right = rcThumb.left;
    rcPlayed.DeflateRect(3, 2, 0, 2);
    dc.FillSolidRect(rcPlayed, color3DDKShadow);
    // dc.FillSolidRect(rcPlayed, RGB(0, 128, 128));
    // dc.FillSolidRect(rcPlayed, RGB(255, 128, 128));
  }

  // realplayer like channel (right, unplayed)
  /*
  {
    CRect rcUnPlayed;
    CRect rcThumb;
    CRect rcChannel;

    rcChannel = GetChannelRect();
    rcThumb = GetThumbRect();

    rcUnPlayed.left = rcThumb.right;
    rcUnPlayed.top = rcChannel.top;
    rcUnPlayed.bottom = rcChannel.bottom;
    rcUnPlayed.right = rcChannel.right;
    rcUnPlayed.DeflateRect(2, 1, 1, 1);
    dc.FillSolidRect(rcUnPlayed, color3dface);
  }
  */

  // restore old pen/brush to avoid gdi resource leak
  dc.SelectObject(pOldPen);
  dc.SelectObject(pOldBrush);

	// Do not call CSliderCtrl::OnPaint() for painting messages
}


void CSeekSliderCtrl::SetPos(int nPos)
{
  if (!m_bDragging)
  {
    if ((nPos >= m_knMin) && (nPos <= m_knMax))
    {
      if (m_nPos != nPos)
      {
        m_nPos = nPos;
        Invalidate();
      }
    }
  }
}


int CSeekSliderCtrl::GetPos(void)
{
  return m_nPos;
}


void CSeekSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
  if (!m_bEnable)
  {
    // return if disabled
    return;
  }

	if (GetThumbRect().PtInRect(point))
	{
    m_bDragging = TRUE;
    m_nY = point.y;
		SetCapture();
		SetFocus();
		// RedrawWindow();
		// CSliderCtrl::OnLButtonDown(nFlags, point);
	}
  else
  {
    m_bDragging = TRUE;
    m_nY = point.y;
    MoveThumb(point);
		SetCapture();
		SetFocus();
    Invalidate();
  }

/*
  if (GetChannelRect().PtInRect(point))
  {
    MoveThumb(point);
  }
*/
}


void CSeekSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  if (m_bDragging == TRUE)
  {
    ReleaseCapture();
    m_bDragging = FALSE;
    // CSliderCtrl::OnLButtonUp(nFlags, point);
    // Post message with SB_THUMBPOSITION prefix, to filter out Home/End message
    GetParent()->PostMessage(WM_HSCROLL, MAKEWPARAM(SB_THUMBPOSITION, (WORD)m_nPos), (LPARAM)m_hWnd);
  }
}


void CSeekSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd* w = GetCapture();
	if(w && w->m_hWnd == m_hWnd && (nFlags & MK_LBUTTON))
  {
    if (abs(m_nY - point.y) > 100)
    {
      m_bDragging = FALSE;
      ReleaseCapture();
    }
    else
    {
      // RedrawWindow();
      MoveThumb(point);
      Invalidate();
      // CSliderCtrl::OnMouseMove(nFlags, point);
    }
  }
}


CRect CSeekSliderCtrl::GetChannelRect(void)
{
  CRect r;

  GetClientRect(&r);

  r.DeflateRect(1, 0);
  // r.bottom = r.top + 20;

  return (r);
}


CRect CSeekSliderCtrl::GetThumbRect(void)
{
  CRect r, rcChannel;
  
  rcChannel = GetChannelRect();
  r = rcChannel;

  int nHalfHeight;

  int x = r.left + (int)((r.Width() - m_knThumbWidth - 4) * m_nPos / 100);
  int y = r.CenterPoint().y;

  nHalfHeight = r.Height() / 2;

  r.SetRect(x, y, x, y);
  r.InflateRect(0, nHalfHeight, m_knThumbWidth, nHalfHeight);
  // r.DeflateRect(0, 2, 0, 2);
  r.left += 2;
  r.right += 2;
  r.top = rcChannel.top + 2;
  r.bottom = rcChannel.bottom - 2;

  if (r.right > rcChannel.right - 2)
  {
    r.right = rcChannel.right - 2;
    r.left = r.right - m_knThumbWidth;
  }

  return (r);
}


void CSeekSliderCtrl::MoveThumb(CPoint point)
{
  CRect r = GetChannelRect();

  point.x -= m_knThumbWidth / 2;

  if (point.x < r.left)
  {
    // SetPos(m_knMin);
    m_nPos = m_knMin;
  }
  else if (point.x >= (r.right - m_knThumbWidth))
  {
    // SetPos(m_knMax);
    m_nPos = m_knMax;
  }
  else
  {
    m_nPos = (int)(point.x * 100 / (r.Width() - m_knThumbWidth));
    // SetPos((int)(point.x * 100 / r.Width()));
  }
}


BOOL CSeekSliderCtrl::OnEraseBkgnd(CDC* pDC) 
{
  return TRUE;
  	
	// return CSliderCtrl::OnEraseBkgnd(pDC);
}


void CSeekSliderCtrl::SetEnable(BOOL bEnable)
{
  if (m_bEnable != bEnable)
  {
    m_bEnable = bEnable;

    if (!m_bEnable)
    {
      // set m_nPos to 0 if disabled
      m_nPos = 0;

      // disable drag just in case
      if (m_bDragging)
      {
        m_bDragging = FALSE;
        ReleaseCapture();
      }
    }

    // redraw the control
    Invalidate();
  }
}


BOOL CSeekSliderCtrl::PreTranslateMessage(MSG* pMsg) 
{
  if(pMsg->message == WM_KEYDOWN)
  {
    if((pMsg->wParam == VK_ESCAPE) && (m_bDragging == TRUE))
    {
      m_bDragging = FALSE;
      ReleaseCapture();
      return TRUE;
    }
  }

	return CSliderCtrl::PreTranslateMessage(pMsg);
}

void CSeekSliderCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CSliderCtrl::OnSetFocus(pOldWnd);
	
	AfxGetMainWnd()->SetFocus(); // don't focus on us, parents will take care of our positioning	
}
