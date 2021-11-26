//*****************************************************************************
//!	@file	Engine/Input/Input.h
//!	@brief	
//!	@note	“ü—ÍƒNƒ‰ƒX
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../Runtime/Core/InputInfo.h"
#include <DirectXMath.h>

namespace GameEngine
{
	class Input
	{
	public:

		static bool GetKeyPress(int vkey);

		static bool GetKeyTrigger(int vkey);

		static bool GetControllerPress(int Xbuttom);
		static bool GetControllerTrigger(int Xbuttom);

		static DirectX::XMFLOAT2 GetControllerLeftStick();
		static DirectX::XMFLOAT2 GetControllerRightStick();

		static void KeyUpdate();

	private:
		static BYTE m_KeyState[256];
		static BYTE m_OldKeyState[256];

	};
}
