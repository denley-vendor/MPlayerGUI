#if !defined(AFX_SEEKSLIDERCTRL_H__3085FBEA_8ADE_41B1_9DA0_DC95305B2D8D__INCLUDED_)
#define AFX_SEEKSLIDERCTRL_H__3085FBEA_8ADE_41B1_9DA0_DC95305B2D8D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SeekSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeekSliderCtrl window

class CSeekSliderCtrl : public CSliderCtrl
{
// Construction
public:
	CSeekSliderCtrl();

private:
  int m_nPos;
  const int m_knMin, m_knMax;
  const int m_knThumbWidth;

  BOOL m_bDragging;
  BOOL m_bEnable;

  int m_nY;

// Attributes
public:

// Operations
public:
  void SetPos(int nPos);
  int  GetPos(void);

  void SetEnable(BOOL bEnable); // set enable/disable


protected:
  CRect GetChannelRect(void);
  CRect GetThumbRect(void);
  void  MoveThumb(CPoint point);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeekSliderCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSeekSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSeekSliderCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEEKSLIDERCTRL_H__3085FBEA_8ADE_41B1_9DA0_DC95305B2D8D__INCLUDED_)
