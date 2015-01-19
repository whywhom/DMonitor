// JobInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobInfoDlg.h"
#include "afxdialogex.h"


// CJobInfoDlg 对话框

IMPLEMENT_DYNAMIC(CJobInfoDlg, CDialog)

CJobInfoDlg::CJobInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobInfoDlg::IDD, pParent)
	, m_jobName(_T(""))
{

}

CJobInfoDlg::~CJobInfoDlg()
{
}

void CJobInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZCW_JOBNAME, m_jobName);
}


BEGIN_MESSAGE_MAP(CJobInfoDlg, CDialog)
END_MESSAGE_MAP()


// CJobInfoDlg 消息处理程序
