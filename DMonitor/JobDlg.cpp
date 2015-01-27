// JobDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobDlg.h"
#include "afxdialogex.h"
#include "JobCopyDlg.h"
#include "JobInfoDlg.h"

#include <fstream> 
#include <cassert> 
#include "json\include\json.h"
using namespace std;
// CJobDlg �Ի���

IMPLEMENT_DYNAMIC(CJobDlg, CDialog)

CJobDlg::CJobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobDlg::IDD, pParent)
{
	
}

CJobDlg::~CJobDlg()
{
		//�ر����ݿ�
	if (m_DataBase.IsOpen())
	m_DataBase.Close();
}

void CJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZCW_JOB_TREE, m_treeCtrl);
	DDX_Control(pDX, IDC_ZCW_JOB_TREE, m_treeCtrl);
	DDX_Control(pDX, IDC_ZCW_JOBTREE_LEFT, m_JobTreeLeft);
}


BEGIN_MESSAGE_MAP(CJobDlg, CDialog)
	ON_COMMAND(ID_JOB_NEW, &CJobDlg::OnJobNew)
	ON_COMMAND(ID_JOB_DEL, &CJobDlg::OnJobDel)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_JOB_LOAD, &CJobDlg::OnJobLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &CJobDlg::OnBnClickedButton1)
	ON_COMMAND(ID_TOOL_NEW, &CJobDlg::OnToolNew)
	ON_COMMAND(ID_TOOL_OPEN, &CJobDlg::OnToolOpen)
	ON_COMMAND(ID_TOOL_COPY, &CJobDlg::OnToolCopy)
	ON_COMMAND(ID_TOOL_DEL, &CJobDlg::OnToolDel)
	ON_BN_CLICKED(IDC_ZCW_ADDITEM, &CJobDlg::OnBnClickedZcwAdditem)
	ON_BN_CLICKED(IDC_ZCW_DELITEM, &CJobDlg::OnBnClickedZcwDelitem)
	ON_NOTIFY(NM_DBLCLK, IDC_ZCW_JOB_TREE, &CJobDlg::OnNMDblclkZcwJobTree)
	ON_NOTIFY(NM_DBLCLK, IDC_ZCW_JOBTREE_LEFT, &CJobDlg::OnNMDblclkZcwJobtreeLeft)
	ON_NOTIFY(NM_RCLICK, IDC_ZCW_JOB_TREE, &CJobDlg::OnNMRClickZcwJobTree)
END_MESSAGE_MAP()


// CJobDlg ��Ϣ�������


