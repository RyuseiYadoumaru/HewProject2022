#include "World1StageSelectScene.h"

using namespace Create;

bool GamePlay::World1StageSelectScene::Start()
{
	//�I�u�W�F�N�g���� ������
	//�t�F�[�h�C��
	m_fadeIn = Instance<SelectFade>("WhiteIn");

	//�t�F�[�h�A�E�g
	m_fadeOut = Instance<Actor>("WhiteOut");
	m_fadeOut->Sprite("white");
	m_fadeOut->Vertex("vs_Ui");
	m_fadeOut->transform->Position.Set(950.0f, 500.0f, 0.0f);
	m_fadeOut->transform->Scale.Set(1.5f, 1.0f, 1.0f);
	m_fadeOut->GetComponent<SpriteRenderer>()->Color.a = 0.0f;
	m_fadeflg = false;

	//�{�^���A�j���[�V����
	m_selectAnimation = Instance<SelectTutorial>("SelectAnimation");

	//�w�i�摜
	m_worldBack = Instance<Actor>("Select");
	m_worldBack->Sprite("world1");
	/*m_worldBack->transform->Scale.Set(0.48f, 0.475f, 0.45f);*/
	m_worldBack->transform->Scale.Set(2.01f, 2.0f, 0.45f);
	//1�̃m�C�Y�ړ�3355
	m_worldBack->transform->Position.Set(6710.0f, 0.0f, 0.0f);


	//�V�[���J��
	m_SceneTransition = Instance<SceneTransition>("Scene");

	//�X�e�[�W�ԍ�
	m_stageNumber = STAGE_01;

	SetCamera();
	camera->GetBackgroundColor()->Set(50.0f, 30.0f, 10.0f, 1.0f);
	camera->transform->Position.Set(0.0f, 0.0f, 0.0f);

	m_sceneRightMoveflg = false;
	m_sceneLeftMoveflg = false;
	m_inputflg = false;
	m_frameCnt = 0;

	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_SELECT);


	return true;
}

