#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "Test.h"
#include "BackGround.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "AnimTest.h"

using namespace Create;

/****	プロトタイプシーン	****/
namespace GamePlay
{
	class ProtScene : public Scene
	{
		bool Start() override;
		STATE Update() override;
		bool End() override;

		bool Render() override;

	private:
		shared_ptr<MainCamera> m_MainCamera;
		shared_ptr<Map> m_Map;
		shared_ptr<Player> m_Player;
		shared_ptr<BackGround> m_BackGruond;
		shared_ptr<Fade> m_Fade;
		shared_ptr<Table> m_Table;
		shared_ptr<AnimTest> m_AnimTest;
	};

}

