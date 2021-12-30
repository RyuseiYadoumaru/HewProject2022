#pragma once
#include "ydmEngine.h"

using Create::Actor;
#define CHAIR_DISTANCE 3200 - 640

/****	ˆÖŽq	****/
class Chair : public Actor
{
public:
	Chair(string in_Name);
	bool Start() override;
	void Debug() override;
};

