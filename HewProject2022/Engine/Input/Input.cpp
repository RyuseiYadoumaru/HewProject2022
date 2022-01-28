//*****************************************************************************
//!	@file	Engine/Input/Input.cpp
//!	@brief	
//!	@note	����
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "Input.h"


/****	�X�^�e�B�b�N�����o�ϐ�	****/
BYTE GameEngine::Input::m_KeyState[256];

XINPUT_STATE	GameEngine::Input::m_GamePadState;
XINPUT_STATE	GameEngine::Input::m_OldGamePadState;

XINPUT_VIBRATION GameEngine::Input::m_Vibration;
TIME			 GameEngine::Input::m_LeftTime = NULL;
TIME			 GameEngine::Input::m_RightTime = NULL;
TIME			 GameEngine::Input::m_Time = NULL;

/****	�O���[�o���ϐ�	****/
short gKeys[0xff];
short gOldKeys[0xff];



bool isDown;


/****	XInput���̓f�[�^	****/
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
//!	@brief	�g���K�[
//!	@param	�L�[�C���f�b�N�X
//!	@retval	���͔���
//==============================================================================
bool GameEngine::Input::GetKeyPress(int vkey)
{
	return (gKeys[vkey] & 0x8000) != 0;

}

//==============================================================================
//!	@fn		GetKeyTrigger
//!	@brief	�g���K�[
//!	@param	�L�[�C���f�b�N�X
//!	@retval	���͔���
//==============================================================================
bool GameEngine::Input::GetKeyTrigger(int vkey)
{
	bool condition1 = (gKeys[vkey] & 0x8000) != 0;
	bool condition2 = (gOldKeys[vkey] & 0x8000) == 0;

	return condition1 && condition2;
}

//==============================================================================
//!	@fn		GetControllerPress
//!	@brief	�R���g���[���v���X
//!	@param	�R���g���[���C���f�b�N�X
//!	@retval	���͔���
//==============================================================================
bool GameEngine::Input::GetControllerPress(int Xbuttom)
{
	//if (m_GamePadState.Gamepad.wButtons & Xbuttom)
	//{
	//	m_GamePadState[Xbuttom] = true;
	//	return true;
	//}
	return (m_GamePadState.Gamepad.wButtons & Xbuttom);
}

//==============================================================================
//!	@fn		GetControllerTrigger
//!	@brief	�R���g���[���g���K�[
//!	@param	�R���g���[���C���f�b�N�X
//!	@retval	���͔���
//==============================================================================
bool GameEngine::Input::GetControllerTrigger(int Xbuttom)
{


	bool condition1 = (m_GamePadState.Gamepad.wButtons & Xbuttom) != 0;
	bool condition2 = (m_OldGamePadState.Gamepad.wButtons & Xbuttom) == 0;

	return condition1 && condition2;

}

//==============================================================================
//!	@fn		GetControllerLeftStick
//!	@brief	���X�e�B�b�N����
//!	@param	
//!	@retval	�A�i���O�p�����[�^(0.0�`1.0)
//==============================================================================
DirectX::XMFLOAT2 GameEngine::Input::GetControllerLeftStick()
{
	DirectX::XMFLOAT2 stick;

	stick.x = m_GamePadState.Gamepad.sThumbLX / 32767.0f;
	stick.y = -m_GamePadState.Gamepad.sThumbLY / 32767.0f;

	return stick;
}

//==============================================================================
//!	@fn		GetControllerRightStick
//!	@brief	�E�X�e�B�b�N����
//!	@param	
//!	@retval	�A�i���O�p�����[�^(0.0�`1.0)
//==============================================================================
DirectX::XMFLOAT2 GameEngine::Input::GetControllerRightStick()
{
	DirectX::XMFLOAT2 stick;

	stick.x = m_GamePadState.Gamepad.sThumbRX / 32767.0f;
	stick.y = -m_GamePadState.Gamepad.sThumbRY / 32767.0f;

	return stick;
}

//==============================================================================
//!	@fn		LeftVibration
//!	@brief	���o�C�u���[�V����
//!	@param	�p���[
//!	@param	�o�C�u����(�ݒ肵�Ȃ�������STOP�܂Ńo�C�u����)
//!	@retval	
//==============================================================================
VIBRATION GameEngine::Input::LeftVibration(VIBRATION in_Power, TIME time)
{
	/*	���Ԑݒ�	*/
	m_LeftTime = time;

	m_Vibration.wLeftMotorSpeed = in_Power;
	XInputSetState(0, &m_Vibration);

	return in_Power;
}