void CJobDlg::OnJobNew()
{
	// TODO: �ڴ���������������
	CJobInfoDlg m_jiDlg;	
	
	if(m_jiDlg.DoModal()==IDOK){			
		JobAdd(m_jiDlg.m_jobName);
	}
}
void CJobDlg::DisplayTreeLeft()
{
	m_JobTreeLeft.DeleteAllItems();
	//���οؼ���ʼ��
	
	//һ���ӽڵ�		
	 try{						   	  			   
				CDaoRecordset rs(&m_DataBase);
				COleVariant OleVariant ;
				//���Tool���ӽڵ�
				rs.Open(dbOpenDynaset,_T("SELECT distinct(jobname) FROM JobList"));
				while(!rs.IsEOF()){					
					rs.GetFieldValue (0,OleVariant);
					HTREEITEM hParent=m_JobTreeLeft.InsertItem(OleVariant.bstrVal,TVI_ROOT);
					DisplayItem(hParent,OleVariant.bstrVal);
					m_JobTreeLeft.Expand(hParent,TVE_EXPAND);
					rs.MoveNext();
				}
				rs.Close();     				
	 } catch(CDaoException *e){		
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}
void CJobDlg::DisplayItem(HTREEITEM hParent,LPCTSTR strName)
{
	 try{						   	  			   
				CDaoRecordset rs(&m_DataBase);
				COleVariant OleVariant ;
				CString JobName=strName;
				//���Tool���ӽڵ�
				rs.Open(dbOpenDynaset,_T("SELECT ToolLabel FROM JobList where JobName='")+JobName+_T("'"));
				while(!rs.IsEOF()){					
					rs.GetFieldValue (0,OleVariant);
					if(OleVariant.bstrVal!=NULL){
					m_JobTreeLeft.InsertItem(OleVariant.bstrVal,hParent);	
					}
					rs.MoveNext();
				}
				rs.Close();   				
	 } catch(CDaoException *e){		
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}
void CJobDlg::DisplayTreeRight()
{

}

void CJobDlg::JobCreat()
{
	CString jobDB=m_Path+_T("job.list");
	try{
			m_DataBase.Create(jobDB);//����½���ҵ�򴴽����ݿ�
				CDaoTableDef td(&m_DataBase);        //��������						
				
				//����JobList��
				td.Create(_T("JobList"));
				td.CreateField(_T("JobName"),dbText,50,0L);	
				td.CreateField(_T("ToolLabel"),dbText,50,0L);	
			    td.Append();
				td.Close();
				
				//����TooList��
				td.Create(_T("ToolList"));
				td.CreateField(_T("LABEL"),dbText,50,0L);				
			    td.Append();
				td.Close();

				//����CurveList��
				td.Create(_T("CurveList"));
				td.CreateField(_T("LABEL"),dbText,50,0L);				
			    td.Append();
				td.Close();

				//����OrignList��
				td.Create(_T("OriginList"));
				td.CreateField(_T("LABEL"),dbText,50,0L);				
			    td.Append();
				td.Close();

		}catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
        }
}

void CJobDlg::JobAdd(CString jobName)
{
	 try{				
			   //�½����ݿ��¼			  			   
				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM JobList"));			
			    rs.AddNew();
				rs.SetFieldValue(0,COleVariant(jobName));
				rs.Update();					
				rs.Close();	
				DisplayTreeLeft();
	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}


BOOL CJobDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_JobTreeLeft.ModifyStyle(0,TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES|TVS_SHOWSELALWAYS);
	m_treeCtrl.ModifyStyle(0,TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES|TVS_SHOWSELALWAYS);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
		CString jobDB=m_Path+_T("job.list");//�����ҵ���ݿⲻ���ھʹ�����������ھʹ�
		fstream _file;
		_file.open(jobDB,ios::in);
		if(!_file){		 
			JobCreat();
		}else{
			m_DataBase.Open(jobDB);	
		}
    DisplayTreeLeft();
	SetWindowText(m_Title); 	
	GetDlgItem(IDC_ZCW_JOB_TREE_TITLE)->SetWindowText(m_TreeTitle);
	m_treeCtrl.ModifyStyle(0,TVS_HASBUTTONS   |   TVS_LINESATROOT   |   TVS_HASLINES);	
	m_treeCtrl.DisplayTree (m_Path,TRUE);
	OnExpandtree();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CJobDlg::OnExpandtree() //չ�����нڵ� 
{ 
	// TODO: Add your command handler code here 
	ExpandTreeNode(m_treeCtrl.GetRootItem()); 
 
}
 
void CJobDlg::ExpandTreeNode(HTREEITEM hTreeItem)
{
	if(!m_treeCtrl.ItemHasChildren(hTreeItem))
    {
        return;
    }
    HTREEITEM hNextItem = m_treeCtrl.GetChildItem(hTreeItem);
    while (hNextItem != NULL)
    {
        ExpandTreeNode(hNextItem);
        hNextItem = m_treeCtrl.GetNextItem(hNextItem, TVGN_NEXT);
    }
    m_treeCtrl.Expand(hTreeItem,TVE_EXPAND);
}

void CJobDlg::OnJobDel()
{
	// TODO: �ڴ���������������
	HTREEITEM sel_job=m_JobTreeLeft.GetSelectedItem(); 
    CString JobName=m_JobTreeLeft.GetItemText(sel_job);//��ȡ�ļ�·������
	HTREEITEM hPar=m_JobTreeLeft.GetParentItem(sel_job);//���ڵ�

	if(!hPar){//������һ���ڵ�
		//MessageBox(JobName,MB_OK);
		if(MessageBox(_T("��ȷ��Ҫɾ����ҵ")+JobName+_T("��?"),_T("����"), MB_OKCANCEL )==IDOK)
		{
			 try{				
			   //�½����ݿ��¼			  			   
				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM JobList where JobName='")+JobName+_T("'"));	
				while(!rs.IsEOF()){					
					rs.Delete();	
					rs.MoveNext();
				}
	
				DisplayTreeLeft();
			} catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
			}	
		}
	}
}


void CJobDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if(receiveFlag == 1)
	{
		OnJobNew();
	}
}


