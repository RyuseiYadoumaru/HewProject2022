#include "StageTestScene.h"

bool StageTestScene::Start()
{
	cout << "�X�e�[�W�e�X�g�V�[��" << endl;
	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>();
	m_ProtPlayer = make_shared<Player>("ProtPlayer");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");

	/*	�I�u�W�F�N�g������	*/
	m_Map->Start();
	m_ProtPlayer->Start();
	m_BackGruond->Start();

	/*	�J�����Z�b�g	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->BackgroundColor = Math::Color::Blue;
	//m_MainCamera->Focus(m_ProtPlayer.get());

	/*�@BG�l�Đ��@*/
	Sound::Sound_Play(SOUND_LABEL_BGM000);

	return true;
}

Scene::STATE StageTestScene::Update()
{

	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����ƃ^�C�g���ɖ߂�
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	m_ProtPlayer->Update();
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
	m_ProtPlayer->Render();

	/****	�}�b�v�`��	****/
	m_Map->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;

}