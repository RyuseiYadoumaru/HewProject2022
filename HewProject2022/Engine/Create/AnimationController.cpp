//*****************************************************************************
//!	@file	Engine/Create/AnimationController.cpp
//!	@brief	
//!	@note	�A�j���[�V�����R���g���[��
//!	@note	�A�j���[�V�����R���g���[���[�̊��N���X�B�p�����č쐬����
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "AnimationController.h"
#include "Animation.h"

//==============================================================================
//!	@fn		GetKind
//!	@brief�@��ގ擾
//!	@param	
//!	@retval	���
//==============================================================================
int Create::AnimationController::GetKind()
{
	return Anim->GetKind();
}

//==============================================================================
//!	@fn		GetFrame
//!	@brief	�t���[���擾
//!	@param	
//!	@retval	�A�j���[�V�����t���[��
//==============================================================================
int Create::AnimationController::GetFrame()
{
	return Anim->GetFrame();
}

int Create::AnimationController::GetKindMax()
{
	return Anim->GetKindMax();
}

int Create::AnimationController::GetFrameMax()
{
	return Anim->GetFrameMax();
}
