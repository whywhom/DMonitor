#pragma once
#pragma warning(disable : 4995)
#include "afxcmn.h"
#include "jobeditdlgtool.h"
#include "jobeditdlgcurve.h"
#include "jobeditdlgorigin.h"
#include "jobeditdlgcontrol.h"
#include "jobeditdlgpower.h"
#include "afxwin.h"


// CJobEditDlg �Ի���

class CJobEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlg)

public:
	CJobEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJobEditDlg();

// �Ի�������
	enum { IDD = IDD_JOBEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_jobName;//��ǰ�������ݿ��ļ���
	CString m_Path;//�����洢·��
	CDaoDatabase m_DataBase;//�洢��ǰ����������
	CDaoDatabase m_DBJobList;//�洢������ҵ-������Ӧ��Ϣ�������źŵı�ǩ
	bool m_Open;
	CTreeCtrl m_jeTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedJobeditTree(NMHDR *pNMHDR, LRESULT *pResult);
public:	
   	CJobEditDlgTool m_Tool;//������Ϣ�Ի����Ӧ����
	CJobEditDlgCurve m_Curve;//������Ϣ�Ի����Ӧ����
	CJobEditDlgOrigin m_Origin;//ԭʼ�źŶԻ����Ӧ����
	CJobEditDlgControl m_Control;//������Ϣ�Ի����Ӧ����
	CJobEditDlgPower m_Power;//�ӵ���Ϣ�Ի����Ӧ����

private:	
	void ToolAdd();
	void ToolInit(CString Label);
	void ToolInit();
	void ToolInitOpen();
	void ToolDel(CString Label);
	void ToolUpdate(CString Label);
	void CurveAdd();
	void CurveInit(CString Label);
	void CurveInit();
	void CurveDel(CString Label);
	void CurveUpdate(CString Label);
	void OriginAdd();
	void OriginInit(CString Label);
	void OriginInit();
	void OriginDel(CString Label);
	void OriginUpdate(CString Label);
	void ControlAdd();
	void ControlUpdate();
	void ControlInit();
	void PowerAdd();
	void PowerUpdate(CString PowerMode);
	void PowerInit(CString PowerMode);
	void DisplayTree(int EditTable);
	void JobInit();//��ʼ����ҵ���ݿ�

public:
	afx_msg void OnBnClickedAdd();
	int m_editTable;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedZcwJobeditImport();
	afx_msg void OnBnClickedZcwJobeditExport();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
