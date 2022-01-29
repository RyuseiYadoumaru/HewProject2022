#include "Tutorial_Y.h"
#include "Player.h"
#include "Result.h"

Tutorial_Y::Tutorial_Y(string in_Name)
{
}

bool Tutorial_Y::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Y";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//�����͓����Ō����Ȃ�
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(Y_TUTORIAL_X, Y_TUTORIAL_Y, Y_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_Tutorial_XYAnimController);

	m_Start_Y_TutorialFlg = false;
	m_PerfectLook_Y_TutorialFlg = false;
	m_EndStart_Y_TutorialFlg = false;
	m_End_Y_TutorialFlg = false;

	return true;
}

bool Tutorial_Y::Update()
{

	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	Result* m_Result = Create::Scene::GetGameObject<Result>("ResultCursor");

	if (m_Result->NowScene == "Stage3") {//�����̓X�e�[�W�R�ł�������Ȃ��悤�ɂ�����

		//��O��ւ�Ƀv���C���[������������A
		if ((transform->Position.x - m_Player->GetTransform().Position.x) <= 200) {
			m_Start_Y_TutorialFlg = true;
		}
		if (m_Start_Y_TutorialFlg == true && m_PerfectLook_Y_TutorialFlg == false) {//���X�Ɍ�����悤�ɂȂ�B
			m_SpriteRenderer->Color.a += 0.03f;
			if (m_SpriteRenderer->Color.a >= 1.0) {
				m_SpriteRenderer->Color.a = 1.0f;
				m_Start_Y_TutorialFlg = false;//���X�Ɍ�����i�K�I���@�@�@���ʂȃt���O�������I�I
				m_PerfectLook_Y_TutorialFlg = true;//���S�Ɍ�����
			}
		}

		if ((Input::GetKeyTrigger(PK_R) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_Y) == true) &&//�L�[��R�܂��̓R���g���[���[��Y����������
			m_PerfectLook_Y_TutorialFlg == true) {
			m_EndStart_Y_TutorialFlg = true;
		}
		if (m_EndStart_Y_TutorialFlg == true && m_End_Y_TutorialFlg == false) {//�����n�߂�
			m_SpriteRenderer->Color.a -= 0.03f;
			if (m_SpriteRenderer->Color.a <= 0.0f) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_EndStart_Y_TutorialFlg = false;//���X�ɏ�����i�K�I��
				m_End_Y_TutorialFlg = true;//���S�ɏ�����
			}
		}
	}
	return true;
}


