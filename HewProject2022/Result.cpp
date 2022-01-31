#include "Result.h"
#include "Fade.h"
#include "Player.h"

#define CURSOR_DISTANCE 130.0f			//カーソルの移動間隔
#define BASE_POSITION_X 1920.0f/2.0f
#define BASE_POSITION_Y 1080.0f/2.0f

Result::Result(string in_Name) :Actor(in_Name)
{
}

bool Result::Start()
{
	m_SpriteRenderer->Init();
	//Result_Checker = 0;
	//Cursor_Position = 0;


	this->Vertex("vs_Ui");
	this->transform->Position.Set(BASE_POSITION_X, BASE_POSITION_Y, 0);
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(1.0f, 1.0f, 0.0f);//基本スケールの設定

	m_SceneTransition = NONE;

	S_flg = false;

	m_ShootingStarSE = false;

	return true;
}

void Result::ResultFront_init()
{
	this->Sprite("ResultFront");
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(1.5f, 1.5f, 0);//スケールの書き換え
	//this, transform->Position.y += 150;
}

void Result::ResultFront_init_GameEnd()
{
	this->Sprite("ResultFrontEnd");
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(1.5f, 1.5f, 0);//スケールの書き換え
	//this, transform->Position.y += 150;
}

void Result::ResultBack_init()
{
	this->Sprite("ResultBack");
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(1.5f, 1.5f, 0);//スケールの書き換え
}

void Result::ResultCursor_Init()
{
	Result_Checker = 0;
	this->Sprite("button_2");
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(0.2f, 0.2f, 0.0f);//スケールの書き換え
}

bool Result::Result_On()
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	if (m_ShootingStarSE == false && m_Player->m_GetStar != 0) {//流れ星SE
		Sound::Sound_Play(SOUND_LABEL_SHOOTINGSTAR);
		m_ShootingStarSE = true;
	}

	this->GetComponent<SpriteRenderer>()->Color.a = 1;
	return true;
}

bool Result::ResultCursor_Move()
{
	Fade* m_Fade = Create::Scene::GetGameObject<Fade>("Black");

	this->GetComponent<SpriteRenderer>()->Color.a = 1.0f;

	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_UP) == true || Input::GetKeyTrigger(VK_UP) == true) && Cursor_Position > 0) {
		Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);
		Cursor_Position--;
	}
	else if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true || Input::GetKeyTrigger(VK_DOWN) == true) && Cursor_Position < 2) {
		Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

		Cursor_Position++;
	}
	else if (Input::GetControllerLeftStick().y < -0.1) {
		if (S_flg == false) {
			Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

			Cursor_Position--;
			S_flg = true;
		}
	}
	else if (Input::GetControllerLeftStick().y > 0.1) {
		if (S_flg == false) {
			Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);

			Cursor_Position++;
			S_flg = true;
		}
	}
	else if (Input::GetControllerLeftStick().y == 0.0) {
		S_flg = false;
	}



	//選択肢による分岐
	switch (Cursor_Position) {
	case 0:
		this->transform->Position.Set(BASE_POSITION_X - 210, BASE_POSITION_Y - CURSOR_DISTANCE + 270, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			Sound::Sound_Play(SOUND_LABEL_OK);
			//Result_Checker = 1;//次のステージ
			m_Fade->SetFadeStatus(m_Fade->FADE_OUT);//フェードアウト開始
			m_SceneTransition = NEXT_SCENE;
			//this->ChangeNextScene();
		}
		break;
	case 1:
		this->transform->Position.Set(BASE_POSITION_X - 210, BASE_POSITION_Y + 270, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			Sound::Sound_Play(SOUND_LABEL_OK);
			//Result_Checker = 2;
			//m_Fade->SetFadeStatus(m_Fade->FADE_OUT);//フェードアウト開始
			m_Fade->fadeStatus = m_Fade->FADE_OUT;
			m_SceneTransition = RETRY;
			//GameEngine::SceneManager::LoadScene(this->NowScene);//やり直す
		}
		break;
	case 2:
		this->transform->Position.Set(BASE_POSITION_X - 210, BASE_POSITION_Y + CURSOR_DISTANCE + 270, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			Sound::Sound_Play(SOUND_LABEL_OK);
			//Result_Checker = 3;//ステージセレクトに戻る
			m_Fade->SetFadeStatus(m_Fade->FADE_OUT);//フェードアウト開始
			m_SceneTransition = STAGE_SELECT;
			//this->ChangeSelectScene();
		}
		break;
	default:
		break;
	}

	if (m_Fade->GetFadeStatus() == m_Fade->FADE_NO) {//フェードアウト終了するまで画面遷移しない
		switch (m_SceneTransition)
		{
		case NONE:
			break;

		case STAGE_SELECT:
			this->ChangeSelectScene();
			break;

		case RETRY:
			GameEngine::SceneManager::LoadScene(this->NowScene);
			break;

		case NEXT_SCENE:
			this->ChangeNextScene();
			break;

		default:
			break;
		}
	}
	this->transform->Update();
	return true;
}

int Result::Get_Checker()
{
	return  Result_Checker;
}

