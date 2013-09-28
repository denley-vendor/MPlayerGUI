#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SeekSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVolumeSliderCtrl window

class CVolumeSliderCtrl : public CSliderCtrl
{
// Construction
public:
	CVolumeSliderCtrl();

private:
  int m_nPos;
  const int m_knMin, m_knMax;
  const int m_knThumbWidth;

  BOOL m_bDragging;

// Attributes
public:

// Operations
public:
  void SetPos(int nPos);
  int  GetPos(void);

protected:
  CRect GetChannelRect(void);
  CRect GetThumbRect(void);
  void  MoveThumb(CPoint point);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVolumeSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVolumeSliderCtrl)
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
