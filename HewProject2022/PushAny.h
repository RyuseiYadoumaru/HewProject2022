#pragma once
#include"ydmEngine.h"
using Create::Actor;

class PushAny :public Actor
{
public:
	float alpha = 0.0f;
	int flash= 0;

	PushAny(string in_Name);
	bool Start() override;
	bool Flashing();


};

