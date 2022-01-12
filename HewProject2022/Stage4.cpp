#include "Stage4.h"

using namespace Create;

bool GamePlay::Stage4Scene::Start()
{
	/*	�C���X�^���X	*/
	m_Map = Instance<Map>("stage1-2");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_SofaStart = Instance<Sofa>("SofaStart");
	m_DeskEnd = Instance<Desk>("DeskEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_4");
	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_4");


	/*	������	*/
	m_DeskEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player, &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	//m_MainCamera->Focus(m_Player);

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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_DeskEnd->GetComponent<BoxCollider2D>());

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
	ObjectRender<BackGround>("Wall");

	/****	�㑕���i	****/
	ObjectRender<LayerBack>("LayerBack");

	/****	�V��	****/
	ObjectRender<Ceiling>("Ceiling");

	/****	�I�u�W�F�N�g�`��	****/
	ObjectRender<Sofa>("SofaStart");
	ObjectRender<Desk>("DeskEnd");

	ObjectRender<Map>("stage1-2");
	ObjectRender<Player>("Player");

	/****	�O�����i	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	�f�o�b�O	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_TableStart->Debug();

	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}