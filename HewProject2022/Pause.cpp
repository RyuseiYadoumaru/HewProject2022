#include "Pause.h"

#define CURSOR_DISTANCE 100.0f			//�J�[�\���̈ړ��Ԋu
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
	this->transform->Scale.Set(1.5f, 1.5f, 0.0f);//��{�X�P�[���̐ݒ�

	return true;
}

//�|�[�Y��ʕ\��
bool Pause::Pause_On()
{
	Pause_Checker = 0;
	this->GetComponent<SpriteRenderer>()->Color.a = 1;
	return true;
}

//�|�[�Y��ʔ�\��
bool Pause::Pause_Off() {
	this->GetComponent<SpriteRenderer>()->Color.a = 0;
	return true;
}

//�J�[�\���X�P�[���ύX�p
bool Pause::SetScale()
{
	this->transform->Scale.Set(0.6f, 0.6f, 0.0f);
	return true;
}

bool Pause::PauseCursor_Move()
{
	//this->Sprite("button_2");
	this->transform->Scale.Set(0.2f, 0.2f, 0.0f);//�J�[�\���p�ɃX�P�[���̏�������

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

	//�I�����ɂ�镪��
	switch (Cursor_Position) {
	case 0:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y - CURSOR_DISTANCE + 100, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			//Pause_Checker = 2;
			Sound::Sound_Play(SOUND_LABEL_OK);
			GameEngine::SceneManager::LoadScene(this->NowScene);//���߂����蒼������
		}
		break;
	case 1:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y + 100, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			Sound::Sound_Play(SOUND_LABEL_BACK);
			Pause_Checker = 1;//�Q�[���ɖ߂�i�|�[�Y�I���j
		}
		break;
	case 2:
		this->transform->Position.Set(BASE_POSITION_X - 170, BASE_POSITION_Y + CURSOR_DISTANCE + 100, 0.0f);
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true) {
			//Pause_Checker = 3;//�X�e�[�W�Z���N�g�ɖ߂�
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
		GameEngine::SceneManager::LoadScene("World1StageSelectScene");//���[���h1�X�e�[�W�Z���N�g��ǂݍ���
	}
	else if (this->NowScene == "Stage6" || this->NowScene == "Stage7" || this->NowScene == "Stage8" || this->NowScene == "Stage9" || this->NowScene == "Stage10") {
		GameEngine::SceneManager::LoadScene("World2StageSelectScene");//���[���h2�X�e�[�W�Z���N�g��ǂݍ���
	}
	else if (this->NowScene == "Stage11" || this->NowScene == "Stage12" || this->NowScene == "Stage13" || this->NowScene == "Stage14" || this->NowScene == "Stage15") {
		GameEngine::SceneManager::LoadScene("World3StageSelectScene");//���[���h3�X�e�[�W�Z���N�g��ǂݍ���
	}
	else if (this->NowScene == "Stage16" || this->NowScene == "Stage17" || this->NowScene == "Stage18" || this->NowScene == "Stage19" || this->NowScene == "Stage20") {
		GameEngine::SceneManager::LoadScene("World4StageSelectScene");//���[���h4�X�e�[�W�Z���N�g��ǂݍ���
	}
	else if (this->NowScene == "Stage21" || this->NowScene == "Stage22" || this->NowScene == "Stage23" || this->NowScene == "Stage24" || this->NowScene == "Stage25") {
		GameEngine::SceneManager::LoadScene("World5StageSelectScene");//���[���h5�X�e�[�W�Z���N�g��ǂݍ���
	}
}


