// MPlayerGUIView.cpp : implementation of the CMPlayerGUIView class
//

#include "stdafx.h"
#include "MPlayerGUI.h"

#include "MPlayerGUIDoc.h"
#include "MPlayerGUIView.h"
#include "MainFrm.h"

// #include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIView

IMPLEMENT_DYNCREATE(CMPlayerGUIView, CView)

BEGIN_MESSAGE_MAP(CMPlayerGUIView, CView)
	//{{AFX_MSG_MAP(CMPlayerGUIView)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIView construction/destruction

CMPlayerGUIView::CMPlayerGUIView()
{
  m_bKeepAspectRatio = TRUE;
  m_bHaveVideo = FALSE;
  m_nVideoWidth = 320;
  m_nVideoHeight = 240;
  m_bContextMenuShown = FALSE;
}

CMPlayerGUIView::~CMPlayerGUIView()
{
}

BOOL CMPlayerGUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

  // cs.style &= ~WS_BORDER;
  // cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
  //    LoadCursor(IDC_HAND), HBRUSH(COLOR_WINDOW+1), NULL);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIView drawing

void CMPlayerGUIView::OnDraw(CDC* pDC)
{
	CMPlayerGUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIView diagnostics

#ifdef _DEBUG
void CMPlayerGUIView::AssertValid() const
{
	CView::AssertValid();
}

void CMPlayerGUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMPlayerGUIDoc* CMPlayerGUIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMPlayerGUIDoc)));
	return (CMPlayerGUIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIView message handlers

void CMPlayerGUIView::OnInitialUpdate() 
{
  if (m_LogoPanel.m_hWnd == NULL)
  {
    CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();

    CBitmap bmpLoad;

    m_LogoPanel.Create(_T("logo panel"), 
      WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(0, 0, 10, 10),
       this);
    bmpLoad.LoadBitmap(IDB_BITMAP_MPLAYER_LOGO);
    m_LogoPanel.SetBitmap(bmpLoad);
    bmpLoad.Detach();

    m_VideoPanel.Create(_T(""),
      WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(0, 0, 10, 10),
      this);
    bmpLoad.LoadBitmap(IDB_BITMAP_VIDEOPANEL);
    m_VideoPanel.SetBitmap(bmpLoad);
    bmpLoad.Detach();

    m_ArtistLabel.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP,
      CRect(0, 0, 10, 10), this);
    m_ArtistLabel.SetFontName("Arial");
    m_ArtistLabel.SetFontSize(14);
    m_ArtistLabel.SetFontBold(FALSE);
    m_ArtistLabel.SetTransparent(FALSE);
    m_ArtistLabel.SetTextColor(RGB(255, 255, 255));
    m_ArtistLabel.SetBkColor(RGB(0, 0, 0));
    // m_ArtistLabel.SetBkColor(RGB(100, 100, 100));
    m_ArtistLabel.SetTextEllipsis(TRUE);
    m_ArtistLabel.SetWindowText(_T(""));

    m_TitleLabel.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP,
      CRect(0, 0, 10, 10), this);
    m_TitleLabel.SetFontName("Arial");
    m_TitleLabel.SetFontSize(18);
    m_TitleLabel.SetFontBold(FALSE);
    m_TitleLabel.SetTransparent(FALSE);
    m_TitleLabel.SetTextColor(RGB(255, 255, 255));
    m_TitleLabel.SetBkColor(RGB(0, 0, 0));
    // m_TitleLabel.SetBkColor(RGB(200, 200, 200));
    m_TitleLabel.SetTextEllipsis(TRUE);
    m_TitleLabel.SetWindowText(_T(""));


    // call MainFrame.SetMPlayerVideoWindow() here to set the video window handle
    // i have no way to call this in MainFrame, no initial function like CView
    // CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
    pMainFrame->SetMPlayerVideoWindow();
    // tell main frame about to check startup openfile
    pMainFrame->SendMessage(UWM_STARTUP_OPENFILE);
  }

	CView::OnInitialUpdate();
}

void CMPlayerGUIView::SetLabelInfo(CString strArtist, CString strTitle)
{
  m_ArtistLabel.SetText(strArtist);
  m_TitleLabel.SetText(strTitle);
}

void CMPlayerGUIView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
  if (m_LogoPanel.m_hWnd != NULL)
  {
    CRect rClient, rNewRect;
    GetClientRect(&rClient);

    rNewRect = rClient;

    // only call KeepAspectRatio() when have video and user required
    if (m_bKeepAspectRatio && m_bHaveVideo)
    {
      KeepAspectRatio(rClient, rNewRect);
    }

    m_LogoPanel.MoveWindow(rNewRect);
    m_VideoPanel.MoveWindow(rNewRect);

    rNewRect.top = 0;
    rNewRect.bottom = rNewRect.top + 25;
    m_ArtistLabel.MoveWindow(rNewRect);
    
    rNewRect.top = 25;
    rNewRect.bottom = rNewRect.top + 30;
    m_TitleLabel.MoveWindow(rNewRect);
  }
}

