#include "StdAfx.h"
#include "DataTemp.h"


CDataTemp::CDataTemp(void)
{
	init();
}


CDataTemp::~CDataTemp(void)
{
}

void CDataTemp::init()
{
	dy = 0;
	dx = 0;
	strDx = _T("");//横坐标数据的字符串
	strTag = _T("");//测试变量的标示，DEPT,TEMP等
	bAssign = false;
	subIndex = 0;
}
