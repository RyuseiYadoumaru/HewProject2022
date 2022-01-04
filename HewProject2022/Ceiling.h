#pragma once
#include "ydmEngine.h"
using Create::Actor;

/****	îwåi	****/
class Ceiling : public Actor
{
public:
	Ceiling(string in_Name);
	bool Start() override;
};
