#pragma once


// CDMonitorView 对话框

class CDMonitorView : public CDialogEx
{
	DECLARE_DYNAMIC(CDMonitorView)

public:
	CDMonitorView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDMonitorView();

// 对话框数据
	enum { IDD = IDD_DMONITERVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
