#include "Stage20.h"

using namespace Create;

bool GamePlay::Stage20Scene::Start()
{
	/* �C���X�^���X */
	m_Map = Instance<Map>("stage1-1");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_Shelf2Start = Instance<Shelf2>("Shelf2Start");
	m_BookShelfEnd = Instance<BookShelf>("BookShelfEnd");

	/*	�w�i������	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("WORLD4_BG");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("world4_obj1_5");

	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("world4_obj2_5");

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World4_Ceiling");

	/*	������	*/
	m_BookShelfEnd->transform->Position.x += ROAD_DISTANCE;



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
	m_ResultCursor->NowScene = "Stage20";


	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage20Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;


	switch (Scene_State) {
	case 0:
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
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Shelf2Start->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BookShelfEnd->GetComponent<BoxCollider2D>());

		/* Pause�����@ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

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
/****	�V�X�e���X�V	****/
m_Map->SystemUpdate();
SystemUpdate();
return PLAY;
}

bool GamePlay::Stage20Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage20Scene::Render()
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
	ObjectRender<Shelf2>("Shelf2Start");
	ObjectRender<BookShelf>("BookShelfEnd");

	/****	�O�����i	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

	/*** �S�[���`�� ***/
	ObjectRender<Goal>("Goal");

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