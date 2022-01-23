#include "JumpTutorial.h"
#include "Player.h"

using namespace Create;

JumpTutorial::JumpTutorial(string in_Name)
{
}

bool JumpTutorial::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "A";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//�����͓����Ō����Ȃ�
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(JUMP_TUTORIAL_X, JUMP_TUTORIAL_Y, JUMP_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_JumpTutorialAnimController);

	m_StartJumpTutorialFlg = false;
	m_PerfectLookJumpTutorialFlg = false;
	m_EndStartJumpTutorialFlg = false;
	m_EndJumpTutorialFlg = false;

	return true;
}

bool JumpTutorial::Update()
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//�{�I�̎�O��ւ�Ƀv���C���[������������A
	if ((transform->Position.x - m_Player->GetTransform().Position.x) <= 200) {
		m_StartJumpTutorialFlg = true;
	}
	if (m_StartJumpTutorialFlg == true && m_PerfectLookJumpTutorialFlg == false) {//���X�Ɍ�����悤�ɂȂ�B
		m_SpriteRenderer->Color.a += 0.03f;
		if (m_SpriteRenderer->Color.a >= 1.0) {
			m_SpriteRenderer->Color.a = 1.0f;
			m_StartJumpTutorialFlg = false;//���X�Ɍ�����i�K�I���@�@�@���ʂȃt���O�������I�I
			m_PerfectLookJumpTutorialFlg = true;//���S�Ɍ�����
		}
	}

	if (m_Player->GetTransform().Position.x >= transform->Position.x) {//�ʂ�߂�����
		m_EndStartJumpTutorialFlg = true;
	}
	if (m_EndStartJumpTutorialFlg == true && m_EndJumpTutorialFlg == false) {//�����n�߂�
		m_SpriteRenderer->Color.a -= 0.03f;
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_EndStartJumpTutorialFlg = false;//���X�ɏ�����i�K�I��
			m_EndJumpTutorialFlg = true;//���S�ɏ�����
		}
	}



	return true;
}
