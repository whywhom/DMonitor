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


BOOL CJobInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CEdit*)GetDlgItem(IDC_ZCW_JOBNAME))->SetLimitText(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
