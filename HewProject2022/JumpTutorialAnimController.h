#pragma once
#include "ydmEngine.h"
#include "JumpTutorialAnim.h"

class JumpTutorialAnimController :public Create::AnimationController
{
public:
	bool Init() override;
	void Update() override;
};

