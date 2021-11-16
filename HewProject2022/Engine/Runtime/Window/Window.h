//*****************************************************************************
//!	@file	Engime/Runtime/Window/Window.h
//!	@brief	
//!	@note	ウインドウ関連クラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <Windows.h>
#include "WindowCallBack.h"


class Window
{
private:

	HWND m_Handle;			//Windowsハンドル
	WindowCallBack* m_CallBack;	//ウィンドウコールバック

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


