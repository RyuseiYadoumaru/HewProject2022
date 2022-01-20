//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/Animator.cpp
//!	@brief	
//!	@note	�A�j���[�^�[�N���X
//!	@note	�A�j���[�V�������Ǘ�����
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "Animator.h"
#include "../../Create/AnimationController.h"
#include "../SpriteRenderer.h"
#include "../../Create/GameObject.h"

//==============================================================================
//!	@fn		Init
//!	@brief�@������
//!	@param	�A�j���[�V����
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::Animator::Init(Create::AnimationController* in_Controller)
{
	/*	�R���g���[��	*/
	Controller = in_Controller;
	Controller->Init();
	/*	�e�N�X�`���T�C�Y�ݒ�	*/
	float Width = 1.0f / Controller->GetFrameMax();
	float Height = 1.0f / Controller->GetKindMax();
	Owner->GetComponent<SpriteRenderer>()->SetTexSize(Width, Height);
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief�@�X�V
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::Animator::Update()
{
	/*	�R���g���[���[�X�V	*/
	Controller->Update();

	/*	UV�^�C�����O�X�V	*/
	Owner->GetComponent<SpriteRenderer>()->UTiling = (float)Controller->GetFrame();
	Owner->GetComponent<SpriteRenderer>()->VTiling = (float)Controller->GetKind();
	return true;
}
