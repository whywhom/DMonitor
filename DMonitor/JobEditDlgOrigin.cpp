// JobEditDlgOrigin.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlgOrigin.h"
#include "afxdialogex.h"


// CJobEditDlgOrigin 对话框

IMPLEMENT_DYNAMIC(CJobEditDlgOrigin, CDialog)

CJobEditDlgOrigin::CJobEditDlgOrigin(CWnd* pParent /*=NULL*/)
	: CDialog(CJobEditDlgOrigin::IDD, pParent)
	, m_Label(_T(""))
{

}

CJobEditDlgOrigin::~CJobEditDlgOrigin()
{
}

void CJobEditDlgOrigin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZCW_ORIGIN_LABEL, m_Label);
	DDX_Control(pDX, IDC_ZCW_ORIGIN_UNIT, m_unitbox);
	DDX_Control(pDX, IDC_ZCW_ORIGIN_FILTER, m_filterbox);
}


BEGIN_MESSAGE_MAP(CJobEditDlgOrigin, CDialog)
	ON_EN_CHANGE(IDC_ZCW_ORIGIN_LABEL, &CJobEditDlgOrigin::OnEnChangeLabel)
END_MESSAGE_MAP()


// CJobEditDlgOrigin 消息处理程序


void CJobEditDlgOrigin::OnEnChangeLabel()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
}


BOOL CJobEditDlgOrigin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString m_unitary[]={_T("mV"),_T("GAPI"),_T("CPS"),_T("us/m"),_T("m"),_T("cm"),_T("mm"),_T("uS"),_T("mS"),_T("S"),_T("MΩ"),_T("kΩ"),_T("Ω"),_T("Ω.m"),_T("s"),_T("S/m"),_T("mS/m"),_T("m/h"),_T("Kg"),_T("Kn"),_T("N"),_T("℃"),_T("℃/m"),_T("kg/m^3"),_T("g/cm^3"),_T("km"),_T("km^3"),_T("m^3"),_T("dm^3"),_T("m/s^2"),_T("mm/s^2"),_T("rad"),_T("mrad"),_T("urad"),_T("°"),_T("km^2"),_T("ha"),_T("dm^2"),_T("cm^2"),_T("mm^2"),_T("kg/s"),_T("m^3/s"),_T("m^3/min"),_T("m^3/d"),_T("L/s"),_T("Std.m3/m3"),_T("t"),_T("Mg/m^3"),_T("pu"),_T("J"),_T("Mev"),_T("MW"),_T("KW"),_T("W"),_T("Pa"),_T("kPa"),_T("MPa"),_T("ATM"),_T("PSI"),_T("Bq"),_T("r/s"),_T("min"),_T("h"),_T("d"),_T("a"),_T("m/s"),_T("Pa.s"),_T("mPa.s"),_T("N.s/m^2"),_T("%"),_T("NAPI"),_T("inch"),_T("API"),_T("V"),_T("度"),_T("uS/m"),_T("ppm"),_T("I")};
	CString m_filterary[]={_T("none"),_T("3点平均"),_T("3点加权"),_T("5点平均"),_T("5点加权"),_T("7点平均"),_T("7点加权"),_T("9点平均"),_T("9点加权"),_T("11点平均"),_T("11点加权"),_T("13点平均"),_T("13点加权"),_T("15点平均"),_T("15点加权"),_T("17点平均"),_T("17点加权"),_T("19点平均"),_T("19点加权"),_T("21点平均"),_T("21点加权"),_T("3700(1)"),_T("3700(2)"),_T("3700(3)"),_T("一阶滤波1"),_T("一阶滤波2"),_T("一阶滤波3"),_T("一阶滤波4"),_T("一阶滤波5"),_T("一阶滤波1"),_T("串联滤波1"),_T("串联滤波1"),_T("累计滤波1"),_T("累计滤波2"),_T("累计滤波3"),_T("累计滤波4"),_T("累计滤波5"),_T("累计滤波6"),_T("累计滤波7"),_T("累计滤波8"),_T("累计滤波9")};

	for(int i=0;i<78;i++){
	m_unitbox.AddString(m_unitary[i]);	
	}
	m_unitbox.SetCurSel(0);
	for(int i=0;i<78;i++){
		if(m_unit==m_unitary[i]){
			m_unitbox.SetCurSel(i);
		}
	}
	
	for(int i=0;i<41;i++){
	m_filterbox.AddString(m_filterary[i]);	
	}
	m_filterbox.SetCurSel(0);
	for(int i=0;i<41;i++){	
		if(m_filter==m_filterary[i]){
			m_filterbox.SetCurSel(i);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
