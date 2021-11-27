#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "Test.h"
#include "BackGround.h"
#include "MainCamera.h"
#include "Player.h"
#include "Sound.h"

using Create::Scene;

/****	ステージシーン	****/
class StageTestScene : public Scene
{

public:
	bool Start() override;
	STATE Update() override;
	bool End() override;

	bool Render() override;

private:
	shared_ptr<MainCamera> m_MainCamera;
	shared_ptr<Map> m_Map;
	shared_ptr<Player> m_ProtPlayer;
	shared_ptr<BackGround> m_BackGruond;

};

