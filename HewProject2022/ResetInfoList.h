#pragma once
#include "ydmEngine.h"
#include "ResetInfo.h"
/****	リセット移動情報リスト	****/
class ResetInfoList
{
public:
	void Add(ResetInfo* in_ResetInfo);
	void Clear();
	bool Empty();
	int Num();

public:
	vector<ResetInfo*> m_List;
};

