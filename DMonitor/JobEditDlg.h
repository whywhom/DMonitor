#pragma once
#pragma warning(disable : 4995)
#include "afxcmn.h"
#include "jobeditdlgtool.h"
#include "jobeditdlgcurve.h"
#include "jobeditdlgorigin.h"
#include "jobeditdlgcontrol.h"
#include "jobeditdlgpower.h"
#include "afxwin.h"


// CJobEditDlg 对话框

class CJobEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CJobEditDlg)

public:
	CJobEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJobEditDlg();

// 对话框数据
	enum { IDD = IDD_JOBEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_jobName;//当前仪器数据库文件名
	CString m_Path;//仪器存储路径
	CDaoDatabase m_DataBase;//存储当前仪器的数据
	CDaoDatabase m_DBJobList;//存储所有作业-仪器对应信息及所有信号的标签
	bool m_Open;
	CTreeCtrl m_jeTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedJobeditTree(NMHDR *pNMHDR, LRESULT *pResult);
public:	
   	CJobEditDlgTool m_Tool;//仪器信息对话框对应的类
	CJobEditDlgCurve m_Curve;//曲线信息对话框对应的类
	CJobEditDlgOrigin m_Origin;//原始信号对话框对应的类
	CJobEditDlgControl m_Control;//控制信息对话框对应的类
	CJobEditDlgPower m_Power;//加电信息对话框对应的类

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
	void JobInit();//初始化作业数据库

public:
	afx_msg void OnBnClickedAdd();
	int m_editTable;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedZcwJobeditImport();
	afx_msg void OnBnClickedZcwJobeditExport();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
