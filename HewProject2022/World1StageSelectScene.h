#pragma once
#include"ydmEngine.h"
#include"StageList.h"
#include "SceneTransition.h"
#include "SelectTutorial.h"
#include"SelectFade.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class World1StageSelectScene :public Create::Scene
	{
	private:
		Actor* m_worldBack;//背景
		SelectTutorial* m_selectAnimation;//ボタンアニメーション
		SelectFade* m_fadeIn;//フェード
		Actor* m_fadeOut;
		SceneTransition* m_SceneTransition;//シーン遷移

		STAGE_NUMBER m_stageNumber;

		int m_frameCnt;
		bool m_inputflg;
		bool m_sceneRightMoveflg;
		bool m_sceneLeftMoveflg;
		bool m_fadeflg;

	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;

		void RightMove(STAGE_NUMBER stage);
		void LeftMove(STAGE_NUMBER stage);
	};
}
