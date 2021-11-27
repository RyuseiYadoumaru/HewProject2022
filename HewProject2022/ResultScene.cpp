#include "ResultScene.h"

using namespace Create;

bool GamePlay::ResultScene::Start()
{
	//オブジェクト生成 初期化
	m_ResultText = make_shared<Actor>("ResultText");
	m_ResultText->Sprite("リザルト");
	m_ResultText->Start();

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//これじゃダメ？
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	for (auto i : ObjectArray)
	{
		i.second->Start();
	}
	return true;
}

Scene::STATE GamePlay::ResultScene::Update()
{
	camera->Update();



	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すとタイトルに戻る
	{
		GameEngine::SceneManager::LoadScene("TitleScene");
	}

	return PLAY;
}

bool GamePlay::ResultScene::End()
{
	/****	絶対いる	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();
	return true;
}

bool GamePlay::ResultScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	//Hanamaru->Render();
	m_ResultText->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}