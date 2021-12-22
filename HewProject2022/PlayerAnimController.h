#pragma once
#include "ydmEngine.h"
#include "PlayerAnim.h"

using Create::AnimationController;


enum
{
	P_LEFT,
	P_RIGHT,
	P_UP,
	P_DOWN
};

class PlayerAnimController : public AnimationController
{
public:
	bool Init() override;
	void Update() override;

};

