#pragma once
class CGraph
{
public:
    DECLARE_SERIAL(CGraph)
    enum
    {
        EN_RECT = 0,
        EN_ELLIPSE,
        EN_LINE,
    };
    CGraph(CPoint ptBegin, CPoint ptEnd, int DrawType);
    CGraph(void);
    ~CGraph(void);
public:
    void SetDrawType(int nType);
    void SetBeginPoint(CPoint ptBegin);
    void SetEndPont(CPoint ptEnd);
    CPoint GetBeginPoint();
    CPoint GetEndPont();
    int GetDrawType();
private:
    CPoint m_ptBegin;
    CPoint m_ptEnd;
    int   m_DrawType;
};

