//*****************************************************************************
//!	@file	Engine/Runtime/Tools/SystemTimer.h
//!	@brief	
//!	@note	システムタイマークラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <Windows.h>

class SystemTimer
{
private:

	SYSTEMTIME m_SystemLocalTime;

	float m_SystemStartTime;
	float m_SaveTime;

	UINT m_SystemCounter;

	float m_WaitTime;
	float m_NowFPS;

public:

	SystemTimer();

	static SystemTimer* Instance();

	bool SystemWait(const float FPS);

	float GetSystemCurrentTime() const;
	float GetSystemTime();
	float GetNowFPS();
	float GetNowFPS(int in_Interval);

private:

	bool CheckSystemWait(const float FPS);

};