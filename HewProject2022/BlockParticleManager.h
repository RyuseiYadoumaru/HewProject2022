#pragma once
#include "ydmEngine.h"
#include "BlockMagicEffect.h"
#include "BlockMoveEffect.h"
#include "BlockResetEffect.h"

using Create::GameObject;
/****	移動パーティクル	****/
class BlockParticleManager
{
public:
	static void CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color);
	static void CreateMoveEffect(GameObject* Owner, BlockEffectColor in_Color);
	static void CreateResetEffect(GameObject* Owner, BlockEffectColor in_Color);

	static void DeleteMagicEffect(float in_Id);
	static void DeleteMoveEffect(float in_Id);
	static void DeleteResetEffect(float in_Id);

	static void MagicStateFinish(float in_Id);
	static void MoveStateFinish(float in_Id);
	static void ResetStateFinish(float in_Id);

private:
	static map<float, BlockMagicEffect*> m_MagicEffectList;
	static map<float, BlockMoveEffect*> m_MoveEffectList;
	static map<float, BlockResetEffect*> m_ResetEffectList;
	static int Counter;

public:
	void ParticleRender();
	void End();


};

