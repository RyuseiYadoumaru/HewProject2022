#include "Stage26.h"

using namespace Create;

bool GamePlay::Stage26Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage26 = make_shared<Actor>("Stage-01");
	m_world6 = make_shared<Actor>("World-06");
	m_stage26->Sprite("stage-01");
	m_world6->Sprite("world-06");

	Instance(m_stage26.get());
	Instance(m_world6.get());

	m_stage26->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world6->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage26Scene::Update()
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

bool GamePlay::Stage26Scene::End()
{
	/****	絶対いる	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();

	return true;
}

bool GamePlay::Stage26Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage26->Render();
	m_world6->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
