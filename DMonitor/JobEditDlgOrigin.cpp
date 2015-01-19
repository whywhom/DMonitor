// JobEditDlgOrigin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlgOrigin.h"
#include "afxdialogex.h"


// CJobEditDlgOrigin �Ի���

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


// CJobEditDlgOrigin ��Ϣ�������


void CJobEditDlgOrigin::OnEnChangeLabel()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


BOOL CJobEditDlgOrigin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString m_unitary[]={_T("mV"),_T("GAPI"),_T("CPS"),_T("us/m"),_T("m"),_T("cm"),_T("mm"),_T("uS"),_T("mS"),_T("S"),_T("M��"),_T("k��"),_T("��"),_T("��.m"),_T("s"),_T("S/m"),_T("mS/m"),_T("m/h"),_T("Kg"),_T("Kn"),_T("N"),_T("��"),_T("��/m"),_T("kg/m^3"),_T("g/cm^3"),_T("km"),_T("km^3"),_T("m^3"),_T("dm^3"),_T("m/s^2"),_T("mm/s^2"),_T("rad"),_T("mrad"),_T("urad"),_T("��"),_T("km^2"),_T("ha"),_T("dm^2"),_T("cm^2"),_T("mm^2"),_T("kg/s"),_T("m^3/s"),_T("m^3/min"),_T("m^3/d"),_T("L/s"),_T("Std.m3/m3"),_T("t"),_T("Mg/m^3"),_T("pu"),_T("J"),_T("Mev"),_T("MW"),_T("KW"),_T("W"),_T("Pa"),_T("kPa"),_T("MPa"),_T("ATM"),_T("PSI"),_T("Bq"),_T("r/s"),_T("min"),_T("h"),_T("d"),_T("a"),_T("m/s"),_T("Pa.s"),_T("mPa.s"),_T("N.s/m^2"),_T("%"),_T("NAPI"),_T("inch"),_T("API"),_T("V"),_T("��"),_T("uS/m"),_T("ppm"),_T("I")};
	CString m_filterary[]={_T("none"),_T("3��ƽ��"),_T("3���Ȩ"),_T("5��ƽ��"),_T("5���Ȩ"),_T("7��ƽ��"),_T("7���Ȩ"),_T("9��ƽ��"),_T("9���Ȩ"),_T("11��ƽ��"),_T("11���Ȩ"),_T("13��ƽ��"),_T("13���Ȩ"),_T("15��ƽ��"),_T("15���Ȩ"),_T("17��ƽ��"),_T("17���Ȩ"),_T("19��ƽ��"),_T("19���Ȩ"),_T("21��ƽ��"),_T("21���Ȩ"),_T("3700(1)"),_T("3700(2)"),_T("3700(3)"),_T("һ���˲�1"),_T("һ���˲�2"),_T("һ���˲�3"),_T("һ���˲�4"),_T("һ���˲�5"),_T("һ���˲�1"),_T("�����˲�1"),_T("�����˲�1"),_T("�ۼ��˲�1"),_T("�ۼ��˲�2"),_T("�ۼ��˲�3"),_T("�ۼ��˲�4"),_T("�ۼ��˲�5"),_T("�ۼ��˲�6"),_T("�ۼ��˲�7"),_T("�ۼ��˲�8"),_T("�ۼ��˲�9")};

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
	// �쳣: OCX ����ҳӦ���� FALSE
}
