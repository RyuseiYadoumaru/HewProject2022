#pragma once
#include "ydmEngine.h"
#include "MoveInfo.h"
/****	移動情報リスト	****/
class MoveInfoList
{
public:
	void Add(MoveInfo* in_MoveInfo);
	void Clear();
	bool Empty();

	bool MoveFront();
	bool ResetAll();

public:
	vector<MoveInfo*> m_List;

};

