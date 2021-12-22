//*****************************************************************************
//!	@file	Engine/Component/Component.h
//!	@brief	
//!	@note	�R���|�[�l���g�N���X
//!	@note	���ׂẴR���|�[�l���g�̊��N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

namespace Create
{
	class GameObject;
}

namespace GameEngine
{
	class Component
	{
	public:
		virtual bool Init() { return true; }
		virtual bool Update() { return true; }
		virtual bool Release() { return true; }

		void SetOwner(Create::GameObject* in) { this->Owner = in; }
		Create::GameObject* GetOwner() { return Owner; }
	protected:
		Create::GameObject* Owner;
	};
}

