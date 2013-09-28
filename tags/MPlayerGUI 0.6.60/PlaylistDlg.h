#if !defined(AFX_PLAYLISTDLG_H__511E3294_FE95_4819_94D6_1F22D2665790__INCLUDED_)
#define AFX_PLAYLISTDLG_H__511E3294_FE95_4819_94D6_1F22D2665790__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PlaylistDlg.h : header file
//

#include "DragAndDropListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPlaylistDlg dialog

class CPlaylistDlg : public CDialog
{
// Construction
public:
	CPlaylistDlg(CWnd* pParent = NULL);   // standard constructor

  void GetFileToPlay(CString &strFileToPlay);
  int  RequestNextFile(void);
  int  RequestPreviousFile(void);
  int  RewindPlayList(void);

  int AddPlayListEntry(CString strEntry);

  void DoPlayListRemove(void);
  void DoPlayListRemoveAll(void);
  void DoPlayListAdd(void);
  void DoPlayListPlay(void);
  void DoPlayListMoveDown(void);
  void DoPlayListMoveUp(void);

  void LoadPlayList(CString strFileName);
  void SavePlayList(CString strFileName);
  void SwapListItem(int nFirst, int nSecond);

  void PlayFromFirst(void);
  void Shuffle(void);
  void DoPlaylistSort(void);

  afx_msg void OnDropFiles(HDROP hDropInfo);

private:
  CString m_strFileToPlay;
  int m_nCurrentPlayIndex;

protected:
  void SetExtendListbox(void);


public:
// Dialog Data
	//{{AFX_DATA(CPlaylistDlg)
	enum { IDD = IDD_PLAYLIST };
	// CListBox	m_Listbox_Playlist;
  CDragAndDropListBox m_Listbox_Playlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaylistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaylistDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListPlaylist();
	afx_msg void OnButtonPlAdd();
	afx_msg void OnButtonPlRemove();
	afx_msg void OnButtonPlRemoveall();
	afx_msg void OnButtonPlStartplay();
	afx_msg void OnButtonPlLoad();
	afx_msg void OnButtonPlShuffle();
	afx_msg void OnButtonPlSave();
	afx_msg void OnButtonPlSort();
	//}}AFX_MSG

  virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTDLG_H__511E3294_FE95_4819_94D6_1F22D2665790__INCLUDED_)
