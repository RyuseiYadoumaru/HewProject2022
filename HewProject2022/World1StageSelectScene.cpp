#include "World1StageSelectScene.h"

using namespace Create;

bool GamePlay::World1StageSelectScene::Start()
{
	//�I�u�W�F�N�g���� ������
	//�t�F�[�h
	m_fade = Instance<SelectFade>("White");
	m_fadeflg = false;

	//�{�^���A�j���[�V����
	m_selectAnimation = Instance<SelectTutorial>("SelectAnimation");

	//�w�i�摜
	m_worldBack = Instance<Actor>("Select");
	m_worldBack->Sprite("select");
	//m_worldBack->transform->Scale.Set(0.5f, 0.5f, 0.5f);
	m_worldBack->transform->Scale.Set(0.49f, 0.49f, 0.49f);//�g�c�K�C�����̃T�C�Y�Ƃ��ς��Ĕw�i�m�C�Y���������ɂ��ā[

	//1�̃m�C�Y�ړ�3500
	m_worldBack->transform->Position.Set(7000.0f, 0.0f, 0.0f);

	//Ui
	m_selectUi = Instance<Actor>("SelectUI");
	m_selectUi->Sprite("selectUI");
	m_selectUi->Vertex("vs_Ui");
	m_selectUi->transform->Position.Set(960.0f, 550.0f, 0.0f);
	m_selectUi->transform->Scale.Set(0.5f, 0.5f, 0.0f);

	//���[���h�摜
	//�z��ɂ�������`�`�`
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

	//�V�[���J��
	m_SceneTransition = Instance<SceneTransition>("Scene");

	//�X�e�[�W�ԍ�
	m_stageNumber = STAGE_01;

	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	camera->transform->Position.Set(0.0f, 0.0f, 0.0f);

	m_sceneRightMoveflg = false;
	m_sceneLeftMoveflg = false;
	m_inputflg = true;
	m_frameCnt = 0;

	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_SELECT);


	return true;
}

Scene::STATE GamePlay::World1StageSelectScene::Update()
{

	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	/*	�^�C�g���ɖ߂�	*/
	if (Input::GetControllerTrigger(XInput::Buttom::B) == true)
	{
		SceneManager::LoadScene("TitleScene");
	}
	switch (m_stageNumber) {
	case STAGE_01:
		if (Input::GetKeyTrigger(VK_RIGHT) == true
			|| Input::GetControllerLeftStick().x > 0.0f) {//���E�L�[�Ŗ��L�[�摜�ړ�
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
		if (camera->transform->Position.x == 3500.0f) {
			m_stageNumber = STAGE_02;
		}
	}
	else if (m_stageNumber == STAGE_02 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_02);
		/*world3�֑J��*/
		if (camera->transform->Position.x == 7000.0f) {
			m_stageNumber = STAGE_03;
		}
	}
	else if (m_stageNumber == STAGE_03 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_03);
		//world4�֑J��
		if (camera->transform->Position.x == 10500.0f) {
			m_stageNumber = STAGE_04;
		}
	}
	else if (m_stageNumber == STAGE_04 && m_sceneRightMoveflg == true) {
		RightMove(STAGE_04);
		//world5�֑J��
		if (camera->transform->Position.x == 14000.0f) {
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
		if (camera->transform->Position.x == 3500.0f) {
			m_stageNumber = STAGE_02;
		}
	}
	else if (m_stageNumber == STAGE_04 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_04);
		//world3�֑J��
		if (camera->transform->Position.x == 7000.0f) {
			m_stageNumber = STAGE_03;
		}
	}
	else if (m_stageNumber == STAGE_05 && m_sceneLeftMoveflg == true) {
		LeftMove(STAGE_05);
		//world4�ֈړ�
		if (camera->transform->Position.x == 10500.0f) {
			m_stageNumber = STAGE_04;
		}
	}

	//LB.RB�Ń��[���h�ړ�
	if (Input::GetKeyTrigger(PK_D) == true
		|| Input::GetControllerTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true) {
		GameEngine::SceneManager::LoadScene("World2StageSelectScene");
	}

	if (Input::GetKeyTrigger(PK_A) == true
		|| Input::GetControllerTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER) == true) {
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

	if (m_fadeflg == true) {
		m_fade->SetFadeStatus(m_fade->FADE_OUT);
		int gomi;
		gomi = m_fade->GetFadeStatus();
		m_fade->Update();
		m_fadeflg = false;
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
	ObjectRender<SelectTutorial>("SelectAnimation");
	ObjectRender<Actor>("Stage-01");
	ObjectRender<Actor>("Stage-02");
	ObjectRender<Actor>("Stage-03");
	ObjectRender<Actor>("Stage-04");
	ObjectRender<Actor>("Stage-05");
	ObjectRender<Actor>("Select");
	ObjectRender<SelectTutorial>("SelectAnimation");
	ObjectRender<Actor>("SelectUI");
	ObjectRender<SelectFade>("White");

	//if (SceneTransition::m_SceneTransitionFlg == false) {
	//	ObjectRender<SceneTransition>("Scene");//�V�[���J�ڃA�j���[�V����
	//}


	/****	��ʕ`��	****/
	SwapChain();
	return true;
}

void GamePlay::World1StageSelectScene::RightMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x < 3500.0f * stage) {
		camera->transform->Position.x += 35.0f * GameTimer::deltaTime();
		//�덷������
		if (camera->transform->Position.x >= 3500.0f * stage) {
			camera->transform->Position.x = 3500.0f * stage;

			m_sceneRightMoveflg = false;
		}
	}
}

void GamePlay::World1StageSelectScene::LeftMove(STAGE_NUMBER stage)
{
	if (camera->transform->Position.x > 3500.0f * (stage - 1) - 3500.0f) {
		camera->transform->Position.x -= 35.0f * GameTimer::deltaTime();
		//�덷������
		if (camera->transform->Position.x <= 3500.0f * (stage - 1) - 3500.0f) {
			camera->transform->Position.x = 3500.0f * (stage - 1) - 3500.0f;

			m_sceneLeftMoveflg = false;
		}
	}
}
