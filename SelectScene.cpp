#include "SelectScene.h"

using namespace Create;

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
	m_world_1->Sprite("world-01");
	m_world_2->Sprite("world-02");
	m_world_3->Sprite("world-03");
	m_world_1->Start();
	m_world_2->Start();
	m_world_3->Start();
	m_world_1->transform->Position.Set(-650.0f, -200.0f, 0.0f);
	m_world_2->transform->Position.Set(0.0f, -200.0f, 0.0f);
	m_world_3->transform->Position.Set(650.0f, -200.0f, 0.0f);

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

Scene::STATE GamePlay::SelectScene::Update()
{
	camera->Update();



	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	//������艺�̏��������Ɨǂ�������

	if (Input::GetKeyTrigger(VK_RIGHT) == true) {//���E�L�[�Ŗ��L�[�摜�ړ�
		m_button->transform->Position.x += 650.0f;
		m_stageNumber = STAGE_02;
		if (m_button->transform->Position.x >= 800.0f) {
			m_button->transform->Position.x = 800.0f;
			m_stageNumber = STAGE_03;
		}
	}
	if (Input::GetKeyTrigger(VK_LEFT) == true) {
		m_button->transform->Position.x -= 650.0f;
		m_stageNumber = STAGE_02;
		if (m_button->transform->Position.x <= -500.0f) {
			m_button->transform->Position.x = -500.0f;
			m_stageNumber = STAGE_01;
		}
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		switch (m_stageNumber)
		{
		case STAGE_01:
			GameEngine::SceneManager::LoadScene("ProtScene");
			break;
		case STAGE_02:
			GameEngine::SceneManager::LoadScene("ProtScene");
			break;
		case STAGE_03:
			GameEngine::SceneManager::LoadScene("ProtScene");
			break;
		}
	}

	m_button->transform->Update();

	m_world_1->transform->Update();
	m_world_2->transform->Update();
	m_world_3->transform->Update();

	return PLAY;
}

bool GamePlay::SelectScene::End()
{
	/****	��΂���	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();
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


	m_button->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}