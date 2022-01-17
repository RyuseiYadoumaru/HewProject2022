#pragma once
#include "ydmEngine.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage17Scene : public Create::Scene
	{
	private:
		shared_ptr<Actor> m_stage17;//ステージ数表示の画像
		shared_ptr<Actor> m_world4;//ワールド数表示のの画像

		/* ゴール */
		Goal* m_Goal;

		/* Pause */
		Pause* m_Pause;
		Pause* m_Button;
		int Scene_State = 0;//Pause処理制御用

		/* リザルト */
		Result* m_ResultCursor;
		Result* m_ResultBack;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
