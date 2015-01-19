#pragma once
#include "afxwin.h"

// CJobEditDlgPower 对话框

class CJobEditDlgPower : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgPower)

public:
	CJobEditDlgPower(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobEditDlgPower();

// 对话框数据
	enum { IDD = IDD_JOBEDIT_POWER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo1;
	CComboBox m_combo2;
	CComboBox m_combo3;
	CComboBox m_combo4;
	CComboBox m_combo5;
	CComboBox m_combo6;
	CComboBox m_combo7;
	CComboBox m_combo8;
	CComboBox m_combo9;
	CComboBox m_combo10;
	CComboBox m_combo11;
	int m_combo1_i;
	int m_combo2_i;
	int m_combo3_i;
	int m_combo4_i;
	int m_combo5_i;
	int m_combo6_i;
	int m_combo7_i;
	int m_combo8_i;
	int m_combo9_i;
	int m_combo10_i;
	int m_combo11_i;
	CString m_edit1;
	CString m_edit2;
	CString m_edit3;
	CString m_edit4;
	CString m_edit5;
	CString m_edit6;
	CString m_edit7;
	CString m_edit8;
	CString m_edit9;
	CString m_edit10;
	CString m_edit11;
	CString m_edit12;
	CString m_edit13;
	CString m_edit14;
	CString m_edit15;
	CString m_edit16;
	CString m_edit17;
	CString m_edit18;
	CString m_edit19;
	CString m_edit20;
	CString m_edit21;
	CString m_edit22;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeZcwPowerEdit1();
	afx_msg void OnEnChangeZcwPowerEdit2();
	afx_msg void OnEnChangeZcwPowerEdit3();
	afx_msg void OnEnChangeZcwPowerEdit4();
	afx_msg void OnEnChangeZcwPowerEdit5();
	afx_msg void OnEnChangeZcwPowerEdit6();
	afx_msg void OnEnChangeZcwPowerEdit7();
	afx_msg void OnEnChangeZcwPowerEdit8();
	afx_msg void OnEnChangeZcwPowerEdit9();
	afx_msg void OnEnChangeZcwPowerEdit10();
	afx_msg void OnEnChangeZcwPowerEdit11();
	afx_msg void OnEnChangeZcwPowerEdit12();
	afx_msg void OnEnChangeZcwPowerEdit13();
	afx_msg void OnEnChangeZcwPowerEdit14();
	afx_msg void OnEnChangeZcwPowerEdit15();
	afx_msg void OnEnChangeZcwPowerEdit16();
	afx_msg void OnEnChangeZcwPowerEdit17();
	afx_msg void OnEnChangeZcwPowerEdit18();
	afx_msg void OnEnChangeZcwPowerEdit19();
	afx_msg void OnEnChangeZcwPowerEdit20();
	afx_msg void OnEnChangeZcwPowerEdit21();
	afx_msg void OnEnChangeZcwPowerEdit22();
};
