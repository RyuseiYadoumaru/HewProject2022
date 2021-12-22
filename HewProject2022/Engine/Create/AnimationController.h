//*****************************************************************************
//!	@file	Engine/Create/AnimationController.h
//!	@brief	
//!	@note	�A�j���[�V�����R���g���[��
//!	@note	�A�j���[�V�����R���g���[���[�̊��N���X�B�p�����č쐬����
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