void CJobDlg::OnJobLoad()
{
	// TODO: �ڴ���������������
	HTREEITEM sel_job=m_JobTreeLeft.GetSelectedItem(); 
    CString JobName=m_JobTreeLeft.GetItemText(sel_job);//��ȡ��ҵ����
	HTREEITEM hPar=m_JobTreeLeft.GetParentItem(sel_job);//���ڵ�

	if(!hPar&&sel_job){//������һ���ڵ㣨��ҵ��
		if(MessageBox(_T("��ȷ��Ҫ������ҵ")+JobName+_T("��?"),_T("��ʾ"), MB_OKCANCEL )==IDOK)
		{
		  LoadJob(JobName);		 
		} 
	}
	else{
		MessageBox(_T("����ѡ����ҵ"));
	}

}
void CJobDlg::LoadJob(CString JobName){
		//����Json�ķ���
		Json::Value root;//��ʾһ��json��ʽ�Ķ���
		Json::Value arrayTool;
		Json::Value arrayCurve;
		Json::Value arrayOrigin;
        Json::Value arrayControl;
        Json::Value arrayPower;

		Json::Value itemTool;
		Json::Value itemCurve;
		Json::Value itemOrigin;
        Json::Value itemControl;
        Json::Value itemPower;
		Json::FastWriter writer; 

		CDaoRecordset rsJob(&m_DataBase);
		COleVariant OleVariantJob ;
		CString Label;
		rsJob.Open(dbOpenDynaset,_T("SELECT ToolLabel FROM JobList where JobName='"+JobName+"' and ToolLabel<>''" ));
			while(!rsJob.IsEOF()){					
				rsJob.GetFieldValue (0,OleVariantJob); 
				CString ToolLabel=OleVariantJob.bstrVal;
				//Label=ToolLabel+_T(".tools");

		CDaoDatabase c_DataBase;
		c_DataBase.Open(m_Path+ToolLabel+_T(".tools"));
		CDaoRecordset rs(&c_DataBase);
		COleVariant OleVariant ;

		//���Tool���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM TOOL" );		
		while(!rs.IsEOF()){		
			rs.GetFieldValue (0,OleVariant);
			_bstr_t bstr_t0(OleVariant.bstrVal);  
            std::string str0(bstr_t0);  
			itemTool["Label"]=str0;	
			rs.GetFieldValue (1,OleVariant);
			_bstr_t bstr_t1(OleVariant.bstrVal); 
            std::string str1(bstr_t1); 
			itemTool["Type"]=str1;
			rs.GetFieldValue (2,OleVariant);
			_bstr_t bstr_t2(OleVariant.bstrVal);  
            std::string str2(bstr_t2);  
			itemTool["SN"]=str2;			
			rs.GetFieldValue (3,OleVariant);
			itemTool["Length"]=OleVariant.iVal;
			rs.GetFieldValue (4,OleVariant);
			itemTool["Weight"]=OleVariant.iVal;
			rs.GetFieldValue (5,OleVariant);
			itemTool["OuteRdiam"]=OleVariant.fltVal;
			rs.GetFieldValue (6,OleVariant);
			_bstr_t bstr_t6(OleVariant.bstrVal);  
            std::string str6(bstr_t6);  
			itemTool["Speed"]=str6;			
			arrayTool.append(itemTool);//json�ڵ�		
			rs.MoveNext();
		}
		rs.Close();     
		//���Curve���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Curve" );		
		while(!rs.IsEOF()){
			rs.GetFieldValue (0,OleVariant);
			_bstr_t bstr_c0(OleVariant.bstrVal);  
            std::string str_c0(bstr_c0); 
			itemCurve["Label"]=str_c0;		

			rs.GetFieldValue (1,OleVariant);
			_bstr_t bstr_c1(OleVariant.bstrVal);  
            std::string str_c1(bstr_c1); 
			itemCurve["Unit"]=str_c1;

			rs.GetFieldValue (2,OleVariant);
			_bstr_t bstr_c2(OleVariant.bstrVal);  
            std::string str_c2(bstr_c2); 
			itemCurve["Filter"]=str_c2;

			rs.GetFieldValue (3,OleVariant);
			_bstr_t bstr_c3(OleVariant.bstrVal);  
            std::string str_c3(bstr_c3);  
			itemCurve["Title"]=str_c3;

			rs.GetFieldValue (4,OleVariant);			
			itemCurve["MIN"]=OleVariant.dblVal;
			rs.GetFieldValue (5,OleVariant);			
			itemCurve["MAX"]=OleVariant.dblVal;
			rs.GetFieldValue (6,OleVariant);
			itemCurve["COLOR_R"]=OleVariant.iVal;
			rs.GetFieldValue (7,OleVariant);
			itemCurve["COLOR_G"]=OleVariant.iVal;
			rs.GetFieldValue (8,OleVariant);
			itemCurve["COLOR_B"]=OleVariant.iVal;
			rs.GetFieldValue (9,OleVariant);
			itemCurve["TRACK"]=OleVariant.iVal;
			rs.GetFieldValue (10,OleVariant);
			itemCurve["LINETYPE"]=OleVariant.iVal;
			rs.GetFieldValue (11,OleVariant);
			itemCurve["LINEWIDTH"]=OleVariant.iVal;
			arrayCurve.append(itemCurve);
			theApp.m_JobCurves.AddTail(theApp.m_JobCurve);
			rs.MoveNext();
		}
		rs.Close();     

		//���Origin���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Origin" );		
		while(!rs.IsEOF()){			
			rs.GetFieldValue (0,OleVariant);			
			_bstr_t bstr_o0(OleVariant.bstrVal);  
            std::string str_o0(bstr_o0);  
			itemOrigin["Label"]=str_o0;			

			rs.GetFieldValue (1,OleVariant);
			_bstr_t bstr_o1(OleVariant.bstrVal);  
            std::string str_o1(bstr_o1); 
			itemOrigin["Unit"]=str_o1;

			rs.GetFieldValue (2,OleVariant);
			_bstr_t bstr_o2(OleVariant.bstrVal);  
            std::string str_o2(bstr_o2); 
			itemOrigin["Filter"]=str_o2;
			arrayOrigin.append(itemOrigin);			
			rs.MoveNext();
		}
		rs.Close();  

		//���Control���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Control" );		
		while(!rs.IsEOF()){			
			rs.GetFieldValue (0,OleVariant);			
			_bstr_t bstr_ct0(OleVariant.bstrVal);  
            std::string str_ct0(bstr_ct0);  
			itemControl["Label"]=str_ct0;	
			rs.GetFieldValue (1,OleVariant);			
			_bstr_t bstr_ct1(OleVariant.bstrVal);  
            std::string str_ct1(bstr_ct1);  
			itemControl["Units"]=str_ct1;	
			rs.GetFieldValue (2,OleVariant);			
			_bstr_t bstr_ct2(OleVariant.bstrVal);  
            std::string str_ct2(bstr_ct2);  
			itemControl["DataValue"]=str_ct2;
			arrayControl.append(itemControl);			
			rs.MoveNext();
		}
		rs.Close();  

		//���Power���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Power" );		
		while(!rs.IsEOF()){			
			rs.GetFieldValue (0,OleVariant);			
			_bstr_t bstr_p0(OleVariant.bstrVal);  
            std::string strp0(bstr_p0);  
			itemPower["Label"]=strp0;
			rs.GetFieldValue (1,OleVariant);			
			itemPower["Cable"]=OleVariant.iVal;
			rs.GetFieldValue (2,OleVariant);			
			itemPower["Type"]=OleVariant.iVal;
			rs.GetFieldValue (3,OleVariant);			
			itemPower["Voltage"]=OleVariant.iVal;
			rs.GetFieldValue (4,OleVariant);			
			itemPower["ElectricCurrent"]=OleVariant.iVal;
			rs.GetFieldValue (5,OleVariant);			
			_bstr_t bstr_p6(OleVariant.bstrVal);  
            std::string strp6(bstr_p6);  
			itemPower["MODE"]=strp6;
			arrayPower.append(itemPower);			
			rs.MoveNext();
		}
		rs.Close(); 
		rsJob.MoveNext();
		}
		rsJob.Close();  			
		
		root["job"]="CurrentJob";		
		root["arrayTool"]=arrayTool;	
		root["arrayCurve"]=arrayCurve;	
		root["arrayOrigin"]=arrayOrigin;	
		root["arrayControl"]=arrayControl;
		root["arrayPower"]=arrayPower;
		//д��CurrentJob.json�ļ�
		
		
		//�ļ��洢��jobs�ļ���,json��ʽ		
		CString CurrentJob=m_Path+_T("currentjob.json");
		_bstr_t bstr_j1(CurrentJob);  
        std::string s(bstr_j1);  
		
		std::string json_file = writer.write(root);   
		ofstream ofs; 
		ofs.open(s);
		assert(ofs.is_open()); 
		ofs<<json_file; 
		ofs.close();
		//֪ͨ�����ߴ���
		::SendMessage(fatherHwnd,WM_JOBLOAD_OK, 0x00, 0x0000);
		SendMessage(WM_CLOSE);
}
/* 
void CJobDlg::LoadFile(CString strPath){
		CDaoDatabase c_DataBase;
		c_DataBase.Open(strPath);
		CDaoRecordset rs(&c_DataBase);
		COleVariant OleVariant ;

		//����Json�ķ���
		Json::Value root;//��ʾһ��json��ʽ�Ķ���
		Json::Value arrayTool;
		Json::Value arrayCurve;
		Json::Value arrayOrigin;
        Json::Value arrayControl;
        Json::Value arrayPower;

		Json::Value itemTool;
		Json::Value itemCurve;
		Json::Value itemOrigin;
        Json::Value itemControl;
        Json::Value itemPower;
		Json::FastWriter writer; 

		//���Tool���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM TOOL" );		
		while(!rs.IsEOF()){	
			theApp.m_JobTool=new CDMoniterApp::JobTool; 	

			rs.GetFieldValue (0,OleVariant);
			theApp.m_JobTool->Label=OleVariant.bstrVal;
			_bstr_t bstr_t0(OleVariant.bstrVal);  
            std::string str0(bstr_t0);  
			itemTool["Label"]=str0;			

			rs.GetFieldValue (1,OleVariant);
			theApp.m_JobTool->Type=OleVariant.bstrVal;
			_bstr_t bstr_t1(OleVariant.bstrVal);  
            std::string str1(bstr_t1);  
			itemTool["Type"]=str1;			

			rs.GetFieldValue (2,OleVariant);
			theApp.m_JobTool->SN=OleVariant.bstrVal;
			_bstr_t bstr_t2(OleVariant.bstrVal);  
            std::string str2(bstr_t2);  
			itemTool["SN"]=str2;			

			rs.GetFieldValue (3,OleVariant);
			itemTool["Length"]=OleVariant.fltVal;
			theApp.m_JobTool->Length=OleVariant.fltVal;

			rs.GetFieldValue (4,OleVariant);
			itemTool["Weight"]=OleVariant.fltVal;
			theApp.m_JobTool->Weight=OleVariant.fltVal;

			rs.GetFieldValue (5,OleVariant);
			itemTool["OuteRdiam"]=OleVariant.fltVal;
			theApp.m_JobTool->OUTERDIAMATER=OleVariant.fltVal;

			rs.GetFieldValue (6,OleVariant);
			theApp.m_JobTool->Speed=OleVariant.bstrVal;
			_bstr_t bstr_t6(OleVariant.bstrVal);  
            std::string str6(bstr_t6);  
			itemTool["Speed"]=str6;			

			arrayTool.append(itemTool);//json�ڵ�		
			theApp.m_JobTools.AddTail(theApp.m_JobTool);
			
			rs.MoveNext();
		}
		rs.Close();     
		//���Curve���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Curve" );		
		while(!rs.IsEOF()){
			theApp.m_JobCurve=new CDMoniterApp::JobCurve;
			rs.GetFieldValue (0,OleVariant);
			theApp.m_JobCurve->Label=OleVariant.bstrVal;
			_bstr_t bstr_c0(OleVariant.bstrVal);  
            std::string str_c0(bstr_c0); 
			itemCurve["Label"]=str_c0;			
			rs.GetFieldValue (1,OleVariant);
			theApp.m_JobCurve->UNIT=OleVariant.iVal;
			itemCurve["Unit"]=OleVariant.iVal;
			rs.GetFieldValue (2,OleVariant);
			theApp.m_JobCurve->FILTER=OleVariant.iVal;
			itemCurve["Filter"]=OleVariant.iVal;
			arrayCurve.append(itemCurve);
			theApp.m_JobCurves.AddTail(theApp.m_JobCurve);
			rs.MoveNext();
		}
		rs.Close();     

		//���Origin���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Origin" );		
		while(!rs.IsEOF()){
			theApp.m_JobOrigin=new CDMoniterApp::JobOrigin;
			rs.GetFieldValue (0,OleVariant);
			theApp.m_JobOrigin->Label=OleVariant.bstrVal;
			_bstr_t bstr_o0(OleVariant.bstrVal);  
            std::string str_o0(bstr_o0);  
			itemOrigin["Label"]=str_o0;			
			rs.GetFieldValue (1,OleVariant);
			theApp.m_JobOrigin->UNIT=OleVariant.iVal;
			itemOrigin["Unit"]=OleVariant.iVal;
			rs.GetFieldValue (2,OleVariant);
			theApp.m_JobOrigin->FILTER=OleVariant.iVal;
			itemOrigin["Filter"]=OleVariant.iVal;
			arrayOrigin.append(itemOrigin);
			theApp.m_JobOrigins.AddTail(theApp.m_JobOrigin);
			rs.MoveNext();
		}
		rs.Close();  

		//���Control���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Control" );		
		while(!rs.IsEOF()){
			theApp.m_JobControl=new CDMoniterApp::JobControl;
			rs.GetFieldValue (0,OleVariant);
			theApp.m_JobControl->Label=OleVariant.bstrVal;
			_bstr_t bstr_ct0(OleVariant.bstrVal);  
            std::string str_ct0(bstr_ct0);  
			itemControl["Label"]=str_ct0;	

			rs.GetFieldValue (1,OleVariant);
			theApp.m_JobControl->UNITS=OleVariant.bstrVal;
			_bstr_t bstr_ct1(OleVariant.bstrVal);  
            std::string str_ct1(bstr_ct1);  
			itemControl["Units"]=str_ct1;	

			rs.GetFieldValue (2,OleVariant);
			theApp.m_JobControl->DATAVALUE=OleVariant.bstrVal;
			_bstr_t bstr_ct2(OleVariant.bstrVal);  
            std::string str_ct2(bstr_ct2);  
			itemControl["DataValue"]=str_ct2;

			arrayControl.append(itemControl);
			theApp.m_JobControls.AddTail(theApp.m_JobControl);
			rs.MoveNext();
		}
		rs.Close();  

		//���Power���ӽڵ�
		rs.Open(dbOpenDynaset, L"SELECT * FROM Power" );		
		while(!rs.IsEOF()){
			theApp.m_JobPower=new CDMoniterApp::JobPower;
			rs.GetFieldValue (0,OleVariant);
			theApp.m_JobPower->Label=OleVariant.bstrVal;
			_bstr_t bstr_p0(OleVariant.bstrVal);  
            std::string strp0(bstr_p0);  
			itemPower["Label"]=strp0;
			rs.GetFieldValue (1,OleVariant);
			theApp.m_JobPower->CABLE=OleVariant.iVal;
			itemPower["Cable"]=OleVariant.iVal;
			rs.GetFieldValue (2,OleVariant);
			theApp.m_JobPower->TYPE=OleVariant.iVal;
			itemPower["Type"]=OleVariant.iVal;
			rs.GetFieldValue (3,OleVariant);
			theApp.m_JobPower->VOLTAGE=OleVariant.iVal;
			itemPower["Voltage"]=OleVariant.iVal;
			rs.GetFieldValue (4,OleVariant);
			theApp.m_JobPower->ElectricCurrent=OleVariant.iVal;
			itemPower["ElectricCurrent"]=OleVariant.iVal;
			rs.GetFieldValue (5,OleVariant);
			theApp.m_JobPower->MODE=OleVariant.bstrVal;
			_bstr_t bstr_p6(OleVariant.bstrVal);  
            std::string strp6(bstr_p6);  
			itemPower["MODE"]=strp6;
			arrayPower.append(itemPower);
			theApp.m_JobPowers.AddTail(theApp.m_JobPower);
			rs.MoveNext();
		}
		rs.Close(); 
		
		root["job"]="CurrentJob";		
		root["arrayTool"]=arrayTool;	
		root["arrayCurve"]=arrayCurve;	
		root["arrayOrigin"]=arrayOrigin;	
		root["arrayControl"]=arrayControl;
		root["arrayPower"]=arrayPower;
		//д��CurrentJob.json�ļ�
		
		
		//�ļ��洢��jobs�ļ���,json��ʽ		
		char *chr=new char[theApp.JobPath.GetLength()+1];
		WideCharToMultiByte(CP_ACP,0,theApp.JobPath.GetBuffer(),-1,chr,theApp.JobPath.GetLength()+1,NULL,NULL);
		std::string s = chr; 

		std::string json_file = writer.write(root);   
		ofstream ofs; 
		ofs.open(s+"currentjob.json"); 
		assert(ofs.is_open()); 
		ofs<<json_file; 
		delete chr;
}
*/
void CJobDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�˴�������JobTools��������������
	/*POSITION pos=theApp.m_JobTools.GetHeadPosition();	
	CString LabelDemo;//��ʾ��ҵ������Tool��Labelֵ��-������
	if(pos!=NULL){
		while(pos)
		{
			theApp.m_JobTool=theApp.m_JobTools.GetNext(pos); 	
			LabelDemo+=theApp.m_JobTool->Label+_T("-");
		}
		MessageBox(LabelDemo);
	}*/
}

