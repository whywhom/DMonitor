#pragma once


// CJobEditDlgTool 对话框

class CJobEditDlgTool : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgTool)

public:
	CJobEditDlgTool(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobEditDlgTool();

// 对话框数据
	enum { IDD = IDD_JOBEDIT_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Label;
	afx_msg void OnEnChangeLabel();
	CString m_Type;
	afx_msg void OnEnChangeType();
	CString m_SN;
	float m_Length;
	afx_msg void OnEnChangeLength();
	afx_msg void OnEnChangeSn();
	float m_Weight;
	afx_msg void OnEnChangeWeight();
	float m_OuteRdiam;
	afx_msg void OnEnChangeOuterdiam();
	CString m_Speed;
	afx_msg void OnEnChangeSpeed();
};
