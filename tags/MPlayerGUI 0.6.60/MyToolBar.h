#ifndef CMYTOOLBAR_H
#define CMYTOOLBAR_H

#include "VolumeSliderCtrl.h"

class CMyToolBar : public CToolBar
{
public:
  CMyToolBar();
  virtual ~CMyToolBar();
  void SetSliderVolume(int nPos);
  int GetSliderVolume(void);

public:
  void ArrangeControls();
  CVolumeSliderCtrl m_Slider_Volume;

  BOOL Create(CWnd *pParentWnd);

protected:
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

  DECLARE_MESSAGE_MAP()
};

#endif
