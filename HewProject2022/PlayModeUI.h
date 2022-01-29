#pragma once
#include "ydmEngine.h"
using Create::Actor;

class PlayModeUI :public Actor
{
public:
	PlayModeUI(string in_Name);
	bool Start() override;
	bool Update() override;

};