BOOL CJobDlg::PreTranslateMessage(MSG* pMsg)
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


void CJobDlg::OnToolNew()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(FALSE,_T(""),_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("tools files(*.tools)|*.tools|"));//���챣���ļ��Ի���
	dlg.m_ofn.lpstrInitialDir=m_Path;
    if(dlg.DoModal()==IDOK)//��ʾ�����ļ��Ի���
	{
		int Where=dlg.GetPathName().ReverseFind('\\');
		CString Label=dlg.GetPathName().Right(dlg.GetPathName().GetLength()-1-Where);
		Label=Label.Left(Label.ReverseFind('.'));//���������Labelֵ,���ToolList�в����������
		CDaoRecordset rs(&m_DataBase);						
		rs.Open(dbOpenDynaset,_T("SELECT * FROM ToolList where LABEL='")+Label+_T("'"));
		if(rs.IsBOF()){
		rs.AddNew();
		rs.SetFieldValue(0,COleVariant(Label));
		rs.Update();
		rs.Close();
		//////////////�������༭�Ի���
		CJobEditDlg m_jeDlg;
		m_jeDlg.m_jobName=dlg.GetPathName();//��ȡ�ļ�·������
		m_jeDlg.m_Path=m_Path;
		m_jeDlg.m_Open=FALSE;
		if(m_jeDlg.DoModal()==IDOK){
		m_treeCtrl.ModifyStyle(0,TVS_HASBUTTONS   |   TVS_LINESATROOT   |   TVS_HASLINES);	
		m_treeCtrl.DisplayTree (m_Path,TRUE);
		}
		//////////////
		}else{
		MessageBox(_T("���ܸ���ͬ������"));
		}
	}
}


