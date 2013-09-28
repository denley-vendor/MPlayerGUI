// MPlayerGUIView.h : interface of the CMPlayerGUIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPLAYERGUIVIEW_H__B4262AAE_8835_422B_A4FA_B31868403C28__INCLUDED_)
#define AFX_MPLAYERGUIVIEW_H__B4262AAE_8835_422B_A4FA_B31868403C28__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MPlayerGUIDoc.h"
#include "Label.h"

class CMPlayerGUIView : public CView
{
protected: // create from serialization only
	CMPlayerGUIView();
	DECLARE_DYNCREATE(CMPlayerGUIView)

// Attributes
public:
	CMPlayerGUIDoc* GetDocument();

public:
  HWND GetMPlayerVideoWindow(void);
  void PreparePanels(BOOL bHaveVideo);
  void SetKeepAspectRatio(BOOL bKeepAspectRatio);
  void SetVideoWidth(int nVideoWidth);
  void SetVideoHeight(int nVideoHeight);
  void KeepAspectRatio(CRect ClientRect, CRect &NewRect);
  void EnableClientEdge(BOOL bEnable);
  // void ForceVideoSize(void);
  void SetLabelInfo(CString strArtist, CString strTitle);
	// void SetLogo(int nLogoID);
  BOOL IsContextMenuShown(void);

private:
  CStatic m_LogoPanel;
  CStatic m_VideoPanel;
  // CStatic m_BlackPanel;
  CLabel m_ArtistLabel;
  CLabel m_TitleLabel;

  BOOL m_bKeepAspectRatio;
  BOOL m_bHaveVideo;
  int m_nVideoWidth;
  int m_nVideoHeight;

  BOOL m_bContextMenuShown;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPlayerGUIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMPlayerGUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMPlayerGUIView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MPlayerGUIView.cpp
inline CMPlayerGUIDoc* CMPlayerGUIView::GetDocument()
   { return (CMPlayerGUIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPLAYERGUIVIEW_H__B4262AAE_8835_422B_A4FA_B31868403C28__INCLUDED_)
