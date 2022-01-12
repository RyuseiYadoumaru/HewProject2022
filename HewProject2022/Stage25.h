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

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage25Scene : public Create::Scene
	{
	private:
		/*	�I�u�W�F�N�g	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		World5_desk* m_World5_deskStart;
		Toy* m_ToyEnd;


		/*	�w�i	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		LayerFront* m_LayerFront;

		/*	�V��	*/
		Ceiling* m_Ceiling;

		/*	�G�t�F�N�g	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
