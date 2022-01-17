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

void TutorialEffectAnimController::Update()//エフェクト初期化処理
{
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");
	JumpTutorial* m_JumpTutorial = Create::Scene::GetGameObject<JumpTutorial>("JumpTutorial");
	TutorialEffect* m_TutorialEffect = Create::Scene::GetGameObject<TutorialEffect>("TutorialEffect");

	Anim->Play("TutorialEffect");

	////移動チュートリアルエフェクト初期化///
	if (m_MoveTutorial->GetTutorialStartFlg() == true && m_MoveInitFirstFlg == false) {//見え始め初期化
		Anim->Init();
		m_MoveInitFirstFlg = true;
	}
	if (m_MoveTutorial->GetTutorialEndStartFlg() == true && m_MoveInitSecondFlg == false) {//消え始め初期化
		Anim->Init();
		m_MoveInitSecondFlg = true;
	}


	////ジャンプチュートリアルエフェクト初期化////
	if (m_JumpTutorial->GetTutorialStartFlg() == true && m_JumpInitFirstFlg == false) {//見え始め初期化
		Anim->Init();
		m_JumpInitFirstFlg = true;
	}
	if (m_JumpTutorial->GetTutorialEndStartFlg() == true && m_JumpInitSecondFlg == false) {//消え始め初期化
		Anim->Init();
		m_JumpInitSecondFlg = true;
	}
}


//アニメーションは常に再生されていて、見えた瞬間に初期化する？



