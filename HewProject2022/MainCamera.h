#pragma once
#include "ydmEngine.h"

using Create::Camera;
using Create::GameObject;
using Math::Vector2;

class MainCamera : public Camera
{
public:
	MainCamera(string in_Name);

	bool Start() override;
	bool Update() override;

public:
	void Range(Vector2& in_TopLeft, Vector2& in_ButtomRight);
	void Focus(GameObject* in_Object);

private:
	Vector2 RangeTopLeft;
	Vector2 RangeButtomRight;
	GameObject* p_FocusObject;
	XMFLOAT2 m_object_distace;
	XMFLOAT2 m_controller_angle;
	XMFLOAT2 m_Save;
public:
	static bool m_CameraMode;
};
