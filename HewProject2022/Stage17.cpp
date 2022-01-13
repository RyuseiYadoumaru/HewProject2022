#include "Stage17.h"

using namespace Create;

bool GamePlay::Stage17Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage17 = make_shared<Actor>("Stage-02");
	m_world4 = make_shared<Actor>("World-04");
	m_stage17->Sprite("stage-02");
	m_world4->Sprite("world-04");

	OldInstance(m_stage17.get());
	OldInstance(m_world4.get());

	m_stage17->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world4->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage17Scene::Update()
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

bool GamePlay::Stage17Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage17Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage17->Render();
	m_world4->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
