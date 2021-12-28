#include "Stage2.h"

using namespace Create;

bool GamePlay::Stage2Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage2 = make_shared<Actor>("Stage-02");
	m_world1 = make_shared<Actor>("World-01");
	m_stage2->Sprite("stage-02");
	m_world1->Sprite("world-01");

	Instance(m_stage2.get());
	Instance(m_world1.get());

	m_stage2->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world1->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage2Scene::Update()
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

bool GamePlay::Stage2Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage2Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage2->Render();
	m_world1->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}