#pragma once
#include "ydmEngine.h"
#include "MainCamera.h"

using Create::Actor;

class waku :public Actor
{
public:
	waku(string in_Name);
	bool Start() override;
	bool Update() override;

	/*	�I�u�W�F�N�g	*/
	MainCamera*		m_MainCamera;
};

