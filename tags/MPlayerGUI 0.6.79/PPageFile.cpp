// PPageFile.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageFile property page

IMPLEMENT_DYNCREATE(CPPageFile, CPropertyPage)

CPPageFile::CPPageFile() : CPropertyPage(CPPageFile::IDD)
{
	//{{AFX_DATA_INIT(CPPageFile)
	m_strAspectRatio = _T("");
	m_strAudioCodec = _T("");
	m_strBitRate = _T("");
	m_strLength = _T("");
	m_strLocation = _T("");
	m_strMediaType = _T("");
	m_strVideoCodec = _T("");
	m_strVideoSize = _T("");
	//}}AFX_DATA_INIT
}

CPPageFile::~CPPageFile()
{
}

void CPPageFile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageFile)
	DDX_Text(pDX, IDC_EDIT_FILE_ASPECTRATIO, m_strAspectRatio);
	DDX_Text(pDX, IDC_EDIT_FILE_AUDIOCODEC, m_strAudioCodec);
	DDX_Text(pDX, IDC_EDIT_FILE_BITRATE, m_strBitRate);
	DDX_Text(pDX, IDC_EDIT_FILE_LENGTH, m_strLength);
	DDX_Text(pDX, IDC_EDIT_FILE_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_FILE_MEDIATYPE, m_strMediaType);
	DDX_Text(pDX, IDC_EDIT_FILE_VIDEOCODEC, m_strVideoCodec);
	DDX_Text(pDX, IDC_EDIT_FILE_VIDEOSIZE, m_strVideoSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageFile)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageFile message handlers
