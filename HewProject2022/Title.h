#pragma once
#include "ydmEngine.h"
using Create::Actor;
class Title :public Actor
{
public:

	float alpha = 0.0f;
	bool Logo_sw;
	float Frame_cnt = 0;

	Title(string in_Name);
	bool Start() override;
	//bool Bound();
	bool Fade_In();
	bool Fade_Out();
	bool Fade_Switch();

	bool GetLogo_sw();

private:
	float nowTime;
	constexpr static float fadeTime = 2000.0f;

};

