// JobEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DMonitor.h"
#include "JobEditDlg.h"
#include "afxdialogex.h"


// CJobEditDlg �Ի���

IMPLEMENT_DYNAMIC(CJobEditDlg, CDialog)

CJobEditDlg::CJobEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobEditDlg::IDD, pParent)
	, m_jobName(_T(""))
	, m_Open(false)
{
	
}

CJobEditDlg::~CJobEditDlg()
{
	//�ر����ݿ�
	if (m_DataBase.IsOpen())
	m_DataBase.Close();
}

void CJobEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZCW_JOBEDIT_JOBNAME, m_jobName);
	DDX_Control(pDX, IDC_ZCW_JOBEDIT_TREE, m_jeTree);
}

BEGIN_MESSAGE_MAP(CJobEditDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_ZCW_JOBEDIT_TREE, &CJobEditDlg::OnSelchangedJobeditTree)
	ON_BN_CLICKED(IDC_ZCW_JOBEDIT_ADD, &CJobEditDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_ZCW_JOBEDIT_DELETE, &CJobEditDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ZCW_JOBEDIT_UPDATE, &CJobEditDlg::OnBnClickedUpdate)
	ON_BN_CLICKED(IDC_ZCW_JOBEDIT_IMPORT, &CJobEditDlg::OnBnClickedZcwJobeditImport)
	ON_BN_CLICKED(IDC_ZCW_JOBEDIT_EXPORT, &CJobEditDlg::OnBnClickedZcwJobeditExport)
END_MESSAGE_MAP()


// CJobEditDlg ��Ϣ�������

BOOL CJobEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString jobDB=m_Path+_T("job.list");//�����ҵ���ݿⲻ���ھʹ�����������ھʹ�
	m_DBJobList.Open(jobDB);
	//MessageBox(jobDB);
	if(m_Open==TRUE){//����Ǵ���ҵ�������������ݿ����ݳ�ʼ������
		m_DataBase.Open(m_jobName);	
		//ToolInitOpen();
	}else{
		JobInit();	
		//ToolInit();			
	}	

	ToolInit();
	m_jeTree.ModifyStyle(0,TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES|TVS_SHOWSELALWAYS);
	DisplayTree(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CJobEditDlg::DisplayTree(int EditTable){
	m_jeTree.DeleteAllItems();
	//���οؼ���ʼ��
	HTREEITEM root1=m_jeTree.InsertItem(_T("������Ϣ"),TVI_ROOT);
	m_jeTree.SetItemData(root1,(DWORD)1);
	HTREEITEM root2=m_jeTree.InsertItem(_T("������Ϣ"),TVI_ROOT);
	m_jeTree.SetItemData(root2,(DWORD)2);
	HTREEITEM root3=m_jeTree.InsertItem(_T("ԭʼ�ź�"),TVI_ROOT);
	m_jeTree.SetItemData(root3,(DWORD)3);
	HTREEITEM root4=m_jeTree.InsertItem(_T("������Ϣ"),TVI_ROOT);
	m_jeTree.SetItemData(root4,(DWORD)4);
	HTREEITEM root5=m_jeTree.InsertItem(_T("�ӵ����"),TVI_ROOT);
	m_jeTree.SetItemData(root5,(DWORD)5);
			switch(EditTable){
				case 1:
					m_jeTree.SelectItem(root1);	
					m_jeTree.EditLabel(root1);
					break;
                case 2:
					m_jeTree.SelectItem(root2);		
					m_jeTree.EditLabel(root2);
					break;
				case 3:
					m_jeTree.SelectItem(root3);
					m_jeTree.EditLabel(root3);
					break;
                case 4:
					m_jeTree.SelectItem(root4);
					m_jeTree.EditLabel(root4);
					break;
				case 5:
					m_jeTree.SelectItem(root5);
					m_jeTree.EditLabel(root5);
					break;
				}

	//һ���ӽڵ�	
	 try{						   	  			   
				CDaoRecordset rs(&m_DataBase);
				COleVariant OleVariant ;
				//���Tool���ӽڵ�
				rs.Open(dbOpenDynaset, L"SELECT * FROM TOOL" );		
				while(!rs.IsEOF()){
					rs.GetFieldValue (0,OleVariant);
					m_jeTree.InsertItem(OleVariant.bstrVal,root1);
					rs.MoveNext();
				}
				rs.Close();     
				//���Curve���ӽڵ�
				rs.Open(dbOpenDynaset, L"SELECT * FROM Curve" );		
				while(!rs.IsEOF()){
					rs.GetFieldValue (0,OleVariant);
					m_jeTree.InsertItem(OleVariant.bstrVal,root2);
					rs.MoveNext();
				}
				rs.Close();     

				//���Origin���ӽڵ�
				rs.Open(dbOpenDynaset, L"SELECT * FROM Origin" );		
				while(!rs.IsEOF()){
					rs.GetFieldValue (0,OleVariant);
					m_jeTree.InsertItem(OleVariant.bstrVal,root3);
					rs.MoveNext();
				}
				rs.Close();  

				//���Power���ӽڵ�
				m_jeTree.InsertItem(_T("������"),root5);
				m_jeTree.InsertItem(_T("�Ϳ̵�"),root5);
				m_jeTree.InsertItem(_T("�߿̵�"),root5);
				m_jeTree.InsertItem(_T("�⾮��"),root5);
				m_jeTree.InsertItem(_T("������"),root5);
				m_jeTree.InsertItem(_T("������"),root5);
				m_jeTree.InsertItem(_T("����"),root5);
				m_jeTree.InsertItem(_T("����"),root5);			
				
	 } catch(CDaoException *e){		
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::OnSelchangedJobeditTree(NMHDR *pNMHDR, LRESULT *pResult)
{	
	
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 HTREEITEM hSel=m_jeTree.GetSelectedItem();//��ǰ�ڵ�
	 HTREEITEM hPar=m_jeTree.GetParentItem(hSel);//���ڵ�
	 DWORD idp;//���ڵ�ID
	 if(hPar){
	 idp = m_jeTree.GetItemData(hPar);//�����ڵ�
	 }else{
	 idp=m_jeTree.GetItemData(hSel);//һ���ڵ�
	 }
	 //CString par;	
     //par.Format(_T("%d"), idp);�˴�����������ʾѡ�еĸ��ڵ��
	 //MessageBox(par,MB_OK);
	 CRect rect;  
	 GetDlgItem(IDC_ZCW_STATIC_RECT)-> GetWindowRect(&rect);  
	 ScreenToClient(&rect);  	
	 if(m_Tool.GetSafeHwnd()!=NULL)
			m_Tool.DestroyWindow();//�����Ϣ��������Ѿ��򿪹�������������������ظ���
	 if(m_Curve.GetSafeHwnd()!=NULL)
			m_Curve.DestroyWindow();//���������Ϣ����Ѿ��򿪹�������������������ظ���
	 if(m_Origin.GetSafeHwnd()!=NULL)
			m_Origin.DestroyWindow();//���ԭʼ�ź�����Ѿ��򿪹�������������������ظ���	
	 if(m_Control.GetSafeHwnd()!=NULL)
			m_Control.DestroyWindow();//������������Ϣ�Ѿ��򿪹�������������������ظ���
	 if(m_Power.GetSafeHwnd()!=NULL)
			m_Power.DestroyWindow();//����ӵ���Ϣ����Ѿ��򿪹�������������������ظ���
	 switch(idp){
	 case 1:
		    if(hPar){			
			ToolInit(m_jeTree.GetItemText(hSel));			
			}else{
			ToolInit();			
			}			
			m_Tool.Create(IDD_JOBEDIT_TOOL, this);  
			m_Tool.MoveWindow(rect);  
			m_Tool.ShowWindow( SW_SHOW ); 				
			m_editTable=1;		
			GetDlgItem(IDC_ZCW_JOBEDIT_ADD)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_DELETE)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_UPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_IMPORT)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_EXPORT)->ShowWindow(FALSE);
		break;
	 case 2:
		    if(hPar){			
			CurveInit(m_jeTree.GetItemText(hSel));				
			}else{
			CurveInit();
			}
		    m_Curve.Create(IDD_JOBEDIT_CURVE, this);  
			m_Curve.MoveWindow(rect);  			
			m_Curve.ShowWindow( SW_SHOW ); 		   		
			m_editTable=2;	
			GetDlgItem(IDC_ZCW_JOBEDIT_ADD)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_DELETE)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_UPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_IMPORT)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_EXPORT)->ShowWindow(FALSE);
		break;
	 case 3:
		    if(hPar){			
			OriginInit(m_jeTree.GetItemText(hSel));				
			}else{
			OriginInit();
			}
		    m_Origin.Create(IDD_JOBEDIT_ORIGIN, this);
			m_Origin.MoveWindow(rect);  			
			m_Origin.ShowWindow( SW_SHOW ); 			
			m_editTable=3;		
			GetDlgItem(IDC_ZCW_JOBEDIT_ADD)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_DELETE)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_UPDATE)->ShowWindow(TRUE);
			GetDlgItem(IDC_ZCW_JOBEDIT_IMPORT)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_EXPORT)->ShowWindow(FALSE);
		break;
	 case 4:
		    ControlInit();
			m_Control.Create(IDD_JOBEDIT_CONTROL, this);
			m_Control.MoveWindow(rect);  			
			m_Control.ShowWindow( SW_SHOW ); 	
			m_editTable=4;			
			GetDlgItem(IDC_ZCW_JOBEDIT_ADD)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_DELETE)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_UPDATE)->ShowWindow(TRUE);	
			GetDlgItem(IDC_ZCW_JOBEDIT_IMPORT)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_EXPORT)->ShowWindow(FALSE);
		break;
	 case 5:		   
			if(hPar){		   
			PowerInit(m_jeTree.GetItemText(hSel));	
			}else{
            PowerInit(_T("������"));           				
			}			
			m_Power.Create(IDD_JOBEDIT_POWER, this);
			m_Power.MoveWindow(rect);  			
			m_Power.ShowWindow( SW_SHOW ); 	
			m_editTable=5;	
			
			GetDlgItem(IDC_ZCW_JOBEDIT_ADD)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_DELETE)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_UPDATE)->ShowWindow(TRUE);		
			GetDlgItem(IDC_ZCW_JOBEDIT_IMPORT)->ShowWindow(FALSE);
			GetDlgItem(IDC_ZCW_JOBEDIT_EXPORT)->ShowWindow(FALSE);
		break;
	 }
	*pResult = 0;
}