//==============================================================================
//!	@fn		RightVibration
//!	@brief	�E�o�C�u���[�V����
//!	@param	�p���[
//!	@param	�o�C�u����(�ݒ肵�Ȃ�������STOP�܂Ńo�C�u����)
//!	@retval	
//==============================================================================
VIBRATION GameEngine::Input::RightVibration(VIBRATION in_Power, TIME time)
{
	/*	���Ԑݒ�	*/
	m_RightTime = time;

	m_Vibration.wRightMotorSpeed = in_Power;
	XInputSetState(0, &m_Vibration);
	return in_Power;
}

//==============================================================================
//!	@fn		Vibration
//!	@brief	�o�C�u���[�V����
//!	@param	�p���[
//!	@param	�o�C�u����(�ݒ肵�Ȃ�������STOP�܂Ńo�C�u����)
//!	@retval	
//==============================================================================
VIBRATION GameEngine::Input::Vibration(VIBRATION in_Power, TIME time)
{
	m_LeftTime = time;
	m_RightTime = time;
	m_Vibration.wLeftMotorSpeed = in_Power;
	m_Vibration.wRightMotorSpeed = in_Power / (WORD)2.0;
	XInputSetState(0, &m_Vibration);
	return in_Power;
}

//==============================================================================
//!	@fn		LeftVibrationStop
//!	@brief	���o�C�u���[�V�����X�g�b�v
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::Input::LeftVibrationStop()
{
	m_LeftTime = NULL;
	m_Vibration.wLeftMotorSpeed = (WORD)0.0;
	XInputSetState(0, &m_Vibration);
}

//==============================================================================
//!	@fn		RightVibrationStop
//!	@brief	�E�o�C�u���[�V�����X�g�b�v
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::Input::RightVibrationStop()
{
	m_RightTime = NULL;
	m_Vibration.wRightMotorSpeed = (WORD)0.0f;
	XInputSetState(0, &m_Vibration);

}

//==============================================================================
//!	@fn		KeyUpdate
//!	@brief	�L�[�X�V
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::Input::KeyUpdate()
{
	/*	1�t���[���O�̃L�[��Ԃ�ۑ�	*/
	memcpy(gOldKeys, gKeys, sizeof(gKeys));

	/****	�L�[�����擾	****/
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
	gKeys[VK_UP] = GetAsyncKeyState(VK_UP);				//��L�[
	gKeys[VK_DOWN] = GetAsyncKeyState(VK_DOWN);			//���L�[
	gKeys[VK_RIGHT] = GetAsyncKeyState(VK_RIGHT);		//�E�L�[
	gKeys[VK_LEFT] = GetAsyncKeyState(VK_LEFT);			//���L�[
	gKeys[VK_LBUTTON] = GetAsyncKeyState(VK_LBUTTON);	//�}�E�X���{�^��
	gKeys[VK_RBUTTON] = GetAsyncKeyState(VK_RBUTTON);	//�}�E�X�E�{�^��
	gKeys[PK_ENTER] = GetAsyncKeyState(PK_ENTER);		//Enter�{�^��
	gKeys[PK_W] = GetAsyncKeyState(PK_W);				//W
	gKeys[PK_A] = GetAsyncKeyState(PK_A);				//A
	gKeys[PK_S] = GetAsyncKeyState(PK_S);				//S
	gKeys[PK_D] = GetAsyncKeyState(PK_D);				//D
	gKeys[PK_R] = GetAsyncKeyState(PK_R);				//R
	gKeys[PK_Q] = GetAsyncKeyState(PK_Q);				//Q
	gKeys[PK_SP] = GetAsyncKeyState(PK_SP);				//SPACE
	gKeys[PK_BS] = GetAsyncKeyState(PK_BS);				//BackSCAPE


	/****	�p�b�h��Ԏ擾	****/
	/*	1�t���[���O�̃L�[���擾	*/
	m_OldGamePadState = m_GamePadState;
	XInputGetState(0, &m_GamePadState);

	/*	���X�e�B�b�N���͂Ȃ�	*/
	if ((m_GamePadState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_GamePadState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_GamePadState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE&&
			m_GamePadState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_GamePadState.Gamepad.sThumbLX = (SHORT)0.0f;
		m_GamePadState.Gamepad.sThumbLY = (SHORT)0.0f;
	}

	/*	�E�X�e�B�b�N���͂Ȃ�	*/
	if ((m_GamePadState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		m_GamePadState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_GamePadState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE&&
			m_GamePadState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_GamePadState.Gamepad.sThumbRX = (SHORT)0.0f;
		m_GamePadState.Gamepad.sThumbRY = (SHORT)0.0f;
	}

	/*	�o�C�u����	*/
	if (m_LeftTime == NULL);
	else if (m_LeftTime > 0.0f)	m_LeftTime -= GameTimer::deltaTime();
	else if (m_LeftTime <= 0.0f) LeftVibrationStop();

	if (m_RightTime == NULL);
	else if (m_RightTime > 0.0f)	m_RightTime -= GameTimer::deltaTime();
	else if (m_RightTime <= 0.0f) RightVibrationStop();

}
