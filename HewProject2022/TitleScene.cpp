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
	m_TeamLogo->transform->Scale.Set(0.8f, 0.8f, 0.0f);

	m_PushAny = Instance<PushAny>("PushAny");
	m_PushAny->Sprite("Any");
	m_PushAny->transform->Position.y -= 100;
	m_PushAny->transform->Scale.Set(1.1f, 1.1f, 0.0f);

	m_GameEnd = Instance<Actor>("GameEnd");
	m_GameEnd->Sprite("End");
	m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 0;
	m_GameEnd->Vertex("vs_Ui");
	m_GameEnd->transform->Position.Set(1920 / 2, 1080 / 2, 0);
	m_GameEnd->transform->Scale.Set(1.5f, 1.5f, 0.0f);

	m_EndCursor = Instance<Actor>("EndCursor");
	m_EndCursor->Sprite("button");
	m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 0;
	m_EndCursor->Vertex("vs_Ui");
	m_EndCursor->transform->Position.Set(1920.0f / 2.0f, 1080.0f / 2.0f, 0.0f);


	/*	�J�����ݒ�	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	EndWin_flg = false;
	End_flg = false;
	isPlaySound = false;
	EndGame = false;

	//�V�[���J�ڃA�j���[�V�����\�t���O������
	SceneTransition::m_SceneTransitionFlg = false;

	return true;
}

Scene::STATE GamePlay::TitleScene::Update()
{
	/****	�I�u�W�F�N�g�X�V	****/
	ObjectUpdate();

	/****  ���S�\��  ****/
	if (EndGame == false)
	{
		if (m_TeamLogo->GetLogo_sw() == true) {
			m_TeamLogo->Fade_Switch();
		}
		else if (m_TeamLogo->GetLogo_sw() == false)
		{
			//�^�C�g����ʂ��o���Ƃ��̃T�E���h���Đ�����
			if (isPlaySound == false)
			{
				/*	�T�E���h�Đ�	*/
				Sound::Sound_Play(SOUND_LABEL_TITLE);
				isPlaySound = true;
			}

			m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 1;
			m_Title->Fade_In();
			//�_�ŏ���
			m_PushAny->Flashing();
			/**  �Q�[���I���p����  **///�N���X�ɂ܂Ƃ߂�Ɖ��̂��G���[�f���̂Œ��ŏ����܂����B�i�N���X�ɂ܂Ƃ߂ꂻ���Ȃ�܂Ƃ߂Ăق����Ȃ��c�j
			if (EndWin_flg == false) {//�ʏ���
				End_flg = false;
				if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true)//�`�{�^���Ń��[���h�Z���N�g��
				{
					Sound::Sound_Play(SOUND_LABEL_OK);
					GameEngine::SceneManager::LoadScene("World1StageSelectScene");
				}
				if (Input::GetControllerTrigger(XINPUT_GAMEPAD_B) == true || Input::GetKeyTrigger(VK_ESCAPE)) {//�X�^�[�g�{�^���ŃQ�[���I���E�C���h�E�̕\��
					//�Q�[���I���E�C���h�E��\������
					Sound::Sound_Play(SOUND_LABEL_BACK);
					m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 1;
					m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 1;
					EndWin_flg = true;//�Q�[���I��������Ԃ�
				}
			}
			else {//�Q�[���I������
				if (m_GameEnd->GetComponent<SpriteRenderer>()->Color.a == 1) {
					if (End_flg == false) {//�J�[�\���ʒu���u�������v�̎�
						m_EndCursor->transform->Position.Set((1920.0f / 2.0f) - 120, (1080.0f / 2.0f) + 80, 0.0f);

						if (Input::GetControllerLeftStick().y > 0.5 || Input::GetKeyTrigger(VK_DOWN) || Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true) {//�X�e�B�b�N�����ɓ|�����Ƃ��̔���
							Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);
							End_flg = true;//true=(�Q�[���I��)
						}

					}
					else {//�J�[�\���ʒu���u�͂��v�̎�
						m_EndCursor->transform->Position.Set((1920.0f / 2.0f) - 120, (1080.0f / 2.0f) + 150 + 80, 0.0f);
						/*if (Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_UP) == true) {
							End_flg = false;
						}*/
						if (Input::GetControllerLeftStick().y < -0.5 || Input::GetKeyTrigger(VK_UP) || Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_UP) == true) {//�X�e�B�b�N����ɓ|�����Ƃ��̔���
							Sound::Sound_Play(SOUND_LAVEL_SELECT_SE);
							End_flg = false;//false=(���̂܂�)
						}

					}
					//�Q�[���I���I��
					if (Input::GetControllerPress(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN)) {//�͂��i�Q�[�����I���j
						if (End_flg == true) {
							Sound::Sound_Play(SOUND_LABEL_OK);
							//���݂̃t���[���擾
							FinFrame = GameTimer::NowFrameCount();
							EndGame = true;;
						}
						if (End_flg == false) {//�������i�Q�[���^�C�g���ɖ߂�j
							//�Q�[���I���E�C���h�E���\���ɂ���
							m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 0;
							m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 0;
							EndWin_flg = false;//�ʏ��Ԃ�
						}
					}
					else if (Input::GetKeyTrigger(VK_ESCAPE))
					{
						Sound::Sound_Play(SOUND_LABEL_BACK);
						m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 0;
						m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 0;
						EndWin_flg = false;//�ʏ��Ԃ�
					}
				}
			}
		}

	}


	/****	�Q�[���I�����̏���	****/
	else
	{
		if (GameTimer::NowFrameCount() - FinFrame >= FinishWaitFrame)
		{
			//�ҋ@�t���[���҂��Ă���I������
			Application::Instance()->isEnd = true;//Engine�̃��[�v��~
		}

	}

	/****	�V�X�e���X�V	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::TitleScene::End()
{
	/*	�T�E���h�X�g�b�v	*/
	Sound::Sound_Stop(SOUND_LABEL_TITLE);

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
	ObjectRender<Actor>("GameEnd");
	ObjectRender<Actor>("EndCursor");

	/****	��ʕ`��	****/
	SwapChain();

	return true;
}
