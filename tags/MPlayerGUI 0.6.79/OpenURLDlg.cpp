// OpenURLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "OpenURLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenURLDlg dialog


COpenURLDlg::COpenURLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenURLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenURLDlg)
	m_strOpenURL = _T("");
	//}}AFX_DATA_INIT
}


void COpenURLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenURLDlg)
	DDX_Text(pDX, IDC_OPENURL, m_strOpenURL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenURLDlg, CDialog)
	//{{AFX_MSG_MAP(COpenURLDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenURLDlg message handlers
