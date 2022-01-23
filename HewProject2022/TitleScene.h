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

		/* ゲーム終了 */
		Actor* m_GameEnd;
		Actor* m_EndCursor;


		/*	エフェクト	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		//ゲーム終了処理用フラグ
		bool End_flg = false;//true=(ゲーム終了) ・ false=(そのまま)
		bool EndWin_flg = false;//true=(ゲーム終了ウインドウの表示 )・ false=(ゲーム終了ウインドウの非表示)
	};
}
