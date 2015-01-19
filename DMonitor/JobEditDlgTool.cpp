// JobEditDlgTool.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlgTool.h"
#include "afxdialogex.h"


// CJobEditDlgTool 对话框

IMPLEMENT_DYNAMIC(CJobEditDlgTool, CDialog)

CJobEditDlgTool::CJobEditDlgTool(CWnd* pParent /*=NULL*/)
	: CDialog(CJobEditDlgTool::IDD, pParent)
	, m_Label(_T(""))
	, m_Type(_T(""))
	, m_SN(_T(""))
	, m_Length(0)
	, m_Weight(0)
	, m_OuteRdiam(0)
	, m_Speed(_T(""))
{

}

CJobEditDlgTool::~CJobEditDlgTool()
{
}

void CJobEditDlgTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZCW_TOOL_LABEL, m_Label);
	DDX_Text(pDX, IDC_ZCW_TOOL_TYPE, m_Type);
	DDX_Text(pDX, IDC_ZCW_TOOL_SN, m_SN);
	DDX_Text(pDX, IDC_ZCW_TOOL_LENGTH, m_Length);
	DDX_Text(pDX, IDC_ZCW_TOOL_WEIGHT, m_Weight);
	DDX_Text(pDX, IDC_ZCW_TOOL_OUTERDIAM, m_OuteRdiam);
	DDX_Text(pDX, IDC_ZCW_TOOL_SPEED, m_Speed);
}


BEGIN_MESSAGE_MAP(CJobEditDlgTool, CDialog)
	ON_EN_CHANGE(IDC_ZCW_TOOL_LABEL, &CJobEditDlgTool::OnEnChangeLabel)
	ON_EN_CHANGE(IDC_ZCW_TOOL_TYPE, &CJobEditDlgTool::OnEnChangeType)
	ON_EN_CHANGE(IDC_ZCW_TOOL_LENGTH, &CJobEditDlgTool::OnEnChangeLength)
	ON_EN_CHANGE(IDC_ZCW_TOOL_SN, &CJobEditDlgTool::OnEnChangeSn)
	ON_EN_CHANGE(IDC_ZCW_TOOL_WEIGHT, &CJobEditDlgTool::OnEnChangeWeight)
	ON_EN_CHANGE(IDC_ZCW_TOOL_OUTERDIAM, &CJobEditDlgTool::OnEnChangeOuterdiam)
	ON_EN_CHANGE(IDC_ZCW_TOOL_SPEED, &CJobEditDlgTool::OnEnChangeSpeed)
END_MESSAGE_MAP()


// CJobEditDlgTool 消息处理程序


void CJobEditDlgTool::OnEnChangeLabel()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgTool::OnEnChangeType()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgTool::OnEnChangeLength()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgTool::OnEnChangeSn()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgTool::OnEnChangeWeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgTool::OnEnChangeOuterdiam()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgTool::OnEnChangeSpeed()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}
