
// DMoniterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "DMonitorDlg.h"
#include "afxdialogex.h"
#include "JobDlg.h"
#include <string>
#include <iostream> 
#include <fstream> 
#include <cassert> 
#include "json\include\json.h"
using namespace std; 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int maxqueue=1000;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int gap = 40;//坐标比例尺跨度
int gap1 = 400;//坐标系1
int gap2 = 150;
int gap3 = 400;//坐标系2
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDMonitorDlg 对话框




CDMonitorDlg::CDMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//设置主界面大小
	m_SM_CXFULLSCREEN = GetSystemMetrics (SM_CXFULLSCREEN);
	m_SM_CYFULLSCREEN = GetSystemMetrics (SM_CYFULLSCREEN);
	minMainDialogWidth = 960;
	minMainDialogHeight = minMainDialogWidth * 9 / 16;
	processType = NO_PROCESSING;
	ClearDataTempa();
	ClearPetroData();
	InitColorVariable();
	pData = NULL;
	bConnect = false;
	unitPixel = 5;//20 pixel = 1 m
	unitRatio = 4;
	m_bDirectDown = true;
	//bOperating = false;
	base = 0;
	bias = 0;
	
	minDepth = 0;
	maxDepth = 0;
	maxPreDepth = 0;
	minDepthLimit = 0;
	maxDepthLimit = 0;
	
	m_drawCount = 0;
	bScroll = false;
	m_step = 5;//每次移动步长为5米
	fp = NULL;
	pPData = NULL;
	pOldPData = NULL;

	bTimer = false;//计时器是否开启
	pos = NULL;//当前记录位置
	
	ClearWorkInfoList();

	pData = NULL;
	fileLimit = 1024*1024*4;
	processType == NO_PROCESSING;

	pPen = NULL;

	VERIFY(m_font.CreateFont(
		18,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial")));                 // lpszFacename

}

void CDMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR_V, mScrollV);
	DDX_Control(pDX, IDC_STATIC_01, cs01);
	DDX_Text(pDX, IDC_STATIC_01, value01);
	DDX_Control(pDX, IDC_STATIC_02, cs02);
	DDX_Text(pDX, IDC_STATIC_02, value02);
	DDX_Control(pDX, IDC_STATIC_03, cs03);
	DDX_Text(pDX, IDC_STATIC_03, value03);
	DDX_Control(pDX, IDC_STATIC_04, cs04);
	DDX_Text(pDX, IDC_STATIC_04, value04);
	DDX_Control(pDX, IDC_EDIT_01, Edit01);
	DDX_Text(pDX, IDC_EDIT_01, strEdit01);
	DDX_Control(pDX, IDC_EDIT_02, Edit02);
	DDX_Text(pDX, IDC_EDIT_02, strEdit02);
	DDX_Control(pDX, IDC_EDIT_03, Edit03);
	DDX_Text(pDX, IDC_EDIT_03, strEdit03);
	DDX_Control(pDX, IDC_EDIT_04, Edit04);
	DDX_Text(pDX, IDC_EDIT_04, strEdit04);
	DDX_Control(pDX, IDC_LIST_DETAIL, listView);
	DDX_Control(pDX, IDC_SCROLLBAR_SCALE, mScrollScaleV);
}

BEGIN_MESSAGE_MAP(CDMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDMonitorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDMonitorDlg::OnBnClickedCancel)
	ON_MESSAGE( WM_USER_RECEIVEDATA, OnCommReceive)//接收端口消息
	ON_MESSAGE( WM_JOBLOAD_OK, OnJobloadReceive)//接收端口消息
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_OPEN, &CDMonitorDlg::OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CDMonitorDlg::OnUpdateFileOpen)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_CONN, &CDMonitorDlg::OnMenuConn)
	ON_UPDATE_COMMAND_UI(ID_MENU_CONN, &CDMonitorDlg::OnUpdateMenuConn)
	ON_COMMAND(ID_MENU_DISCONN, &CDMonitorDlg::OnMenuDisconn)
	ON_UPDATE_COMMAND_UI(ID_MENU_DISCONN, &CDMonitorDlg::OnUpdateMenuDisconn)
	ON_COMMAND(ID_MENU_MEASUREDOWN, &CDMonitorDlg::OnMenuMeasuredown)
	ON_UPDATE_COMMAND_UI(ID_MENU_MEASUREDOWN, &CDMonitorDlg::OnUpdateMenuMeasuredown)
	ON_COMMAND(ID_MENU_MEASUREUP, &CDMonitorDlg::OnMenuMeasureup)
	ON_UPDATE_COMMAND_UI(ID_MENU_MEASUREUP, &CDMonitorDlg::OnUpdateMenuMeasureup)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MENU_INSTRUMENT, &CDMonitorDlg::OnMenuInstrument)
	ON_COMMAND(ID_MENU_JOB, &CDMonitorDlg::OnMenuJob)
	ON_COMMAND(ID_MENU_TOOL, &CDMonitorDlg::OnMenuTool)
	ON_COMMAND(ID_MENU_NEWJOB, &CDMonitorDlg::OnMenuNewjob)
	ON_COMMAND(ID_MENU_JOBLOAD, &CDMonitorDlg::OnMenuJobload)
	ON_COMMAND(ID_TEST_MODE1, &CDMonitorDlg::OnTestMode1)
	ON_COMMAND(ID_MENU_ABOUT, &CDMonitorDlg::OnMenuAbout)
	ON_COMMAND(ID_INSTRUCTION, &CDMonitorDlg::OnInstruction)
END_MESSAGE_MAP()


// CDMonitorDlg 消息处理程序

BOOL CDMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_hMenu = LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));//导入资源,创建菜单
	::SetMenu(this->GetSafeHwnd(),m_hMenu);//添加到对话框
	bExiting = false;
	bLoadAssignment = false;
	OnInitWidget();
	ParseWorkInfoData();
	ParseWorkUnitData();
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST, 0);
	// TODO: 在此添加额外的初始化代码
	ShowWindow(SW_SHOWMAXIMIZED);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CDMonitorDlg::OnInitWidget()
{
	value01.LoadString(IDS_DEEPTH);
	cs01.SetWindowText(value01);
	value02.LoadString(IDS_SPEED);
	cs02.SetWindowText(value02);
	value03.LoadString(IDS_TENSION);
	cs03.SetWindowText(value03);
	value04.LoadString(IDS_STATE);
	cs04.SetWindowText(value04);

	//btSetup.SetWindowText(theApp.GetResString(IDS_SETUP));	
	listView.InsertColumn( 0, theApp.GetResString(IDS_WHY_CURVE), LVCFMT_LEFT, 60 ); 
    listView.InsertColumn( 1, theApp.GetResString(IDS_WHY_VALUE), LVCFMT_LEFT, 60 ); 
	listView.InsertColumn( 2, theApp.GetResString(IDS_WHY_UNIT), LVCFMT_LEFT, 60 ); 
	listView.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP ); 
}
void CDMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
void CDMonitorDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (MessageBox(theApp.GetResString(IDS_EXIT_APP_QUESTION),_T("提示"),MB_ICONQUESTION|MB_OKCANCEL)==IDOK)
	{
		bExiting = true;
		theApp.commLayer.m_SerialPort.ClosePort();//关闭串口
		Sleep(500);
		ClearWorkInfoList();
	
		CDialogEx::OnClose();
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
BOOL CDMonitorDlg::PreTranslateMessage(MSG* pMsg)
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
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		GetClientRect(rectMain);
		GetRectParam(rectMain);
		if(mScrollV)
		{
			mScrollV.SetWindowPos(0,rectScrollV.left,rectScrollV.top,rectScrollV.Width(),rectScrollV.Height(),SWP_NOZORDER);
		}
		if(mScrollScaleV)
		{
			mScrollScaleV.SetWindowPos(0,rectScrollScaleV.left,rectScrollScaleV.top,rectScrollScaleV.Width(),rectScrollScaleV.Height(),SWP_NOZORDER);
		}
		
		dc.FillSolidRect(rectView,crViewBackground); 
		dc.FillSolidRect(rectScale,crViewBackground); 
		CPen pen(PS_SOLID, 1, RGB(0,0,0));
		CPen *oPen = dc.SelectObject(&pen);
		
		dc.Rectangle(rectView.left-1,rectView.top-1,rectView.right+1,rectView.bottom+1);
		dc.Rectangle(rectScale.left-1,rectScale.top-1,rectScale.right+1,rectScale.bottom+1);
		dc.SelectObject(oPen);
		///////////////////////
		/////***********///////
		///////////////////////
		//建立与屏幕显示兼容的内存显示设备，这时还不能绘图，因为没有地方画
		MemDC.CreateCompatibleDC(NULL);  
		//建立一个与屏幕显示兼容的位图，至于位图的大小，可以用窗口的大小  
		MemBitmap.CreateCompatibleBitmap(&dc,rectView.Width(),rectView.Height());  
		CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(0,0,rectView.Width(),rectView.Height(),crViewBackground);
		m_clientRect = rectView;
		m_clientRect.right -= m_clientRect.left; 
		m_clientRect.left = 0;
		m_clientRect.bottom -= m_clientRect.top; 
		m_clientRect.top = 0;

		DrawData(&MemDC);
		//将内存中的图拷贝到屏幕上进行显示  
		dc.BitBlt(rectView.left,rectView.top,rectView.Width(),rectView.Height(),&MemDC,0,0,SRCCOPY);  
		//绘图完成后的清理  
		MemBitmap.DeleteObject();  
		MemDC.DeleteDC(); 
		///////////////////////
		/////***********///////
		///////////////////////
		//建立与坐标屏幕显示兼容的内存显示设备，这时还不能绘图，因为没有地方画
		ScaleMemDC.CreateCompatibleDC(NULL);  
		//建立一个与坐标屏幕显示兼容的位图，至于位图的大小，可以用窗口的大小  
		ScaleMemBitmap.CreateCompatibleBitmap(&dc,rectScale.Width(),rectScale.Height());  
		CBitmap *pScaleOldBit=ScaleMemDC.SelectObject(&ScaleMemBitmap);
		ScaleMemDC.FillSolidRect(0,0,rectScale.Width(),rectScale.Height(),crViewBackground);
		m_scaleRect = rectScale;
		m_scaleRect.right -= m_scaleRect.left; 
		m_scaleRect.left = 0;
		m_scaleRect.bottom -= m_scaleRect.top; 
		m_scaleRect.top = 0;

		DrawScale(&ScaleMemDC);
		//将内存中的图拷贝到屏幕上进行显示  
		dc.BitBlt(rectScale.left,rectScale.top,rectScale.Width(),rectScale.Height(),&ScaleMemDC,0,0,SRCCOPY);  
		//绘图完成后的清理  
		ScaleMemBitmap.DeleteObject();  
		ScaleMemDC.DeleteDC(); 
		///////////////////////
		/////***********///////
		///////////////////////
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDMonitorDlg::InitColorVariable()
{
	crViewBackground = RGB(255,255,255);//背景
	crViewCoordinate = RGB(0,0,0);
	crViewPlot = RGB(127,127,127);//坐标线
	crViewGraduation  = RGB(0,0,0);//刻度
	crViewGridColor = RGB(127,127,127);//RGB(127,127,127);RGB(0,0,0)

	colorRed = RGB(255,0,0);
	colorBlue = RGB(0,0,255);
	colorGreen = RGB(0,255,0);
	colorBlack = RGB(0,0,0);
	colorCyan = RGB(2,141,153);
	colorArray = NULL;
}
void CDMonitorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDMonitorDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDMonitorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI-> ptMinTrackSize.x = minMainDialogWidth ; //宽 
	lpMMI-> ptMinTrackSize.y = min(minMainDialogHeight,m_SM_CYFULLSCREEN) ; //高 
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CDMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	GetClientRect(rectMain);
	GetRectParam(rectMain);
	int mWidth1 = 40;
	int mWidth2 = rectPanel.Width()-20-mWidth1;
	int temp = (rectPanel.Height())/15;
	int mHight = temp*3/4;
	int gap = temp - mHight;
	if(cs01.m_hWnd != NULL)
	{
		cs01.SetWindowPos(NULL,rectPanel.left,rectPanel.top,mWidth1,mHight,0);
	}
	if(Edit01.m_hWnd != NULL)
	{
		Edit01.SetWindowPos(NULL,rectPanel.left+50,rectPanel.top,mWidth2,mHight,0);
	}

	if(cs02.m_hWnd != NULL)
	{
		cs02.SetWindowPos(NULL,rectPanel.left,rectPanel.top + (mHight + gap)*1,mWidth1,mHight,0);
	}
	if(Edit02.m_hWnd != NULL)
	{
		Edit02.SetWindowPos(NULL,rectPanel.left+50,rectPanel.top + (mHight + gap)*1,mWidth2,mHight,0);
	}

	if(cs03.m_hWnd != NULL)
	{
		cs03.SetWindowPos(NULL,rectPanel.left,rectPanel.top + (mHight + gap)*2,mWidth1,mHight,0);
	}
	if(Edit03.m_hWnd != NULL)
	{
		Edit03.SetWindowPos(NULL,rectPanel.left+50,rectPanel.top + (mHight + gap)*2,mWidth2,mHight,0);
	}

	if(cs04.m_hWnd != NULL)
	{
		cs04.SetWindowPos(NULL,rectPanel.left,rectPanel.top + (mHight + gap)*3,mWidth1,mHight,0);
	}
	if(Edit04.m_hWnd != NULL)
	{
		Edit04.SetWindowPos(NULL,rectPanel.left+50,rectPanel.top + (mHight + gap)*3,mWidth2,mHight,0);
	}
	if(listView.m_hWnd != NULL)
	{
		listView.SetWindowPos(NULL,rectPanel.left,rectPanel.top + (mHight + gap)*4,rectPanel.Width()-10,rectPanel.bottom - (mHight + gap)*5 ,0);
	}
	if(mScrollV)
	{
		mScrollV.SetWindowPos(0,rectScrollV.left,rectScrollV.top,rectScrollV.Width(),rectScrollV.Height(),SWP_NOZORDER);
	}
	if(mScrollScaleV)
	{
		mScrollScaleV.SetWindowPos(0,rectScrollScaleV.left,rectScrollScaleV.top,rectScrollScaleV.Width(),rectScrollScaleV.Height(),SWP_NOZORDER);
	}
	InvalidateRect(rectMain);
	// TODO: 在此处添加消息处理程序代码
}

