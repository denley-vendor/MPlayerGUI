///////////////////////////////////////////////////////////////////////////////
//
//  FileName: SSDisabler.h
//  Creator:  Jason Yang
//  Date:     
//  Comment:  Definition of the CSSDisabler class
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SSDISABLER_H
#define _SSDISABLER_H

#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////////
//
//  ClassName: CSSDisabler
//  Creator:   Jason Yang
//  Date:      
//  Comment:   Screen saver, power saver disabler and restorer
//
///////////////////////////////////////////////////////////////////////////////
class CSSDisabler
{
private:
  int m_nLowPower;
  int m_nPowerOff;
  int m_nScreenSaver;

public:
  CSSDisabler(void);
  ~CSSDisabler(void);

  void Disable(void);
  void Restore(void);
};

#endif
