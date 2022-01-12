#include "BlockMagicEffect.h"


/****	�R���X�g���N�^	****/
BlockMagicEffect::BlockMagicEffect(NAME in_Name) : Effect(in_Name)
{
	/*	�I�[�i�[�ݒ�	*/
	m_Owner = nullptr;
	/*	�F�ݒ�	*/
	EffectColor = BlockEffectColor::RED;
}

/****	������	****/
bool BlockMagicEffect::Start()
{
	/*	�G�t�F�N�g�F�ݒ�	*/
	EffectColor = BlockEffectColor::RED;

	/*	�g�����X�t�H�[���ݒ�	*/
	SetOwnerTransform();
	SetSize(TILE_WIDTH, TILE_HEIGHT);

	/*	�X�v���C�g������	*/
	if (EffectColor == BlockEffectColor::RED)
	{
		m_SpriteRenderer->SpriteName = "red1-20";
	}
	else if (EffectColor == BlockEffectColor::BLUE)
	{
		m_SpriteRenderer->SpriteName = "blue1-20";
	}
	m_SpriteRenderer->Init();

	/*	�p�[�e�B�N���V�X�e���R���|�[�l���g	*/
	m_ParticleSystem = AddComponent<ParticleSystem>(&m_Particle);

	return true;
}

/****	�X�V	****/
bool BlockMagicEffect::Update()
{
	/*	�G�t�F�N�g	*/
	if (Input::GetKeyTrigger(PK_1) == true)
	{
		m_ParticleSystem->SetParticle(ParticleSystem::LOOP);
	}
	if (Input::GetKeyTrigger(PK_2) == true)
	{
		m_ParticleSystem->SetParticle(ParticleSystem::ONE_SHOT);
	}
	if (Input::GetKeyTrigger(PK_3) == true)
	{
		m_ParticleSystem->SetParticle(ParticleSystem::END);
	}

	/*	�g�����X�t�H�[���X�V	*/
	SetOwnerTransform();
	return true;
}
