// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "LogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog


CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_Edit_Log);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	//{{AFX_MSG_MAP(CLogDlg)
	ON_BN_CLICKED(IDC_BUTTON_LOG_RESET, OnButtonLogReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg message handlers

void CLogDlg::OnCancel() 
{
	CDialog::OnCancel();
  AfxGetApp()->m_pMainWnd->PostMessage(UWM_LOG_DLG_HIDE, 0, 0);
  // DestroyWindow();
}

void CLogDlg::OnOK() 
{
  CDialog::OnOK();
  AfxGetApp()->m_pMainWnd->PostMessage(UWM_LOG_DLG_HIDE, 0, 0);
}


BOOL CLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_nHardLimit = 200;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CLogDlg::Log(CString strLog)
{
  if (m_Edit_Log.GetLineCount() > m_nHardLimit)
  {
    DeleteFirstLine();
    // Reset();
  }

  m_Edit_Log.SetRedraw(FALSE);
  m_Edit_Log.SetSel(m_Edit_Log.GetWindowTextLength(), -1);

  strLog += _T("\r\n");
  m_Edit_Log.ReplaceSel(_T(strLog));
  m_Edit_Log.SetRedraw(TRUE);

}


void CLogDlg::DeleteFirstLine(void)
{
  m_Edit_Log.SetRedraw(FALSE);
  m_Edit_Log.SetSel(m_Edit_Log.LineIndex(0), m_Edit_Log.LineIndex(1));
  m_Edit_Log.ReplaceSel("");
  m_Edit_Log.SetSel(m_Edit_Log.GetWindowTextLength(), -1);
  // m_Edit_Log.SetSel(-1, -1);
  m_Edit_Log.SetRedraw(TRUE);
}


void CLogDlg::Reset(void)
{
  m_Edit_Log.SetSel(0, -1);
  m_Edit_Log.Clear();
}

void CLogDlg::OnButtonLogReset() 
{
	Reset();
}
