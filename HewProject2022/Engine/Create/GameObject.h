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
#include "../../Engine/Component/SpriteRenderer.h"
#include "../Component/Component.h"
#include "../Runtime/Core/Tag.h"
#include <DirectXMath.h>
#include <list>

using GameEngine::Transform;
using GameEngine::Component;

#define GAMEOBJECT_ID	(99)

namespace GameEngine
{
	class Component;
}

namespace Create
{
	class GameObject : public Object
	{
	public:
		Transform* transform;
		Tag tag;
		std::list<Component*> ComponentList;

	public:
		GameObject();
		GameObject(std::string in_name);

		Transform GetTransform();
		std::string GetName() { return name; }
		int GetId()const { return id; }

		virtual void Debug() {}

	public:
		//==============================================================================
		//!	@fn		GetComponent
		//!	@brief	コンポーネントリストから取得する
		//!	@note	ない場合nullptrを返す
		//!	@retval	Component
		//==============================================================================
		template<class T>
		T* GetComponent()
		{
			for (auto com : ComponentList)
			{
				T* Buff = dynamic_cast<T*> (com);
				if (Buff != nullptr) return Buff;
			}

			return nullptr;
		}

		//==============================================================================
		//!	@fn		AddComponent
		//!	@brief	コンポーネントリスト追加
		//!	@note	コンポーネントクラスじゃない場合nullptrを返す
		//!	@retval	Component
		//==============================================================================
		//template<class T>
		//T* AddComponent()
		//{
		//	T* Buff = new T();

		//	Buff->SetOwner(this);
		//	ComponentList.push_front(Buff);
		//	Buff->Init();
		//	return Buff;
		//}
		template<class T, class... In>
		T* AddComponent(In... arg)
		{
			T* Buff = new T();

			Buff->SetOwner(this);
			ComponentList.push_front(Buff);
			Buff->Init(arg...);
			return Buff;
		}


	};
}


