#include "Stage13.h"

using namespace Create;

bool GamePlay::Stage13Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage13 = make_shared<Actor>("Stage-03");
	m_world3 = make_shared<Actor>("World-03");
	m_stage13->Sprite("stage-03");
	m_world3->Sprite("world-03");

	Instance(m_stage13.get());
	Instance(m_world3.get());

	m_stage13->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world3->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage13Scene::Update()
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

bool GamePlay::Stage13Scene::End()
{
	/****	��΂���	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();

	return true;
}

bool GamePlay::Stage13Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage13->Render();
	m_world3->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
