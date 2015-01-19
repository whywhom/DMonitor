#pragma once
#include "jobeditdlg.h"
#include "dirtreectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

// CJobDlg 对话框

class CJobDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobDlg)

public:
	CJobDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobDlg();

// 对话框数据
	enum { IDD = IDD_JOB };
public:
	HWND fatherHwnd;
	int receiveFlag;
	void OnExpandtree(); //展开所有节点 
	void ExpandTreeNode(HTREEITEM hTreeItem);
	CDaoDatabase m_DataBase;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnJobNew();
	virtual BOOL OnInitDialog();
	CDirTreeCtrl m_treeCtrl;
	afx_msg void OnJobDel();
	CString m_Path;
	CString m_Title;
	CString m_TreeTitle;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnJobLoad();
	void LoadJob(CString JobName);
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnToolNew();
	afx_msg void OnToolOpen();
	afx_msg void OnToolCopy();
	afx_msg void OnToolDel();
	void JobCreat();
	void JobAdd(CString jobName);
	void DisplayTreeLeft();
	void DisplayTreeRight();
	CTreeCtrl m_JobTreeLeft;
	void DisplayItem(HTREEITEM hParent,LPCTSTR strName);
	afx_msg void OnBnClickedZcwAdditem();
	afx_msg void OnBnClickedZcwDelitem();
};
