//*****************************************************************************
//!	@file	Engime/Runtime/Core/InputInfo.h
//!	@brief	
//!	@note	���͏��
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <windows.h>
#include <xinput.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "xinput.lib")

/****	�A�i���O�X�e�B�b�N�f�b�h�]�[��	****/
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE		7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE		8689

/****	XInput���̓f�[�^	****/
namespace XInput
{
	/*	�{�^��	*/
	namespace Buttom
	{
		extern const int A;

		extern const int B;

		extern const int X;

		extern const int Y;

		extern const int UP;

		extern const int DOWN;

		extern const int LEFT;

		extern const int RIGHT;

		extern const int START;

		extern const int BACK;

		extern const int LEFT_THUMB;

		extern const int RIGHT_THUMB;

		extern const int LEFT_SHOULDER;

		extern const int RIGHT_SHOULDER;

	}
}


/****	�L�[�{�[�h	****/
#define PK_ENTER				VK_RETURN
#define PK_ESC					VK_ESCAPE
#define PK_F1					VK_F1
#define PK_F2					VK_F2
#define PK_F3					VK_F3
#define PK_F4					VK_F4
#define PK_F5					VK_F5
#define PK_F6					VK_F6
#define PK_F7					VK_F7
#define PK_F8					VK_F8
#define PK_F9					VK_F9
#define PK_F10					VK_F10
#define PK_F11					VK_F11
#define PK_F12					VK_F12

#define PK_SP					VK_SPACE
#define PK_UP					VK_UP
#define PK_DOWN					VK_DOWN
#define PK_RIGHT				VK_RIGHT
#define PK_LEFT					VK_LEFT
#define PK_SHIFT				VK_SHIFT
#define PK_CTRL					VK_CONTROL
#define PK_ALT					VK_MENU
#define PK_BS					VK_BACK
#define PK_PAUSE				VK_PAUSE
#define PK_INS					VK_INSERT
#define PK_DEL					VK_DELETE
#define PK_TAB					VK_TAB
#define PK_NFER					VK_KANA		/* [���ϊ�]	*/
#define PK_XFER					VK_CONVERT	/* [�ϊ�]	*/
#define PK_0					0x30
#define PK_1					0x31
#define PK_2					0x32
#define PK_3					0x33
#define PK_4					0x34
#define PK_5					0x35
#define PK_6					0x36
#define PK_7					0x37
#define PK_8					0x38
#define PK_9					0x39
#define PK_NUMPAD0				VK_NUMPAD0	/* �e���L�[��[0]	*/
#define PK_NUMPAD1				VK_NUMPAD1	/* �e���L�[��[1]	*/
#define PK_NUMPAD2				VK_NUMPAD2	/* �e���L�[��[2]	*/
#define PK_NUMPAD3				VK_NUMPAD3	/* �e���L�[��[3]	*/
#define PK_NUMPAD4				VK_NUMPAD4	/* �e���L�[��[4]	*/
#define PK_NUMPAD5				VK_NUMPAD5	/* �e���L�[��[5]	*/
#define PK_NUMPAD6				VK_NUMPAD6	/* �e���L�[��[6]	*/
#define PK_NUMPAD7				VK_NUMPAD7	/* �e���L�[��[7]	*/
#define PK_NUMPAD8				VK_NUMPAD8	/* �e���L�[��[8]	*/
#define PK_NUMPAD9				VK_NUMPAD9	/* �e���L�[��[9]	*/
#define PK_A					0x41
#define PK_B					0x42
#define PK_C					0x43
#define PK_D					0x44
#define PK_E					0x45
#define PK_F					0x46
#define PK_G					0x47
#define PK_H					0x48
#define PK_I					0x49
#define PK_J					0x4A
#define PK_K					0x4B
#define PK_L					0x4C
#define PK_M					0x4D
#define PK_N					0x4E
#define PK_O					0x4F
#define PK_P					0x50
#define PK_Q					0x51
#define PK_R					0x52
#define PK_S					0x53
#define PK_T					0x54
#define PK_U					0x55
#define PK_V					0x56
#define PK_W					0x57
#define PK_X					0x58
#define PK_Y					0x59
#define PK_Z					0x5A
#define PK_LT					0x0BC		/* [,]	*/
#define PK_GT					0x0BE		/* [.]	*/
#define PK_SLUSH				0x0BF		/* [?]	*/
#define PK_DOT					VK_DECIMAL	/* �e���L�[��[.]	*/
#define PK_DIV					VK_DIVIDE	/* �e���L�[��[/]	*/
#define PK_BSLUSH				0x0E2		/* [_]	*/
#define PK_SEMICOLON			0x0BB		/* [;]	*/
#define PK_ADD					VK_ADD		/* �e���L�[��[+]	*/
#define PK_COLON				0x0BA		/* [:]	*/
#define PK_MUL					VK_MULTIPLY	/* �e���L�[��[*]	*/
#define PK_RBRACE				0x0DD		/* []]	*/
#define PK_ATMARK				0x0C0		/* [@]	*/
#define PK_LBRACE				0x0DB		/* [[]	*/
#define PK_MINUS				0x0BD		/* [-]	*/
#define PK_SUB					VK_SUBTRACT	/* �e���L�[��[-]	*/
#define PK_XOR					0x0DE		/* [^]	*/
#define PK_YEN					0x0DC		/* [\]	*/
#define PK_KANJI				0x0F3		/* [���p/�S�p]	*/
#define PK_CAPS					0x0F0		/* [�p��][�Ђ炪��]	*/

/****	�}�E�X	****/
#define PM_LEFT					VK_LBUTTON
#define PM_MID					VK_MBUTTON
#define PM_RIGHT				VK_RBUTTON
#define PM_CURX					0x0101
#define PM_CURY					0x0102