void CDMonitorDlg::GetRectParam(CRect rectMain)
{
	rectMain.left += 2;
	rectMain.top += 25;
	rectMain.right -= 2;
	rectMain.bottom -= 2;

	rectPanel = rectMain;
	rectPanel.right = rectPanel.left+200;

	rectView = rectMain;
	rectView.left = rectPanel.right + 1;
	rectView.right = rectMain.right -20;
	rectView.bottom = rectMain.bottom - 200;

	rectScrollV = rectMain;
	rectScrollV.left = rectView.right + 1;
	rectScrollV.bottom = rectView.bottom;

	rectScale = rectMain;
	rectScale.left = rectPanel.right + 1;
	rectScale.top = rectView.bottom + 10;
	rectScale.right = rectMain.right -20;

	rectScrollScaleV = rectMain;
	rectScrollScaleV.left = rectScale.right + 1;
	rectScrollScaleV.top = rectScale.top;
	rectScrollScaleV.bottom = rectScale.bottom;
}


void CDMonitorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	// TODO: 在此处添加消息处理程序代码
	DestroyMenu(m_hMenu);
}


void CDMonitorDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	if(!bLoadAssignment)
	{
		MessageBox(_T("请加载作业"),_T("提示"),MB_OK);
		return;
	}
	bool bReturn=false;
	processType = FILEDATA_PROCESSING;
	TCHAR   *pFileBuffer = new TCHAR[MAX_PATH];//最多允许300个文件
	CFileDialog dlg (TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER , _T("dmor文件(*.dmor)|*.dmor||"),this);
	if (dlg.DoModal () == IDOK)
	{
		CString csFileName = dlg.GetPathName();
		CFile fAddressImport;
		CFileException eFileException;
		if (!fAddressImport.Open (csFileName, CFile::modeRead | CFile::shareDenyWrite, &eFileException))
		{
			return;
		}
		DWORD dwFileLength = fAddressImport.GetLength ();
		pData = new BYTE[dwFileLength];
		memset(pData,0,dwFileLength);
		fAddressImport.SeekToBegin ();
		fAddressImport.Read (pData,dwFileLength);
		petroList.RemoveAll();
		ParseData(pData,dwFileLength);
		StopTimer();
		StartTimer();
	}
}


void CDMonitorDlg::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CDMonitorDlg::ParseData(BYTE* tmp, WPARAM wParam) 
{
	if(bExiting)
	{
		return;
	}
	std::string str,strTitle,strData;
	CPetroData* pPData = NULL;
	int subId = 0;
	BYTE buf0 = 0;
	bool bSupport = false;
	double iDept = 0;
	for(int i = 0; i< wParam; i++)
	{
		if(i == wParam-1)
		{
			if(pPData != NULL)
			{
				pushToQueue(pPData);
				//petroList.AddTail(pPData);
			}
		}
		if(tmp[i] == '$')//起始标示
		{
			str.clear();
			//TRACE(_T("Find Char '$' \r\n"));
		}
		else if(tmp[i] == ',' || tmp[i] == '*')//数据结束
		{
			bool bUnit = false;
			for(int k=0;k<str_unitlist.size();k++)
			{
				string s = str_unitlist.at(k);
				if(str == s)
				{
					bUnit = true;
					bSupport = true;
				}
			}
			if(bUnit)
			{
				strTitle = str;
				if(str == "DEPT")
				{
					if(pPData != NULL)
					{
						pushToQueue(pPData);
					}
					pPData = new CPetroData();
					subId = 0;
				}
				str.clear();
			}
			else
			{
				int result = CheckString(str);
				//if(result == 0)//整数
				if(str != "LQRD" && bSupport && result != 2 )
				{
					double num;
					num=atof(str.c_str());
					if(pPData != NULL)
					{
						for(int k=0;k<str_unitlist.size();k++)
						{
							string s = str_unitlist.at(k);
							if(strTitle == s)
							{
								DATA_PART dataPart;
								initDataPart(dataPart);
								dataPart.iData = num;
								dataPart.strData = str.c_str();
								dataPart.bAssign = true;
								if(s == "DEPT")
								{
									iDept = num;
								}
								else if(s == "MAG")
								{
									dataPart.subIndex = subId;
									subId++;
								}
								else
								{
									dataPart.subIndex = 0;
								}
								dataPart.iDeptData = iDept;
								dataPart.strTag = strTitle.c_str();
								CWorkInfo* plist = theApp.workInfoList.GetAt(theApp.workInfoList.FindIndex(k));
								dataPart.strUnit = plist->strUnit;
								pPData->pData.push_back(dataPart);
								break;
							}
						}
					}
				}
				str.clear();
				strTitle.clear();
				bSupport = false;
			}
			if( tmp[i] == '*')
			{
				i+=2;
			}
		}
		else if(tmp[i] == 0x0D || tmp[i] == 0x0A)
		{
			continue;
		}
		else
		{
			str += tmp[i];
		}
	}
}

void CDMonitorDlg::pushToQueue(CPetroData* pPData)
{
	int nSize = petroList.GetSize();
	CPetroData* pCurrent = NULL;
	if(nSize >= maxqueue && processType == REALTIME_PROCESSING)
	{
		pCurrent = petroList.RemoveHead();
		delete pCurrent;
		pCurrent=NULL;
	}
	petroList.AddTail(pPData);
}
int CDMonitorDlg::CheckString( std::string str )
{
	bool bIsDigit = true;
	bool bIsPoint = false;
	int nCount = str.length(); // 获得字符个数
	for ( int i = 0; i < nCount; i ++ )
	{
		if ( 0 == isdigit( str[i] ) ) // 不是数字就置标志位
		{
			if(str[i] == '.')//带小数点
			{
				bIsPoint = true;
			}
			else
			{
				bIsDigit = false;
				break;// 退出
			}
		}
	}
	if(!bIsDigit)
	{
		return 2;//非数字
	}
	else if(bIsPoint)
	{
		return 1;//有小数点
	}
	else
	{
		return 0;//整数
	}
}

void CDMonitorDlg::ClearPetroData()
{
	CPetroData* pCurrent = NULL;
	while(petroList.IsEmpty()==false)
	{
		pCurrent = petroList.RemoveHead();
		delete pCurrent;
		pCurrent=NULL;
	}
}
void CDMonitorDlg::InitArrayData()
{
#if 0
	for(int i = 0;i<2;i++)
	{
		tempLimitArray[i] = 0;//0-min;1-max;
		gmLimitArray[i] = 0;
		rmLimitArray[i] = 0;
		cclLimitArray[i] = 0;
		magLimitArray[0][i] = 0;
		magLimitArray[1][i] = 0;
		magLimitArray[2][i] = 0;
	}
#endif
}
void CDMonitorDlg::InitOldArrayData()
{
#if 0
	olddeptArray.dx = 0;
	olddeptArray.dy = 0;
	olddeptArray.bAssign = false;
	olddeptArray.strDx = _T("");

	oldtempArray.dx = 0;
	oldtempArray.dy = 0;
	oldtempArray.bAssign = false;
	oldtempArray.strDx = _T("");

	oldgmArray.dx = 0;
	oldgmArray.dy = 0;
	oldgmArray.bAssign = false;
	oldgmArray.strDx = _T("");

	oldrmArray.dx = 0;
	oldrmArray.dy = 0;
	oldrmArray.bAssign = false;
	oldrmArray.strDx = _T("");

	oldcclArray.dx = 0;
	oldcclArray.dy = 0;
	oldcclArray.bAssign = false;
	oldcclArray.strDx = _T("");

	oldmagArray[0].dx = 0;
	oldmagArray[0].dy = 0;
	oldmagArray[0].bAssign = false;
	oldmagArray[0].strDx = _T("");

	oldmagArray[1].dx = 0;
	oldmagArray[1].dy = 0;
	oldmagArray[1].bAssign = false;
	oldmagArray[1].strDx = _T("");

	oldmagArray[2].dx = 0;
	oldmagArray[2].dy = 0;
	oldmagArray[2].bAssign = false;
	oldmagArray[2].strDx = _T("");
#endif
}
void CDMonitorDlg::PrepareDraw()
{
	base = 0;
	bias = 0;
	counter = 0;
	m_iterator = 1;
	m_drawCount = 0;
	bScroll = false;
	m_step = 5;//每次移动步长为5米
	pPData = NULL;
	pOldPData = NULL;
	pos = NULL;//当前记录位置
	bTimer = true;
	InitOldArrayData();
	InitArrayData();
	if(petroList.IsEmpty())
	{
		return;//没有数据不进行绘制
	}
	if(m_bDirectDown)
	{
		pos = petroList.GetHeadPosition();
	}
	else
	{
		pos = petroList.GetTailPosition();
	}

	if(processType == REALTIME_PROCESSING)
	{
		minDepth = 0;
		maxDepth = 0;
		minDepthLimit = 0;
		maxDepthLimit = 0;
		bScroll = false;
		//AddPanelListView();
		//SetTimer(TIMER_CMD_DRAW,TIME_REFRESH_REALTIME,NULL);
	}
	else// if(theApp.processType == FILEDATA_PROCESSING)
	{
		minDepth = 0;
		maxDepth = 0;
		minDepthLimit = 0;
		maxDepthLimit = 0;
		bScroll = false;
		m_drawCount = TIME_REFRESH_FILE/20;
		GetMaxMinData();//在绘图前进行一次计算的操作
		//AddPanelListView();
		if(m_bDirectDown)
		{
			minDepth = (int)minDepthLimit;
		}
		else
		{
			maxDepth = (int)maxDepthLimit+1;
		}
		SetTimer(TIMER_CMD_DRAW,TIME_REFRESH_FILE,NULL);
	}
}
void CDMonitorDlg::SetRealtimeDataLimit()
{

}
void CDMonitorDlg::GetMaxMinData()
{
	bool isFound = false;
	POSITION pos;
	int mpos = 0;
	if(!petroList.IsEmpty())
	{
		CPetroData* p = NULL;
		pos = petroList.GetHeadPosition();
		while(pos)
		{
			p = petroList.GetNext(pos);
			int size = p->pData.size();
			for(int i=0;i<size;i++)
			{
				if(p->pData.at(i).strTag == _T("DEPT"))
				{
					isFound = true;
					mpos = i;
					break;
				}
			}
			if(isFound)
			{
				break;
			}
		}
		if(isFound)
		{
			minDepthLimit = (double)(p->pData.at(mpos).iData);
			maxDepthLimit = minDepthLimit;
		}
		else
		{
			minDepthLimit = 0;
			maxDepthLimit = 6000;
			return;
		}
	}
	pos = petroList.GetHeadPosition();
	isFound = false;
	mpos = 0;
	while(pos)
	{
		CPetroData* pData = petroList.GetNext(pos);
		int size = pData->pData.size();
		for(int i=0;i<size;i++)
		{
			if(pData->pData.at(i).strTag == _T("DEPT"))
			{
				isFound = true;
				mpos = i;
				break;
			}
		}
		//查找当前最小深度值
		double dData = pData->pData.at(mpos).iData;
		if(minDepthLimit > dData)
		{
			minDepthLimit = dData;
		}
		if(maxDepthLimit < dData)
		{
			maxDepthLimit = dData;
		}

		unsigned long m = 0;
	}
}

