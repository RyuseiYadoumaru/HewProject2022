//*****************************************************************************
//!	@file	Engine/SceneManager.cpp
//!	@brief	
//!	@note	シーンマネージャークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "SceneManager.h"
#include "../Runtime/Tools/Log.h"
#include "../../SceneList.h"
#include "../Runtime/Tools/Log.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------

int GameEngine::SceneManager::SceneCount = 0;
Create::Scene* GameEngine::SceneManager::scene = NULL;
Create::Scene* GameEngine::SceneManager::NextScene = NULL;
std::map<std::string, Create::Scene*> GameEngine::SceneManager::SceneList;

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
GameEngine::SceneManager::SceneManager()
{
	CreateScene("TitleScene", new GamePlay::TitleScene);
	//三木原追加
	CreateScene("World1StageSelectScene", new GamePlay::World1StageSelectScene);
	CreateScene("World2StageSelectScene", new GamePlay::World2StageSelectScene);
	CreateScene("World3StageSelectScene", new GamePlay::World3StageSelectScene);
	CreateScene("World4StageSelectScene", new GamePlay::World4StageSelectScene);
	CreateScene("World5StageSelectScene", new GamePlay::World5StageSelectScene);
	CreateScene("Stage1", new GamePlay::Stage1Scene);
	CreateScene("Stage2", new GamePlay::Stage2Scene);
	CreateScene("Stage3", new GamePlay::Stage3Scene);
	CreateScene("Stage4", new GamePlay::Stage4Scene);
	CreateScene("Stage5", new GamePlay::Stage5Scene);
	CreateScene("Stage6", new GamePlay::Stage6Scene);
	CreateScene("Stage7", new GamePlay::Stage7Scene);
	CreateScene("Stage8", new GamePlay::Stage8Scene);
	CreateScene("Stage9", new GamePlay::Stage9Scene);
	CreateScene("Stage10", new GamePlay::Stage10Scene);
	CreateScene("Stage11", new GamePlay::Stage11Scene);
	CreateScene("Stage12", new GamePlay::Stage12Scene);
	CreateScene("Stage13", new GamePlay::Stage13Scene);
	CreateScene("Stage14", new GamePlay::Stage14Scene);
	CreateScene("Stage15", new GamePlay::Stage15Scene);
	CreateScene("Stage16", new GamePlay::Stage16Scene);
	CreateScene("Stage17", new GamePlay::Stage17Scene);
	CreateScene("Stage18", new GamePlay::Stage18Scene);
	CreateScene("Stage19", new GamePlay::Stage19Scene);
	CreateScene("Stage20", new GamePlay::Stage20Scene);
	CreateScene("Stage21", new GamePlay::Stage21Scene);
	CreateScene("Stage22", new GamePlay::Stage22Scene);
	CreateScene("Stage23", new GamePlay::Stage23Scene);
	CreateScene("Stage24", new GamePlay::Stage24Scene);
	CreateScene("Stage25", new GamePlay::Stage25Scene);

	NextScene = SceneList["TitleScene"];
}

//==============================================================================
//!	@fn		CreateScene
//!	@brief	シーンリストにシーンを生成する
//!	@param	シーンの名前
//!	@param	シーンアドレス
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::SceneManager::CreateScene(std::string SceneName, Create::Scene* create)
{
	/****	エラーチェック	****/
	if (create == NULL)
	{
		Log::LogError("生成するシーンが見つかりません");
		return false;
	}

	SceneList.insert(std::make_pair(SceneName, create));
	SceneCount++;
	return true;
}

//==============================================================================
//!	@fn		LoadScene
//!	@brief	シーンをロードする
//!	@param	ロードするシーンの名前
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::SceneManager::LoadScene(std::string SceneName)
{
	if (SceneList.empty())
	{
		Log::LogError("シーンがありません");
		return false;
	}

	NextScene = NULL;
	NextScene = SceneList[SceneName];

	/****	エラーチェック	****/
	if (scene == NULL)
	{
		Log::LogError("ロードシーンに失敗しました");
		return false;
	}

	/****	シーン状態変更	****/
	scene->SetState(Create::Scene::END);

	return true;

}

bool GameEngine::SceneManager::LoadResult(std::string NowSceneName)
{
	if (SceneList.empty())
	{
		Log::LogError("シーンがありません");
		return false;
	}

	NextScene = NULL;
	NextScene = SceneList["ResultScene"];

	/****	エラーチェック	****/
	if (scene == NULL)
	{
		Log::LogError("ロードシーンに失敗しました");
		return false;
	}

	/****	シーン状態変更	****/
	scene->SetState(Create::Scene::END);

	return true;
}

//==============================================================================
//!	@fn		SetUp
//!	@brief	シーンの設定を行う
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::SceneManager::SetUp()
{
	/****	シーン変更	****/
	scene = NextScene;

	/****	シーン状態変更	****/
	scene->SetState(Create::Scene::PLAY);
	Input::LeftVibrationStop();
	Input::RightVibrationStop();


	return true;
}

//==============================================================================
//!	@fn		Releace
//!	@brief	シーンマネージャー解放処理
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::SceneManager::Releace()
{

	SceneList.clear();
	delete NextScene;

	return true;
}
