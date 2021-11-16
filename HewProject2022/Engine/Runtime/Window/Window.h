//*****************************************************************************
//!	@file	Engime/Runtime/Window/Window.h
//!	@brief	
//!	@note	�E�C���h�E�֘A�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <Windows.h>
#include "WindowCallBack.h"


class Window
{
private:

	HWND m_Handle;			//Windows�n���h��
	WindowCallBack* m_CallBack;	//�E�B���h�E�R�[���o�b�N

public:

	Window();
	~Window();

	static Window* Instance();

	bool SetWindowParam
	(
		HINSTANCE h_Instance,
		LPCSTR h_ClassName,
		unsigned long h_Style
	);

	bool SetWindow
	(
		LPCSTR h_ClassName,
		LPCSTR h_WindowName,
		HINSTANCE hInstance,
		const int Width,
		const int Height
	);

	static LRESULT CALLBACK WindowProc
	(
		HWND h_Handle,
		UINT h_Message,
		WPARAM h_WParam,
		LPARAM h_LParam
	);

	HWND GetHandle() const;
	WindowCallBack* GetCallBack() const;

};


