//*****************************************************************************
//!	@file	Engine/Component/Physics/Rigidbody2d.h
//!	@brief	
//!	@note	2D�X�v���C�g�̂��߂̕��������R���|�[�l���g
//!	@note	
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Rigidbody2d.h"
#include "BoxCollider2D.h"

//==============================================================================
//!	@fn		Init
//!	@brief�@������
//!	@param	
//==============================================================================
bool GameEngine::Rigidbody2d::Init()
{
	Gravity = 0.5f;
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief�@�X�V
//!	@param	
//==============================================================================
bool GameEngine::Rigidbody2d::Update()
{
	/*	�d��	*/

	BoxCollider2D* Col = Owner->GetComponent<BoxCollider2D>();
	if (Col != nullptr)
	{
		Col->PushBackObject();
	}


	return true;
}
