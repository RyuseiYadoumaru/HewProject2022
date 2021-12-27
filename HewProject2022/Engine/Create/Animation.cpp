//*****************************************************************************
//!	@file	Engine/Create/Animation.cpp
//!	@brief	
//!	@note	�A�j���[�V�����N���X
//!	@note	�A�j���[�V�����̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Animation.h"
#include "../Runtime/Tools/SystemTimer.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Create::Animation::Animation()
{
	m_speed = 0.0f;
	m_animationFrame = 1;
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

	/*	�X�s�[�h�ݒ�	*/
	m_speed = 1.0f;

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

}

//==============================================================================
//!	@fn		Play
//!	@brief	�Đ�
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	
//==============================================================================
void Create::Animation::Play(std::string AnimName)
{
	//���݂̃A�j���[�V����
	std::vector<int> NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int> NowKind = AnimationTableList[AnimName].m_Kind;

	// �f���^�^�C�����擾�����Z
	SystemTimer* Timer = SystemTimer::Instance();
	m_time += Timer->DeltaTime() * m_speed;

	// �A�j���[�V�����e�[�u���擾
	int AnimationCounter = ((int)m_time % (sizeof(NowTable) / sizeof(int))) + 1;

	// �A�j���[�V�������[�v
	if (NowTable[AnimationCounter] == ANIMATION_LOOP)
	{
		AnimationCounter = 0;
		m_time = 0;
	}

	//�A�j���[�V������ލX�V
	m_kind = NowKind[AnimationCounter];

	// �A�j���[�V�����e�[�u���X�V
	m_animationFrame = NowTable[AnimationCounter];
}

//==============================================================================
//!	@fn		CreateAnimation
//!	@brief	�A�j���[�V��������
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	
//==============================================================================
//void Create::Animation::CreateAnimation(std::string in_Name, std::vector<int> in_AnimTable)
//{
//	AnimationList.insert(std::make_pair(in_Name, in_AnimTable));
//
//}

void Create::Animation::CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable)
{
	AnimationTableList.insert(std::make_pair(in_Name, in_AnimTable));
}
