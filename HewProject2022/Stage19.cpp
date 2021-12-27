#include "Stage19.h"

using namespace Create;

bool GamePlay::Stage19Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage19 = make_shared<Actor>("Stage-04");
	m_world4 = make_shared<Actor>("World-04");
	m_stage19->Sprite("stage-04");
	m_world4->Sprite("world-04");

	Instance(m_stage19.get());
	Instance(m_world4.get());

	m_stage19->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world4->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage19Scene::Update()
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

bool GamePlay::Stage19Scene::End()
{
	/****	��΂���	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();

	return true;
}

bool GamePlay::Stage19Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage19->Render();
	m_world4->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}