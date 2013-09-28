// PPageSubtitles.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageSubtitles.h"

#include "XFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageSubtitles property page

IMPLEMENT_DYNCREATE(CPPageSubtitles, CPropertyPage)

CPPageSubtitles::CPPageSubtitles() : CPropertyPage(CPPageSubtitles::IDD)
{
	//{{AFX_DATA_INIT(CPPageSubtitles)
	m_bAutoloadSubtitles = FALSE;
	m_strSubtitleFont = _T("");
	m_nSubCP = -1;
	//}}AFX_DATA_INIT
}

CPPageSubtitles::~CPPageSubtitles()
{
}

void CPPageSubtitles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSubtitles)
	DDX_Check(pDX, IDC_CHECK_AUTOLOADSUB, m_bAutoloadSubtitles);
	DDX_Text(pDX, IDC_EDIT_FONTPATHNAME, m_strSubtitleFont);
	DDX_CBIndex(pDX, IDC_COMBO_SUBCP, m_nSubCP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageSubtitles, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageSubtitles)
	ON_BN_CLICKED(IDC_BUTTON_PICKFONT, OnButtonPickfont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSubtitles message handlers

void CPPageSubtitles::OnButtonPickfont() 
{
  LOGFONT lf;
  TCHAR szDisplayName[1000], szFontFile[1000];

  CFontDialog dlg(NULL,
    CF_SCREENFONTS | CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCALABLEONLY | CF_NOVECTORFONTS | CF_TTONLY);

  if (dlg.DoModal() == IDOK)
  {
    dlg.GetCurrentFont(&lf);

    if (GetFontFile(lf.lfFaceName, szDisplayName, 1000, szFontFile, 1000))
    {
      TCHAR szWinDir[_MAX_PATH*2];
      ::GetWindowsDirectory(szWinDir, _MAX_PATH);

      CString strFontFilePath = szWinDir;
      strFontFilePath += _T("\\FONTS\\");
      strFontFilePath += szFontFile;

      UpdateData(TRUE);
      m_strSubtitleFont = strFontFilePath;
      UpdateData(FALSE);
    }
    else
    {
      MessageBox("Sorry, Font File Not Found!");
    }
  }
}
