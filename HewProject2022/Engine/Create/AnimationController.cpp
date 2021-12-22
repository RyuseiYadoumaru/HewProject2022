//*****************************************************************************
//!	@file	Engine/Create/AnimationController.cpp
//!	@brief	
//!	@note	アニメーションコントローラ
//!	@note	アニメーションコントローラーの基底クラス。継承して作成する
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "AnimationController.h"
#include "Animation.h"

//==============================================================================
//!	@fn		GetKind
//!	@brief　種類取得
//!	@param	
//!	@retval	種類
//==============================================================================
int Create::AnimationController::GetKind()
{
	return Anim->GetKind();
}

//==============================================================================
//!	@fn		GetFrame
//!	@brief	フレーム取得
//!	@param	
//!	@retval	アニメーションフレーム
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
