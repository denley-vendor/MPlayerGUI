// PPageAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageAdvanced property page

IMPLEMENT_DYNCREATE(CPPageAdvanced, CPropertyPage)

CPPageAdvanced::CPPageAdvanced() : CPropertyPage(CPPageAdvanced::IDD)
{
	//{{AFX_DATA_INIT(CPPageAdvanced)
	m_strMPlayerUserConfig = _T("");
	m_nMPlayerPriority = -1;
	m_bDisableMPlayerMonitor = FALSE;
	m_bEnableLogging = FALSE;
	//}}AFX_DATA_INIT
}

CPPageAdvanced::~CPPageAdvanced()
{
}

void CPPageAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageAdvanced)
	DDX_Text(pDX, IDC_EDIT_MPLAYER_USER_CONFIG, m_strMPlayerUserConfig);
	DDX_CBIndex(pDX, IDC_COMBO_MPLAYER_PRIORITY, m_nMPlayerPriority);
	DDX_Check(pDX, IDC_CHECK_DISABLEMPLAYERMONITOR, m_bDisableMPlayerMonitor);
	DDX_Check(pDX, IDC_CHECK_ENABLELOGGING, m_bEnableLogging);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageAdvanced, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageAdvanced)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageAdvanced message handlers
