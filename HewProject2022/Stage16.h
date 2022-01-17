#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Umbrella.h"
#include "Shelf2.h"
#include "BackGround.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "Ceiling.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage16Scene : public Create::Scene
	{
	private:
		//shared_ptr<Actor> m_stage16;//ステージ数表示の画像
		//shared_ptr<Actor> m_world4;//ワールド数表示のの画像

		/* オブジェクト */
		MainCamera* m_MainCamera;
		Map* m_Map;
		Player* m_Player;
		Umbrella* m_UmbrellaStart;
		Shelf2* m_Shelf2End;

		/*	背景	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		LayerFront*		m_LayerFront;

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
