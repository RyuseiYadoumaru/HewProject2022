#include "TutorialEffect.h"
#include "MoveTutorial.h"
#include "JumpTutorial.h"
#include "Tutorial_X.h"
#include "Tutorial_Y.h"
#include "Result.h"

using namespace Create;

TutorialEffect::TutorialEffect(string in_Name)
{
}

bool TutorialEffect::Start()
{
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "TutorialEffect";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//�����͓����Ō����Ȃ�
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(MOVE_TUTORIAL_X, MOVE_TUTORIAL_Y, MOVE_TUTORIAL_Z);//�ړ��`���[�g���A���Ɠ����ʒu
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_TutoriaEffectlAnimController);

	m_MoveTutorialEffectFlg = false;
	m_JumpTutorialEffectFlg = false;
	m_X_TutorialEffectFlg = false;
	m_Y_TutorialEffectFlg = false;

	return true;
}

bool TutorialEffect::Update()
{
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");
	JumpTutorial* m_JumpTutorial = Create::Scene::GetGameObject<JumpTutorial>("JumpTutorial");
	Tutorial_X* m_Tutorial_X = Create::Scene::GetGameObject<Tutorial_X>("Tutorial_X");
	Tutorial_Y* m_Tutorial_Y = Create::Scene::GetGameObject<Tutorial_Y>("Tutorial_Y");

	Result* m_Result = Create::Scene::GetGameObject<Result>("ResultCursor");


	if (m_Result->NowScene == "Stage1") {//�X�e�[�W�P�ł�������Ȃ�

		//////�ړ��`���[�g���A��////
		if (m_MoveTutorialEffectFlg == false) {
			if (m_MoveTutorial->GetTutorialStartFlg() == true) {
				//������悤�ɂȂ���
				m_SpriteRenderer->Color.a = 1.0f;
				//�A�j���[�V�������Đ�
			}
			//�ړ��`���[�g���A�������S�Ɍ������猩���Ȃ��Ȃ�
			if (m_MoveTutorial->GetTutorialLookPerfectFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
			}
			//�ړ��`���[�g���A���������n�߂����ɂ�����x������
			if (m_MoveTutorial->GetTutorialEndStartFlg() == true) {
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//�ړ��`���[�g���A���������Ȃ��Ȃ����������
			if (m_MoveTutorial->GetTutorialEndFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_MoveTutorialEffectFlg = true;
			}
		}


		////�W�����v�`���[�g���A��////
		if (m_JumpTutorialEffectFlg == false) {
			if (m_JumpTutorial->GetTutorialStartFlg() == true) {
				//���W���W�����v�`���[�g���A���Ɠ����Ƃ���ɂ���
				transform->Position.Set(m_JumpTutorial->transform->Position.x, m_JumpTutorial->transform->Position.y, m_JumpTutorial->transform->Position.z);
				//������悤�ɂȂ�
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//�W�����v�`���[�g���A�������S�Ɍ������猩���Ȃ��Ȃ�
			if (m_JumpTutorial->GetTutorialLookPerfectFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
			}
			//�W�����v�`���[�g���A���������n�߂����ɂ�����x������
			if (m_JumpTutorial->GetTutorialEndStartFlg() == true) {
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//�W�����v�`���[�g���A���������Ȃ��Ȃ����������
			if (m_JumpTutorial->GetTutorialEndFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_JumpTutorialEffectFlg = true;
			}
		}

		////X�`���[�g���A��////
		if (m_X_TutorialEffectFlg == false) {
			if (m_Tutorial_X->GetTutorialStartFlg() == true) {
				//���W��X�`���[�g���A���Ɠ����Ƃ���ɂ���
				transform->Position.Set(m_Tutorial_X->transform->Position.x, m_Tutorial_X->transform->Position.y, m_Tutorial_X->transform->Position.z);
				//������悤�ɂȂ�
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//X�`���[�g���A�������S�Ɍ������猩���Ȃ��Ȃ�
			if (m_Tutorial_X->GetTutorialLookPerfectFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
			}
			//X�`���[�g���A���������n�߂����ɂ�����x������
			if (m_Tutorial_X->GetTutorialEndStartFlg() == true) {
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//X�`���[�g���A���������Ȃ��Ȃ����������
			if (m_Tutorial_X->GetTutorialEndFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_X_TutorialEffectFlg = true;
			}
		}
	}

	if (m_Result->NowScene == "Stage3") {//�X�e�[�W3�ł�������Ȃ�

		////Y�`���[�g���A��////
		if (m_Y_TutorialEffectFlg == false) {
			if (m_Tutorial_Y->GetTutorialStartFlg() == true) {
				//���W��Y�`���[�g���A���Ɠ����Ƃ���ɂ���
				transform->Position.Set(m_Tutorial_Y->transform->Position.x, m_Tutorial_Y->transform->Position.y, m_Tutorial_Y->transform->Position.z);
				//������悤�ɂȂ�
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//Y�`���[�g���A�������S�Ɍ������猩���Ȃ��Ȃ�
			if (m_Tutorial_Y->GetTutorialLookPerfectFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
			}
			//Y�`���[�g���A���������n�߂����ɂ�����x������
			if (m_Tutorial_Y->GetTutorialEndStartFlg() == true) {
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//Y�`���[�g���A���������Ȃ��Ȃ����������
			if (m_Tutorial_Y->GetTutorialEndFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_Y_TutorialEffectFlg = true;
			}
		}
	}
	return true;
}

