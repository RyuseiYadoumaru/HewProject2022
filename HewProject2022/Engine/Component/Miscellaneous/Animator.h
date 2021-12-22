//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/Animator.h
//!	@brief	
//!	@note	アニメータークラス
//!	@note	アニメーションを管理する
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Component.h"

namespace Create
{
	class AnimationController;
}

namespace GameEngine
{
	class Animator : public Component
	{
	public:
		bool Init(Create::AnimationController* in_Controller);
		bool Update() override;

	protected:
		Create::AnimationController* Controller;
	};
}
