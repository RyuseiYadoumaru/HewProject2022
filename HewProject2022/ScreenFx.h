#pragma once
#include "ydmEngine.h"
using Create::Actor;
using GameEngine::Input;

class ScreenFx : public Actor
{
public:
	ScreenFx(string in_Name);
	bool Start() override;
	bool Update() override;

};

