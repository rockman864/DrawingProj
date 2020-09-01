
// DrawingProjView.cpp : implementation of the CDrawingProjView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrawingProj.h"
#endif

#include "DrawingProjDoc.h"
#include "DrawingProjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawingProjView

IMPLEMENT_DYNCREATE(CDrawingProjView, CView)

BEGIN_MESSAGE_MAP(CDrawingProjView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Rect, &CDrawingProjView::OnRect)
	ON_COMMAND(ID_Ellipse, &CDrawingProjView::OnEllipse)
	ON_COMMAND(ID_Line, &CDrawingProjView::OnLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CDrawingProjView construction/destruction

CDrawingProjView::CDrawingProjView() noexcept
{
	// TODO: add construction code here

}

CDrawingProjView::~CDrawingProjView()
{
}

BOOL CDrawingProjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDrawingProjView drawing

void CDrawingProjView::OnDraw(CDC* pDC)
{
	CDrawingProjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int nCount = pDoc->m_obArray.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		((CGraph*)pDoc->m_obArray.GetAt(i))->DrawItem(pDC);
	}
}


// CDrawingProjView printing

BOOL CDrawingProjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawingProjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawingProjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDrawingProjView diagnostics

#ifdef _DEBUG
void CDrawingProjView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawingProjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawingProjDoc* CDrawingProjView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingProjDoc)));
	return (CDrawingProjDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingProjView message handlers


void CDrawingProjView::OnRect()
{
	// TODO: Add your command handler code here
	m_GraphInfo.SetDrawType(CGraph::EN_RECT);
}


void CDrawingProjView::OnEllipse()
{
	// TODO: Add your command handler code here
	m_GraphInfo.SetDrawType(CGraph::EN_ELLIPSE);

}


void CDrawingProjView::OnLine()
{
	// TODO: Add your command handler code here
	m_GraphInfo.SetDrawType(CGraph::EN_LINE);

}


void CDrawingProjView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_GraphInfo.SetBeginPoint(point);
	CView::OnLButtonDown(nFlags, point);
}


void CDrawingProjView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_GraphInfo.SetEndPont(point);
	CGraph* pNewGraph = m_GraphInfo.CreateGraphObj();
	if (pNewGraph != NULL)
	{
		CDrawingProjDoc* pDoc = GetDocument();
		if (pDoc != NULL)
		{
			pDoc->m_obArray.Add(pNewGraph);
		}
	}
	//引发客户窗口无效，发生重绘，
//图形能立即显示，但大量数据情况下频繁重绘效率下
	Invalidate(TRUE);
	CView::OnLButtonUp(nFlags, point);
}
