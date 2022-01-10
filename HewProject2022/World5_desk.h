#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Math::Vector3;
using Create::Actor;
class World5_desk : public Actor
{
public:
	World5_desk(string in_Name);
	bool Start() override;
	void Debug() override;
};

