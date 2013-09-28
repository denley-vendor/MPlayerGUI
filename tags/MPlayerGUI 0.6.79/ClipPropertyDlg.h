#if !defined(AFX_CLIPPROPERTYDLG_H__30CE738A_7688_4C54_B249_0FE7AD730277__INCLUDED_)
#define AFX_CLIPPROPERTYDLG_H__30CE738A_7688_4C54_B249_0FE7AD730277__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClipPropertyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClipPropertyDlg dialog

class CClipPropertyDlg : public CDialog
{
// Construction
public:
	CClipPropertyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClipPropertyDlg)
	enum { IDD = IDD_CLIP_PROPERTY };
	CString	m_strAudioInfo_Bitrate;
	CString	m_strAudioInfo_Codec;
	CString	m_strAudioInfo_Format;
	CString	m_strAudioInfo_Rate;
	CString	m_strClipInfo_Length;
	CString	m_strVideoInfo_Bitrate;
	CString	m_strVideoInfo_Codec;
	CString	m_strVideoInfo_FPS;
	CString	m_strVideoInfo_Height;
	CString	m_strVideoInfo_Width;
	CString	m_strAudioInfo_NCH;
	CString	m_strClipInfo_Album;
	CString	m_strClipInfo_Artist;
	CString	m_strClipInfo_Title;
	CString	m_strClipInfo_Genre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipPropertyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClipPropertyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPPROPERTYDLG_H__30CE738A_7688_4C54_B249_0FE7AD730277__INCLUDED_)
