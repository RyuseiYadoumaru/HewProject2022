#include "World5StageSelectScene.h"

using namespace Create;

bool GamePlay::World5StageSelectScene::Start()
{
	//オブジェクト生成 初期化
	//フェード
	m_fade = Instance<SelectFade>("White");
	//ボタンアニメーション
	m_selectAnimation = Instance<SelectTutorial>("SelectAnimation");

	//背景画像
	m_worldBack = Instance<Actor>("Select");
	m_worldBack->Sprite("select");
	m_worldBack->Start();
	m_worldBack->transform->Scale.Set(0.5f, 0.5f, 0.5f);

	//1つのノイズ移動3500
	m_worldBack->transform->Position.Set(7000.0f, 0.0f, 0.0f);

	//Ui
	m_selectUi = Instance<Actor>("SelectUI");
	m_selectUi->Sprite("selectUI");
	m_selectUi->Vertex("vs_Ui");
	m_selectUi->transform->Position.Set(960.0f, 550.0f, 0.0f);
	m_selectUi->transform->Scale.Set(0.5f, 0.5f, 0.0f);

	//ワールド画像
	//配列にしたいよ〜〜〜
	m_stage_1 = Instance<Actor>("Stage-01");
	m_stage_2 = Instance<Actor>("Stage-02");
	m_stage_3 = Instance<Actor>("Stage-03");
	m_stage_4 = Instance<Actor>("Stage-04");
	m_stage_5 = Instance<Actor>("Stage-05");
	m_stage_1->Sprite("stage-01");
	m_stage_2->Sprite("stage-02");
	m_stage_3->Sprite("stage-03");
	m_stage_4->Sprite("stage-04");
	m_stage_5->Sprite("stage-05");
	m_stage_1->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_stage_2->transform->Position.Set(3500.0f, 0.0f, 0.0f);
	m_stage_3->transform->Position.Set(7000.0f, 0.0f, 0.0f);
	m_stage_4->transform->Position.Set(10500.0f, 0.0f, 0.0f);
	m_stage_5->transform->Position.Set(14000.0f, 0.0f, 0.0f);

	//ステージ番号
	m_stageNumber = STAGE_01;

	m_sceneRightMoveflg = false;
	m_sceneLeftMoveflg = false;
	m_inputflg = true;
	m_frameCnt = 0;

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//これじゃダメ？
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::World5StageSelectScene::Update()
{
	ObjectUpdate();

	switch (m_stageNumber) {
	case STAGE_01:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
			if (m_frameCnt >= 20) {
				m_sceneRightMoveflg = true;
				m_inputflg = true;
				m_frameCnt = 0;
			}
		}

		if (Input::GetKeyTrigger(VK_LEFT) == true
			|| Input::GetControllerLeftStick().x < 0.0f) {
		}
		break;

	case STAGE_02:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
			if (m_frameCnt >= 20) {
				m_sceneRightMoveflg = true;
				m_frameCnt = 0;
			}
		}

		if (Input::GetKeyTrigger(VK_LEFT) == true
			|| Input::GetControllerLeftStick().x < 0.0f) {
			if (m_frameCnt >= 20) {
				m_sceneLeftMoveflg = true;
				m_frameCnt = 0;
			}
		}
		break;
	case STAGE_03:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
			if (m_frameCnt >= 20) {
				m_sceneRightMoveflg = true;
				m_frameCnt = 0;
			}
		}

		if (Input::GetKeyTrigger(VK_LEFT) == true
			|| Input::GetControllerLeftStick().x < 0.0f) {
			if (m_frameCnt >= 20) {
				m_sceneLeftMoveflg = true;
				m_frameCnt = 0;
			}
		}
		break;
	case STAGE_04:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
			if (m_frameCnt >= 20) {
				m_sceneRightMoveflg = true;
				m_frameCnt = 0;
			}
		}

		if (Input::GetKeyTrigger(VK_LEFT) == true
			|| Input::GetControllerLeftStick().x < 0.0f) {
			if (m_frameCnt >= 20) {
				m_sceneLeftMoveflg = true;
				m_frameCnt = 0;
			}
		}
		break;
	case STAGE_05:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
		}

		if (Input::GetKeyTrigger(VK_LEFT) == true
			|| Input::GetControllerLeftStick().x < 0.0f) {
			if (m_frameCnt >= 20) {
				m_sceneLeftMoveflg = true;
				m_frameCnt = 0;
			}
		}
		break;
	}

	//右シーン遷移
	if (m_stageNumber == STAGE_01 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_01);
		/*world2へ遷移*/
		if (camera->transform->Position.x == 3500.0f) {
			m_stageNumber = STAGE_02;
		}
	}
	else if (m_stageNumber == STAGE_02 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_02);
		/*world3へ遷移*/
		if (camera->transform->Position.x == 7000.0f) {
			m_stageNumber = STAGE_03;
		}
	}
	else if (m_stageNumber == STAGE_03 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_03);
		//world4へ遷移
		if (camera->transform->Position.x == 10500.0f) {
			m_stageNumber = STAGE_04;
		}
	}
	else if (m_stageNumber == STAGE_04 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_04);
		//world5へ遷移
		if (camera->transform->Position.x == 14000.0f) {
			m_stageNumber = STAGE_05;
		}
	}

	//左シーン遷移
	if (m_stageNumber == STAGE_02 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_02);
		//world1へ遷移
		if (camera->transform->Position.x == 0.0f) {
			m_stageNumber = STAGE_01;
		}
	}
	else if (m_stageNumber == STAGE_03 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_03);
		//world2へ遷移
		if (camera->transform->Position.x == 3500.0f) {
			m_stageNumber = STAGE_02;
		}
	}
	else if (m_stageNumber == STAGE_04 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_04);
		//world3へ遷移
		if (camera->transform->Position.x == 7000.0f) {
			m_stageNumber = STAGE_03;
		}
	}
	else if (m_stageNumber == STAGE_05 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_05);
		//world4へ移動
		if (camera->transform->Position.x == 10500.0f) {
			m_stageNumber = STAGE_04;
		}
	}

	//LB.RBでワールド移動

	if (Input::GetKeyTrigger(PK_A) == true
		|| Input::GetControllerTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER) == true) {
		GameEngine::SceneManager::LoadScene("World4StageSelectScene");
	}

	if (Input::GetKeyTrigger(VK_SPACE) == true
		|| Input::GetControllerTrigger(XINPUT_GAMEPAD_B) == true) {
		GameEngine::SceneManager::LoadScene("TitleScene");
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true)//エンター押すと次のシーンへ移動
	{
		switch (m_stageNumber)
		{
		case STAGE_01:
			GameEngine::SceneManager::LoadScene("Stage21");
			break;
		case STAGE_02:
			GameEngine::SceneManager::LoadScene("Stage22");
			break;
		case STAGE_03:
			GameEngine::SceneManager::LoadScene("Stage23");
			break;
		case STAGE_04:
			GameEngine::SceneManager::LoadScene("Stage24");
			break;
		case STAGE_05:
			GameEngine::SceneManager::LoadScene("Stage25");
			break;
		}
	}

	m_frameCnt++;
	SystemUpdate();
	return PLAY;
}

