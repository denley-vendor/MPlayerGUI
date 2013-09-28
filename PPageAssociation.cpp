// PPageAssociation.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PPageAssociation.h"

#include "cgfiltyp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageAssociation property page

IMPLEMENT_DYNCREATE(CPPageAssociation, CPropertyPage)

CPPageAssociation::CPPageAssociation() : CPropertyPage(CPPageAssociation::IDD)
{
	//{{AFX_DATA_INIT(CPPageAssociation)
	m_strExtensions = _T("");
	//}}AFX_DATA_INIT
  
  char szAppPath[MAX_PATH] = "";

  // Get the Module pathname
  ::GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);
  m_strApp = szAppPath;
}

CPPageAssociation::~CPPageAssociation()
{
}

void CPPageAssociation::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageAssociation)
	DDX_Control(pDX, IDC_EDIT_EXTENSIONS, m_Edit_Extensions);
	DDX_Text(pDX, IDC_EDIT_EXTENSIONS, m_strExtensions);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageAssociation, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageAssociation)
	ON_BN_CLICKED(IDC_BUTTON_EXT_LOAD, OnButtonExtLoad)
	ON_BN_CLICKED(IDC_BUTTON_EXT_ASSOCIATE, OnButtonExtAssociate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageAssociation message handlers

void CPPageAssociation::OnButtonExtLoad() 
{
  // define filters for use with the file dialog
  const char fileDialogFilter[] = "text files (*.txt)|*.txt||";
  const char fileDialogExt[] = "txt";
  CString strPathName;

  CString strTemp;
  CStdioFile file;

  UpdateData(TRUE);

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
      // Reset
      m_strExtensions = _T("");

      if (!file.Open(strPathName, CFile::modeRead | CFile::typeText))
      {
        MessageBox("unable to open file");
        return;
      }

      while (file.ReadString(strTemp))
      {
        strTemp.TrimLeft();
        strTemp.TrimRight();

        if (strTemp.GetLength() > 0)
        {
          m_strExtensions += strTemp;
          m_strExtensions += _T("\r\n");
        }
      }

      UpdateData(FALSE);
    }
  }
}

void CPPageAssociation::OnButtonExtAssociate() 
{
  int i;
  int nLineCount, nLen;
  CString strText, strLine; 
  BOOL bError;
  CString strError;
  int nCount;

  bError = FALSE;
  strError = _T("Failed to Associate:\n\n");
  nCount = 0;

  UpdateData(TRUE);

  nLineCount = m_Edit_Extensions.GetLineCount();	

  for  (i = 0; i < nLineCount; i++) 
  { 
    //  length  of  line  i: 
    nLen = m_Edit_Extensions.LineLength(m_Edit_Extensions.LineIndex(i)); 
    m_Edit_Extensions.GetLine(i, strText.GetBuffer(nLen), nLen); 
    strText.ReleaseBuffer(nLen); 

    strText.TrimLeft();
    strText.TrimRight();

    if (strText.GetLength() > 0)
    {
      if (AssociateWithExtension(strText))
      {
        // strSummary += strText + _T("\r\n");
        nCount++;
      }
      else
      {
        bError = TRUE;
        strError += strText + _T("\n");
      }
    }
  }

  // MessageBox(strSummary);

  if (bError)
  {
    MessageBox(strError);
  }
  else
  {
    if (nCount > 0)
    {
      MessageBox("Succeed!");
    }
    else
    {
      MessageBox("No action.");
    }
  }
}


BOOL CPPageAssociation::AssociateWithExtension(CString strExtension)
{
  // AfxMessageBox(strExtension);
  CGCFileTypeAccess TheFTA;

  CString csTempText;
  TheFTA.SetExtension(_T(strExtension));

  // just pass file path in quotes on command line
  csTempText  = m_strApp;
  csTempText += " \"%1\"";
  TheFTA.SetShellOpenCommand(csTempText);
  TheFTA.SetDocumentShellOpenCommand(csTempText);
  TheFTA.SetDocumentClassName("MPlayerGUI.Document");

  // use second icon in program
  csTempText  = m_strApp;
  csTempText += ",1";
  TheFTA.SetDocumentDefaultIcon(csTempText);

  // set the necessary registry entries	
  TheFTA.RegSetAllInfo();

  return TRUE;
}


