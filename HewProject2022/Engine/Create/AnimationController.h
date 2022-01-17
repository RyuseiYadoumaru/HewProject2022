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
		virtual void Update() = 0;

		int GetKind();
		int GetFrame();

		int GetKindMax();
		int GetFrameMax();

	public:
		int AnimState = 0;

	protected:
		std::shared_ptr<Animation> Anim;
	};
}

