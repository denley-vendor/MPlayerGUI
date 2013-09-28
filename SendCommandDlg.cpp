// SendCommandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "SendCommandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendCommandDlg dialog


CSendCommandDlg::CSendCommandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendCommandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendCommandDlg)
	m_strCommand = _T("");
	//}}AFX_DATA_INIT
}


void CSendCommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendCommandDlg)
	DDX_Text(pDX, IDC_EDIT_SENDCOMMAND, m_strCommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendCommandDlg, CDialog)
	//{{AFX_MSG_MAP(CSendCommandDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendCommandDlg message handlers

void CSendCommandDlg::GetCommand(CString &strCommand)
{
  strCommand = m_strCommand;
}
