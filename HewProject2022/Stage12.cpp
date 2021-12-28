#include "Stage12.h"

using namespace Create;

bool GamePlay::Stage12Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage12 = make_shared<Actor>("Stage-02");
	m_world3 = make_shared<Actor>("World-03");
	m_stage12->Sprite("stage-02");
	m_world3->Sprite("world-03");

	Instance(m_stage12.get());
	Instance(m_world3.get());

	m_stage12->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world3->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage12Scene::Update()
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

bool GamePlay::Stage12Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage12Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage12->Render();
	m_world3->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
