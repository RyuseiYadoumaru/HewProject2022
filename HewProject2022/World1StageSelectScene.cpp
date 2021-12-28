#include "World1StageSelectScene.h"

using namespace Create;

bool GamePlay::World1StageSelectScene::Start()
{
	//�I�u�W�F�N�g���� ������

	//���L�[�摜
	m_button = make_shared<Actor>("SelectButton");
	m_button->Sprite("button");
	m_button->Start();
	m_button->transform->Scale.Set(0.5f, 0.5f, 0.5f);
	m_button->transform->Position.Set(-700.0f, 150.0f, 0.0f);

	//���[���h�摜
	//�z��ɂ�������`�`�`
	m_stage_1 = make_shared<Actor>("Stage-01");
	m_stage_2 = make_shared<Actor>("Stage-02");
	m_stage_3 = make_shared<Actor>("Stage-03");
	m_stage_4 = make_shared<Actor>("Stage-04");
	m_stage_5 = make_shared<Actor>("Stage-05");
	m_stage_1->Sprite("stage-01");
	m_stage_2->Sprite("stage-02");
	m_stage_3->Sprite("stage-03");
	m_stage_4->Sprite("stage-04");
	m_stage_5->Sprite("stage-05");
	m_stage_1->Start();
	m_stage_2->Start();
	m_stage_3->Start();
	m_stage_4->Start();
	m_stage_5->Start();
	m_stage_1->transform->Position.Set(-800.0f, 0.0f, 0.0f);
	m_stage_2->transform->Position.Set(-400.0f, 0.0f, 0.0f);
	m_stage_3->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_stage_4->transform->Position.Set(400.0f, 0.0f, 0.0f);
	m_stage_5->transform->Position.Set(800.0f, 0.0f, 0.0f);
	m_stage_4->transform->Scale.Set(1.0f, 1.0f, 1.0f);


	//�X�e�[�W�ԍ�
	m_stageNumber = STAGE_01;

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//���ꂶ��_���H
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	for (auto i : ObjectArray)
	{
		i.second->Start();
	}
	return true;
}

Scene::STATE GamePlay::World1StageSelectScene::Update()
{
	camera->Update();

	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	if (Input::GetKeyTrigger(VK_RIGHT) == true) {//���E�L�[�Ŗ��L�[�摜�ړ�
		m_button->transform->Position.x += 400.0f;
		if (m_button->transform->Position.x >= 900.0f) {
			m_button->transform->Position.x = 900.0f;
		}
	}
	if (Input::GetKeyTrigger(VK_LEFT) == true) {
		m_button->transform->Position.x -= 400.0f;
		if (m_button->transform->Position.x <= -700.0f) {
			m_button->transform->Position.x = -700.0f;
		}
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		if (m_button->transform->Position.x == -700.0f) {
			m_stageNumber = STAGE_01;
		}
		else if (m_button->transform->Position.x == -300.0f) {
			m_stageNumber = STAGE_02;
		}
		else if (m_button->transform->Position.x == 100.0f) {
			m_stageNumber = STAGE_03;
		}
		else if (m_button->transform->Position.x == 500.0f) {
			m_stageNumber = STAGE_04;
		}
		else if (m_button->transform->Position.x == 900.0f) {
			m_stageNumber = STAGE_05;
		}

		switch (m_stageNumber)
		{
		case STAGE_01:
			GameEngine::SceneManager::LoadScene("Stage1");
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

	m_button->transform->Update();

	m_stage_1->transform->Update();
	m_stage_2->transform->Update();
	m_stage_3->transform->Update();
	m_stage_4->transform->Update();
	m_stage_5->transform->Update();

	return PLAY;
}

bool GamePlay::World1StageSelectScene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::World1StageSelectScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	//���O�̕`��
	m_stage_1->Render();
	m_stage_2->Render();
	m_stage_3->Render();
	m_stage_4->Render();
	m_stage_5->Render();
	m_button->Render();

	/****	��ʕ`��	****/
	SwapChain();
	return true;
}