#pragma once
#include "ydmEngine.h"
#include "MainCamera.h"
using Create::Actor;

class PlayModeUI :public Actor
{
public:
	PlayModeUI(string in_Name);
	bool Start() override;
	bool Update() override;

	/*	�I�u�W�F�N�g	*/
	MainCamera*		m_MainCamera;

};