void CDMonitorDlg::DrawData(CDC* pDC)
{
	if(processType == REALTIME_PROCESSING)
	{
		DrawRealtimeBasic(pDC);//获取内存映射绘制区域大小
		DrawRealtimeGrid(pDC);
		DrawRealtimePlot(pDC);
		DrawRealtimeCurve(pDC,minDepth,maxDepth);
	}
	else if(processType == FILEDATA_PROCESSING)
	{
		DrawFileDataBasic(pDC);//获取内存映射绘制区域大小
		DrawFileDataGrid(pDC);
		DrawFileDataPlot(pDC);
		DrawFileDataCurve(pDC,minDepth,maxDepth);
	}
	else
	{
		DrawBasic(pDC);//获取内存映射绘制区域大小
		DrawGrid(pDC);
		DrawPlot(pDC);
	}
}

void CDMonitorDlg::DrawScale(CDC* pDC)
{
	if(processType == NO_PROCESSING)
	{
		mScrollScaleV.SetScrollRange(0,0);
		mScrollScaleV.SetScrollPos(0);
	
	}
	else
	{
		CString str;
		CFont font;
		VERIFY(font.CreateFont(
			14,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("Arial")));                 // lpszFacename

		 LOGBRUSH logBrush;

		int i = 0;
		int j = 0;
		int iDrawType = PS_SOLID;
		int iLineWidth = 1;
		COLORREF colorR = RGB(20,20,20);
		CPen pen(iDrawType, 1, colorR); //画笔
		CPen* pOldPen = pDC->SelectObject(&pen);//画笔和画线区连接
		int count1 = theApp.workInfoList.GetCount();
		if(count1 > 0)
		{
			int count  = 0;
			int count2  = 0;
			POSITION pos = theApp.workInfoList.GetHeadPosition();
			while(pos)
			{
				if(count < scaleScrollPos && count2 < scaleScrollPos)
				{
					CWorkInfo* plist = theApp.workInfoList.GetNext(pos);
					if(plist->strTitle == _T("DEPT"))
					{
						continue;
					}
					if(plist->trackNum == 0)
					{
						count++;
					}
					else
					{
						count2++;
					}
					continue;
				}
				CRect rectTop,rectBottom;
			
				CWorkInfo* plist = theApp.workInfoList.GetNext(pos);
				if(plist->strTitle == _T("DEPT"))
				{
					continue;
				}
				if(plist->trackNum == 0)
				{
					memset(&logBrush, 0, sizeof(logBrush));
					logBrush.lbStyle = BS_SOLID;
					logBrush.lbColor = plist->curveColor;
					DWORD dwF[] = {5, 10, 15, 20};
					//画线
					CPen pen;//(iDrawType, iLineWidth, colorR); //画笔
					//pen.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_ROUND, plist->lineWidth, &logBrush,4,dwF);
					pen.CreatePen(plist->lineType|PS_GEOMETRIC|PS_ENDCAP_SQUARE, plist->lineWidth, &logBrush);
					pDC->SelectObject(&pen);//画笔和画线区连接
			
					rectTop = m_scaleRect;
					rectTop.top = gap*i+1;
					rectTop.bottom = gap*i+gap/2-1;
					rectTop.right = rectTop.left + gap1;

					rectBottom = m_scaleRect;
					rectBottom.top = gap*i+gap/2+3;
					rectBottom.bottom = gap*i+gap-1;
					rectBottom.right = rectBottom.left + gap1;

					pDC->MoveTo(0, gap*i+gap/2);
					pDC->LineTo(rectTop.Width(), gap*i+gap/2);

					//画边框
					CPen pen2(PS_SOLID, 1, RGB(0,0,0)); //画笔
					pDC->SelectObject(&pen2);//画笔和画线区连接

					pDC->MoveTo(0, rectBottom.bottom);
					pDC->LineTo(rectBottom.Width(), rectBottom.bottom);

					pDC->MoveTo(rectTop.Width(), rectTop.top);
					pDC->LineTo(rectTop.Width(), rectBottom.bottom);
					//画标注
					pDC->SelectObject(&font);
					pDC->SetTextColor(colorR);   //文本字体颜色为蓝色
					//pDC->TextOut(rect.Width()/2,30*i,plist->strCurveName);   //输出文本值
					pDC->DrawText(plist->strSignal,rectTop,DT_CENTER);

					pDC->SetTextAlign(TA_LEFT);
					str.Format(_T("%f"),plist->leftLimit);
					//pDC->TextOut(1,30*i+16,str);   //输出文本值
					pDC->DrawText(str,rectBottom,DT_LEFT);

					pDC->SetTextAlign(TA_RIGHT);
					str.Format(_T("%f"),plist->rightLimit);
					//pDC->TextOut(rect.Width()-100,30*i+16,str);   //输出文本值
					pDC->DrawText(str,rectBottom,DT_RIGHT);
					i++;
					count++;
				}
				else
				{
					memset(&logBrush, 0, sizeof(logBrush));
					logBrush.lbStyle = BS_SOLID;
					logBrush.lbColor = plist->curveColor;
					DWORD dwF[] = {5, 10, 15, 20};
					//画线
					CPen pen;//(iDrawType, iLineWidth, colorR); //画笔
					//pen.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_ROUND, plist->lineWidth, &logBrush,4,dwF);
					pen.CreatePen(plist->lineType|PS_GEOMETRIC|PS_ENDCAP_SQUARE, plist->lineWidth, &logBrush);
					pDC->SelectObject(&pen);//画笔和画线区连接
			
					rectTop = m_scaleRect;
					rectTop.top = gap*j+1;
					rectTop.bottom = gap*j+gap/2-1;
					rectTop.left = rectTop.left + gap1 + gap2;
					rectTop.right = rectTop.left + gap3;

					rectBottom = m_scaleRect;
					rectBottom.top = gap*j+gap/2+3;
					rectBottom.bottom = gap*j+gap-1;
					rectBottom.left = rectBottom.left + gap1 + gap2;
					rectBottom.right = rectBottom.left + gap3;

					pDC->MoveTo(rectBottom.left, gap*j+gap/2);
					pDC->LineTo(rectBottom.right, gap*j+gap/2);

					//画边框
					CPen pen2(PS_SOLID, 1, RGB(0,0,0)); //画笔
					pDC->SelectObject(&pen2);//画笔和画线区连接

					pDC->MoveTo(rectBottom.left, rectBottom.bottom);
					pDC->LineTo(rectBottom.right, rectBottom.bottom);

					pDC->MoveTo(rectTop.left-1, rectTop.top);
					pDC->LineTo(rectTop.left-1, rectBottom.bottom);

					pDC->MoveTo(rectTop.right, rectTop.top);
					pDC->LineTo(rectTop.right, rectBottom.bottom);
					//画标注
					pDC->SelectObject(&font);
					pDC->SetTextColor(colorR);   //文本字体颜色为蓝色
					//pDC->TextOut(rect.Width()/2,30*i,plist->strCurveName);   //输出文本值
					pDC->DrawText(plist->strSignal,rectTop,DT_CENTER);

					pDC->SetTextAlign(TA_LEFT);
					str.Format(_T("%f"),plist->leftLimit);
					//pDC->TextOut(1,30*i+16,str);   //输出文本值
					pDC->DrawText(str,rectBottom,DT_LEFT);

					pDC->SetTextAlign(TA_RIGHT);
					str.Format(_T("%f"),plist->rightLimit);
					//pDC->TextOut(rect.Width()-100,30*i+16,str);   //输出文本值
					pDC->DrawText(str,rectBottom,DT_RIGHT);
					j++;
					count2++;
				}
				
			}
			
			//画笔刷新
			pDC->SelectObject(pOldPen);  //
		}
	}
}

void CDMonitorDlg::DrawRealtimeCurve(CDC* pDC , double upDepth, double DownDepth)
{
	int iDrawType = PS_SOLID;
	DATA_PART mDataPart;
	bool bFound = false;
	int mCounter = 0;

	long pre_iy=0,cur_iy=0,pre_dy=0,cur_dy=0;
	long pre_ix=0,cur_ix=0,pre_dx=0,cur_dx=0;

	if(processType == REALTIME_PROCESSING)
	{
		if(m_bDirectDown)
		{
			pos = petroList.GetTailPosition();
			
			while(pos)
			{
				pPData = petroList.GetPrev(pos);

				for(int j =0;j<pPData->pData.size();j++)
				{
					mDataPart = pPData->pData.at(j);
					if(mDataPart.strTag == _T("DEPT"))
					{
						bFound = true;
						//OutputDebugString(_T("DrawRealtimeCurve dept = ")+ mDataPart.strData +" \r\n");
						break;
					}
				}
				if(!bFound)
				{
					continue;
				}
				if(mDataPart.bAssign == true)
				{
					if(mDataPart.iData > minDepth)
					{
						DrawParamData(pDC,pPData);//通用
					}
					else
					{
						break;
					}
				}
			}	
		}
		else
		{
			pos = petroList.GetTailPosition();
			while(pos)
			{
				pPData = petroList.GetPrev(pos);

				for(int j =0;j<pPData->pData.size();j++)
				{
					mDataPart = pPData->pData.at(j);
					if(mDataPart.strTag == _T("DEPT"))
					{
						bFound = true;
						break;
					}
				}
				if(!bFound)
				{
					continue;
				}
				//if(pPData->dept.bAssign == true)
				if(mDataPart.bAssign == true)
				{
					//if(pPData->dept.iData < maxDepth)
					if(mDataPart.iData < maxDepth)
					{
						DrawParamData(pDC,pPData);//通用
					}
					else
					{
						break;
					}
				}
			}
		}	
	}
}
void CDMonitorDlg::DrawFileDataCurve(CDC* pDC , double upDepth, double DownDepth)
{
	int iDrawType = PS_SOLID;
	DATA_PART mDataPart;
	bool bFound = false;
	int mCounter = 0;

	long pre_iy=0,cur_iy=0,pre_dy=0,cur_dy=0;
	long pre_ix=0,cur_ix=0,pre_dx=0,cur_dx=0;

	if(processType == FILEDATA_PROCESSING)
	{
		if(m_bDirectDown)
		{
			int TempPos = mScrollV.GetScrollPos();
			int pageMeter = m_clientRect.Height()/unitPixel;
			minDepth = (int)TempPos+minDepthLimit;
			maxDepth = (int)minDepth+pageMeter;

			pos = petroList.GetHeadPosition();
			while(pos)
			{
				pPData = petroList.GetNext(pos);
				for(int j =0;j<pPData->pData.size();j++)
				{
					mDataPart = pPData->pData.at(j);
					if(mDataPart.strTag == _T("DEPT"))
					{
						bFound = true;
						break;
					}
				}
				if(!bFound)
				{
					continue;
				}
				if(mDataPart.bAssign == true)
				{
					if(mDataPart.iData < minDepth)
					{
						continue;
					}
					else
					{
						if(mDataPart.iData < maxDepth)
						{
							if(mDataPart.bAssign)
							{
								DrawParamData(pDC,pPData);//通用
							}
						}
						else
						{
							break;
						}
					}
			
				}
			}
			UpdatePanelListView(pPData);
		}
		else
		{
			int TempPos = mScrollV.GetScrollPos();
			int pageMeter = m_clientRect.Height()/unitPixel;
			minDepth = (int)TempPos+minDepthLimit;
			maxDepth = (int)minDepth+pageMeter;
			pos = petroList.GetTailPosition();
			while(pos)
			{
				pPData = petroList.GetPrev(pos);
				for(int j =0;j<pPData->pData.size();j++)
				{
					mDataPart = pPData->pData.at(j);
					if(mDataPart.strTag == _T("DEPT"))
					{
						bFound = true;
						break;
					}
				}
				if(!bFound)
				{
					continue;
				}
				if(mDataPart.bAssign == true)
				{
					if(mDataPart.iData > maxDepth)
					{
						continue;
					}
					else
					{
						if(mDataPart.iData > minDepth)
						{
								if(mDataPart.bAssign)
								{
									DrawParamData(pDC,pPData);//通用
								}
						}
						else
						{
							break;
						}
					}
			
				}
		
			}
			UpdatePanelListView(pPData);
		}	
	}
}

