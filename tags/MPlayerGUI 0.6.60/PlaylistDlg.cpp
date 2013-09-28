// PlaylistDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mplayergui.h"
#include "PlaylistDlg.h"

#include "PathInfo.h"
// #include "splitpath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PLAYLIST_HARDLIMIT 500

/////////////////////////////////////////////////////////////////////////////
// CPlaylistDlg dialog


CPlaylistDlg::CPlaylistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlaylistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlaylistDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPlaylistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlaylistDlg)
	DDX_Control(pDX, IDC_LIST_PLAYLIST, m_Listbox_Playlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlaylistDlg, CDialog)
	//{{AFX_MSG_MAP(CPlaylistDlg)
	ON_LBN_DBLCLK(IDC_LIST_PLAYLIST, OnDblclkListPlaylist)
	ON_BN_CLICKED(IDC_BUTTON_PL_ADD, OnButtonPlAdd)
	ON_BN_CLICKED(IDC_BUTTON_PL_REMOVE, OnButtonPlRemove)
	ON_BN_CLICKED(IDC_BUTTON_PL_REMOVEALL, OnButtonPlRemoveall)
	ON_BN_CLICKED(IDC_BUTTON_PL_STARTPLAY, OnButtonPlStartplay)
	ON_BN_CLICKED(IDC_BUTTON_PL_LOAD, OnButtonPlLoad)
	ON_BN_CLICKED(IDC_BUTTON_PL_SHUFFLE, OnButtonPlShuffle)
	ON_BN_CLICKED(IDC_BUTTON_PL_SAVE, OnButtonPlSave)
	ON_BN_CLICKED(IDC_BUTTON_PL_SORT, OnButtonPlSort)
	//}}AFX_MSG_MAP
  ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaylistDlg message handlers

void CPlaylistDlg::OnCancel() 
{
	CDialog::OnCancel();
  AfxGetApp()->m_pMainWnd->PostMessage(UWM_PLAYLIST_DLG_HIDE, 0, 0);
  // DestroyWindow();
}

void CPlaylistDlg::OnOK() 
{
  CDialog::OnOK();
  AfxGetApp()->m_pMainWnd->PostMessage(UWM_PLAYLIST_DLG_HIDE, 0, 0);
}

BOOL CPlaylistDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_strFileToPlay = "";
  m_nCurrentPlayIndex = 0;

  // m_Listbox_Playlist.SetHorizontalExtent(1000);
  DragAcceptFiles(TRUE); // Accept user dropped file
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlaylistDlg::GetFileToPlay(CString &strFileToPlay)
{
  strFileToPlay = m_strFileToPlay;
}


int CPlaylistDlg::RequestNextFile(void)
{
  int nCurSel, nCount;

  nCount = m_Listbox_Playlist.GetCount();

  // if playlist has no more files to be play
  if ((m_nCurrentPlayIndex + 1) >= nCount)
  {
    return -1;
  }

  // select next file in list
  m_nCurrentPlayIndex++;

  // check if the file can be selected
  if (m_Listbox_Playlist.SetCurSel(m_nCurrentPlayIndex) == LB_ERR)
  {
    return -1;
  }

  // double check the file
  nCurSel = m_Listbox_Playlist.GetCurSel();

  if (nCurSel != LB_ERR)
  {
    m_Listbox_Playlist.GetText(nCurSel, m_strFileToPlay);
  }

  return 1;
}

int CPlaylistDlg::RequestPreviousFile(void)
{
  int nCurSel, nCount;

  nCount = m_Listbox_Playlist.GetCount();

  // if current file is the first already
  if (m_nCurrentPlayIndex == 0)
  {
    return -1;
  }

  // select previous file in list
  m_nCurrentPlayIndex--;

  // check if the file can be selected
  if (m_Listbox_Playlist.SetCurSel(m_nCurrentPlayIndex) == LB_ERR)
  {
    return -1;
  }

  // double check the file
  nCurSel = m_Listbox_Playlist.GetCurSel();

  if (nCurSel != LB_ERR)
  {
    m_Listbox_Playlist.GetText(nCurSel, m_strFileToPlay);
  }

  return 1;
}

