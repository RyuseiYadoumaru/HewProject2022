#pragma once
#include "ydmEngine.h"
#include "Test.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "MiniBook.h"
#include "BigBook.h"
#include "Sofa.h"
#include "Ceiling.h"
#include"PushAny.h"
#include"Title.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class TitleScene : public Create::Scene
	{
	private:

		/*	背景	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		LayerFront*		m_LayerFront;

		/* タイトル */
		Title*  m_Title;
		PushAny* m_PushAny;

		Title* m_TeamLogo;


		/*	エフェクト	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}


