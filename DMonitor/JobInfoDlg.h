#pragma once


// CJobInfoDlg �Ի���

class CJobInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobInfoDlg)

public:
	CJobInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJobInfoDlg();

// �Ի�������
	enum { IDD = IDD_JOBINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_jobName;
};
