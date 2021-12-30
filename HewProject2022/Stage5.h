#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Chair.h"
#include "ScreenFx.h"
#include "CameraFrame.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage5Scene : public Create::Scene
	{
	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

	private:
		/*	�I�u�W�F�N�g	*/
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<Chair> m_ChairStart;
		shared_ptr<Chair> m_ChairEnd;

		/*	�w�i	*/
		shared_ptr<Actor> m_BackGround;

		/*	�����i	*/
		shared_ptr<Actor> m_Window;
		shared_ptr<Actor> m_Door;
		shared_ptr<Actor> m_Aquarium;

		/*	�G�t�F�N�g	*/
		shared_ptr<ScreenFx> m_ScreenEffect;
		shared_ptr<CameraFrame> m_CameraFrame;
		shared_ptr<Fade> m_Fade;

		/*	�e�X�g	*/
		shared_ptr<Actor> m_stage4;//�X�e�[�W���\���̉摜
		shared_ptr<Actor> m_world1;//���[���h���\���̂̉摜
	};
}
