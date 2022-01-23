#include "MoveTutorial.h"
#include "Player.h"

using namespace Create;

MoveTutorial::MoveTutorial(string in_Name)
{
}

bool MoveTutorial::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "L";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//�����͓����Ō����Ȃ�
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(MOVE_TUTORIAL_X, MOVE_TUTORIAL_Y, MOVE_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_TutorialAnimController);

	m_StartMoveTutorialFlg = false;
	m_PerfectLookMoveTutorialFlg = false;

	m_EndStartMoveTutorialFlg = false;
	m_EndMoveTutorialFlg = false;

	return true;
}

bool MoveTutorial::Update()//�����œ����ɂ��鏈���Ƃ������΂����񂩂�
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	if (m_PerfectLookMoveTutorialFlg == false) {//�Q�[���X�^�[�g�Ɠ����Ɋ��S�Ɍ�����悤�ɂȂ�܂Ō�����悤�ɂ���
		m_StartMoveTutorialFlg = true;//�����n�߂�
		m_SpriteRenderer->Color.a += 0.03f;

		if (m_SpriteRenderer->Color.a >= 1.0f) {
			m_SpriteRenderer->Color.a = 1.0f;
			m_StartMoveTutorialFlg = false;//���X�Ɍ����n�߂�i�K�I��
			m_PerfectLookMoveTutorialFlg = true;//���S�Ɍ�����
		}
	}

	if (m_Player->GetTransform().Position.x >= transform->Position.x) {//�ʂ�߂����������
		m_EndStartMoveTutorialFlg = true;
	}
	if (m_EndStartMoveTutorialFlg == true) {//�����n�߂�
		m_SpriteRenderer->Color.a -= 0.03f;
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_EndStartMoveTutorialFlg = false;//���X�ɏ����n�߂�i�K�I��
			m_EndMoveTutorialFlg = true;//���S�ɏ�����
		}
	}

	return true;
}
