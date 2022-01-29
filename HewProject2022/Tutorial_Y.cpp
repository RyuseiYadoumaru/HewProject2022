#include "Tutorial_Y.h"
#include "Player.h"
#include "Result.h"

Tutorial_Y::Tutorial_Y(string in_Name)
{
}

bool Tutorial_Y::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Y";
	m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 0.0f;//初期は透明で見えない
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(Y_TUTORIAL_X, Y_TUTORIAL_Y, Y_TUTORIAL_Z);
	transform->Scale.Set(0.5f, 0.5f, 0.5f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_Tutorial_XYAnimController);

	m_Start_Y_TutorialFlg = false;
	m_PerfectLook_Y_TutorialFlg = false;
	m_EndStart_Y_TutorialFlg = false;
	m_End_Y_TutorialFlg = false;

	return true;
}

bool Tutorial_Y::Update()
{

	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	Result* m_Result = Create::Scene::GetGameObject<Result>("ResultCursor");

	if (m_Result->NowScene == "Stage3") {//ここはステージ３でしか入らないようにしたい

		//手前らへんにプレイヤーが到着したら、
		if ((transform->Position.x - m_Player->GetTransform().Position.x) <= 200) {
			m_Start_Y_TutorialFlg = true;
		}
		if (m_Start_Y_TutorialFlg == true && m_PerfectLook_Y_TutorialFlg == false) {//徐々に見えるようになる。
			m_SpriteRenderer->Color.a += 0.03f;
			if (m_SpriteRenderer->Color.a >= 1.0) {
				m_SpriteRenderer->Color.a = 1.0f;
				m_Start_Y_TutorialFlg = false;//徐々に見える段階終了　　　無駄なフラグ多すぎ！！
				m_PerfectLook_Y_TutorialFlg = true;//完全に見えた
			}
		}

		if ((Input::GetKeyTrigger(PK_R) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_Y) == true) &&//キーでRまたはコントローラーでYを押したら
			m_PerfectLook_Y_TutorialFlg == true) {
			m_EndStart_Y_TutorialFlg = true;
		}
		if (m_EndStart_Y_TutorialFlg == true && m_End_Y_TutorialFlg == false) {//消え始める
			m_SpriteRenderer->Color.a -= 0.03f;
			if (m_SpriteRenderer->Color.a <= 0.0f) {
				m_SpriteRenderer->Color.a = 0.0f;
				m_EndStart_Y_TutorialFlg = false;//徐々に消える段階終了
				m_End_Y_TutorialFlg = true;//完全に消えた
			}
		}
	}
	return true;
}


