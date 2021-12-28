#include "Stage16.h"

using namespace Create;

bool GamePlay::Stage16Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage16 = make_shared<Actor>("Stage-01");
	m_world4 = make_shared<Actor>("World-04");
	m_stage16->Sprite("stage-01");
	m_world4->Sprite("world-04");

	Instance(m_stage16.get());
	Instance(m_world4.get());

	m_stage16->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world4->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage16Scene::Update()
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

bool GamePlay::Stage16Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage16Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage16->Render();
	m_world4->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
