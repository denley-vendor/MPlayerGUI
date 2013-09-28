// MPlayerGUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MPlayerGUI.h"

#include "LimitSingleInstance.h"

// AppSettings
#ifndef APPSETTINGS_H
#include "AppSettings.h"
#endif

#include "MainFrm.h"
#include "MPlayerGUIDoc.h"
#include "MPlayerGUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// The one and only CLimitSingleInstance object.
// Change what is passed to constructor. GUIDGEN Tool may be of help.
CLimitSingleInstance g_SingleInstanceObj(TEXT("Global\\{94215F8F-937A-4c53-B66C-73CD520C83C1}"));

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIApp

BEGIN_MESSAGE_MAP(CMPlayerGUIApp, CWinApp)
	//{{AFX_MSG_MAP(CMPlayerGUIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIApp construction

CMPlayerGUIApp::CMPlayerGUIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMPlayerGUIApp object

CMPlayerGUIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIApp initialization

BOOL CMPlayerGUIApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
  WNDCLASS wndcls;
  memset(&wndcls, 0, sizeof(WNDCLASS));
  wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
  wndcls.lpfnWndProc = ::DefWindowProc; 
  wndcls.hInstance = AfxGetInstanceHandle();
  wndcls.hIcon = LoadIcon(IDR_MAINFRAME);
  wndcls.hCursor = LoadCursor(IDC_ARROW);
  wndcls.hbrBackground = 0; //(HBRUSH)(COLOR_WINDOW + 1);
  // no bkg brush, the view and the bars should always fill the whole client area
  wndcls.lpszMenuName = NULL;
  wndcls.lpszClassName = MPLAYERGUI_WND_CLASS_NAME;

  if(!AfxRegisterClass(&wndcls))
  {
    AfxMessageBox(_T("MainFrm class registration failed!"));
    return FALSE;
  }

  CAppSettings MyAppSettings;
  BOOL bAllowMultipleInstances;

  bAllowMultipleInstances = MyAppSettings.ReadBoolean("bAllowMultipleInstances", FALSE);

  if ((!bAllowMultipleInstances) && (g_SingleInstanceObj.IsAnotherInstanceRunning()))
  {
    HWND hwndPrevious = ::FindWindow(MPLAYERGUI_WND_CLASS_NAME, NULL);

#if 0 // don't SetForegroundWindow(), annoying
    if (hwndPrevious)
	    SetForegroundWindow(hwndPrevious);

    if (IsIconic(hwndPrevious))
      ShowWindow(hwndPrevious, SW_RESTORE);
#endif

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
    
    // if (1)
    if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
    {
      // DoFileOpen(_T(cmdInfo.m_strFileName));
      CString strDataToSend;
      strDataToSend = _T(cmdInfo.m_strFileName);
      // strDataToSend = _T("Message To You :)");

      COPYDATASTRUCT cpd;
      cpd.dwData = 0;
      cpd.cbData = strDataToSend.GetLength() + 1;
      cpd.lpData = (void*)strDataToSend.GetBuffer(cpd.cbData);
      SendMessage(hwndPrevious, WM_COPYDATA,
                                (WPARAM)AfxGetApp()->m_pMainWnd->GetSafeHwnd(),
                                (LPARAM)&cpd);
      strDataToSend.ReleaseBuffer();
    }

    return FALSE;
	}


	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	// SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	// LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)
  // no touch of the registry!

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMPlayerGUIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMPlayerGUIView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMPlayerGUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIApp commands
