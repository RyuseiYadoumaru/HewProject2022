#pragma once
#include "ydmEngine.h"
#include "DefaultAnim.h"

using Create::AnimationController;


enum
{
	P_LEFT,
	P_RIGHT,
	P_UP,
	P_DOWN
};

class DefaultAnimController : public AnimationController
{
public:
	bool Init() override;
	void Update() override;

};

