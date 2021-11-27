#include "TitleScene.h"

using namespace Create;

bool GamePlay::TitleScene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_TitleText = make_shared<Actor>("TitleText");
	m_TitleText->Sprite("�^�C�g��");
	m_TitleText->Start();

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//���ꂶ��_���H
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	for (auto i : ObjectArray)
	{
		i.second->Start();
	}
	return true;
}

Scene::STATE GamePlay::TitleScene::Update()
{
	camera->Update();



	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		GameEngine::SceneManager::LoadScene("StageTestScene");
	}

	return PLAY;
}

bool GamePlay::TitleScene::End()
{
	/****	��΂���	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();
	return true;
}

bool GamePlay::TitleScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	//Hanamaru->Render();
	m_TitleText->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}