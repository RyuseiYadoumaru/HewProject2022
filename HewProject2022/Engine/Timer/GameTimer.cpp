//*****************************************************************************
//!	@file	Engine/Timer/GameTimer.cpp
//!	@brief	
//!	@note	ゲームタイマークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "GameTimer.h"
#include "../Runtime/Application.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
using namespace GameEngine;

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
float GameTimer::m_CurrenTime = 0.0f;
float GameTimer::m_OldTime = 0.0f;
float GameTimer::m_TotalFrameCnt = 0.0f;

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
GameTimer::GameTimer()
{
}

//==============================================================================
//!	@fn		Instance
//!	@brief	ゲームタイマー生成
//!	@retval	インスタンス
//==============================================================================
GameTimer* GameTimer::Instance()
{
	static GameTimer Instance;
	return &Instance;
}


//==============================================================================
//!	@fn		Update
//!	@brief	ゲームタイマー更新
//!	@retval	
//==============================================================================
void GameEngine::GameTimer::Update()
{
	//前フレームの時間代入
	m_OldTime = m_CurrenTime;

	//現在の時間を取得
	m_CurrenTime = timeGetTime();

	//ゲーム全体のフレームカウント
	m_TotalFrameCnt++;
}

//==============================================================================
//!	@fn		deltaTime
//!	@brief	デルタタイム
//!	@retval	デルタタイム	
//==============================================================================
TIME GameEngine::GameTimer::deltaTime()
{
	return m_CurrenTime - m_OldTime;
}

//==============================================================================
//!	@fn		fixedDeltaTime
//!	@brief	固定デルタタイム
//!	@retval	固定デルタタイム	
//==============================================================================
TIME GameEngine::GameTimer::fixedDeltaTime()
{
	return 1.0f / Application::FPS;
}

//==============================================================================
//!	@fn		NowFrameCount
//!	@brief	現在のトータルフレーム数
//!	@retval	トータルフレーム
//==============================================================================
FRAME GameEngine::GameTimer::NowFrameCount()
{
	return m_TotalFrameCnt;
}
