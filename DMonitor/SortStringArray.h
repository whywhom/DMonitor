#pragma once
#include "afxcoll.h"
class CSortStringArray :
	public CStringArray//����CDirTreeCtrl�ؼ�Ԫ�ص�����
{
public:
	CSortStringArray(void);
	~CSortStringArray(void);
	void Sort();
private: 
	BOOL CompareAndSwap( int pos );
};

