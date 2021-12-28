#include "Stage10.h"

using namespace Create;

bool GamePlay::Stage10Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage10 = make_shared<Actor>("Stage-05");
	m_world2 = make_shared<Actor>("World-02");
	m_stage10->Sprite("stage-05");
	m_world2->Sprite("world-02");

	Instance(m_stage10.get());
	Instance(m_world2.get());

	m_stage10->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world2->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage10Scene::Update()
{
	/****	オブジェクト更新	****/
	ObjectUpdate();


	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_B))//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage10Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage10Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage10->Render();
	m_world2->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}