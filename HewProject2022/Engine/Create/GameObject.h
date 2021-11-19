//*****************************************************************************
//!	@file	Engine/Create/GameObject.h
//!	@brief	
//!	@note	�Q�[���I�u�W�F�N�g�N���X
//!	@note	�S�ẴQ�[���I�u�W�F�N�g�̌��ƂȂ�B�p�����邱�ƂŃI�u�W�F�N�g���쐬�ł���
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


