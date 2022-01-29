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

	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "TutorialEffect";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//初期は透明で見えない
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(MOVE_TUTORIAL_X, MOVE_TUTORIAL_Y, MOVE_TUTORIAL_Z);//移動チュートリアルと同じ位置
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	アニメーションコンポーネント	*/
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


	if (m_Result->NowScene == "Stage1") {//ステージ１でしか入らない

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

		////Xチュートリアル////
		if (m_X_TutorialEffectFlg == false) {
			if (m_Tutorial_X->GetTutorialStartFlg() == true) {
				//座標をXチュートリアルと同じところにする
				transform->Position.Set(m_Tutorial_X->transform->Position.x, m_Tutorial_X->transform->Position.y, m_Tutorial_X->transform->Position.z);
				//見えるようになる
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//Xチュートリアルが完全に見えたら見えなくなる
			if (m_Tutorial_X->GetTutorialLookPerfectFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
			}
			//Xチュートリアルが消え始めた時にもう一度見える
			if (m_Tutorial_X->GetTutorialEndStartFlg() == true) {
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//Xチュートリアルが見えなくなったら消える
			if (m_Tutorial_X->GetTutorialEndFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_X_TutorialEffectFlg = true;
			}
		}
	}

	if (m_Result->NowScene == "Stage3") {//ステージ3でしか入らない

		////Yチュートリアル////
		if (m_Y_TutorialEffectFlg == false) {
			if (m_Tutorial_Y->GetTutorialStartFlg() == true) {
				//座標をYチュートリアルと同じところにする
				transform->Position.Set(m_Tutorial_Y->transform->Position.x, m_Tutorial_Y->transform->Position.y, m_Tutorial_Y->transform->Position.z);
				//見えるようになる
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//Yチュートリアルが完全に見えたら見えなくなる
			if (m_Tutorial_Y->GetTutorialLookPerfectFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
			}
			//Yチュートリアルが消え始めた時にもう一度見える
			if (m_Tutorial_Y->GetTutorialEndStartFlg() == true) {
				m_SpriteRenderer->Color.a = 1.0f;
			}
			//Yチュートリアルが見えなくなったら消える
			if (m_Tutorial_Y->GetTutorialEndFlg() == true) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_Y_TutorialEffectFlg = true;
			}
		}
	}
	return true;
}

