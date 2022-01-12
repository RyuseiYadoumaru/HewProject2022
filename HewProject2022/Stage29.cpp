#include "Stage29.h"

using namespace Create;

bool GamePlay::Stage29Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage29 = make_shared<Actor>("Stage-04");
	m_world6 = make_shared<Actor>("World-06");
	m_stage29->Sprite("stage-04");
	m_world6->Sprite("world-06");

	OldInstance(m_stage29.get());
	OldInstance(m_world6.get());

	m_stage29->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world6->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage29Scene::Update()
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

bool GamePlay::Stage29Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage29Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage29->Render();
	m_world6->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
