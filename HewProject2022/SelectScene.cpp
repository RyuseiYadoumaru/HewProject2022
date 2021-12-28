#include "SelectScene.h"

using namespace Create;

GamePlay::SelectScene::SelectScene()
{
	m_1pageFlg = true;
}

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
	m_world_4 = make_shared<Actor>("World-04");
	m_world_5 = make_shared<Actor>("World-05");
	m_world_6 = make_shared<Actor>("World-06");
	m_world_1->Sprite("world-01");
	m_world_2->Sprite("world-02");
	m_world_3->Sprite("world-03");
	m_world_4->Sprite("world-04");
	m_world_5->Sprite("world-05");
	m_world_6->Sprite("world-06");
	m_world_1->Start();
	m_world_2->Start();
	m_world_3->Start();
	m_world_4->Start();
	m_world_5->Start();
	m_world_6->Start();
	m_world_1->transform->Position.Set(-650.0f, -200.0f, 0.0f);
	m_world_2->transform->Position.Set(0.0f, -200.0f, 0.0f);
	m_world_3->transform->Position.Set(650.0f, -200.0f, 0.0f);
	m_world_4->transform->Position.Set(-650.0f, -800.0f, 0.0f);
	m_world_5->transform->Position.Set(0.0f, -800.0f, 0.0f);
	m_world_6->transform->Position.Set(650.0f, -800.0f, 0.0f);

	//ステージ番号
	m_worldNumber = WORLD_01;

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
	//1ページ目
	if (m_1pageFlg == true) {
		m_world_1->transform->Position.y = -200.0f;
		m_world_2->transform->Position.y = -200.0f;
		m_world_3->transform->Position.y = -200.0f;
		m_world_4->transform->Position.y = -800.0f;
		m_world_5->transform->Position.y = -800.0f;
		m_world_6->transform->Position.y = -800.0f;

		if (Input::GetKeyTrigger(VK_RIGHT) == true) {//左右キーで矢印キー画像移動
			m_button->transform->Position.x += 650.0f;
			m_worldNumber = WORLD_02;
			if (m_button->transform->Position.x >= 800.0f) {
				m_button->transform->Position.x = 800.0f;
				m_worldNumber = WORLD_03;
			}
		}
		if (Input::GetKeyTrigger(VK_LEFT) == true) {
			m_button->transform->Position.x -= 650.0f;
			m_worldNumber = WORLD_02;
			if (m_button->transform->Position.x <= -500.0f) {
				m_button->transform->Position.x = -500.0f;
				m_worldNumber = WORLD_01;
			}
		}
		if (Input::GetKeyTrigger(VK_UP) == true) {
			m_1pageFlg = false;
			//ページ変更後のbuttom位置
			m_button->transform->Position.x = -500.0f;
		}
	}

	else {
		//ページ変更後
		//2ページ目
		m_world_1->transform->Position.y = -1100.0f;
		m_world_2->transform->Position.y = -1100.0f;
		m_world_3->transform->Position.y = -1100.0f;
		m_world_4->transform->Position.y = -200.0f;
		m_world_5->transform->Position.y = -200.0f;
		m_world_6->transform->Position.y = -200.0f;

		if (Input::GetKeyTrigger(VK_RIGHT) == true) {
			m_button->transform->Position.x += 650.0f;
			m_worldNumber = WORLD_05;
			if (m_button->transform->Position.x >= 800.0f) {
				m_button->transform->Position.x = 800.0f;
				m_worldNumber = WORLD_06;
			}
		}
		if (Input::GetKeyTrigger(VK_LEFT) == true) {
			m_button->transform->Position.x -= 650.0f;
			m_worldNumber = WORLD_05;
			if (m_button->transform->Position.x <= -500.0f) {
				m_button->transform->Position.x = -500.0f;
				m_worldNumber = WORLD_04;
			}
		}
		if (Input::GetKeyTrigger(VK_DOWN) == true) {
			m_1pageFlg = true;
			//ページ変更後のbuttom位置
			m_button->transform->Position.x = -500.0f;
		}
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すと次のシーンへ移動
	{
		if (m_worldNumber == WORLD_01 && m_1pageFlg == false) {
			m_worldNumber = WORLD_04;
		}
		else if (m_worldNumber == WORLD_02 && m_1pageFlg == false) {
			m_worldNumber = WORLD_05;
		}
		else if (m_worldNumber == WORLD_03 && m_1pageFlg == false) {
			m_worldNumber = WORLD_06;
		}

		switch (m_worldNumber)
		{
		case WORLD_01:
			GameEngine::SceneManager::LoadScene("World1StageSelectScene");
			break;
		case WORLD_02:
			GameEngine::SceneManager::LoadScene("World2StageSelectScene");
			break;
		case WORLD_03:
			GameEngine::SceneManager::LoadScene("World3StageSelectScene");
			break;
		case WORLD_04:
			GameEngine::SceneManager::LoadScene("World4StageSelectScene");
			break;
		case WORLD_05:
			GameEngine::SceneManager::LoadScene("World5StageSelectScene");
			break;
		case WORLD_06:
			GameEngine::SceneManager::LoadScene("World6StageSelectScene");
			break;
		}

		//worldセレクト1ページ目に戻す
		m_1pageFlg = true;
	}

	m_button->transform->Update();

	m_world_1->transform->Update();
	m_world_2->transform->Update();
	m_world_3->transform->Update();
	m_world_4->transform->Update();
	m_world_5->transform->Update();
	m_world_6->transform->Update();

	return PLAY;
}

bool GamePlay::SelectScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();
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
	m_world_4->Render();
	m_world_5->Render();
	m_world_6->Render();


	m_button->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}