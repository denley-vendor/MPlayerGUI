// PPageVideo.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageVideo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageVideo property page

IMPLEMENT_DYNCREATE(CPPageVideo, CPropertyPage)

CPPageVideo::CPPageVideo() : CPropertyPage(CPPageVideo::IDD)
{
	//{{AFX_DATA_INIT(CPPageVideo)
	m_nBrightness = 0;
	m_nHue = 0;
	m_nSaturation = 0;
	m_nContrast = 0;
	m_bDoubleBuffering = FALSE;
	//}}AFX_DATA_INIT
}

CPPageVideo::~CPPageVideo()
{
}

void CPPageVideo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageVideo)
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_SliderVideoSaturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_SliderVideoHue);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_SliderVideoContrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_SliderVideoBrightness);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_nBrightness);
	DDX_Text(pDX, IDC_EDIT_HUE, m_nHue);
	DDX_Text(pDX, IDC_EDIT_SATURATION, m_nSaturation);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_nContrast);
	DDX_Check(pDX, IDC_CHECK_DOUBLEBUFFERING, m_bDoubleBuffering);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageVideo, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageVideo)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_RESET, OnButtonVideoReset)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageVideo message handlers

void CPPageVideo::OnButtonVideoReset() 
{
  m_SliderVideoBrightness.SetPos(0);
  m_SliderVideoContrast.SetPos(0);
  m_SliderVideoHue.SetPos(0);
  m_SliderVideoSaturation.SetPos(0);

  m_nBrightness = m_nContrast = m_nHue = m_nSaturation = 0;

  UpdateData(FALSE);
}

BOOL CPPageVideo::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

  m_SliderVideoBrightness.SetLineSize(1);
  m_SliderVideoBrightness.SetPageSize(10);
  m_SliderVideoBrightness.SetRange(-100, 100, TRUE);
  m_SliderVideoBrightness.SetPos(0);

  m_SliderVideoContrast.SetLineSize(1);
  m_SliderVideoContrast.SetPageSize(10);
  m_SliderVideoContrast.SetRange(-100, 100, TRUE);
  m_SliderVideoContrast.SetPos(0);

  m_SliderVideoHue.SetLineSize(1);
  m_SliderVideoHue.SetPageSize(10);
  m_SliderVideoHue.SetRange(-100, 100, TRUE);
  m_SliderVideoHue.SetPos(0);

  m_SliderVideoSaturation.SetLineSize(1);
  m_SliderVideoSaturation.SetPageSize(10);
  m_SliderVideoSaturation.SetRange(-100, 100, TRUE);
  m_SliderVideoSaturation.SetPos(0);

  // Should be set in SetXXXXX() already
  // m_nBrightness = m_nContrast = m_nHue = m_nSaturation = 0;
  m_SliderVideoBrightness.SetPos(m_nBrightness);
  m_SliderVideoContrast.SetPos(m_nContrast);
  m_SliderVideoHue.SetPos(m_nHue);
  m_SliderVideoSaturation.SetPos(m_nSaturation);

  UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


int CPPageVideo::GetVideoBrightness(void)
{
  return m_nBrightness;
}

int CPPageVideo::GetVideoContrast(void)
{
  return m_nContrast;
}

int CPPageVideo::GetVideoHue(void)
{
  return m_nHue;
}

int CPPageVideo::GetVideoSaturation(void)
{
  return m_nSaturation;
}

void CPPageVideo::SetVideoBrightness(int nBrightness)
{
  if ((nBrightness < -100) || (nBrightness > 100))
    m_nBrightness = 0;
  else
    m_nBrightness = nBrightness;

  // m_SliderVideoBrightness.SetPos(m_nBrightness);
  // UpdateData(FALSE);
}

void CPPageVideo::SetVideoContrast(int nContrast)
{
  if ((nContrast < -100) || (nContrast > 100))
    m_nContrast = 0;
  else
    m_nContrast = nContrast;

  // m_SliderVideoContrast.SetPos(m_nContrast);
  // UpdateData(FALSE);
}

void CPPageVideo::SetVideoHue(int nHue)
{
  if ((nHue < -100) || (nHue > 100))
    m_nHue = 0;
  else
    m_nHue = nHue;

  // m_SliderVideoHue.SetPos(m_nHue);
  // UpdateData(FALSE);
}

void CPPageVideo::SetVideoSaturation(int nSaturation)
{
  if ((nSaturation < -100) || (nSaturation > 100))
    m_nSaturation = 0;
  else
    m_nSaturation = nSaturation;

  // m_SliderVideoSaturation.SetPos(m_nSaturation);
  // UpdateData(FALSE);
}

void CPPageVideo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if ((CSliderCtrl*)pScrollBar == (CSliderCtrl*)GetDlgItem(IDC_SLIDER_BRIGHTNESS))
  {
    m_nBrightness = m_SliderVideoBrightness.GetPos();
    UpdateData(FALSE);
  }

  if ((CSliderCtrl*)pScrollBar == (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST))
  {
    m_nContrast = m_SliderVideoContrast.GetPos();
    UpdateData(FALSE);
  }

  if ((CSliderCtrl*)pScrollBar == (CSliderCtrl*)GetDlgItem(IDC_SLIDER_HUE))
  {
    m_nHue = m_SliderVideoHue.GetPos();
    UpdateData(FALSE);
  }

  if ((CSliderCtrl*)pScrollBar == (CSliderCtrl*)GetDlgItem(IDC_SLIDER_SATURATION))
  {
    m_nSaturation = m_SliderVideoSaturation.GetPos();
    UpdateData(FALSE);
  }

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
