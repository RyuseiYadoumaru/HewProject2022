//*****************************************************************************
//!	@file	Runtime/WindowCallBack.cpp
//!	@brief	
//!	@note	�E�B���h�E�R�[���o�b�N�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "WindowCallBack.h"
#include "../Tools/Log.h"
#include "../Tools/macro.h"
#include "../Tools/SystemTimer.h"
#include "../Application.h"

#include <string>
#include<sstream>

//==============================================================================
//!	@fn		OnKeyDown
//!	@brief	�L�[����
//!	@param	
//!	@retval	�I������
//==============================================================================
LRESULT WindowCallBack::OnKeyDown(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam)
{
	/*if (h_WParam == VK_ESCAPE)
	{
		int status = Log::LogCloseWindow(h_Handle, "�I�����܂����H");
		if (status == IDYES)
		{
			return DestroyWindow(h_Handle);
		}

	}*/
	return 0;
}

//==============================================================================
//!	@fn		OnClose
//!	@brief�@�~
//!	@param	
//!	@retval	�I������
//==============================================================================
LRESULT WindowCallBack::OnClose(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam)
{
	int status = Log::LogCloseWindow(h_Handle, "�I�����܂����H");
	if (status == IDYES)
	{
		return DestroyWindow(h_Handle);
	}
	return 0;
}

//==============================================================================
//!	@fn		OnWindowMove
//!	@brief�@�E�B���h�E�ړ���
//!	@param	
//!	@retval	�I������
//==============================================================================
LRESULT WindowCallBack::OnWindowMove(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam)
{
	return 0;
}

//==============================================================================
//!	@fn		OnDestroy
//!	@brief�@�I��
//!	@param	
//!	@retval 0
//==============================================================================
LRESULT WindowCallBack::OnDestroy(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam)
{
	PostQuitMessage(0);
	return 0;
}
