#include "Stage30.h"

using namespace Create;

bool GamePlay::Stage30Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage30 = make_shared<Actor>("Stage-05");
	m_world6 = make_shared<Actor>("World-06");
	m_stage30->Sprite("stage-05");
	m_world6->Sprite("world-06");

	Instance(m_stage30.get());
	Instance(m_world6.get());

	m_stage30->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world6->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage30Scene::Update()
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

bool GamePlay::Stage30Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage30Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage30->Render();
	m_world6->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
