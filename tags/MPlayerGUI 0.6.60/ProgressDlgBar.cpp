// ProgressDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "MPlayerGUI.h"
#include "ProgressDlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlgBar dialog


CProgressDlgBar::CProgressDlgBar(CWnd* pParent /*=NULL*/)
	: CDialogBar(/*CProgressDlgBar::IDD, pParent*/)
{
	//{{AFX_DATA_INIT(CProgressDlgBar)
	//}}AFX_DATA_INIT
}


void CProgressDlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlgBar)
	DDX_Control(pDX, IDC_SLIDER_PROGRESS, m_Slider_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CProgressDlgBar)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlgBar message handlers

BOOL CProgressDlgBar::Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID) 
{
 BOOL bRes= CDialogBar::Create(pParentWnd,nIDTemplate,nStyle,nID);

 InitDialogBar();

 return bRes;
}

BOOL CProgressDlgBar::InitDialogBar(void)
{
  UpdateData(FALSE);

  // init the slider progress
  m_Slider_Progress.SetLineSize(1);
  m_Slider_Progress.SetPageSize(10);
  m_Slider_Progress.SetRange(0, 100);
  m_Slider_Progress.SetPos(0);

  return TRUE;
}

void CProgressDlgBar::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);
	
  if (GetDlgItem(IDC_SLIDER_PROGRESS) != NULL)
  {
    GetDlgItem(IDC_SLIDER_PROGRESS)->MoveWindow(0, 0, cx, 14);
  }
}

void CProgressDlgBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if ((CSliderCtrl*)pScrollBar == (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PROGRESS))
  {
    // only handle SB_THUMBPOSITION message
    // Up/Down, Home/End,  PageUp/Down on CSliderCtrl will send message also
    if (nSBCode == SB_THUMBPOSITION)
    {
      int nSliderPos;
      nSliderPos = m_Slider_Progress.GetPos();
      AfxGetApp()->m_pMainWnd->PostMessage(UWM_SLIDER_PROGRESS, nSliderPos, 0);
    }
  }

	CDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CProgressDlgBar::SetSliderProgress(int nPos)
{
  if (GetDlgItem(IDC_SLIDER_PROGRESS) != NULL)
  {
    if ((nPos < 0) || (nPos > 100))
    {
      nPos = 0;
    }

    m_Slider_Progress.SetPos(nPos);
  }
}

void CProgressDlgBar::EnableProgressBar(BOOL bEnable)
{
  m_Slider_Progress.SetEnable(bEnable);
}

