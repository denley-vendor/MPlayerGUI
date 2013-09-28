// PPageOutput.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageOutput property page

IMPLEMENT_DYNCREATE(CPPageOutput, CPropertyPage)

CPPageOutput::CPPageOutput() : CPropertyPage(CPPageOutput::IDD)
{
	//{{AFX_DATA_INIT(CPPageOutput)
	m_nAudioOutputDriver = -1;
	m_nVideoOutputDriver = -1;
	//}}AFX_DATA_INIT
}

CPPageOutput::~CPPageOutput()
{
}

void CPPageOutput::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageOutput)
	DDX_CBIndex(pDX, IDC_COMBO_AUDIOOUTPUTDRIVER, m_nAudioOutputDriver);
	DDX_CBIndex(pDX, IDC_COMBO_VIDEOOUTPUTDRIVER, m_nVideoOutputDriver);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageOutput, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageOutput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageOutput message handlers
