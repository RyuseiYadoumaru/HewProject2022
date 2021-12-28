#include "Stage2.h"

using namespace Create;

bool GamePlay::Stage2Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage2 = make_shared<Actor>("Stage-02");
	m_world1 = make_shared<Actor>("World-01");
	m_stage2->Sprite("stage-02");
	m_world1->Sprite("world-01");

	Instance(m_stage2.get());
	Instance(m_world1.get());

	m_stage2->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world1->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage2Scene::Update()
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

bool GamePlay::Stage2Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage2Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage2->Render();
	m_world1->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}