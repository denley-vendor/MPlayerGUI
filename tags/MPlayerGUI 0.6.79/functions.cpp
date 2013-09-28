// Implementation of general functions

#include "stdafx.h"
#include "functions.h"


// Get the operating system's major version
// Return values:
//  int  : os major version
int OS_GetMajorVersion(void)
{
  OSVERSIONINFO osvi;

  ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  GetVersionEx(&osvi);

  return osvi.dwMajorVersion;
}


CTimeSplitter::CTimeSplitter(void)
{
  m_nHours = 0;
  m_nMinutes = 0;
  m_nSeconds = 0;
  m_lTime = 0;
}

CTimeSplitter::~CTimeSplitter(void)
{
}

void CTimeSplitter::SetTime(long lTime)
{
  m_lTime = lTime;

  m_nHours = m_lTime / 3600;
  m_nMinutes = (m_lTime - m_nHours * 3600) / 60;
  m_nSeconds = m_lTime - m_nHours * 3600 - m_nMinutes * 60;
}

int CTimeSplitter::GetHours(void) const
{
  return m_nHours;
}

int CTimeSplitter::GetMinutes(void) const
{
  return m_nMinutes;
}

int CTimeSplitter::GetSeconds(void) const
{
  return m_nSeconds;
}







