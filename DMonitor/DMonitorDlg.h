
// DMoniterDlg.h : 头文件
//

#pragma once

using namespace std;

#include "afxwin.h"
#include "PublicInterface.h"
#include "CommLayer.h"
#include "PetroData.h"
#include <string>
#include <queue>
#include <algorithm>
#include <numeric>
#include "dirtreectrl.h"
#include "TestDlg.h"
#include "tinyxml.h"
#include "DataTemp.h"
// CDMonitorDlg 对话框
class CDMonitorDlg : public CDialogEx
{
// 构造
public:
	CDMonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DMONITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	HMENU m_hMenu;//菜单
	CToolBar m_ToolBar;//工具栏
	bool bExiting;//点击退出时此变量设置为ture
	bool bLoadAssignment;//是否已加载作业
	//bool bOperating;
	CRect rectMain;//主界面区域
	CRect rectView;//绘图界面区域
	CRect rectPanel;//数据参数区域
	CRect rectScale;//比例图标区域
	CRect rectScrollV;//垂直滚动条区域
	CRect rectScrollScaleV;//垂直滚动条区域
	int minMainDialogWidth, minMainDialogHeight;//主界面最小长度、宽度
	int m_SM_CXFULLSCREEN,m_SM_CYFULLSCREEN;//获取屏幕分辨率

	int processType;//处理数据类型：0 - 从串口获得的数据，1 - 从文件获取的数据
	BYTE* pData;//存储文件数据
	CTypedPtrList < CPtrList, CPetroData * >petroList;//数据存储链表
	bool bConnect;//标志连接
	CString sGetFileName;//保存打开的文件路径
	CString sGetFilePreName;//保存打开的文件名
	FILE* fp;//指向打开的文件
	CString fileName;//记录串口数据的文件
	unsigned long totalReceiveByte;
	unsigned long fileLimit;//文件大小限制，超过的话则自动生成下一个文件
	int fileNum;
	CDC   MemDC;          //双缓冲 定义一个显示设备对象  
	CBitmap   MemBitmap;  //双缓冲 定义一个位图对象  
	CDC   ScaleMemDC;          //双缓冲 定义一个显示设备对象  
	CBitmap   ScaleMemBitmap;  //双缓冲 定义一个位图对象  
	//why add 绘图变量
	unsigned long base;//深度起点
	unsigned long bias;//深度偏移量
	long counter;//计数器

	POSITION pos;//当前记录位置
	CPetroData* pPData;//得到队列数据
	CPetroData* pOldPData;//保存前一个数据队列
	CRect rectTotal;

	int			unitPixel;//每米对应像素值
	int			unitRatio;//每米对应像素值的系数
	int			m_iterator;//绘图迭代数
	CRect		m_screenRect;// m_screenRect - view的可见范围相对屏幕左上角坐标
	CRect		m_clientRect;// m_clientRect - view的可见范围客户区
	CRect		m_totalRect;// m_totalRect - 整个要绘制区域的范围，包括不可见
	CRect		m_scaleRect;// m_scaleRect - ScaleView的可见范围客户区
	CRect		m_totalScaleRect;// m_totalScaleRect - 整个要绘制区域的范围，包括不可见

	CRect		m_plot1Rect;// m_plot1Rect - borderspace1
	CRect		m_plot2Rect;// m_plot2Rect - borderspace2
	CRect		m_plot3Rect;// m_plot3Rect - borderspace3

	SIZE sizeTotal;//整个要绘制区域的范围，包括不可见

	double		minDepth;//可见范围最小深度
	double		maxDepth;//可见范围最大深度
	double		maxPreDepth;//可见范围移动之前的最大深度
	double		minDepthLimit;//作业中最小深度
	double		maxDepthLimit;//作业中最大深度
	bool		m_bAutoScrollY;		// automatic y range scrolling
	bool		m_bDirectDown;		// 向下绘制
	bool		bScroll;//绘制到底部开始滚动时设置为true
	int			m_drawCount;//每次绘制多少个数据
	int			m_step;//每次移动距离，以米为单位
	bool		bTimer;

	//颜色
	COLORREF crViewBackground;//背景
	COLORREF crViewCoordinate;
	COLORREF crViewPlot;//坐标线
	COLORREF crViewGraduation;//刻度
	COLORREF crViewGridColor;// grid line color

	COLORREF colorRed;
	COLORREF colorBlue;
	COLORREF colorGreen;
	COLORREF colorBlack;
	COLORREF colorCyan;//青色，蓝绿色
	COLORREF* colorArray;

	//字体设置
	CFont		m_font;
	LOGFONT		m_zoomFont;

