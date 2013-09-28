// MPlayerGUIDoc.h : interface of the CMPlayerGUIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPLAYERGUIDOC_H__CDE4D3A1_B29B_4D3D_AF3D_0FB33F2F3923__INCLUDED_)
#define AFX_MPLAYERGUIDOC_H__CDE4D3A1_B29B_4D3D_AF3D_0FB33F2F3923__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMPlayerGUIDoc : public CDocument
{
protected: // create from serialization only
	CMPlayerGUIDoc();
	DECLARE_DYNCREATE(CMPlayerGUIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPlayerGUIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMPlayerGUIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMPlayerGUIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPLAYERGUIDOC_H__CDE4D3A1_B29B_4D3D_AF3D_0FB33F2F3923__INCLUDED_)