// -1 means no file in playlist
int CPlaylistDlg::RewindPlayList(void)
{
  if (m_Listbox_Playlist.SetCurSel(0) != LB_ERR)
  {
    // set the index to 0
    m_nCurrentPlayIndex = 0;
    // prepare the filename for first rewind play
    m_Listbox_Playlist.GetText(0, m_strFileToPlay);
    return 1;
  }
  else
  {
    return -1;
  }
}

int CPlaylistDlg::AddPlayListEntry(CString strEntry)
{
  int nCount;
  int nReturn;

  nReturn = 0;
  nCount = m_Listbox_Playlist.GetCount();

  if (nCount < PLAYLIST_HARDLIMIT)
  {
    m_Listbox_Playlist.AddString(strEntry);

    // set the horizontal extent
    SetExtendListbox();
    nReturn = 1;
  }
  else
  {
    nReturn = -1;
  }

  return nReturn;
}

/*
void CPlaylistDlg::DoPlayListMoveUp(void)
{
  int nCurSel;
  CString strTemp;
  
  nCurSel = m_Listbox_Playlist.GetCurSel();

  if (nCurSel == LB_ERR)
  {
    return;
  }
  
  if (nCurSel == 0)
  {
    return;
  }

  // save current text
  m_Listbox_Playlist.GetText(nCurSel, strTemp);
  // delete current
  m_Listbox_Playlist.DeleteString(nCurSel);
  // insert before current
  m_Listbox_Playlist.InsertString(nCurSel - 1, strTemp);
  // select current
  m_Listbox_Playlist.SetCurSel(nCurSel - 1);
}

void CPlaylistDlg::DoPlayListMoveDown(void)
{
  int nCurSel, nCount;
  CString strTemp;
  
  nCurSel = m_Listbox_Playlist.GetCurSel();
  nCount = m_Listbox_Playlist.GetCount();

  if (nCurSel == LB_ERR)
  {
    return;
  }
  
  if ((nCurSel + 1) == nCount)
  {
    return;
  }

  // save current text
  m_Listbox_Playlist.GetText(nCurSel, strTemp);
  // delete current
  m_Listbox_Playlist.DeleteString(nCurSel);
  // insert before current
  m_Listbox_Playlist.InsertString(nCurSel + 1, strTemp);
  // select current
  m_Listbox_Playlist.SetCurSel(nCurSel + 1);
}
*/

void CPlaylistDlg::DoPlayListPlay(void)
{
  int nCurSel;
  
  nCurSel = m_Listbox_Playlist.GetCurSel();

  if (nCurSel != LB_ERR)
  {
    // save start point to a member variable
    m_nCurrentPlayIndex = nCurSel;

    m_Listbox_Playlist.GetText(nCurSel, m_strFileToPlay);
    // inform main frame that a file is ready to be played
    AfxGetApp()->m_pMainWnd->PostMessage(UWM_PLAYLIST_PLAY, 0, 0);
  }
}

void CPlaylistDlg::DoPlayListAdd(void)
{
  // define filters for use with the file dialog
  const char fileDialogFilter[] =
    "all files (*.*)|*.*||";
  const char fileDialogExt[] = "";
  CString strFilename, strPathName;
  CString str(" ", 10000);
  POSITION pos;

  CFileDialog fileDialog(TRUE,
    fileDialogExt,
    NULL,
    OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_READONLY | OFN_ALLOWMULTISELECT,
    fileDialogFilter);

  fileDialog.m_ofn.lpstrFile = str.GetBuffer(10000);
  fileDialog.m_ofn.nMaxFile = 10000;
  str.ReleaseBuffer();

  if (fileDialog.DoModal() == IDOK)
  {
    pos = fileDialog.GetStartPosition();

    // to avoid refresh
    m_Listbox_Playlist.SetRedraw(FALSE);
    // show the wait cursor
    CWaitCursor wait;

    while (pos != NULL)
    {
      strPathName = fileDialog.GetNextPathName(pos);
      // call routine to add entry, maximum PLAYLIST_HARDLIMIT entries
      if (AddPlayListEntry(strPathName) != 1)
      {
        break;
      }
    }

    // enable drawing and make sure list box is redrawn
    m_Listbox_Playlist.SetRedraw(TRUE);
    m_Listbox_Playlist.Invalidate();
  }
}

