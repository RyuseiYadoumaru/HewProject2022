#pragma once
#include"ydmEngine.h"
#include"SelectAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class SelectTutorial : public Actor
{
public:
	SelectTutorial(string in_Name);
public:
	bool Start() override;
	bool Update() override;

private:
	SelectAnimController m_SelectAnimController;

};

