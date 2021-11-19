//*****************************************************************************
//!	@file	Engine/Create/GameObject.h
//!	@brief	
//!	@note	ゲームオブジェクトクラス
//!	@note	全てのゲームオブジェクトの元となる。継承することでオブジェクトを作成できる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../Runtime/Core/Object.h"
#include "../Component/Transform.h"
#include <DirectXMath.h>

using GameEngine::Transform;

namespace Create
{
	class GameObject : public Object
	{
	public:
		Transform transform;

	public:
		GameObject();
		GameObject(std::string in_name);

		Transform GetTransform();

	};
}


