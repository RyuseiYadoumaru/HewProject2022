#pragma once
#include"ydmEngine.h"
#include"SceneTransitionAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class SceneTransition :public Actor
{
public:
	SceneTransition(string in_Name);

public:
	bool Start() override;
	bool Update() override;

	bool m_KeyOperation;//�L�[����s�t���O

	static bool m_SceneTransitionFlg;

private:
	SceneTransitionAnimController m_SceneTransitionAnimController;
};

