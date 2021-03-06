#pragma once
#include"ydmEngine.h"
#include"StageList.h"
#include "SelectTutorial.h"
#include "SelectFade.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class World4StageSelectScene :public Create::Scene
	{
	private:
		Actor* m_worldBack;//背景
		SelectTutorial* m_selectAnimation;//ボタンアニメーション
		SelectFade* m_fadeIn;//フェードイン
		Actor* m_fadeOut;//フェードアウト
		STAGE_NUMBER m_stageNumber;

		int m_frameCnt;
		bool m_inputflg;
		bool m_sceneRightMoveflg;
		bool m_sceneLeftMoveflg;
		bool m_fadeflg;
		bool m_nextWorldflg;
	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;

		void RightMove(STAGE_NUMBER stage);
		void LeftMove(STAGE_NUMBER stage);
	};
}
