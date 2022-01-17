#include "Stage9.h"

using namespace Create;

bool GamePlay::Stage9Scene::Start()
{

	/*	�I�u�W�F�N�g����	*/
	//m_Map = make_shared<Map>("stage1-1");
	//m_Player = make_shared<Player>("Player");
	//m_MainCamera = make_shared<MainCamera>("MainCamera");
	//m_Fade = make_shared<Fade>("Black");
	//m_SinkStart = make_shared<Sink>("SinkStart");
	//m_TablewareEnd = make_shared<Tableware>("TablewareEnd");
	//m_ScreenEffect = make_shared<ScreenFx>("SFX");
	//m_CameraFrame = make_shared<CameraFrame>("CFX");


	///*	�w�i������	*/
	//m_BackGround = make_shared<BackGround>("Wall");
	//m_BackGround->Sprite("World2_BG");
	//OldInstance(m_BackGround.get());

	//m_LayerBack = make_shared<LayerBack>("LayerBack");
	//m_LayerBack->Sprite("World2_obj1_4");
	//OldInstance(m_LayerBack.get());

	//m_LayerFront = make_shared<LayerFront>("LayerFront");
	////m_LayerFront->Sprite("World2_obj2_1");
	//OldInstance(m_LayerFront.get());

	///*	�V�䏉����	*/
	//m_Ceiling = make_shared<Ceiling>("Ceiling");
	//m_Ceiling->Sprite("World2_ceiling");
	//OldInstance(m_Ceiling.get());


	/*	�C���X�^���X	*/
	m_Map = Instance<Map>("stage1-1");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_SinkStart = Instance<Sink>("SinkStart");
	m_TablewareEnd = Instance<Tableware>("TablewareEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("World2_BG");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World2_obj1_4");
	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World2_obj2_1");


	/*	������	*/
	m_TablewareEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/


	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	return true;
}

Scene::STATE GamePlay::Stage9Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	/****	�u���b�N�ړ�	****/
	m_Map->CheckLandTile(m_Player->m_LandTile);
	if (((m_Player->m_LandTile->GetisLandTile() == false) ||
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SinkStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TablewareEnd->GetComponent<BoxCollider2D>());

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

bool GamePlay::Stage9Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage9Scene::Render()
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
	ObjectRender<Sink>("SinkStart");
	ObjectRender<Tableware>("TablewareEnd");

	ObjectRender<Map>("stage1-1");
	ObjectRender<Player>("Player");

	/****	�O�����i	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	�f�o�b�O	****/
	//m_ShelfEnd->Debug();
	//m_TablewareStart->Debug();
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