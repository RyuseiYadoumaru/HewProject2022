#pragma once
#include "ydmEngine.h"
#include "SelectAnim.h"

class SelectAnimController :public Create::AnimationController
{

public:
	bool Init() override;
	void Update() override;
};