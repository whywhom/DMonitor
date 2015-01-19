// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream> 
using namespace std; 

// CTestDlg 对话框
CString m_unitary[]={_T("mV"),_T("GAPI"),_T("CPS"),_T("us/m"),_T("m"),
	_T("cm"),_T("mm"),_T("uS"),_T("mS"),_T("S"),
	_T("MΩ"),_T("kΩ"),_T("Ω"),_T("Ω.m"),_T("s"),
	_T("S/m"),_T("mS/m"),_T("m/h"),_T("Kg"),_T("Kn"),
	_T("N"),_T("℃"),_T("℃/m"),_T("kg/m^3"),_T("g/cm^3"),
	_T("km"),_T("km^3"),_T("m^3"),_T("dm^3"),_T("m/s^2"),
	_T("mm/s^2"),_T("rad"),_T("mrad"),_T("urad"),_T("°"),
	_T("km^2"),_T("ha"),_T("dm^2"),_T("cm^2"),_T("mm^2"),
	_T("kg/s"),_T("m^3/s"),_T("m^3/min"),_T("m^3/d"),_T("L/s"),
	_T("Std.m3/m3"),_T("t"),_T("Mg/m^3"),_T("pu"),_T("J"),
	_T("Mev"),_T("MW"),_T("KW"),_T("W"),_T("Pa"),
	_T("kPa"),_T("MPa"),_T("ATM"),_T("PSI"),_T("Bq"),
	_T("r/s"),_T("min"),_T("h"),_T("d"),_T("a"),
	_T("m/s"),_T("Pa.s"),_T("mPa.s"),_T("N.s/m^2"),_T("%"),
	_T("NAPI"),_T("inch"),_T("API"),_T("V"),_T("度"),
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


// CTestDlg 消息处理程序


BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
				return TRUE;
			case VK_UP://屏蔽上下方向键
			case VK_DOWN:	
			case VK_SPACE:
			case VK_RETURN://屏蔽回车
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

	// TODO:  在此添加额外的初始化
	CRect   temprect(0,0,320,200);
    CRect rect;
    CRect rc;
    CRect rc2;
    //CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
    CenterWindow();
		
	if(theApp.workInfoList.IsEmpty())
	{
		//初始化
		InitWorkInfoList(_T("深度"),_T("DEPT"),_T("m"), 0, 6000);
		InitWorkInfoList(_T("井温"),_T("TEMP"),_T("C"), -10, 90);
		InitWorkInfoList(_T("电阻率"),_T("RM"),_T("rm"), 0, 40);
		InitWorkInfoList(_T("放射性"),_T("GR"),_T("GAPI"), 0, 2000);
		InitWorkInfoList(_T("磁三分量"),_T("MAG"),_T("mag"),-10000, 10000);
		InitWorkInfoList(_T("磁定位器"),_T("CCL"),_T("CCL"), 0, 1);
		InitCtrl();
		if(!SetCurveInfo(0))
		{
			SendMessage(WM_CLOSE);
		}
	}
	else
	{
		//解析theApp.workInfoList
		InitCtrl();
		if(!SetCurveInfo(0))
		{
			SendMessage(WM_CLOSE);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
	plist->curveColor = RGB(255,0,0); //颜色
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
	mTestList.InsertColumn( 0, _T("原始信号"), LVCFMT_LEFT, 60 ); 
    mTestList.InsertColumn( 1, _T("英文简写"), LVCFMT_LEFT, 60 ); 
	mTestList.InsertColumn( 2, _T("度量单位"), LVCFMT_LEFT, 60 ); 
	mTestList.InsertColumn( 3, _T("取值范围"), LVCFMT_LEFT, 60 ); 
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
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CTestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CTestDlg::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;

	if (dlg.DoModal() == IDOK)
	{
		curveSelectColor = dlg.GetColor();
		mStaticColor.SetStaiticColor(curveSelectColor);
	}
}

void CTestDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;

	nTestEditMin.GetWindowText(str);
	int nMin = _wtoi(str);
	nTestEditMax.GetWindowText(str);
	int nMax = _wtoi(str);
	if(nMax <= nMin)
	{
		MessageBox(_T("最大取值应大于最小取值，请重新输入！"),MB_OK);
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
	MessageBox(_T("保存成功！"),MB_OK);
}


void CTestDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CWorkInfo* plist;
	POSITION pss=mTestList.GetFirstSelectedItemPosition();//pos就是行索引号，晕
	int i=0;
	if(pss==NULL)
	{
		return;
	}
	else
	{
		while(pss)//关键，如果你选择多行
		{  
			int nIdx = mTestList.GetNextSelectedItem(pss);//多少行--
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
					SetCurveInfo(mTestList.GetItemCount() -1);    //pNMLV->iItem为选中的项目
				} else
				{
					SetCurveInfo(nIdx);    //pNMLV->iItem为选中的项目
				}
				break;
			}
		}
	}
}


void CTestDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMLV->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
    {
        SetCurveInfo(pNMLV->iItem);    //pNMLV->iItem为选中的项目
    }
	*pResult = 0;
}


void CTestDlg::OnCbnSelchangeComboSignal()
{
	// TODO: 在此添加控件通知处理程序代码
	int item = ((CComboBox*)GetDlgItem(IDC_COMBO_SIGNAL))->GetCurSel();
	SetCurveInfo(item);
}
