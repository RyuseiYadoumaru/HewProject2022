#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "MiniBook.h"
#include "BigBook.h"
#include "Sofa.h"
#include "Cuhsion.h"
#include "Ceiling.h"
#include"Pause.h"
#include"Result.h"
#include "Goal.h"


using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage2Scene : public Create::Scene
	{
	private:
		/*	オブジェクト	*/
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<Sofa> m_SofaStart;
		shared_ptr<Cuhsion> m_CuhsionEnd;

		/*	背景	*/
		shared_ptr<BackGround> m_BackGround;
		shared_ptr<LayerBack> m_LayerBack;
		shared_ptr<LayerFront> m_LayerFront;

		/*	天井	*/
		shared_ptr<Ceiling> m_Ceiling;

		/* ゴール */
		Goal* m_Goal;

		/*	エフェクト	*/
		shared_ptr<ScreenFx> m_ScreenEffect;
		shared_ptr<CameraFrame> m_CameraFrame;
		shared_ptr<Fade> m_Fade;

		/* Pause */
		Pause* m_Pause;
		Pause* m_Button;

		/* リザルト */
		Result* m_ResultCursor;
		Result* m_ResultBack;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		int Scene_State = 0;//Pause処理制御用
	};
}
