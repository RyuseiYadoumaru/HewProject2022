//*****************************************************************************
//!	@file	Engine/Timer/GameTimer.h
//!	@brief	
//!	@note	ゲームタイマークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
namespace GameEngine
{
	class GameTimer
	{
	public:
		GameTimer();
		static GameTimer* Instance();

		static void Update();
		static float deltaTime();
		static float fixedDeltaTime();

	private:
		static float m_CurrenTime;
		static float m_OldTime;
		static float m_TotalFrameCnt;

	};
}

