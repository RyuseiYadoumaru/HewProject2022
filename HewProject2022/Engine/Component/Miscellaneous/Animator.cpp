//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/Animator.cpp
//!	@brief	
//!	@note	アニメータークラス
//!	@note	アニメーションを管理する
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "Animator.h"
#include "../../Create/AnimationController.h"
#include "../SpriteRenderer.h"
#include "../../Create/GameObject.h"

//==============================================================================
//!	@fn		Init
//!	@brief　初期化
//!	@param	アニメーション
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::Animator::Init(Create::AnimationController* in_Controller)
{
	/*	コントローラ	*/
	Controller = in_Controller;
	Controller->Init();
	/*	テクスチャサイズ設定	*/
	float Width = 1.0f / Controller->GetFrameMax();
	float Height = 1.0f / Controller->GetKindMax();
	Owner->GetComponent<SpriteRenderer>()->SetTexSize(Width, Height);
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief　更新
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::Animator::Update()
{
	/*	コントローラー更新	*/
	Controller->Update();

	/*	UVタイリング更新	*/
	Owner->GetComponent<SpriteRenderer>()->UTiling = (float)Controller->GetFrame();
	Owner->GetComponent<SpriteRenderer>()->VTiling = (float)Controller->GetKind();
	return true;
}
