#pragma once
#include "ydmEngine.h"
#include "PlayerAnimController.h"
using Create::Character;

class AnimTest : public Character
{
public:
	AnimTest(string in_Name);
	bool Start()override;
	bool Update() override;

	PlayerAnimController P_AnimController;

};

