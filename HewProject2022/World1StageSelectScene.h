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
		Actor* m_button;//�I����摜
		Actor* m_stage_1;//���[���h1�摜
		Actor* m_stage_2;//���[���h2�摜
		Actor* m_stage_3;//���[���h3�摜
		Actor* m_stage_4;//���[���h4�摜
		Actor* m_stage_5;//���[���h5�摜
		Actor* m_worldBack;//�w�i

		Fade* m_fade;//�t�F�[�h
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
