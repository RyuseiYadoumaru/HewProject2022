#include "Stage1.h"
#include "Test.h"
using namespace Create;

bool GamePlay::Stage1Scene::Start()
{
	/*	�C���X�^���X	*/
	m_Map = Instance<Map>("stage1-1");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_TableStart = Instance<Table>("TableStart");
	m_SofaEnd = Instance<Sofa>("SofaEnd");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BigBook = Instance<BigBook>("Book1");
	m_MiniBook = Instance<MiniBook>("Book2");

	//�O�،��ǉ� �`���[�g���A��������
	m_MoveTutorial = Instance<MoveTutorial>("MoveTutorial");
	m_JumpTutorial = Instance<JumpTutorial>("JumpTutorial");
	m_TutorialEffect = Instance<TutorialEffect>("TutorialEffect");

	/*	�w�i������	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("world4_obj1_1");

	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_1");

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");

	/*	������	*/
	m_SofaEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player, &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);



	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_WORLD1_GAMEBGM);

	return true;
}

Scene::STATE GamePlay::Stage1Scene::Update()
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

	/****	�����蔻��	****/

	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TableStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaEnd->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BigBook->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_MiniBook->GetComponent<BoxCollider2D>());
	m_Map->HitCheckMap(*m_Player);

	/****	�I�u�W�F�N�g�X�V	****/
	cout << "PlayerPositionY:" << m_Player->transform->Position.y << endl;
	ObjectUpdate();
	cout << "PlayerPositionY:" << m_Player->transform->Position.y << endl;

	/****	���[�h�V�[��	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)
	{
		GameEngine::SceneManager::LoadScene("Stage2");
	}

	/****	�V�X�e���X�V	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage1Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage1Scene::Render()
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
	ObjectRender<Player>("Player");
	ObjectRender<Map>("stage1-1");
	ObjectRender<Table>("TableStart");
	ObjectRender<Sofa>("SofaEnd");
	ObjectRender<BigBook>("Book1");
	ObjectRender<MiniBook>("Book2");

	/****	�O�����i	****/
	ObjectRender<LayerFront>("LayerFront");

	//�O�،��ǉ� �`���[�g���A���`��
	ObjectRender<MoveTutorial>("MoveTutorial");
	ObjectRender<JumpTutorial>("JumpTutorial");
	ObjectRender<TutorialEffect>("TutorialEffect");

	/****	�f�o�b�O	****/
	m_Player->Debug();
	m_Map->Debug();
	m_TableStart->Debug();
	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}