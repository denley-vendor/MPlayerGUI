// Implementation of the CPlaybackPosition Class
// The CPlaybackPosition is build on top of CIniFile
// To provide a convenienced way to save and load playback positions
#include "stdafx.h"
#include "PlaybackPosition.h"


// Constuction of the CPlaybackPosition Class
// Actually the core function, which set the path and name of the INI file
CPlaybackPosition::CPlaybackPosition(void)
{
  CString strAppDirectory, strIniFileName;
  char szAppPath[MAX_PATH] = "";

  // Get the Module pathname, ex: "D:\App\MediaPlayer\MPlayerGUI\MPlayerGUI.exe"
  ::GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);

  // Extract directory from pathname, ex: "D:\App\MediaPlayer\MPlayerGUI"
  strAppDirectory = szAppPath;
  strAppDirectory = strAppDirectory.Left(strAppDirectory.ReverseFind('\\'));

  // Makeup the INI filename, ex: "D:\App\MediaPlayer\MPlayerGUI\PlaybackPosition.ini"
  strIniFileName.Format("%s\\PlaybackPosition.ini", _T(strAppDirectory));

  // Set the INI filename
  m_IniFile.SetIniFile(strIniFileName);

  // Set the Section, which is fixed to "PlaybackPosition"
  m_IniFile.SetSection("PlaybackPosition");
}


// Deconstruction of the CPlaybackPosition Class
CPlaybackPosition::~CPlaybackPosition(void)
{
  // nothing to do
}


// All functions call corresponding CIniFile functions do the real job
int CPlaybackPosition::ReadInteger(CString strKey, int nDefaultValue)
{
  return m_IniFile.ReadInteger(strKey, nDefaultValue);
}


float CPlaybackPosition::ReadFloat(CString strKey, float fDefaultValue)
{
  return m_IniFile.ReadFloat(strKey, fDefaultValue);
}


BOOL CPlaybackPosition::ReadBoolean(CString strKey, BOOL bDefaultValue)
{
  return m_IniFile.ReadBoolean(strKey, bDefaultValue);
}


void CPlaybackPosition::ReadString(CString strKey, CString &strResult, CString strDefaultValue)
{
  m_IniFile.ReadString(strKey, strResult, strDefaultValue);
}


BOOL CPlaybackPosition::WriteInteger(CString strKey, int nValue)
{
  return m_IniFile.WriteInteger(strKey, nValue);
}


BOOL CPlaybackPosition::WriteFloat(CString strKey, float fValue)
{
  return m_IniFile.WriteFloat(strKey, fValue);
}


BOOL CPlaybackPosition::WriteBoolean(CString strKey, BOOL bValue)
{
  return m_IniFile.WriteBoolean(strKey, bValue);
}


BOOL CPlaybackPosition::WriteString(CString strKey, CString strValue)
{
  return m_IniFile.WriteString(strKey, strValue);
}


BOOL CPlaybackPosition::DeleteKey(CString strKey)
{
  return m_IniFile.DeleteKey(strKey);
}


