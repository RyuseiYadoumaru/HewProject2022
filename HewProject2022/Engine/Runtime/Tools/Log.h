//*****************************************************************************
//!	@file	Engine/Runtime/Tools/Log.h
//!	@brief	
//!	@note	ÉçÉOÇèoóÕÇ∑ÇÈ
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <Windows.h>
#include <string>
#include <sstream>

#define LOG_ERROR(text) MessageBoxA(NULL, text, "ERROR!", MB_OK);
#define LOG_CLOSE_WINDOW(text) MessageBoxA(NULL, text, "CloseWindow?", MB_YESNO );
#define LOG_WARNING(text) MessageA(NULL. text, "WARNING!", MB_ABORTRETRYIGNORE);

class Log
{
private:

	MSG WindowMessage;

public:

	static Log* Instance();

	static void LogError();
	static void LogError(const char* in_text);
	static void LogError(HWND in_handle, const char* in_text);

	static int LogCloseWindow();
	static int LogCloseWindow(const char* in_text);
	static int LogCloseWindow(HWND in_handle, const char* in_text);

	static int LogWarning();
	static int LogWarning(const char* in_text);
	static int LogWarning(HWND in_handle, const char* in_text);

	bool ChangeWindowText(HWND in_handle);
	bool ChangeWindowText(HWND in_handle, const char* in_text);

	bool FPSWindowText(HWND in_handle, float in_NowFPS);

	bool ExecMessage();
};