void CDMonitorDlg::DrawParamData(CDC* pDC ,CPetroData* pPData)
{
	CPen* pOldPen = NULL;
	LOGBRUSH logBrush;
	long pre_iy=0,cur_iy=0;
	long pre_ix=0,cur_ix=0;
	CWorkInfo* p = NULL;
	CDataTemp* mOldArray = NULL;
	int id = 0;
	bool bFound = false;
	int mid = 0;
	int i_dx2 = 0;
	int d_dx2 = 0;
	int iDrawType = PS_SOLID;
	for(int i=0; i< pPData->pData.size(); i++)
	{
		DATA_PART mDataPart = pPData->pData.at(i);
		POSITION pos = theApp.workInfoList.GetHeadPosition();
		while(pos)
		{
			p = theApp.workInfoList.GetNext(pos);
			if(!mDataPart.strTag.Compare(p->strTitle))
			{
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			continue;
		}
		iDrawType = p->lineType;
		bFound = false;
		pos = oldArray.GetHeadPosition();
		while(pos)
		{
			mOldArray = oldArray.GetNext(pos);
			if(!mOldArray->strTag.Compare(mDataPart.strTag))
			{
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			mOldArray = new CDataTemp();
		}
		if(mOldArray->bAssign && mOldArray->strTag != _T("DEPT"))
		{
			CPen pen;//(iDrawType, 1, p->curveColor); 
			memset(&logBrush, 0, sizeof(logBrush));
			logBrush.lbStyle = BS_SOLID;
			logBrush.lbColor = p->curveColor;
			pen.CreatePen(p->lineType|PS_GEOMETRIC|PS_ENDCAP_SQUARE, p->lineWidth, &logBrush);
			pOldPen = pDC->SelectObject(&pen);//画笔和画线区连接

			long lRange = p->rightLimit - p->leftLimit;
			int i_dx = (int)((mOldArray->dx - (int)mOldArray->dx)*10);
			int d_dx = (int)(mOldArray->dx);
			pre_ix = (int)((d_dx - p->leftLimit)*m_plot1Rect.Width()/lRange
					+i_dx*m_plot1Rect.Width()/(10*lRange));
			if(p->trackNum == 0)
			{
				pre_ix = (int)((d_dx - p->leftLimit)*m_plot1Rect.Width()/lRange
					+i_dx*m_plot1Rect.Width()/(10*lRange));
			}
			else
			{
				pre_ix = (int)((d_dx - p->leftLimit)*m_plot3Rect.Width()/lRange
					+i_dx*m_plot3Rect.Width()/(10*lRange));
			}
			if(mDataPart.iData >= p->rightLimit)
			{
				i_dx2 = (int)((p->rightLimit - (int)p->rightLimit)*10);
				d_dx2 = (int)(p->rightLimit);
			}
			else if(mDataPart.iData <= p->leftLimit)
			{
				i_dx2 = (int)((p->leftLimit - (int)p->leftLimit)*10);
				d_dx2 = (int)(p->leftLimit);				
			}
			else
			{
				i_dx2 = (int)((mDataPart.iData - (int)mDataPart.iData)*10);
				d_dx2 = (int)(mDataPart.iData);
			}
			if(p->trackNum == 0)
			{
				mid = (int)((d_dx2 - p->leftLimit)*m_plot1Rect.Width()/lRange
				+i_dx2*m_plot1Rect.Width()/(10*lRange));
			}
			else
			{
				mid = (int)((d_dx2 - p->leftLimit)*m_plot3Rect.Width()/lRange
				+i_dx2*m_plot3Rect.Width()/(10*lRange));
			}
			cur_ix = (int)mid;
			pre_iy = (mOldArray->dy - minDepth)*unitPixel;
			cur_iy = (mDataPart.iDeptData - minDepth)*unitPixel;
			if(p->trackNum == 0)
			{
				pDC->MoveTo(pre_ix,pre_iy);
				pDC->LineTo(cur_ix,cur_iy);
			}
			else
			{
				pDC->MoveTo(m_plot3Rect.left + pre_ix,pre_iy);
				pDC->LineTo(m_plot3Rect.left + cur_ix,cur_iy);
			}
			if(pOldPen != NULL)
			{
				pDC->SelectObject(pOldPen);
			}
		}
		if(mDataPart.iData >= p->rightLimit)
		{
			mOldArray->dx = p->rightLimit;
		}
		else if(mDataPart.iData <= p->leftLimit)
		{
			mOldArray->dx = p->leftLimit;
		}
		else
		{
			mOldArray->dx = mDataPart.iData;
		}
		mOldArray->bAssign = mDataPart.bAssign;
		mOldArray->dy = mDataPart.iDeptData;
		mOldArray->strDx = mDataPart.strData;
		mOldArray->strTag = mDataPart.strTag;
		mOldArray->subIndex = mDataPart.subIndex;
		if(!bFound)
		{
			oldArray.AddTail(mOldArray);
		}
		bFound = false;
	}
}

unsigned long CDMonitorDlg::GetMinData(DATA_PART tmp,unsigned long m)
{
	unsigned long t = 0;
	if(tmp.bAssign == false)
	{
		return m;
	}
	if(tmp.iData > 0)
	{
		if(m == 0)
		{
			t = tmp.iData/10*10;
		}
		else
		{
			t = min(m,tmp.iData/10*10);
		}
		return t;
	}
	else
	{
		return m;
	}
}
void CDMonitorDlg::DrawBasic(CDC * pDC)
{
	m_totalRect = rectView;
	maxPreDepth = maxDepth;
	int depPixel = 0;

	if(processType == NO_PROCESSING)
	{
		m_totalRect.bottom = m_totalRect.top + max(depPixel,m_totalRect.Height());
		mScrollV.SetScrollRange(0,m_totalRect.bottom-m_totalRect.top);
		mScrollV.SetScrollPos(0);
	
	}
}
void CDMonitorDlg::DrawRealtimeBasic(CDC * pDC)
{
	m_totalRect = rectView;
	maxPreDepth = maxDepth;
	int depPixel = 0;
	if(processType == REALTIME_PROCESSING)
	{
		CPetroData * pHeadData = petroList.GetHead();
		CPetroData * pTailData = petroList.GetTail();
		DATA_PART headData;
		DATA_PART tailData;
		for(int j =0;j<pHeadData->pData.size();j++)
		{			
			if(pHeadData->pData.at(j).strTag == _T("DEPT"))
			{
				headData = pHeadData->pData.at(j);
				break;
			}
		}
		for(int j =0;j<pTailData->pData.size();j++)
		{
			if(pTailData->pData.at(j).strTag == _T("DEPT"))
			{
				tailData = pTailData->pData.at(j);
				break;
			}
		}
		if(m_bDirectDown)
		{
			minDepthLimit = headData.iData;
			maxDepthLimit = tailData.iData;
			if(bScroll)
			{
				maxDepth = maxDepthLimit;
				minDepth = maxDepth - m_clientRect.Height()/unitPixel;
			}
			else
			{
				maxDepth = maxDepthLimit;
				minDepth = maxDepth - m_clientRect.Height()/unitPixel;
			}
		}
		else
		{
			maxDepthLimit = headData.iData;
			minDepthLimit = tailData.iData;
			if(bScroll)
			{
				minDepth = minDepthLimit;
				maxDepth = minDepth + m_clientRect.Height()/unitPixel;
			}
			else
			{
				minDepth = minDepthLimit;
				maxDepth = minDepth + m_clientRect.Height()/unitPixel;
			}
		}
	
		mScrollV.SetScrollRange(0,0);
		mScrollV.SetScrollPos(0);
	}
}
void CDMonitorDlg::DrawFileDataBasic(CDC * pDC)
{
	m_totalRect = rectView;
	maxPreDepth = maxDepth;
	int depPixel = 0;
	if(processType == FILEDATA_PROCESSING)
	{

	}
}
void CDMonitorDlg::DrawGrid(CDC * pDC)
{
	m_plot1Rect = m_clientRect;
	m_plot1Rect.right = m_plot1Rect.left + gap1;

	m_plot2Rect = m_clientRect;
	m_plot2Rect.left = m_plot1Rect.right;
	m_plot2Rect.right = m_plot2Rect.left + gap2;

	m_plot3Rect = m_clientRect;
	m_plot3Rect.left = m_plot2Rect.right;
	m_plot3Rect.right = m_plot3Rect.left + gap3;


	CPen *old, pen(PS_SOLID, 1, crViewGridColor), pen2(PS_DOT, 1,crViewGridColor); //画笔;
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));
	old = pDC->SelectObject(&pen);
	//绘制坐标系
	int iCount=0;

	for (int i=m_plot1Rect.left,iCount= 0;i<=m_plot1Rect.right;i+=unitPixel*unitRatio,iCount++)
	{
		if(iCount != 0 && iCount%5 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(i,m_plot1Rect.top); //
			pDC->LineTo(i,m_plot1Rect.bottom);
		}
		else
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(i,m_plot1Rect.top); // [0,0]
			pDC->LineTo(i,m_plot1Rect.bottom);
		}
	}
	for (int i=m_plot3Rect.left,iCount = 0;i<=m_plot3Rect.right;i+=unitPixel*unitRatio,iCount++)
	{
		
		if(iCount%5 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(i,m_plot3Rect.top);
			pDC->LineTo(i,m_plot3Rect.bottom);
		}
		else
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(i,m_plot3Rect.top);
			pDC->LineTo(i,m_plot3Rect.bottom);
		}
	}
	for (int j=m_plot1Rect.top,iCount = 0;j<=m_plot3Rect.bottom;j+=unitPixel,iCount++)
	{
		
		if(iCount != 0 && (iCount)%10 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_plot1Rect.left,j); 
			pDC->LineTo(m_plot1Rect.right,j);
		}
		else if(iCount != 0 && (iCount)%5 == 0)
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(m_plot1Rect.left,j); 
			pDC->LineTo(m_plot1Rect.right,j);
		}
	}
	for (int j=m_plot3Rect.top,iCount = 0;j<=m_plot3Rect.bottom;j+=unitPixel,iCount++)
	{
		if(iCount != 0 && (iCount)%10 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_plot3Rect.left,j);
			pDC->LineTo(m_plot3Rect.right,j);
		}
		else if(iCount != 0 && (iCount)%5 == 0)
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(m_plot3Rect.left,j); 
			pDC->LineTo(m_plot3Rect.right,j);
		}
	}
	//画笔刷新
	pDC->SelectObject(old);
}
void CDMonitorDlg::DrawRealtimeGrid(CDC * pDC)
{
	m_plot1Rect = m_clientRect;
	m_plot1Rect.right = m_plot1Rect.left + 400;

	m_plot2Rect = m_clientRect;
	m_plot2Rect.left = m_plot1Rect.right;
	m_plot2Rect.right = m_plot2Rect.left + 150;

	m_plot3Rect = m_clientRect;
	m_plot3Rect.left = m_plot2Rect.right;
	m_plot3Rect.right = m_plot3Rect.left + 400;

	CPen *old, pen(PS_SOLID, 1, crViewGridColor), pen2(PS_DOT, 1,crViewGridColor); //画笔;
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));
	old = pDC->SelectObject(&pen);
	//绘制坐标系
	int iCount=0;

	for (int i=m_plot1Rect.left,iCount= 0;i<=m_plot1Rect.right;i+=unitPixel*unitRatio,iCount++)
	{
		if(iCount != 0 && iCount%5 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(i,m_plot1Rect.top); //
			pDC->LineTo(i,m_plot1Rect.bottom);
		}
		else
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(i,m_plot1Rect.top); // [0,0]
			pDC->LineTo(i,m_plot1Rect.bottom);
		}
	}
	for (int i=m_plot3Rect.left,iCount = 0;i<=m_plot3Rect.right;i+=unitPixel*unitRatio,iCount++)
	{
		
		if(iCount%5 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(i,m_plot3Rect.top);
			pDC->LineTo(i,m_plot3Rect.bottom);
		}
		else
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(i,m_plot3Rect.top);
			pDC->LineTo(i,m_plot3Rect.bottom);
		}
	}
	for (int j=m_plot1Rect.top,iCount = 0;j<=m_plot3Rect.bottom;j+=unitPixel,iCount++)
	{
		
		if(iCount != 0 && (iCount)%10 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_plot1Rect.left,j); 
			pDC->LineTo(m_plot1Rect.right,j);
		}
		else if(iCount != 0 && (iCount)%5 == 0)
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(m_plot1Rect.left,j); 
			pDC->LineTo(m_plot1Rect.right,j);
		}
	}
	for (int j=m_plot3Rect.top,iCount = 0;j<=m_plot3Rect.bottom;j+=unitPixel,iCount++)
	{
		if(iCount != 0 && (iCount)%10 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_plot3Rect.left,j);
			pDC->LineTo(m_plot3Rect.right,j);
		}
		else if(iCount != 0 && (iCount)%5 == 0)
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(m_plot3Rect.left,j); 
			pDC->LineTo(m_plot3Rect.right,j);
		}
	}
	//画笔刷新
	pDC->SelectObject(old);
}
void CDMonitorDlg::DrawFileDataGrid(CDC * pDC)
{
	m_plot1Rect = m_clientRect;
	m_plot1Rect.right = m_plot1Rect.left + 400;

	m_plot2Rect = m_clientRect;
	m_plot2Rect.left = m_plot1Rect.right;
	m_plot2Rect.right = m_plot2Rect.left + 150;

	m_plot3Rect = m_clientRect;
	m_plot3Rect.left = m_plot2Rect.right;
	m_plot3Rect.right = m_plot3Rect.left + 400;

	CPen *old, pen(PS_SOLID, 1, crViewGridColor), pen2(PS_DOT, 1,crViewGridColor); //画笔;
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));
	old = pDC->SelectObject(&pen);
	//绘制坐标系
	int iCount=0;

	for (int i=m_plot1Rect.left,iCount= 0;i<=m_plot1Rect.right;i+=unitPixel*unitRatio,iCount++)
	{
		if(iCount != 0 && iCount%5 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(i,m_plot1Rect.top); //
			pDC->LineTo(i,m_plot1Rect.bottom);
		}
		else
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(i,m_plot1Rect.top); // [0,0]
			pDC->LineTo(i,m_plot1Rect.bottom);
		}
	}
	for (int i=m_plot3Rect.left,iCount = 0;i<=m_plot3Rect.right;i+=unitPixel*unitRatio,iCount++)
	{
		
		if(iCount%5 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(i,m_plot3Rect.top);
			pDC->LineTo(i,m_plot3Rect.bottom);
		}
		else
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(i,m_plot3Rect.top);
			pDC->LineTo(i,m_plot3Rect.bottom);
		}
	}
	for (int j=m_plot1Rect.top,iCount = 0;j<=m_plot3Rect.bottom;j+=unitPixel,iCount++)
	{
		
		if(iCount != 0 && (iCount)%10 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_plot1Rect.left,j); 
			pDC->LineTo(m_plot1Rect.right,j);
		}
		else if(iCount != 0 && (iCount)%5 == 0)
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(m_plot1Rect.left,j); 
			pDC->LineTo(m_plot1Rect.right,j);
		}
	}
	for (int j=m_plot3Rect.top,iCount = 0;j<=m_plot3Rect.bottom;j+=unitPixel,iCount++)
	{
		if(iCount != 0 && (iCount)%10 == 0)
		{
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_plot3Rect.left,j);
			pDC->LineTo(m_plot3Rect.right,j);
		}
		else if(iCount != 0 && (iCount)%5 == 0)
		{
			pDC->SelectObject(&pen2);
			pDC->MoveTo(m_plot3Rect.left,j); 
			pDC->LineTo(m_plot3Rect.right,j);
		}
	}
	//画笔刷新
	pDC->SelectObject(old);
}
void CDMonitorDlg::DrawPlot(CDC* pDC)
{
	m_zoomFont.lfHeight			= -13;
	m_zoomFont.lfWidth			= 0;
	m_zoomFont.lfEscapement		= 0;
	m_zoomFont.lfOrientation		= 0;
	m_zoomFont.lfWeight			= 400;
	m_zoomFont.lfItalic			= FALSE;
	m_zoomFont.lfUnderline		= FALSE;
	m_zoomFont.lfStrikeOut		= FALSE;
	m_zoomFont.lfCharSet			= ANSI_CHARSET;
	m_zoomFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_zoomFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_zoomFont.lfQuality			= PROOF_QUALITY;
	m_zoomFont.lfPitchAndFamily	= DEFAULT_PITCH;
	wcscpy(m_zoomFont.lfFaceName,_T("Ariel"));
	
	m_font.Detach();
	m_font.CreateFontIndirect(&m_zoomFont);
	CFont *oFont = pDC->SelectObject(&m_font);
	CRect textRect;
	CSize z=pDC->GetTextExtent(CString("A"));
	textRect = m_plot2Rect;
	textRect.left += 2;
	textRect.right -= 2;
	CString str;
	int TempPos = mScrollV.GetScrollPos();
	int pageMeter = m_clientRect.Height()/unitPixel;
	minDepth = (int)TempPos+minDepthLimit;
	maxDepth = (int)minDepth+pageMeter;
	for (int i=m_plot2Rect.top,iCount = 0;i<=m_plot2Rect.bottom;i+=unitPixel*10,iCount++)
	{
		textRect.top = m_plot2Rect.top + i-z.cy/2;
		textRect.bottom = textRect.top + z.cy;
		double tmp = i/unitPixel+minDepth;
		str.Format(_T("%.1f"),tmp);
		pDC->DrawText(str,textRect,DT_LEFT|DT_VCENTER);

	}
	pDC->SelectObject(oFont);
}
void CDMonitorDlg::DrawRealtimePlot(CDC* pDC)
{
	m_zoomFont.lfHeight			= -13;
	m_zoomFont.lfWidth			= 0;
	m_zoomFont.lfEscapement		= 0;
	m_zoomFont.lfOrientation		= 0;
	m_zoomFont.lfWeight			= 400;
	m_zoomFont.lfItalic			= FALSE;
	m_zoomFont.lfUnderline		= FALSE;
	m_zoomFont.lfStrikeOut		= FALSE;
	m_zoomFont.lfCharSet			= ANSI_CHARSET;
	m_zoomFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_zoomFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_zoomFont.lfQuality			= PROOF_QUALITY;
	m_zoomFont.lfPitchAndFamily	= DEFAULT_PITCH;
	wcscpy(m_zoomFont.lfFaceName,_T("Ariel"));
	
	m_font.Detach();
	m_font.CreateFontIndirect(&m_zoomFont);
	CFont *oFont = pDC->SelectObject(&m_font);
	CRect textRect;
	CSize z=pDC->GetTextExtent(CString("A"));
	textRect = m_plot2Rect;
	textRect.left += 2;
	textRect.right -= 2;
	CString str;
	int TempPos = mScrollV.GetScrollPos();
	int pageMeter = m_clientRect.Height()/unitPixel;
	//minDepth = (int)TempPos+minDepthLimit;
	//maxDepth = (int)minDepth+pageMeter;
	if(m_bDirectDown)
	{
		for (int i=m_plot2Rect.bottom,iCount = 0;i>=m_plot2Rect.top;i-=unitPixel*10,iCount++)
		{
			textRect.top = m_plot2Rect.top + i-z.cy/2;
			textRect.bottom = textRect.top + z.cy;
			double tmp = maxDepth - ((m_plot2Rect.bottom - i)/unitPixel);
			str.Format(_T("%.1f"),tmp);
			//OutputDebugString(_T("DrawRealtimePlot dept = ")+ str +" \r\n");
			pDC->DrawText(str,textRect,DT_LEFT|DT_VCENTER);

		}
	}
	else
	{
		for (int i=m_plot2Rect.top,iCount = 0;i<=m_plot2Rect.bottom;i+=unitPixel*10,iCount++)
		{
			textRect.top = m_plot2Rect.top + i-z.cy/2;
			textRect.bottom = textRect.top + z.cy;
			double tmp = i/unitPixel+minDepth;
			str.Format(_T("%.1f"),tmp);
			pDC->DrawText(str,textRect,DT_LEFT|DT_VCENTER);

		}
	}
	pDC->SelectObject(oFont);
}
void CDMonitorDlg::DrawFileDataPlot(CDC* pDC)
{
	m_zoomFont.lfHeight			= -13;
	m_zoomFont.lfWidth			= 0;
	m_zoomFont.lfEscapement		= 0;
	m_zoomFont.lfOrientation		= 0;
	m_zoomFont.lfWeight			= 400;
	m_zoomFont.lfItalic			= FALSE;
	m_zoomFont.lfUnderline		= FALSE;
	m_zoomFont.lfStrikeOut		= FALSE;
	m_zoomFont.lfCharSet			= ANSI_CHARSET;
	m_zoomFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_zoomFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_zoomFont.lfQuality			= PROOF_QUALITY;
	m_zoomFont.lfPitchAndFamily	= DEFAULT_PITCH;
	wcscpy(m_zoomFont.lfFaceName,_T("Ariel"));
	
	m_font.Detach();
	m_font.CreateFontIndirect(&m_zoomFont);
	CFont *oFont = pDC->SelectObject(&m_font);
	CRect textRect;
	CSize z=pDC->GetTextExtent(CString("A"));
	textRect = m_plot2Rect;
	textRect.left += 2;
	textRect.right -= 2;
	CString str;
	int TempPos = mScrollV.GetScrollPos();
	int pageMeter = m_clientRect.Height()/unitPixel;
	minDepth = (int)TempPos+minDepthLimit;
	maxDepth = (int)minDepth+pageMeter;
	for (int i=m_plot2Rect.top,iCount = 0;i<=m_plot2Rect.bottom;i+=unitPixel*10,iCount++)
	{
		textRect.top = m_plot2Rect.top + i-z.cy/2;
		textRect.bottom = textRect.top + z.cy;
		double tmp = i/unitPixel+minDepth;
		str.Format(_T("%.1f"),tmp);
		pDC->DrawText(str,textRect,DT_LEFT|DT_VCENTER);

	}
	pDC->SelectObject(oFont);
}
void CDMonitorDlg::CalculateParam()
{
	CPetroData * pHeadData = petroList.GetHead();
	CPetroData * pTailData = petroList.GetTail();

	DATA_PART headData;
	DATA_PART tailData;
	for(int j =0;j<pHeadData->pData.size();j++)
	{			
		if(pHeadData->pData.at(j).strTag == _T("DEPT"))
		{
			headData = pHeadData->pData.at(j);
			break;
		}
	}

	for(int j =0;j<pTailData->pData.size();j++)
	{
		if(pTailData->pData.at(j).strTag == _T("DEPT"))
		{
			tailData = pTailData->pData.at(j);
			break;
		}
	}
	if(headData.iData < tailData.iData)
	{
		m_bDirectDown = true;
	}
	else
	{
		m_bDirectDown = false;
	}
	
}

