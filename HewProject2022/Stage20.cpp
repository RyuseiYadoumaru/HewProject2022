#include "Stage20.h"

using namespace Create;

bool GamePlay::Stage20Scene::Start()
{
	/* �C���X�^���X */
	m_Map = Instance<Map>(STAGE_4_5);
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_Shelf2Start = Instance<Shelf2>("Shelf2Start");
	m_BookShelfEnd = Instance<BookShelf>("BookShelfEnd");

	/*	�w�i������	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("WORLD4_BG");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("world4_obj1_5");

	m_GrayBack = Instance<GrayBack>("GrayBack");
	m_GrayBack->Sprite("Grey4_5");

	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("world4_obj2_5");
	m_LayerBack->transform->Position.y += 5.0f;
	m_GrayBack->transform->Position.y += 5.0f;

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World4_ceiling");
	/*	������	*/
	m_BookShelfEnd->transform->Position.x += ROAD_DISTANCE;

	/* �S�[�����v���C���[�G�t�F�N�g���� */
	m_PGoalEffect = Instance<PlayerGoalEffect>("PGoalEffect");

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

	m_Button->NowScene = m_ResultCursor->NowScene;

	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_WORLD4_GAMEBGM);

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
		/****	�����蔻��	****/

		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Shelf2Start->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BookShelfEnd->GetComponent<BoxCollider2D>());

		/***  �S�[������p  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());

		/****	�I�u�W�F�N�g�X�V	****/
		ObjectUpdate();

		//����������S�[��
		for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject())
		{
			if (name == m_Player->ToString())
			{
				if (m_Player->m_OnGround == true) {
					Scene_State = 2;//���U���g�p����Ɉړ�
				}
			}
		}
		/* Pause�����@ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true || Input::GetKeyTrigger(VK_ESCAPE)) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

		break;


	case 1://�|�[�Y���
	/****   �|�[�Y������   ****/
		m_Button->PauseCursor_Move();
		/* Pause�����@OFF */
		if (m_Button->Get_Checker() == 1 || Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true || Input::GetKeyTrigger(VK_ESCAPE)) {
			m_Pause->Pause_Off();
			m_Button->Pause_Off();
			Scene_State = 0;
		}
		break;
	case 2://���U���g���

		m_Player->Goal(m_Goal->transform->Position.x);//�S�[���A�j���[�V�����Đ�
		m_PGoalEffect->EF_Start();
		m_PGoalEffect->transform->Position.Set(m_Player->transform->Position.x, m_Player->transform->Position.y, 0);
		if (m_Player->GetGoal() == true) {//�A�j���[�V�����I���Ń��U���g�\��
			m_ResultBack->Result_On();//���U���g��ʂ̃t���O
			m_ResultCursor->Result_On();
			m_ResultCursor->ResultCursor_Move();//�J�[�\���t���O������
			m_Fade->Update();
		}
		break;
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
	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_WORLD4_GAMEBGM);

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

	// �O���[�w�i
	ObjectRender<GrayBack>("GrayBack");

	/****	�V��	****/
	ObjectRender<Ceiling>("Ceiling");

	/*** �S�[���`�� ***/
	ObjectRender<Goal>("Goal");
	ObjectRender<PlayerGoalEffect>("PGoalEffect");

	/****	�I�u�W�F�N�g�`��	****/
	ObjectRender<Player>("Player");
	ObjectRender<Map>(STAGE_4_5);
	ObjectRender<Shelf2>("Shelf2Start");
	ObjectRender<BookShelf>("BookShelfEnd");

	/****	�O�����i	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");

	/*** ���U���g ***/
	ObjectRender<Result>("ResultBack");
	ObjectRender<Result>("ResultCursor");

	/*** �t�F�[�h ***/
	m_Fade->Render();

	/**** Pause�`�� ****/
	ObjectRender<Pause>("Pause");
	ObjectRender<Pause>("Button");


	/****	��ʕ`��	****/
	SwapChain();

	return true;
}