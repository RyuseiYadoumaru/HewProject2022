#include "ProtScene.h"

using namespace GamePlay;
/****	������	****/
bool ProtScene::Start()
{
	cout << "�v���g�^�C�v�V�[��" << endl;
	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>("ProtMap");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");
	m_Fade = make_shared<Fade>("Black");
	m_Table = make_shared<Table>("Table");
	m_AnimTest = make_shared<AnimTest>("Animtest");
	m_Screen = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	�C���X�^���X	*/
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_BackGruond.get());
	Instance(m_Table.get());
	Instance(m_Fade.get());
	Instance(m_AnimTest.get());
	Instance(m_Screen.get());
	Instance(m_CameraFrame.get());

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	/*	�M�~�b�N������	*/
	//�X�̕������Ȃ艘�����ǋ����Ă�����
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*�@BG�l�Đ��@*/
	//Sound::Sound_Play(SOUND_LABEL_BGM000);

	return true;
}

/****	�X�V	****/
Scene::STATE ProtScene::Update()
{
	static int cnt = 0;
	cnt++;
	/*	�t���[���J�E���g	*/
	cout << "\n�t���[��" << cnt << endl;

	/****	�u���b�N�ړ�	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);

	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();
	m_Fade->Update();

	/****	�����蔻��	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Table->GetComponent<BoxCollider2D>());

	/****	���[�h�V�[��	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)		//�G���^�[�����Ǝ��̃V�[���ֈړ�
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

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
	//m_BackGruond->Render();
	m_Table->Render();
	m_Map->Render();
	m_Player->Render();
	m_AnimTest->Render();

	/****	�R���C�_�`��	****/
	//m_Map->Debug();
	//m_Player->Debug();
	//m_Table->Debug();

	/****	��ʃG�t�F�N�g	****/
	m_Fade->Render();
	m_Screen->Render();
	m_CameraFrame->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
