#include "Stage3.h"

using namespace Create;

bool GamePlay::Stage3Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage3 = make_shared<Actor>("Stage-03");
	m_world1 = make_shared<Actor>("World-01");
	m_stage3->Sprite("stage-03");
	m_world1->Sprite("world-01");

	Instance(m_stage3.get());
	Instance(m_world1.get());

	m_stage3->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world1->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage3Scene::Update()
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

bool GamePlay::Stage3Scene::End()
{
	/****	絶対いる	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();

	return true;
}

bool GamePlay::Stage3Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage3->Render();
	m_world1->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}