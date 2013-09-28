#if !defined(AFX_RESIZEABLEFILEDIALOG_H__4F982E62_AC05_11D4_B918_00104B47ABDF__INCLUDED_)
#define AFX_RESIZEABLEFILEDIALOG_H__4F982E62_AC05_11D4_B918_00104B47ABDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResizeableFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizeableFileDialog dialog

/////////////////////////////////////////////////////////////////////////////
// CResizeableFileDialogParentWnd dialog

#define ANCHORE_LEFT	0x0000
#define ANCHORE_TOP		0x0000
#define ANCHORE_RIGHT	0x0001
#define ANCHORE_BOTTOM	0x0002
#define	RESIZE_HOR		0x0004
#define	RESIZE_VER		0x0008
#define	RESIZE_BOTH		(RESIZE_HOR | RESIZE_VER)

class CResizeableFileDialogParentWnd : public CCommonDialog
{
// Construction
public:
	CResizeableFileDialogParentWnd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResizeableFileDialogParentWnd)
//removed:	enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeableFileDialogParentWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int	m_minWidth, m_minHeight;
    bool m_bMinInfo; // flag that GetMinMax wasn't called yet
	CDWordArray	m_ControlInfo; //list of resizeable controls
	bool m_CanResize; //can apply resize algorhytm

    //previous window size
	int m_OldX;
	int m_OldY;

	void ResizeChild(CWnd *pWnd, int dx, int dy, int Anchore);
	void SetControlInfo(WORD CtrlId, WORD Anchore);

	// Generated message map functions
	//{{AFX_MSG(CResizeableFileDialogParentWnd)
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* pMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing( UINT nSide, LPRECT lpRect );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CResizeableFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CResizeableFileDialog)

public:
	CResizeableFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

    //static LPOFNHOOKPROC pOrigHookProc;
    CResizeableFileDialogParentWnd ParentWnd;

protected:
	//{{AFX_MSG(CResizeableFileDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEABLEFILEDIALOG_H__4F982E62_AC05_11D4_B918_00104B47ABDF__INCLUDED_)
