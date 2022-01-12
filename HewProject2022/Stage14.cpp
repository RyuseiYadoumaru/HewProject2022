#include "Stage14.h"

using namespace Create;

bool GamePlay::Stage14Scene::Start()
{

	/*	�I�u�W�F�N�g����	*/
	//m_Map = make_shared<Map>("MapSizeTest_3");
	//m_Player = make_shared<Player>("Player");
	//m_MainCamera = make_shared<MainCamera>("MainCamera");
	//m_Fade = make_shared<Fade>("Black");
	//m_RoseStart = make_shared<Rose>("RoseStart");
	//m_TreeEnd = make_shared<Tree>("TreeEnd");
	//m_ScreenEffect = make_shared<ScreenFx>("SFX");
	//m_CameraFrame = make_shared<CameraFrame>("CFX");


	///*	�w�i������	*/
	//m_BackGround = make_shared<BackGround>("Wall");
	//m_BackGround->Sprite("World3_BG");
	//OldInstance(m_BackGround.get());

	//m_LayerBack = make_shared<LayerBack>("LayerBack");
	//m_LayerBack->Sprite("Wrold3_obj1_3");
	//OldInstance(m_LayerBack.get());

	//m_LayerFront = make_shared<LayerFront>("LayerFront");
	//m_LayerFront->Sprite("Wrold3_obj2_4");
	//OldInstance(m_LayerFront.get());

	///*	�V�䏉����	*/
	//m_Ceiling = make_shared<Ceiling>("Ceiling");
	//m_Ceiling->Sprite("World2_ceiling");
	//OldInstance(m_Ceiling.get());


	/*	�C���X�^���X	*/
	m_Map = Instance<Map>("stage1-1");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_RoseStart = Instance<Rose>("RoseStart");
	m_TreeEnd = Instance<Tree>("TreeEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("World3_BG");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("Wrold3_obj1_3");
	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("Wrold3_obj2_4");


	/*	������	*/
	m_TreeEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player, &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	return true;
}

Scene::STATE GamePlay::Stage14Scene::Update()
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_RoseStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TreeEnd->GetComponent<BoxCollider2D>());

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

bool GamePlay::Stage14Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage14Scene::Render()
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
	ObjectRender<Rose>("RoseStart");
	ObjectRender<Tree>("TreeEnd");

	ObjectRender<Map>("stage1-1");
	ObjectRender<Player>("Player");

	/****	�O�����i	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	�f�o�b�O	****/
	//m_PlantsEnd->Debug();
	//m_RoseStart->Debug();
	//m_Player->Debug();
	//m_Map->Debug();

	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}