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
		Actor* m_worldBack;//�w�i
		SelectTutorial* m_selectAnimation;//�{�^���A�j���[�V����
		SelectFade* m_fadeIn;//�t�F�[�h
		Actor* m_fadeOut;
		SceneTransition* m_SceneTransition;//�V�[���J��

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
