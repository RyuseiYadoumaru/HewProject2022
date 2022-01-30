#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "ScreenFx.h"

#include "BackGround.h"
#include "MiniBook.h"
#include "BigBook.h"
#include "Sofa.h"
#include "Cuhsion.h"
#include "Ceiling.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"
#include"PlayerGoalEffect.h"

#include "MoveTutorial.h"
#include "JumpTutorial.h"
#include "TutorialEffect.h"
#include "Tutorial_X.h"
#include "Tutorial_Y.h"

#include "PlayModeUI.h"
#include "waku.h"

#include"Fireworks.h"
#include"Star.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage3Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Cuhsion* m_CuhsionStart;
		Sofa* m_SofaEnd;

		/*	�w�i	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		GrayBack*       m_GrayBack;

		/*	�V��	*/
		Ceiling* m_Ceiling;

		/* �S�[�� */
		Goal* m_Goal;
		PlayerGoalEffect* m_PGoalEffect;

		/*	�G�t�F�N�g	*/
		ScreenFx* m_ScreenEffect;

		Fade* m_Fade;

		/* Pause */
		Pause* m_Pause;
		Pause* m_Button;

		/* ���U���g */
		Result* m_ResultFront;
		Result* m_ResultBack;
		Result* m_ResultCursor;
		Fireworks* m_Fireworks;
		Star* m_Star;

		// �Q�[�����UI
		PlayModeUI* m_PlayModeUI;
		waku* m_waku;

		/* �`���[�g���A�� */
		MoveTutorial* m_MoveTutorial;
		JumpTutorial* m_JumpTutorial;
		TutorialEffect* m_TutorialEffect;
		Tutorial_X* m_Tutorial_X;
		Tutorial_Y* m_Tutorial_Y;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		int Scene_State = 0;//Pause��������p
	};
}
