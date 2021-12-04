#include "ResultScene.h"

using namespace Create;

bool GamePlay::ResultScene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_ResultText = make_shared<Actor>("ResultText");
	m_ResultText->Sprite("���U���g");
	Instance(m_ResultText.get());

	/*	�J����	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::ResultScene::Update()
{
	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����ƃ^�C�g���ɖ߂�
	{
		GameEngine::SceneManager::LoadScene("TitleScene");
	}

	/****	�V�X�e���X�V	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::ResultScene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();
	return true;
}

bool GamePlay::ResultScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_ResultText->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}