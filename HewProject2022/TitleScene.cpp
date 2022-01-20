#include "TitleScene.h"

using namespace Create;

bool GamePlay::TitleScene::Start()
{

	m_BackGround = Instance<BackGround>("BackGround");
	m_BackGround->Sprite("Title");
	m_BackGround->Vertex("vs_Ui");
	m_BackGround->transform->Position.Set(1920 / 2, 1080 / 2, 0);
	//m_BackGround->transform->Scale.Set(1, 1, 0);
	m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 0;


	//�I�u�W�F�N�g���� ������

	/**** �^�C�g���E�`�[�����S������ ****/
	m_Title = Instance<Title>("TitleText");
	m_Title->Sprite("TitleLogo");
	m_Title->transform->Position.y -= 120;

	m_TeamLogo = Instance<Title>("TeamLogo");
	m_TeamLogo->Sprite("TeamLogo");
	m_TeamLogo->transform->Scale.Set(0.8, 0.8, 0);

	m_PushAny = Instance<PushAny>("PushAny");
	m_PushAny->Sprite("Any");
	m_PushAny->transform->Position.y -= 100;
	m_PushAny->transform->Scale.Set(1.1, 1.1, 0);


	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::TitleScene::Update()
{


	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	/****  ���S�\��  ****/
	if (m_TeamLogo->GetLogo_sw() == true) {
		m_TeamLogo->Fade_Switch();
	}
	else if (m_TeamLogo->GetLogo_sw() == false)
	{
		m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 1;
		m_Title->Fade_In();
		//�_�ŏ���
		m_PushAny->Flashing();
	}

	/****	NextScene	****/
	if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true ||
		Input::GetKeyTrigger(PK_ENTER) == true)
	{
		Input::Vibration(XINPUT_GAMEPAD_RIGHT_VIBRATION_MAX, 750.0f);
		GameEngine::SceneManager::LoadScene("WorldSelectScene");
	}

	/****	�V�X�e���X�V	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::TitleScene::End()
{
	/*	�I�u�W�F�N�g�I������	*/
	ObjectEnd();

	/*	�������	*/
	Releace();

	return true;
}

bool GamePlay::TitleScene::Render()
{
	/****	��ʃN���A	****/
	ClearDisplay();

	/****	�I�u�W�F�N�g�`��	****/
	ObjectRender<BackGround>("BackGround");
	ObjectRender<Title>("TitleText");
	ObjectRender<PushAny>("PushAny");
	ObjectRender<Title>("TeamLogo");
	/****	��ʕ`��	****/
	SwapChain();

	return true;
}