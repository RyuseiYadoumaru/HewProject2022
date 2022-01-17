#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "BackGround.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "Ceiling.h"
#include "Shelf2.h"
#include "BookShelf.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage17Scene : public Create::Scene
	{
	private:
		/* �I�u�W�F�N�g */
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Shelf2* m_Shelf2Start;
		BookShelf* m_BookShelfEnd;

		/*	�w�i	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		LayerFront*		m_LayerFront;

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
