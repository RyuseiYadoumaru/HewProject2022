#include "SelectScene.h"

using namespace Create;

GamePlay::SelectScene::SelectScene()
{
	m_1pageFlg = true;
}

bool GamePlay::SelectScene::Start()
{
	//�I�u�W�F�N�g���� ������

	//���L�[�摜
	m_button = make_shared<Actor>("SelectButton");
	m_button->Sprite("button");
	m_button->Start();
	m_button->transform->Scale.Set(0.5f, 0.5f, 0.5f);
	m_button->transform->Position.Set(-500.0f, 150.0f, 0.0f);

	//���[���h�摜
	//�z��ɂ�������`�`�`
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

	//�X�e�[�W�ԍ�
	m_worldNumber = WORLD_01;

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//���ꂶ��_���H
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

	//������艺�̏��������Ɨǂ�������
	//1�y�[�W��
	if (m_1pageFlg == true) {
		m_world_1->transform->Position.y = -200.0f;
		m_world_2->transform->Position.y = -200.0f;
		m_world_3->transform->Position.y = -200.0f;
		m_world_4->transform->Position.y = -800.0f;
		m_world_5->transform->Position.y = -800.0f;
		m_world_6->transform->Position.y = -800.0f;

		if (Input::GetKeyTrigger(VK_RIGHT) == true) {//���E�L�[�Ŗ��L�[�摜�ړ�
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
			//�y�[�W�ύX���buttom�ʒu
			m_button->transform->Position.x = -500.0f;
		}
	}

	else {
		//�y�[�W�ύX��
		//2�y�[�W��
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
			//�y�[�W�ύX���buttom�ʒu
			m_button->transform->Position.x = -500.0f;
		}
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����Ǝ��̃V�[���ֈړ�
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

		//world�Z���N�g1�y�[�W�ڂɖ߂�
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
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();
	return true;
}

bool GamePlay::SelectScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	//���O�̕`��
	m_world_1->Render();
	m_world_2->Render();
	m_world_3->Render();
	m_world_4->Render();
	m_world_5->Render();
	m_world_6->Render();


	m_button->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}