//*****************************************************************************
//!	@file	Engine/Create/Particle.cpp
//!	@brief	
//!	@note	�p�[�e�B�N���N���X
//!	@note	�p�[�e�B�N���̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Particle.h"
#include "../Runtime/Tools/Log.h"
#include "../Timer/GameTimer.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Create::Particle::Particle()
{
	m_ParticleName = "Name";
	m_ParticleFrame = 0;
	m_time = 0;
	m_Counter = 0;
	FrameMax = 0;
	State = PARTICLE_STOP;
}

//==============================================================================
//!	@fn		Init
//!	@brief	������
//!	@param	
//!	@retva	
//==============================================================================
void Create::Particle::Init()
{
	/*	�\���e�N�X�`��������	*/
	m_ParticleFrame = 0;
}

//==============================================================================
//!	@fn		Play
//!	@brief	�Đ�
//!	@param	�p�[�e�B�N���e�[�u��
//!	@retva	�p�[�e�B�N���X�e�[�^�X
//==============================================================================
int Create::Particle::Play()
{
	/****	�p�[�e�B�N���J�n����	***/
	if (State == PARTICLE_FINISH) return PARTICLE_FINISH;

	//�A�j���[�V�����X�e�[�^�X
	State = PARTICLE_PLAY;
	//���݂̃A�j���[�V����
	std::vector<int>& NowTable = m_Particle.m_Frame;
	std::vector<float>& NowKey = m_Particle.m_Key;

	if (NowTable.size() == 0)
	{
		Log::LogError("�A�j���[�V�����̖��O���ԈႦ�Ă��܂�");
		return PARTICLE_NAME_ERROR;
	}

	// �f���^�^�C�����擾�����Z
	m_time += GameEngine::GameTimer::deltaTime();

	// �A�j���[�V�������[�v
	if (NowTable[m_Counter + 1] == PARTICLE_FINISH)
	{
		State = PARTICLE_PLAY;
		m_Counter = 0;
		m_time = 0.0f;
	}

	//�A�j���[�V�����J�E���^�X�V
	else if (m_time >= NowKey[m_Counter + 1])
	{
		//Key�^�C���ɂȂ�����animation�t���[�����X�V����
		m_Counter++;
	}

	// �A�j���[�V�����e�[�u���X�V
	m_ParticleFrame = NowTable[m_Counter];

	return State;
}

//==============================================================================
//!	@fn		PlayOneShot
//!	@brief	�P��Đ�
//!	@param	�p�[�e�B�N���e�[�u��
//!	@retva	�p�[�e�B�N���X�e�[�^�X
//==============================================================================
int Create::Particle::PlayOneShot()
{

	/****	�p�[�e�B�N���J�n����	***/
	if (State == PARTICLE_FINISH) return PARTICLE_FINISH;

	//�A�j���[�V�����X�e�[�^�X
	State = PARTICLE_PLAY;

	//���݂̃A�j���[�V����
	std::vector<int>& NowTable = m_Particle.m_Frame;
	std::vector<float>& NowKey = m_Particle.m_Key;

	if (NowTable.size() == 0)
	{
		Log::LogError("�A�j���[�V�����̖��O���ԈႦ�Ă��܂�");
		return PARTICLE_NAME_ERROR;
	}

	// �f���^�^�C�����擾�����Z
	m_time += GameEngine::GameTimer::fixedDeltaTime();

	// �A�j���[�V�������[�v
	if (NowTable[m_Counter + 1] == PARTICLE_FINISH)
	{
		State = PARTICLE_STOP;
		m_Counter = 0;
		m_time = 0.0f;
		return State;
	}

	//�A�j���[�V�����J�E���^�X�V
	else if (m_time >= NowKey[m_Counter + 1])
	{
		//Key�^�C���ɂȂ�����animation�t���[�����X�V����
		m_Counter++;
	}

	// �A�j���[�V�����e�[�u���X�V
	m_ParticleFrame = NowTable[m_Counter];
	return State;
}

//==============================================================================
//!	@fn		End
//!	@brief	�I������
//!	@param	
//!	@retva	
//==============================================================================
int Create::Particle::End()
{
	m_ParticleFrame = 256;
	return PARTICLE_FINISH;
}
