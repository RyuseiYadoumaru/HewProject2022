#pragma once
#include "ydmEngine.h"
#include "Map.h"
#include "Test.h"
#include "BackGround.h"
#include "MainCamera.h"
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
	shared_ptr<GamePlay::Test> m_Test;
	shared_ptr<BackGround> m_BackGruond;

};

