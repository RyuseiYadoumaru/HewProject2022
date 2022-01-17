#pragma once
#include "ydmEngine.h"
#include "Test.h"
#include "Fade.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include"PushAny.h"
#include"Title.h"
#include"Pause.h"
#include"Result.h"

using Create::Actor;
using GameEngine::Input;


namespace GamePlay
{
	class ResultScene : public Create::Scene
	{
	private:
		Actor* m_ResultText;//リザルトテキストの画像
		Result* m_Cursor;

		BackGround* m_BackGround;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

	};

}

