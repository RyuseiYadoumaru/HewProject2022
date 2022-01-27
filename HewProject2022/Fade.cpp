#include "Fade.h"

Fade::Fade(string in_Name) : Actor(in_Name)
{
}

bool Fade::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Black";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->Init();
	m_SpriteRenderer->Color.Set(1.0f, 1.0f, 1.0f, 1.0f);

	transform->Scale.Set(10.0f, 10.0f, 0.0f);
	transform->Position.Set(0.0f, 0.0f, 0.0f);

	//fadeStatus = FADE_NO;
	fadeStatus = FADE_IN;//開始とともにフェードイン開始
	//fadeSpeed = 0.0035f;//フェードするスピード
	fadeSpeed = 0.01f;//フェードするスピード

	m_FadeFlg = true;
	return true;
}

bool Fade::Update()
{
	//フェードイン、フェードアウト中は操作できないようにする
	//if (fadeStatus == FADE_NO) {

	//	//フェードイン
	//	if (Input::GetKeyTrigger(PK_1) || Input::GetControllerTrigger(XINPUT_GAMEPAD_B)) {
	//		m_FadeFlg = true;//プレイヤー操作不可能
	//		fadeStatus = FADE_IN;
	//	}
	//	//フェードアウト
	//	if (Input::GetKeyTrigger(PK_2) || Input::GetControllerTrigger(XINPUT_GAMEPAD_B)) {
	//		m_FadeFlg = true;//プレイヤー操作不可能
	//		fadeStatus = FADE_OUT;
	//	}
	//}

	//ステートマシン
	switch (fadeStatus)
	{
	case Fade::FADE_NO://リザルトからシーン遷移可能
		//ここではプレイヤーを操作できる
		m_FadeFlg = false;//プレイヤー操作可能 
		break;

	case Fade::FADE_IN:
		m_FadeFlg = true;//プレイヤー操作不可能 
		//this->m_SpriteRenderer->Color.Set(1.0f, 1.0f, 1.0f, 1.0f);//色を真っ黒にする
		m_SpriteRenderer->Color.a -= fadeSpeed;
		if (m_SpriteRenderer->Color.a < 0.0f) {
			fadeStatus = FADE_NO; // フェードなし
			m_SpriteRenderer->Color.a = 0.0f;
		}
		break;
	case Fade::FADE_OUT://リザルトからシーン遷移不可能
		m_FadeFlg = true;//プレイヤー操作不可能
		//this->m_SpriteRenderer->Color.Set(1.0f, 1.0f, 1.0f, 0.0f);//色を真っ黒にし、透明にする
		m_SpriteRenderer->Color.a += fadeSpeed;
		if (m_SpriteRenderer->Color.a > 1.0f) {
			fadeStatus = FADE_NO; // フェードなし
			m_SpriteRenderer->Color.a = 1.0f;
		}

	case Fade::FADE_WHITE_IN:
		m_FadeFlg = true;//プレイヤー操作不可能
		//this->m_SpriteRenderer->Color.Set(0.1f, 0.1f, 0.1f, 0.0f);//色を真っ白にする
		m_SpriteRenderer->Color.a -= m_WhiteFadeSpeed;//白くする
		if (m_SpriteRenderer->Color.a > 1.0f) {//真っ白になったら
			fadeStatus = FADE_NO; // フェードなし
			m_SpriteRenderer->Color.a = 0.0f;
		}
		break;
	case Fade::FADE_WHITE_OUT:
		m_FadeFlg = true;//プレイヤー操作不可能
		//this->m_SpriteRenderer->Color.Set(0.1f, 0.1f, 0.1f, 0.0f);//色を白っぽくし、透明にする
		m_SpriteRenderer->Color.a += m_WhiteFadeSpeed;//白くする
		if (m_SpriteRenderer->Color.a > 1.0f) {//真っ白になったら
			fadeStatus = FADE_NO; // フェードなし
			m_SpriteRenderer->Color.a = 1.0f;
		}
		break;
	}

	return true;
}
