//*****************************************************************************
//!	@file	Game/GameObject/Camera.h
//!	@brief	
//!	@note	�J�����N���X
//!	@note	�S�ẴJ�����̌��ƂȂ�
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../../Engine/Create/GameObject.h"
#include "../../Engine/Runtime/Tools/macro.h"
#include "../../Engine/Math/Color.h"
#include "../../Engine/Component/Transform.h"
#include "../../Engine/Math/CRect.h"
#include <DirectXMath.h>

//left right top buttom

namespace Create
{
	class  Camera : public GameObject
	{
	public:
		Math::Color BackgroundColor;


	public:
		Camera(std::string in_name);

		bool Start() override;
		bool Update() override;

	public:
		Math::Color* GetBackgroundColor();

		float GetLeft();
		float GetRight();
		float GetTop();
		float GetButtom();

	protected:
		void SetCameraPos();

	};
}