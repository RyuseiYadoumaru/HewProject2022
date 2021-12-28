#include "Stage21.h"

using namespace Create;

bool GamePlay::Stage21Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage21 = make_shared<Actor>("Stage-01");
	m_world5 = make_shared<Actor>("World-05");
	m_stage21->Sprite("stage-01");
	m_world5->Sprite("world-05");

	Instance(m_stage21.get());
	Instance(m_world5.get());

	m_stage21->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world5->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage21Scene::Update()
{
	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();


	/****	���[�h�V�[��	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_B))//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	�V�X�e���X�V	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage21Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage21Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage21->Render();
	m_world5->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
