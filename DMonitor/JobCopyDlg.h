#pragma once


// CJobCopyDlg �Ի���

class CJobCopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobCopyDlg)

public:
	CJobCopyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJobCopyDlg();

// �Ի�������
	enum { IDD = IDD_JOBCOPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_oldName;
	CString m_newName;
};
