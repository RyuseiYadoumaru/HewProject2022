#pragma once
#include "ydmEngine.h"
using Create::Actor;
using GameEngine::Input;

class CameraFrame : public Actor
{
public:
	CameraFrame(string in_Name);
	bool Start() override;
	bool Update() override;

};

