#pragma once
#include"ydmEngine.h"
#include"StageList.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class World2StageSelectScene :public Create::Scene
	{
	private:
		shared_ptr<Actor> m_button;//�I����摜
		shared_ptr<Actor> m_stage_1;//���[���h1�摜
		shared_ptr<Actor> m_stage_2;//���[���h2�摜
		shared_ptr<Actor> m_stage_3;//���[���h3�摜
		shared_ptr<Actor> m_stage_4;//���[���h4�摜
		shared_ptr<Actor> m_stage_5;//���[���h5�摜

		shared_ptr<Actor> m_worldBack;//�w�i

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