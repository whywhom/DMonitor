// LimitEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "LimitEdit.h"


// CLimitEdit

IMPLEMENT_DYNAMIC(CLimitEdit, CEdit)

CLimitEdit::CLimitEdit()
{

}

CLimitEdit::~CLimitEdit()
{
}


BEGIN_MESSAGE_MAP(CLimitEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CLimitEdit 消息处理程序




void CLimitEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar == 0x30 || nChar == 0x31 || nChar == 0x32 || nChar == 0x33 || nChar == 0x34 
		|| nChar == 0x35 || nChar == 0x36 || nChar == 0x37 || nChar == 0x38 || nChar == 0x39 
		|| nChar == 0x2E/*.*/ || nChar == 0x2D/*-*/ || nChar == 0x08 /*退格*/)
	{
		
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		return;
	}
	
}