bool GamePlay::World5StageSelectScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::World5StageSelectScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	//自前の描画
	ObjectRender<Actor>("Stage-01");
	ObjectRender<Actor>("Stage-02");
	ObjectRender<Actor>("Stage-03");
	ObjectRender<Actor>("Stage-04");
	ObjectRender<Actor>("Stage-05");
	ObjectRender<Actor>("Select");
	ObjectRender<SelectTutorial>("SelectAnimation");
	ObjectRender<Actor>("SelectUI");
	ObjectRender<SelectFade>("White");

	/****	画面描画	****/
	SwapChain();
	return true;
}

void GamePlay::World5StageSelectScene::RightMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x < 3500.0f * stage) {
		camera->transform->Position.x += 35.0f * GameTimer::deltaTime();
		//誤差無くし
		if (camera->transform->Position.x >= 3500.0f * stage) {
			camera->transform->Position.x = 3500.0f * stage;

			m_sceneRightMoveflg = false;
		}
	}
}

void GamePlay::World5StageSelectScene::LeftMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x > 3500.0f * (stage - 1) - 3500.0f) {
		camera->transform->Position.x -= 35.0f * GameTimer::deltaTime();
		//誤差無くし
		if (camera->transform->Position.x <= 3500.0f * (stage - 1) - 3500.0f) {
			camera->transform->Position.x = 3500.0f * (stage - 1) - 3500.0f;

			m_sceneLeftMoveflg = false;
		}
	}
}
