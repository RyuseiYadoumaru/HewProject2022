#include "Stage6.h"

using namespace Create;

bool GamePlay::Stage6Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage6 = make_shared<Actor>("Stage-01");
	m_world2 = make_shared<Actor>("World-02");
	m_stage6->Sprite("stage-01");
	m_world2->Sprite("world-02");

	Instance(m_stage6.get());
	Instance(m_world2.get());

	m_stage6->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world2->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage6Scene::Update()
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

bool GamePlay::Stage6Scene::End()
{
	/****	絶対いる	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();

	return true;
}

bool GamePlay::Stage6Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage6->Render();
	m_world2->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}