void CJobEditDlg::ToolInit(CString Label){
	//��ʼ��������Ϣ����
	 COleVariant OleVariant ;
		try{					
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM TOOL where LABEL='")+Label+_T("'"));
					rs.MoveFirst () ;				
					rs.GetFieldValue (0,OleVariant);
					m_Tool.m_Label=OleVariant.bstrVal;

					rs.GetFieldValue (1,OleVariant);
					m_Tool.m_Type=OleVariant.bstrVal;

					rs.GetFieldValue (2,OleVariant);
					m_Tool.m_SN=OleVariant.bstrVal;	

					rs.GetFieldValue (3,OleVariant);
					m_Tool.m_Length=OleVariant.fltVal;	

					rs.GetFieldValue (4,OleVariant);
					m_Tool.m_Weight=OleVariant.fltVal;

					rs.GetFieldValue (5,OleVariant);
					m_Tool.m_OuteRdiam=OleVariant.fltVal;	

					rs.GetFieldValue (6,OleVariant);
					m_Tool.m_Speed=OleVariant.bstrVal;							
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::ToolInit(){
//��ʼ��������Ϣ����
	 COleVariant OleVariant ;
		try{					
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM TOOL"));				
					rs.MoveFirst () ;				
					rs.GetFieldValue (0,OleVariant);
					m_Tool.m_Label=OleVariant.bstrVal;

					rs.GetFieldValue (1,OleVariant);
					m_Tool.m_Type=OleVariant.bstrVal;

					rs.GetFieldValue (2,OleVariant);
					m_Tool.m_SN=OleVariant.bstrVal;	

					rs.GetFieldValue (3,OleVariant);
					m_Tool.m_Length=OleVariant.fltVal;	

					rs.GetFieldValue (4,OleVariant);
					m_Tool.m_Weight=OleVariant.fltVal;

					rs.GetFieldValue (5,OleVariant);
					m_Tool.m_OuteRdiam=OleVariant.fltVal;	

					rs.GetFieldValue (6,OleVariant);
					m_Tool.m_Speed=OleVariant.bstrVal;							
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::CurveInit(CString Label){
	//��ʼ��������Ϣ����	
	 COleVariant OleVariant ;
		try{				
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Curve where LABEL='")+Label+_T("'"));
					rs.MoveFirst () ;				
					rs.GetFieldValue (0,OleVariant);
					m_Curve.m_Label=OleVariant.bstrVal;

					//��λ,�ַ���
					rs.GetFieldValue (1,OleVariant);
					m_Curve.m_unit=OleVariant.bstrVal;						
					//�˲�����,�ַ���
					rs.GetFieldValue (2,OleVariant);
					m_Curve.m_filter=OleVariant.bstrVal;
					//��ʶ
					rs.GetFieldValue (3,OleVariant);
					m_Curve.m_title=OleVariant.bstrVal;
					//��Сȡֵ
					rs.GetFieldValue (4,OleVariant);
					m_Curve.m_minLimit=OleVariant.dblVal;
					//���ȡֵ
					rs.GetFieldValue (5,OleVariant);
					m_Curve.m_maxLimit=OleVariant.dblVal;
					//R��ɫ
					BYTE R,G,B;
					rs.GetFieldValue (6,OleVariant);
					R=OleVariant.iVal;	
					//G��ɫ
					rs.GetFieldValue (7,OleVariant);
					G=OleVariant.iVal;	
					//B��ɫ
					rs.GetFieldValue (8,OleVariant);
					B=OleVariant.iVal;	
					m_Curve.curveSelectColor=RGB(R,G,B);
					//���	
					rs.GetFieldValue (9,OleVariant);
					m_Curve.m_track=OleVariant.iVal;
					//����	
					rs.GetFieldValue (10,OleVariant);
					m_Curve.m_line=OleVariant.iVal;	
					//�߿�
					rs.GetFieldValue (11,OleVariant);
					m_Curve.m_linewid=OleVariant.iVal-1;	

				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::OriginInit(CString Label){
	//��ʼ��ԭʼ�źŴ���	
	 COleVariant OleVariant ;
		try{						
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Origin where LABEL='")+Label+_T("'"));
					rs.MoveFirst () ;				
					rs.GetFieldValue (0,OleVariant);
					m_Origin.m_Label=OleVariant.bstrVal;

					rs.GetFieldValue (1,OleVariant);
					m_Origin.m_unit=OleVariant.bstrVal;						

					rs.GetFieldValue (2,OleVariant);
					m_Origin.m_filter=OleVariant.bstrVal;		

				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::ToolDel(CString Label){
	//ɾ��ѡ�е�������Ϣ	
	 COleVariant OleVariant ;
		try{					
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM TOOL where LABEL='")+Label+_T("'"));
				rs.Delete();					
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::CurveDel(CString Label){
	//ɾ��ѡ�е�������Ϣ	
	 COleVariant OleVariant ;
		try{					
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Curve where LABEL='")+Label+_T("'"));
				rs.Delete();					
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::OriginDel(CString Label){
	//ɾ��ѡ�е�ԭʼ�ź�	
	 COleVariant OleVariant ;
		try{					
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Origin where LABEL='")+Label+_T("'"));
				rs.Delete();					
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}
/*
void CJobEditDlg::ToolInit(){
	//��ʼ��������Ϣ����	
	                CString LabelName=m_jobName.Left(m_jobName.Find(_T(".")));//��ȡ�ļ���
					LabelName=LabelName.Right(LabelName.Find(_T("\\")));
					LabelName=LabelName.Right(LabelName.GetLength()-1);
					m_Tool.m_Label=LabelName;					
					m_Tool.m_SN=_T("001");					
					m_Tool.m_Speed=_T("1000");						
					m_Tool.m_Type=_T("001");						
					m_Tool.m_Length=0;						
					m_Tool.m_Weight=0;						
					m_Tool.m_OuteRdiam=0;			
}
*/
void CJobEditDlg::CurveInit(){
	//��ʼ��������Ϣ����	
					m_Curve.m_Label=_T("");					
					//m_Curve.m_unit=0;
					//m_Curve.m_filter=0;
}

void CJobEditDlg::OriginInit(){
	//��ʼ��ԭʼ�źŴ���	
					m_Origin.m_Label=_T("");					
					//m_Origin.m_unit=0;
					//m_Origin.m_filter=0;
}

void CJobEditDlg::ControlInit(){
	//��ʼ�������źŴ���				
					CString m_combo1ary[]={_T("100"),_T("125"),_T("25"),_T("31.25")};
					CString m_combo2ary[]={_T("600"),_T("450"),_T("300"),_T("100")};
					CString m_combo3ary[]={_T("3000")};
					CString m_combo4ary[]={_T("1"),_T("2"),_T("4"),_T("8")};
					CString m_combo5ary[]={_T("10"),_T("20"),_T("30"),_T("40"),_T("50"),_T("55")};
					COleVariant OleVariant ;
					try{						
					CDaoRecordset rs(&m_DataBase);
					rs.Open(dbOpenDynaset,_T("SELECT * FROM Control"));
						rs.MoveFirst();					
						rs.GetFieldValue (2,OleVariant);
						for(int i=0;i<4;i++){
						if(m_combo1ary[i]==OleVariant.bstrVal)	m_Control.m_combo1_i=i;						
						}
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OleVariant);
						for(int i=0;i<4;i++){
						if(m_combo2ary[i]==OleVariant.bstrVal)	m_Control.m_combo2_i=i;
						}
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OleVariant);
						for(int i=0;i<1;i++){
						if(m_combo3ary[i]==OleVariant.bstrVal)	m_Control.m_combo3_i=i;
						}
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OleVariant);
						for(int i=0;i<4;i++){
						if(m_combo4ary[i]==OleVariant.bstrVal)	m_Control.m_combo4_i=i;
						}
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OleVariant);
						for(int i=0;i<6;i++){
						if(m_combo5ary[i]==OleVariant.bstrVal) m_Control.m_combo5_i=i;
						}
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit1=OleVariant.bstrVal;
						rs.MoveNext();

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit2=OleVariant.bstrVal;
						rs.MoveNext();

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit3=OleVariant.bstrVal;
						rs.MoveNext();

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit4=OleVariant.bstrVal;
						rs.MoveNext();

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit5=OleVariant.bstrVal;
						rs.MoveNext();

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit6=OleVariant.bstrVal;
						rs.MoveNext();

						rs.GetFieldValue (2,OleVariant);
						m_Control.m_edit7=OleVariant.bstrVal;
						rs.MoveNext();
					rs.Close();				
					}
					catch(CDaoException *e){
					MessageBox(e->m_pErrorInfo->m_strDescription);
					e->Delete();
					}			
}

void CJobEditDlg::PowerInit(CString PowerMode){

	//��ʼ�ӵ���Ϣ����				
					CString m_combo1ary[]={_T("���ӵ�"),_T("����1"),_T("����2"),_T("ֱ��1[��]"),_T("ֱ��1[��]"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo2ary[]={_T("���ӵ�"),_T("ֱ��1[��]"),_T("ֱ��1[��]"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo3ary[]={_T("���ӵ�"),_T("����2"),_T("ֱ��2[��]"),_T("ֱ��2[��]"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo4ary[]={_T("���ӵ�"),_T("����1")};
					CString m_combo5ary[]={_T("���ӵ�"),_T("ֱ��2[��]"),_T("ֱ��2[��]"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo6ary[]={_T("���ӵ�"),_T("����1")};
					CString m_combo7ary[]={_T("���ӵ�"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo8ary[]={_T("���ӵ�"),_T("����2"),_T("ֱ��1[��]"),_T("ֱ��1[��]"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo9ary[]={_T("���ӵ�"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};
					CString m_combo10ary[]={_T("NO"),_T("AMP LOGIC"),_T("CAL POWER"),_T("POLE POWER")};
					CString m_combo11ary[]={_T("���ӵ�"),_T("����2"),_T("ֱ��3[��]"),_T("ֱ��3[��]")};

				

					CString m_modeary[]={_T("������"),_T("�Ϳ̵�"),_T("�߿̵�"),_T("�⾮��"),_T("������"),_T("������"),_T("����"),_T("����")};
									
					CString sMode;
					for(int i=0;i<8;i++){
					if(m_modeary[i]==PowerMode)
					sMode.Format(_T("%d"),i);
					}

					COleVariant OV1,OV2,OV3;
					try{						
					    CDaoRecordset rs(&m_DataBase);						
					    rs.Open(dbOpenDynaset,_T("SELECT * FROM Power where Mode='")+sMode+_T("'"));
						rs.MoveFirst();					
						rs.GetFieldValue (2,OV1);m_Power.m_combo1_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit1.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit12.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	
						
						rs.GetFieldValue (2,OV1);m_Power.m_combo2_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit2.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit13.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo3_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit3.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit14.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo4_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit4.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit15.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo5_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit5.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit16.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo6_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit6.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit17.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo7_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit7.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit18.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo8_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit8.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit19.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo9_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit9.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit20.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo10_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit10.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit21.Format(_T("%d"),OV3.iVal);
						rs.MoveNext() ;	

						rs.GetFieldValue (2,OV1);m_Power.m_combo11_i=OV1.iVal;
						rs.GetFieldValue (3,OV2);m_Power.m_edit11.Format(_T("%d"),OV2.iVal);
						rs.GetFieldValue (4,OV3);m_Power.m_edit22.Format(_T("%d"),OV3.iVal);
						rs.MoveNext();
					rs.Close();				
					}
					catch(CDaoException *e){
					MessageBox(e->m_pErrorInfo->m_strDescription);
					e->Delete();
					}			
}

void CJobEditDlg::ToolAdd()
{	
	 try{				
			   //�½����ݿ��¼			  			   
				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM TOOL"));
				if(rs.IsBOF()){
			    rs.AddNew();
				int Where=m_jobName.ReverseFind('\\');
				CString LabelName=m_jobName.Right(m_jobName.GetLength()-1-Where);
				LabelName=LabelName.Left(LabelName.ReverseFind('.'));
				rs.SetFieldValue(0,COleVariant(LabelName));
				rs.SetFieldValue(1,_T("001"));	
				rs.SetFieldValue(2,_T("001"));
				rs.SetFieldValue(3,_T("0"));
				rs.SetFieldValue(4,_T("0"));	
				rs.SetFieldValue(5,_T("0"));
				rs.SetFieldValue(6,_T("1000"));
				rs.Update();
				//MessageBox(_T("��ӳɹ�"));
				}else{
				MessageBox(_T("������Ϣ")+m_Tool.m_Label+_T("�Ѿ�����"),MB_OK);
				}
				rs.Close();		

	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::CurveAdd()
{	
	 try{				
			   //�½����ݿ��¼
		        CDaoRecordset rsJobList(&m_DBJobList);						
				rsJobList.Open(dbOpenDynaset,_T("SELECT * FROM CurveList where LABEL='")+m_Curve.m_Label+_T("'"));

				if(rsJobList.IsBOF()){
				rsJobList.AddNew();
				rsJobList.SetFieldValue(0,COleVariant(m_Curve.m_Label));
				rsJobList.Update();

				CDaoRecordset rs(&m_DataBase);	
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Curve"));
			    rs.AddNew();
				rs.SetFieldValue(0,COleVariant(m_Curve.m_Label));
				//��λ				
				int iUnit=m_Curve.m_unitbox.GetCurSel();
				CString strUnit;
				m_Curve.m_unitbox.GetLBText(iUnit,strUnit);
				rs.SetFieldValue(1,COleVariant(strUnit));

				//�˲�����
				int iFilter=m_Curve.m_filterbox.GetCurSel();
				CString strFilter;
				m_Curve.m_filterbox.GetLBText(iFilter,strFilter);
				rs.SetFieldValue(2,COleVariant(strFilter));
				
				rs.SetFieldValue(3,COleVariant(m_Curve.m_title));//��ʶ
				rs.SetFieldValue(4,COleVariant(double(m_Curve.m_minLimit)));//��Сȡֵ
				rs.SetFieldValue(5,COleVariant(double(m_Curve.m_maxLimit)));//���ȡֵ
				rs.SetFieldValue(6,COleVariant(BYTE(GetRValue(m_Curve.curveSelectColor))));//R��ɫ
				rs.SetFieldValue(7,COleVariant(BYTE(GetGValue(m_Curve.curveSelectColor))));//G��ɫ
				rs.SetFieldValue(8,COleVariant(BYTE(GetBValue(m_Curve.curveSelectColor))));//B��ɫ
				rs.SetFieldValue(9,COleVariant(long(m_Curve.m_trackbox.GetCurSel())));//���	
				rs.SetFieldValue(10,COleVariant(long(m_Curve.m_linetype.GetCurSel())));//����	
				rs.SetFieldValue(11,COleVariant(long(m_Curve.m_linewidth.GetCurSel()+1)));//����
				rs.Update();
				rs.Close();
				MessageBox(_T("��ӳɹ�"));
				}else{
				MessageBox(_T("������Ϣ")+m_Curve.m_Label+_T("�Ѿ�����"),MB_OK);
				}
				rsJobList.Close();			
	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::OriginAdd()
{	
	 try{				
			   //�½����ݿ��¼			  			   
				CDaoRecordset rsJobList(&m_DBJobList);						
				rsJobList.Open(dbOpenDynaset,_T("SELECT * FROM OriginList where LABEL='")+m_Origin.m_Label+_T("'"));

				if(rsJobList.IsBOF()){
				rsJobList.AddNew();
				rsJobList.SetFieldValue(0,COleVariant(m_Origin.m_Label));
				rsJobList.Update();

				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Origin"));
			    rs.AddNew();
				rs.SetFieldValue(0,COleVariant(m_Origin.m_Label));
				//��λ				
				int iUnit=m_Origin.m_unitbox.GetCurSel();
				CString strUnit;
				m_Origin.m_unitbox.GetLBText(iUnit,strUnit);
				rs.SetFieldValue(1,COleVariant(strUnit));

				//�˲�����
				int iFilter=m_Origin.m_filterbox.GetCurSel();
				CString strFilter;
				m_Origin.m_filterbox.GetLBText(iFilter,strFilter);
				rs.SetFieldValue(2,COleVariant(strFilter));				
				rs.Update();
				rs.Close();
				MessageBox(_T("��ӳɹ�"));
				}else{
				MessageBox(_T("ԭʼ�ź�")+m_Origin.m_Label+_T("�Ѿ�����"),MB_OK);
				}
				rsJobList.Close();	

	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::ControlAdd()
{	
	 try{				
			   int Where=m_jobName.ReverseFind('\\');
				CString Label=m_jobName.Right(m_jobName.GetLength()-1-Where);
				Label=Label.Left(Label.ReverseFind('.'));//���������Labelֵ
				//�½����ݿ��¼			    
				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Control"));				
				if(rs.IsBOF()){
                CString strDataValue;                
			    rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_DEPTHSTEP"));
				rs.SetFieldValue(1,_T("mm"));				
				rs.SetFieldValue(2,_T("100"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_TIMESTEP"));
				rs.SetFieldValue(1,_T("ms"));					
				rs.SetFieldValue(2,_T("600"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_DISPSTEP"));
				rs.SetFieldValue(1,_T("ms"));					
				rs.SetFieldValue(2,_T("3000"));
				rs.Update();
				
				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Sonic_AdStep"));
				rs.SetFieldValue(1,_T("uS"));						
				rs.SetFieldValue(2,_T("2"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Pole_FreqNum"));
				rs.SetFieldValue(1,_T("HZ"));					
				rs.SetFieldValue(2,_T("30"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Speed_Max"));
				rs.SetFieldValue(1,_T("m/h"));					
				rs.SetFieldValue(2,_T("1200"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Load_Max"));
				rs.SetFieldValue(1,_T("KG"));				
				rs.SetFieldValue(2,_T("5000"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Load_Diff"));
				rs.SetFieldValue(1,_T("KG"));						
				rs.SetFieldValue(2,_T("500"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Sonic_FreqNum"));
				rs.SetFieldValue(1,_T("10ms"));						
				rs.SetFieldValue(2,_T("5"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_Sonic_LogicalWidth"));
				rs.SetFieldValue(1,_T("200uS"));					
				rs.SetFieldValue(2,_T("2"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_FORMATLABEL"));
				rs.SetFieldValue(1,_T(" "));				
				rs.SetFieldValue(2,_T("BORE.xml"));
				rs.Update();

				rs.AddNew();
				rs.SetFieldValue(0,Label+_T("_HEADLABEL"));
				rs.SetFieldValue(1,_T(" "));			
				rs.SetFieldValue(2,_T("BOREHEAD.xml"));
				rs.Update();
				}else{
				MessageBox(_T("�����ź��Ѵ���"),MB_OK);
				}
				rs.Close();	

	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::PowerAdd()
{	
	 try{				
			   //�½����ݿ��¼
		        int Where=m_jobName.ReverseFind('\\');
				CString Label=m_jobName.Right(m_jobName.GetLength()-1-Where);
				Label=Label.Left(Label.ReverseFind('.'));//���������Labelֵ

				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Power"));				
				if(rs.IsBOF()){
                for(int i=0;i<8;i++){
					for(int j=0;j<11;j++){
						 rs.AddNew();	
						 CString sLabel;
						 sLabel.Format(_T("%d"),256*i+j+1);
						 CString sMode;
						 sMode.Format(_T("%d"),i);
						 rs.SetFieldValue(0,COleVariant(Label+_T("_")+sLabel));
						 rs.SetFieldValue(1,COleVariant(long(j+1)));	
						 rs.SetFieldValue(2,_T("0"));
						 rs.SetFieldValue(3,_T("0"));
						 rs.SetFieldValue(4,_T("0"));
						 rs.SetFieldValue(5,COleVariant(sMode));	
						 rs.Update();
					}
				}	   			
				}else{
				MessageBox(_T("�ӵ���Ϣ�Ѵ���"),MB_OK);
				}
				rs.Close();	

	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}


void CJobEditDlg::ControlUpdate()
{	
	 try{				
			   //�½����ݿ��¼			    
				CDaoRecordset rs(&m_DataBase);				
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Control"));		
				
				if(!rs.IsBOF()){
                CString strDataValue;  

				rs.MoveFirst();
				rs.Edit();
				rs.SetFieldValue(0,_T("DEPTHSTEP"));
				rs.SetFieldValue(1,_T("mm"));
				m_Control.m_combo1.GetLBText(m_Control.m_combo1.GetCurSel(),strDataValue);				
				rs.SetFieldValue(2,COleVariant(strDataValue));
				rs.Update();
				rs.MoveNext();

                rs.Edit();
				rs.SetFieldValue(0,_T("TIMESTEP"));
				rs.SetFieldValue(1,_T("ms"));				
				m_Control.m_combo2.GetLBText(m_Control.m_combo2.GetCurSel(),strDataValue);			
				rs.SetFieldValue(2,COleVariant(strDataValue));
				rs.Update();
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(0,_T("DISPSTEP"));
				rs.SetFieldValue(1,_T("ms"));						
				m_Control.m_combo3.GetLBText(m_Control.m_combo3.GetCurSel(),strDataValue);				
				rs.SetFieldValue(2,COleVariant(strDataValue));
				rs.Update();				
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(0,_T("Sonic_AdStep"));
				rs.SetFieldValue(1,_T("uS"));					
				m_Control.m_combo4.GetLBText(m_Control.m_combo4.GetCurSel(),strDataValue);
				rs.SetFieldValue(2,COleVariant(strDataValue));
				rs.Update();
			    rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(0,_T("Pole_FreqNum"));
				rs.SetFieldValue(1,_T("HZ"));				
				m_Control.m_combo5.GetLBText(m_Control.m_combo5.GetCurSel(),strDataValue);
				rs.SetFieldValue(2,COleVariant(strDataValue));
				rs.Update();
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(0,_T("Speed_Max"));
				rs.SetFieldValue(1,_T("m/h"));	
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit1));
				rs.Update();
				rs.MoveNext();	

				rs.Edit();
				rs.SetFieldValue(0,_T("Load_Max"));
				rs.SetFieldValue(1,_T("KG"));						
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit2));
				rs.Update();
				rs.MoveNext();
 
				rs.Edit();
				rs.SetFieldValue(0,_T("Load_Diff"));
				rs.SetFieldValue(1,_T("KG"));				
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit3));
				rs.Update();
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(0,_T("Sonic_FreqNum"));
				rs.SetFieldValue(1,_T("10ms"));				
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit4));
				rs.Update();
				rs.MoveNext();	
 
				rs.Edit();
				rs.SetFieldValue(0,_T("Sonic_LogicalWidth"));
				rs.SetFieldValue(1,_T("200uS"));				
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit5));
				rs.Update();
			    rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(0,_T("FORMATLABEL"));
				rs.SetFieldValue(1,_T(" "));				
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit6));
				rs.Update();
				rs.MoveNext();		

				rs.Edit();
				rs.SetFieldValue(0,_T("HEADLABEL"));
				rs.SetFieldValue(1,_T(" "));				
				rs.SetFieldValue(2,COleVariant(m_Control.m_edit7));
				rs.Update();
				rs.Close();	
				//CString sEditTable;
				//sEditTable.Format(_T("%d"),m_editTable);
				MessageBox(_T("�޸ĳɹ�"));
				}else{
				MessageBox(_T("δ�ҵ�������Ϣ"),MB_OK);
				}				

	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::PowerUpdate(CString PowerMode)
{	
	 try{				
			   //�½����ݿ��¼			    
				CDaoRecordset rs(&m_DataBase);				
				CString m_modeary[]={_T("������"),_T("�Ϳ̵�"),_T("�߿̵�"),_T("�⾮��"),_T("������"),_T("������"),_T("����"),_T("����")};
									
				CString sMode;
				for(int i=0;i<8;i++){
					if(m_modeary[i]==PowerMode)
					sMode.Format(_T("%d"),i);
				}
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Power where Mode='")+sMode+_T("'"));
				
				if(!rs.IsBOF()){
                CString strDataValue;  

				rs.MoveFirst();
				rs.Edit();			
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo1.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit1)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit12)));
				rs.Update();
				rs.MoveNext();

                rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo2.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit2)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit13)));
				rs.Update();
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo3.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit3)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit14)));
				rs.Update();				
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo4.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit4)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit15)));
				rs.Update();
			    rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo5.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit5)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit16)));
				rs.Update();
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo6.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit6)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit17)));
				rs.Update();
				rs.MoveNext();	

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo7.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit7)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit18)));
				rs.Update();
				rs.MoveNext();
 
				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo8.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit8)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit19)));
				rs.Update();
				rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo9.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit9)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit20)));
				rs.Update();
				rs.MoveNext();	
 
				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo10.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit10)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit21)));
				rs.Update();
			    rs.MoveNext();

				rs.Edit();
				rs.SetFieldValue(2,COleVariant(long(m_Power.m_combo11.GetCurSel())));	
				rs.SetFieldValue(3,COleVariant(_ttol(m_Power.m_edit11)));
				rs.SetFieldValue(4,COleVariant(_ttol(m_Power.m_edit22)));
				rs.Update();
				rs.MoveNext();	
				rs.Close();	
				MessageBox(_T("�޸ĳɹ�"));
				}else{
				MessageBox(_T("δ�ҵ��ӵ���Ϣ"),MB_OK);
				}				

	 } catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
     }
}

void CJobEditDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(m_editTable){
	case 1:		
		if(m_Tool.m_Label.Trim().IsEmpty()){
		MessageBox(_T("���Ʋ���Ϊ��"),MB_OK);
		}else{
		ToolAdd();				
		}
		break;
	case 2:
		if(m_Curve.m_Label.Trim().IsEmpty()){
		MessageBox(_T("���Ʋ���Ϊ��"),MB_OK);
		}else if(m_Curve.m_title.Trim().IsEmpty()){
        MessageBox(_T("��ʶ����Ϊ��"),MB_OK);
		}else{
		CurveAdd();			
		}		
		break;
	case 3:
		if(m_Origin.m_Label.Trim().IsEmpty()){
		MessageBox(_T("���Ʋ���Ϊ��"),MB_OK);
		}else{
		OriginAdd();			
		}		
		break;
	}
	DisplayTree(m_editTable);	
}

void CJobEditDlg::JobInit(){
	try{
			m_DataBase.Create(m_jobName);//����½���ҵ�򴴽����ݿ�
				CDaoTableDef td(&m_DataBase);        //��������						
				
				//����TOOL��
				td.Create(_T("TOOL"));
				td.CreateField(_T("LABEL"),dbText,50,0L);			
				td.CreateField(_T("TYPE"),dbText,50,0L);
				td.CreateField(_T("SN"),dbText,50,0L);					
				td.CreateField(_T("LENGTH"),dbSingle,0L);
				td.CreateField(_T("Weight"),dbSingle,0L);
			    td.CreateField(_T("OUTERDIAMATER"),dbSingle,0L);			
				td.CreateField(_T("SPEED"),dbText,50,0L);
			    td.Append();
				td.Close();
				ToolAdd();//��ʼ��tool����
				//����Curve��
				td.Create(_T("CURVE"));
				td.CreateField(_T("LABEL"),dbText,50,0L);
				td.CreateField(_T("UNIT"),dbText,50,0L);
				td.CreateField(_T("FILTER"),dbText,50,0L);	
				td.CreateField(_T("TITLE"),dbText,50,0L);
				td.CreateField(_T("MIN"),dbDouble,0L);
				td.CreateField(_T("MAX"),dbDouble,0L);
				td.CreateField(_T("COLOR_R"),dbByte,0xFFL);	
				td.CreateField(_T("COLOR_G"),dbByte,0L);
				td.CreateField(_T("COLOR_B"),dbByte,0L);
				td.CreateField(_T("TRACK"),dbInteger,0L);	
				td.CreateField(_T("LINETYPE"),dbInteger,0L);
				td.CreateField(_T("LINEWIDTH"),dbInteger,0L);
			    td.Append();
				td.Close();

				//����Origin��
				td.Create(_T("ORIGIN"));
				td.CreateField(_T("LABEL"),dbText,50,0L);
				td.CreateField(_T("UNIT"),dbText,50,0L);		
				td.CreateField(_T("FILTER"),dbText,50,0L);		
			    td.Append();
				td.Close();

				//����Control��
				td.Create(_T("CONTROL"));
				td.CreateField(_T("LABEL"),dbText,50,0L);
				td.CreateField(_T("UNITS"),dbText,50,0L);		
				td.CreateField(_T("DATAVALUE"),dbText,50,0L);		
			    td.Append();
				td.Close();

				ControlAdd();//Control�����ݳ�ʼ��

				//����Power��
				td.Create(_T("POWER"));
				td.CreateField(_T("LABEL"),dbText,50,0L);
				td.CreateField(_T("CABLE"),dbInteger,0L);	
				td.CreateField(_T("TYPE"),dbInteger,0L);	
				td.CreateField(_T("VOLTAGE"),dbInteger,0L);	
				td.CreateField(_T("ElectricCurrent"),dbInteger,0L);	
				td.CreateField(_T("MODE"),dbText,50,0L);						
			    td.Append();
				td.Close();

				PowerAdd();//Power�����ݳ�ʼ��

		}catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
        }
}

