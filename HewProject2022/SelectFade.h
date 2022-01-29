#pragma once
#include "ydmEngine.h"
using Create::Actor;
using GameEngine::Input;

class SelectFade : public Actor
{
public:
	SelectFade(string in_Name);
	bool Start() override;
	bool Update() override;

	bool Get_FadeFlg() { return m_FadeFlg; };

	enum FadeStatus
	{
		FADE_NO,

		FADE_IN,
		FADE_OUT,
	};
	FadeStatus GetFadeStatus() {
		return fadeStatus;
	}

	void SetFadeStatus(FadeStatus fadePattern) {
		fadeStatus = fadePattern;
	}

	void SetFadeFlg(bool flg) {
		m_FadeFlg = flg;
	}

	//private:

	bool m_FadeFlg;//フェードするフラグ

	float fadeSpeed;//フェードするスピード

	float m_WhiteFadeSpeed;

	FadeStatus fadeStatus;
};