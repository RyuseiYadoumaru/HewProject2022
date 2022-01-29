#pragma once
#include "ydmEngine.h"
using Create::Actor;

class waku :public Actor
{
public:
	waku(string in_Name);
	bool Start() override;
	bool Update() override;

};

