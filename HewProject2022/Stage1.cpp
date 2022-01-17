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

	///*	�w�i������	*/
	//m_BackGround = make_shared<BackGround>("Wall");
	//m_BackGround->Sprite("Wall");
	//OldInstance(m_BackGround.get());

	//m_LayerBack = make_shared<LayerBack>("LayerBack");
	//m_LayerBack->Sprite("World_obj1_1");
	//OldInstance(m_LayerBack.get());

	//m_LayerFront = make_shared<LayerFront>("LayerFront");
	//m_LayerFront->Sprite("World_obj2_1");
	//OldInstance(m_LayerFront.get());

	///*	�V�䏉����	*/
	//m_Ceiling = make_shared<Ceiling>("Ceiling");
	//m_Ceiling->Sprite("ceiling");
	//OldInstance(m_Ceiling.get());


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

	/* Pause������ */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("�|�[�Y");
	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button");
	m_Button->NowScene = "Stage1";

	/*  �S�[���C���X�^���X����  */
	m_Goal = Instance<Goal>("Goal");





	/*	�w�i������	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_1");

	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_1");

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");

	/* ���U���g������ */
	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();
	m_ResultCursor = Instance<Result>("ResultCursor");//���U���g���J�[�\���̃C���X�^���X����
	m_ResultCursor->ResultCursor_Init();//�����l�Z�b�g
	m_ResultCursor->Sprite("button");
	m_ResultCursor->NowScene = "Stage1";//���݂̃V�[���ݒ�
	/*	������	*/
	m_SofaEnd->transform->Position.x += ROAD_DISTANCE;


	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);



	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_WORLD1_GAMEBGM);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage1Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;


	switch (Scene_State) {
	case 0://���C���Q�[������
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
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TableStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaEnd->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BigBook->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_MiniBook->GetComponent<BoxCollider2D>());

		/****	�I�u�W�F�N�g�X�V	****/
		cout << "PlayerPositionY:" << m_Player->transform->Position.y << endl;
		ObjectUpdate();
		cout << "PlayerPositionY:" << m_Player->transform->Position.y << endl;

		/***  �S�[������p  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());
		//����������S�[��
		for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject()) {
			if (name == m_Player->ToString()) {
				Scene_State = 2;//���U���g�p����Ɉړ�
				m_ResultBack->Result_On();
				m_ResultCursor->Result_On();
			}
		}


		/****	���[�h�V�[��	****/
		if (Input::GetKeyTrigger(PK_ENTER) == true)
		{
			GameEngine::SceneManager::LoadScene("Stage2");
		}

		/* Pause�����@ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

		/****	�V�X�e���X�V	****/
		m_Map->SystemUpdate();
		SystemUpdate();
		return PLAY;
		break;
	case 1://�|�[�Y���
		/****   �|�[�Y������   ****/
		m_Button->PauseCursor_Move();
		/* Pause�����@OFF */
		if (m_Button->Get_Checker() == 1) {
			m_Pause->Pause_Off();
			m_Button->Pause_Off();
			Scene_State = 0;
		}
		break;
	case 2://���U���g���
		m_ResultBack->Result_On();//���U���g��ʂ̃t���O
		m_ResultCursor->Result_On();
		m_ResultCursor->ResultCursor_Move();//�J�[�\���t���O������
		break;

	}

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

	/*** �S�[���`�� ***/
	ObjectRender<Goal>("Goal");

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

	/**** Pause�`�� ****/
	ObjectRender<Pause>("Pause");
	ObjectRender<Pause>("Button");

	/*** ���U���g ***/
	ObjectRender<Result>("ResultBack");
	ObjectRender<Result>("ResultCursor");



	/****	��ʕ`��	****/
	SwapChain();

	return true;
}