void CJobEditDlg::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hSel=m_jeTree.GetSelectedItem();//��ǰ�ڵ�
	HTREEITEM hPar=m_jeTree.GetParentItem(hSel);//���ڵ�		
	switch(m_editTable){
	case 1:				
			if(hPar){//��һ���ڵ�
				if(MessageBox(_T("ȷ��ɾ��������Ϣ")+m_jeTree.GetItemText(hSel)+_T("��"),_T("����"),MB_OKCANCEL)==IDOK){
					ToolDel(m_jeTree.GetItemText(hSel));					
				}			
			}			
		break;
	case 2:
		   if(hPar){//��һ���ڵ�
				if(MessageBox(_T("ȷ��ɾ��������Ϣ")+m_jeTree.GetItemText(hSel)+_T("��"),_T("����"),MB_OKCANCEL)==IDOK){
					CurveDel(m_jeTree.GetItemText(hSel));					
				}			
			}	
		break;
	case 3:
		if(hPar){//��һ���ڵ�
				if(MessageBox(_T("ȷ��ɾ��ԭʼ�ź�")+m_jeTree.GetItemText(hSel)+_T("��"),_T("����"),MB_OKCANCEL)==IDOK){
					OriginDel(m_jeTree.GetItemText(hSel));					
				}			
			}	
		break;
	}
	DisplayTree(m_editTable);	
}

