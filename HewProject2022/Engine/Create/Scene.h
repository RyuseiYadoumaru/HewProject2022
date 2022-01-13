//*****************************************************************************
//!	@file	Engine/Create/Scene.h
//!	@brief	
//!	@note	�V�[���N���X
//!	@note	�V�[���̌��ƂȂ�B�p�����邱�ƂŃV�[�����쐬�ł���
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
using NAME = std::string;

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
		static GameObject* Find(ID& id);
		static GameObject* Find(float id);
		static Camera* GetCamera() { return camera; }

	public:
		//==============================================================================
		//!	@fn		Instance
		//!	@brief	�V�[���ɃI�u�W�F�N�g����
		//!	@note	�Q�[���I�u�W�F�N�g�N���X����Ȃ��ꍇnullptr��Ԃ�
		//!	@param	�I�u�W�F�N�g�̖��O
		//!	@retval	GameObject
		//==============================================================================
		template<class OBJ>
		static OBJ* Instance(NAME in_ObjectName)
		{
			OBJ* Buff = new OBJ(in_ObjectName);
			ObjectArray[in_ObjectName] = Buff;
			ObjectArray[in_ObjectName]->Active = true;
			ObjectArray[in_ObjectName]->Start();
			for (auto& Com : ObjectArray[in_ObjectName]->ComponentList)
			{
				ComponenArray[in_ObjectName].push_back(Com);
			}
			ObjectCnt++;	//�I�u�W�F�N�g���Z

			return Buff;
		}
		//==============================================================================
		//!	@fn		GetObject
		//!	@brief	�V�[���̃I�u�W�F�N�g�擾
		//!	@note	�Q�[���I�u�W�F�N�g�N���X����Ȃ��ꍇnullptr��Ԃ�
		//!	@param	�I�u�W�F�N�g�̖��O
		//!	@retval	GameObject
		//==============================================================================
		template<class OBJ>
		static OBJ* GetGameObject(NAME in_ObjectName)
		{
			if (ObjectArray.count(in_ObjectName) == 0) return nullptr;
			OBJ* Buff = dynamic_cast<OBJ*>(ObjectArray[in_ObjectName]);
			if (Buff != nullptr) return Buff;
			return nullptr;
		}
		//==============================================================================
		//!	@fn		ObjectRender
		//!	@brief	�V�[���̃I�u�W�F�N�g�`��
		//!	@note	�Q�[���I�u�W�F�N�g�N���X����Ȃ��ꍇnullptr��Ԃ�
		//!	@param	�I�u�W�F�N�g�̖��O
		//!	@retval	GameObject
		//==============================================================================
		template<class OBJ>
		static OBJ* ObjectRender(NAME in_ObjectName)
		{
			if (ObjectArray.count(in_ObjectName) == 0) return nullptr;
			OBJ* Buff = dynamic_cast<OBJ*>(ObjectArray[in_ObjectName]);
			Buff->Render();
			if (Buff != nullptr) return Buff;
			return nullptr;
		}

		//==============================================================================
		//!	@fn		Destroy
		//!	@brief	�V�[���̃I�u�W�F�N�g�j��
		//!	@param	�I�u�W�F�N�g�̖��O
		//!	@retval	
		//==============================================================================
		static void Destroy(NAME in_ObjectName)
		{
			ObjectArray[in_ObjectName]->End();
			ComponenArray.erase(in_ObjectName);
			ObjectArray.erase(in_ObjectName);
			ObjectCnt--;
		}

	protected:
		static Camera* camera;
		static std::map<std::string, GameObject*> ObjectArray;
		static std::map<std::string, std::vector<Component*>> ComponenArray;
		static STATE State;
		static int ObjectCnt;


	public:
		Scene();

		virtual bool Start() = 0;
		virtual STATE Update() = 0;
		virtual bool End() = 0;
		virtual bool Render();


		STATE GetState() const;
		void SetState(const STATE in_State);

	protected:

		void OldInstance(GameObject* in_Object);
		void OldDestroy(std::string in_ObjectName);
		void SetCamera();
		void OldSetCamera(Camera* out_Camera);
		void SetCamera(Camera* out_Camera) { camera = out_Camera; }

		void SystemUpdate();
		void ObjectUpdate();
		void ObjectEnd();

		bool ClearDisplay();
		bool SwapChain();

		bool Releace();
	};
}



