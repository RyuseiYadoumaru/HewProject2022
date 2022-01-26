#pragma once
#include "ydmEngine.h"
#include "BlockParticleManager.h"
#include "MoveInfoList.h"

class TileColumn;
class LandTile;
/****	É}ÉbÉvà⁄ìÆä«óù	****/
class MoveManager
{
public:
	static int NowFinFrontMoveColumn;
	static int NowFinBackMoveColumn;

public:
	MoveManager();
	bool Init(LandTile* in_StandardTile);
	bool Update();

public:
	string& GetLandObjectName();
	int GetLandObjectID() const;

private:
	MoveInfoList Front;
	MoveInfoList Back;

	LandTile* m_StandardTile;

private:
	bool SetMoveList();
	bool Move();
	bool MoveResetBefore();

	bool SetMagicParticle();
	void SetMoveParticle();
	void SetResetParticle();

private:
	int FrontCounter;
	int BackCounter;
	BlockEffectColor EffectColor;
	bool isMagicFin;
	MoveInfoList FrontParticle;
	MoveInfoList BackParticle;

	vector<int> ResetColumnNum;
	bool isResetFin = false;


private:
	MoveInfoList ResetBeforeList;
	float HitCeilingColumn;
	bool isResetBefore;
	bool isHitCeiling;
	static constexpr unsigned int HitStopFrameCount = 5;
	int SaveHitFrame;

private:
	void SetHitCeilingColumn(float column);
	bool ResetBefore();



private:
	static constexpr TIME m_OneMagicWaitTime = 300.0f;
	TIME m_MoveWaitTime;
	TIME m_Timer;


};

