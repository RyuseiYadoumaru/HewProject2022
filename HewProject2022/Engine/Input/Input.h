//*****************************************************************************
//!	@file	Engine/Input/Input.h
//!	@brief	
//!	@note	“ü—ÍƒNƒ‰ƒX
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../Runtime/Core/InputInfo.h"
#include "../Timer/GameTimer.h"
#include <map>
#include <DirectXMath.h>

using VIBRATION = WORD;

namespace GameEngine
{
	class Input
	{
	public:
		static void KeyUpdate();
		static bool GetKeyPress(int vkey);
		static bool GetKeyTrigger(int vkey);

	public:
		static bool GetControllerPress(int Xbuttom);
		static bool GetControllerTrigger(int Xbuttom);

		static DirectX::XMFLOAT2 GetControllerLeftStick();
		static DirectX::XMFLOAT2 GetControllerRightStick();

		static VIBRATION LeftVibration(VIBRATION in_Power, TIME time = NULL);
		static VIBRATION RightVibration(VIBRATION in_Power, TIME time = NULL);
		static VIBRATION Vibration(VIBRATION in_Power, TIME time = NULL)
			;
		static void LeftVibrationStop();
		static void RightVibrationStop();


	private:
		static BYTE m_KeyState[256];
		static BYTE m_OldKeyState[256];

	private:
		static XINPUT_VIBRATION m_Vibration;

		static XINPUT_STATE m_GamePadState;
		static XINPUT_STATE m_OldGamePadState;

		static TIME m_LeftTime;
		static TIME m_RightTime;
		static TIME m_Time;



	};
}
