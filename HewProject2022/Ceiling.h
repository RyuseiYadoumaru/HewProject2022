#pragma once
#include "ydmEngine.h"
using Create::Actor;

/****	�w�i	****/
class Ceiling : public Actor
{
public:
	Ceiling(string in_Name);
	bool Start() override;
};
