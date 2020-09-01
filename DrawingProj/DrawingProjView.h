
// DrawingProjView.h : interface of the CDrawingProjView class
//

#pragma once
#include "CGraph.h"

class CDrawingProjView : public CView
{
protected: // create from serialization only
	CDrawingProjView() noexcept;
	DECLARE_DYNCREATE(CDrawingProjView)

// Attributes
public:
	CDrawingProjDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDrawingProjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	CDC m_dcCompatible;
	CGraph m_GraphInfo;
public:
	afx_msg void OnRect();
	afx_msg void OnEllipse();
	afx_msg void OnLine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in DrawingProjView.cpp
inline CDrawingProjDoc* CDrawingProjView::GetDocument() const
   { return reinterpret_cast<CDrawingProjDoc*>(m_pDocument); }
#endif

