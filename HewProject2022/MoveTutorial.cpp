#include "MoveTutorial.h"
#include "Player.h"

using namespace Create;

MoveTutorial::MoveTutorial(string in_Name)
{
}

bool MoveTutorial::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "L";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//初期は透明で見えない
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(MOVE_TUTORIAL_X, MOVE_TUTORIAL_Y, MOVE_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_TutorialAnimController);

	m_StartMoveTutorialFlg = false;
	m_PerfectLookMoveTutorialFlg = false;

	m_EndStartMoveTutorialFlg = false;
	m_EndMoveTutorialFlg = false;

	return true;
}

bool MoveTutorial::Update()//ここで透明にする処理とか書けばいいんかな
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	if (m_PerfectLookMoveTutorialFlg == false) {//ゲームスタートと同時に完全に見えるようになるまで見えるようにする
		m_StartMoveTutorialFlg = true;//見え始めた
		m_SpriteRenderer->Color.a += 0.03f;

		if (m_SpriteRenderer->Color.a >= 1.0f) {
			m_SpriteRenderer->Color.a = 1.0f;
			m_StartMoveTutorialFlg = false;//徐々に見え始める段階終了
			m_PerfectLookMoveTutorialFlg = true;//完全に見えた
		}
	}

	if (m_Player->GetTransform().Position.x >= transform->Position.x) {//通り過ぎたら消える
		m_EndStartMoveTutorialFlg = true;
	}
	if (m_EndStartMoveTutorialFlg == true) {//消え始めた
		m_SpriteRenderer->Color.a -= 0.03f;
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_EndStartMoveTutorialFlg = false;//徐々に消え始める段階終了
			m_EndMoveTutorialFlg = true;//完全に消えた
		}
	}

	return true;
}
