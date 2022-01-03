//*****************************************************************************
//!	@file	Engine/Input/Input.cpp
//!	@brief	
//!	@note	入力
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "Input.h"


/****	スタティックメンバ変数	****/
BYTE GameEngine::Input::m_KeyState[256];

std::map<int, bool> GameEngine::Input::m_GamePadState;
std::map<int, bool> GameEngine::Input::m_OldGamePadState;

/****	グローバル変数	****/
short gKeys[0xff];
short gOldKeys[0xff];

XINPUT_STATE g_PadState;
XINPUT_STATE g_OldPadState;


bool isDown;


/****	XInput入力データ	****/
const int XInput::Buttom::A = XINPUT_GAMEPAD_A;
const int XInput::Buttom::B = XINPUT_GAMEPAD_B;
const int XInput::Buttom::X = XINPUT_GAMEPAD_X;
const int XInput::Buttom::Y = XINPUT_GAMEPAD_Y;

const int XInput::Buttom::UP = XINPUT_GAMEPAD_DPAD_UP;
const int XInput::Buttom::DOWN = XINPUT_GAMEPAD_DPAD_DOWN;
const int XInput::Buttom::LEFT = XINPUT_GAMEPAD_DPAD_LEFT;
const int XInput::Buttom::RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT;

const int XInput::Buttom::START = XINPUT_GAMEPAD_START;
const int XInput::Buttom::BACK = XINPUT_GAMEPAD_BACK;

const int XInput::Buttom::LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB;
const int XInput::Buttom::RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB;
const int XInput::Buttom::LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER;
const int XInput::Buttom::RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER;


//==============================================================================
//!	@fn		GetKeyPress
//!	@brief	トリガー
//!	@param	キーインデックス
//!	@retval	入力判定
//==============================================================================
bool GameEngine::Input::GetKeyPress(int vkey)
{
	return (gKeys[vkey] & 0x8000) != 0;

}

//==============================================================================
//!	@fn		GetKeyTrigger
//!	@brief	トリガー
//!	@param	キーインデックス
//!	@retval	入力判定
//==============================================================================
bool GameEngine::Input::GetKeyTrigger(int vkey)
{
	bool condition1 = (gKeys[vkey] & 0x8000) != 0;
	bool condition2 = (gOldKeys[vkey] & 0x8000) == 0;

	return condition1 && condition2;
}

//==============================================================================
//!	@fn		GetControllerPress
//!	@brief	コントローラプレス
//!	@param	コントローラインデックス
//!	@retval	入力判定
//==============================================================================
bool GameEngine::Input::GetControllerPress(int Xbuttom)
{
	return (g_PadState.Gamepad.wButtons & Xbuttom);
}

