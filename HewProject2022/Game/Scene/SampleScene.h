#pragma once
#include "../../ydmEngine.h"
#include "../../Test.h"
using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class SampleScene : public Create::Scene
	{
	private:
		shared_ptr<Test> Hanamaru;
	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;

	};

}


