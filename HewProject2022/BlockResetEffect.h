#pragma once
#include "ydmEngine.h"
#include "BlockResetparticle.h"
#include "BlockEffectInfo.h"
using Create::Effect;

/****	ブロックマジックエフェクト	****/
class BlockResetEffect : public Effect
{
public:
	BlockResetEffect(NAME in_Name);
	bool Start();
	bool Update() override;

	/*	エフェクト色設定	*/
	void EffectColorRed()
	{
		EffectColor = BlockEffectColor::RED;
		Sprite("red1-20");
	}
	void EffectColorBlue()
	{
		EffectColor = BlockEffectColor::BLUE;
		Sprite("blue1-20");
	}
	/*	パーティクルステート設定	*/
	void StateFinish() { m_Particle.StateFinish(); }
	void StateStop() { m_Particle.StateStop(); }


private:
	BlockEffectColor EffectColor;
	BlockResetParticle m_Particle;	//エフェクト

};

