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
		shared_ptr<Actor> m_button;//選択矢印画像
		shared_ptr<Actor> m_world_1;//ワールド1画像
		shared_ptr<Actor> m_world_2;//ワールド2画像
		shared_ptr<Actor> m_world_3;//ワールド3画像
		shared_ptr<Actor> m_world_4;//ワールド4画像
		shared_ptr<Actor> m_world_5;//ワールド5画像
		shared_ptr<Actor> m_world_6;//ワールド6画像

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