void Result::ChangeNextScene()
{

	if (this->NowScene == "Stage1" || this->NowScene == "Stage2" || this->NowScene == "Stage3" || this->NowScene == "Stage4" || this->NowScene == "Stage5") {
		if (this->NowScene == "Stage1") {
			GameEngine::SceneManager::LoadScene("Stage2");
		}
		else if (this->NowScene == "Stage2") {
			GameEngine::SceneManager::LoadScene("Stage3");
		}
		else if (this->NowScene == "Stage3") {
			GameEngine::SceneManager::LoadScene("Stage4");
		}
		else if (this->NowScene == "Stage4") {
			GameEngine::SceneManager::LoadScene("Stage5");
		}
		else if (this->NowScene == "Stage5") {
			GameEngine::SceneManager::LoadScene("Stage6");
		}
	}
	else if (this->NowScene == "Stage6" || this->NowScene == "Stage7" || this->NowScene == "Stage8" || this->NowScene == "Stage9" || this->NowScene == "Stage10") {
		if (this->NowScene == "Stage6") {
			GameEngine::SceneManager::LoadScene("Stage7");
		}
		else if (this->NowScene == "Stage7") {
			GameEngine::SceneManager::LoadScene("Stage8");
		}
		else if (this->NowScene == "Stage8") {
			GameEngine::SceneManager::LoadScene("Stage9");
		}
		else if (this->NowScene == "Stage9") {
			GameEngine::SceneManager::LoadScene("Stage10");
		}
		else if (this->NowScene == "Stage10") {
			GameEngine::SceneManager::LoadScene("Stage11");
		}
	}
	else if (this->NowScene == "Stage11" || this->NowScene == "Stage12" || this->NowScene == "Stage13" || this->NowScene == "Stage14" || this->NowScene == "Stage15") {
		if (this->NowScene == "Stage11") {
			GameEngine::SceneManager::LoadScene("Stage12");
		}
		else if (this->NowScene == "Stage12") {
			GameEngine::SceneManager::LoadScene("Stage13");
		}
		else if (this->NowScene == "Stage13") {
			GameEngine::SceneManager::LoadScene("Stage14");
		}
		else if (this->NowScene == "Stage14") {
			GameEngine::SceneManager::LoadScene("Stage15");
		}
		else if (this->NowScene == "Stage15") {
			GameEngine::SceneManager::LoadScene("Stage16");
		}
	}
	else if (this->NowScene == "Stage16" || this->NowScene == "Stage17" || this->NowScene == "Stage18" || this->NowScene == "Stage19" || this->NowScene == "Stage20") {
		if (this->NowScene == "Stage16") {
			GameEngine::SceneManager::LoadScene("Stage17");
		}
		else if (this->NowScene == "Stage17") {
			GameEngine::SceneManager::LoadScene("Stage18");
		}
		else if (this->NowScene == "Stage18") {
			GameEngine::SceneManager::LoadScene("Stage19");
		}
		else if (this->NowScene == "Stage19") {
			GameEngine::SceneManager::LoadScene("Stage20");
		}
		else if (this->NowScene == "Stage20") {
			GameEngine::SceneManager::LoadScene("Stage21");
		}
	}
	else if (this->NowScene == "Stage21" || this->NowScene == "Stage22" || this->NowScene == "Stage23" || this->NowScene == "Stage24" || this->NowScene == "Stage25") {
		if (this->NowScene == "Stage21") {
			GameEngine::SceneManager::LoadScene("Stage22");
		}
		else if (this->NowScene == "Stage22") {
			GameEngine::SceneManager::LoadScene("Stage23");
		}
		else if (this->NowScene == "Stage23") {
			GameEngine::SceneManager::LoadScene("Stage24");
		}
		else if (this->NowScene == "Stage24") {
			GameEngine::SceneManager::LoadScene("Stage25");
		}
		else if (this->NowScene == "Stage25") {
			GameEngine::SceneManager::LoadScene("TitleScene");
		}
	}

}

void Result::ChangeSelectScene()
{

	if (this->NowScene == "Stage1" || this->NowScene == "Stage2" || this->NowScene == "Stage3" || this->NowScene == "Stage4" || this->NowScene == "Stage5") {
		GameEngine::SceneManager::LoadScene("World1StageSelectScene");//ワールド1ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage6" || this->NowScene == "Stage7" || this->NowScene == "Stage8" || this->NowScene == "Stage9" || this->NowScene == "Stage10") {
		GameEngine::SceneManager::LoadScene("World2StageSelectScene");//ワールド2ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage11" || this->NowScene == "Stage12" || this->NowScene == "Stage13" || this->NowScene == "Stage14" || this->NowScene == "Stage15") {
		GameEngine::SceneManager::LoadScene("World3StageSelectScene");//ワールド3ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage16" || this->NowScene == "Stage17" || this->NowScene == "Stage18" || this->NowScene == "Stage19" || this->NowScene == "Stage20") {
		GameEngine::SceneManager::LoadScene("World4StageSelectScene");//ワールド4ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage21" || this->NowScene == "Stage22" || this->NowScene == "Stage23" || this->NowScene == "Stage24" || this->NowScene == "Stage25") {
		GameEngine::SceneManager::LoadScene("World5StageSelectScene");//ワールド5ステージセレクトを読み込み
	}
}


