// PetroData.cpp : 实现文件
//

#include "stdafx.h"
#include "DMonitor.h"
#include "PetroData.h"


// CPetroData

CPetroData::CPetroData()
{
	//InitData();
	pData.clear();
}

CPetroData::~CPetroData()
{
	//InitData();
	pData.clear();
}


// CPetroData 成员函数
#if 0
void CPetroData::InitData()
{
	dept.iData = 0;//深度
	dept.strData.Empty();
	dept.bAssign = false;

	temp.iData = 0;//井温
	temp.strData.Empty();
	temp.bAssign = false;

	rm.iData = 0;//电阻率
	rm.strData.Empty();
	rm.bAssign = false;

	gr.iData = 0;//放射性
	gr.strData.Empty();
	gr.bAssign = false;

	mag[0].iData = 0;//磁三分量
	mag[0].strData.Empty();
	mag[0].bAssign = false;

	mag[1].iData = 0;//磁三分量
	mag[1].strData.Empty();
	mag[1].bAssign = false;

	mag[2].iData = 0;//磁三分量
	mag[2].strData.Empty();
	mag[2].bAssign = false;

	ccl.iData = 0;//磁定位器
	ccl.strData.Empty();
	ccl.bAssign = false;
}
#endif