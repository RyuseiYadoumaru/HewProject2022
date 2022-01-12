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
		/*	オブジェクト	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		World5_desk* m_World5_deskStart;
		Toy* m_ToyEnd;


		/*	背景	*/
		BackGround* m_BackGround;
		LayerBack* m_LayerBack;
		LayerFront* m_LayerFront;

		/*	天井	*/
		Ceiling* m_Ceiling;

		/*	エフェクト	*/
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
