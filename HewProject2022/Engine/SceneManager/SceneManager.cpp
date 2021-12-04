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
	CreateScene("ResultScene", new GamePlay::ResultScene);
	CreateScene("SampleScene", new GamePlay::SampleScene);
	CreateScene("StageTestScene", new StageTestScene);
	CreateScene("ProtScene", new ProtScene);
	NextScene = SceneList["ProtScene"];
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
