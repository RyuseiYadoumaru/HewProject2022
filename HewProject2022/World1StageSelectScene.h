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
		shared_ptr<Actor> m_button;//選択矢印画像
		shared_ptr<Actor> m_stage_1;//ワールド1画像
		shared_ptr<Actor> m_stage_2;//ワールド2画像
		shared_ptr<Actor> m_stage_3;//ワールド3画像
		shared_ptr<Actor> m_stage_4;//ワールド4画像
		shared_ptr<Actor> m_stage_5;//ワールド5画像

		STAGE_NUMBER m_stageNumber;

	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;
	};
}
