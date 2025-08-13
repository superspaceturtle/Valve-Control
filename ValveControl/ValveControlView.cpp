
// ValveControlView.cpp : implementation of the CValveControlView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ValveControl.h"
#endif

#include "ValveControlDoc.h"
#include "ValveControlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CValveControlView

IMPLEMENT_DYNCREATE(CValveControlView, CView)

BEGIN_MESSAGE_MAP(CValveControlView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CValveControlView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CValveControlView construction/destruction

CValveControlView::CValveControlView() noexcept
{
	// TODO: add construction code here

}

CValveControlView::~CValveControlView()
{
}

BOOL CValveControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CValveControlView drawing

void CValveControlView::OnDraw(CDC* pDC)
{
	CValveControlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CString csText;
	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	pOldPen = pDC->SelectObject(&pen);


	csText.Format(_T("%d"), slider);
}


// CValveControlView printing


void CValveControlView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CValveControlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CValveControlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CValveControlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CValveControlView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CValveControlView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CValveControlView diagnostics

#ifdef _DEBUG
void CValveControlView::AssertValid() const
{
	CView::AssertValid();
}

void CValveControlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CValveControlDoc* CValveControlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CValveControlDoc)));
	return (CValveControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CValveControlView message handlers

void CValveControlView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_pControlDlg = new ControlDlg();
	m_pControlDlg->Create(IDD_DIALOG1, this);
	m_pControlDlg->ShowWindow(SW_SHOW);
}
