//*****************************************************************************
//!	@file	Game/GameObject/Actor.h
//!	@brief	
//!	@note	�A�N�^�[�N���X
//!	@note	�ÓI�I�u�W�F�N�g�̊��N���X
//!	@note	�L�����N�^�[�ȊO�̃Q�[���I�u�W�F�N�g�Ɍp������
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../../Engine/Create/GameObject.h"
#include "../../Engine/Component/Physics/BoxCollider2D.h"
#include <memory>

namespace Create
{
	class Actor : public GameObject
	{
	protected:
		GameEngine::SpriteRenderer* m_SpriteRenderer;

	public:
		Actor();
		Actor(std::string in_Name);
		bool Start() override;
		bool Update() override;
		bool End() override;

		virtual bool Render();

		void SetSize(float in_SizeX, float in_SizeY);
		void Sprite(std::string in_SpriteName);
		void Vertex(std::string in_VertexName);
		void Pixcel(std::string in_PixcelName);
	};
}

