// ClipPropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPlayerGUI.h"
#include "ClipPropertyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipPropertyDlg dialog


CClipPropertyDlg::CClipPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipPropertyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClipPropertyDlg)
	m_strAudioInfo_Bitrate = _T("");
	m_strAudioInfo_Codec = _T("");
	m_strAudioInfo_Format = _T("");
	m_strAudioInfo_Rate = _T("");
	m_strClipInfo_Length = _T("");
	m_strVideoInfo_Bitrate = _T("");
	m_strVideoInfo_Codec = _T("");
	m_strVideoInfo_FPS = _T("");
	m_strVideoInfo_Height = _T("");
	m_strVideoInfo_Width = _T("");
	m_strAudioInfo_NCH = _T("");
	m_strClipInfo_Album = _T("");
	m_strClipInfo_Artist = _T("");
	m_strClipInfo_Title = _T("");
	m_strClipInfo_Genre = _T("");
	//}}AFX_DATA_INIT
}


void CClipPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipPropertyDlg)
	DDX_Text(pDX, IDC_EDIT_ABITRATE, m_strAudioInfo_Bitrate);
	DDX_Text(pDX, IDC_EDIT_ACODEC, m_strAudioInfo_Codec);
	DDX_Text(pDX, IDC_EDIT_AFORMAT, m_strAudioInfo_Format);
	DDX_Text(pDX, IDC_EDIT_ARATE, m_strAudioInfo_Rate);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_strClipInfo_Length);
	DDX_Text(pDX, IDC_EDIT_VBITRATE, m_strVideoInfo_Bitrate);
	DDX_Text(pDX, IDC_EDIT_VCODEC, m_strVideoInfo_Codec);
	DDX_Text(pDX, IDC_EDIT_VFPS, m_strVideoInfo_FPS);
	DDX_Text(pDX, IDC_EDIT_VHEIGHT, m_strVideoInfo_Height);
	DDX_Text(pDX, IDC_EDIT_VWIDTH, m_strVideoInfo_Width);
	DDX_Text(pDX, IDC_EDIT_NCH, m_strAudioInfo_NCH);
	DDX_Text(pDX, IDC_EDIT_ALBUM, m_strClipInfo_Album);
	DDX_Text(pDX, IDC_EDIT_ARTIST, m_strClipInfo_Artist);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strClipInfo_Title);
	DDX_Text(pDX, IDC_EDIT_GENRE, m_strClipInfo_Genre);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClipPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CClipPropertyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipPropertyDlg message handlers
