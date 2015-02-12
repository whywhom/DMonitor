// JobCopyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobCopyDlg.h"
#include "afxdialogex.h"


// CJobCopyDlg �Ի���

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


// CJobCopyDlg ��Ϣ�������


BOOL CJobCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 ((CEdit*)GetDlgItem(IDC_ZCW_COPY_NEWNAME))->SetLimitText(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
