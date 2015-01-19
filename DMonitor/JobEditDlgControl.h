#pragma once
#include "afxwin.h"


// CJobEditDlgControl 对话框

class CJobEditDlgControl : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgControl)

public:
	CJobEditDlgControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobEditDlgControl();

// 对话框数据
	enum { IDD = IDD_JOBEDIT_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_combo1;
	CComboBox m_combo2;
	CComboBox m_combo3;
	CComboBox m_combo4;
	CComboBox m_combo5;
	int m_combo1_i;
	int m_combo2_i;
	int m_combo3_i;
	int m_combo4_i;
	int m_combo5_i;
	CString m_edit1;
	CString m_edit2;
	CString m_edit3;
	CString m_edit4;
	CString m_edit5;
	CString m_edit6;
	CString m_edit7;
	afx_msg void OnBnClickedZcwControlButton1();
	afx_msg void OnBnClickedZcwControlButton2();
	afx_msg void OnEnChangeZcwControlEdit1();
	afx_msg void OnEnChangeZcwControlEdit2();
	afx_msg void OnEnChangeZcwControlEdit3();
	afx_msg void OnEnChangeZcwControlEdit4();
	afx_msg void OnEnChangeZcwControlEdit5();
	afx_msg void OnEnChangeZcwControlEdit6();
	afx_msg void OnEnChangeZcwControlEdit7();
};
