#pragma once
#include "../../ydmEngine.h"
#include "../../Test.h"
#include "../../Test2.h"
using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class SampleScene : public Create::Scene
	{
	private:
		shared_ptr<Test> Hanamaru;
		//Test* Player;
		//Test2* Block;
		shared_ptr<Test2> Teee;
	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;

	};

}


