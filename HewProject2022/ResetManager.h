#pragma once
#include "ydmEngine.h"
#include "ResetInfoList.h"
class TileColumn;
class LandTile;
class Map;

/****	ƒŠƒZƒbƒgˆ—	****/
class ResetManager
{
public:
	ResetManager();
	bool Init();
	bool Update();


private:
	ResetInfoList Reset;


private:
	bool ResetParticle();

private:
	static constexpr TIME m_MaxResetWaitTime = 1000.0f;
	static constexpr int m_ResetMaxColumn = 40;
	TIME m_ResetWaitTime;
	TIME m_Timer;

};

