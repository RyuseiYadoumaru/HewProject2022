//*****************************************************************************
//!	@file	Game/GameObject/Camera.h
//!	@brief	
//!	@note	カメラクラス
//!	@note	全てのカメラの元となる
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../../Engine/Create/GameObject.h"
#include "../../Engine/Runtime/Tools/macro.h"
#include "../../Engine/Math/Color.h"
#include "../../Engine/Component/Transform.h"
#include "../../Engine/Math/CRect.h"
#include <DirectXMath.h>

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

	protected:
		void SetCameraPos();

	};
}