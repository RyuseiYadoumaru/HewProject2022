#include "StageTestScene.h"

bool StageTestScene::Start()
{
	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>();
	m_Test = make_shared<GamePlay::Test>("Hanamaru");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");

	/*	�I�u�W�F�N�g������	*/
	m_Test->transform.Scale.Set(0.2f, 0.1f, 0);
	m_Map->Start();
	m_Test->Start();
	m_BackGruond->Start();

	/*	�J�����Z�b�g	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->BackgroundColor = Math::Color::Blue;
	m_MainCamera->Focus(m_Test.get());
	return true;
}

Scene::STATE StageTestScene::Update()
{

	/*	�u���b�N����	*/
	if (Input::GetKeyTrigger(PK_ENTER) == true)
	{
		//���������Ă͂܂����Ƃ��A�u���b�N������


	}

	m_Test->Update();
	m_Map->Update();
	m_BackGruond->Update();
	m_MainCamera->Update();

	return PLAY;
}

bool StageTestScene::End()
{
	return true;
}

bool StageTestScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�w�i	****/
	m_BackGruond->Render();

	/****	�e�X�g	****/
	m_Test->Render();

	/****	�}�b�v�`��	****/
	m_Map->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;

}