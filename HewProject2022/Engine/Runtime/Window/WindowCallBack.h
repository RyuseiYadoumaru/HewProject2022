//*****************************************************************************
//!	@file	Engine/Runtime/Window/WindowCallBack.h
//!	@brief	
//!	@note	ウィンドウコールバッククラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include	<Windows.h>

class WindowCallBack
{
public:

	LRESULT OnKeyDown(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam);
	LRESULT OnClose(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam);
	LRESULT OnWindowMove(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam);
	LRESULT OnDestroy(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam);
};


