#include "JumpTutorial.h"
#include "Player.h"

using namespace Create;

JumpTutorial::JumpTutorial(string in_Name)
{
}

bool JumpTutorial::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "A";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//初期は透明で見えない
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(JUMP_TUTORIAL_X, JUMP_TUTORIAL_Y, JUMP_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	アニメーションコンポーネント	*/
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

	//本棚の手前らへんにプレイヤーが到着したら、
	if ((transform->Position.x - m_Player->GetTransform().Position.x) <= 200) {
		m_StartJumpTutorialFlg = true;
	}
	if (m_StartJumpTutorialFlg == true && m_PerfectLookJumpTutorialFlg == false) {//徐々に見えるようになる。
		m_SpriteRenderer->Color.a += 0.03f;
		if (m_SpriteRenderer->Color.a >= 1.0) {
			m_SpriteRenderer->Color.a = 1.0f;
			m_StartJumpTutorialFlg = false;//徐々に見える段階終了　　　無駄なフラグ多すぎ！！
			m_PerfectLookJumpTutorialFlg = true;//完全に見えた
		}
	}

	if (m_Player->GetTransform().Position.x >= transform->Position.x) {//通り過ぎたら
		m_EndStartJumpTutorialFlg = true;
	}
	if (m_EndStartJumpTutorialFlg == true && m_EndJumpTutorialFlg == false) {//消え始める
		m_SpriteRenderer->Color.a -= 0.03f;
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_EndStartJumpTutorialFlg = false;//徐々に消える段階終了
			m_EndJumpTutorialFlg = true;//完全に消えた
		}
	}



	return true;
}
