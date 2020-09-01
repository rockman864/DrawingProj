
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
	//������DC����ʾ���濽����Ŀ��DC������ʾ����Ļ
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
		//1)��������DC,�ҽ�����1��
		m_dcCompatible.CreateCompatibleDC(&dc);
		//2����������λͼ
		CRect DrawRangle;
		GetClientRect(&DrawRangle);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, DrawRangle.Width(), DrawRangle.Height());
		//3��ѡ��λͼ����ȷ����ʾ�����С���Ӷ������ڼ���DC�ϻ�ͼ
		m_dcCompatible.SelectObject(&bitmap);
		//4)��ԭʼDC�е���ɫ����������ݿ鸴�Ƶ�����DC
		m_dcCompatible.BitBlt(0, 0, DrawRangle.Width(), DrawRangle.Height(), &dc, 0, 0, SRCCOPY);

		m_dcCompatible.SelectObject(pBrush);
	}
	switch (m_GraphInfo.GetDrawType())//���ݲ˵������ڼ���DC�ϻ�ͼ
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
	//������Ч�������ػ����
	Invalidate(TRUE);
	////������ʾ�滭����
	UpdateWindow();
	CView::OnLButtonUp(nFlags, point);
}