void CDMonitorDlg::StartTimer()
{
	base = 0;
	bias = 0;
	counter = 0;
	m_iterator = 1;
	m_drawCount = 0;
	bScroll = false;
	m_step = 5;//每次移动步长为5米
	pPData = NULL;
	pOldPData = NULL;
	pos = NULL;//当前记录位置
	bTimer = true;
	InitOldArrayData();
	InitArrayData();
	ClearDataTempa();
	SetScaleScroll();
	if(processType == REALTIME_PROCESSING)
	{
		minDepth = 0;
		maxDepth = 0;
		minDepthLimit = 0;
		maxDepthLimit = 0;
		AddPanelListView();
		bScroll = false;
		InvalidateRect(rectScale,false);
		SetTimer(TIMER_CMD_DRAW,TIME_REFRESH_REALTIME,NULL);
	}
	else if(processType == FILEDATA_PROCESSING)
	{
		if(petroList.IsEmpty())
		{
			return;//没有数据不进行绘制
		}
		if(m_bDirectDown)
		{
			pos = petroList.GetHeadPosition();
		}
		else
		{
			pos = petroList.GetTailPosition();
		}
		minDepth = 0;
		maxDepth = 0;
		minDepthLimit = 0;
		maxDepthLimit = 0;
		bScroll = false;
		m_drawCount = TIME_REFRESH_FILE/20;
		GetMaxMinData();//在绘图前进行一次计算的操作
		AddPanelListView();
		int pageMeter = m_clientRect.Height()/unitPixel;
		if(m_bDirectDown)
		{
			mScrollV.SetScrollRange(0,(maxDepthLimit - minDepthLimit - pageMeter));
			mScrollV.SetScrollPos(maxDepthLimit - minDepthLimit - pageMeter);
		}
		else
		{
			mScrollV.SetScrollRange(0,(maxDepthLimit - minDepthLimit - pageMeter));
			mScrollV.SetScrollPos(0);
		}
		SetTimer(TIMER_CMD_DRAW,TIME_REFRESH_FILE,NULL);
	}
}

