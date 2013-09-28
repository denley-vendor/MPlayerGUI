///////////////////////////////////////////////////////////////////////////////
//
//  FileName: SSDisabler.cpp
//  Creator:  Jason Yang
//  Date:     
//  Comment:  Implementation of the CSSDisabler class
//            Screen Saver Disabler, this class can be used to disable
//            screen saver and other power saver system by easy
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ssdisabler.h"

/////////////////////////////////////////////////////////////////////
//
// Remarks:
//  Construction of the CSSDisabler class
//
// Parameters:
//  [in]  
//  [out] 
//
// Return values:
//  
//
/////////////////////////////////////////////////////////////////////
CSSDisabler::CSSDisabler(void)
{
  m_nLowPower = 0;
  m_nPowerOff = 0;
  m_nScreenSaver = 0;

  // Save current status
  SystemParametersInfo(SPI_GETLOWPOWERTIMEOUT, 0, &m_nLowPower, 0);
  SystemParametersInfo(SPI_GETPOWEROFFTIMEOUT, 0, &m_nPowerOff, 0);
  SystemParametersInfo(SPI_GETSCREENSAVETIMEOUT, 0, &m_nScreenSaver, 0);
}


/////////////////////////////////////////////////////////////////////
//
// Remarks:
//  Deconstruction of CSSDisabler class
//
// Parameters:
//  [in]  
//  [out] 
//
// Return values:
//  
//
/////////////////////////////////////////////////////////////////////
CSSDisabler::~CSSDisabler(void)
{
  Restore();
}


/////////////////////////////////////////////////////////////////////
//
// Remarks:
//  Restore screen saver to previous status (before construction)
//
// Parameters:
//  [in]  
//  [out] 
//
// Return values:
//  
//
/////////////////////////////////////////////////////////////////////
void CSSDisabler::Restore(void)
{
  // Restore to previous status
  SystemParametersInfo(SPI_SETLOWPOWERTIMEOUT, m_nLowPower, NULL, 0);
  SystemParametersInfo(SPI_SETPOWEROFFTIMEOUT, m_nPowerOff, NULL, 0);
  SystemParametersInfo(SPI_SETSCREENSAVETIMEOUT, m_nScreenSaver, NULL, 0);
}


/////////////////////////////////////////////////////////////////////
//
// Remarks:
//  Disable screen saver and other power savers
//
// Parameters:
//  [in]  
//  [out] 
//
// Return values:
//  
//
/////////////////////////////////////////////////////////////////////
void CSSDisabler::Disable(void)
{
  // Disable them
  SystemParametersInfo(SPI_SETLOWPOWERTIMEOUT, 0, NULL, 0);
  SystemParametersInfo(SPI_SETPOWEROFFTIMEOUT, 0, NULL, 0);
  SystemParametersInfo(SPI_SETSCREENSAVETIMEOUT, 0, NULL, 0);
}


