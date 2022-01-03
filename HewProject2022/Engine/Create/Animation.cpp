//*****************************************************************************
//!	@file	Engine/Create/Animation.cpp
//!	@brief	
//!	@note	�A�j���[�V�����N���X
//!	@note	�A�j���[�V�����̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Animation.h"
#include "../Runtime/Tools/SystemTimer.h"
#include "../Timer/GameTimer.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Create::Animation::Animation()
{
	m_AnimationName = "Name";
	m_animationFrame = 0;
	m_AnimationCounter = 0;
	m_kind = 1;
	m_time = 0;
}

//==============================================================================
//!	@fn		Init
//!	@brief	������
//!	@param	
//!	@retva	
//==============================================================================
void Create::Animation::Init()
{
	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

}

//==============================================================================
//!	@fn		PlayLoop
//!	@brief	���[�v�Đ�
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	
//==============================================================================
void Create::Animation::PlayLoop(std::string AnimName)
{
	/*	������	*/
	if (m_AnimationName != AnimName)
	{
		//�A�j���[�V�������ς�������ɏ���������
		m_AnimationCounter = 0;
		m_time = 0.0f;
		m_AnimationName = AnimName;

	}
	//���݂̃A�j���[�V����
	std::vector<int> NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int> NowKind = AnimationTableList[AnimName].m_Kind;
	std::vector<float>& NowKey = AnimationTableList[AnimName].m_Key;

	// �f���^�^�C�����擾�����Z
	SystemTimer* Timer = SystemTimer::Instance();
	m_time += GameEngine::GameTimer::deltaTime();
	printf("DeltaTime:%f\n", GameEngine::GameTimer::deltaTime());

	// �A�j���[�V�������[�v
	if (NowTable[m_AnimationCounter + 1] == ANIMATION_FINISH)
	{
		printf("���[�v�A�j���[�V����\n");
		m_AnimationCounter = 0;
		m_time = 0;
	}

	//�A�j���[�V�����J�E���^�X�V
	if (m_time >= NowKey[m_AnimationCounter + 1])
	{
		//Key�^�C���ɂȂ�����animation�t���[�����X�V����
		m_AnimationCounter++;
	}

	//�A�j���[�V������ލX�V
	m_kind = NowKind[m_AnimationCounter];

	// �A�j���[�V�����e�[�u���X�V
	m_animationFrame = NowTable[m_AnimationCounter];
}

//==============================================================================
//!	@fn		PlayOneShot
//!	@brief	�P��Đ�
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	
//==============================================================================
int Create::Animation::PlayOneShot(std::string AnimName)
{
	//���݂̃A�j���[�V����
	std::vector<int>& NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int>& NowKind = AnimationTableList[AnimName].m_Kind;

	// �f���^�^�C�����擾�����Z
	SystemTimer* Timer = SystemTimer::Instance();

	// �A�j���[�V�����e�[�u���擾
	int AnimationCounter = ((int)m_time % (sizeof(NowTable) / sizeof(int))) + 1;

	// �A�j���[�V�������[�v
	if (NowTable[AnimationCounter] == ANIMATION_FINISH)
	{
		AnimationCounter = 0;
		m_time = 0;
	}

	//�A�j���[�V������ލX�V
	m_kind = NowKind[AnimationCounter];

	// �A�j���[�V�����e�[�u���X�V
	m_animationFrame = NowTable[AnimationCounter];

	//�A�j���[�V�������I��������Đ��I����Ԃ�
	return ANIMATION_FINISH;
}

//==============================================================================
//!	@fn		CreateAnimation
//!	@brief	�A�j���[�V��������
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	
//==============================================================================
void Create::Animation::CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable)
{
	AnimationTableList.insert(std::make_pair(in_Name, in_AnimTable));
}