void CPlaylistDlg::DoPlayListRemove(void)
{
  int nCurSel;

  nCurSel = m_Listbox_Playlist.GetCurSel();

  if (nCurSel != LB_ERR)
  {
    m_Listbox_Playlist.DeleteString(nCurSel);

    // set the horizontal extent
    SetExtendListbox();

    // try to select next string
    if (m_Listbox_Playlist.GetCount() > 0)
    {
      if (m_Listbox_Playlist.SetCurSel(nCurSel) == LB_ERR)
      {
        m_Listbox_Playlist.SetCurSel(nCurSel - 1);
      }
    }
  }
}

void CPlaylistDlg::DoPlayListRemoveAll(void)
{
  m_Listbox_Playlist.ResetContent();

  // set the horizontal extent
  SetExtendListbox();
}


void CPlaylistDlg::OnDblclkListPlaylist() 
{
  DoPlayListPlay();
}



void CPlaylistDlg::OnButtonPlAdd() 
{
  DoPlayListAdd();
}

/*
void CPlaylistDlg::OnButtonPlMovedown() 
{
  DoPlayListMoveDown();
}

void CPlaylistDlg::OnButtonPlMoveup() 
{
  DoPlayListMoveUp();
}
*/

void CPlaylistDlg::OnButtonPlRemove() 
{
  DoPlayListRemove();
}

void CPlaylistDlg::OnButtonPlRemoveall() 
{
  DoPlayListRemoveAll();
}

void CPlaylistDlg::OnButtonPlStartplay() 
{
  DoPlayListPlay();
}


void CPlaylistDlg::LoadPlayList(CString strFileName)
{
  CString strTemp;
  CStdioFile file;
  CString strPathPrefix;

  // reset content
  m_Listbox_Playlist.ResetContent();

  if (!file.Open(strFileName, CFile::modeRead | CFile::typeText))
  {
    MessageBox("unable to open file");
    return;
  }

  // get strFileName path (for absolute path prefix)
  // CSplitPath SplitPath = (_T(strFileName));
  // strPathPrefix = SplitPath.GetDrive() + SplitPath.GetDirectory();
  strPathPrefix = PathInfo::getDirectory(strFileName);
  // AfxMessageBox(strPathPrefix);

  // to avoid refresh
  m_Listbox_Playlist.SetRedraw(FALSE);
  // show the wait cursor
  CWaitCursor wait;

  while (file.ReadString(strTemp))
  {
    strTemp.TrimLeft();
    strTemp.TrimRight();

    if (strTemp.GetLength() > 0)
    {
      // entries preceded by '#' or ';' or '[' are comments, just ignore them
      if (strTemp.Find("#") == 0)
        continue;
      if (strTemp.Find(";") == 0)
        continue;
      if (strTemp.Find("[") == 0)
        continue;

      // no "://" found, means not a Net Radio Stream URL
      if (strTemp.Find("://") == -1)
      {
        // find ":\" in filename, if not found, means relative path
        if (strTemp.Find(":\\") == -1)
        {
          // strTemp = strPathPrefix + strTemp;
          // MessageBox(strPathPrefix);
          // convert to absolute path
          strTemp = PathInfo::getAbsPath(strTemp, strPathPrefix);
        }
      }

      // call AddPlayListEntry(), PLAYLIST_HARDLIMIT limit
      if (AddPlayListEntry(strTemp) != 1)
      {
        break;
      }
    }
  }

  // enable drawing and make sure list box is redrawn
  m_Listbox_Playlist.SetRedraw(TRUE);
  m_Listbox_Playlist.Invalidate();
}


