#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Cuhsion.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage2Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<Cuhsion> m_CuhsionStart;
		shared_ptr<Cuhsion> m_CuhsionEnd;

		/*	�w�i	*/
		shared_ptr<Actor> m_BackGround;

		/*	�G�t�F�N�g	*/
		shared_ptr<ScreenFx> m_ScreenEffect;
		shared_ptr<CameraFrame> m_CameraFrame;
		shared_ptr<Fade> m_Fade;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
