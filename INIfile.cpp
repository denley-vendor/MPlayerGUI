// Implementation of the CIniFile class

#include "stdafx.h"
#include "inifile.h"

// Construction of CIniFile class
CIniFile::CIniFile()
{
  m_strFileName = "";
  m_strSection = "";
}


// Deconstruction of CIniFile class
CIniFile::~CIniFile()
{
  // nothing
}


// Set INI file name
// Parameters:
//  [in]  CString strFileName : ini file name
void CIniFile::SetIniFile(CString strFileName)
{
  m_strFileName = strFileName;
}


// Set current section of ini file
// Parameters:
//  [in]  CString strSection : current section
//  [out] 
void CIniFile::SetSection(CString strSection)
{
  m_strSection = strSection;
}


// Read Integer value from ini file
// Parameters:
//  [in]  CString strKey : key to be read
//  [in]  int nDefaultValue : default value
// Return values:
//  int : key value read
int CIniFile::ReadInteger(CString strKey, int nDefaultValue)
{
  int nResult;
  nResult = GetPrivateProfileInt(_T(m_strSection),
                                 _T(strKey),
                                 nDefaultValue,
                                 _T(m_strFileName));
  return nResult;
}


// Read Float value from ini file
// Parameters:
//  [in]  CString strKey : key to be read
//  [in]  float fDefaultValue : default value
// Return values:
//  float : key value read
float CIniFile::ReadFloat(CString strKey, float fDefaultValue)
{
  char szResult[255];
  CString strDefault;
  float fResult;

  strDefault.Format("%f", fDefaultValue);
  GetPrivateProfileString(_T(m_strSection),
                          _T(strKey),
                          _T(strDefault),
                          szResult,
                          255,
                          _T(m_strFileName));
  fResult = (float)atof(szResult);

  return fResult;
}


// Read Boolean value from ini file
// Boolean value is stored as "true"/"false" in .ini file
// Parameters:
//  [in]  CString strKey : key to be read
//  [in]  BOOL bDefaultValue : default value
// Return values:
//  BOOL : key value read
BOOL CIniFile::ReadBoolean(CString strKey, BOOL bDefaultValue)
{
  char szResult[255];
  CString strDefault;
  BOOL bResult;

  if (bDefaultValue)
  {
    strDefault = _T("true");
  }
  else
  {
    strDefault = _T("false");
  }

  GetPrivateProfileString(_T(m_strSection),
                          _T(strKey),
                          _T(strDefault),
                          szResult,
                          255,
                          _T(m_strFileName));
  bResult = (stricmp(szResult, "true") == 0) ? TRUE : FALSE;
  return bResult;
}


// Read String value from ini file
// Parameters:
//  [in]  CString strKey : key to be read
//  [in]  CString strDefaultValue : default value
//  [out] CString &strResult : key value read
void CIniFile::ReadString(CString strKey, CString &strResult, CString strDefaultValue)
{
  char szResult[255];

  GetPrivateProfileString(_T(m_strSection),
                          _T(strKey),
                          _T(strDefaultValue),
                          szResult,
                          255,
                          _T(m_strFileName));
  strResult = szResult;
}


// Write Integer value to ini file
// Parameters:
//  [in]  CString strKey : key to be write
//  [in]  int nValue : value to be write
BOOL CIniFile::WriteInteger(CString strKey, int nValue)
{
  BOOL bSuccess;
  CString strValue;

  strValue.Format("%d", nValue);
  bSuccess = WritePrivateProfileString(_T(m_strSection),
                                       _T(strKey),
                                       _T(strValue),
                                       _T(m_strFileName));
  return bSuccess;
}


// Write Float value to ini file
// Parameters:
//  [in]  CString strKey : key to be write
//  [in]  float fValue : value to be write
BOOL CIniFile::WriteFloat(CString strKey, float fValue)
{
  BOOL bSuccess;
  CString strValue;

  strValue.Format("%f", fValue);
  bSuccess = WritePrivateProfileString(_T(m_strSection),
                                       _T(strKey),
                                       _T(strValue),
                                       _T(m_strFileName));
  return bSuccess;
}


// Write Boolean value to ini file
// Boolean value is stored as "true"/"faluse" in .ini file
// Parameters:
//  [in]  CString strKey : key to be write
//  [in]  BOOL bValue : value to be write
BOOL CIniFile::WriteBoolean(CString strKey, BOOL bValue)
{
  BOOL bSuccess;
  CString strValue;

  if (bValue)
  {
    strValue = "true";
  }
  else
  {
    strValue = "false";
  }

  bSuccess = WritePrivateProfileString(_T(m_strSection),
                                       _T(strKey),
                                       _T(strValue),
                                       _T(m_strFileName));
  return bSuccess;
}


// Write String value to ini file
// Parameters:
//  [in]  CString strKey : key to be write
//  [in]  CString strValue : value to be write
BOOL CIniFile::WriteString(CString strKey, CString strValue)
{
  BOOL bSuccess;

  bSuccess = WritePrivateProfileString(_T(m_strSection),
                                       _T(strKey),
                                       _T(strValue),
                                       _T(m_strFileName));
  return bSuccess;
}


BOOL CIniFile::DeleteKey(CString strKey)
{
  BOOL bSuccess;

  bSuccess = WritePrivateProfileString(_T(m_strSection),
                                       _T(strKey),
                                       NULL,
                                       _T(m_strFileName));
  return bSuccess;
}

