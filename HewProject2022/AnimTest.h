#pragma once
#include "ydmEngine.h"
#include "DefaultAnimController.h"
using Create::Character;

class AnimTest : public Character
{
public:
	AnimTest(string in_Name);
	bool Start()override;
	bool Update() override;

	DefaultAnimController P_AnimController;

};

