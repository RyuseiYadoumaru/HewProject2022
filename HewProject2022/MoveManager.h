#pragma once
#include "ydmEngine.h"
#include "MoveParticleManager.h"
#include "MoveInfoList.h"

class TileColumn;
class LandTile;
/****	É}ÉbÉvà⁄ìÆä«óù	****/
class MoveManager
{
public:
	MoveManager();
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
	bool SetMoveList(vector<TileColumn>* in_AllTile);
	bool Move();

private:
	static constexpr TIME m_OneColumnWaitTime = 200.0f;
	TIME m_MoveWaitTime;
	TIME m_Timer;


};

