#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Sink.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "Tableware.h"
#include "Ceiling.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"
#include"PlayerGoalEffect.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage6Scene : public Create::Scene
	{
	private:
		/*	オブジェクト	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Sink* m_SinkStart;
		Tableware* m_TablewareEnd;


		/*	背景	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		GrayBack*       m_GrayBack;
		LayerFront* m_LayerFront;

		/*	天井	*/
		Ceiling* m_Ceiling;

		/* ゴール */
		Goal* m_Goal;
		PlayerGoalEffect* m_PGoalEffect;

		/*	エフェクト	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

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
