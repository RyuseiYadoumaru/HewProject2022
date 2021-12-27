#pragma once
#include "ydmEngine.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage14Scene : public Create::Scene
	{
	private:
		shared_ptr<Actor> m_stage14;//ステージ数表示の画像
		shared_ptr<Actor> m_world3;//ワールド数表示のの画像

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}

