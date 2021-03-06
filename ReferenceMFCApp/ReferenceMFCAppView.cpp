
// ReferenceMFCAppView.cpp : implementation of the CReferenceMFCAppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ReferenceMFCApp.h"
#endif

#include "ReferenceMFCAppDoc.h"
#include "ReferenceMFCAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReferenceMFCAppView

IMPLEMENT_DYNCREATE(CReferenceMFCAppView, CView)

BEGIN_MESSAGE_MAP(CReferenceMFCAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CReferenceMFCAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CReferenceMFCAppView construction/destruction

CReferenceMFCAppView::CReferenceMFCAppView()
{
	// TODO: add construction code here

}

CReferenceMFCAppView::~CReferenceMFCAppView()
{
}

BOOL CReferenceMFCAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CReferenceMFCAppView drawing

void CReferenceMFCAppView::OnDraw(CDC* /*pDC*/)
{
	CReferenceMFCAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CReferenceMFCAppView printing


void CReferenceMFCAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CReferenceMFCAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReferenceMFCAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReferenceMFCAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CReferenceMFCAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CReferenceMFCAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CReferenceMFCAppView diagnostics

#ifdef _DEBUG
void CReferenceMFCAppView::AssertValid() const
{
	CView::AssertValid();
}

void CReferenceMFCAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReferenceMFCAppDoc* CReferenceMFCAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReferenceMFCAppDoc)));
	return (CReferenceMFCAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CReferenceMFCAppView message handlers
