#include "Stage20.h"

using namespace Create;

bool GamePlay::Stage20Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage20 = make_shared<Actor>("Stage-05");
	m_world4 = make_shared<Actor>("World-04");
	m_stage20->Sprite("stage-05");
	m_world4->Sprite("world-04");

	Instance(m_stage20.get());
	Instance(m_world4.get());

	m_stage20->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world4->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage20Scene::Update()
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

bool GamePlay::Stage20Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage20Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage20->Render();
	m_world4->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}