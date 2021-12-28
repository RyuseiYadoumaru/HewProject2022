#include "Stage14.h"

using namespace Create;

bool GamePlay::Stage14Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage14 = make_shared<Actor>("Stage-04");
	m_world3 = make_shared<Actor>("World-03");
	m_stage14->Sprite("stage-04");
	m_world3->Sprite("world-03");

	Instance(m_stage14.get());
	Instance(m_world3.get());

	m_stage14->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world3->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage14Scene::Update()
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

bool GamePlay::Stage14Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage14Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage14->Render();
	m_world3->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