void CDMonitorDlg::StopTimer()
{
	bTimer = false;
	KillTimer(TIMER_CMD_DRAW);
}

void CDMonitorDlg::SetScaleScroll()
{
	scaleScrollPos = 0;
	m_totalScaleRect = m_scaleRect;
	m_totalScaleRect.bottom = m_scaleRect.top + gap*theApp.workInfoList.GetCount();
	mScrollScaleV.SetScrollRange(0,m_totalScaleRect.Height()- m_scaleRect.Height());
	mScrollScaleV.SetScrollPos(0);
}
void CDMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case TIMER_CMD_DRAW:
		{
			if(processType == FILEDATA_PROCESSING)
			{				
				Invalidate();
				KillTimer(TIMER_CMD_DRAW);
				return;
			}
			else if(processType == REALTIME_PROCESSING)
			{
				if(!petroList.IsEmpty())
				{
					//CalculateParam();
					if(m_bDirectDown)
					{
						UpdatePanelListView(petroList.GetTail());
					}
					else
					{
						UpdatePanelListView(petroList.GetHead());
					}
					InvalidateRect(rectView,false);
				}
				SetTimer(TIMER_CMD_DRAW,TIME_REFRESH_REALTIME,NULL);
			}
			else if(processType == NO_PROCESSING)
			{
				
			}
		}
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDMonitorDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if((CScrollBar*)GetDlgItem(IDC_SCROLLBAR_V) == pScrollBar)
	{
		int TempPos = pScrollBar->GetScrollPos();
		int pageMeter = m_clientRect.Height()/unitPixel;
		switch(nSBCode)
		{
		case SB_THUMBPOSITION://拖动滑块
			pScrollBar->SetScrollPos(nPos);
			if(processType == FILEDATA_PROCESSING)
			{
				TempPos = pScrollBar->GetScrollPos();
				if(TempPos<pageMeter)
				{
					TempPos = 0;
				}
				else if(TempPos>maxDepthLimit - minDepthLimit - pageMeter)
				{
					TempPos = maxDepthLimit - minDepthLimit - pageMeter;
				}
				else
				{
					TempPos = pScrollBar->GetScrollPos();
				}
				minDepth = (int)TempPos+minDepthLimit;
				maxDepth = (int)minDepth+pageMeter;
			}
			InvalidateRect(rectView,false);
			break;
		case SB_LINEUP://点击上边的箭头
			if(processType == FILEDATA_PROCESSING)
			{
				if(TempPos<pageMeter)
				{
					TempPos = 0;
				}
				else
				{
					TempPos -= pageMeter;
				}
				minDepth = (int)TempPos+minDepthLimit;
				maxDepth = (int)minDepth+pageMeter;
				pScrollBar->SetScrollPos(TempPos);
			}
			InvalidateRect(rectView,false);
			break;
		case SB_LINEDOWN://点击下边的箭头
			if(processType == FILEDATA_PROCESSING)
			{
				if(TempPos>maxDepthLimit - minDepthLimit - pageMeter)
				{
					TempPos = maxDepthLimit - minDepthLimit - pageMeter;
				}
				else
				{
					TempPos += pageMeter;
				}
				minDepth = (int)TempPos+minDepthLimit;
				maxDepth = (int)minDepth+pageMeter;
				pScrollBar->SetScrollPos(TempPos);
			}
			InvalidateRect(rectView,false);
			break;
		case SB_PAGEUP://向上翻页
			if(processType == FILEDATA_PROCESSING)
			{
				if(TempPos<pageMeter)
				{
					TempPos = 0;
				}
				else
				{
					TempPos -= pageMeter;
				}
				minDepth = (int)TempPos+minDepthLimit;
				maxDepth = (int)minDepth+pageMeter;
				pScrollBar->SetScrollPos(TempPos);
			}
			InvalidateRect(rectView,false);
			break;
		case SB_PAGEDOWN://向下翻页
			if(processType == FILEDATA_PROCESSING)
			{
				if(TempPos>maxDepthLimit - minDepthLimit - pageMeter)
				{
					TempPos = maxDepthLimit - minDepthLimit - pageMeter;
				}
				else
				{
					TempPos += pageMeter;
				}
				minDepth = (int)TempPos+minDepthLimit;
				maxDepth = (int)minDepth+pageMeter;
				pScrollBar->SetScrollPos(TempPos);
			}
			InvalidateRect(rectView,false);
			break;
		} 
	}
	else if((CScrollBar*)GetDlgItem(IDC_SCROLLBAR_SCALE) == pScrollBar)
	{
		int TempPos = pScrollBar->GetScrollPos();
		int pageMeter = m_totalScaleRect.Height() - m_scaleRect.Height();
		switch(nSBCode)
		{
		case SB_THUMBPOSITION://拖动滑块
			pScrollBar->SetScrollPos(nPos);
			if(processType == FILEDATA_PROCESSING || processType == REALTIME_PROCESSING)
			{
				TempPos = pScrollBar->GetScrollPos();
				if(TempPos<=0)
				{
					TempPos = 0;

				}
				else if(TempPos>pageMeter)
				{
					TempPos = pageMeter;
					scaleScrollPos++;
				}
				else
				{
					TempPos = pScrollBar->GetScrollPos();
				}
				scaleScrollPos = TempPos/gap;
			}
			InvalidateRect(rectScale,false);
			break;
		case SB_LINEUP://点击上边的箭头
			if(processType == FILEDATA_PROCESSING || processType == REALTIME_PROCESSING)
			{
				if(TempPos<=0)
				{
					TempPos = 0;
				}
				else
				{
					TempPos -= gap;
				}
				pScrollBar->SetScrollPos(TempPos);
				scaleScrollPos = TempPos/gap;
			}
			InvalidateRect(rectScale,false);
			break;
		case SB_LINEDOWN://点击下边的箭头
			if(processType == FILEDATA_PROCESSING || processType == REALTIME_PROCESSING)
			{
				if(TempPos>pageMeter)
				{
					TempPos = pageMeter;
				}
				else
				{
					TempPos += gap;
				}
				pScrollBar->SetScrollPos(TempPos);
				scaleScrollPos = TempPos/gap;
			}
			InvalidateRect(rectScale,false);
			break;
		case SB_PAGEUP://向上翻页
			if(processType == FILEDATA_PROCESSING || processType == REALTIME_PROCESSING)
			{
				if(TempPos<=0)
				{
					TempPos = 0;
				}
				else
				{
					TempPos -= gap;
				}
				pScrollBar->SetScrollPos(TempPos);
				scaleScrollPos = TempPos/gap;
			}
			InvalidateRect(rectScale,false);
			break;
		case SB_PAGEDOWN://向下翻页
			if(processType == FILEDATA_PROCESSING || processType == REALTIME_PROCESSING)
			{
				if(TempPos>pageMeter)
				{
					TempPos = pageMeter;
				}
				else
				{
					TempPos += gap;
				}
				pScrollBar->SetScrollPos(TempPos);
				scaleScrollPos = TempPos/gap;
			}
			InvalidateRect(rectScale,false);
			break;
		} 
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}




void CDMonitorDlg::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CDMonitorDlg::OnMenuConn()
{
	// TODO: 在此添加命令处理程序代码
	if(!bLoadAssignment)
	{
		MessageBox(_T("请加载作业"),_T("提示"),MB_OK);
		return;
	}
	CMenu* pSubMenu = NULL;
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	{
		pSubMenu = pMainMenu->GetSubMenu(1);
		if (pSubMenu && pSubMenu->GetMenuItemID(0) == ID_MENU_CONN)
		{
			pSubMenu->CheckMenuItem(ID_MENU_CONN,MF_CHECKED); 
		}
		if (pSubMenu && pSubMenu->GetMenuItemID(1) == ID_MENU_DISCONN)
		{
			pSubMenu->CheckMenuItem(ID_MENU_DISCONN,MF_UNCHECKED); 
		}
	}
	if(bConnect == true)
	{
		return;
	}
	bConnect = true;
	theApp.commLayer.SetConnectType(TYPE_NONE);
	theApp.commLayer.fatherHwnd = (AfxGetMainWnd()->GetSafeHwnd());//获取HWND，赋值给通信层进行消息传递
	
	CString strTime;
	//获取系统时间
	CTime tm;
	tm=CTime::GetCurrentTime();
	strTime=tm.Format(_T("(%Y-%m-%d-%H-%M-%S)"));
	fileName = theApp.DataPath + _T("export ")+strTime;
	CFileDialog dlg (FALSE, _T("dmor"), fileName, OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT, NULL);
	if (dlg.DoModal () == IDOK)
	{
		sGetFileName = dlg.GetPathName ();
		openDataFile(sGetFileName);
	}
	totalReceiveByte = 0;
	fileNum = 0;
	theApp.m_CommResault=theApp.commLayer.CreatConnect();
	if(theApp.m_CommResault==COMM_SUCCESS)
	{
		processType = REALTIME_PROCESSING;
		StartTimer();
	}
	if(theApp.m_CommResault==COMM_ERROE_HARDWARE_CONNECT_FAIL)
	{
		//TRACE(_T("Communication Fail!\n"));
	}
}


