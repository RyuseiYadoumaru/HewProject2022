#include "Stage17.h"

using namespace Create;

bool GamePlay::Stage17Scene::Start()
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
	m_LayerBack->Sprite("world4_obj1_2");

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World4_ceiling");
	/*	������	*/
	m_BookShelfEnd->transform->Position.x += ROAD_DISTANCE;

	/*	�M�~�b�N������	*/


	///***  �S�[������p  ***/


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
	m_ResultCursor->NowScene = "Stage17";

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage17Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	switch (Scene_State) {
	case 0:

		/****	�����蔻��	****/
		m_Map->HitCheckMap(*m_Player);
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Shelf2Start->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BookShelfEnd->GetComponent<BoxCollider2D>());

		/****	�I�u�W�F�N�g�X�V	****/
		ObjectUpdate();


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
	/****	�V�X�e���X�V	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;

}

bool GamePlay::Stage17Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage17Scene::Render()
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
