#pragma once
#include "ydmEngine.h"
#include "BlockMagicEffect.h"
class  MoveManager;
using Create::GameObject;
/****	�ړ��p�[�e�B�N��	****/
class MoveParticleManager
{
public:
	static void CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color);
private:
	static vector<BlockMagicEffect*> m_MagicEffectList;
	static int Counter;

public:
	void Init(MoveManager* in_Owner);
	void ParticleRender();
	void End();




private:
	MoveManager* Owner;

};

