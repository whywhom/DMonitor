#pragma once


// CJobEditDlgTool �Ի���

class CJobEditDlgTool : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgTool)

public:
	CJobEditDlgTool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJobEditDlgTool();

// �Ի�������
	enum { IDD = IDD_JOBEDIT_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
