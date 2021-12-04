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


	/****	�}�b�v�����蔻��	****/
	m_Map->HitCheckMap(*m_Player);

	/****	�V�X�e���X�V	****/
	SystemUpdate();
	return PLAY;
}

/****	�I������	****/
bool ProtScene::End()
{
	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_BGM000);
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
	m_Map->DebugCollider();
	m_Player->Debug();
	/****	��ʕ`��	****/
	SwapChain();

	return false;
}
