#pragma once
#include "ydmEngine.h"
using Create::Actor;

#define CUHSION_DISTANCE 3200 - 640

/****	�N�b�V����	****/
class Cuhsion : public Actor
{
public:
	Cuhsion(string in_Name);
	bool Start() override;
	void Debug() override;

};

