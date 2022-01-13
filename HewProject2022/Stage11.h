#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "Plants.h"
#include "Tree.h"
#include "Rose.h"
#include "Ceiling.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage11Scene : public Create::Scene
	{
	private:
		/*	オブジェクト	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Rose* m_RoseStart;
		Plants* m_PlantsEnd;


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
