#pragma once
#include "ydmEngine.h"
#include "BlockMagicparticle.h"
#include "BlockEffectInfo.h"
using Create::Effect;

/****	ブロックマジックエフェクト	****/
class BlockMagicEffect : public Effect
{
public:
	BlockMagicEffect(NAME in_Name);
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
	BlockMagicParticle m_Particle;	//エフェクト

};

