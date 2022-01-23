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

	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "TutorialEffect";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//初期は透明で見えない
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(m_MoveTutorial->transform->Position.x, m_MoveTutorial->transform->Position.y, m_MoveTutorial->transform->Position.z);//移動チュートリアルと同じ位置
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_TutoriaEffectlAnimController);

	m_MoveTutorialEffectFlg = false;
	m_JumpTutorialEffectFlg = false;

	return true;
}

bool TutorialEffect::Update()
{
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");
	JumpTutorial* m_JumpTutorial = Create::Scene::GetGameObject<JumpTutorial>("JumpTutorial");

	//////移動チュートリアル////
	if (m_MoveTutorialEffectFlg == false) {
		if (m_MoveTutorial->GetTutorialStartFlg() == true) {
			//見えるようになって
			m_SpriteRenderer->Color.a = 1.0f;
			//アニメーションを再生
		}
		//移動チュートリアルが完全に見えたら見えなくなる
		if (m_MoveTutorial->GetTutorialLookPerfectFlg() == true) {
			m_SpriteRenderer->Color.a = 0.0f;
		}
		//移動チュートリアルが消え始めた時にもう一度見える
		if (m_MoveTutorial->GetTutorialEndStartFlg() == true) {
			m_SpriteRenderer->Color.a = 1.0f;
		}
		//移動チュートリアルが見えなくなったら消える
		if (m_MoveTutorial->GetTutorialEndFlg() == true) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_MoveTutorialEffectFlg = true;
		}
	}


	////ジャンプチュートリアル////
	if (m_JumpTutorialEffectFlg == false) {
		if (m_JumpTutorial->GetTutorialStartFlg() == true) {
			//座標をジャンプチュートリアルと同じところにする
			transform->Position.Set(m_JumpTutorial->transform->Position.x, m_JumpTutorial->transform->Position.y, m_JumpTutorial->transform->Position.z);
			//見えるようになる
			m_SpriteRenderer->Color.a = 1.0f;
		}
		//ジャンプチュートリアルが完全に見えたら見えなくなる
		if (m_JumpTutorial->GetTutorialLookPerfectFlg() == true) {
			m_SpriteRenderer->Color.a = 0.0f;
		}
		//ジャンプチュートリアルが消え始めた時にもう一度見える
		if (m_JumpTutorial->GetTutorialEndStartFlg() == true) {
			m_SpriteRenderer->Color.a = 1.0f;
		}
		//ジャンプチュートリアルが見えなくなったら消える
		if (m_JumpTutorial->GetTutorialEndFlg() == true) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_JumpTutorialEffectFlg = true;
		}
	}

	return true;
}

