#include "TitleScene.h"

using namespace Create;

bool GamePlay::TitleScene::Start()
{
	//オブジェクト生成 初期化
	m_TitleText = make_shared<Actor>("TitleText");
	m_TitleText->Sprite("タイトル");
	m_TitleText->Start();

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//これじゃダメ？
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	for (auto i : ObjectArray)
	{
		i.second->Start();
	}
	return true;
}

Scene::STATE GamePlay::TitleScene::Update()
{
	camera->Update();



	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("StageTestScene");
	}

	return PLAY;
}

bool GamePlay::TitleScene::End()
{
	/****	絶対いる	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();
	return true;
}

bool GamePlay::TitleScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	//Hanamaru->Render();
	m_TitleText->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}