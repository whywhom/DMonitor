// DMonitorView.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "DMonitorView.h"
#include "afxdialogex.h"


// CDMonitorView 对话框

IMPLEMENT_DYNAMIC(CDMonitorView, CDialogEx)

CDMonitorView::CDMonitorView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDMonitorView::IDD, pParent)
{

}

CDMonitorView::~CDMonitorView()
{
}

void CDMonitorView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDMonitorView, CDialogEx)
END_MESSAGE_MAP()


// CDMonitorView 消息处理程序
