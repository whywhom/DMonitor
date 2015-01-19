
// DMoniterDlg.h : ͷ�ļ�
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
// CDMonitorDlg �Ի���
class CDMonitorDlg : public CDialogEx
{
// ����
public:
	CDMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DMONITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	HMENU m_hMenu;//�˵�
	CToolBar m_ToolBar;//������
	bool bExiting;//����˳�ʱ�˱�������Ϊture
	bool bLoadAssignment;//�Ƿ��Ѽ�����ҵ
	//bool bOperating;
	CRect rectMain;//����������
	CRect rectView;//��ͼ��������
	CRect rectPanel;//���ݲ�������
	CRect rectScale;//����ͼ������
	CRect rectScrollV;//��ֱ����������
	CRect rectScrollScaleV;//��ֱ����������
	int minMainDialogWidth, minMainDialogHeight;//��������С���ȡ����
	int m_SM_CXFULLSCREEN,m_SM_CYFULLSCREEN;//��ȡ��Ļ�ֱ���

	int processType;//�����������ͣ�0 - �Ӵ��ڻ�õ����ݣ�1 - ���ļ���ȡ������
	BYTE* pData;//�洢�ļ�����
	CTypedPtrList < CPtrList, CPetroData * >petroList;//���ݴ洢����
	bool bConnect;//��־����
	CString sGetFileName;//����򿪵��ļ�·��
	CString sGetFilePreName;//����򿪵��ļ���
	FILE* fp;//ָ��򿪵��ļ�
	CString fileName;//��¼�������ݵ��ļ�
	unsigned long totalReceiveByte;
	unsigned long fileLimit;//�ļ���С���ƣ������Ļ����Զ�������һ���ļ�
	int fileNum;
	CDC   MemDC;          //˫���� ����һ����ʾ�豸����  
	CBitmap   MemBitmap;  //˫���� ����һ��λͼ����  
	CDC   ScaleMemDC;          //˫���� ����һ����ʾ�豸����  
	CBitmap   ScaleMemBitmap;  //˫���� ����һ��λͼ����  
	//why add ��ͼ����
	unsigned long base;//������
	unsigned long bias;//���ƫ����
	long counter;//������

	POSITION pos;//��ǰ��¼λ��
	CPetroData* pPData;//�õ���������
	CPetroData* pOldPData;//����ǰһ�����ݶ���
	CRect rectTotal;

	int			unitPixel;//ÿ�׶�Ӧ����ֵ
	int			unitRatio;//ÿ�׶�Ӧ����ֵ��ϵ��
	int			m_iterator;//��ͼ������
	CRect		m_screenRect;// m_screenRect - view�Ŀɼ���Χ�����Ļ���Ͻ�����
	CRect		m_clientRect;// m_clientRect - view�Ŀɼ���Χ�ͻ���
	CRect		m_totalRect;// m_totalRect - ����Ҫ��������ķ�Χ���������ɼ�
	CRect		m_scaleRect;// m_scaleRect - ScaleView�Ŀɼ���Χ�ͻ���
	CRect		m_totalScaleRect;// m_totalScaleRect - ����Ҫ��������ķ�Χ���������ɼ�

	CRect		m_plot1Rect;// m_plot1Rect - borderspace1
	CRect		m_plot2Rect;// m_plot2Rect - borderspace2
	CRect		m_plot3Rect;// m_plot3Rect - borderspace3

	SIZE sizeTotal;//����Ҫ��������ķ�Χ���������ɼ�

	double		minDepth;//�ɼ���Χ��С���
	double		maxDepth;//�ɼ���Χ������
	double		maxPreDepth;//�ɼ���Χ�ƶ�֮ǰ��������
	double		minDepthLimit;//��ҵ����С���
	double		maxDepthLimit;//��ҵ��������
	bool		m_bAutoScrollY;		// automatic y range scrolling
	bool		m_bDirectDown;		// ���»���
	bool		bScroll;//���Ƶ��ײ���ʼ����ʱ����Ϊtrue
	int			m_drawCount;//ÿ�λ��ƶ��ٸ�����
	int			m_step;//ÿ���ƶ����룬����Ϊ��λ
	bool		bTimer;

	//��ɫ
	COLORREF crViewBackground;//����
	COLORREF crViewCoordinate;
	COLORREF crViewPlot;//������
	COLORREF crViewGraduation;//�̶�
	COLORREF crViewGridColor;// grid line color

	COLORREF colorRed;
	COLORREF colorBlue;
	COLORREF colorGreen;
	COLORREF colorBlack;
	COLORREF colorCyan;//��ɫ������ɫ
	COLORREF* colorArray;

	//��������
	CFont		m_font;
	LOGFONT		m_zoomFont;

	CTestDlg testDlg;
	std::vector<std::string>   str_unitlist;
	CTypedPtrList < CPtrList, CDataTemp * >oldArray;//���ݴ洢����

	CPen* pPen;
public:
	void GetRectParam(CRect rectMain);
	void OnInitWidget();
	void ClearPetroData();
	void InitArrayData();
	void InitOldArrayData();
	void ParseData(BYTE* tmp, WPARAM wParam);//������������
	void writeDataFile(BYTE* tmp, WPARAM wParam);
	int CheckString( std::string str );
	void closeDataFile(CString strFile);
	void openDataFile(CString strFile);
	void DrawData(CDC* pDC);
	void DrawScale(CDC* pDC);
	void DrawBasic(CDC * pDC);//��ͼ������ʼ
	void DrawRealtimeBasic(CDC * pDC);//��ͼ������ʼ
	void DrawFileDataBasic(CDC * pDC);
	void DrawGrid(CDC * pDC);//���ƺ�����������
	void DrawRealtimeGrid(CDC * pDC);//���ƺ�����������
	void DrawFileDataGrid(CDC * pDC);
	void DrawPlot(CDC* pDC);//������������
	void DrawRealtimePlot(CDC* pDC);//������������
	void DrawFileDataPlot(CDC * pDC);
	void DrawRealtimeCurve(CDC* pDC , double upDepth, double DownDepth);//���Ʋ������
	void DrawFileDataCurve(CDC* pDC , double upDepth, double DownDepth);//���Ʋ������

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
// ʵ��
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
	// ���ɵ���Ϣӳ�亯��
	void OnMyMenuJob(int myparameterFlag);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// ��ͼ����ֱ������
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
	afx_msg LRESULT OnCommReceive(WPARAM wParam, LPARAM lParam);//���ն˿���Ϣ
	afx_msg LRESULT OnJobloadReceive(WPARAM wParam, LPARAM lParam);//���ռ�����ҵ��Ϣ
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
