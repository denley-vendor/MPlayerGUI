// Implementation of the CAppSettings Class
// The CAppSettings is build on top of CIniFile
// To provide a convenienced way to save and load settings for MPlayerGUI
#include "stdafx.h"
#include "AppSettings.h"


// Constuction of the CAppSettings Class
// Actually the core function, which set the path and name of the INI file
CAppSettings::CAppSettings(void)
{
  CString strAppDirectory, strIniFileName;
  char szAppPath[MAX_PATH] = "";

  // Get the Module pathname, ex: "D:\App\MediaPlayer\MPlayerGUI\MPlayerGUI.exe"
  ::GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);

  // Extract directory from pathname, ex: "D:\App\MediaPlayer\MPlayerGUI"
  strAppDirectory = szAppPath;
  strAppDirectory = strAppDirectory.Left(strAppDirectory.ReverseFind('\\'));

  // Makeup the INI filename, ex: "D:\App\MediaPlayer\MPlayerGUI\MPlayerGUI.ini"
  strIniFileName.Format("%s\\MPlayerGUI.ini", _T(strAppDirectory));

  // Set the INI filename
  m_IniFile.SetIniFile(strIniFileName);

  // Set the Section, which is fixed to "MPlayerGUI"
  m_IniFile.SetSection("MPlayerGUI");
}


// Deconstruction of the CAppSettings Class
CAppSettings::~CAppSettings(void)
{
  // nothing to do
}


// All functions call corresponding CIniFile functions do the real job
int CAppSettings::ReadInteger(CString strKey, int nDefaultValue)
{
  return m_IniFile.ReadInteger(strKey, nDefaultValue);
}


float CAppSettings::ReadFloat(CString strKey, float fDefaultValue)
{
  return m_IniFile.ReadFloat(strKey, fDefaultValue);
}


BOOL CAppSettings::ReadBoolean(CString strKey, BOOL bDefaultValue)
{
  return m_IniFile.ReadBoolean(strKey, bDefaultValue);
}


void CAppSettings::ReadString(CString strKey, CString &strResult, CString strDefaultValue)
{
  m_IniFile.ReadString(strKey, strResult, strDefaultValue);
}


BOOL CAppSettings::WriteInteger(CString strKey, int nValue)
{
  return m_IniFile.WriteInteger(strKey, nValue);
}


BOOL CAppSettings::WriteFloat(CString strKey, float fValue)
{
  return m_IniFile.WriteFloat(strKey, fValue);
}


BOOL CAppSettings::WriteBoolean(CString strKey, BOOL bValue)
{
  return m_IniFile.WriteBoolean(strKey, bValue);
}


BOOL CAppSettings::WriteString(CString strKey, CString strValue)
{
  return m_IniFile.WriteString(strKey, strValue);
}