void CDMonitorDlg::OnUpdateMenuConn(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CDMonitorDlg::OnMenuDisconn()
{
	// TODO: 在此添加命令处理程序代码
	CMenu* pSubMenu = NULL;
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	{
		pSubMenu = pMainMenu->GetSubMenu(1);
		if (pSubMenu && pSubMenu->GetMenuItemID(0) == ID_MENU_CONN)
		{
			pSubMenu->CheckMenuItem(ID_MENU_CONN,MF_UNCHECKED); 
		}
		if (pSubMenu && pSubMenu->GetMenuItemID(1) == ID_MENU_DISCONN)
		{
			pSubMenu->CheckMenuItem(ID_MENU_DISCONN,MF_CHECKED); 
		}
	}
	if(bConnect == false)
	{
		return;
	}
	bConnect = false;
	StopTimer();
	theApp.commLayer.m_SerialPort.ClosePort();//关闭串口
	//bRunning = false;
	Sleep(500);
	closeDataFile(sGetFileName);
}


void CDMonitorDlg::OnUpdateMenuDisconn(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CDMonitorDlg::closeDataFile(CString strFile)  
{    
	if(fp != NULL)
	{
		fclose(fp);   
	}
} 
void CDMonitorDlg::openDataFile(CString strFile)  
{   
	if(fp != NULL)
	{
		fclose(fp);  
	}
	fp = _wfopen(strFile, _T("w")); 
} 

LRESULT CDMonitorDlg::OnJobloadReceive(WPARAM wParam, LPARAM lParam)
{
	CString CurrentJob=theApp.ToolPath+_T("currentjob.json");
	//char * pFileName = theApp.FromUNICODEToANSI(CurrentJob);
	ParseJsonFromFile(CurrentJob);
	//delete []pFileName;
	//pFileName = NULL;
	if(wParam == 0)
	{
		MessageBox(_T("载入作业成功！"),_T("提示"), MB_OKCANCEL );	 
	} 
	PrepareCurveInfo();
	return 0;
}

int CDMonitorDlg::ParseJsonFromFile(CString filename)  
{  
	ClearWorkInfoList();
	//CFile fAddressImport;
	//CFileException eFileException;
	//if (!fAddressImport.Open (filename, CFile::modeRead, &eFileException))
	//{
	//	return 0xFF;
	//}
	char * pFileName = theApp.FromUNICODEToANSI(filename);
	
	//int len = fAddressImport.GetLength();
	//char * pFile = new char(len);
	//memset(pFile,0,len);
	//fAddressImport.Read(pFile,len);
	//fAddressImport.Close();
	// 解析json用Json::Reader   
	Json::Reader reader;  
	// Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array...   
	Json::Value root;         

	std::ifstream is;  
	is.open (filename, std::ios::binary);  

	if (reader.parse(is, root))  
	{  
		std::string code;  
		if (!root["arrayCurve"].isNull())  // 访问节点，Access an object value by name, create a null member if it does not exist.   
		{	
			//code = root["uploadid"].asString();  

			// 访问节点，Return the member named key if it exist, defaultValue otherwise.   
			//code = root.get("uploadid", "null").asString();  

			// 得到"files"的数组个数   
			int curve_size = root["arrayCurve"].size();  

			// 遍历数组   
			for(int i = 0; i < curve_size; ++i)  
			{  
				CWorkInfo* plist = new CWorkInfo();
				Json::Value val_Label = root["arrayCurve"][i]["Label"];  
				plist->strSignal = val_Label.asCString();
				Json::Value val_Unit = root["arrayCurve"][i]["Unit"]; 
				plist->strUnit = val_Unit.asCString();
				Json::Value val_Filter = root["arrayCurve"][i]["Filter"]; 
				plist->strFilter = val_Filter.asCString();
				Json::Value val_Title = root["arrayCurve"][i]["Title"]; 
				plist->strTitle = val_Title.asCString();
				Json::Value val_MIN = root["arrayCurve"][i]["MIN"]; 
				double min = val_MIN.asInt();
				plist->leftLimit = val_MIN.asInt();
				Json::Value val_MAX = root["arrayCurve"][i]["MAX"]; 
				double max = val_MAX.asInt();
				plist->rightLimit = val_MAX.asInt();
				Json::Value val_COLOR_R = root["arrayCurve"][i]["COLOR_R"]; 
				BYTE cR = val_COLOR_R.asUInt();
				Json::Value val_COLOR_G = root["arrayCurve"][i]["COLOR_G"]; 
				BYTE cG = val_COLOR_G.asUInt();
				Json::Value val_COLOR_B = root["arrayCurve"][i]["COLOR_B"]; 
				BYTE cB = val_COLOR_B.asUInt();
				plist->curveColor = RGB(cR,cG,cB);
				Json::Value val_TRACK = root["arrayCurve"][i]["TRACK"]; 
				plist->trackNum = val_TRACK.asInt();
				Json::Value val_LINETYPE = root["arrayCurve"][i]["LINETYPE"]; 
				plist->lineType = val_LINETYPE.asInt();
				Json::Value val_LINEWIDTH = root["arrayCurve"][i]["LINEWIDTH"]; 
				plist->lineWidth = val_LINEWIDTH.asInt();
				//plist->curveColor = curveSelectColor;
				theApp.workInfoList.AddTail(plist);
			}
		}
	}  
	is.close();  
	delete []pFileName;
	pFileName = NULL;
	//delete []pFile;
	//pFile = NULL;
	return 0;  
}  

LRESULT CDMonitorDlg::OnCommReceive(WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
#if 0
    //TRACE(_T("Communication Receive!\n"));
	TRACE0("RX = ");
	//TRACE(_T(" %02X\n"),wParam);

    for(WORD cont = 0; cont < wParam ; cont++)
    {
        //TRACE(_T(" %02X"),theApp.commLayer.m_ReceiveBuff[cont]);
    }
	TRACE0("\n");
#endif
#endif
	CString str;
	totalReceiveByte += wParam;
	if(totalReceiveByte>fileLimit)
	{
		fileNum++;
		closeDataFile(sGetFileName);
		sGetFilePreName = sGetFileName;
		int pos = sGetFilePreName.ReverseFind(_T('.'));
		int length = sGetFilePreName.GetLength();
		CString strPre = sGetFilePreName.Left(pos);
		CString strSub = sGetFilePreName.Right(length - pos);
		CString strAdd;
		strAdd.Format(_T("_%d"),fileNum);
		sGetFileName = strPre + strAdd + strSub;
		openDataFile(sGetFileName);
	}
#if 0
	if(totalReceiveByte < 1024)
	{
		str.Format(_T("已接收数据: %d B"),totalReceiveByte);
	}
	else if(totalReceiveByte < 1024*1024)
	{
		str.Format(_T("已接收数据:%2f KB"),(float)totalReceiveByte/1024);
	}
	else
	{
		str.Format(_T("已接收数据:%2f MB"),(float)totalReceiveByte/(1024*1024));
	}
#endif
	writeDataFile(&theApp.commLayer.m_ReceiveBuff[0],wParam);
	ParseData(&theApp.commLayer.m_ReceiveBuff[0],wParam);
    return 0;
}
void CDMonitorDlg::writeDataFile(BYTE* tmp, WPARAM wParam)  
{     
    if(fp != NULL)
	{ 
		fseek(fp,0L,2);
		{
			unsigned int nSize = fwrite( &tmp[0], wParam, 1, fp);  
		}
    }   
}  

void CDMonitorDlg::AddPanelListView( )
{
	listView.SetRedraw(FALSE);
	listView.DeleteAllItems();
	for(int i=0;i<str_unitlist.size();i++)
	{
		string s =str_unitlist.at(i).c_str();
		CString str(s.c_str()); 
		listView.InsertItem(i,str);
	}
	listView.SetRedraw(TRUE);
	listView.Invalidate();
	listView.UpdateWindow();
}
void CDMonitorDlg::UpdatePanelListView(CPetroData* pPData)
{
	CString strMag;
	for(int i=0;i<pPData->pData.size();i++)
	{
		for(int j =0;j<str_unitlist.size();j++)
		{
			CString str(str_unitlist.at(j).c_str());
			if(!str.Compare(pPData->pData.at(i).strTag))
			{
				if(!str.Compare(_T("DEPT")))
				{
					//OutputDebugString(_T("OnTimer dept = ")+ pPData->pData.at(i).strData +" \r\n");
					Edit01.SetWindowText(pPData->pData.at(i).strData);
				}
				if(!str.Compare(_T("MAG")))
				{
					if(pPData->pData.at(i).subIndex == 0)
					{
						strMag += pPData->pData.at(i).strData;
						strMag += _T(",");
					}
					else if(pPData->pData.at(i).subIndex == 1)
					{
						strMag += pPData->pData.at(i).strData;
						strMag += _T(",");
					}
					else
					{
						strMag += pPData->pData.at(i).strData;
						listView.SetItemText(j,1,strMag);
						listView.SetItemText(j,2,pPData->pData.at(i).strUnit);
					}
				}
				else
				{
					listView.SetItemText(j,1,pPData->pData.at(i).strData);
					listView.SetItemText(j,2,pPData->pData.at(i).strUnit);
				}
				break;
			}
		}
	}
	listView.SetRedraw(TRUE);
	listView.Invalidate();
	listView.UpdateWindow();
}

void CDMonitorDlg::OnMenuMeasuredown()
{
	// TODO: 在此添加命令处理程序代码
	m_bDirectDown = true;
	CMenu* pSubMenu = NULL;
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	{
		pSubMenu = pMainMenu->GetSubMenu(3);
		if (pSubMenu && pSubMenu->GetMenuItemID(0) == ID_MENU_MEASUREUP)
		{
			pSubMenu->CheckMenuItem(ID_MENU_MEASUREUP,m_bDirectDown?MF_UNCHECKED:MF_CHECKED); 
		}
		if (pSubMenu && pSubMenu->GetMenuItemID(1) == ID_MENU_MEASUREDOWN)
		{
			pSubMenu->CheckMenuItem(ID_MENU_MEASUREDOWN,m_bDirectDown?MF_CHECKED:MF_UNCHECKED); 
		}
	}
}


void CDMonitorDlg::OnUpdateMenuMeasuredown(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CDMonitorDlg::OnMenuMeasureup()
{
	// TODO: 在此添加命令处理程序代码
	m_bDirectDown = false;
	CMenu* pSubMenu = NULL;
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	{
		pSubMenu = pMainMenu->GetSubMenu(3);
		if (pSubMenu && pSubMenu->GetMenuItemID(0) == ID_MENU_MEASUREUP)
		{
			pSubMenu->CheckMenuItem(ID_MENU_MEASUREUP,m_bDirectDown?MF_UNCHECKED:MF_CHECKED); 
		}
		if (pSubMenu && pSubMenu->GetMenuItemID(1) == ID_MENU_MEASUREDOWN)
		{
			pSubMenu->CheckMenuItem(ID_MENU_MEASUREDOWN,m_bDirectDown?MF_CHECKED:MF_UNCHECKED); 
		}
	}
}


void CDMonitorDlg::OnUpdateMenuMeasureup(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


BOOL CDMonitorDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CDMonitorDlg::OnMenuInstrument()
{
	// TODO: 在此添加命令处理程序代码
	
}


void CDMonitorDlg::OnMenuJob()
{
	// TODO: 在此添加命令处理程序代码
	parameterFlag=0;
	OnMyMenuJob(parameterFlag);
}

void CDMonitorDlg::OnMyMenuJob(int myparameterFlag)
{
	// TODO: 在此添加命令处理程序代码
	CJobDlg m_jDlg;
	m_jDlg.fatherHwnd = (AfxGetMainWnd()->GetSafeHwnd());//获取HWND，赋值给通信层进行消息传递
	m_jDlg.m_Path=theApp.ToolPath;
	m_jDlg.receiveFlag = myparameterFlag;
	m_jDlg.m_Title=_T("力擎作业/仪器管理");
	m_jDlg.m_TreeTitle=_T("仪器列表");
	m_jDlg.DoModal();
}

void CDMonitorDlg::OnMenuTool()
{
	// TODO: 在此添加命令处理程序代码
	CJobDlg m_jDlg;
	m_jDlg.fatherHwnd = (AfxGetMainWnd()->GetSafeHwnd());//获取HWND，赋值给通信层进行消息传递
	m_jDlg.m_Path=theApp.ToolPath;
	m_jDlg.m_Title=_T("力擎作业/仪器管理");
	m_jDlg.m_TreeTitle=_T("仪器列表");
	m_jDlg.DoModal();
}


void CDMonitorDlg::OnMenuNewjob()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(FALSE,_T(""),_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("tools files(*.tools)|*.tools|tool files(*.mdb)|*.mdb|All files(*.*)|*.*|"));//构造保存文件对话框
	dlg.m_ofn.lpstrInitialDir=theApp.JobPath;
    if(dlg.DoModal()==IDOK)//显示保存文件对话框
	{
		CJobEditDlg m_jeDlg;
		m_jeDlg.m_jobName=dlg.GetPathName();//获取文件路径名称
		m_jeDlg.m_Open=FALSE;
		if(m_jeDlg.DoModal()==IDOK){
		m_treeCtrl.ModifyStyle(0,TVS_HASBUTTONS   |   TVS_LINESATROOT   |   TVS_HASLINES);	
		m_treeCtrl.DisplayTree (theApp.JobPath,TRUE);
		}
	}
}


void CDMonitorDlg::OnMenuJobload()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CJobDlg m_jDlg;
	m_jDlg.fatherHwnd = (AfxGetMainWnd()->GetSafeHwnd());//获取HWND，赋值给通信层进行消息传递
	m_jDlg.m_Path=theApp.ToolPath;
	m_jDlg.m_Title=_T("力擎作业/仪器管理");
	m_jDlg.m_TreeTitle=_T("仪器列表");
	m_jDlg.DoModal();
}


void CDMonitorDlg::OnTestMode1()
{
	// TODO: 在此添加命令处理程序代码
	//testDlg.DoModal();
	if (testDlg.DoModal () == IDOK)
	{
		PrepareCurveInfo();
	}
}

void CDMonitorDlg::PrepareCurveInfo()
{
	CreateCurveFile(theApp.strCurveFile);
	CreateUnitFile(theApp.strUnitsFile);
	POSITION pos = theApp.workInfoList.GetHeadPosition();
	str_unitlist.clear();
	while(pos)
	{
		CWorkInfo* p = theApp.workInfoList.GetNext(pos);
		if(p)
		{
			CT2CA pszConvertedAnsiString (p->strTitle);   
			// construct a std::string using the LPCSTR input   
			std::string strStd (pszConvertedAnsiString);  
			str_unitlist.push_back(strStd);
		}
	}
	bLoadAssignment = true;
}
void CDMonitorDlg::ClearWorkInfoList()
{
	CWorkInfo* pCurrent = NULL;
	while(theApp.workInfoList.IsEmpty()==false)
	{
		pCurrent=theApp.workInfoList.RemoveHead();
		delete pCurrent;
		pCurrent=NULL;
	}
}
void CDMonitorDlg::ClearWorkUnitList()
{
	CWorkUnit* pCurrent = NULL;
	while(theApp.workUnitList.IsEmpty()==false)
	{
		pCurrent=theApp.workUnitList.RemoveHead();
		delete pCurrent;
		pCurrent=NULL;
	}
}

int CDMonitorDlg::CreateUnitFile(CString strFile)
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "yes" );
	doc.LinkEndChild( decl ); 
	TiXmlElement * element = new TiXmlElement( "Units" );
	////
	POSITION pos = theApp.workUnitList.GetHeadPosition();
	while(pos)
	{
		CWorkUnit* plist = theApp.workUnitList.GetNext(pos);
		LinkUnitElementeFuns(element,plist);	
	}

	doc.LinkEndChild( element );
	////
	char * pFileName = theApp.FromUNICODEToANSI(strFile);
	doc.SaveFile(pFileName);

	delete []pFileName;
	pFileName = NULL;
	return 0;
}
void CDMonitorDlg::LinkUnitElementeFuns(TiXmlElement * element,CWorkUnit* plist)
{
	TiXmlElement* msgs = new TiXmlElement( "Unit" ); 
	element->LinkEndChild( msgs );
	TiXmlElement* msg = new TiXmlElement( "Label" ); 
	////********/////transfer//////********//////
	const int maxBufferSize = 64;
	unsigned short UnicodeStr[maxBufferSize];
	unsigned short utf8StrLen;
	DWORD dwLength;//转换后的UTF－8编码的长度in BYTEs
	char utf8Str[64];
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	short UnicodeStrLen=2*plist->strUnit.GetLength();
	memcpy(UnicodeStr,plist->strUnit,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 
}

int CDMonitorDlg::CreateCurveFile(CString strFile)
{

	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "yes" );
	doc.LinkEndChild( decl ); 
	TiXmlElement * element = new TiXmlElement( "Works" );
	POSITION pos = theApp.workInfoList.GetHeadPosition();
	while(pos)
	{
		CWorkInfo* plist = theApp.workInfoList.GetNext(pos);
		LinkElementeFuns(element,plist);	
	}
	doc.LinkEndChild( element );
	////
	char * pFileName = theApp.FromUNICODEToANSI(strFile);
	doc.SaveFile(pFileName);

	delete []pFileName;
	pFileName = NULL;
	return 0;
}

