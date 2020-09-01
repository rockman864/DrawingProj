
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

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);
	//将兼容DC的显示表面拷贝到目的DC，即显示到屏幕
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcCompatible, 0, 0, SRCCOPY);
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
	CClientDC dc(this);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	if (!m_dcCompatible.m_hDC)
	{
		//1)创建兼容DC,且仅创建1个
		m_dcCompatible.CreateCompatibleDC(&dc);
		//2）创建兼容位图
		CRect DrawRangle;
		GetClientRect(&DrawRangle);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, DrawRangle.Width(), DrawRangle.Height());
		//3）选入位图，来确定显示表面大小，从而可以在兼容DC上画图
		m_dcCompatible.SelectObject(&bitmap);
		//4)将原始DC中的颜色表和像素数据块复制到兼容DC
		m_dcCompatible.BitBlt(0, 0, DrawRangle.Width(), DrawRangle.Height(), &dc, 0, 0, SRCCOPY);

		m_dcCompatible.SelectObject(pBrush);
	}
	switch (m_GraphInfo.GetDrawType())//根据菜单命令在兼容DC上画图
	{
	case CGraph::EN_RECT:
	{
		CRect rect(m_GraphInfo.GetBeginPoint(), m_GraphInfo.GetEndPont());
		m_dcCompatible.Rectangle(&rect);
		break;
	}
	case CGraph::EN_LINE:
	{
		m_dcCompatible.MoveTo(m_GraphInfo.GetBeginPoint());
		m_dcCompatible.LineTo(m_GraphInfo.GetEndPont());
		break;
	}

	case CGraph::EN_ELLIPSE:
	{
		CRect Ellipse(m_GraphInfo.GetBeginPoint(), m_GraphInfo.GetEndPont());
		m_dcCompatible.Ellipse(&Ellipse);
		break;
	}
	default:
		break;
	}
	//窗口无效，引发重绘操作
	Invalidate(TRUE);
	////立即显示绘画内容
	UpdateWindow();
	CView::OnLButtonUp(nFlags, point);
}
