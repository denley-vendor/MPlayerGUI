#if !defined(AFX_PLAYERSTATUSBAR_H__D945E6B8_17D9_4E26_80F8_740D53164519__INCLUDED_)
#define AFX_PLAYERSTATUSBAR_H__D945E6B8_17D9_4E26_80F8_740D53164519__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PlayerStatusbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayerStatusbar dialog

#include "Label.h"

#define STATUSMODE_IDLE         0
#define STATUSMODE_LOCALMEDIA   1
#define STATUSMODE_NETMEDIA     2
#define STATUSMODE_BUFFERING    3
#define STATUSMODE_FAILED       4


class CPlayerStatusbar : public CDialogBar
{
// Construction
public:
	CPlayerStatusbar(CWnd* pParent = NULL);   // standard constructor

  void SetMessage(CString strMessage);
  void SetTime(long lCurTime);
  void SetDuration(long lTotalTime);

  void SetStatusMode(int nMode);
  void SetAudioMode(int nMode);

  void Reset(void);

  void SetFlipInfo0(CString strFlipInfo0);
  void SetFlipInfo1(CString strFlipInfo1);
  void SetFlipInfo2(CString strFlipInfo2);
  void SetFlipInfo3(CString strFlipInfo3);
  void SetFlipInfo4(CString strFlipInfo4);

  void StartFlipInfo(void);
  void StopFlipInfo(void);

  void StartBuffering(void);
  void StopBuffering(void);

protected:

  BOOL InitDialogBar(void);

  CStatic m_IconStatus, m_IconSpeakerL, m_IconSpeakerR;
  HICON m_hIconStatus, m_hIconSpeakerL, m_hIconSpeakerR;

  CLabel m_StatusLabel;
  CLabel m_TimerLabel;
  // CLabel m_DurationLabel;
  // BOOL m_bTimerShortMode;
  int m_nTimeDisplayMode;
  int m_nAudioMode;
  int m_nFlipInfoCounter;
  CString m_strFlipInfo0, m_strFlipInfo1, m_strFlipInfo2, m_strFlipInfo3, m_strFlipInfo4;
  CString m_strDuration;

  void DoFlipInfo(void);

  int m_nBufferingCounter;

  void DoBuffering(void);

  void Relayout(void);

  void SetStatusIcon(WORD wIcon);
  void SetSpeakerLIcon(WORD wIcon);
  void SetSpeakerRIcon(WORD wIcon);

  void SetStatusIcon2(HICON hIcon);
  void SetSpeakerLIcon2(HICON hIcon);
  void SetSpeakerRIcon2(HICON hIcon);

public:
// Dialog Data
	//{{AFX_DATA(CPlayerStatusbar)
	enum { IDD = IDD_PLAYER_STATUSBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerStatusbar)
	public:
	virtual BOOL Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayerStatusbar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERSTATUSBAR_H__D945E6B8_17D9_4E26_80F8_740D53164519__INCLUDED_)
