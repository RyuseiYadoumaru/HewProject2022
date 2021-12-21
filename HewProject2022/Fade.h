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
private:

	float fadeSpeed;//フェードするスピード

	enum FadeStatus
	{
		FADE_NO,
		FADE_IN,
		FADE_OUT
	};

	FadeStatus fadeStatus;
};
