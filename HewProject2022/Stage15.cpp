#include "Stage15.h"

using namespace Create;

bool GamePlay::Stage15Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage15 = make_shared<Actor>("Stage-05");
	m_world3 = make_shared<Actor>("World-03");
	m_stage15->Sprite("stage-05");
	m_world3->Sprite("world-03");

	Instance(m_stage15.get());
	Instance(m_world3.get());

	m_stage15->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world3->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage15Scene::Update()
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

bool GamePlay::Stage15Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage15Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage15->Render();
	m_world3->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
