#pragma once


// CDMonitorView �Ի���

class CDMonitorView : public CDialogEx
{
	DECLARE_DYNAMIC(CDMonitorView)

public:
	CDMonitorView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDMonitorView();

// �Ի�������
	enum { IDD = IDD_DMONITERVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
