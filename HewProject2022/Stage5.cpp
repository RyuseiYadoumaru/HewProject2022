#include "Stage5.h"

using namespace Create;

bool GamePlay::Stage5Scene::Start()
{

	/*	�I�u�W�F�N�g����	*/
	m_Map = make_shared<Map>("stage1-5");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_DeskStart = make_shared<Desk>("DeskStart");
	m_DeskEnd = make_shared<Desk>("DeskEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	�w�i������	*/
	m_BackGround = make_shared<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	OldInstance(m_BackGround.get());

	m_LayerBack = make_shared<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_5");
	OldInstance(m_LayerBack.get());

	m_LayerFront = make_shared<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_5");
	OldInstance(m_LayerFront.get());

	/*	�V�䏉����	*/
	m_Ceiling = make_shared<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");
	OldInstance(m_Ceiling.get());


	/*	�C���X�^���X	*/
	OldInstance(m_Map.get());
	OldInstance(m_Player.get());
	OldInstance(m_DeskStart.get());
	OldInstance(m_DeskEnd.get());
	OldInstance(m_Fade.get());
	OldInstance(m_ScreenEffect.get());
	OldInstance(m_CameraFrame.get());

	/* Pause������ */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("�|�[�Y");

	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button");

	/*  �S�[���C���X�^���X����  */
	m_Goal = Instance<Goal>("Goal");

	/* ���U���g������ */
	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();
	m_ResultCursor = Instance<Result>("ResultCursor");
	m_ResultCursor->ResultCursor_Init();
	m_ResultCursor->NowScene = "Stage1";
	


	/*	������	*/
	m_DeskEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	�J�����ݒ�	*/
	OldSetCamera(m_MainCamera.get());
	//m_MainCamera->Focus(m_Player.get());

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage5Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	switch (Scene_State) {
	case 0:
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
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_DeskStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_DeskEnd->GetComponent<BoxCollider2D>());

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
		//if (Input::GetKeyTrigger(PK_ENTER) == true ||
		//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
		//{
		//	//GameEngine::SceneManager::LoadScene("ResultScene");
		//}

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
		m_ResultCursor->ResultCursor_Move();//�J�[�\���t���O������
		break;
	}
}

bool GamePlay::Stage5Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage5Scene::Render()
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
	m_DeskStart->Render();
	m_DeskEnd->Render();

	m_Map->Render();
	m_Player->Render();

	/*** �S�[���`�� ***/
	ObjectRender<Goal>("Goal");

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