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
		/*	�I�u�W�F�N�g	*/
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Rose* m_RoseStart;
		Plants* m_PlantsEnd;


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
