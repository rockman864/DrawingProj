#include "pch.h"
#include "CGraph.h"

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
