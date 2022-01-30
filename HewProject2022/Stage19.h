#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "BackGround.h"
#include "ScreenFx.h"
#include "Ceiling.h"
#include "BookShelf.h"
#include "PictureFrame.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"
#include "Shelf2.h"
#include"PlayerGoalEffect.h"

#include "PlayModeUI.h"
#include "waku.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage19Scene : public Create::Scene
	{
	private:
		/* �I�u�W�F�N�g */
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		PictureFrame* m_PicTureFrameStart;
		Shelf2* m_Shelf2End;


		/*	�w�i	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		GrayBack*       m_GrayBack;
		LayerFront*		m_LayerFront;

		/*	�V��	*/
		Ceiling* m_Ceiling;

		/* �S�[�� */
		Goal* m_Goal;
		PlayerGoalEffect* m_PGoalEffect;

		/* Pause */
		Pause* m_Pause;
		Pause* m_Button;
		int Scene_State = 0;//Pause��������p

		/* ���U���g */
		Result* m_ResultCursor;
		Result* m_ResultBack;

		/*	�G�t�F�N�g	*/
		Fade* m_Fade;
		ScreenFx* m_ScreenEffect;

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
