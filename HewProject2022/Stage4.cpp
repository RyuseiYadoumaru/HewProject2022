#include "Stage4.h"

using namespace Create;

bool GamePlay::Stage4Scene::Start()
{

	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>("MapSizeTest_3");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_ChairStart = make_shared<Chair>("ChairStart");
	m_ChairEnd = make_shared<Chair>("ChairEnd");
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
	Instance(m_ChairStart.get());
	Instance(m_ChairEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());

	/*	������	*/
	m_Player->transform->Position.Set(-2500.0f, -500.0f, 0.0f);
	m_ChairEnd->transform->Position.x = CHAIR_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage4Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	/****	�u���b�N�ړ�	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);
	if (m_Player->m_LandTile.GetisLandTile() == false ||
		Input::GetControllerTrigger(XINPUT_GAMEPAD_X))
	{
		m_Map->MoveReset();
	}

	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	/****	�����蔻��	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_ChairStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_ChairEnd->GetComponent<BoxCollider2D>());


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

bool GamePlay::Stage4Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage4Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�w�i	****/
	m_BackGround->Render();

	/****	�I�u�W�F�N�g�`��	****/
	m_ChairStart->Render();
	m_ChairEnd->Render();
	m_Map->Render();
	m_Player->Render();

	/****	�f�o�b�O	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_ChairStart->Debug();

	/****	��ʃG�t�F�N�g	****/
	m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}