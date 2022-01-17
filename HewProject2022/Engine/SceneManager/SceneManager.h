//*****************************************************************************
//!	@file	Engine/SceneManager/SceneManager.h
//!	@brief	
//!	@note	シーンマネージャークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Create/Scene.h"
#include <map>

namespace GameEngine
{
	class SceneManager
	{
	public:
		static int SceneCount;
		static Create::Scene* scene;


	private:

		static std::map<std::string, Create::Scene*> SceneList;
		static Create::Scene* NextScene;

	public:

		SceneManager();

		static bool CreateScene(std::string SceneName, Create::Scene* create);
		
		static bool LoadScene(std::string SceneName);
		//永浦追加
		static bool LoadResult(std::string NowSceneName);

		bool SetUp();

	public:
		bool Releace();

	};
}

enum Scene_L {
	TitleScene,
	ResultScene,
	ProtScene,
	WorldSelectScene,
	World1StageSelectScene,
	World2StageSelectScene,
	World3StageSelectScene,
	World4StageSelectScene,
	World5StageSelectScene,
	World6StageSelectScene,
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	Stage6,
	Stage7,
	Stage8,
	Stage9,
	Stage10,
	Stage11,
	Stage12,
	Stage13,
	Stage14,
	Stage15,
	Stage16,
	Stage17,
	Stage18,
	Stage19,
	Stage20,
	Stage21,
	Stage22,
	Stage23,
	Stage24,
	Stage25,
	Stage26,
	Stage27,
	Stage28,
	Stage29,
	Stage30


};

