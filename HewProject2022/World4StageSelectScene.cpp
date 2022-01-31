#include "World4StageSelectScene.h"

using namespace Create;

bool GamePlay::World4StageSelectScene::Start()
{
	//オブジェクト生成 初期化
	//フェード
	m_fadeIn = Instance<SelectFade>("WhiteIn");

	//フェードアウト
	m_fadeOut = Instance<Actor>("WhiteOut");
	m_fadeOut->Sprite("white");
	m_fadeOut->Vertex("vs_Ui");
	m_fadeOut->transform->Position.Set(950.0f, 500.0f, 0.0f);
	m_fadeOut->GetComponent<SpriteRenderer>()->Color.a = 0.0f;
	m_fadeflg = false;
	m_nextWorldflg = false;

	//ボタンアニメーション
	m_selectAnimation = Instance<SelectTutorial>("SelectAnimation");

	//背景画像
	m_worldBack = Instance<Actor>("Select");
	m_worldBack->Sprite("world4");
	/*m_worldBack->transform->Scale.Set(0.48f, 0.475f, 0.45f);*/
	m_worldBack->transform->Scale.Set(2.01f, 2.0f, 0.45f);
	//1つのノイズ移動3355
	m_worldBack->transform->Position.Set(6710.0f, 0.0f, 0.0f);

	//ステージ番号
	m_stageNumber = STAGE_01;
	m_sceneRightMoveflg = false;
	m_sceneLeftMoveflg = false;
	m_inputflg = false;
	m_frameCnt = 0;

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//これじゃダメ？
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	// BGM再生
	Sound::Sound_Play(SOUND_LABEL_SELECT);

	return true;
}

