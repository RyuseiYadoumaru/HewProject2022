#pragma once
#include "ydmEngine.h"
#include "BlockMagicEffect.h"
#include "BlockMoveEffect.h"
#include "BlockResetEffect.h"
#include "Tile.h"


#define EFFECT_RED true
#define EFFECT_BLUE false
using Create::GameObject;
/****	移動パーティクル	****/
class BlockParticleManager
{
public:
	static void CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color);
	static void CreateMoveEffect(GameObject* Owner, BlockEffectColor in_Color);
	static void CreateResetEffect(GameObject* Owner, BlockEffectColor in_Color);

	static bool DeleteMagicEffect(float in_Id);
	static bool DeleteMoveEffect(float in_Id);
	static bool DeleteResetEffect(float in_Id);

	static void MagicStateFinish(float in_Id);
	static void MoveStateFinish(float in_Id);
	static void ResetStateFinish(float in_Id);

	static bool CheckPlayMoveEffect(float in_Id);

	static bool JudgeRedorBlue(MAPOBJ in_kind);

	static void MagicReset(Tile& in_OldLandTile);

private:
	static map<float, BlockMagicEffect*> m_MagicEffectList;
	static map<float, BlockMoveEffect*> m_MoveEffectList;
	static map<float, BlockResetEffect*> m_ResetEffectList;
	static int Counter;

public:
	void ParticleRender();
	void End();


};

