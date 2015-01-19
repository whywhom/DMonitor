#pragma once
#include "afxwin.h"


// CJobEditDlgOrigin 对话框

class CJobEditDlgOrigin : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgOrigin)

public:
	CJobEditDlgOrigin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobEditDlgOrigin();

// 对话框数据
	enum { IDD = IDD_JOBEDIT_ORIGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
