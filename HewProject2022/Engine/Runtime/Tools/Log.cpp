//*****************************************************************************
//!	@file	Engine/Runtime/Tools/Log.cpp
//!	@brief	
//!	@note	���O���o�͂���
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Log.h"

//==============================================================================
//!	@fn		Instance
//!	@brief	���O�𐶐�����
//!	@retval	�C���X�^���X
//==============================================================================
Log* Log::Instance()
{
	static Log Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		LogError
//!	@brief	�G���[���O�o��
//!	@param	
//==============================================================================
void Log::LogError()
{
	MessageBoxA(NULL, "�G���[���������܂���", "ERROR!", MB_OK);
}

//==============================================================================
//!	@fn		LogError
//!	@brief	�G���[���O�o��
//!	@param	�G���[�e�L�X�g
//==============================================================================
void Log::LogError(const char* in_text)
{
	MessageBoxA(NULL, in_text, "ERROR!", MB_OK);

}

//==============================================================================
//!	@fn		LogError
//!	@brief	�G���[���O�o��
//!	@param	�G���[�e�L�X�g
//!	@param	�E�B���h�E�n���h��
//==============================================================================
void Log::LogError(HWND in_handle, const char * in_text)
{
	MessageBoxA(in_handle, in_text, "ERROR!", MB_OK);
}

//==============================================================================
//!	@fn		LogCloseWindow
//!	@brief	�I�����O�o��
//!	@param	
//!	@retval	IDYES or IDNO
//==============================================================================
int Log::LogCloseWindow()
{
	return MessageBoxA(NULL, "�I�����܂����H", "CloseWindow?", MB_YESNO);
}

//==============================================================================
//!	@fn		LogCloseWindow
//!	@brief	�I�����O�o��
//!	@param	�I���e�L�X�g
//!	@retval	IDYES or IDNO
//==============================================================================
int Log::LogCloseWindow(const char * in_text)
{
	return MessageBoxA(NULL, in_text, "CloseWindow?", MB_YESNO);
}

//==============================================================================
//!	@fn		LogCloseWindow
//!	@brief	�I�����O�o��
//!	@param	�I���e�L�X�g
//!	@param	�E�B���h�E�n���h��
//!	@retval	IDYES or IDNO
//==============================================================================
int Log::LogCloseWindow(HWND in_handle, const char * in_text)
{
	return MessageBoxA(in_handle, in_text, "CloseWindow?", MB_YESNO);
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	�x�����O�o��
//!	@param	
//!	@param	
//!	@retval	IDRETRY or IDABORT or IDIGNORE
//==============================================================================
int Log::LogWarning()
{
	return MessageBoxA(NULL, "�ُ�ȏ������s���Ă��܂�", "WARNING!", MB_ABORTRETRYIGNORE);
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	�x�����O�o��
//!	@param	�x���e�L�X�g
//!	@param	
//!	@retval	IDRETRY or IDABORT or IDIGNORE
//==============================================================================
int Log::LogWarning(const char * in_text)
{
	return MessageBoxA(NULL, in_text, "WARNING!", MB_ABORTRETRYIGNORE);
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	�x�����O�o��
//!	@param	�x���e�L�X�g
//!	@param	�E�B���h�E�n���h��
//!	@retval	IDRETRY or IDABORT or IDIGNORE
//==============================================================================
int Log::LogWarning(HWND in_handle, const char * in_text)
{
	return MessageBoxA(in_handle, in_text, "WARNING!", MB_ABORTRETRYIGNORE);
}

//==============================================================================
//!	@fn		ChangeWindowText
//!	@brief	�E�B���h�E�e�L�X�g�ύX
//!	@param	�E�B���h�E�n���h��
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Log::ChangeWindowText(HWND in_handle)
{
	if (in_handle == NULL)
	{
		return false;
	}

	return SetWindowTextA(in_handle, "�T���v���E�B���h�E");
}
//==============================================================================
//!	@fn		ChangeWindowText
//!	@brief	�E�B���h�E�e�L�X�g�ύX
//!	@param	�E�B���h�E�n���h��
//!	@param�@�E�B���h�E�e�L�X�g
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Log::ChangeWindowText(HWND in_handle, const char * in_text)
{
	if (in_handle == NULL)
	{
		return false;
	}

	return SetWindowTextA(in_handle, in_text);
}
//==============================================================================
//!	@fn		FPSWindowText
//!	@brief	FPS���E�B���h�E�e�L�X�g�ɕ\��
//!	@param	�E�B���h�E�n���h��
//!	@param�@���݂�FPS
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Log::FPSWindowText(HWND in_handle, float in_NowFPS)
{
	if (in_handle == NULL)
	{
		return false;
	}

	/****	FPS�\���ݒ�	****/
	std::stringstream ss;
	ss << "FPS�F" << in_NowFPS;
	std::string text = ss.str();

	return SetWindowTextA(in_handle, text.c_str());
}

//==============================================================================
//!	@fn		ExecMessage
//!	@brief	�I�����b�Z�[�W����
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
bool Log::ExecMessage()
{
	if (PeekMessage(&WindowMessage, nullptr, 0, 0, PM_REMOVE) != 0)
	{
		if (WindowMessage.message == WM_QUIT)
		{
			return true;
		}
		else
		{
			// �Ăяo�����X���b�h�̃��b�Z�[�W�L���[���烁�b�Z�[�W���擾
			TranslateMessage(&WindowMessage);
			DispatchMessage(&WindowMessage);
		}
	}

	return false;
}
