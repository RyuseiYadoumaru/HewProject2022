#include "ResultScene.h"

using namespace Create;

bool GamePlay::ResultScene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_ResultText = Instance<Actor>("ResultText");
	m_ResultText->Sprite("congratulations");
	m_ResultText->Vertex("vs_Ui");
	m_ResultText->transform->Position.Set(1920 / 2,(1080 / 2) - 300, 0);

	m_Cursor = Instance<Result>("Cursor");
	m_Cursor->Sprite("button");
	//m_Cursor->transform->Scale.Set(1.2, 1.2, 0);

	m_BackGround = Instance<BackGround>("BackGround");
	m_BackGround->Sprite("Aquarium");
	m_BackGround->Vertex("vs_Ui");
	m_BackGround->transform->Position.Set(0, 0, 0);
	m_BackGround->transform->Scale.Set(8, 8, 1);
	m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 1;

	/*	�J����	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::ResultScene::Update()
{
	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();
	//m_Cursor->ResultCursor_Move();

	

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
	m_BackGround->Render();
	m_ResultText->Render();
	//m_Cursor->Render();
	ObjectRender<Result>("Cursor");
	

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}