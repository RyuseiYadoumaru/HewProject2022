#pragma once
#include "ydmEngine.h"
using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Test : public Actor
	{
	private:
		float m_Speed;

	public:
		Test(string in_Name);
		bool Start() override;
		bool Update() override;

	};

}

