// PPagePath.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPagePath.h"

// Folder Browser
// #include "FolderDialog.h"

#include "PathInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPagePath property page

IMPLEMENT_DYNCREATE(CPPagePath, CPropertyPage)

CPPagePath::CPPagePath() : CPropertyPage(CPPagePath::IDD)
{
	//{{AFX_DATA_INIT(CPPagePath)
	m_nUseDefault = -1;
	m_strMPlayerPathName = _T("");
	//}}AFX_DATA_INIT

  m_strAppDirectory = _T("");
}

CPPagePath::~CPPagePath()
{
}

void CPPagePath::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPagePath)
	DDX_Radio(pDX, IDC_RADIO_USEDEFAULTPATH, m_nUseDefault);
	DDX_Text(pDX, IDC_EDIT_MPLAYER_PATHNAME, m_strMPlayerPathName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPagePath, CPropertyPage)
	//{{AFX_MSG_MAP(CPPagePath)
	ON_BN_CLICKED(IDC_BUTTON_PATHNAMEBROWSE, OnButtonPathnamebrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPagePath message handlers

/*
void CPPagePath::OnButtonPathbrowse() 
{
  CFolderDialog folderDlg(NULL, NULL, this);
  CString strPath;

  // get values from controls to variables
  // otherwise, the UpdateData(FALSE) will set radio button to previous state
  UpdateData(TRUE);

  if (folderDlg.DoModal() == IDOK)
  {
    // strPath.Format("%s", chPath);
    // MessageBox(szPath);
    // strPath = dirDialog.m_strPath;
    m_strMPlayerPath = folderDlg.GetPathName();
    UpdateData(FALSE);
  }
}
*/

void CPPagePath::OnButtonPathnamebrowse() 
{
  // define filters for use with the file dialog
  const char fileDialogFilter[] = "executable file (*.exe)|*.exe||";
  const char fileDialogExt[] = "exe";
  CString strPathName;
  CString strRelPath;

  CFileDialog fileDialog(TRUE,
    fileDialogExt,
    NULL,
    OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_READONLY,
    fileDialogFilter);

  if (fileDialog.DoModal() == IDOK)
  {
    strPathName = fileDialog.GetPathName();
    strPathName.TrimLeft();
    strPathName.TrimRight();

    if (strPathName.GetLength() > 0)
    {
      strRelPath = m_strAppDirectory + _T("\\"); // for PathInfo
      // Get relative pathname if possible
      m_strMPlayerPathName = PathInfo::getRelPath(strPathName, strRelPath);
      // m_strMPlayerPathName = strPathName;

      UpdateData(FALSE);
    }
  }	
}
