#pragma once
#include"ydmEngine.h"
#include"StageList.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class World1StageSelectScene :public Create::Scene
	{
	private:
		shared_ptr<Actor> m_button;//�I����摜
		shared_ptr<Actor> m_stage_1;//���[���h1�摜
		shared_ptr<Actor> m_stage_2;//���[���h2�摜
		shared_ptr<Actor> m_stage_3;//���[���h3�摜
		shared_ptr<Actor> m_stage_4;//���[���h4�摜
		shared_ptr<Actor> m_stage_5;//���[���h5�摜

		STAGE_NUMBER m_stageNumber;

	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;
	};
}
