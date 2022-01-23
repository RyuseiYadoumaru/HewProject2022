#pragma once
#include "ydmEngine.h"
using Create::Actor;
using GameEngine::Input;

class Fade : public Actor
{
public:
	Fade(string in_Name);
	bool Start() override;
	bool Update() override;

	bool Get_FadeFlg() { return m_FadeFlg; };

	enum FadeStatus
	{
		FADE_NO,
		FADE_IN,
		FADE_OUT
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

	FadeStatus fadeStatus;
};
