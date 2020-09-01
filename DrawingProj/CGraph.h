#pragma once
class CGraph:public CObject
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
    virtual void Serialize(CArchive& ar);
public:
    void SetDrawType(int nType);
    void SetBeginPoint(CPoint ptBegin);
    void SetEndPont(CPoint ptEnd);
    CPoint GetBeginPoint();
    CPoint GetEndPont();
    int GetDrawType();
    CGraph* CreateGraphObj();
    void  DrawItem(CDC* pDC);
private:
    CPoint m_ptBegin;
    CPoint m_ptEnd;
    int   m_DrawType;
};

