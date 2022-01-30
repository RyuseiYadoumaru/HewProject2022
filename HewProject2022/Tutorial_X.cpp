#include "Tutorial_X.h"
#include "Player.h"

Tutorial_X::Tutorial_X(string in_Name)
{
}

bool Tutorial_X::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "X";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//初期は透明で見えない
	//m_SpriteRenderer->Color.a = 1.0f;
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(X_TUTORIAL_X, X_TUTORIAL_Y, X_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_Tutorial_XYAnimController);

	m_Start_X_TutorialFlg = false;
	m_PerfectLook_X_TutorialFlg = false;
	m_EndStart_X_TutorialFlg = false;
	m_End_X_TutorialFlg = false;

	return true;
}

bool Tutorial_X::Update()
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//本棚の手前らへんにプレイヤーが到着したら、
	if ((transform->Position.x - m_Player->GetTransform().Position.x) <= 300) {
		m_Start_X_TutorialFlg = true;
	}
	if (m_Start_X_TutorialFlg == true && m_PerfectLook_X_TutorialFlg == false) {//徐々に見えるようになる。
		m_SpriteRenderer->Color.a += 0.03f;
		if (m_SpriteRenderer->Color.a >= 1.0) {
			m_SpriteRenderer->Color.a = 1.0f;
			m_Start_X_TutorialFlg = false;//徐々に見える段階終了　　　無駄なフラグ多すぎ！！
			m_PerfectLook_X_TutorialFlg = true;//完全に見えた
		}
	}

	if (m_Player->m_LandTile->GetLandTile() == LandGround) return true;

	if ((Input::GetKeyTrigger(PK_Q) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_X) == true) &&//キーでQまたはコントローラーでXを押したら
		(m_PerfectLook_X_TutorialFlg == true && m_Player->m_LandTile->GetLandTile()->GetKind() == RED_BLOCK) ||
		(m_PerfectLook_X_TutorialFlg == true && m_Player->m_LandTile->GetLandTile()->GetKind() == BLUE_BLOCK) ||
		(m_PerfectLook_X_TutorialFlg == true && m_Player->m_LandTile->GetLandTile()->GetKind() == GREEN_BLOCK)
		) {//プレイヤーが赤のカラーブロックの上
		m_EndStart_X_TutorialFlg = true;
	}
	if (m_EndStart_X_TutorialFlg == true && m_End_X_TutorialFlg == false) {//消え始める
		m_SpriteRenderer->Color.a -= 0.03f;
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;
			m_EndStart_X_TutorialFlg = false;//徐々に消える段階終了
			m_End_X_TutorialFlg = true;//完全に消えた
		}
	}
	return true;
}

