//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/ParticleSystem.cpp
//!	@brief	
//!	@note	�p�[�e�B�N���V�X�e���N���X
//!	@note	�p�[�e�B�N�����Ǘ�����
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "ParticleSystem.h"
#include "../../Create/Particle.h"
#include "../SpriteRenderer.h"
#include "../../Create/GameObject.h"
#include "../../Runtime/Tools/Log.h"

//==============================================================================
//!	@fn		Init
//!	@brief�@������
//!	@param	�p�[�e�B�N��
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::ParticleSystem::Init(Create::Particle* in_Particle = nullptr)
{

	if (in_Particle == nullptr)
	{
		Log::LogError("�p�[�e�B�N���f�[�^������܂���");
		return false;
	}

	/*	�p�[�e�B�N���ݒ�	*/
	m_Pariticle = in_Particle;
	m_Pariticle->Init();

	/*	�e�N�X�`���T�C�Y�ݒ�	*/
	float Width = 1.0f / m_Pariticle->GetFrameMax();
	float Height = 1.0f;
	Owner->GetComponent<SpriteRenderer>()->SetTexSize(Width, Height);

	m_Status = PARTICLE_STATUS::STOP;
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief�@�X�V
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::ParticleSystem::Update()
{
	if (m_Pariticle == nullptr)
	{
		return false;
	}

	switch (m_Status)
	{
		/*	���[�v�Đ�	*/
	case GameEngine::ParticleSystem::LOOP:
		m_Pariticle->Play();
		break;

		/*	�P��Đ�	*/
	case GameEngine::ParticleSystem::ONE_SHOT:
		if (m_Pariticle->PlayOneShot() == PARTICLE_STOP)
			m_Status = ParticleSystem::STOP;
		break;

		/*	�X�g�b�v	*/
	case GameEngine::ParticleSystem::STOP:
		m_Pariticle->StateStop();
		break;

		/*	�I��	*/
	case GameEngine::ParticleSystem::END:
		m_Pariticle->StateFinish();
		m_Pariticle->End();
		break;
	}

	/*	UV�^�C�����O�X�V	*/
	Owner->GetComponent<SpriteRenderer>()->UTiling = (float)m_Pariticle->GetFrame();
	Owner->GetComponent<SpriteRenderer>()->VTiling = 0.0f;

	return true;
}

//==============================================================================
//!	@fn		SetParticle
//!	@brief	�p�[�e�B�N���Z�b�g
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::ParticleSystem::SetParticle(PARTICLE_STATUS in_Status, Create::Particle* in_Particle)
{
	/*	�p�[�e�B�N��������	*/
	if (in_Particle != nullptr)
	{
		m_Pariticle = in_Particle;
		m_Pariticle->Init();
	}

	/*	�X�e�[�^�X	*/
	m_Status = in_Status;

}
