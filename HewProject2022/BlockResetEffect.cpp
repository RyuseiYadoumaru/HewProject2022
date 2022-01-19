#include "BlockResetEffect.h"
#include "BlockParticleManager.h"


/****	�R���X�g���N�^	****/
BlockResetEffect::BlockResetEffect(NAME in_Name) : Effect(in_Name)
{
	/*	�I�[�i�[�ݒ�	*/
	m_Owner = nullptr;
	/*	�F�ݒ�	*/
	EffectColor = BlockEffectColor::RED;
}

/****	������	****/
bool BlockResetEffect::Start()
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
		m_SpriteRenderer->SpriteName = "red35-50";
	}
	else if (EffectColor == BlockEffectColor::BLUE)
	{
		m_SpriteRenderer->SpriteName = "blue35-50";
	}
	m_SpriteRenderer->Init();

	/*	�p�[�e�B�N���V�X�e���R���|�[�l���g	*/
	m_ParticleSystem = AddComponent<ParticleSystem>(&m_Particle);
	m_ParticleSystem->SetParticle(ParticleSystem::ONE_SHOT);

	return true;
}

/****	�X�V	****/
bool BlockResetEffect::Update()
{

	//�X�g�b�v��ԂɂȂ�����I������
	if (m_Particle.GetState() == PARTICLE_STOP) m_Particle.StateFinish();

	/*	�I��������j������@	*/
	if (m_Particle.GetState() == PARTICLE_FINISH)
	{
		BlockParticleManager::DeleteResetEffect(m_Owner->GetId().x);
		Destroy();
	}

	/*	�g�����X�t�H�[���X�V	*/
	SetOwnerPosition();
	return true;
}
