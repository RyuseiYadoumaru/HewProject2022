#pragma once
#include "ydmEngine.h"
#include "MainCamera.h"
#include "PushAny.h"
#include "Title.h"
#include "SceneTransition.h"
#include "BackGround.h"

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

		SceneTransition* m_SceneTransition;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		//ゲーム終了処理用フラグ
		bool End_flg = false;//true=(ゲーム終了) ・ false=(そのまま)
		bool EndWin_flg = false;//true=(ゲーム終了ウインドウの表示 )・ false=(ゲーム終了ウインドウの非表示)
		bool EndGame;
		bool isPlaySound;

	private:
		static constexpr FRAME FinishWaitFrame = 30.0f;	//終了待機フレーム
		FRAME FinFrame = 0.0f;


	};
}