void CJobDlg::OnToolOpen()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
		CJobEditDlg m_jeDlg;
		HTREEITEM sel_htem=m_treeCtrl.GetSelectedItem(); 
		 CString strPath=m_treeCtrl.GetFullPath(sel_htem);//��ȡ�ļ�·������
		if(!m_treeCtrl.FindSubDir(strPath)){//���ܱ༭�ǿ���Ŀ¼
		m_jeDlg.m_jobName=strPath;//��ȡ�ļ�·������
		m_jeDlg.m_Path=m_Path;
		m_jeDlg.m_Open=TRUE;
		m_jeDlg.DoModal();
		}
}


void CJobDlg::OnToolCopy()
{
	// TODO: �ڴ���������������
	CJobCopyDlg m_jcDlg;
	HTREEITEM sel_htem=m_treeCtrl.GetSelectedItem(); //��ǰ�ڵ�
	HTREEITEM par_htem=m_treeCtrl.GetParentItem(sel_htem); //���ڵ�
	CString strPath=m_treeCtrl.GetFullPath(sel_htem);	
	if(!m_treeCtrl.FindSubDir(strPath)){//���ܸ���Ŀ¼
    CString stroldName=m_treeCtrl.GetItemText(sel_htem);
	m_jcDlg.m_oldName=stroldName.Left(stroldName.Find(_T(".")));//��ȡ�ļ���
	if(m_jcDlg.DoModal()==IDOK){
		CString strNewPath=m_treeCtrl.GetFullPath(par_htem)+_T("\\")+m_jcDlg.m_newName+_T(".tools");//����ҵ·��
		if(GetFileAttributes(strNewPath)==-1L){
		CopyFile(strPath,strNewPath,TRUE);
		m_treeCtrl.AddItem(par_htem,strNewPath);//��ӽڵ�
		}else{
			MessageBox(strNewPath+_T("�Ѵ���"),MB_OK);
		}
	}
	}
}


