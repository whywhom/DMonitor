#pragma once
class CDataTemp
{
public:
	CDataTemp(void);
	~CDataTemp(void);
	void init();
	double dy;
	double dx;
	CString strDx;//横坐标数据的字符串
	CString strTag;//测试变量的标示，DEPT,TEMP等
	bool bAssign;
	int subIndex;
};

