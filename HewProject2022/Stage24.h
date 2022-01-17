#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "World5_desk.h"
#include "Storage.h"
#include "House.h"
#include "Toy.h"
#include "Ceiling.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage24Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<Storage> m_StorageStart;
		shared_ptr<House> m_HouseEnd;


		/*	�w�i	*/
		shared_ptr<BackGround> m_BackGround;
		shared_ptr<LayerBack> m_LayerBack;
		shared_ptr<LayerFront> m_LayerFront;

		/*	�V��	*/
		shared_ptr<Ceiling> m_Ceiling;

		/* �S�[�� */
		Goal* m_Goal;

		/*	�G�t�F�N�g	*/
		shared_ptr<ScreenFx> m_ScreenEffect;
		shared_ptr<CameraFrame> m_CameraFrame;
		shared_ptr<Fade> m_Fade;

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
