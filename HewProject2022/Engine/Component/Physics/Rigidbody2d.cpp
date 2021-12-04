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
//!	@fn		Update
//!	@brief　更新
//!	@param	
//==============================================================================
bool GameEngine::Rigidbody2d::Update()
{
	BoxCollider2D* Col = Owner->GetComponent<BoxCollider2D>();
	if (Col != nullptr)
	{
		Col->PushBackObject();
	}


	return true;
}
