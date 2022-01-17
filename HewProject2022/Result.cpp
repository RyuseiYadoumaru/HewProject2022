#include "Result.h"

#define CURSOR_DISTANCE 100.0f			//カーソルの移動間隔
#define BASE_POSITION_X 1920.0f/2.0f
#define BASE_POSITION_Y 1080.0f/2.0f

Result::Result(string in_Name):Actor(in_Name)
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

	return true;
}

void Result::ResultBack_init()
{
	this->Sprite("result");
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(0.3, 0.3, 0);//スケールの書き換え
	this, transform->Position.y += 150;
}

void Result::ResultCursor_Init()
{
	this->Sprite("button");
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	this->transform->Scale.Set(1.2, 1.2, 0);//スケールの書き換え
}

bool Result::Result_On()
{
	Result_Checker = 0;
	this->GetComponent<SpriteRenderer>()->Color.a = 1;
	return true;
}

bool Result::ResultCursor_Move()
{
	this->GetComponent<SpriteRenderer>()->Color.a = 1.0f;

	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_UP) == true || Input::GetKeyTrigger(VK_UP) == true) && Cursor_Position > 0) {
		Cursor_Position--;
	}
	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true || Input::GetKeyTrigger(VK_DOWN) == true) && Cursor_Position < 2) {
		Cursor_Position++;
	}

	//選択肢による分岐
	switch (Cursor_Position) {
	case 0:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y - CURSOR_DISTANCE + 200, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_B) == true) {
			//Result_Checker = 1;//次のステージ
			this->ChangeNextScene();
		}
		break;
	case 1:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y + 200, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_B) == true) {
			//Result_Checker = 2;//初めからやり直す処理
			GameEngine::SceneManager::LoadScene(this->NowScene);//ステージセレクトに戻る
		}
		break;
	case 2:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y + CURSOR_DISTANCE + 200, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_B) == true) {
			//Result_Checker = 3;//ステージセレクトに戻る
			this->ChangeSelectScene();
		}
		break;
	default:
		break;
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
		GameEngine::SceneManager::LoadScene("World12StageSelectScene");//ワールド2ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage11" || this->NowScene == "Stage12" || this->NowScene == "Stage13" || this->NowScene == "Stage14" || this->NowScene == "Stage15") {
		GameEngine::SceneManager::LoadScene("World3StageSelectScene");//ワールド3ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage16" || this->NowScene == "Stage17" || this->NowScene == "Stage18" || this->NowScene == "Stage19" || this->NowScene == "Stage20") {
		GameEngine::SceneManager::LoadScene("World14StageSelectScene");//ワールド4ステージセレクトを読み込み
	}
	else if (this->NowScene == "Stage21" || this->NowScene == "Stage22" || this->NowScene == "Stage23" || this->NowScene == "Stage24" || this->NowScene == "Stage25") {
		GameEngine::SceneManager::LoadScene("World5StageSelectScene");//ワールド5ステージセレクトを読み込み
	}
}

