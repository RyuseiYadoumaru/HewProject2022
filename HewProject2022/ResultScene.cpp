#include "ResultScene.h"

using namespace Create;

bool GamePlay::ResultScene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_ResultText = make_shared<Actor>("ResultText");
	m_ResultText->Sprite("���U���g");
	m_ResultText->Start();

	//camera = make_shared<Camera>("MainCamera");
	SetCamera();//���ꂶ��_���H
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);
	for (auto i : ObjectArray)
	{
		i.second->Start();
	}
	return true;
}

Scene::STATE GamePlay::ResultScene::Update()
{
	camera->Update();



	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����ƃ^�C�g���ɖ߂�
	{
		GameEngine::SceneManager::LoadScene("TitleScene");
	}

	return PLAY;
}

bool GamePlay::ResultScene::End()
{
	/****	��΂���	****/
	for (auto i : ObjectArray)
	{
		i.second->End();
	}
	ObjectArray.clear();
	return true;
}

bool GamePlay::ResultScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	//Hanamaru->Render();
	m_ResultText->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}