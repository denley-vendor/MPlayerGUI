// ResizeableFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ResizeableFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeableFileDialog

IMPLEMENT_DYNAMIC(CResizeableFileDialog, CFileDialog)

CResizeableFileDialog::CResizeableFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CResizeableFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CResizeableFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CResizeableFileDialog::OnInitDialog() 
{    
    if((GetParent()->GetStyle() & WS_THICKFRAME) == 0) //cancel own resize logic for by-system resizeable cases
    {
        GetParent()->ModifyStyle(0, /* WS_MAXIMIZEBOX |*/ WS_THICKFRAME);
        
        CMenu* pMenu = GetParent()->GetSystemMenu(FALSE);
        if (pMenu)
        {
            pMenu->InsertMenu(0, MF_BYPOSITION | MF_STRING, SC_SIZE, "&Size");
            //pMenu->AppendMenu(MF_STRING,SC_RESTORE,"Restore");
            //pMenu->AppendMenu(MF_STRING,SC_MAXIMIZE,"Maximize");
        }
        
        CWnd *pParent = GetParent();
        BOOL bulo = ParentWnd.SubclassWindow(pParent->GetSafeHwnd());
    }

	CFileDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CResizeableFileDialogParentWnd dialog


CResizeableFileDialogParentWnd::CResizeableFileDialogParentWnd(CWnd* pParent /*=NULL*/)
	: CCommonDialog(/* removed: ParentWnd::IDD,*/ pParent)
{
	//{{AFX_DATA_INIT(CResizeableFileDialogParentWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_minWidth = m_minHeight = 0;
    m_bMinInfo = false;
	m_CanResize = false;
}


void CResizeableFileDialogParentWnd::DoDataExchange(CDataExchange* pDX)
{
	CCommonDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizeableFileDialogParentWnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizeableFileDialogParentWnd, CCommonDialog)
	//{{AFX_MSG_MAP(CResizeableFileDialogParentWnd)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_SIZING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeableFileDialogParentWnd message handlers

void CResizeableFileDialogParentWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    CCommonDialog::OnGetMinMaxInfo(lpMMI);

    if (m_bMinInfo)
    {
        lpMMI->ptMinTrackSize.x = m_minWidth;
        lpMMI->ptMinTrackSize.y = m_minHeight;
    }
}

void CResizeableFileDialogParentWnd::ResizeChild(CWnd *pWnd, int dx, int dy, int Anchore)
{
	CRect WndRect;

	pWnd->GetWindowRect(&WndRect);  ScreenToClient(&WndRect);
	
	//InvalidateRect(WndRect);
	
	if(Anchore & RESIZE_HOR)
		WndRect.right += dx;
	else if(Anchore & ANCHORE_RIGHT)
		WndRect.OffsetRect(dx,0);
	
	if(Anchore & RESIZE_VER)
		WndRect.bottom += dy;
	else if(Anchore & ANCHORE_BOTTOM)
		WndRect.OffsetRect(0,dy);
	
	pWnd->MoveWindow(&WndRect);
}

void CResizeableFileDialogParentWnd::OnSize(UINT nType, int cx, int cy) 
{
	CCommonDialog::OnSize(nType, cx, cy);
	
	if(m_CanResize)
	{
        int dx = cx - m_OldX;
        int dy = cy - m_OldY;
        
        CWnd *pWnd;
        
        //Find list control's rect
        CRect Rect;
        CRect LCRect;
        for(pWnd = GetTopWindow(); pWnd;)
        {
            pWnd->GetWindowRect(&Rect);
            
            if((pWnd == GetTopWindow())
                || (LCRect.Width() * LCRect.Height() < Rect.Width() * Rect.Height()))
            {
                LCRect = Rect;
            }
            
            pWnd = pWnd->GetNextWindow();
        }
        
		// Move and Size the controls
        for(pWnd = GetTopWindow(); pWnd;)
        {
            pWnd->GetWindowRect(&Rect);

            int Anchore = ANCHORE_LEFT | ANCHORE_TOP;
            
            if(Rect == LCRect)
            {
                //list ctrl
                Anchore = RESIZE_BOTH;
            }
            else
            {
                if(Rect.bottom > LCRect.top)
                {
                    //item under
                    Anchore = ANCHORE_BOTTOM;
                }

                if(Rect.left > LCRect.right)
                {
                    //item at right size
                    Anchore = ANCHORE_RIGHT;
                }
            }

            ResizeChild(pWnd, dx, dy, Anchore);
            
            pWnd = pWnd->GetNextWindow();
        }

        RedrawWindow(NULL, NULL, /* RDW_UPDATENOW | RDW_ERASE |*/ RDW_INVALIDATE | RDW_ALLCHILDREN);
    }

	m_OldX = cx;
	m_OldY = cy;
}

void CResizeableFileDialogParentWnd::OnSizing(UINT fwSide, LPRECT pRect) 
{
    m_CanResize = true;

    if (m_bMinInfo == false) // first time
	{
        CRect rect;
        GetWindowRect(rect);
        m_minWidth = rect.Width();
        m_minHeight = rect.Height();

        m_bMinInfo = true;
    }

    CCommonDialog::OnSizing(fwSide, pRect);
}
