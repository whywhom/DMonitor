// JobInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobInfoDlg.h"
#include "afxdialogex.h"


// CJobInfoDlg �Ի���

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


// CJobInfoDlg ��Ϣ�������


BOOL CJobInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CEdit*)GetDlgItem(IDC_ZCW_JOBNAME))->SetLimitText(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
