//*****************************************************************************
//!	@file	Engime/Runtime/Window/Window.cpp
//!	@brief	
//!	@note	�E�B���h�E�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Window.h"
#include "../Tools/Log.h"
#include "../Tools/macro.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Window::Window()
{
	m_Handle = NULL;
	m_CallBack = nullptr;
}
//==============================================================================
//!	@fn		Destructor
//!	@brief	�f�X�g���N�^
//!	@param	
//==============================================================================
Window::~Window()
{
	SAFE_DELETE(m_CallBack);
}

//==============================================================================
//!	@fn		Instance
//!	@brief	�C���X�^���X�擾
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
Window* Window::Instance()
{
	static Window Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		SetWindowParam
//!	@brief	�E�B���h�E�N���X�o�^
//!	@param	�C���X�^���X�n���h��
//!	@param	�N���X�l�[��
//!	@param	�E�B���h�E�X�^�C��
//!	@retval	true:�����@false:���s
//==============================================================================
bool Window::SetWindowParam(HINSTANCE h_Instance, LPCSTR h_ClassName, unsigned long h_Style)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = h_Style;
	WndClassEx.lpfnWndProc = WindowProc;
	WndClassEx.cbClsExtra = 0L;
	WndClassEx.cbWndExtra = 0L;
	WndClassEx.hInstance = h_Instance;
	WndClassEx.hIcon = nullptr;
	WndClassEx.hCursor = nullptr;
	WndClassEx.hbrBackground = nullptr;
	WndClassEx.lpszMenuName = nullptr;
	WndClassEx.lpszClassName = h_ClassName;
	WndClassEx.hIconSm = NULL;

	//�E�B���h�E�N���X�o�^
	if (!RegisterClassEx(&WndClassEx))
	{
		LOG_ERROR("�E�B���h�E�N���X�o�^�Ɏ��s");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		SetWindow
//!	@brief	�E�B���h�E����
//!	@param	
//!	@retval	true:�����@false:���s
//==============================================================================
bool Window::SetWindow(LPCSTR h_ClassName, LPCSTR h_WindowName, HINSTANCE hInstance, const int Width, const int Height)
{
	m_Handle = CreateWindowEx
	(
		0,												// �g���E�B���h�E�X�^�C��
		h_ClassName,										// �E�B���h�E�N���X�̖��O
		h_WindowName,									// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,							// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,									// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,									// �E�B���h�E�̍���x���W 
		Width,											// �E�B���h�E�̕�
		Height,											// �E�B���h�E�̍���
		NULL,											// �e�E�B���h�E�̃n���h��
		NULL,											// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,										// �C���X�^���X�n���h��
		NULL											// �E�B���h�E�쐬�f�[�^
	);

	//�G���[�`�F�b�N
	if (!m_Handle)
	{
		LOG_ERROR("�E�B���h�E�\���Ɏ��s");
		return false;
	}

	/****	�R�[���o�b�N����	****/
	m_CallBack = new WindowCallBack;

	return true;
}

//==============================================================================
//!	@fn		WindowProc
//!	@brief	�E�B���h�E�v���[�W���[
//!	@param	�E�B���h�E�n���h��
//!	@param	���b�Z�[�WID
//!	@param	���b�Z�[�W�p�����[�^
//!	@param	���b�Z�[�W�p�����[�^
//!	@retval	�I������ID
//==============================================================================
LRESULT Window::WindowProc(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam)
{
	/****	�R�[���o�b�N�擾	****/
	WindowCallBack* callback = Window::Instance()->GetCallBack();
	if (callback == nullptr)
	{
		return DefWindowProc(h_Handle, h_Message, h_WParam, h_LParam);
	}

	/****	�R�[���o�b�N����	****/
	switch (h_Message)
	{
		/****	�E�B���h�E�j��	****/
	case WM_DESTROY:
		return callback->OnDestroy(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	�V�X�e���L�[����	****/
	case WM_KEYDOWN:
		return callback->OnKeyDown(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	�E�B���h�E�ړ�	****/
	case WM_MOVE:
		return callback->OnWindowMove(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	�E�B���h�E�I���I��	****/
	case WM_CLOSE:
		return callback->OnClose(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	�C�x���g�Ȃ�	****/
	default:
		return DefWindowProc(h_Handle, h_Message, h_WParam, h_LParam);
		break;
	}

	return 0;
}

//==============================================================================
//!	@fn		GetHandle
//!	@brief	�n���h���擾
//!	@retval	�n���h��
//==============================================================================
HWND Window::GetHandle() const
{
	return m_Handle;
}

//==============================================================================
//!	@fn		GetCallBack
//!	@brief	�R�[���o�b�N�擾
//!	@retval	�R�[���o�b�N
//==============================================================================
WindowCallBack* Window::GetCallBack() const
{
	return m_CallBack;
}


