#include "Stage2.h"

using namespace Create;

bool GamePlay::Stage2Scene::Start()
{

	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>("stage1-2");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_SofaStart = make_shared<Sofa>("SofaStart");
	m_CuhsionEnd = make_shared<Cuhsion>("CuhsioniEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	�w�i������	*/
	m_BackGround = make_shared<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	Instance(m_BackGround.get());

	m_LayerBack = make_shared<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_2");
	Instance(m_LayerBack.get());

	m_LayerFront = make_shared<LayerFront>("LayerFront");
	//m_LayerFront->Sprite("World_obj2_1");
	Instance(m_LayerFront.get());

	/*	�V�䏉����	*/
	m_Ceiling = make_shared<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");
	Instance(m_Ceiling.get());


	/*	�C���X�^���X	*/
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_SofaStart.get());
	Instance(m_CuhsionEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());


	/*	������	*/
	m_CuhsionEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera.get());
	//m_MainCamera->Focus(m_Player.get());

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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionEnd->GetComponent<BoxCollider2D>());

	/****	���[�h�V�[��	****/
	//if (Input::GetKeyTrigger(PK_ENTER) == true ||
	//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
	//{
	//	//GameEngine::SceneManager::LoadScene("ResultScene");
	//}

	/****	�V�X�e���X�V	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;
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

	/****	�㑕���i	****/
	m_LayerBack->Render();

	/****	�V��	****/
	m_Ceiling->Render();

	/****	�I�u�W�F�N�g�`��	****/
	m_SofaStart->Render();
	m_CuhsionEnd->Render();

	m_Map->Render();
	m_Player->Render();

	/****	�O�����i	****/
	m_LayerFront->Render();

	/****	�f�o�b�O	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_TableStart->Debug();

	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}