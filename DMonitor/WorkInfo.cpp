#include "StdAfx.h"
#include "WorkInfo.h"


CWorkInfo::CWorkInfo(void)
{
	init();
}


CWorkInfo::~CWorkInfo(void)
{
}

void CWorkInfo::init()
{
	strSignal = _T("");//�ź�����
	strTitle = _T("");//�ź���д,����������
	strUnit = _T("");//��λ
	leftLimit = 0;//��߽�
	rightLimit = 100;//�ұ߽�
	trackNum = 0;//�����
	lineWidth = 1;
	lineType = 0;
	curveColor = RGB(255,0,0); //��ɫ
}
