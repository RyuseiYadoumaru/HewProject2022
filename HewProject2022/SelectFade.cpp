#include "Fade.h"
#include "SelectFade.h"

SelectFade::SelectFade(string in_Name)
{
}

bool SelectFade::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "white";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	/*m_SpriteRenderer->Color.a = 0.0f;*/
	m_SpriteRenderer->Init();

	transform->Scale.Set(10.0f, 10.0f, 0.0f);
	transform->Position.Set(0.0f, 0.0f, 0.0f);

	fadeStatus = FADE_IN;//開始とともにフェードイン開
	fadeSpeed = 0.01f;//フェードするスピード

	m_FadeFlg = true;
	return true;
}

bool SelectFade::Update()
{
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
		//this->m_SpriteRenderer->Color.Set(0.0f, 0.0f, 0.0f, 0.0f);//色を真っ黒にし、透明にする
		m_SpriteRenderer->Color.a += fadeSpeed;
		if (m_SpriteRenderer->Color.a > 1.0f) {
			fadeStatus = FADE_NO; // フェードなし
			m_SpriteRenderer->Color.a = 1.0f;
		}
	}

	return true;
}
