#if !defined(AFX_PROGRESSDLGBAR_H__D8F40264_BC3C_4C46_871C_60BD26F6DB1C__INCLUDED_)
#define AFX_PROGRESSDLGBAR_H__D8F40264_BC3C_4C46_871C_60BD26F6DB1C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProgressDlgBar.h : header file
//

#include "SeekSliderCtrl.h"
#include "VolumeSliderCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressDlgBar dialog

class CProgressDlgBar : public CDialogBar
{
// Construction
public:
	CProgressDlgBar(CWnd* pParent = NULL);   // standard constructor

  BOOL InitDialogBar(void);
  void SetSliderProgress(int nPos);
  int GetSliderProgress(void);
  void EnableProgressBar(BOOL bEnable);  // enable/disable progress bar

// Dialog Data
	//{{AFX_DATA(CProgressDlgBar)
	enum { IDD = IDD_PROGRESS_DLGBAR };
	CSeekSliderCtrl	m_Slider_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlgBar)
	public:
	virtual BOOL Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlgBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLGBAR_H__D8F40264_BC3C_4C46_871C_60BD26F6DB1C__INCLUDED_)