void CDMonitorDlg::LinkElementeFuns(TiXmlElement * element,CWorkInfo* plist)
{
	TiXmlElement* msgs = new TiXmlElement( "WorkInfo" ); 
	element->LinkEndChild( msgs );
	TiXmlElement* msg = new TiXmlElement( "Signal" ); 
	CString str = plist->strSignal;
	////********/////transfer//////********//////
	const int maxBufferSize = 64;
	unsigned short UnicodeStr[maxBufferSize];
	unsigned short utf8StrLen;
	DWORD dwLength;//转换后的UTF－8编码的长度in BYTEs
	char utf8Str[64];
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	short UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "Title" ); 
	str = plist->strTitle;
	////********/////transfer//////********//////

	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "Unit" ); 
	str = plist->strUnit;
	////********/////transfer//////********//////

	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "LeftLimit" ); 
	str.Format(_T("%d"),plist->leftLimit);
	////********/////transfer//////********//////
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "RightLimit" ); 
	str.Format(_T("%d"),plist->rightLimit);
	////********/////transfer//////********//////
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "LineWidth" ); 
	str.Format(_T("%d"),plist->lineWidth);
	////********/////transfer//////********//////
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "LineType" ); 
	str.Format(_T("%d"),plist->lineType);
	////********/////transfer//////********//////
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

	msg = new TiXmlElement( "Color" ); 
	str.Format(_T("%d"),plist->curveColor);
	////********/////transfer//////********//////
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 

}

void CDMonitorDlg::ParseWorkInfoData()
{
	WCHAR pwBuffer[100];
	CString str;
	ClearWorkInfoList();
	string fileXml = theApp.IniFilePath + "workinfo.xml";
	TiXmlDocument doc(fileXml.c_str());
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		if ( !doc.Parse( fileXml.c_str() ) )
		{
			cout << doc.ErrorDesc() << endl;
		}
		//step 1 : Get the RootElement
		TiXmlElement *root = doc.RootElement();
		for ( TiXmlNode *child = root->FirstChild(); child; child = child->NextSibling() )
		{
			if ( ( child->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( child->Value(), "WorkInfo" ) ) )
			{
				CWorkInfo* plist = new CWorkInfo();
				for ( TiXmlNode *subchild = child->FirstChild(); subchild; subchild = subchild->NextSibling() )
				{
					if ( ( subchild->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( subchild->Value(), "Signal" ) ) )
					{
						TiXmlNode* subsubchild = subchild->FirstChild();
						memset(pwBuffer,0,sizeof(pwBuffer));
						const char* strValue = subsubchild->Value();
						int len = strlen(strValue);
						theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
						str = pwBuffer;
						plist->strSignal = str;
					}
					else if ( ( subchild->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( subchild->Value(), "Title" ) ) )
					{
						TiXmlNode* subsubchild = subchild->FirstChild();
						memset(pwBuffer,0,sizeof(pwBuffer));
						const char* strValue = subsubchild->Value();
						int len = strlen(strValue);
						theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
						str = pwBuffer;
						plist->strTitle = str;
					}
					else if ( ( subchild->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( subchild->Value(), "Unit" ) ) )
					{
						TiXmlNode* subsubchild = subchild->FirstChild();
						memset(pwBuffer,0,sizeof(pwBuffer));
						const char* strValue = subsubchild->Value();
						int len = strlen(strValue);
						theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
						str = pwBuffer;
						plist->strUnit = str;
					}
					else if ( ( subchild->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( subchild->Value(), "LeftLimit" ) ) )
					{
						TiXmlNode* subsubchild = subchild->FirstChild();
						memset(pwBuffer,0,sizeof(pwBuffer));
						const char* strValue = subsubchild->Value();
						int len = strlen(strValue);
						theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
						str = pwBuffer;
						plist->leftLimit = _tstoi(pwBuffer);;
					}
					else if ( ( subchild->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( subchild->Value(), "RightLimit" ) ) )
					{
						TiXmlNode* subsubchild = subchild->FirstChild();
						memset(pwBuffer,0,sizeof(pwBuffer));
						const char* strValue = subsubchild->Value();
						int len = strlen(strValue);
						theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
						str = pwBuffer;
						plist->rightLimit = _tstoi(pwBuffer);;
					}
					else if ( ( subchild->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( subchild->Value(), "Color" ) ) )
					{
						TiXmlNode* subsubchild = subchild->FirstChild();
						memset(pwBuffer,0,sizeof(pwBuffer));
						const char* strValue = subsubchild->Value();
						int len = strlen(strValue);
						theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
						str = pwBuffer;
						plist->curveColor = _tstoi(pwBuffer);;
					}
				}
				theApp.workInfoList.AddTail(plist);
			}
		}
	}
}
bool CDMonitorDlg::ParseElementeFuns(TiXmlNode * element,char* str)
{
	WCHAR pwBuffer[100];
	if ( ( element->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( element->Value(), str ) ) )
	{
		CWorkUnit* pWorkUnit = new CWorkUnit();
		TiXmlNode* subsubchild = element->FirstChild();
		memset(pwBuffer,0,sizeof(pwBuffer));
		const char* strValue = subsubchild->Value();
		int len = strlen(strValue);
		theApp.FromUTF8ToUnicode((BYTE*)strValue,  len, (WORD*)pwBuffer, sizeof(pwBuffer));
		CString str = pwBuffer;
		pWorkUnit->strUnit = str;
		theApp.workUnitList.AddTail(pWorkUnit);
		return true;
	}
	return false;
}
void CDMonitorDlg::initDataPart(DATA_PART &dataPart)
{
	dataPart.bAssign = false;
	dataPart.iData = 0;
	dataPart.iDeptData = 0;
	dataPart.strData = _T("");
	dataPart.strTag = _T("");
	dataPart.strUnit = _T("");
	dataPart.subIndex = 0;
}
void CDMonitorDlg::ClearDataTempa()
{
	CDataTemp* pCurrent = NULL;
	while(oldArray.IsEmpty()==false)
	{
		pCurrent = oldArray.RemoveHead();
		delete pCurrent;
		pCurrent=NULL;
	}
}
void CDMonitorDlg::ParseWorkUnitData()
{
	WCHAR pwBuffer[100];
	
	ClearWorkUnitList();
	string fileXml = theApp.IniFilePath + "Units.xml";
	TiXmlDocument doc(fileXml.c_str());
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		if ( !doc.Parse( fileXml.c_str() ) )
		{
			cout << doc.ErrorDesc() << endl;
		}
		//step 1 : Get the RootElement
		TiXmlElement *root = doc.RootElement();
		for ( TiXmlNode *child = root->FirstChild(); child; child = child->NextSibling() )
		{
			if ( ( child->Type() == TiXmlNode::TINYXML_ELEMENT ) && ( !strcmp( child->Value(), "Unit" ) ) )
			{
				for ( TiXmlNode *subchild = child->FirstChild(); subchild; subchild = subchild->NextSibling() )
				{
					if ( ParseElementeFuns( subchild, "Label" ))
					{
						continue;
					}
#if 0
					if ( ParseElementeFuns( subchild, "mV" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "rm" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "CCL" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mag" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "GAPI" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "CPS" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "us/m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "cm" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mm" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "uS" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mS" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "S" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "MΩ" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "kΩ" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Ω" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Ω.m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "S/m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mS/m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m/h" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Kg" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Kn" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "N" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "℃" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "℃/m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "kg/m^3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "g/cm^3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "km" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "km^3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m^3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "dm^3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m/s^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mm/s^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "rad" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mrad" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "urad" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "°" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "km^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "ha" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "dm^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mm^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "kg/s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m^3/s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m^3/min" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m^3/d" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "L/s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Std.m3/m3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "t" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Mg/m^3" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "pu" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "J" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Mev" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "MW" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "KW" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "W" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Pa" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "kPa" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "MPa" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "ATM" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "PSI" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Bq" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "r/s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "min" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "h" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "d" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "a" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "m/s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "Pa.s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "mPa.s" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "N.s/m^2" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "%" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "NAPI" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "inch" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "API" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "V" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "度" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "uS/m" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "ppm" ))
					{
						continue;
					}
					else if ( ParseElementeFuns( subchild, "I" ))
					{
						continue;
					}
#endif
				}
			}
		}
	}
}



void CDMonitorDlg::OnInstruction()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwAttr = 0;
	TCHAR szModPath[_MAX_PATH];
	GetModuleFileName(theApp.m_hInstance, szModPath, _MAX_PATH);
    CString strName = _T("help.pdf");
    CString PdfHelpFilePath = szModPath;
	PdfHelpFilePath = PdfHelpFilePath.Left(PdfHelpFilePath.ReverseFind('\\'));
	PdfHelpFilePath = PdfHelpFilePath + _T("\\Help\\");
	dwAttr=GetFileAttributes(PdfHelpFilePath);
	//若文件夹不存在，创建文件夹
	if(dwAttr==0xFFFFFFFF)
	{
		MessageBox(_T("文件夹不存在\n"),_T("提示"),MB_OK); 
		return;
	}
	CString DocHelpFilePath = PdfHelpFilePath;
	PdfHelpFilePath += strName;
	if (ShellExecute (NULL,_T("open"),PdfHelpFilePath,NULL,NULL,SW_SHOW) <(HANDLE) 32) 
	{
		strName = _T("help.doc");
		DocHelpFilePath += strName;
		if (ShellExecute (NULL,_T("open"),DocHelpFilePath,NULL,NULL,SW_SHOW) <(HANDLE) 32) 
		{
			CString str;
			str.Format(_T("无法打开%s文件，\n"),DocHelpFilePath);
			MessageBox(str,_T("提示"),MB_OK); 
		}
	}
}
