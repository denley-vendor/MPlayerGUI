// CPlaybackPosition Class
// An ini settings accessing wrapper
#ifndef PLAYBACKPOSITION_H
#define PLAYBACKPOSITION_H

#include "stdafx.h"
#include "IniFile.h"


class CPlaybackPosition
{
private:
  CIniFile m_IniFile;

public:
  CPlaybackPosition(void);
	~CPlaybackPosition(void);

  // Read
  int ReadInteger(CString strKey, int nDefaultValue = 0);
  float ReadFloat(CString strKey, float fDefaultValue = 0);
  BOOL ReadBoolean(CString strKey, BOOL bDefaultValue = FALSE);
  void ReadString(CString strKey, CString &strResult, CString strDefaultValue = "");

  // Write
  BOOL WriteInteger(CString strKey, int nValue);
  BOOL WriteFloat(CString strKey, float fValue);
  BOOL WriteBoolean(CString strKey, BOOL bValue);
  BOOL WriteString(CString strKey, CString strValue);

  // Delete
  BOOL DeleteKey(CString strKey);
};


#endif
