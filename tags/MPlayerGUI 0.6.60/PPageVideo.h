#if !defined(AFX_PPAGEVIDEO_H__5F47153A_3A5A_4D4D_A0AA_C12232579C2E__INCLUDED_)
#define AFX_PPAGEVIDEO_H__5F47153A_3A5A_4D4D_A0AA_C12232579C2E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPageVideo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageVideo dialog

class CPPageVideo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageVideo)

// Construction
public:
	CPPageVideo();
	~CPPageVideo();

// Dialog Data
	//{{AFX_DATA(CPPageVideo)
	enum { IDD = IDD_PROPPAGE_VIDEO };
	CSliderCtrl	m_SliderVideoSaturation;
	CSliderCtrl	m_SliderVideoHue;
	CSliderCtrl	m_SliderVideoContrast;
	CSliderCtrl	m_SliderVideoBrightness;
	int		m_nBrightness;
	int		m_nHue;
	int		m_nSaturation;
	int		m_nContrast;
	BOOL	m_bDoubleBuffering;
	//}}AFX_DATA

  int GetVideoBrightness(void);
  int GetVideoContrast(void);
  int GetVideoHue(void);
  int GetVideoSaturation(void);

  void SetVideoBrightness(int nBrightness);
  void SetVideoContrast(int nContrast);
  void SetVideoHue(int nHue);
  void SetVideoSaturation(int nSaturation);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageVideo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageVideo)
	afx_msg void OnButtonVideoReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEVIDEO_H__5F47153A_3A5A_4D4D_A0AA_C12232579C2E__INCLUDED_)
