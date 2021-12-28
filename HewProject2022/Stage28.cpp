#include "Stage28.h"

using namespace Create;

bool GamePlay::Stage28Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage28 = make_shared<Actor>("Stage-03");
	m_world6 = make_shared<Actor>("World-06");
	m_stage28->Sprite("stage-03");
	m_world6->Sprite("world-06");

	Instance(m_stage28.get());
	Instance(m_world6.get());

	m_stage28->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world6->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage28Scene::Update()
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

bool GamePlay::Stage28Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage28Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage28->Render();
	m_world6->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
