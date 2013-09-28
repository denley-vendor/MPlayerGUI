// PPageCommands.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageCommands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageCommands property page

IMPLEMENT_DYNCREATE(CPPageCommands, CPropertyPage)

CPPageCommands::CPPageCommands() : CPropertyPage(CPPageCommands::IDD)
{
	//{{AFX_DATA_INIT(CPPageCommands)
	m_strF1CMD = _T("");
	m_strF2CMD = _T("");
	m_strF3CMD = _T("");
	m_strF4CMD = _T("");
	m_strF5CMD = _T("");
	m_strF6CMD = _T("");
	m_strF7CMD = _T("");
	m_strF8CMD = _T("");
	//}}AFX_DATA_INIT
}

CPPageCommands::~CPPageCommands()
{
}

void CPPageCommands::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageCommands)
	DDX_Text(pDX, IDC_EDIT_F1CMD, m_strF1CMD);
	DDX_Text(pDX, IDC_EDIT_F2CMD, m_strF2CMD);
	DDX_Text(pDX, IDC_EDIT_F3CMD, m_strF3CMD);
	DDX_Text(pDX, IDC_EDIT_F4CMD, m_strF4CMD);
	DDX_Text(pDX, IDC_EDIT_F5CMD, m_strF5CMD);
	DDX_Text(pDX, IDC_EDIT_F6CMD, m_strF6CMD);
	DDX_Text(pDX, IDC_EDIT_F7CMD, m_strF7CMD);
	DDX_Text(pDX, IDC_EDIT_F8CMD, m_strF8CMD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageCommands, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageCommands)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageCommands message handlers
