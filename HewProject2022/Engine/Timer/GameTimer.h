//*****************************************************************************
//!	@file	Engine/Timer/GameTimer.h
//!	@brief	
//!	@note	ゲームタイマークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
typedef float FRAME;
typedef float TIME;
namespace GameEngine
{
	class GameTimer
	{
	public:
		GameTimer();
		static GameTimer* Instance();

		static void Update();
		static TIME deltaTime();
		static TIME fixedDeltaTime();
		static FRAME NowFrameCount();
		static bool ErrorFPS();

	private:
		static TIME m_CurrenTime;
		static TIME m_OldTime;
		static FRAME m_TotalFrameCnt;

	};
}

