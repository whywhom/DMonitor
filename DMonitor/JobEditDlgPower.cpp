// JobEditDlgPower.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlgPower.h"
#include "afxdialogex.h"


// CJobEditDlgPower 对话框

IMPLEMENT_DYNAMIC(CJobEditDlgPower, CDialog)

CJobEditDlgPower::CJobEditDlgPower(CWnd* pParent /*=NULL*/)
	: CDialog(CJobEditDlgPower::IDD, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_edit4(_T(""))
	, m_edit5(_T(""))
	, m_edit6(_T(""))
	, m_edit7(_T(""))
	, m_edit8(_T(""))
	, m_edit9(_T(""))
	, m_edit10(_T(""))
	, m_edit11(_T(""))
	, m_edit12(_T(""))
	, m_edit13(_T(""))
	, m_edit14(_T(""))
	, m_edit15(_T(""))
	, m_edit16(_T(""))
	, m_edit17(_T(""))
	, m_edit18(_T(""))
	, m_edit19(_T(""))
	, m_edit20(_T(""))
	, m_edit21(_T(""))
	, m_edit22(_T(""))
{

}

CJobEditDlgPower::~CJobEditDlgPower()
{
}

void CJobEditDlgPower::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO3, m_combo3);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO4, m_combo4);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO5, m_combo5);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO6, m_combo6);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO7, m_combo7);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO8, m_combo8);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO9, m_combo9);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO10, m_combo10);
	DDX_Control(pDX, IDC_ZCW_POWER_COMBO11, m_combo11);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT9, m_edit9);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT10, m_edit10);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT11, m_edit11);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT12, m_edit12);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT13, m_edit13);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT14, m_edit14);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT15, m_edit15);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT16, m_edit16);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT17, m_edit17);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT18, m_edit18);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT19, m_edit19);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT20, m_edit20);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT21, m_edit21);
	DDX_Text(pDX, IDC_ZCW_POWER_EDIT22, m_edit22);
}


BEGIN_MESSAGE_MAP(CJobEditDlgPower, CDialog)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT1, &CJobEditDlgPower::OnEnChangeZcwPowerEdit1)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT2, &CJobEditDlgPower::OnEnChangeZcwPowerEdit2)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT3, &CJobEditDlgPower::OnEnChangeZcwPowerEdit3)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT4, &CJobEditDlgPower::OnEnChangeZcwPowerEdit4)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT5, &CJobEditDlgPower::OnEnChangeZcwPowerEdit5)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT6, &CJobEditDlgPower::OnEnChangeZcwPowerEdit6)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT7, &CJobEditDlgPower::OnEnChangeZcwPowerEdit7)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT8, &CJobEditDlgPower::OnEnChangeZcwPowerEdit8)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT9, &CJobEditDlgPower::OnEnChangeZcwPowerEdit9)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT10, &CJobEditDlgPower::OnEnChangeZcwPowerEdit10)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT11, &CJobEditDlgPower::OnEnChangeZcwPowerEdit11)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT12, &CJobEditDlgPower::OnEnChangeZcwPowerEdit12)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT13, &CJobEditDlgPower::OnEnChangeZcwPowerEdit13)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT14, &CJobEditDlgPower::OnEnChangeZcwPowerEdit14)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT15, &CJobEditDlgPower::OnEnChangeZcwPowerEdit15)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT16, &CJobEditDlgPower::OnEnChangeZcwPowerEdit16)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT17, &CJobEditDlgPower::OnEnChangeZcwPowerEdit17)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT18, &CJobEditDlgPower::OnEnChangeZcwPowerEdit18)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT19, &CJobEditDlgPower::OnEnChangeZcwPowerEdit19)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT20, &CJobEditDlgPower::OnEnChangeZcwPowerEdit20)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT21, &CJobEditDlgPower::OnEnChangeZcwPowerEdit21)
	ON_EN_CHANGE(IDC_ZCW_POWER_EDIT22, &CJobEditDlgPower::OnEnChangeZcwPowerEdit22)
END_MESSAGE_MAP()


// CJobEditDlgPower 消息处理程序


BOOL CJobEditDlgPower::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString m_combo1ary[]={_T("不加电"),_T("交流1"),_T("交流2"),_T("直流1[正]"),_T("直流1[负]"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo2ary[]={_T("不加电"),_T("直流1[正]"),_T("直流1[负]"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo3ary[]={_T("不加电"),_T("交流2"),_T("直流2[正]"),_T("直流2[负]"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo4ary[]={_T("不加电"),_T("交流1")};
	CString m_combo5ary[]={_T("不加电"),_T("直流2[正]"),_T("直流2[负]"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo6ary[]={_T("不加电"),_T("交流1")};
	CString m_combo7ary[]={_T("不加电"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo8ary[]={_T("不加电"),_T("交流2"),_T("直流1[正]"),_T("直流1[负]"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo9ary[]={_T("不加电"),_T("直流3[正]"),_T("直流3[负]")};
	CString m_combo10ary[]={_T("NO"),_T("AMP LOGIC"),_T("CAL POWER"),_T("POLE POWER")};
	CString m_combo11ary[]={_T("不加电"),_T("交流2"),_T("直流3[正]"),_T("直流3[负]")};


	for(int i=0;i<7;i++){
	m_combo1.AddString(m_combo1ary[i]);
	}
	m_combo1.SetCurSel(m_combo1_i);
	
	for(int i=0;i<5;i++){
	m_combo2.AddString(m_combo2ary[i]);
	}
	m_combo2.SetCurSel(m_combo2_i);

	for(int i=0;i<6;i++){
	m_combo3.AddString(m_combo3ary[i]);
	}
	m_combo3.SetCurSel(m_combo3_i);

	for(int i=0;i<2;i++){
	m_combo4.AddString(m_combo4ary[i]);
	}
	m_combo4.SetCurSel(m_combo4_i);

	for(int i=0;i<5;i++){
	m_combo5.AddString(m_combo5ary[i]);
	}
	m_combo5.SetCurSel(m_combo5_i);

	for(int i=0;i<2;i++){
	m_combo6.AddString(m_combo6ary[i]);
	}
	m_combo6.SetCurSel(m_combo6_i);

	for(int i=0;i<3;i++){
	m_combo7.AddString(m_combo7ary[i]);
	}
	m_combo7.SetCurSel(m_combo7_i);

	for(int i=0;i<6;i++){
	m_combo8.AddString(m_combo8ary[i]);
	}
	m_combo8.SetCurSel(m_combo8_i);

	for(int i=0;i<3;i++){
	m_combo9.AddString(m_combo9ary[i]);
	}
	m_combo9.SetCurSel(m_combo9_i);

	for(int i=0;i<4;i++){
	m_combo10.AddString(m_combo10ary[i]);
	}
	m_combo10.SetCurSel(m_combo10_i);

	for(int i=0;i<4;i++){
	m_combo11.AddString(m_combo11ary[i]);
	}
	m_combo11.SetCurSel(m_combo11_i);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit13()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit14()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit15()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit16()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit17()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit18()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit19()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit20()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


void CJobEditDlgPower::OnEnChangeZcwPowerEdit22()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}
