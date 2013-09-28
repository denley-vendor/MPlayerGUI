// CAppSettings Class
// An ini settings accessing wrapper
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include "stdafx.h"
#include "IniFile.h"


class CAppSettings
{
private:
  CIniFile m_IniFile;

public:
  CAppSettings(void);
	~CAppSettings(void);

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
};


#endif
