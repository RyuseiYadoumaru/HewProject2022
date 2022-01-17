#include "TutorialEffectAnimController.h"

#include "TutorialEffect.h"
#include "MoveTutorial.h"
#include "JumpTutorial.h"

bool TutorialEffectAnimController::Init()
{
	Anim = make_shared<TutorialEffectAnim>();
	Anim->Init();

	m_MoveInitFirstFlg = false;
	m_MoveInitSecondFlg = false;

	m_JumpInitFirstFlg = false;
	m_JumpInitSecondFlg = false;
	return true;
}

void TutorialEffectAnimController::Update()//�G�t�F�N�g����������
{
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");
	JumpTutorial* m_JumpTutorial = Create::Scene::GetGameObject<JumpTutorial>("JumpTutorial");
	TutorialEffect* m_TutorialEffect = Create::Scene::GetGameObject<TutorialEffect>("TutorialEffect");

	Anim->Play("TutorialEffect");

	////�ړ��`���[�g���A���G�t�F�N�g������///
	if (m_MoveTutorial->GetTutorialStartFlg() == true && m_MoveInitFirstFlg == false) {//�����n�ߏ�����
		Anim->Init();
		m_MoveInitFirstFlg = true;
	}
	if (m_MoveTutorial->GetTutorialEndStartFlg() == true && m_MoveInitSecondFlg == false) {//�����n�ߏ�����
		Anim->Init();
		m_MoveInitSecondFlg = true;
	}


	////�W�����v�`���[�g���A���G�t�F�N�g������////
	if (m_JumpTutorial->GetTutorialStartFlg() == true && m_JumpInitFirstFlg == false) {//�����n�ߏ�����
		Anim->Init();
		m_JumpInitFirstFlg = true;
	}
	if (m_JumpTutorial->GetTutorialEndStartFlg() == true && m_JumpInitSecondFlg == false) {//�����n�ߏ�����
		Anim->Init();
		m_JumpInitSecondFlg = true;
	}
}


//�A�j���[�V�����͏�ɍĐ�����Ă��āA�������u�Ԃɏ���������H



