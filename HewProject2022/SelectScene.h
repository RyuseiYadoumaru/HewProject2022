#pragma once
#include"ydmEngine.h"
#include"StageList.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class SelectScene :public Create::Scene
	{
	private:
		shared_ptr<Actor> m_button;//�I����摜
		shared_ptr<Actor> m_world_1;//���[���h1�摜
		shared_ptr<Actor> m_world_2;//���[���h2�摜
		shared_ptr<Actor> m_world_3;//���[���h3�摜
		shared_ptr<Actor> m_world_4;//���[���h4�摜
		shared_ptr<Actor> m_world_5;//���[���h5�摜
		shared_ptr<Actor> m_world_6;//���[���h6�摜

		WORLD_NUMBER m_worldNumber;

		bool m_1pageFlg;
	public:
		SelectScene();

		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;
	};
}
