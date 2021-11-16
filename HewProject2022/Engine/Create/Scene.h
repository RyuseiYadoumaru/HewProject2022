//*****************************************************************************
//!	@file	Engine/Create/Scene.h
//!	@brief	
//!	@note	シーンクラス
//!	@note	シーンの元となる。継承することでシーンを作成できる
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../../Game/GameObject/Camera.h"
#include "../Runtime/Core/Object.h"
#include "../Runtime/Core/Renderer.h"
#include <map>
#include <string>
#include <memory>

namespace Create
{
	class Scene
	{
	public:
		enum  STATE
		{
			START,

			PLAY,

			END

		};

	public:
		Scene();

		virtual bool Start() = 0;
		virtual STATE Update() = 0;
		virtual bool End() = 0;
		virtual bool Render();

		void Instance(Object* in_Object);
		void Destroy(std::string in_ObjectName);

		STATE GetState() const;
		void SetState(const STATE in_State);

	protected:
		static STATE State;

	protected:
		std::shared_ptr<Camera> camera;
		std::map<std::string, Object*> ObjectArray;


	protected:
		bool ClearDisplay();
		bool SwapChain();
	};
}



