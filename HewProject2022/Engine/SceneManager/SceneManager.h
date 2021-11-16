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

		bool SetUp();

	};
}

