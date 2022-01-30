#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "ScreenFx.h"
#include "BackGround.h"
#include "Plants.h"
#include "Tree.h"
#include "Rose.h"
#include "Ceiling.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"
#include"PlayerGoalEffect.h"
#include "PlayModeUI.h"
#include "waku.h"

#include"Fireworks.h"
#include"Star.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage12Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Plants* m_PlantsStart;
		Tree* m_TreeEnd;


		/*	�w�i	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		GrayBack*       m_GrayBack;
		LayerFront* m_LayerFront;

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
		int Scene_State = 0;//Pause��������p

		/* ���U���g */
		Result* m_ResultFront;
		Result* m_ResultBack;
		Result* m_ResultCursor;
		Fireworks* m_Fireworks;
		Star* m_Star;

		// �Q�[�����UI
		PlayModeUI* m_PlayModeUI;
		waku* m_waku;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
