#include "Stage14.h"

using namespace Create;

bool GamePlay::Stage14Scene::Start()
{


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
	m_LayerBack->Sprite("World3_obj1-4");
	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World3_obj2-4");

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World3_ceiling");

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
	m_ResultCursor->NowScene = "Stage14";



	/*	������	*/
	m_TreeEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/


	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage14Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	switch (Scene_State) {
	case 0:
		/****	�I�u�W�F�N�g�X�V	****/
		ObjectUpdate();

		/****	�����蔻��	****/
		m_Map->HitCheckMap(*m_Player);
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_RoseStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TreeEnd->GetComponent<BoxCollider2D>());

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


		/* Pause�����@ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

		/****	�V�X�e���X�V	****/
		m_Map->SystemUpdate();
		SystemUpdate();	return PLAY;
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

	/*** �S�[���`�� ***/
	ObjectRender<Goal>("Goal");

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