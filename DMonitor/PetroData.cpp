// PetroData.cpp : ʵ���ļ�
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


// CPetroData ��Ա����
#if 0
void CPetroData::InitData()
{
	dept.iData = 0;//���
	dept.strData.Empty();
	dept.bAssign = false;

	temp.iData = 0;//����
	temp.strData.Empty();
	temp.bAssign = false;

	rm.iData = 0;//������
	rm.strData.Empty();
	rm.bAssign = false;

	gr.iData = 0;//������
	gr.strData.Empty();
	gr.bAssign = false;

	mag[0].iData = 0;//��������
	mag[0].strData.Empty();
	mag[0].bAssign = false;

	mag[1].iData = 0;//��������
	mag[1].strData.Empty();
	mag[1].bAssign = false;

	mag[2].iData = 0;//��������
	mag[2].strData.Empty();
	mag[2].bAssign = false;

	ccl.iData = 0;//�Ŷ�λ��
	ccl.strData.Empty();
	ccl.bAssign = false;
}
#endif