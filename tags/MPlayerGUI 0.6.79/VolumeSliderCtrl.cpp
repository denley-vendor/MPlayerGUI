// VolumeSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
// #include "test_slider.h"
#include "MPlayerGUI.h"
#include "VolumeSliderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeSliderCtrl

CVolumeSliderCtrl::CVolumeSliderCtrl() : m_knMin(0), m_knMax(100), m_knThumbWidth(10)
{
  m_bDragging = FALSE;
}

CVolumeSliderCtrl::~CVolumeSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CVolumeSliderCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CVolumeSliderCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeSliderCtrl message handlers

void CVolumeSliderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
  // CMemDC dc(&dc0);

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

  CBrush brush3DFACE(color3dface);
  CBrush brush3DDKShadow(color3DDKShadow);
  CPen penWhite(PS_SOLID, 0, colorLight); // colorWhite);
  CPen penShadow(PS_SOLID, 0, colorShadow);

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
    // rcChannel.DeflateRect(0, 2, m_knThumbWidth / 2, 4);
    rcChannel.DeflateRect(0, 1, 1, 4);

    CPoint ptPoint[3];
    ptPoint[0].x = rcChannel.right;
    ptPoint[0].y = rcChannel.top;

    ptPoint[1].x = rcChannel.right;
    ptPoint[1].y = rcChannel.bottom;

    ptPoint[2].x = rcChannel.left;
    ptPoint[2].y = rcChannel.bottom;

    pOldPen = dc.SelectObject(&penWhite);
    dc.MoveTo(ptPoint[0]);
    dc.LineTo(ptPoint[1]);

    dc.MoveTo(ptPoint[1]);
    dc.LineTo(ptPoint[2]);

    dc.SelectObject(&penShadow);
    dc.MoveTo(ptPoint[2]);
    dc.LineTo(ptPoint[0]);

    // dc.Polygon(ptPoint, 3);
    dc.SelectObject(pOldPen);
  }

  // thumb
  {
    CRect rcThumb;

    rcThumb = GetThumbRect();
    dc.FillSolidRect(rcThumb, color3dface);
    dc.Draw3dRect(rcThumb, colorLight, color3DDKShadow);
    rcThumb.DeflateRect(1, 1, 1, 1);
    dc.Draw3dRect(rcThumb, color3dface, colorShadow);
  }

  // restore old pen/brush to avoid gdi resource leak
  dc.SelectObject(pOldPen);
  dc.SelectObject(pOldBrush);

	// Do not call CSliderCtrl::OnPaint() for painting messages
}


void CVolumeSliderCtrl::SetPos(int nPos)
{
  if (!m_bDragging)
  {
    if ((nPos >= m_knMin) && (nPos <= m_knMax))
    {
      m_nPos = nPos;
    }
    Invalidate();
  }
}


int CVolumeSliderCtrl::GetPos(void)
{
  return m_nPos;
}


void CVolumeSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (GetThumbRect().PtInRect(point))
	{
    m_bDragging = TRUE;
		SetCapture();
		SetFocus();
		// RedrawWindow();
		// CSliderCtrl::OnLButtonDown(nFlags, point);
	}
  else
  {
    m_bDragging = TRUE;
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


void CVolumeSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
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


void CVolumeSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd* w = GetCapture();
	if(w && w->m_hWnd == m_hWnd && (nFlags & MK_LBUTTON))
  {
    // RedrawWindow();
    MoveThumb(point);
    Invalidate();
    // CSliderCtrl::OnMouseMove(nFlags, point);
  }
}


CRect CVolumeSliderCtrl::GetChannelRect(void)
{
  CRect r;

  GetClientRect(&r);

  // r.DeflateRect(0, 2);
  // r.DeflateRect(0, 3, m_knThumbWidth / 2, 4);
  // r.bottom = r.top + 20;

  return (r);
}


CRect CVolumeSliderCtrl::GetThumbRect(void)
{
  CRect r, rcClient;

  GetClientRect(&rcClient);
  r = GetChannelRect();

  // r.DeflateRect(0, 3, m_knThumbWidth / 2, 4);

  int nHalfHeight;

  int x = r.left + (int)((r.Width() - m_knThumbWidth) * m_nPos / 100);
  int y = r.CenterPoint().y;

  nHalfHeight = r.Height() / 2;

  r.SetRect(x, y, x, y);
  r.InflateRect(0, nHalfHeight, m_knThumbWidth, nHalfHeight);

  // r.bottom += 5;

  return (r);
}


void CVolumeSliderCtrl::MoveThumb(CPoint point)
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
/*
    if (m_nPos > 95)
    {
      m_nPos = 100;
    }
*/
    // SetPos((int)(point.x * 100 / r.Width()));
  }
}


BOOL CVolumeSliderCtrl::OnEraseBkgnd(CDC* pDC) 
{
  return TRUE;
  	
	// return CSliderCtrl::OnEraseBkgnd(pDC);
}

void CVolumeSliderCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CSliderCtrl::OnSetFocus(pOldWnd);
	
	AfxGetMainWnd()->SetFocus(); // don't focus on us, parents will take care of our positioning	
}
