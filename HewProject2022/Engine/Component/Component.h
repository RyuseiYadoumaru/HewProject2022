//*****************************************************************************
//!	@file	Engine/Component/Component.h
//!	@brief	
//!	@note	コンポーネントクラス
//!	@note	すべてのコンポーネントの基底クラス
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