void CJobDlg::OnToolDel()
{
	// TODO: �ڴ���������������
	HTREEITEM sel_htem=m_treeCtrl.GetSelectedItem(); 
    CString strPath=m_treeCtrl.GetFullPath(sel_htem);//��ȡ�ļ�·������
	int Where=strPath.ReverseFind('\\');
	CString LabelName=strPath.Right(strPath.GetLength()-1-Where);
	LabelName=LabelName.Left(LabelName.ReverseFind('.'));
	if(!m_treeCtrl.FindSubDir(strPath)){//����ɾ���ǿ���Ŀ¼
		if(MessageBox(_T("��ȷ��Ҫɾ������")+LabelName+_T("��?�˲���Ҳ��ɾ��������ҵ�Ը�����������"),_T("����"), MB_OKCANCEL )==IDOK)
		{
		  DeleteFile(strPath);//ɾ���ļ�
		  m_treeCtrl.DeleteItem(sel_htem);//ɾ���ڵ�

		  CDaoRecordset rs(&m_DataBase);//ɾ��ToolList������
		  rs.Open(dbOpenDynaset,_T("SELECT * FROM ToolList where Label='")+LabelName+_T("'"));
		  rs.Delete();					
		  rs.Close();

		  rs.Open(dbOpenDynaset,_T("SELECT * FROM JobList where ToolLabel='")+LabelName+_T("'"));	
			while(!rs.IsEOF()){//ɾ��JobList������
				rs.Delete();	
				rs.MoveNext();
			}
		  rs.Close();
		  DisplayTreeLeft();
		} 
	}
}