	CTestDlg testDlg;
	std::vector<std::string>   str_unitlist;
	CTypedPtrList < CPtrList, CDataTemp * >oldArray;//数据存储链表

	CPen* pPen;
public:
	void GetRectParam(CRect rectMain);
	void OnInitWidget();
	void ClearPetroData();
	void InitArrayData();
	void InitOldArrayData();
	void ParseData(BYTE* tmp, WPARAM wParam);//解析串口数据
	void writeDataFile(BYTE* tmp, WPARAM wParam);
	int CheckString( std::string str );
	void closeDataFile(CString strFile);
	void openDataFile(CString strFile);
	void DrawData(CDC* pDC);
	void DrawScale(CDC* pDC);
	void DrawBasic(CDC * pDC);//绘图函数初始
	void DrawRealtimeBasic(CDC * pDC);//绘图函数初始
	void DrawFileDataBasic(CDC * pDC);
	void DrawGrid(CDC * pDC);//绘制横纵坐标网格
	void DrawRealtimeGrid(CDC * pDC);//绘制横纵坐标网格
	void DrawFileDataGrid(CDC * pDC);
	void DrawPlot(CDC* pDC);//绘制坐标数据
	void DrawRealtimePlot(CDC* pDC);//绘制坐标数据
	void DrawFileDataPlot(CDC * pDC);
	void DrawRealtimeCurve(CDC* pDC , double upDepth, double DownDepth);//绘制测绘数据
	void DrawFileDataCurve(CDC* pDC , double upDepth, double DownDepth);//绘制测绘数据

	void PrepareDraw();
	void GetMaxMinData();
	unsigned long GetMinData(DATA_PART tmp,unsigned long m);

	void StartTimer();
	void StopTimer();
	void CalculateParam();

	void DrawParamData(CDC* pDC ,CPetroData* pPData);

	void AddPanelListView( );
	void UpdatePanelListView(CPetroData* pPData);
	void pushToQueue(CPetroData* pPData);
	void SetRealtimeDataLimit();
	void InitColorVariable();
	void ParseWorkInfoData();
	void ParseWorkUnitData();
	void PrepareCurveInfo();
	void ClearWorkInfoList();
	void ClearWorkUnitList();
	int CreateCurveFile(CString strFile);
	bool ParseElementeFuns(TiXmlNode * element,char* str);
	int CreateUnitFile(CString strFile);
	void LinkUnitElementeFuns(TiXmlElement * element,CWorkUnit* plist);
	void LinkElementeFuns(TiXmlElement * element,CWorkInfo* plist);
	void initDataPart(DATA_PART &dataPart);
	void ClearDataTempa();
	void SetScaleScroll();
	int ParseJsonFromFile(CString filename);
// 实现
protected:
	HICON m_hIcon;
	CStatic cs01;
	CString value01;
	CStatic cs02;
	CString value02;
	CStatic cs03;
	CString value03;
	CStatic cs04;
	CString value04;
	CEdit Edit01;
	CString strEdit01;
	CEdit Edit02;
	CString strEdit02;
	CEdit Edit03;
	CString strEdit03;
	CEdit Edit04;
	CString strEdit04;
	CListCtrl listView;
	CDirTreeCtrl m_treeCtrl;
	int parameterFlag;//send flag to jobdlg for some action, 0-nothing;1-new job
	int scaleScrollPos;
	// 生成的消息映射函数
	void OnMyMenuJob(int myparameterFlag);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// 绘图区域垂直滚动条
	CScrollBar mScrollV;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	afx_msg void OnMenuConn();
	afx_msg void OnUpdateMenuConn(CCmdUI *pCmdUI);
	afx_msg void OnMenuDisconn();
	afx_msg void OnUpdateMenuDisconn(CCmdUI *pCmdUI);
	afx_msg LRESULT OnCommReceive(WPARAM wParam, LPARAM lParam);//接收端口消息
	afx_msg LRESULT OnJobloadReceive(WPARAM wParam, LPARAM lParam);//接收加载作业消息
	afx_msg void OnMenuMeasuredown();
	afx_msg void OnUpdateMenuMeasuredown(CCmdUI *pCmdUI);
	afx_msg void OnMenuMeasureup();
	afx_msg void OnUpdateMenuMeasureup(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenuInstrument();
	afx_msg void OnMenuJob();
	afx_msg void OnMenuTool();
	afx_msg void OnMenuNewjob();
	afx_msg void OnMenuJobload();
	afx_msg void OnTestMode1();
	CScrollBar mScrollScaleV;
	afx_msg void OnMenuAbout();
	afx_msg void OnInstruction();
};
