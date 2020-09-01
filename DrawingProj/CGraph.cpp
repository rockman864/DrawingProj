#include "pch.h"
#include "CGraph.h"
IMPLEMENT_SERIAL(CGraph, CObject, 1)
CGraph::CGraph(CPoint ptBegin, CPoint ptEnd, int DrawType)
{
    this->m_ptBegin = ptBegin;
    this->m_ptEnd = ptEnd;
    this->m_DrawType = DrawType;
}

CGraph::CGraph(void)
{
    m_DrawType = 0;
}

CGraph::~CGraph(void)
{
}

void CGraph::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << m_DrawType << m_ptBegin << m_ptEnd;
    }
    else
    {
        ar >> m_DrawType >> m_ptBegin >> m_ptEnd;
    }
}

void CGraph::SetDrawType(int nType)
{
    m_DrawType = nType;
}

void CGraph::SetBeginPoint(CPoint ptBegin)
{
    m_ptBegin = ptBegin;
}

void CGraph::SetEndPont(CPoint ptEnd)
{
    m_ptEnd = ptEnd;
}

CPoint CGraph::GetBeginPoint()
{
    return m_ptBegin;
}

CPoint CGraph::GetEndPont()
{
    return m_ptEnd;
}

int CGraph::GetDrawType()
{
    return m_DrawType;
}

CGraph* CGraph::CreateGraphObj()
{
    CGraph* pObj = NULL;

    try
    {
        pObj = new CGraph(m_ptBegin, m_ptEnd, m_DrawType);
    }
    catch (...)
    {
        return NULL;
    }

    return pObj;
}

void CGraph::DrawItem(CDC* pDC)
{
    CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
    CBrush* pOldBrush = pDC->SelectObject(pBrush);
    //»­Í¼Ñ¡Ôñ
    switch (m_DrawType)
    {
    case CGraph::EN_RECT:
    {
        pDC->Rectangle(CRect(m_ptBegin, m_ptEnd));
        break;
    }

    case CGraph::EN_LINE:
    {
        pDC->MoveTo(m_ptBegin);
        pDC->LineTo(m_ptEnd);
        break;
    }

    case CGraph::EN_ELLIPSE:
    {
        pDC->Ellipse(CRect(m_ptBegin, m_ptEnd));
        break;
    }

    default:
        break;
    }

    pDC->SelectObject(pOldBrush);
}