Scene::STATE GamePlay::World4StageSelectScene::Update()
{
	ObjectUpdate();

	if (m_frameCnt >= 20) {
		m_inputflg = true;
	}

	if (m_fadeIn->m_FadeFlg == false) {//遷移アニメーション(ホワイトアウト)が終了するまで操作できない

		/*	タイトルに戻る	*/
		if (Input::GetControllerTrigger(XInput::Buttom::B) == true || Input::GetKeyTrigger(PK_BS) == true)
		{
			SceneManager::LoadScene("TitleScene");
		}

		switch (m_stageNumber) {
		case STAGE_01:
			if (Input::GetKeyTrigger(VK_RIGHT) == true
				|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
				if (m_frameCnt >= 20) {
					m_sceneRightMoveflg = true;
					m_frameCnt = 0;
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);
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
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

				}
			}

			if (Input::GetKeyTrigger(VK_LEFT) == true
				|| Input::GetControllerLeftStick().x < 0.0f) {
				if (m_frameCnt >= 20) {
					m_sceneLeftMoveflg = true;
					m_frameCnt = 0;
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

				}
			}
			break;
		case STAGE_03:
			if (Input::GetKeyTrigger(VK_RIGHT) == true
				|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
				if (m_frameCnt >= 20) {
					m_sceneRightMoveflg = true;
					m_frameCnt = 0;
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

				}
			}

			if (Input::GetKeyTrigger(VK_LEFT) == true
				|| Input::GetControllerLeftStick().x < 0.0f) {
				if (m_frameCnt >= 20) {
					m_sceneLeftMoveflg = true;
					m_frameCnt = 0;
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

				}
			}
			break;
		case STAGE_04:
			if (Input::GetKeyTrigger(VK_RIGHT) == true
				|| Input::GetControllerLeftStick().x > 0.0f) {//左右キーで矢印キー画像移動
				if (m_frameCnt >= 20) {
					m_sceneRightMoveflg = true;
					m_frameCnt = 0;
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

				}
			}

			if (Input::GetKeyTrigger(VK_LEFT) == true
				|| Input::GetControllerLeftStick().x < 0.0f) {
				if (m_frameCnt >= 20) {
					m_sceneLeftMoveflg = true;
					m_frameCnt = 0;
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

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
					Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

				}
			}
			break;
		}

		//右シーン遷移
		if (m_stageNumber == STAGE_01 && m_sceneRightMoveflg == true) {
			RightMove(STAGE_01);
			/*world2へ遷移*/
			if (camera->transform->Position.x == 3355.0f) {
				m_stageNumber = STAGE_02;
			}
		}
		else if (m_stageNumber == STAGE_02 && m_sceneRightMoveflg == true) {
			RightMove(STAGE_02);
			/*world3へ遷移*/
			if (camera->transform->Position.x == 6710.0f) {
				m_stageNumber = STAGE_03;
			}
		}
		else if (m_stageNumber == STAGE_03 && m_sceneRightMoveflg == true) {
			RightMove(STAGE_03);
			//world4へ遷移
			if (camera->transform->Position.x == 10065.0f) {
				m_stageNumber = STAGE_04;
			}
		}
		else if (m_stageNumber == STAGE_04 && m_sceneRightMoveflg == true) {
			RightMove(STAGE_04);
			//world5へ遷移
			if (camera->transform->Position.x == 13420.0f) {
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
			if (camera->transform->Position.x == 3355.0f) {
				m_stageNumber = STAGE_02;
			}
		}
		else if (m_stageNumber == STAGE_04 && m_sceneLeftMoveflg == true) {
			LeftMove(STAGE_04);
			//world3へ遷移
			if (camera->transform->Position.x == 6710.0f) {
				m_stageNumber = STAGE_03;
			}
		}
		else if (m_stageNumber == STAGE_05 && m_sceneLeftMoveflg == true) {
			LeftMove(STAGE_05);
			//world4へ移動
			if (camera->transform->Position.x == 10065.0f) {
				m_stageNumber = STAGE_04;
			}
		}

		//LB.RBでワールド移動
		if (Input::GetKeyTrigger(PK_D) == true
			|| Input::GetControllerTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true) {
			m_fadeflg = true;
			m_nextWorldflg = true;
		}

		if (Input::GetKeyTrigger(PK_A) == true
			|| Input::GetControllerTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER) == true) {
			m_fadeflg = true;
		}

		if (m_fadeflg == true && m_nextWorldflg == true) {
			if (m_fadeOut->GetComponent<SpriteRenderer>()->Color.a < 1.0f) {
				m_fadeOut->GetComponent<SpriteRenderer>()->Color.a += 0.03;
			}
			if (m_fadeOut->GetComponent<SpriteRenderer>()->Color.a >= 1.0f) {
				m_fadeOut->GetComponent<SpriteRenderer>()->Color.a = 1.0f;
				m_fadeflg = false;
				m_nextWorldflg = false;
				GameEngine::SceneManager::LoadScene("World5StageSelectScene");
			}
		}
		else if (m_fadeflg == true && m_nextWorldflg == false) {
			if (m_fadeOut->GetComponent<SpriteRenderer>()->Color.a < 1.0f) {
				m_fadeOut->GetComponent<SpriteRenderer>()->Color.a += 0.03;
			}
			if (m_fadeOut->GetComponent<SpriteRenderer>()->Color.a >= 1.0f) {
				m_fadeOut->GetComponent<SpriteRenderer>()->Color.a = 1.0f;
				m_fadeflg = false;
				GameEngine::SceneManager::LoadScene("World3StageSelectScene");
			}
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
				if (m_inputflg == true) {
					GameEngine::SceneManager::LoadScene("Stage16");
				}
				break;
			case STAGE_02:
				GameEngine::SceneManager::LoadScene("Stage17");
				break;
			case STAGE_03:
				GameEngine::SceneManager::LoadScene("Stage18");
				break;
			case STAGE_04:
				GameEngine::SceneManager::LoadScene("Stage19");
				break;
			case STAGE_05:
				GameEngine::SceneManager::LoadScene("Stage20");
				break;
			}
		}
	}
	m_frameCnt++;
	SystemUpdate();
	return PLAY;
}

bool GamePlay::World4StageSelectScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	サウンドストップ	*/
	Sound::Sound_Stop(SOUND_LABEL_SELECT);

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::World4StageSelectScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	//自前の描画
	ObjectRender<Actor>("Select");
	ObjectRender<SelectTutorial>("SelectAnimation");
	ObjectRender<Actor>("WhiteOut");
	ObjectRender<SelectFade>("WhiteIn");

	/****	画面描画	****/
	SwapChain();
	return true;
}

void GamePlay::World4StageSelectScene::RightMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x < 3355.0f * stage) {
		camera->transform->Position.x += 33.0f * GameTimer::deltaTime();
		//誤差無くし
		if (camera->transform->Position.x >= 3355.0f * stage) {
			camera->transform->Position.x = 3355.0f * stage;

			m_sceneRightMoveflg = false;
		}
	}
}

void GamePlay::World4StageSelectScene::LeftMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x > 3355.0f * (stage - 1) - 3355.0f) {
		camera->transform->Position.x -= 33.0f * GameTimer::deltaTime();
		//誤差無くし
		if (camera->transform->Position.x <= 3355.0f * (stage - 1) - 3355.0f) {
			camera->transform->Position.x = 3355.0f * (stage - 1) - 3355.0f;

			m_sceneLeftMoveflg = false;
		}
	}
}
