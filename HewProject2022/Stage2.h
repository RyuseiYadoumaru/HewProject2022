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
#include "PlayModeUI.h"
#include "waku.h"


using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage2Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Sofa* m_SofaStart;
		Cuhsion* m_CuhsionEnd;

		/*	�w�i	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		GrayBack*      m_GrayBack;

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
		Result* m_ResultCursor;
		Result* m_ResultBack;

		// �Q�[�����UI
		PlayModeUI* m_PlayModeUI;
		waku* m_waku;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		int Scene_State = 0;//Pause��������p
	};
}
