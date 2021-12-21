#include "SelectScene.h"

using namespace Create;

bool GamePlay::SelectScene::Start()
{
	//オブジェクト生成 初期化

	//矢印キー画像
	m_button = make_shared<Actor>("SelectButton");
	m_button->Sprite("button");
	m_button->Start();
	m_button->transform->Scale.Set(0.5f, 0.5f, 0.5f);
	m_button->transform->Position.Set(-500.0f, 150.0f, 0.0f);

	//ワールド画像
	//配列にしたいよ～～～
	m_world_1 = make_shared<Actor>("World-01");
	m_world_2 = make_shared<Actor>("World-02");
	m_world_3 = make_shared<Actor>("World-03");
	m_world_1->Sprite("world-01");
	m_world_2->Sprite("world-02");
	m_world_3->Sprite("world-03");
	m_world_1->Start();
	m_world_2->Start();
	m_world_3->Start();
	m_world_1->transform->Position.Set(-650.0f, -200.0f, 0.0f);
	m_world_2->transform->Position.Set(0.0f, -200.0f, 0.0f);
	m_world_3->transform->Position.Set(650.0f, -200.0f, 0.0f);

	//ステージ番号
	m_stageNumber = STAGE_01;

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//これじゃダメ？
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	for (auto i : ObjectArray)
	{
		i.second->Start();
	}
	return true;
}

Scene::STATE GamePlay::SelectScene::Update()
{
	camera->Update();



	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	//ここより下の処理もっと良くしたい

	if (Input::GetKeyTrigger(VK_RIGHT) == true) {//左右キーで矢印キー画像移動
		m_button->transform->Position.x += 650.0f;
		m_stageNumber = STAGE_02;
		if (m_button->transform->Position.x >= 800.0f) {
			m_button->transform->Position.x = 800.0f;
			m_stageNumber = STAGE_03;
		}
	}
	if (Input::GetKeyTrigger(VK_LEFT) == true) {
		m_button->transform->Position.x -= 650.0f;
		m_stageNumber = STAGE_02;
		if (m_button->transform->Position.x <= -500.0f) {
			m_button->transform->Position.x = -500.0f;
			m_stageNumber = STAGE_01;
		}
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すと次のシーンへ移動
	{
		switch (m_stageNumber)
		{
		case STAGE_01:
			GameEngine::SceneManager::LoadScene("ProtScene");
			break;
		case STAGE_02:
			GameEngine::SceneManager::LoadScene("ProtScene");
			break;
		case STAGE_03:
			GameEngine::SceneManager::LoadScene("ProtScene");
			break;
		}
	}

	m_button->transform->Update();

	m_world_1->transform->Update();
	m_world_2->transform->Update();
	m_world_3->transform->Update();

	return PLAY;
}

bool GamePlay::SelectScene::End()
{
	/****	絶対いる	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();
	return true;
}

bool GamePlay::SelectScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	//自前の描画
	m_world_1->Render();
	m_world_2->Render();
	m_world_3->Render();


	m_button->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}