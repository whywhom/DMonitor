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
	strDx = _T("");//���������ݵ��ַ���
	strTag = _T("");//���Ա����ı�ʾ��DEPT,TEMP��
	bAssign = false;
	subIndex = 0;
}
