// JobEditDlgControl.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlgControl.h"
#include "afxdialogex.h"


// CJobEditDlgControl 对话框

IMPLEMENT_DYNAMIC(CJobEditDlgControl, CDialog)

CJobEditDlgControl::CJobEditDlgControl(CWnd* pParent /*=NULL*/)
	: CDialog(CJobEditDlgControl::IDD, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_edit4(_T(""))
	, m_edit5(_T(""))
	, m_edit6(_T(""))
	, m_edit7(_T(""))
{

}

CJobEditDlgControl::~CJobEditDlgControl()
{
}

void CJobEditDlgControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZCW_CONTROL_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_ZCW_CONTROL_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_ZCW_CONTROL_COMBO3, m_combo3);
	DDX_Control(pDX, IDC_ZCW_CONTROL_COMBO4, m_combo4);
	DDX_Control(pDX, IDC_ZCW_CONTROL_COMBO5, m_combo5);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_ZCW_CONTROL_EDIT7, m_edit7);
}


BEGIN_MESSAGE_MAP(CJobEditDlgControl, CDialog)
	ON_BN_CLICKED(IDC_ZCW_CONTROL_BUTTON1, &CJobEditDlgControl::OnBnClickedZcwControlButton1)
	ON_BN_CLICKED(IDC_ZCW_CONTROL_BUTTON2, &CJobEditDlgControl::OnBnClickedZcwControlButton2)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT1, &CJobEditDlgControl::OnEnChangeZcwControlEdit1)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT2, &CJobEditDlgControl::OnEnChangeZcwControlEdit2)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT3, &CJobEditDlgControl::OnEnChangeZcwControlEdit3)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT4, &CJobEditDlgControl::OnEnChangeZcwControlEdit4)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT5, &CJobEditDlgControl::OnEnChangeZcwControlEdit5)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT6, &CJobEditDlgControl::OnEnChangeZcwControlEdit6)
	ON_EN_CHANGE(IDC_ZCW_CONTROL_EDIT7, &CJobEditDlgControl::OnEnChangeZcwControlEdit7)
END_MESSAGE_MAP()


// CJobEditDlgControl 消息处理程序


BOOL CJobEditDlgControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString m_combo1ary[]={_T("100"),_T("125"),_T("25"),_T("31.25")};
	CString m_combo2ary[]={_T("600"),_T("450"),_T("300"),_T("100")};
	CString m_combo3ary[]={_T("3000")};
	CString m_combo4ary[]={_T("1"),_T("2"),_T("4"),_T("8")};
	CString m_combo5ary[]={_T("10"),_T("20"),_T("30"),_T("40"),_T("50"),_T("55")};


	for(int i=0;i<4;i++){
	m_combo1.AddString(m_combo1ary[i]);
	}
	m_combo1.SetCurSel(m_combo1_i);

	for(int i=0;i<4;i++){
	m_combo2.AddString(m_combo2ary[i]);
	}
	m_combo2.SetCurSel(m_combo2_i);

	for(int i=0;i<1;i++){
	m_combo3.AddString(m_combo3ary[i]);
	}
	m_combo3.SetCurSel(m_combo3_i);

	for(int i=0;i<4;i++){
	m_combo4.AddString(m_combo4ary[i]);
	}
	m_combo4.SetCurSel(m_combo4_i);

	for(int i=0;i<6;i++){
	m_combo5.AddString(m_combo5ary[i]);
	}
	m_combo5.SetCurSel(m_combo5_i);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CJobEditDlgControl::OnBnClickedZcwControlButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,_T(""),_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("format files(*.xml)|*.xml|All files(*.*)|*.*|"));//构造打开文件对话框
	dlg.m_ofn.lpstrInitialDir=theApp.IniFilePath;
    if(dlg.DoModal()==IDOK)//显示打开文件对话框
	{		
		//m_edit6=dlg.GetPathName();//获取文件路径名称
		GetDlgItem(IDC_ZCW_CONTROL_EDIT6)->SetWindowText(dlg.GetFileName());
	}
}


void CJobEditDlgControl::OnBnClickedZcwControlButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,_T(""),_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("format files(*.xml)|*.xml|All files(*.*)|*.*|"));//构造打开文件对话框
	dlg.m_ofn.lpstrInitialDir=theApp.IniFilePath;
    if(dlg.DoModal()==IDOK)//显示打开文件对话框
	{		
		//m_edit7=dlg.GetPathName();//获取文件路径名称		
		GetDlgItem(IDC_ZCW_CONTROL_EDIT7)->SetWindowText(dlg.GetFileName());
	}
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgControl::OnEnChangeZcwControlEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}
