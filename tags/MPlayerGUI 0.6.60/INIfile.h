// Definition of the CIniFile class

#ifndef INIFILE_H
#define INIFILE_H

#include "stdafx.h"

class CIniFile
{
private:
  CString m_strFileName, m_strSection;

public:
  CIniFile();
  ~CIniFile();

  void SetIniFile(CString strFileName);
  void SetSection(CString strSection);

  int ReadInteger(CString strKey, int nDefaultValue = 0);
  float ReadFloat(CString strKey, float fDefaultValue = 0);
  BOOL ReadBoolean(CString strKey, BOOL bDefaultValue = FALSE);
  void ReadString(CString strKey, CString &strResult, CString strDefaultValue = "");

  BOOL WriteInteger(CString strKey, int nValue);
  BOOL WriteFloat(CString strKey, float fValue);
  BOOL WriteBoolean(CString strKey, BOOL bValue);
  BOOL WriteString(CString strKey, CString strValue);
};

#endif
