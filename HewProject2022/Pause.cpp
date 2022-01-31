#include "Pause.h"

#define CURSOR_DISTANCE 100.0f			//カーソルの移動間隔
#define BASE_POSITION_X 1920.0f/2.0f
#define BASE_POSITION_Y 1080.0f/2.0f

Pause::Pause(string in_Name) : Actor(in_Name)
{

}

bool Pause::Start()
{
	m_SpriteRenderer->Init();
	Cursor_Position = 0;
	Pause_Checker = 0;

	this->Vertex("vs_Ui");
	this->transform->Position.Set(BASE_POSITION_X, BASE_POSITION_Y, 0);
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(1.5f, 1.5f, 0.0f);//基本スケールの設定

	return true;
}

//ポーズ画面表示
bool Pause::Pause_On()
{
	Pause_Checker = 0;
	this->GetComponent<SpriteRenderer>()->Color.a = 1;
	return true;
}

//ポーズ画面非表示
bool Pause::Pause_Off() {
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	return true;
}

//カーソルスケール変更用
bool Pause::SetScale()
{
	this->transform->Scale.Set(0.6f, 0.6f, 0.0f);
	return true;
}

bool Pause::PauseCursor_Move()
{
	//this->Sprite("button_2");
	this->transform->Scale.Set(0.2f, 0.2f, 0.0f);//カーソル用にスケールの書き換え

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
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y - CURSOR_DISTANCE + 100, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			//Pause_Checker = 2;
			Sound::Sound_Play(SOUND_LABEL_OK);
			GameEngine::SceneManager::LoadScene(this->NowScene);//初めからやり直す処理
		}
		break;
	case 1:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y + 100, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			Sound::Sound_Play(SOUND_LABEL_BACK);
			Pause_Checker = 1;//ゲームに戻る（ポーズ終了）
		}
		break;
	case 2:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y + CURSOR_DISTANCE + 100, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			//Pause_Checker = 3;//ステージセレクトに戻る
			Sound::Sound_Play(SOUND_LABEL_OK);
			this->ChangeSelectScene();
		}
		break;
	default:
		break;
	}
	this->transform->Update();
	return true;
}

int Pause::Get_Checker()
{
	return Pause_Checker;
}

void Pause::ChangeSelectScene()
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


