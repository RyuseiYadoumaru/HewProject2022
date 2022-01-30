#pragma once
#include "ydmEngine.h"
#include "UI_Star.h"
#include "UI_StarList.h"

using Create::Actor;

class PlayModeUI :public Actor
{
public:
	PlayModeUI(string in_Name);
	bool Start() override;
	bool Update() override;
	bool Render() override;

	/*	オブジェクト	*/
	MainCamera*		m_MainCamera;

	UI_StarList* m_StarList;
};