void CJobEditDlg::ToolUpdate(CString Label)
{	
	 COleVariant OleVariant ;
		try{						
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM TOOL where LABEL='")+Label+_T("'"));
				rs.Edit();
				if(!rs.IsBOF()){			   
				rs.SetFieldValue(0,COleVariant(m_Tool.m_Label));
				rs.SetFieldValue(1,COleVariant(m_Tool.m_Type));	
				rs.SetFieldValue(2,COleVariant(m_Tool.m_SN));
				rs.SetFieldValue(3,COleVariant(m_Tool.m_Length));
				rs.SetFieldValue(4,COleVariant(m_Tool.m_Weight));	
				rs.SetFieldValue(5,COleVariant(m_Tool.m_OuteRdiam));
				rs.SetFieldValue(6,COleVariant(m_Tool.m_Speed));
				rs.Update();
				MessageBox(_T("�޸ĳɹ�,�����������Ϣ�鿴"));
				}else{
				MessageBox(_T("������Ϣ")+m_Tool.m_Label+_T("������"),MB_OK);
				}				
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::CurveUpdate(CString Label)
{	
	 COleVariant OleVariant ;
		try{						
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM CURVE where LABEL='")+Label+_T("'"));
				rs.Edit();
				if(!rs.IsBOF()){			   
				rs.SetFieldValue(0,COleVariant(m_Curve.m_Label));
				//��λ				
				int iUnit=m_Curve.m_unitbox.GetCurSel();
				CString strUnit;
				m_Curve.m_unitbox.GetLBText(iUnit,strUnit);
				rs.SetFieldValue(1,COleVariant(strUnit));

				//�˲�����
				int iFilter=m_Curve.m_filterbox.GetCurSel();
				CString strFilter;
				m_Curve.m_filterbox.GetLBText(iFilter,strFilter);
				rs.SetFieldValue(2,COleVariant(strFilter));

				rs.SetFieldValue(3,COleVariant(m_Curve.m_title));//��ʶ
				rs.SetFieldValue(4,COleVariant(double(m_Curve.m_minLimit)));//��Сȡֵ
				rs.SetFieldValue(5,COleVariant(double(m_Curve.m_maxLimit)));//���ȡֵ
				rs.SetFieldValue(6,COleVariant(BYTE(GetRValue(m_Curve.curveSelectColor))));//R��ɫ
				rs.SetFieldValue(7,COleVariant(BYTE(GetGValue(m_Curve.curveSelectColor))));//G��ɫ
				rs.SetFieldValue(8,COleVariant(BYTE(GetBValue(m_Curve.curveSelectColor))));//B��ɫ
				rs.SetFieldValue(9,COleVariant(long(m_Curve.m_trackbox.GetCurSel())));//���	
				rs.SetFieldValue(10,COleVariant(long(m_Curve.m_linetype.GetCurSel())));//����	
				rs.SetFieldValue(11,COleVariant(long(m_Curve.m_linewidth.GetCurSel()+1)));//����
				
				rs.Update();
				MessageBox(_T("�޸ĳɹ�,�����������Ϣ�鿴"));
				}else{
				MessageBox(_T("������Ϣ")+m_Curve.m_Label+_T("������"),MB_OK);
				}				
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::OriginUpdate(CString Label)
{	
	 COleVariant OleVariant ;
		try{					
				CDaoRecordset rs(&m_DataBase);
				rs.Open(dbOpenDynaset,_T("SELECT * FROM Origin where LABEL='")+Label+_T("'"));
				rs.Edit();
				if(!rs.IsBOF()){			   
				rs.SetFieldValue(0,COleVariant(m_Origin.m_Label));
				//��λ				
				int iUnit=m_Origin.m_unitbox.GetCurSel();
				CString strUnit;
				m_Origin.m_unitbox.GetLBText(iUnit,strUnit);
				rs.SetFieldValue(1,COleVariant(strUnit));

				//�˲�����
				int iFilter=m_Origin.m_filterbox.GetCurSel();
				CString strFilter;
				m_Origin.m_filterbox.GetLBText(iFilter,strFilter);
				rs.SetFieldValue(2,COleVariant(strFilter));		
				rs.Update();
				MessageBox(_T("�޸ĳɹ�,�����ԭʼ�źŲ鿴"));
				}else{
				MessageBox(_T("ԭʼ�ź�")+m_Origin.m_Label+_T("������"),MB_OK);
				}				
				rs.Close();				
            }
            catch(CDaoException *e){
			MessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
            }
}

void CJobEditDlg::OnBnClickedUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hSel=m_jeTree.GetSelectedItem();//��ǰ�ڵ�
	HTREEITEM hPar=m_jeTree.GetParentItem(hSel);//���ڵ�		
	switch(m_editTable){
	case 1:				
			if(hPar){//��һ���ڵ�				
				ToolUpdate(m_jeTree.GetItemText(hSel));						
			}			
		break;
	case 2:
		if(hPar){//��һ���ڵ�				
				CurveUpdate(m_jeTree.GetItemText(hSel));							
			}	
		break;
	case 3:
		if(hPar){//��һ���ڵ�				
				OriginUpdate(m_jeTree.GetItemText(hSel));							
			}	
		break;
	case 4:
		ControlUpdate();		
		break;
	case 5:
		if(hPar){//��һ���ڵ�				
			PowerUpdate(m_jeTree.GetItemText(hSel));						
		}else{	
			PowerUpdate(_T("������"));
		}
		break;
	}
	DisplayTree(m_editTable);	
}


void CJobEditDlg::OnBnClickedZcwJobeditImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,_T(""),_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("tools files(*.tools)|*.tools|tool files(*.mdb)|*.mdb|All files(*.*)|*.*|"));//���챣���ļ��Ի���
	dlg.m_ofn.lpstrInitialDir=theApp.ToolPath;
    if(dlg.DoModal()==IDOK)//��ʾ���ļ��Ի���
	{		
		CString strToolPath=dlg.GetPathName();//��ȡ����·������
		CDaoDatabase t_DataBase;
		t_DataBase.Open(strToolPath);

		CDaoRecordset rsJob(&m_DataBase);
		CDaoRecordset rsTool(&t_DataBase);
		COleVariant OleVariant ;

		//����������Ϣ
		rsJob.Open(dbOpenDynaset,_T("SELECT * FROM Tool"));
		rsTool.Open(dbOpenDynaset,_T("SELECT * FROM Tool"));
		rsTool.MoveFirst();
		while(!rsTool.IsEOF()){
				rsTool.GetFieldValue (0,OleVariant);
				CString Label=OleVariant.bstrVal;
				rsTool.GetFieldValue (1,OleVariant);
				CString Type=OleVariant.bstrVal;
				rsTool.GetFieldValue (2,OleVariant);
				CString SN=OleVariant.bstrVal;	
				rsTool.GetFieldValue (3,OleVariant);
				float Length=OleVariant.fltVal;						
				rsTool.GetFieldValue (4,OleVariant);
				float Weight=OleVariant.fltVal;
				rsTool.GetFieldValue (5,OleVariant);
				float OuteRdiam=OleVariant.fltVal;	
				rsTool.GetFieldValue (6,OleVariant);
				CString Speed=OleVariant.bstrVal;	

				rsJob.AddNew();
				rsJob.SetFieldValue(0,COleVariant(Label));
				rsJob.SetFieldValue(1,COleVariant(Type));	
				rsJob.SetFieldValue(2,COleVariant(SN));
				rsJob.SetFieldValue(3,COleVariant(Length));
				rsJob.SetFieldValue(4,COleVariant(Weight));	
				rsJob.SetFieldValue(5,COleVariant(OuteRdiam));
				rsJob.SetFieldValue(6,COleVariant(Speed));
				rsJob.Update();
				rsTool.MoveNext();
		}
		rsTool.Close();
		rsJob.Close();

		//����������Ϣ
		rsJob.Open(dbOpenDynaset,_T("SELECT * FROM Curve"));
		rsTool.Open(dbOpenDynaset,_T("SELECT * FROM Curve"));
		rsTool.MoveFirst();
		while(!rsTool.IsEOF()){
				rsTool.GetFieldValue (0,OleVariant);
				CString Label=OleVariant.bstrVal;
				rsTool.GetFieldValue (1,OleVariant);
				long UNIT=OleVariant.iVal;
				rsTool.GetFieldValue (2,OleVariant);
				long FILTER=OleVariant.iVal;	
				
				rsJob.AddNew();
				rsJob.SetFieldValue(0,COleVariant(Label));
				rsJob.SetFieldValue(1,COleVariant(UNIT));	
				rsJob.SetFieldValue(2,COleVariant(FILTER));				
				rsJob.Update();
				rsTool.MoveNext();
		}
		rsTool.Close();
		rsJob.Close();

		//����ԭʼ�ź�
		rsJob.Open(dbOpenDynaset,_T("SELECT * FROM Origin"));
		rsTool.Open(dbOpenDynaset,_T("SELECT * FROM Origin"));
		rsTool.MoveFirst();
		while(!rsTool.IsEOF()){
				rsTool.GetFieldValue (0,OleVariant);
				CString Label=OleVariant.bstrVal;
				rsTool.GetFieldValue (1,OleVariant);
				long UNIT=OleVariant.iVal;
				rsTool.GetFieldValue (2,OleVariant);
				long FILTER=OleVariant.iVal;	
				
				rsJob.AddNew();
				rsJob.SetFieldValue(0,COleVariant(Label));
				rsJob.SetFieldValue(1,COleVariant(UNIT));	
				rsJob.SetFieldValue(2,COleVariant(FILTER));				
				rsJob.Update();
				rsTool.MoveNext();
		}
		rsTool.Close();
		rsJob.Close();
		MessageBox(_T("����ɹ�"),MB_OK);
	}
	DisplayTree(1);	
}


void CJobEditDlg::OnBnClickedZcwJobeditExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE,_T(""),_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("tools files(*.tools)|*.tools|All files(*.*)|*.*|"));//���챣���ļ��Ի���
	dlg.m_ofn.lpstrInitialDir=theApp.ToolPath;
    if(dlg.DoModal()==IDOK)//��ʾ�����ļ��Ի���
	{		
		CString strToolPath=dlg.GetPathName();//��ȡ����·������
		if(GetFileAttributes(strToolPath)==-1L){
		CopyFile(m_jobName,strToolPath,TRUE);		
		}else{
			MessageBox(strToolPath+_T("�Ѵ���"),MB_OK);
		}
	}
}


BOOL CJobEditDlg::PreTranslateMessage(MSG* pMsg)
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
