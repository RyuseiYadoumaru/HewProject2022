#include "Stage2.h"

using namespace Create;

bool GamePlay::Stage2Scene::Start()
{

	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>("MapSizeTest_3");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_CuhsionStart = make_shared<Cuhsion>("CuhsionStart");
	m_CuhsionEnd = make_shared<Cuhsion>("CuhsionEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	�w�i������	*/
	m_BackGround = make_shared<Actor>("Wall");
	m_BackGround->Sprite("Wall");
	Instance(m_BackGround.get());
	m_BackGround->transform->Position.Set(-40.0f, -200.0f, 0.0f);


	/*	�C���X�^���X	*/
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_CuhsionStart.get());
	Instance(m_CuhsionEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());

	/*	������	*/
	m_Player->transform->Position.Set(-2500.0f, -500.0f, 0.0f);
	m_CuhsionEnd->transform->Position.x = CUHSION_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage2Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	/****	�u���b�N�ړ�	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);
	if (((m_Player->m_LandTile.GetisLandTile() == false) ||
		(Input::GetControllerTrigger(XINPUT_GAMEPAD_X)) || Input::GetKeyTrigger(PK_R)) &&
		(m_Map->m_OnReset == false))
	{
		//���Z�b�g����
		m_Map->m_OnReset = true;
	}
	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	/****	�����蔻��	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionEnd->GetComponent<BoxCollider2D>());


	/****	���[�h�V�[��	****/
	//if (Input::GetKeyTrigger(PK_ENTER) == true ||
	//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
	//{
	//	//GameEngine::SceneManager::LoadScene("ResultScene");
	//}

	/****	�V�X�e���X�V	****/
	m_Map->SystemUpdate();
	SystemUpdate();	return PLAY;
}

bool GamePlay::Stage2Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage2Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�w�i	****/
	m_BackGround->Render();

	/****	�I�u�W�F�N�g�`��	****/
	m_CuhsionStart->Render();
	m_CuhsionEnd->Render();
	m_Map->Render();
	m_Player->Render();

	/****	�f�o�b�O	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_CuhsionStart->Debug();

	/****	��ʃG�t�F�N�g	****/
	m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}