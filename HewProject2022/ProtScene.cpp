#include "ProtScene.h"

using namespace GamePlay;
/****	������	****/
bool ProtScene::Start()
{
	cout << "�v���g�^�C�v�V�[��" << endl;
	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>();
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");

	Instance(m_Player.get());
	Instance(m_Map.get());
	Instance(m_BackGruond.get());
	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	/*�@BG�l�Đ��@*/
	Sound::Sound_Play(SOUND_LABEL_BGM000);

	return true;
}

/****	�X�V	****/
Scene::STATE ProtScene::Update()
{
	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	/****	�u���b�N�ړ�	****/
	if (Input::GetKeyTrigger(PK_1))
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[24].mp_Column[0];
		m_Map->MoveMap(Debug);
	}

	/*	�u���b�N����	*/
	if (Input::GetKeyTrigger(PK_3) == true && m_Map->GetisMove() == false)
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[23].mp_Column[0];
		m_Map->MoveMap(Debug);
	}

	/****	���[�h�V�[��	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	�}�b�v�����蔻��	****/
	m_Map->HitCheckMap(*m_Player);

	/****	�V�X�e���X�V	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;
}

/****	�I������	****/
bool ProtScene::End()
{
	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_BGM000);

	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool ProtScene::Render()
{

	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_BackGruond->Render();
	m_Player->Render();
	m_Map->Render();

	/****	�R���C�_�`��	****/
	//m_Map->DebugCollider();
	m_Player->Debug();
	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
