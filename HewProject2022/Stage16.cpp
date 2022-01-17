#include "Stage16.h"

using namespace Create;

bool GamePlay::Stage16Scene::Start()
{
	//�I�u�W�F�N�g���� ������
	m_stage16 = make_shared<Actor>("Stage-01");
	m_world4 = make_shared<Actor>("World-04");
	m_stage16->Sprite("stage-01");
	m_world4->Sprite("world-04");

	OldInstance(m_stage16.get());
	OldInstance(m_world4.get());

	///***  �S�[������p  ***/
	//m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());
	////����������S�[��
	//for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject()) {
	//	if (name == m_Player->ToString()) {
	//		Scene_State = 2;//���U���g�p����Ɉړ�
	//		m_ResultBack->Result_On();
	//		m_ResultCursor->Result_On();
	//	}
	//}

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
	m_ResultCursor->NowScene = "Stage16";
	

	m_stage16->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world4->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage16Scene::Update()
{
	switch (Scene_State) {
	case 0:
		/****	�I�u�W�F�N�g�X�V	****/
		ObjectUpdate();


		/****	���[�h�V�[��	****/
		if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_B))//�G���^�[�����Ǝ��̃V�[���ֈړ�
		{
			GameEngine::SceneManager::LoadScene("ResultScene");
		}

		/* Pause�����@ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

		/****	�V�X�e���X�V	****/
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

bool GamePlay::Stage16Scene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::Stage16Scene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	m_stage16->Render();
	m_world4->Render();

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