/*
void CMPlayerGUIView::ForceVideoSize(void)
{
  if ((m_LogoPanel.m_hWnd != NULL) && (m_bHaveVideo))
  {
    CRect rClient, rNewRect;
    CPoint ptCenter;

    GetClientRect(&rClient);
    ptCenter = rClient.CenterPoint();

    if ((rClient.Width() != m_nVideoWidth) || (rClient.Height() != m_nVideoHeight))
    {
      rNewRect.left = ptCenter.x - m_nVideoWidth / 2;
      rNewRect.top = ptCenter.y - m_nVideoHeight / 2;
      rNewRect.right = rNewRect.left + m_nVideoWidth;
      rNewRect.bottom = rNewRect.top + m_nVideoHeight;

      m_VideoPanel.MoveWindow(rNewRect);
    }
  }
}
*/

HWND CMPlayerGUIView::GetMPlayerVideoWindow(void)
{
  if (m_VideoPanel.m_hWnd != NULL)
  {
    return m_VideoPanel.m_hWnd;
  }
  
  return NULL;
}


void CMPlayerGUIView::PreparePanels(BOOL bHaveVideo)
{
  CRect rClient;
  GetClientRect(&rClient);

  // save, for OnSize(), call KeepAspectRatio()?
  m_bHaveVideo = bHaveVideo;

  if (bHaveVideo)
  {
    m_LogoPanel.ShowWindow(SW_HIDE);
    m_ArtistLabel.ShowWindow(SW_HIDE);
    m_TitleLabel.ShowWindow(SW_HIDE);
    m_VideoPanel.ShowWindow(SW_SHOW);
  }
  else
  {
    m_VideoPanel.ShowWindow(SW_HIDE);
    m_LogoPanel.ShowWindow(SW_HIDE);
    m_ArtistLabel.ShowWindow(SW_SHOW);
    m_TitleLabel.ShowWindow(SW_SHOW);
  }

  m_LogoPanel.MoveWindow(rClient);
  m_VideoPanel.MoveWindow(rClient);
}

void CMPlayerGUIView::SetKeepAspectRatio(BOOL bKeepAspectRatio)
{
  m_bKeepAspectRatio = bKeepAspectRatio;
}

void CMPlayerGUIView::SetVideoWidth(int nVideoWidth)
{
  m_nVideoWidth = nVideoWidth;
}

void CMPlayerGUIView::SetVideoHeight(int nVideoHeight)
{
  m_nVideoHeight = nVideoHeight;
}

void CMPlayerGUIView::KeepAspectRatio(CRect ClientRect, CRect &NewRect)
{
  float fVideoAspect, fClientAspect;
  CPoint pointCenter;
  int nWidth, nHeight;

  NewRect = ClientRect;

  if (m_nVideoHeight > 0)
  {
    fVideoAspect = (float)m_nVideoWidth / (float)m_nVideoHeight;
  }
  else
  {
    fVideoAspect = 1;
  }

  if (ClientRect.Height() > 0)
  {
    fClientAspect = (float)ClientRect.Width() / (float)ClientRect.Height();
  }
  else
  {
    fClientAspect = 1;
  }

  pointCenter = ClientRect.CenterPoint();

  if (fClientAspect > fVideoAspect)
  {
    nWidth = (int)(fVideoAspect * ClientRect.Height());
    NewRect.left = pointCenter.x - nWidth / 2;
    NewRect.right = NewRect.left + nWidth;
  }
  else
  {
    nHeight = (int)((1.0 / fVideoAspect) * ClientRect.Width());
    NewRect.top = pointCenter.y - nHeight / 2;
    NewRect.bottom = NewRect.top + nHeight;
  }
}


void CMPlayerGUIView::EnableClientEdge(BOOL bEnable)
{
  if (bEnable)
  {
    ModifyStyleEx(0, WS_EX_CLIENTEDGE);
  }
  else
  {
    ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
  }
}

void CMPlayerGUIView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  if (point.x == -1 && point.y == -1){
    //keystroke invocation
    CRect rect;
    GetClientRect(rect);
    ClientToScreen(rect);

    point = rect.TopLeft();
    point.Offset(5, 5);
  }

  // load the menu resource
  CMenu menu;
  VERIFY(menu.LoadMenu(IDR_MENU_CONTEXT));

  // get the first sub menu
  CMenu* pPopup = menu.GetSubMenu(0);
  ASSERT(pPopup != NULL);
  CWnd* pWndPopupOwner = this;

  // jason: comments out this, or i can not handle Command Message by
  //  myself here (i mean CChessBoard class)
  // if the current owner is a CHILD Window, get it's parent window
  while (pWndPopupOwner->GetStyle() & WS_CHILD)
    pWndPopupOwner = pWndPopupOwner->GetParent();

  m_bContextMenuShown = TRUE;
  // display the popup menu at point.x, point.y and track it's selection
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
    pWndPopupOwner);	
  m_bContextMenuShown = FALSE;
}

BOOL CMPlayerGUIView::IsContextMenuShown(void)
{
  return m_bContextMenuShown;
}

BOOL CMPlayerGUIView::OnEraseBkgnd(CDC* pDC) 
{
  CRect rect;
  GetClientRect(&rect);
  pDC->FillSolidRect(rect, RGB(0, 0, 0));

  return TRUE;
  // return CView::OnEraseBkgnd(pDC);
}

void CMPlayerGUIView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
  CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
  pMainFrame->PostMessage(UWM_VIEW_MPLAYER_FULLSCREEN);

	CView::OnLButtonDblClk(nFlags, point);
}
