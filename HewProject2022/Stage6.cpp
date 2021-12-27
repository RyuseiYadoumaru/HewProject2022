#include "Stage6.h"

using namespace Create;

bool GamePlay::Stage6Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage6 = make_shared<Actor>("Stage-01");
	m_world2 = make_shared<Actor>("World-02");
	m_stage6->Sprite("stage-01");
	m_world2->Sprite("world-02");

	Instance(m_stage6.get());
	Instance(m_world2.get());

	m_stage6->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world2->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage6Scene::Update()
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

bool GamePlay::Stage6Scene::End()
{
	/****	��΂���	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();

	return true;
}

bool GamePlay::Stage6Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage6->Render();
	m_world2->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}