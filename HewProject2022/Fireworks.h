#pragma once
#include"ydmEngine.h"
#include"FireworkController.h"
using Create::Actor;
class Fireworks :public Actor
{
public:
	Fireworks(string in_Name);
	bool Start() override;
	void Anim_Start();

private:
	FireworkController m_FireworkController;//‰Ô‰Î
};


