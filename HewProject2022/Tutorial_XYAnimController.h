#pragma once
#include "ydmEngine.h"
#include "Tutorial_XYAnim.h"

class Tutorial_XYAnimController :public Create::AnimationController
{
public:
	bool Init() override;
	void Update() override;
};

