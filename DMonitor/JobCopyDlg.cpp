// JobCopyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobCopyDlg.h"
#include "afxdialogex.h"


// CJobCopyDlg 对话框

IMPLEMENT_DYNAMIC(CJobCopyDlg, CDialog)

CJobCopyDlg::CJobCopyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobCopyDlg::IDD, pParent)
	, m_oldName(_T(""))
	, m_newName(_T(""))
{

}

CJobCopyDlg::~CJobCopyDlg()
{
}

void CJobCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZCW_COPY_OLDNAME, m_oldName);
	DDX_Text(pDX, IDC_ZCW_COPY_NEWNAME, m_newName);
}


BEGIN_MESSAGE_MAP(CJobCopyDlg, CDialog)
END_MESSAGE_MAP()


// CJobCopyDlg 消息处理程序
