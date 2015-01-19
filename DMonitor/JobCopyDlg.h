#pragma once


// CJobCopyDlg 对话框

class CJobCopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobCopyDlg)

public:
	CJobCopyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobCopyDlg();

// 对话框数据
	enum { IDD = IDD_JOBCOPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_oldName;
	CString m_newName;
};
