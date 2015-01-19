#pragma once
#include "afxwin.h"
#include "ColorStatic.h"

// CJobEditDlgCurve 对话框

class CJobEditDlgCurve : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlgCurve)

public:
	CJobEditDlgCurve(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobEditDlgCurve();

// 对话框数据
	enum { IDD = IDD_JOBEDIT_CURVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_unitbox;
	CComboBox m_filterbox;
	COLORREF curveSelectColor;
	CString m_Label;
	CString m_unit;
	CString m_filter;
	afx_msg void OnEnChangeLabel();
	CComboBox m_trackbox;
	CComboBox m_linetype;
	CColorStatic m_scolor;
	CButton m_btColor;
	CEdit nTestEditMin;
	CEdit nTestEditMax;
	CEdit m_edittitle;
	afx_msg void OnBnClickedButtonColor();
	CString m_title;
	double m_minLimit;
	double m_maxLimit;
	int m_line;
	int m_linewid;
	int m_track;
	afx_msg void OnEnChangeZcwCurveTitle();
	afx_msg void OnEnChangeEditMin();
	afx_msg void OnEnChangeEditMax();
	CComboBox m_linewidth;
};
