//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/Animator.h
//!	@brief	
//!	@note	�A�j���[�^�[�N���X
//!	@note	�A�j���[�V�������Ǘ�����
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
		//!	@brief	�R���g���[����ǉ�����
		//!	@note	�Ȃ��ꍇnullptr��Ԃ�
		//!	@retval	Controller
		//==============================================================================
		template<class T>
		T* AddController()
		{
			//�A�j���[�V�����R���g���[���[����
			Controller = new T();
			Cnotroller->Init();
			return Controller;
		}

	protected:
		Create::AnimationController* Controller;


	};
}
