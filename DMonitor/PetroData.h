#pragma once

// CPetroData ÃüÁîÄ¿±ê

using namespace std;

#include"PublicInterface.h"
#include <queue>

class CPetroData : public CObject
{
public:
	CPetroData();
	virtual ~CPetroData();
	std::vector<DATA_PART> pData;
};


