#pragma once
#include "ydmEngine.h"
#include "BlockMoveparticle.h"
#include "BlockEffectInfo.h"
using Create::Effect;

/****	�u���b�N�}�W�b�N�G�t�F�N�g	****/
class BlockMoveEffect : public Effect
{
public:
	BlockMoveEffect(NAME in_Name);
	bool Start();
	bool Update() override;

	/*	�G�t�F�N�g�F�ݒ�	*/
	void EffectColorRed()
	{
		EffectColor = BlockEffectColor::RED;
		Sprite("blue35");
	}
	void EffectColorBlue()
	{
		EffectColor = BlockEffectColor::BLUE;
		Sprite("blue35");
	}
	/*	�p�[�e�B�N���X�e�[�g�ݒ�	*/
	void StateFinish() { m_Particle.StateFinish(); }
	void StateStop() { m_Particle.StateStop(); }

private:
	BlockEffectColor EffectColor;
	BlockMoveParticle m_Particle;	//�G�t�F�N�g

};

