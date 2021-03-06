//*****************************************************************************
//!	@file	Game/GameObject/Character.h
//!	@brief	
//!	@note	キャラクタークラス
//!	@note	キャラクターオブジェクトの基底クラス
//!	@note	キャラクターのゲームオブジェクトに継承する
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../../Engine/Create/GameObject.h"
#include "../../Engine/Component/Physics/BoxCollider2D.h"
#include <memory>

namespace Create
{
	class Character : public GameObject
	{
	protected:
		GameEngine::SpriteRenderer* m_SpriteRenderer;

	public:
		Character(std::string in_Name);
		bool Start() override;
		bool Update() override;
		bool End() override;

		bool Render() override;

		void Sprite(std::string in_SpriteName);
		void Vertex(std::string in_VertexName);
		void Pixcel(std::string in_PixcelName);
	};
}

