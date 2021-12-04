//*****************************************************************************
//!	@file	Engine/Create/Scene.h
//!	@brief	
//!	@note	シーンクラス
//!	@note	シーンの元となる。継承することでシーンを作成できる
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Component/Component.h"
#include "../../Game/GameObject/Camera.h"
#include "../Runtime/Core/Object.h"
#include "../Runtime/Core/Renderer.h"
#include <map>
#include <string>
#include <memory>

using GameEngine::Component;
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


		STATE GetState() const;
		void SetState(const STATE in_State);

	public:

		static Camera* GetCamera() { return camera; }

	protected:
		static STATE State;

	protected:
		static Camera* camera;
		static std::map<std::string, GameObject*> ObjectArray;
		static std::map<std::string, std::vector<Component*>> ComponenArray;

		int ObjectCnt;

	protected:

		void Instance(GameObject* in_Object);
		void Destroy(std::string in_ObjectName);
		void SetCamera();
		void SetCamera(Camera* out_Camera);

		void SystemUpdate();
		void ObjectUpdate();
		void ObjectEnd();

		bool ClearDisplay();
		bool SwapChain();

		bool Releace();
	};
}



