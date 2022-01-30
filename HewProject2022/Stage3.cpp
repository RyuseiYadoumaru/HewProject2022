#include "Stage3.h"

using namespace Create;

bool GamePlay::Stage3Scene::Start()
{
	/*	�C���X�^���X	*/
	m_Map = Instance<Map>(STAGE_1_3);
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_CuhsionStart = Instance<Cuhsion>("CuhsionStart");
	m_SofaEnd = Instance<Sofa>("SofaEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");

	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World1_obj1-3");
	m_GrayBack = Instance<GrayBack>("GrayBack");
	m_GrayBack->Sprite("Grey1-3");

	m_PGoalEffect = Instance<PlayerGoalEffect>("PGoalEffect");

	/* Pause������ */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("�|�[�Y");

	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button");
	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");


	/*  �S�[���C���X�^���X����  */
	m_Goal = Instance<Goal>("Goal");

	/* ���U���g������ */
	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();
	m_ResultCursor = Instance<Result>("ResultCursor");
	m_ResultCursor->ResultCursor_Init();
	m_ResultCursor->NowScene = "Stage3";

	m_Button->NowScene = m_ResultCursor->NowScene;

	/* �`���[�g���A�������� */
	m_MoveTutorial = Instance<MoveTutorial>("MoveTutorial");
	m_JumpTutorial = Instance<JumpTutorial>("JumpTutorial");
	m_TutorialEffect = Instance<TutorialEffect>("TutorialEffect");
	m_Tutorial_X = Instance<Tutorial_X>("Tutorial_X");
	m_Tutorial_Y = Instance<Tutorial_Y>("Tutorial_Y");

	/*	������	*/
	m_SofaEnd->transform->Position.x += ROAD_DISTANCE;

	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_WORLD1_GAMEBGM);

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage3Scene::Update()
{
	/*	�t���[���J�E���g	*/
	static int cnt = 0;
	cnt++;
	cout << "\n�t���[��" << cnt << endl;

	switch (Scene_State) {
	case 0:
		/****	�����蔻��	****/

		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaEnd->GetComponent<BoxCollider2D>());

		/***  �S�[������p  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());

		/****	�I�u�W�F�N�g�X�V	****/
		ObjectUpdate();

		//����������S�[��
		for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject()) {
			if (name == m_Player->ToString()) {
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

bool GamePlay::Stage3Scene::End()
{
	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_WORLD1_GAMEBGM);


	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage3Scene::Render()
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
	ObjectRender<Cuhsion>("CuhsionStart");
	ObjectRender<Sofa>("SofaEnd");

	ObjectRender<Map>(STAGE_1_3);
	ObjectRender<Player>("Player");

	//�O�،��ǉ� �`���[�g���A���`��
	ObjectRender<TutorialEffect>("TutorialEffect");
	ObjectRender<Tutorial_Y>("Tutorial_Y");

	/****	�f�o�b�O	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_TableStart->Debug();

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