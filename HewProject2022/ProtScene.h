#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "Test.h"
#include "BackGround.h"
#include "MainCamera.h"
#include "Player.h"

using namespace Create;

/****	�v���g�^�C�v�V�[��	****/
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
	};

}
