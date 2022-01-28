//*****************************************************************************
//!	@file	Engine/Create/Animation.cpp
//!	@brief	
//!	@note	�A�j���[�V�����N���X
//!	@note	�A�j���[�V�����̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Animation.h"
#include "../Runtime/Tools/Log.h"
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
//!	@fn		Play
//!	@brief	�Đ�
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	�A�j���[�V�����X�e�[�^�X
//==============================================================================
int  Create::Animation::Play(std::string AnimName)
{
	/*	������	*/
	AnimStart(AnimName);

	//�A�j���[�V�����X�e�[�^�X
	int State = ANIMATION_PLAY;

	//���݂̃A�j���[�V����
	std::vector<int>& NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int>& NowKind = AnimationTableList[AnimName].m_Kind;
	std::vector<float>& NowKey = AnimationTableList[AnimName].m_Key;

	if (NowTable.size() == 0)
	{
		Log::LogError("�A�j���[�V�����̖��O���ԈႦ�Ă��܂�");
		return ANIMATION_NAME_ERROR;
	}

	// �f���^�^�C�����擾�����Z
	m_time += GameEngine::GameTimer::deltaTime();

	// �A�j���[�V�������[�v
	if (NowTable[m_AnimationCounter + 1] == ANIMATION_FINISH)
	{
		State = ANIMATION_FINISH;
		m_AnimationCounter = 0;
		m_time = 0.0f;
	}

	//�A�j���[�V�����J�E���^�X�V
	else if (m_time >= NowKey[m_AnimationCounter + 1])
	{
		//Key�^�C���ɂȂ�����animation�t���[�����X�V����
		m_AnimationCounter++;
	}

	//�A�j���[�V������ލX�V
	m_kind = NowKind[m_AnimationCounter];

	// �A�j���[�V�����e�[�u���X�V
	m_animationFrame = NowTable[m_AnimationCounter];

	return State;
}

//==============================================================================
//!	@fn		Delete
//!	@brief	�폜
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	�A�j���[�V�����X�e�[�^�X
//==============================================================================
int Create::Animation::Delete()
{
	//�A�j���[�V������ލX�V
	m_kind = 256;
	// �A�j���[�V�����e�[�u���X�V
	m_animationFrame = 256;
	return ANIMATION_DELETE;
}

//==============================================================================
//!	@fn		Stop
//!	@brief	�A�j���[�V�����X�g�b�v
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	�A�j���[�V�����X�e�[�^�X
//==============================================================================
int Create::Animation::Stop()
{
	//�A�j���[�V������ލX�V
	m_kind = m_kind;
	// �A�j���[�V�����e�[�u���X�V
	m_animationFrame = m_animationFrame;
	return ANIMATION_STOP;
}

//==============================================================================
//!	@fn		CreateAnimation
//!	@brief	�A�j���[�V��������
//!	@param	�A�j���[�V�����e�[�u��
//!	@retva	
//==============================================================================
void Create::Animation::CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable)
{
	in_AnimTable.m_Frame.push_back(ANIMATION_FINISH);
	AnimationTableList.insert(std::make_pair(in_Name, in_AnimTable));
}

//==============================================================================
//!	@fn		AnimStart
//!	@brief	�A�j���[�V����������
//!	@param	�A�j���[�V�������O
//!	@retva	
//==============================================================================

void Create::Animation::AnimStart(std::string in_AnimName)
{
	if (m_AnimationName != in_AnimName)
	{
		//�A�j���[�V�������ς�������ɏ���������
		m_AnimationCounter = 0;
		m_time = 0.0f;
		m_AnimationName = in_AnimName;

	}
}
