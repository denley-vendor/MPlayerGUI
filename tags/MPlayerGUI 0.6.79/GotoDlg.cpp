// GotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "GotoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg dialog


CGotoDlg::CGotoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoDlg)
	m_strGoto_Hours = _T("");
	m_strGoto_Minutes = _T("");
	m_strGoto_Seconds = _T("");
	//}}AFX_DATA_INIT
}


void CGotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoDlg)
	DDX_Control(pDX, IDC_SPIN_S, m_Spin_S);
	DDX_Control(pDX, IDC_SPIN_M, m_Spin_M);
	DDX_Control(pDX, IDC_SPIN_H, m_Spin_H);
	DDX_Text(pDX, IDC_EDIT_GOTO_H, m_strGoto_Hours);
	DDV_MaxChars(pDX, m_strGoto_Hours, 2);
	DDX_Text(pDX, IDC_EDIT_GOTO_M, m_strGoto_Minutes);
	DDV_MaxChars(pDX, m_strGoto_Minutes, 2);
	DDX_Text(pDX, IDC_EDIT_GOTO_S, m_strGoto_Seconds);
	DDV_MaxChars(pDX, m_strGoto_Seconds, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoDlg, CDialog)
	//{{AFX_MSG_MAP(CGotoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg message handlers

BOOL CGotoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_strGoto_Hours = "00";
  m_strGoto_Minutes = "00";
  m_strGoto_Seconds = "00";

  m_Spin_H.SetRange(0, 99);
  m_Spin_M.SetRange(0, 59);
  m_Spin_S.SetRange(0, 59);

  UpdateData(FALSE);
  	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CGotoDlg::GetHours(void)
{
  int nHours;

  // UpdateData(TRUE);

  sscanf(m_strGoto_Hours, "%d", &nHours);

  return nHours;
}

int CGotoDlg::GetMinutes(void)
{
  int nMinutes;

  // UpdateData(TRUE);

  sscanf(m_strGoto_Minutes, "%d", &nMinutes);

  return nMinutes;
}

int CGotoDlg::GetSeconds(void)
{
  int nSeconds;

  // UpdateData(TRUE);

  sscanf(m_strGoto_Seconds, "%d", &nSeconds);

  return nSeconds;
}

