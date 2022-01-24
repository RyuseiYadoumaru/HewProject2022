#pragma once
#include"ydmEngine.h"
#include"StageList.h"
#include "Fade.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class World1StageSelectScene :public Create::Scene
	{
	private:
		Actor* m_button;//選択矢印画像
		Actor* m_stage_1;//ワールド1画像
		Actor* m_stage_2;//ワールド2画像
		Actor* m_stage_3;//ワールド3画像
		Actor* m_stage_4;//ワールド4画像
		Actor* m_stage_5;//ワールド5画像
		Actor* m_worldBack;//背景

		Fade* m_fade;//フェード
		STAGE_NUMBER m_stageNumber;

		int m_frameCnt;
		bool m_inputflg;
		bool m_sceneRightMoveflg;
		bool m_sceneLeftMoveflg;

	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;

		void RightMove(STAGE_NUMBER stage);
		void LeftMove(STAGE_NUMBER stage);
	};
}
