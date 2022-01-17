//*****************************************************************************
//!	@file	Game/GameObject/Effect.h
//!	@brief	
//!	@note	エフェクトクラス
//!	@note	エフェクトオブジェクトの基底クラス
//!	@note	エフェクトのゲームオブジェクトに継承する
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../../Engine/Create/GameObject.h"
#include "../../Engine/Component/Miscellaneous/ParticleSystem.h"
#include <memory>
#include <map>

namespace Create
{
	class Effect : public GameObject
	{
	public:
		Effect();
		Effect(std::string in_Name);
		bool Start() override;
		bool Update() override;
		bool End() override;
		bool Render() override;

		void SetSize(float in_SizeX, float in_SizeY);
		void Sprite(std::string in_SpriteName);
		void Vertex(std::string in_VertexName);
		void Pixcel(std::string in_PixcelName);

		void SetOwner(GameObject* in_Owner) { m_Owner = in_Owner; }

	protected:
		void SetOwnerPosition();


	protected:
		GameObject* m_Owner;
		GameEngine::SpriteRenderer* m_SpriteRenderer;
		GameEngine::ParticleSystem* m_ParticleSystem;
	};
}

