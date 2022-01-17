//*****************************************************************************
//!	@file	Engine/Component/Physics/Rigidbody2d.h
//!	@brief	
//!	@note	2Dスプライトのための物理挙動コンポーネント
//!	@note	
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Rigidbody2d.h"
#include "BoxCollider2D.h"

//==============================================================================
//!	@fn		Init
//!	@brief　初期化
//!	@param	
//==============================================================================
bool GameEngine::Rigidbody2d::Init()
{
	Gravity = 0.5f;
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief　更新
//!	@param	
//==============================================================================
bool GameEngine::Rigidbody2d::Update()
{
	/*	重力	*/

	BoxCollider2D* Col = Owner->GetComponent<BoxCollider2D>();
	if (Col != nullptr)
	{
		Col->PushBackObject();
	}


	return true;
}