void CPlaylistDlg::OnButtonPlLoad() 
{
  // define filters for use with the file dialog
  const char fileDialogFilter[] = "playlist files (*.txt, *.pls)|*.txt;*.pls||";
  const char fileDialogExt[] = "txt";
  CString strPathName;

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
      LoadPlayList(strPathName);
    }
  }
}

void CPlaylistDlg::OnButtonPlShuffle() 
{
  int nCount, i;
  int nFirst, nSecond;
  time_t t;

  nCount = m_Listbox_Playlist.GetCount();

  if (nCount < 2) // needless if there is only 1 or 0 item in list
    return;

  srand((unsigned)time(&t)); // set random seed

  // to avoid refresh
  m_Listbox_Playlist.SetRedraw(FALSE);
  // show the wait cursor
  CWaitCursor wait;

  /*
  for (i = 0; i < nCount / 2; i++)
  {
    nFirst = rand() % nCount;
    nSecond = rand() % nCount;

    SwapListItem(nFirst, nSecond);
  }
  */

  // New Shuffle algorithm
  for (i = 0; i < nCount - 1; i++)
  {
    nFirst = i;
    nSecond = i + 1 + rand() % nCount;

    SwapListItem(nFirst, nSecond);
  }

  // enable drawing and make sure list box is redrawn
  m_Listbox_Playlist.SetRedraw(TRUE);
  m_Listbox_Playlist.Invalidate();
}

void CPlaylistDlg::SwapListItem(int nFirst, int nSecond)
{
  int nCount;
  CString strFirst, strSecond;

  nCount = m_Listbox_Playlist.GetCount();

  // >= nCount
  if ((nFirst >= nCount) || (nSecond >= nCount)) // not in range, error
    return;

  // save the first and second text
  m_Listbox_Playlist.GetText(nFirst, strFirst);
  m_Listbox_Playlist.GetText(nSecond, strSecond);

  // remove the original first text
  m_Listbox_Playlist.DeleteString(nFirst);
  // insert the second text
  m_Listbox_Playlist.InsertString(nFirst, strSecond);
  // remove the original second text
  m_Listbox_Playlist.DeleteString(nSecond);
  // insert the first text
  m_Listbox_Playlist.InsertString(nSecond, strFirst);
}


void CPlaylistDlg::PlayFromFirst(void)
{
  int nCount;

  nCount = m_Listbox_Playlist.GetCount();

  // if there is no item in list, return immediately
  if (nCount < 1)
    return;

  // select the first one
  m_Listbox_Playlist.SetCurSel(0);

  // start play
  DoPlayListPlay();
}

void CPlaylistDlg::SetExtendListbox(void) 
{ 
  //m_lbData.SetHorizontalExtent(500); // arbitraire 

  // Find the longest string in the list box. 
  CString str; 
  CSize sz; 
  int dx = 0; 
  TEXTMETRIC tm; 
  CDC* pDC = m_Listbox_Playlist.GetDC(); 
  CFont* pFont = m_Listbox_Playlist.GetFont(); 

  // Select the listbox font, save the old font 
  CFont* pOldFont = pDC->SelectObject(pFont); 
  // Get the text metrics for avg char width 
  pDC->GetTextMetrics(&tm); 

  for (int i = 0; i < m_Listbox_Playlist.GetCount(); i++) 
  { 
    m_Listbox_Playlist.GetText(i, str); 
    sz = pDC->GetTextExtent(str); 

    // Add the avg width to prevent clipping 
    sz.cx += tm.tmAveCharWidth; 

    if (sz.cx > dx) 
      dx = sz.cx; 
  }
  // Select the old font back into the DC 
  pDC->SelectObject(pOldFont); 
  m_Listbox_Playlist.ReleaseDC(pDC); 

  // Set the horizontal extent so every character of all strings 
  // can be scrolled to. 
  m_Listbox_Playlist.SetHorizontalExtent(dx); 
}

