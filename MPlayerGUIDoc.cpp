// MPlayerGUIDoc.cpp : implementation of the CMPlayerGUIDoc class
//

#include "stdafx.h"
#include "MPlayerGUI.h"

#include "MPlayerGUIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIDoc

IMPLEMENT_DYNCREATE(CMPlayerGUIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMPlayerGUIDoc, CDocument)
	//{{AFX_MSG_MAP(CMPlayerGUIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIDoc construction/destruction

CMPlayerGUIDoc::CMPlayerGUIDoc()
{
	// TODO: add one-time construction code here

}

CMPlayerGUIDoc::~CMPlayerGUIDoc()
{
}

BOOL CMPlayerGUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIDoc serialization

void CMPlayerGUIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIDoc diagnostics

#ifdef _DEBUG
void CMPlayerGUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMPlayerGUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMPlayerGUIDoc commands
