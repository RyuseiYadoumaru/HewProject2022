//*****************************************************************************
//!	@file	Engine/Component/Physics/Rigidbody2d.h
//!	@brief	
//!	@note	2D�X�v���C�g�̂��߂̕��������R���|�[�l���g
//!	@note	
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../Component.h"

namespace GameEngine
{
	class Rigidbody2d : public Component
	{
	public:
		bool Init() override;
		bool Update() override;

	public:
		float Gravity;

	private:
		static constexpr float GravitationalAcceleration = 9.8f;


	};
}

