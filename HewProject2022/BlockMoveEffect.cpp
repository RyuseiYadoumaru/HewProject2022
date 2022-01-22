#include "BlockMoveEffect.h"
#include "BlockParticleManager.h"

/****	�R���X�g���N�^	****/
BlockMoveEffect::BlockMoveEffect(NAME in_Name) : Effect(in_Name)
{
	/*	�I�[�i�[�ݒ�	*/
	m_Owner = nullptr;
	/*	�F�ݒ�	*/
	EffectColor = BlockEffectColor::RED;
}

/****	������	****/
bool BlockMoveEffect::Start()
{
	/*	�G�t�F�N�g�F�ݒ�	*/
	EffectColor = BlockEffectColor::RED;

	/*	�g�����X�t�H�[���ݒ�	*/
	SetOwnerPosition();
	SetSize(TILE_WIDTH, TILE_HEIGHT);
	transform->Scale.Set(2.5f, 2.5f, 0.0f);
	/*	�X�v���C�g������	*/
	if (EffectColor == BlockEffectColor::RED)
	{
		m_SpriteRenderer->SpriteName = "red35";
	}
	else if (EffectColor == BlockEffectColor::BLUE)
	{
		m_SpriteRenderer->SpriteName = "blue35";
	}
	m_SpriteRenderer->Init();

	/*	�p�[�e�B�N���V�X�e���R���|�[�l���g	*/
	m_ParticleSystem = AddComponent<ParticleSystem>(&m_Particle);
	m_ParticleSystem->SetParticle(ParticleSystem::LOOP);

	return true;
}

/****	�X�V	****/
bool BlockMoveEffect::Update()
{

	/*	�I��������j������@	*/
	if (m_Particle.GetState() == PARTICLE_FINISH)
	{
		Destroy();
		BlockParticleManager::DeleteMoveEffect(m_Owner->GetId().x);
	}

	/*	�g�����X�t�H�[���X�V	*/
	SetOwnerPosition();
	return true;
}
