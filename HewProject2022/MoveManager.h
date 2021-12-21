#pragma once
#include "ydmEngine.h"
#include "MoveInfoList.h"

class TileColumn;
class LandTile;
/****	マップ移動管理	****/
class MoveManager
{
public:
	bool Init(vector<TileColumn>* in_AllTile, LandTile* in_StandardTile);
	bool Update();

public:
	string& GetLandObjectName();
	int GetLandObjectID() const;

private:
	MoveInfoList Front;
	MoveInfoList Back;

	LandTile* m_StandardTile;

private:
	void SetMoveList(vector<TileColumn>* in_AllTile);

	bool Move();

};

