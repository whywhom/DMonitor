#pragma once


// CJobInfoDlg 对话框

class CJobInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobInfoDlg)

public:
	CJobInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobInfoDlg();

// 对话框数据
	enum { IDD = IDD_JOBINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_jobName;
};
