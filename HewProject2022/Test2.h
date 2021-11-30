#pragma once
#include "ydmEngine.h"
using Create::Actor;
using Create::Character;
using GameEngine::Input;

namespace GamePlay
{
	class Test2 : public Character
	{
	private:
		float m_Speed;

	public:
		Test2(string in_Name);
		bool Start() override;
		bool Update() override;

	};

}

