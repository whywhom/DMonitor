// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream> 
using namespace std; 

// CTestDlg �Ի���
CString m_unitary[]={_T("mV"),_T("GAPI"),_T("CPS"),_T("us/m"),_T("m"),
	_T("cm"),_T("mm"),_T("uS"),_T("mS"),_T("S"),
	_T("M��"),_T("k��"),_T("��"),_T("��.m"),_T("s"),
	_T("S/m"),_T("mS/m"),_T("m/h"),_T("Kg"),_T("Kn"),
	_T("N"),_T("��"),_T("��/m"),_T("kg/m^3"),_T("g/cm^3"),
	_T("km"),_T("km^3"),_T("m^3"),_T("dm^3"),_T("m/s^2"),
	_T("mm/s^2"),_T("rad"),_T("mrad"),_T("urad"),_T("��"),
	_T("km^2"),_T("ha"),_T("dm^2"),_T("cm^2"),_T("mm^2"),
	_T("kg/s"),_T("m^3/s"),_T("m^3/min"),_T("m^3/d"),_T("L/s"),
	_T("Std.m3/m3"),_T("t"),_T("Mg/m^3"),_T("pu"),_T("J"),
	_T("Mev"),_T("MW"),_T("KW"),_T("W"),_T("Pa"),
	_T("kPa"),_T("MPa"),_T("ATM"),_T("PSI"),_T("Bq"),
	_T("r/s"),_T("min"),_T("h"),_T("d"),_T("a"),
	_T("m/s"),_T("Pa.s"),_T("mPa.s"),_T("N.s/m^2"),_T("%"),
	_T("NAPI"),_T("inch"),_T("API"),_T("V"),_T("��"),
	_T("uS/m"),_T("ppm"),_T("I")};
int arrayLength = 78;
IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	curveSelectColor = RGB(0xFF,0x00,0x00);
	pCurList = NULL;
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mTestList);
	DDX_Control(pDX, IDC_COMBO_SIGNAL, mCbSignal);
	DDX_Control(pDX, IDC_COMBO_TITLE, nAbbr);
	DDX_Control(pDX, IDC_COMBO_UNIT, mTestUnit);
	DDX_Control(pDX, IDC_EDIT_MIN, nTestEditMin);
	DDX_Control(pDX, IDC_EDIT_MAX, nTestEditMax);
	DDX_Control(pDX, IDC_BUTTON_ADD, mTestAdd);
	DDX_Control(pDX, IDC_BUTTON_DEL, mTestDel);
	DDX_Control(pDX, IDC_STATIC_COLOR, mStaticColor);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CTestDlg::OnBnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CTestDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CTestDlg::OnBnClickedButtonDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTestDlg::OnLvnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL, &CTestDlg::OnCbnSelchangeComboSignal)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������


BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
				return TRUE;
			case VK_UP://�������·����
			case VK_DOWN:	
			case VK_SPACE:
			case VK_RETURN://���λس�
				return TRUE;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect   temprect(0,0,320,200);
    CRect rect;
    CRect rc;
    CRect rc2;
    //CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
    CenterWindow();
		
	if(theApp.workInfoList.IsEmpty())
	{
		//��ʼ��
		InitWorkInfoList(_T("���"),_T("DEPT"),_T("m"), 0, 6000);
		InitWorkInfoList(_T("����"),_T("TEMP"),_T("C"), -10, 90);
		InitWorkInfoList(_T("������"),_T("RM"),_T("rm"), 0, 40);
		InitWorkInfoList(_T("������"),_T("GR"),_T("GAPI"), 0, 2000);
		InitWorkInfoList(_T("��������"),_T("MAG"),_T("mag"),-10000, 10000);
		InitWorkInfoList(_T("�Ŷ�λ��"),_T("CCL"),_T("CCL"), 0, 1);
		InitCtrl();
		if(!SetCurveInfo(0))
		{
			SendMessage(WM_CLOSE);
		}
	}
	else
	{
		//����theApp.workInfoList
		InitCtrl();
		if(!SetCurveInfo(0))
		{
			SendMessage(WM_CLOSE);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool CTestDlg::SetCurveInfo(int item)
{
	if(item >= theApp.workInfoList.GetCount() || item <0)
	{
		return false;
	}
	CWorkInfo* plist = theApp.workInfoList.GetAt(theApp.workInfoList.FindIndex(item));
	pCurList = plist;
	mTestList.SetItemState(item, LVIS_FOCUSED | LVIS_SELECTED,
                                 LVIS_FOCUSED | LVIS_SELECTED );
	CString str;

	((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->SetCurSel(item);

	((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->SetCurSel(item);

	//((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->SetCurSel(item);

	bool isInList = false;
	//for(int i=0;i<arrayLength;i++)
	int i=0;
	CWorkUnit* p = NULL;
	POSITION pos = theApp.workUnitList.GetHeadPosition();
	while(pos)
	{
		p = theApp.workUnitList.GetNext(pos);
		if(!p->strUnit.Compare(plist->strUnit))
		{
			//((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->SetCurSel(i);
			isInList = true;
			break;
		}
		i++;
	}
	if(!isInList)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->InsertString(mTestUnit.GetCount(),plist->strUnit);
		CWorkUnit* pUnit = new CWorkUnit();
		pUnit->strUnit = plist->strUnit;
		theApp.workUnitList.AddTail(pUnit);
		((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->SetCurSel(mTestUnit.GetCount()-1);
	}
	else
	{
		//CWorkInfo* plist = theApp.workInfoList.GetAt(theApp.workInfoList.FindIndex(i));
		((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->SetCurSel(i);
	}

	str.Format(_T("%d"),plist->leftLimit);
	nTestEditMin.SetWindowText(str);

	str.Format(_T("%d"),plist->rightLimit);
	nTestEditMax.SetWindowText(str);

	mStaticColor.SetStaiticColor(plist->curveColor);
	curveSelectColor = plist->curveColor;
	return true;
}

void CTestDlg::InitWorkInfoList(CString signal,CString title, CString uint, int min, int max)
{
	CWorkInfo* plist = new CWorkInfo();
	plist->strSignal = signal;
	plist->strTitle = title;
	plist->strUnit = uint;
	plist->leftLimit = min;
	plist->rightLimit = max;
	plist->curveColor = RGB(255,0,0); //��ɫ
	theApp.workInfoList.AddTail(plist);
}

void CTestDlg::InitCtrl()
{
	int id = 0;

	((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->ResetContent();
	//for(int i=0;i<theApp.workUnitList.GetCount();i++)
	CWorkUnit* p = NULL;
	POSITION pos = theApp.workUnitList.GetHeadPosition();
	while(pos)
	{
		p = theApp.workUnitList.GetNext(pos);
		((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->AddString(p->strUnit);
	}

	mStaticColor.SetStaiticColor(curveSelectColor);
	mTestList.InsertColumn( 0, _T("ԭʼ�ź�"), LVCFMT_LEFT, 60 ); 
    mTestList.InsertColumn( 1, _T("Ӣ�ļ�д"), LVCFMT_LEFT, 60 ); 
	mTestList.InsertColumn( 2, _T("������λ"), LVCFMT_LEFT, 60 ); 
	mTestList.InsertColumn( 3, _T("ȡֵ��Χ"), LVCFMT_LEFT, 60 ); 
	mTestList.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP ); 
	RefreshListCtrl();
}

void CTestDlg::RefreshListCtrl()
{
	int id = 0;
	POSITION pos;
	mTestList.DeleteAllItems();
	((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->ResetContent();
	pos = theApp.workUnitList.GetHeadPosition();
	while(pos)
	{
		CWorkUnit* plist = theApp.workUnitList.GetNext(pos);
		((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->AddString(plist->strUnit);
	}
	pos = theApp.workInfoList.GetHeadPosition();
	while(pos)
	{
		CWorkInfo* plist = theApp.workInfoList.GetNext(pos);
		((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->AddString(plist->strSignal);
		((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->AddString(plist->strTitle);
		
		mTestList.InsertItem(id,plist->strSignal);
		mTestList.SetItemText(id,1,plist->strTitle);
		mTestList.SetItemText(id,2,plist->strUnit);
		CString strMin,strMax;
		strMin.Format(_T("%d"),plist->leftLimit);
		strMax.Format(_T("%d"),plist->rightLimit);
		if(!strMin.IsEmpty() || !strMax.IsEmpty())
		{
			mTestList.SetItemText(id,3,strMin+_T(" - ")+strMax);
		}
		id++;
	}
}

void CTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void CTestDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CTestDlg::OnBnClickedButtonColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;

	if (dlg.DoModal() == IDOK)
	{
		curveSelectColor = dlg.GetColor();
		mStaticColor.SetStaiticColor(curveSelectColor);
	}
}

void CTestDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;

	nTestEditMin.GetWindowText(str);
	int nMin = _wtoi(str);
	nTestEditMax.GetWindowText(str);
	int nMax = _wtoi(str);
	if(nMax <= nMin)
	{
		MessageBox(_T("���ȡֵӦ������Сȡֵ�����������룡"),MB_OK);
		return;
	}
	bool isExist = false;
	int item = ((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetCurSel();
	if(item >= 0)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetLBText(item , str);
	}
	else
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetWindowText(str);
	}
	CWorkInfo* plist;
	POSITION pos = theApp.workInfoList.GetHeadPosition();
	while(pos)
	{
		plist = theApp.workInfoList.GetNext(pos);
		if(!str.Compare(plist->strSignal))
		{
			isExist = true;
			break;
		}
	}
	if(isExist)
	{

		item = ((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetCurSel();
		//((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetLBText(item, plist->strTitle);
		if(item >= 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetLBText(item , plist->strTitle);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetWindowText(plist->strTitle);
		}
		item = ((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetCurSel();
		//((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetLBText(item, plist->strUnit);
		if(item >= 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetLBText(item , plist->strUnit);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetWindowText(plist->strUnit);
			CWorkUnit* p = new CWorkUnit();
			p->strUnit = plist->strUnit;
			theApp.workUnitList.AddTail(p);
		}
		nTestEditMin.GetWindowText(str);
		plist->leftLimit = _wtoi(str);
		nTestEditMax.GetWindowText(str);
		plist->rightLimit = _wtoi(str);
		plist->curveColor = curveSelectColor;
	}
	else
	{
		CWorkInfo* plist = new CWorkInfo();
		item = ((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetCurSel();
		//((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetLBText(item, plist->strSignal);
		if(item >= 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetLBText(item , plist->strSignal);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetWindowText(plist->strSignal);
		}
		item = ((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetCurSel();
		//((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetLBText(item, plist->strTitle);
		if(item >= 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetLBText(item , plist->strTitle);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->GetWindowText(plist->strTitle);
		}
		item = ((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetCurSel();
		//((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetLBText(item, plist->strUnit);
		if(item >= 0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetLBText(item , plist->strUnit);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->GetWindowText(plist->strUnit);
		}
		nTestEditMin.GetWindowText(str);
		plist->leftLimit = _wtoi(str);
		nTestEditMax.GetWindowText(str);
		plist->rightLimit = _wtoi(str);
		plist->curveColor = curveSelectColor;
		theApp.workInfoList.AddTail(plist);
	}
	RefreshListCtrl();
	MessageBox(_T("����ɹ���"),MB_OK);
}


void CTestDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWorkInfo* plist;
	POSITION pss=mTestList.GetFirstSelectedItemPosition();//pos�����������ţ���
	int i=0;
	if(pss==NULL)
	{
		return;
	}
	else
	{
		while(pss)//�ؼ��������ѡ�����
		{  
			int nIdx = mTestList.GetNextSelectedItem(pss);//������--
			if(nIdx >=0&&nIdx<mTestList.GetItemCount())
			{
				CString strSingle = mTestList.GetItemText(nIdx, 0);
				CString strUnit = mTestList.GetItemText(nIdx, 1);
				mTestList.DeleteItem(nIdx);
				int nRt = ((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->FindString(-1,strSingle);
				int nRt2 = ((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->FindString(-1,strUnit);
				if (nRt!=CB_ERR  )
				{
					((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->DeleteString(nRt);
				}
				if (nRt2!=CB_ERR  )
				{
					((CComboBox*)GetDlgItem(IDC_COMBO_TITLE))->DeleteString(nRt2);
				}
				POSITION pos = theApp.workInfoList.GetHeadPosition();
				POSITION pos2;
				while(pos)
				{
					pos2 = pos;
					plist = theApp.workInfoList.GetNext(pos);
					if(!strSingle.Compare(plist->strSignal))
					{
						theApp.workInfoList.RemoveAt(pos2);
						delete plist;
						break;
					}
				}
				if(nIdx >= mTestList.GetItemCount())
				{
					SetCurveInfo(mTestList.GetItemCount() -1);    //pNMLV->iItemΪѡ�е���Ŀ
				} else
				{
					SetCurveInfo(nIdx);    //pNMLV->iItemΪѡ�е���Ŀ
				}
				break;
			}
		}
	}
}


void CTestDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (pNMLV->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
    {
        SetCurveInfo(pNMLV->iItem);    //pNMLV->iItemΪѡ�е���Ŀ
    }
	*pResult = 0;
}


void CTestDlg::OnCbnSelchangeComboSignal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int item = ((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetCurSel();
	SetCurveInfo(item);
}
