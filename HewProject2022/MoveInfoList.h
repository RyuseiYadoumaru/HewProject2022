#pragma once
#include "ydmEngine.h"
#include "MoveInfo.h"
/****	�ړ���񃊃X�g	****/
class MoveInfoList
{
public:
	void Add(MoveInfo* in_MoveInfo);
	void Clear();
	bool Empty();
	int Num();

	float FrontColumn();
	bool MoveFront();

public:
	vector<MoveInfo*> m_List;
};