void CJobDlg::OnBnClickedZcwAdditem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM sel_tool=m_treeCtrl.GetSelectedItem(); 
    CString strPath=m_treeCtrl.GetFullPath(sel_tool);//��ȡ�ļ�·������
	int Where=strPath.ReverseFind('\\');
	CString LabelName=strPath.Right(strPath.GetLength()-1-Where);
	LabelName=LabelName.Left(LabelName.ReverseFind('.'));

	HTREEITEM sel_job=m_JobTreeLeft.GetSelectedItem(); 
    CString strJobName=m_JobTreeLeft.GetItemText(sel_job);//��ȡ�ļ�·������
	HTREEITEM hPar=m_JobTreeLeft.GetParentItem(sel_job);//���ڵ�

	if(m_treeCtrl.FindSubDir(strPath)){
		MessageBox(_T("��ѡ������"));
	}else if((!sel_job)||hPar){
	    MessageBox(_T("��ѡ����ҵ"));
	}else{		
		 try{				
			   //�½����ݿ��¼			  			   
				CDaoRecordset rs(&m_DataBase);	
				rs.Open(dbOpenDynaset,_T("SELECT * FROM JobList where ToolLabel='")+LabelName+_T("' and JobName='")+strJobName+_T("'"));
				if(rs.IsBOF()){					
			    rs.AddNew();
				rs.SetFieldValue(0,COleVariant(strJobName));	
				rs.SetFieldValue(1,COleVariant(LabelName));
				rs.Update();					
				rs.Close();			
				DisplayTreeLeft();
				}else{
				MessageBox(strJobName+_T("�Ѿ���������")+LabelName);
				}
		} catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
		}	
	}
}


