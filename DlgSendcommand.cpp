// DlgSendcommand.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "DlgSendcommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSendcommand dialog


CDlgSendcommand::CDlgSendcommand(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSendcommand::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSendcommand)
	m_strSendCommand = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSendcommand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSendcommand)
	DDX_Text(pDX, IDC_EDIT_SENDCOMMAND, m_strSendCommand);
	DDV_MaxChars(pDX, m_strSendCommand, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSendcommand, CDialog)
	//{{AFX_MSG_MAP(CDlgSendcommand)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSendcommand message handlers

void CDlgSendcommand::GetCommand(CString strCommand)
{
  strCommand = m_strSendCommand;
}