Scene::STATE GamePlay::World1StageSelectScene::Update()
{

	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	if (m_frameCnt >= 30) {
		m_inputflg = true;
	}

	/*	�^�C�g���ɖ߂�	*/
	if (Input::GetControllerTrigger(XInput::Buttom::B) == true || Input::GetKeyTrigger(PK_BS) == true)
	{
		SceneManager::LoadScene("TitleScene");
	}
	switch (m_stageNumber) {
	case STAGE_01:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//���E�L�[�Ŗ��L�[�摜�ړ�
			if (m_frameCnt >= 20) {
				m_sceneRightMoveflg = true;
				m_frameCnt = 0;
			}
		}

		if (Input::GetKeyTrigger(VK_LEFT) == true
			|| Input::GetControllerLeftStick().x < 0.0f) {
		}
		break;

	case STAGE_02:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//���E�L�[�Ŗ��L�[�摜�ړ�
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
			|| Input::GetControllerLeftStick().x > 0.0f) {//���E�L�[�Ŗ��L�[�摜�ړ�
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
			|| Input::GetControllerLeftStick().x > 0.0f) {//���E�L�[�Ŗ��L�[�摜�ړ�
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
			|| Input::GetControllerLeftStick().x > 0.0f) {//���E�L�[�Ŗ��L�[�摜�ړ�
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


	//�E�V�[���J��
	if (m_stageNumber == STAGE_01 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_01);
		/*world2�֑J��*/
		if (camera->transform->Position.x == 3355.0f) {
			m_stageNumber = STAGE_02;
		}
	}
	else if (m_stageNumber == STAGE_02 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_02);
		/*world3�֑J��*/
		if (camera->transform->Position.x == 6710.0f) {
			m_stageNumber = STAGE_03;
		}
	}
	else if (m_stageNumber == STAGE_03 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_03);
		//world4�֑J��
		if (camera->transform->Position.x == 10065.0f) {
			m_stageNumber = STAGE_04;
		}
	}
	else if (m_stageNumber == STAGE_04 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_04);
		//world5�֑J��
		if (camera->transform->Position.x == 13420.0f) {
			m_stageNumber = STAGE_05;
		}
	}

	//���V�[���J��
	if (m_stageNumber == STAGE_02 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_02);
		//world1�֑J��
		if (camera->transform->Position.x == 0.0f) {
			m_stageNumber = STAGE_01;
		}
	}
	else if (m_stageNumber == STAGE_03 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_03);
		//world2�֑J��
		if (camera->transform->Position.x == 3355.0f) {
			m_stageNumber = STAGE_02;
		}
	}
	else if (m_stageNumber == STAGE_04 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_04);
		//world3�֑J��
		if (camera->transform->Position.x == 6710.0f) {
			m_stageNumber = STAGE_03;
		}
	}
	else if (m_stageNumber == STAGE_05 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_05);
		//world4�ֈړ�
		if (camera->transform->Position.x == 10065.0f) {
			m_stageNumber = STAGE_04;
		}
	}

	//LB.RB�Ń��[���h�ړ�
	if (Input::GetKeyTrigger(PK_D) == true
		|| Input::GetControllerTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true) {
		SceneTransition::m_SceneTransitionFlg = true;
		m_fadeflg = true;
	}

	if (m_fadeflg == true) {
		if (m_fadeOut->GetComponent<SpriteRenderer>()->Color.a < 1.0f) {
			m_fadeOut->GetComponent<SpriteRenderer>()->Color.a += 0.03;
		}
		if (m_fadeOut->GetComponent<SpriteRenderer>()->Color.a >= 1.0f) {
			m_fadeOut->GetComponent<SpriteRenderer>()->Color.a = 1.0f;
			m_fadeflg = false;
			GameEngine::SceneManager::LoadScene("World2StageSelectScene");
		}
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true ||
		Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true)//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		switch (m_stageNumber)
		{
		case STAGE_01:
			if (m_inputflg == true) {
				GameEngine::SceneManager::LoadScene("Stage1");
			}
			break;
		case STAGE_02:
			GameEngine::SceneManager::LoadScene("Stage2");
			break;
		case STAGE_03:
			GameEngine::SceneManager::LoadScene("Stage3");
			break;
		case STAGE_04:
			GameEngine::SceneManager::LoadScene("Stage4");
			break;
		case STAGE_05:
			GameEngine::SceneManager::LoadScene("Stage5");
			break;
		}
	}

	std::cout << m_frameCnt << std::endl;
	m_frameCnt++;

	/****	�V�X�e���X�V	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::World1StageSelectScene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_SELECT);
	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::World1StageSelectScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	//���O�̕`��
	ObjectRender<Actor>("Select");
	ObjectRender<SelectTutorial>("SelectAnimation");
	ObjectRender<Actor>("WhiteOut");
	ObjectRender<SelectFade>("WhiteIn");

	//if (SceneTransition::m_SceneTransitionFlg == false) {
	//	ObjectRender<SceneTransition>("Scene");//�V�[���J�ڃA�j���[�V����
	//}


	/****	��ʕ`��	****/
	SwapChain();
	return true;
}

void GamePlay::World1StageSelectScene::RightMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x < 3355.0f * stage) {
		camera->transform->Position.x += 33.0f * GameTimer::deltaTime();
		//�덷������
		if (camera->transform->Position.x >= 3355.0f * stage) {
			camera->transform->Position.x = 3355.0f * stage;

			m_sceneRightMoveflg = false;
		}
	}
}

void GamePlay::World1StageSelectScene::LeftMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x > 3355.0f * (stage - 1) - 3355.0f) {
		camera->transform->Position.x -= 33.0f * GameTimer::deltaTime();
		//�덷������
		if (camera->transform->Position.x <= 3355.0f * (stage - 1) - 3355.0f) {
			camera->transform->Position.x = 3355.0f * (stage - 1) - 3355.0f;

			m_sceneLeftMoveflg = false;
		}
	}
}
