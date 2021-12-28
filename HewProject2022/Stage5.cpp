#include "Stage5.h"

using namespace Create;

bool GamePlay::Stage5Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage5 = make_shared<Actor>("Stage-05");
	m_world1 = make_shared<Actor>("World-01");
	m_stage5->Sprite("stage-05");
	m_world1->Sprite("world-01");

	Instance(m_stage5.get());
	Instance(m_world1.get());

	m_stage5->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world1->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage5Scene::Update()
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

bool GamePlay::Stage5Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage5Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage5->Render();
	m_world1->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}