void CJobDlg::OnBnClickedZcwDelitem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM sel_job=m_JobTreeLeft.GetSelectedItem();    
	HTREEITEM hPar=m_JobTreeLeft.GetParentItem(sel_job);//���ڵ�
	CString LabelName=m_JobTreeLeft.GetItemText(sel_job);//��ȡ��������
	if(hPar){//��߱����Ƕ����ڵ�		
		 try{				
			   //�½����ݿ��¼							
				CString JobName=m_JobTreeLeft.GetItemText(hPar);//��ȡ��ҵ����
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM JobList where ToolLabel='")+LabelName+_T("' and JobName='")+JobName+_T("'"));
				rs.Delete();					
				rs.Close();		
				DisplayTreeLeft();
		} catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
		}	
	}
}


void CJobDlg::OnNMDblclkZcwJobTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	OnToolOpen();
}


void CJobDlg::OnNMDblclkZcwJobtreeLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CJobDlg::OnNMRClickZcwJobTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//*pResult = 0;
	CPoint  cp; 
	GetCursorPos(&cp); 
	m_treeCtrl.ScreenToClient(&cp);  //m_TREE��CTreeCtrl�ؼ�������
	HTREEITEM  titem = m_treeCtrl.HitTest(cp,NULL); //��ȡ��ǰ����Ҽ�������λ���µ�item
	//m_treeCtrl.SetItemState(titem, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK); // ѡ��
	CString str = m_treeCtrl.GetItemText(titem);
	HTREEITEM sel_htem=m_treeCtrl.GetSelectedItem(); 
	if(sel_htem != titem)
	{
		return;
	}
	CString strPath=m_treeCtrl.GetFullPath(sel_htem);//��ȡ�ļ�·������
	if(!m_treeCtrl.FindSubDir(strPath))
	{
		CPoint point;
        GetCursorPos(&point);
		CMenu menu;
		menu.LoadMenu(IDR_TOOL);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | 
		TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
	}
}
