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
		bool Update() override;

	public:
		//==============================================================================
		//!	@fn		AddController
		//!	@brief	コントローラを追加する
		//!	@note	ない場合nullptrを返す
		//!	@retval	Controller
		//==============================================================================
		template<class T>
		T* AddController()
		{
			//アニメーションコントローラー生成
			Controller = new T();
			Cnotroller->Init();
			return Controller;
		}

	protected:
		Create::AnimationController* Controller;


	};
}
