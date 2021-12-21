#pragma once
#include"ydmEngine.h"

using Create::Actor;
using GameEngine::Input;

enum STAGE_NUMBER {
	STAGE_01,
	STAGE_02,
	STAGE_03,
};

namespace GamePlay
{
	class SelectScene :public Create::Scene
	{
	private:
		shared_ptr<Actor> m_button;//�I����摜
		shared_ptr<Actor> m_world_1;//���[���h1�摜
		shared_ptr<Actor> m_world_2;//���[���h2�摜
		shared_ptr<Actor> m_world_3;//���[���h3�摜

		STAGE_NUMBER m_stageNumber;
	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;
	};
}
