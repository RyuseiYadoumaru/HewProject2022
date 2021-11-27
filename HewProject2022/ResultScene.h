#pragma once
#include "ydmEngine.h"
#include "Test.h"
using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class ResultScene : public Create::Scene
	{
	private:
		shared_ptr<Actor> m_ResultText;//リザルトテキストの画像

	public:
		bool Start() override;

		STATE Update() override;

		bool End() override;

		bool Render() override;

	};

}


