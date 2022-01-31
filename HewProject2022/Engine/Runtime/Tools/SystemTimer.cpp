//*****************************************************************************
//!	@file	Engine/Runtime/Tools/SystemTimer.cpp
//!	@brief	
//!	@note	システムタイマークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "SystemTimer.h"
#include "../Application.h"
#include "../../Timer/GameTimer.h"
#include "Log.h"
#pragma comment(lib, "winmm.lib")

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
SystemTimer::SystemTimer()
{
	GetLocalTime(&m_SystemLocalTime);

	m_SystemStartTime = (float)timeGetTime();
	m_WaitTime = 0.0f;
	m_SaveTime = 0.0f;
	m_SystemCounter = 0;

	m_NowFPS = 60;
}

//==============================================================================
//!	@fn		Instance
//!	@brief	システムタイマー生成
//!	@retval	インスタンス
//==============================================================================
SystemTimer* SystemTimer::Instance()
{
	static SystemTimer Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		SystemWait
//!	@brief	処理待ち
//!	@param	FPS
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool SystemTimer::SystemWait(const float FPS)
{
	float BaseTime = GetSystemTime() + 1;

	//処理待ち時間
	m_WaitTime = m_SystemCounter * 1000 / FPS - BaseTime;


	//処理待ち
	if (m_WaitTime > 0)
	{
		Sleep((DWORD)m_WaitTime);
	}
	else
	{
		Sleep(1 / Application::FPS);
	}

	//フレームカウント
	m_SystemCounter++;

	//ゲームタイマー更新
	GameEngine::GameTimer::Update();

	return true;
}

//==============================================================================
//!	@fn		GetSystemCurrentTime
//!	@brief	システム現在時刻取得
//!	@param	
//!	@retval	現在時刻ミリ秒
//==============================================================================
float SystemTimer::GetSystemCurrentTime() const
{
	return (float)timeGetTime();
}

//==============================================================================
//!	@fn		GetSystemTime
//!	@brief	システム経過時間取得
//!	@param	
//!	@retval	経過時間ミリ秒
//==============================================================================
float SystemTimer::GetSystemTime()
{
	return GetSystemCurrentTime() - m_SystemStartTime;
}

//==============================================================================
//!	@fn		GetNowFPS
//!	@brief	現在のフレームレート取得
//!	@param	
//!	@retval	現在のフレームレート
//==============================================================================
float SystemTimer::GetNowFPS()
{
	int IntervalFrame = 30;

	/*	FPS計測	*/
	if (m_SystemCounter % IntervalFrame == 0)
	{
		float CurrentTime = GetSystemTime();


		m_NowFPS = IntervalFrame * 1000.0f / (CurrentTime - m_SaveTime);
		m_SaveTime = CurrentTime;

	}

	return m_NowFPS;
}

//==============================================================================
//!	@fn		GetNowFPS
//!	@brief	現在のフレームレート取得
//!	@param	インターバル
//!	@retval	現在のフレームレート
//==============================================================================
float SystemTimer::GetNowFPS(int in_Interval)
{
	int IntervalFrame = in_Interval;

	/*	FPS計測	*/
	if (m_SystemCounter % IntervalFrame == 0)
	{
		float CurrentTime = GetSystemTime();


		m_NowFPS = IntervalFrame * 1000.0f / (CurrentTime - m_SaveTime);
		m_SaveTime = CurrentTime;

	}

	return m_NowFPS;
}

//==============================================================================
//!	@fn		ErrorFPS
//!	@brief	FPSの異常を検知
//!	@param	
//!	@retval	true:異常　false:正常
//==============================================================================
bool SystemTimer::ErrorFPS()
{
	//fps範囲
	float Min = Application::FPS - ErrorFPSRange;
	float Max = Application::FPS + ErrorFPSRange;

	//異常チェック
	if (m_NowFPS < Min || m_NowFPS > Max) return true;

	//正常
	return false;
}

//==============================================================================
//!	@fn		CheckSytemWait
//!	@brief	処理待ち確認
//!	@param	FPS
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool SystemTimer::CheckSystemWait(const float FPS)
{
	/****	待ち時間確認	****/
	float CheckMaxWaitTime = (1 / FPS) * 2;
	float CheckMinWaitTime = (1 / FPS) / 2;
	if (m_WaitTime > CheckMaxWaitTime || m_WaitTime < CheckMinWaitTime) return false;

	/****	経過時間確認	****/
	if (GetSystemTime() <= 0) return false;

	/****	システムカウンタ確認	****/
	if (m_SystemCounter == NULL) return false;

	/****	現在FPS確認	****/
	if (m_NowFPS > FPS * 1.2 || m_NowFPS < FPS * 0.7) return false;
	return true;
}
