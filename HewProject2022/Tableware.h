#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Math::Vector3;
using Create::Actor;
class Tableware : public Actor
{
public:
	Tableware(string in_Name);
	bool Start() override;
	void Debug() override;
};

