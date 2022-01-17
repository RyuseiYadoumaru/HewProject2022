#include "Stage27.h"

using namespace Create;

bool GamePlay::Stage27Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage27 = make_shared<Actor>("Stage-02");
	m_world6 = make_shared<Actor>("World-06");
	m_stage27->Sprite("stage-02");
	m_world6->Sprite("world-06");

	OldInstance(m_stage27.get());
	OldInstance(m_world6.get());

	m_stage27->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world6->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage27Scene::Update()
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

bool GamePlay::Stage27Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage27Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage27->Render();
	m_world6->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
