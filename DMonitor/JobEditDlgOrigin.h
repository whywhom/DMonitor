#pragma once
#include "afxwin.h"


// CJobEditDlgOrigin �Ի���

class CJobEditDlgOrigin : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgOrigin)

public:
	CJobEditDlgOrigin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJobEditDlgOrigin();

// �Ի�������
	enum { IDD = IDD_JOBEDIT_ORIGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Label;
	afx_msg void OnEnChangeLabel();
	CComboBox m_unitbox;
	CComboBox m_filterbox;
	CString m_unit;
	CString m_filter;
	virtual BOOL OnInitDialog();
};
