#pragma once
#include "ydmEngine.h"
#include "MoveInfoList.h"
#include "ResetInfoList.h"

class TileColumn;
class LandTile;
/****	É}ÉbÉvà⁄ìÆä«óù	****/
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

