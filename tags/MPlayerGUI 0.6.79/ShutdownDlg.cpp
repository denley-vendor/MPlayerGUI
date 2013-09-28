// ShutdownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "ShutdownDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShutdownDlg dialog


#define TIMER_ONE_SECOND 1


CShutdownDlg::CShutdownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShutdownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShutdownDlg)
	m_strShutdownCounter = _T("");
	//}}AFX_DATA_INIT
}


void CShutdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShutdownDlg)
	DDX_Text(pDX, IDC_EDIT_SHUTDOWN_COUNTER, m_strShutdownCounter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShutdownDlg, CDialog)
	//{{AFX_MSG_MAP(CShutdownDlg)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShutdownDlg message handlers

BOOL CShutdownDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  SetTimer(TIMER_ONE_SECOND, 1000, NULL);

  m_nCounter = 30;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShutdownDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
  KillTimer(TIMER_ONE_SECOND);
}

void CShutdownDlg::OnTimer(UINT nIDEvent) 
{
  switch (nIDEvent)
  {
	  case TIMER_ONE_SECOND:
    {
      m_strShutdownCounter.Format("%d", m_nCounter);
      UpdateData(FALSE);

      m_nCounter--;

      if (m_nCounter < 0)
      {
        KillTimer(TIMER_ONE_SECOND);
        DoShutdown();
      }
    }
    default:
    {
      break;
    }
  }

	CDialog::OnTimer(nIDEvent);
}

void CShutdownDlg::DoShutdown(void)
{
  // Windows 98 need .Shutdown() here, strange...
  m_Logoff.Poweroff();
}

