#pragma once
#include "ydmEngine.h"
#include "MoveInfoList.h"

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
	MoveInfoList Reset;

	LandTile* m_StandardTile;

private:
	void SetMoveList(vector<TileColumn>* in_AllTile);
	void SetResetList(vector<TileColumn>* in_AllTile);

	bool Move();
	bool ResetMove();

};

