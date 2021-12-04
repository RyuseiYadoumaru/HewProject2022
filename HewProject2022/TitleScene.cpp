#include "TitleScene.h"

using namespace Create;

bool GamePlay::TitleScene::Start()
{
	//オブジェクト生成 初期化
	m_TitleText = make_shared<Actor>("TitleText");
	m_TitleText->Sprite("タイトル");

	Instance(m_TitleText.get());

	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::TitleScene::Update()
{
	/****	オブジェクト更新	****/
	ObjectUpdate();


	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("ProtScene");
	}

	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::TitleScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::TitleScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_TitleText->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}