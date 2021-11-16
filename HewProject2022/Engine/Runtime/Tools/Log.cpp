//*****************************************************************************
//!	@file	Engine/Runtime/Tools/Log.cpp
//!	@brief	
//!	@note	ログを出力する
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Log.h"

//==============================================================================
//!	@fn		Instance
//!	@brief	ログを生成する
//!	@retval	インスタンス
//==============================================================================
Log* Log::Instance()
{
	static Log Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		LogError
//!	@brief	エラーログ出力
//!	@param	
//==============================================================================
void Log::LogError()
{
	MessageBoxA(NULL, "エラーが発生しました", "ERROR!", MB_OK);
}

//==============================================================================
//!	@fn		LogError
//!	@brief	エラーログ出力
//!	@param	エラーテキスト
//==============================================================================
void Log::LogError(const char* in_text)
{
	MessageBoxA(NULL, in_text, "ERROR!", MB_OK);

}

//==============================================================================
//!	@fn		LogError
//!	@brief	エラーログ出力
//!	@param	エラーテキスト
//!	@param	ウィンドウハンドル
//==============================================================================
void Log::LogError(HWND in_handle, const char * in_text)
{
	MessageBoxA(in_handle, in_text, "ERROR!", MB_OK);
}

//==============================================================================
//!	@fn		LogCloseWindow
//!	@brief	終了ログ出力
//!	@param	
//!	@retval	IDYES or IDNO
//==============================================================================
int Log::LogCloseWindow()
{
	return MessageBoxA(NULL, "終了しますか？", "CloseWindow?", MB_YESNO);
}

//==============================================================================
//!	@fn		LogCloseWindow
//!	@brief	終了ログ出力
//!	@param	終了テキスト
//!	@retval	IDYES or IDNO
//==============================================================================
int Log::LogCloseWindow(const char * in_text)
{
	return MessageBoxA(NULL, in_text, "CloseWindow?", MB_YESNO);
}

//==============================================================================
//!	@fn		LogCloseWindow
//!	@brief	終了ログ出力
//!	@param	終了テキスト
//!	@param	ウィンドウハンドル
//!	@retval	IDYES or IDNO
//==============================================================================
int Log::LogCloseWindow(HWND in_handle, const char * in_text)
{
	return MessageBoxA(in_handle, in_text, "CloseWindow?", MB_YESNO);
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	警告ログ出力
//!	@param	
//!	@param	
//!	@retval	IDRETRY or IDABORT or IDIGNORE
//==============================================================================
int Log::LogWarning()
{
	return MessageBoxA(NULL, "異常な処理が行われています", "WARNING!", MB_ABORTRETRYIGNORE);
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	警告ログ出力
//!	@param	警告テキスト
//!	@param	
//!	@retval	IDRETRY or IDABORT or IDIGNORE
//==============================================================================
int Log::LogWarning(const char * in_text)
{
	return MessageBoxA(NULL, in_text, "WARNING!", MB_ABORTRETRYIGNORE);
}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	警告ログ出力
//!	@param	警告テキスト
//!	@param	ウィンドウハンドル
//!	@retval	IDRETRY or IDABORT or IDIGNORE
//==============================================================================
int Log::LogWarning(HWND in_handle, const char * in_text)
{
	return MessageBoxA(in_handle, in_text, "WARNING!", MB_ABORTRETRYIGNORE);
}

//==============================================================================
//!	@fn		ChangeWindowText
//!	@brief	ウィンドウテキスト変更
//!	@param	ウィンドウハンドル
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Log::ChangeWindowText(HWND in_handle)
{
	if (in_handle == NULL)
	{
		return false;
	}

	return SetWindowTextA(in_handle, "サンプルウィンドウ");
}
//==============================================================================
//!	@fn		ChangeWindowText
//!	@brief	ウィンドウテキスト変更
//!	@param	ウィンドウハンドル
//!	@param　ウィンドウテキスト
//!	@retval	true:正常終了　false:異常終了
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
//!	@brief	FPSをウィンドウテキストに表示
//!	@param	ウィンドウハンドル
//!	@param　現在のFPS
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Log::FPSWindowText(HWND in_handle, float in_NowFPS)
{
	if (in_handle == NULL)
	{
		return false;
	}

	/****	FPS表示設定	****/
	std::stringstream ss;
	ss << "FPS：" << in_NowFPS;
	std::string text = ss.str();

	return SetWindowTextA(in_handle, text.c_str());
}

//==============================================================================
//!	@fn		ExecMessage
//!	@brief	終了メッセージ処理
//!	@param	
//!	@retval	インスタンス
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
			// 呼び出し側スレッドのメッセージキューからメッセージを取得
			TranslateMessage(&WindowMessage);
			DispatchMessage(&WindowMessage);
		}
	}

	return false;
}
