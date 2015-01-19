// JobEditDlgCurve.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlgCurve.h"
#include "afxdialogex.h"


// CJobEditDlgCurve �Ի���

IMPLEMENT_DYNAMIC(CJobEditDlgCurve, CDialog)

CJobEditDlgCurve::CJobEditDlgCurve(CWnd* pParent /*=NULL*/)
	: CDialog(CJobEditDlgCurve::IDD, pParent)
	, m_Label(_T(""))
	, m_unit(_T(""))
	, m_filter(_T(""))
	, m_title(_T(""))
	, m_minLimit(1.0)
	, m_maxLimit(100.0)
	, m_line(0)
	, m_linewid(0)
	, m_track(0)
	, curveSelectColor(RGB(0xFF,0x00,0x00))
{

}

CJobEditDlgCurve::~CJobEditDlgCurve()
{
}

void CJobEditDlgCurve::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZCW_CURVE_UNIT, m_unitbox);
	DDX_Control(pDX, IDC_ZCW_CURVE_FILTER, m_filterbox);
	DDX_Text(pDX, IDC_ZCW_CURVE_LABEL, m_Label);
	DDX_Control(pDX, IDC_ZCW_CURVE_TRACK, m_trackbox);
	DDX_Control(pDX, IDC_ZCW_CURVE_LINETYPE, m_linetype);
	DDX_Control(pDX, IDC_STATIC_COLOR, m_scolor);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_btColor);
	DDX_Control(pDX, IDC_EDIT_MIN, nTestEditMin);
	DDX_Control(pDX, IDC_EDIT_MAX, nTestEditMax);
	DDX_Control(pDX, IDC_ZCW_CURVE_TITLE, m_edittitle);
	DDX_Text(pDX, IDC_ZCW_CURVE_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_MIN, m_minLimit);
	DDX_Text(pDX, IDC_EDIT_MAX, m_maxLimit);
	DDX_Control(pDX, IDC_ZCW_CURVE_LINEWIDTH, m_linewidth);
}


BEGIN_MESSAGE_MAP(CJobEditDlgCurve, CDialog)
	ON_EN_CHANGE(IDC_ZCW_CURVE_LABEL, &CJobEditDlgCurve::OnEnChangeLabel)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CJobEditDlgCurve::OnBnClickedButtonColor)
	ON_EN_CHANGE(IDC_ZCW_CURVE_TITLE, &CJobEditDlgCurve::OnEnChangeZcwCurveTitle)
	ON_EN_CHANGE(IDC_EDIT_MIN, &CJobEditDlgCurve::OnEnChangeEditMin)
	ON_EN_CHANGE(IDC_EDIT_MAX, &CJobEditDlgCurve::OnEnChangeEditMax)
END_MESSAGE_MAP()


// CJobEditDlgCurve ��Ϣ�������


BOOL CJobEditDlgCurve::OnInitDialog()
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

	m_trackbox.AddString(_T("��� 1"));
	m_trackbox.AddString(_T("��� 2"));
	m_trackbox.SetCurSel(m_track);

	m_scolor.SetStaiticColor(curveSelectColor);

	m_linetype.InsertString(0,_T("ʵ��"));//PS_SOLID /* ��*/
	//m_linetype.InsertString(1,_T("����"));//PS_DASH  /* -------  */
	//m_linetype.InsertString(2,_T("����"));//PS_DOT  /* .......  */
	//m_linetype.InsertString(3,_T("�㻮��"));//PS_DASHDOT  /* _._._._  */
	//m_linetype.InsertString(4,_T("˫�㻮��"));//PS_DASHDOTDOT  /* _.._.._  */
	m_linetype.SetCurSel(m_line);

	m_linewidth.InsertString(0,_T("ϸ��"));//PS_SOLID /* ��*/
	m_linewidth.InsertString(1,_T("��ͨ"));//PS_DASH  /* -------  */
	m_linewidth.InsertString(2,_T("����"));//PS_DOT  /* .......  */
	m_linewidth.SetCurSel(m_linewid);

	//nTestEditMin.SetWindowText(m_minLimit);
	//nTestEditMax.SetWindowText(m_maxLimit);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CJobEditDlgCurve::OnEnChangeLabel()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CJobEditDlgCurve::OnBnClickedButtonColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;

	if (dlg.DoModal() == IDOK)
	{
		curveSelectColor = dlg.GetColor();
		m_scolor.SetStaiticColor(curveSelectColor);
	}
}


void CJobEditDlgCurve::OnEnChangeZcwCurveTitle()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CJobEditDlgCurve::OnEnChangeEditMin()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CJobEditDlgCurve::OnEnChangeEditMax()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}
