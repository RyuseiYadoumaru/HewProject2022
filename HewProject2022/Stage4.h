#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "ScreenFx.h"
#include "CameraFrame.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage4Scene : public Create::Scene
	{
	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

	private:
		/*	オブジェクト	*/
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<Table> m_TableStart;
		shared_ptr<Table> m_TableEnd;

		/*	エフェクト	*/
		shared_ptr<ScreenFx> m_ScreenEffect;
		shared_ptr<CameraFrame> m_CameraFrame;
		shared_ptr<Fade> m_Fade;

		/*	テスト	*/
		shared_ptr<Actor> m_stage4;//ステージ数表示の画像
		shared_ptr<Actor> m_world1;//ワールド数表示のの画像
	};
}
