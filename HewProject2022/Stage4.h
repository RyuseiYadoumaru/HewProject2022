#pragma once
#include "ydmEngine.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage4Scene : public Create::Scene
	{
	private:
		shared_ptr<Actor> m_stage4;//ステージ数表示の画像
		shared_ptr<Actor> m_world1;//ワールド数表示のの画像

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
