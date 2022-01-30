#include "Tutorial_X.h"
#include "Player.h"

Tutorial_X::Tutorial_X(string in_Name)
{
}

bool Tutorial_X::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "X";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//�����͓����Ō����Ȃ�
	//m_SpriteRenderer->Color.a = 1.0f;
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(X_TUTORIAL_X, X_TUTORIAL_Y, X_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_Tutorial_XYAnimController);

	m_Start_X_TutorialFlg = false;
	m_PerfectLook_X_TutorialFlg = false;
	m_EndStart_X_TutorialFlg = false;
	m_End_X_TutorialFlg = false;

	return true;
}

bool Tutorial_X::Update()
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//�{�I�̎�O��ւ�Ƀv���C���[������������A
	if ((transform->Position.x - m_Player->GetTransform().Position.x) <= 300) {
		m_Start_X_TutorialFlg = true;
	}
	if (m_Start_X_TutorialFlg == true && m_PerfectLook_X_TutorialFlg == false) {//���X�Ɍ�����悤�ɂȂ�B
		m_SpriteRenderer->Color.a += 0.03f;
		if (m_SpriteRenderer->Color.a >= 1.0) {
			m_SpriteRenderer->Color.a = 1.0f;
			m_Start_X_TutorialFlg = false;//���X�Ɍ�����i�K�I���@�@�@���ʂȃt���O�������I�I
			m_PerfectLook_X_TutorialFlg = true;//���S�Ɍ�����
		}
	}

	if (m_Player->m_LandTile->GetLandTile() == LandGround) return true;

	if ((Input::GetKeyTrigger(PK_Q) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_X) == true) &&//�L�[��Q�܂��̓R���g���[���[��X����������
		(m_PerfectLook_X_TutorialFlg == true && m_Player->m_LandTile->GetLandTile()->GetKind() == RED_BLOCK) ||
		(m_PerfectLook_X_TutorialFlg == true && m_Player->m_LandTile->GetLandTile()->GetKind() == BLUE_BLOCK) ||
		(m_PerfectLook_X_TutorialFlg == true && m_Player->m_LandTile->GetLandTile()->GetKind() == GREEN_BLOCK)
		) {//�v���C���[���Ԃ̃J���[�u���b�N�̏�
		m_EndStart_X_TutorialFlg = true;
	}
	if (m_EndStart_X_TutorialFlg == true && m_End_X_TutorialFlg == false) {//�����n�߂�
		m_SpriteRenderer->Color.a -= 0.03f;
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_EndStart_X_TutorialFlg = false;//���X�ɏ�����i�K�I��
			m_End_X_TutorialFlg = true;//���S�ɏ�����
		}
	}
	return true;
}

