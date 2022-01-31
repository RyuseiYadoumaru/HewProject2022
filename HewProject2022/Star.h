#pragma once
#include"ydmEngine.h"
#include"StarAnimController.h"
using Create::Actor;
class Star :public Actor
{
public:
	Star(string in_Name);
	bool Start() override;
	void Anim_Start1();
	void Anim_Start2();
	void Anim_Start3();
	void StarChecker(int star);

private:
	StarAnimController m_StarAnimController;//‰Ô‰Î

	bool is_Star = false;
};

