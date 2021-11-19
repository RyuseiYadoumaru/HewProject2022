#pragma once
#include "ydmEngine.h"
using Create::Camera;
using Create::GameObject;

class MainCamera : public Camera
{
public:
	bool Start() override;
	bool Update() override;

	MainCamera(string in_Name);
public:
	void Focus(GameObject* in_Object);

private:
	GameObject* p_FocusObject;
};

