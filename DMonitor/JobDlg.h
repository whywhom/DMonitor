#pragma once
#include "jobeditdlg.h"
#include "dirtreectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

// CJobDlg �Ի���

class CJobDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobDlg)

public:
	CJobDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJobDlg();

// �Ի�������
	enum { IDD = IDD_JOB };
public:
	HWND fatherHwnd;
	int receiveFlag;
	void OnExpandtree(); //չ�����нڵ� 
	void ExpandTreeNode(HTREEITEM hTreeItem);
	CDaoDatabase m_DataBase;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	afx_msg void OnNMDblclkZcwJobTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkZcwJobtreeLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickZcwJobTree(NMHDR *pNMHDR, LRESULT *pResult);
};
