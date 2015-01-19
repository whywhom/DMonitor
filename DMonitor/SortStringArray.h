#pragma once
#include "afxcoll.h"
class CSortStringArray :
	public CStringArray//用于CDirTreeCtrl控件元素的排序
{
public:
	CSortStringArray(void);
	~CSortStringArray(void);
	void Sort();
private: 
	BOOL CompareAndSwap( int pos );
};

