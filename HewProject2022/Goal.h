#pragma once
#include "ydmEngine.h"
using Create::Actor;

class Goal :public Actor
{
public:
	Goal(string in_Name);
	bool Start() override;
	
	bool Change_Result();
};

