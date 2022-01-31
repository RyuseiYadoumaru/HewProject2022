#include "Stage18.h"

using namespace Create;

bool GamePlay::Stage18Scene::Start()
{
	/* �C���X�^���X */
	m_Map = Instance<Map>(STAGE_4_3);
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_BookShelfStart = Instance<BookShelf>("BookShelfStart");
	m_PictureFrameEnd = Instance<PictureFrame>("PictureFrameEnd");

	/*	�w�i������	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("WORLD4_BG");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("world4_obj1_3");
	m_GrayBack = Instance<GrayBack>("GrayBack");
	m_GrayBack->Sprite("Grey");
	m_LayerBack->transform->Position.y += 5.0f;
	m_GrayBack->transform->Position.y += 5.0f;

	/*	�V�䏉����	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World4_ceiling");
	/*	������	*/
	m_PictureFrameEnd->transform->Position.x += ROAD_DISTANCE;

	/* �S�[�����v���C���[�G�t�F�N�g���� */
	m_PGoalEffect = Instance<PlayerGoalEffect>("PGoalEffect");


	/* Pause������ */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("�|�[�Y");

	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button_2");

	/*  �S�[���C���X�^���X����  */
	m_Goal = Instance<Goal>("Goal");

	// �Q�[�����UI������
	m_PlayModeUI = Instance<PlayModeUI>("PlayModeUI");
	m_waku = Instance<waku>("waku");

	/* ���U���g������ */
	m_ResultFront = Instance<Result>("ResultFront");
	m_ResultFront->ResultFront_init();
	m_ResultCursor = Instance<Result>("ResultCursor");	//���U���g���J�[�\���̃C���X�^���X����
	m_ResultCursor->ResultCursor_Init();				//�����l�Z�b�g
	m_ResultCursor->NowScene = "Stage18";//���݂̃V�[���ݒ�
	m_Button->NowScene = m_ResultCursor->NowScene;

	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();

	/* ���U���g�A�j���[�V�����C���X�^���X���� */
	m_Fireworks = Instance<Fireworks>("Fireworks");
	m_Star = Instance<Star>("Star");

	/*	�J�����ݒ�	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);


	// BGM�Đ�
	Sound::Sound_Play(SOUND_LABEL_WORLD4_GAMEBGM);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage18Scene::Update()
{
	switch (Scene_State) {
	case 0:

		/****	�����蔻��	****/
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BookShelfStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_PictureFrameEnd->GetComponent<BoxCollider2D>());

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
			m_Star->StarChecker(m_Player->m_GetStar);
			m_Fireworks->Anim_Start();
			m_ResultFront->Result_On();//���U���g��ʂ̃t���O
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

bool GamePlay::Stage18Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();
	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_WORLD4_GAMEBGM);

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage18Scene::Render()
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
	ObjectRender<Map>(STAGE_4_3);
	ObjectRender<BookShelf>("BookShelfStart");
	ObjectRender<PictureFrame>("PictureFrameEnd");

	/****	��ʃG�t�F�N�g	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");

	// �Q�[�����UI
	ObjectRender<PlayModeUI>("PlayModeUI");
	ObjectRender<waku>("waku");

	/*** ���U���g ***/
	ObjectRender<Result>("ResultBack");
	ObjectRender<Fireworks>("Fireworks");
	ObjectRender<Star>("Star");
	ObjectRender<Result>("ResultFront");
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