// PPageContent.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageContent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageContent property page

IMPLEMENT_DYNCREATE(CPPageContent, CPropertyPage)

CPPageContent::CPPageContent() : CPropertyPage(CPPageContent::IDD)
{
	//{{AFX_DATA_INIT(CPPageContent)
	m_strAlbum = _T("");
	m_strArtist = _T("");
	m_strComments = _T("");
	m_strComposer = _T("");
	m_strCopyright = _T("");
	m_strGenre = _T("");
	m_strTitle = _T("");
	m_strRating = _T("");
	//}}AFX_DATA_INIT
}

CPPageContent::~CPPageContent()
{
}

void CPPageContent::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageContent)
	DDX_Text(pDX, IDC_EDIT_CONTENT_ALBUM, m_strAlbum);
	DDX_Text(pDX, IDC_EDIT_CONTENT_ARTIST, m_strArtist);
	DDX_Text(pDX, IDC_EDIT_CONTENT_COMMENTS, m_strComments);
	DDX_Text(pDX, IDC_EDIT_CONTENT_COMPOSER, m_strComposer);
	DDX_Text(pDX, IDC_EDIT_CONTENT_COPYRIGHT, m_strCopyright);
	DDX_Text(pDX, IDC_EDIT_CONTENT_GENRE, m_strGenre);
	DDX_Text(pDX, IDC_EDIT_CONTENT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT_RATING, m_strRating);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageContent, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageContent)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageContent message handlers
