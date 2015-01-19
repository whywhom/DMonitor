// ColorStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic( )
{
	m_clrBack = RGB(0xFF, 0x00, 0x00);//
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CColorStatic 消息处理程序




void CColorStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CRect rect;
	this->GetClientRect(&rect);
	CBrush brush(m_clrBack);
	dc.FillRect(rect,&brush);
}

void CColorStatic::SetStaiticColor(COLORREF color)
{
	m_clrBack = color;
	CWnd::Invalidate();
}

HBRUSH CColorStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
