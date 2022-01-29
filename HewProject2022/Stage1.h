#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "MiniBook.h"
#include "BigBook.h"
#include "Sofa.h"
#include "Ceiling.h"
#include "Pause.h"
#include "Goal.h"
#include"Result.h"
#include"PlayerGoalEffect.h"

#include "BlockMagicEffect.h"

#include "MoveTutorial.h"
#include "JumpTutorial.h"
#include "TutorialEffect.h"
#include "Tutorial_X.h"
#include "Tutorial_Y.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage1Scene : public Create::Scene
	{
	private:
		/*	オブジェクト	*/
		MainCamera*		m_MainCamera;
		Map*			m_Map;
		Player*			m_Player;
		Table*			m_TableStart;
		Sofa*			m_SofaEnd;
		BigBook*		m_BigBook;
		MiniBook*		m_MiniBook;

		//三木原追加 チュートリアル
		MoveTutorial* m_MoveTutorial;
		JumpTutorial* m_JumpTutorial;
		TutorialEffect* m_TutorialEffect;
		Tutorial_X* m_Tutorial_X;
		Tutorial_Y* m_Tutorial_Y;

		/*	背景	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		GrayBack*       m_GrayBack;
		LayerFront*		m_LayerFront;

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
		Result* m_ResultBack;
		Result* m_ResultCursor;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;


	};
}
