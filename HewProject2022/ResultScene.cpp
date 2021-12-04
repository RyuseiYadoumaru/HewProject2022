#include "ResultScene.h"

using namespace Create;

bool GamePlay::ResultScene::Start()
{
	//オブジェクト生成 初期化
	m_ResultText = make_shared<Actor>("ResultText");
	m_ResultText->Sprite("リザルト");
	Instance(m_ResultText.get());

	/*	カメラ	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::ResultScene::Update()
{
	/****	オブジェクト更新	****/
	ObjectUpdate();

	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すとタイトルに戻る
	{
		GameEngine::SceneManager::LoadScene("TitleScene");
	}

	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::ResultScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();
	return true;
}

bool GamePlay::ResultScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_ResultText->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}