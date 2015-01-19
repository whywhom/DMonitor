// ColorStatic.cpp : ʵ���ļ�
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



// CColorStatic ��Ϣ�������




void CColorStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
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

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
