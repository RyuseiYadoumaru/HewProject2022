#pragma once
#include"ydmEngine.h"
#include"StageList.h"
#include "SelectTutorial.h"
#include "SelectFade.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class World3StageSelectScene :public Create::Scene
	{
	private:
		Actor* m_stage_1;//���[���h1�摜
		Actor* m_stage_2;//���[���h2�摜
		Actor* m_stage_3;//���[���h3�摜
		Actor* m_stage_4;//���[���h4�摜
		Actor* m_stage_5;//���[���h5�摜
		Actor* m_selectUi;//Ui
		Actor* m_worldBack;//�w�i
		SelectTutorial* m_selectAnimation;//�{�^���A�j���[�V����
		SelectFade* m_fadeIn;//�t�F�[�h�C��
		Actor* m_fadeOut;//�t�F�[�h�A�E�g

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