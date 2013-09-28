// Definition of general functions

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "stdafx.h"

int OS_GetMajorVersion(void);

// Translate Time (in Seconds) to Hours:Minutes:Seconds
class CTimeSplitter
{
public:
  CTimeSplitter(void);
  ~CTimeSplitter(void);
  void SetTime(long lTime);
  int GetHours(void) const;
  int GetMinutes(void) const;
  int GetSeconds(void) const;

private:
  int m_nHours, m_nMinutes, m_nSeconds;
  long m_lTime;
};


#endif
