#pragma once
class CDataTemp
{
public:
	CDataTemp(void);
	~CDataTemp(void);
	void init();
	double dy;
	double dx;
	CString strDx;//���������ݵ��ַ���
	CString strTag;//���Ա����ı�ʾ��DEPT,TEMP��
	bool bAssign;
	int subIndex;
};