void CPlaylistDlg::OnButtonPlSave() 
{
  // define filters for use with the file dialog
  const char fileDialogFilter[] = "playlist files (*.txt, *.pls)|*.txt;*.pls||";
  const char fileDialogExt[] = "txt";
  CString strPathName;

  CFileDialog fileDialog(FALSE,
    fileDialogExt,
    NULL,
    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    fileDialogFilter);

  if (fileDialog.DoModal() == IDOK)
  {
    strPathName = fileDialog.GetPathName();
    strPathName.TrimLeft();
    strPathName.TrimRight();

    if (strPathName.GetLength() > 0)
    {
      SavePlayList(strPathName);
    }
  }
}


void CPlaylistDlg::SavePlayList(CString strFileName)
{
  CStdioFile file;
  CString strAbsolutePathName;
  CString strRelativePath, strRelativePathName;

  // get path to be related to (eg: "D:\user\album.pls" -> "D:\user\")
  strRelativePath = PathInfo::getDirectory(strFileName);

  if (!file.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
  {
    MessageBox("unable to open file");
    return;
  }

  for (int i = 0; i < m_Listbox_Playlist.GetCount(); i++)
  { 
    // get absolute pathname from list (eg: "d:\music\1.mp3")
    m_Listbox_Playlist.GetText(i, strAbsolutePathName);
    // absolute -> relative path (eg: "music\1.mp3")
    strRelativePathName = PathInfo::getRelPath(strAbsolutePathName, strRelativePath);
    strRelativePathName += "\n";
    // save it
    file.WriteString(strRelativePathName);
  }
}

// Shuffle interface, to use protected member: OnButtonPlShuffle()
void CPlaylistDlg::Shuffle(void)
{
  OnButtonPlShuffle();
}


void CPlaylistDlg::DoPlaylistSort(void)
{
  // int i, j;
  int n;
  // BOOL bExchange;
  // CString strOne, strTwo;

  n = m_Listbox_Playlist.GetCount();

  // needless to do sort?
  if (n < 2)
    return;

  // to avoid refresh
  m_Listbox_Playlist.SetRedraw(FALSE);
  // show the wait cursor
  CWaitCursor wait;

  // Very Basic Sort algorithm
  /*
  for (i = 0; i < n - 1; i++)
  {
    bExchange = FALSE;
    for (j = n - 2; j >= i; j--)
    {
      m_Listbox_Playlist.GetText(j, strOne);
      m_Listbox_Playlist.GetText(j + 1, strTwo);

      if (strOne > strTwo)
      {
        SwapListItem(j, j + 1);
        bExchange = TRUE;
      }
    }

    if (!bExchange)
      break;
  }
  */

  // Call it's own sort algorithm
  m_Listbox_Playlist.SortList(TRUE);

  // enable drawing and make sure list box is redrawn
  m_Listbox_Playlist.SetRedraw(TRUE);
  m_Listbox_Playlist.Invalidate();
}


void CPlaylistDlg::OnButtonPlSort() 
{
  DoPlaylistSort();	
}

// Dropped file handler
void CPlaylistDlg::OnDropFiles(HDROP hDropInfo) 
{
  TCHAR szFileName[_MAX_PATH];

  UINT nFiles = ::DragQueryFile(hDropInfo, (UINT) -1, NULL, 0);

  // Empty playlist
  // DoPlayListRemoveAll();

  // Add the whole list to playlist
  for (int nIndex = 0; nIndex < nFiles; nIndex++)
  {
    ::DragQueryFile(hDropInfo, nIndex, szFileName, _MAX_PATH);
    AddPlayListEntry(szFileName);
  }

  ::DragFinish(hDropInfo);
}

