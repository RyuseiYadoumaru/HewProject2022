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

	bool m_FadeFlg;//�t�F�[�h����t���O

	float fadeSpeed;//�t�F�[�h����X�s�[�h

	float m_WhiteFadeSpeed;

	FadeStatus fadeStatus;
};