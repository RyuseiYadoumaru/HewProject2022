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
		shared_ptr<Actor> m_button;//選択矢印画像
		shared_ptr<Actor> m_world_1;//ワールド1画像
		shared_ptr<Actor> m_world_2;//ワールド2画像
		shared_ptr<Actor> m_world_3;//ワールド3画像

		STAGE_NUMBER m_stageNumber;
	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;
	};
}
