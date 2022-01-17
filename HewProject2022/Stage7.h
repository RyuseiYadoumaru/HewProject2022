#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "Sink.h"
#include "Tableware.h"
#include "Shelf.h"
#include "Ceiling.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage7Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Tableware* m_TablewareStart;
		Shelf* m_ShelfEnd;


		/*	�w�i	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		LayerFront* m_LayerFront;

		/*	�V��	*/
		Ceiling* m_Ceiling;

		/* �S�[�� */
		Goal* m_Goal;

		/*	�G�t�F�N�g	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

		/* Pause */
		Pause* m_Pause;
		Pause* m_Button;
		int Scene_State = 0;//Pause��������p

		/* ���U���g */
		Result* m_ResultCursor;
		Result* m_ResultBack;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
