#if !defined(AFX_LOGDLG_H__BD2B8932_B119_434F_8F08_3AB6ABF07012__INCLUDED_)
#define AFX_LOGDLG_H__BD2B8932_B119_434F_8F08_3AB6ABF07012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog

class CLogDlg : public CDialog
{
// Construction
public:
	CLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogDlg)
	enum { IDD = IDD_LOG };
	CEdit	m_Edit_Log;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
  void Log(CString strLog);
  void Reset(void);


private:
  int m_nHardLimit;

  void DeleteFirstLine(void);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLogReset();
	//}}AFX_MSG

  virtual void OnOK();
  virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGDLG_H__BD2B8932_B119_434F_8F08_3AB6ABF07012__INCLUDED_)
