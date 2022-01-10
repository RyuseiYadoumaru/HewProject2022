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
	class Stage15Scene : public Create::Scene
	{
	private:
		/*	オブジェクト	*/
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<Tree> m_TreeStart;
		shared_ptr<Plants> m_PlantsEnd;


		/*	背景	*/
		shared_ptr<BackGround> m_BackGround;
		shared_ptr<LayerBack> m_LayerBack;
		shared_ptr<LayerFront> m_LayerFront;

		/*	天井	*/
		shared_ptr<Ceiling> m_Ceiling;

		/*	エフェクト	*/
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
