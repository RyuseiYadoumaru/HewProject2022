#pragma once
#include"PlayerEffectController.h"
#include "ydmEngine.h"
using Create::Actor;
class PlayerGoalEffect :public Actor
{
public:
	PlayerGoalEffect(string in_Name);
	bool Start() override;
	void EF_Start();
private:
	PlayerEffectController m_PlayerEffectController;
};