//==============================================================================
//!	@fn		GetControllerTrigger
//!	@brief	コントローラトリガー
//!	@param	コントローラインデックス
//!	@retval	入力判定
//==============================================================================
bool GameEngine::Input::GetControllerTrigger(int Xbuttom)
{
	if (g_PadState.Gamepad.wButtons & Xbuttom)
	{
		m_GamePadState[Xbuttom] = true;

		if (m_OldGamePadState[Xbuttom] == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	m_GamePadState[Xbuttom] = false;
	return false;
}

//==============================================================================
//!	@fn		GetControllerLeftStick
//!	@brief	左スティック入力
//!	@param	
//!	@retval	アナログパラメータ(0.0〜1.0)
//==============================================================================
DirectX::XMFLOAT2 GameEngine::Input::GetControllerLeftStick()
{
	DirectX::XMFLOAT2 stick;

	stick.x = g_PadState.Gamepad.sThumbLX / 32767.0f;
	stick.y = -g_PadState.Gamepad.sThumbLY / 32767.0f;

	return stick;
}

//==============================================================================
//!	@fn		GetControllerRightStick
//!	@brief	右スティック入力
//!	@param	
//!	@retval	アナログパラメータ(0.0〜1.0)
//==============================================================================
DirectX::XMFLOAT2 GameEngine::Input::GetControllerRightStick()
{
	DirectX::XMFLOAT2 stick;

	stick.x = g_PadState.Gamepad.sThumbRX / 32767.0f;
	stick.y = -g_PadState.Gamepad.sThumbRY / 32767.0f;

	return stick;
}

//==============================================================================
//!	@fn		KeyUpdate
//!	@brief	キー更新
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::Input::KeyUpdate()
{
	/*	1フレーム前のキー状態を保存	*/
	memcpy(gOldKeys, gKeys, sizeof(gKeys));


	/****	キー情報を取得	****/
	gKeys[PK_0] = GetAsyncKeyState(PK_0);				//0
	gKeys[PK_1] = GetAsyncKeyState(PK_1);				//1
	gKeys[PK_2] = GetAsyncKeyState(PK_2);				//2
	gKeys[PK_3] = GetAsyncKeyState(PK_3);				//3
	gKeys[PK_4] = GetAsyncKeyState(PK_4);				//4
	gKeys[PK_5] = GetAsyncKeyState(PK_5);				//5
	gKeys[PK_6] = GetAsyncKeyState(PK_6);				//6
	gKeys[PK_7] = GetAsyncKeyState(PK_7);				//7
	gKeys[PK_8] = GetAsyncKeyState(PK_8);				//8
	gKeys[PK_9] = GetAsyncKeyState(PK_9);				//9
	gKeys[PK_F1] = GetAsyncKeyState(PK_F1);				//F1
	gKeys[PK_F2] = GetAsyncKeyState(PK_F2);				//F2
	gKeys[PK_F3] = GetAsyncKeyState(PK_F3);				//F3
	gKeys[PK_F4] = GetAsyncKeyState(PK_F4);				//F4
	gKeys[PK_F5] = GetAsyncKeyState(PK_F5);				//F5
	gKeys[PK_F6] = GetAsyncKeyState(PK_F6);				//F6
	gKeys[PK_F7] = GetAsyncKeyState(PK_F7);				//F7
	gKeys[PK_F8] = GetAsyncKeyState(PK_F8);				//F8
	gKeys[VK_UP] = GetAsyncKeyState(VK_UP);				//上キー
	gKeys[VK_DOWN] = GetAsyncKeyState(VK_DOWN);			//下キー
	gKeys[VK_RIGHT] = GetAsyncKeyState(VK_RIGHT);		//右キー
	gKeys[VK_LEFT] = GetAsyncKeyState(VK_LEFT);			//左キー
	gKeys[VK_LBUTTON] = GetAsyncKeyState(VK_LBUTTON);	//マウス左ボタン
	gKeys[VK_RBUTTON] = GetAsyncKeyState(VK_RBUTTON);	//マウス右ボタン
	gKeys[PK_ENTER] = GetAsyncKeyState(PK_ENTER);		//Enterボタン
	gKeys[PK_W] = GetAsyncKeyState(PK_W);				//W
	gKeys[PK_A] = GetAsyncKeyState(PK_A);				//A
	gKeys[PK_S] = GetAsyncKeyState(PK_S);				//S
	gKeys[PK_D] = GetAsyncKeyState(PK_D);				//D
	gKeys[PK_R] = GetAsyncKeyState(PK_R);				//R
	gKeys[PK_SP] = GetAsyncKeyState(PK_SP);				//SPACE


	/*	1フレーム前のキー情報取得	*/
	m_OldGamePadState = m_GamePadState;

	/****	パッド状態取得	****/

	m_GamePadState[XINPUT_GAMEPAD_A] = false;
	m_GamePadState[XINPUT_GAMEPAD_B] = false;
	m_GamePadState[XINPUT_GAMEPAD_X] = false;
	m_GamePadState[XINPUT_GAMEPAD_Y] = false;
	m_GamePadState[XINPUT_GAMEPAD_DPAD_UP] = false;
	m_GamePadState[XINPUT_GAMEPAD_DPAD_DOWN] = false;
	m_GamePadState[XINPUT_GAMEPAD_DPAD_LEFT] = false;
	m_GamePadState[XINPUT_GAMEPAD_DPAD_RIGHT] = false;
	m_GamePadState[XINPUT_GAMEPAD_START] = false;
	m_GamePadState[XINPUT_GAMEPAD_BACK] = false;

	XInputGetState(0, &g_PadState);
	g_OldPadState = g_PadState;

	/*	左スティック入力なし	*/
	if ((g_PadState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_PadState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_PadState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE&&
			g_PadState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_PadState.Gamepad.sThumbLX = (SHORT)0.0f;
		g_PadState.Gamepad.sThumbLY = (SHORT)0.0f;
	}

	/*	右スティック入力なし	*/
	if ((g_PadState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		g_PadState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(g_PadState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE&&
			g_PadState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		g_PadState.Gamepad.sThumbRX = (SHORT)0.0f;
		g_PadState.Gamepad.sThumbRY = (SHORT)0.0f;
	}

}
