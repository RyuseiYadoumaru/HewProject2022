#pragma once
#include "ydmEngine.h"
#include "ResetInfo.h"
/****	���Z�b�g�ړ���񃊃X�g	****/
class ResetInfoList
{
public:
	void Add(ResetInfo* in_ResetInfo);
	void Clear();
	bool Empty();

public:
	vector<ResetInfo*> m_List;
};

