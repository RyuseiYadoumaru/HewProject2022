#include "TutorialEffect.h"
#include "MoveTutorial.h"
#include "JumpTutorial.h"

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
	transform->Position.Set(m_MoveTutorial->transform->Position.x, m_MoveTutorial->transform->Position.y, m_MoveTutorial->transform->Position.z);//�ړ��`���[�g���A���Ɠ����ʒu
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_TutoriaEffectlAnimController);

	m_MoveTutorialEffectFlg = false;
	m_JumpTutorialEffectFlg = false;

	return true;
}

bool TutorialEffect::Update()
{
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");
	JumpTutorial* m_JumpTutorial = Create::Scene::GetGameObject<JumpTutorial>("JumpTutorial");

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

	return true;
}

