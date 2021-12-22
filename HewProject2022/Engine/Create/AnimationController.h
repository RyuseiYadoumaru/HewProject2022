//*****************************************************************************
//!	@file	Engine/Create/AnimationController.h
//!	@brief	
//!	@note	アニメーションコントローラ
//!	@note	アニメーションコントローラーの基底クラス。継承して作成する
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <vector>
#include <memory>

namespace Create
{
	class Animation;

	class AnimationController
	{
	public:
		virtual bool Init() = 0;
		virtual void AnimState() = 0;

		int GetKind();
		int GetFrame();
	protected:
		std::shared_ptr<Animation> Anim;
		std::vector<int> playAnim;
	};
}

