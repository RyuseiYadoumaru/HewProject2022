#include "Stage28.h"

using namespace Create;

bool GamePlay::Stage28Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage28 = make_shared<Actor>("Stage-03");
	m_world6 = make_shared<Actor>("World-06");
	m_stage28->Sprite("stage-03");
	m_world6->Sprite("world-06");

	Instance(m_stage28.get());
	Instance(m_world6.get());

	m_stage28->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world6->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage28Scene::Update()
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

bool GamePlay::Stage28Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage28Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage28->Render();
	m_world6->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
