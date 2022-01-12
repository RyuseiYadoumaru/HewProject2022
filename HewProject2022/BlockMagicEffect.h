#pragma once
#include "ydmEngine.h"
#include "BlockMagicparticle.h"
#include "BlockEffectInfo.h"
using Create::Effect;

/****	�u���b�N�}�W�b�N�G�t�F�N�g	****/
class BlockMagicEffect : public Effect
{
public:
	BlockMagicEffect(NAME in_Name);
	bool Start();
	bool Update() override;

	/*	�G�t�F�N�g�F�ݒ�	*/
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

private:
	BlockEffectColor EffectColor;
	BlockMagicParticle m_Particle;	//�G�t�F�N�g

};

