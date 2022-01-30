#pragma once
#include "ydmEngine.h"
using Create::Actor;

#define MAX_STAR_SIZE (78.0f)

class UI_Star :public Actor
{
public:
	UI_Star(string in_Name);
	bool Start() override;
	bool Update() override;
	bool Render() override;
	bool End() override;
};

