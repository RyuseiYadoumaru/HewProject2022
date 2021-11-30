//*****************************************************************************
//!	@file	Engime/Runtime/Window/Window.cpp
//!	@brief	
//!	@note	ウィンドウクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Window.h"
#include "../Tools/Log.h"
#include "../Tools/macro.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Window::Window()
{
	m_Handle = NULL;
	m_CallBack = nullptr;
}
//==============================================================================
//!	@fn		Destructor
//!	@brief	デストラクタ
//!	@param	
//==============================================================================
Window::~Window()
{
	SAFE_DELETE(m_CallBack);
}

//==============================================================================
//!	@fn		Instance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
Window* Window::Instance()
{
	static Window Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		SetWindowParam
//!	@brief	ウィンドウクラス登録
//!	@param	インスタンスハンドル
//!	@param	クラスネーム
//!	@param	ウィンドウスタイル
//!	@retval	true:成功　false:失敗
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

	//ウィンドウクラス登録
	if (!RegisterClassEx(&WndClassEx))
	{
		LOG_ERROR("ウィンドウクラス登録に失敗");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		SetWindow
//!	@brief	ウィンドウ生成
//!	@param	
//!	@retval	true:成功　false:失敗
//==============================================================================
bool Window::SetWindow(LPCSTR h_ClassName, LPCSTR h_WindowName, HINSTANCE hInstance, const int Width, const int Height)
{
	m_Handle = CreateWindowEx
	(
		0,												// 拡張ウィンドウスタイル
		h_ClassName,										// ウィンドウクラスの名前
		h_WindowName,									// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,							// ウィンドウスタイル
		CW_USEDEFAULT,									// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,									// ウィンドウの左上Ｙ座標 
		Width,											// ウィンドウの幅
		Height,											// ウィンドウの高さ
		NULL,											// 親ウィンドウのハンドル
		NULL,											// メニューハンドルまたは子ウィンドウID
		hInstance,										// インスタンスハンドル
		NULL											// ウィンドウ作成データ
	);

	//エラーチェック
	if (!m_Handle)
	{
		LOG_ERROR("ウィンドウ表示に失敗");
		return false;
	}

	/****	コールバック生成	****/
	m_CallBack = new WindowCallBack;

	return true;
}

//==============================================================================
//!	@fn		WindowProc
//!	@brief	ウィンドウプロージャー
//!	@param	ウィンドウハンドル
//!	@param	メッセージID
//!	@param	メッセージパラメータ
//!	@param	メッセージパラメータ
//!	@retval	終了結果ID
//==============================================================================
LRESULT Window::WindowProc(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam)
{
	/****	コールバック取得	****/
	WindowCallBack* callback = Window::Instance()->GetCallBack();
	if (callback == nullptr)
	{
		return DefWindowProc(h_Handle, h_Message, h_WParam, h_LParam);
	}

	/****	コールバック処理	****/
	switch (h_Message)
	{
		/****	ウィンドウ破棄	****/
	case WM_DESTROY:
		return callback->OnDestroy(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	システムキー押下	****/
	case WM_KEYDOWN:
		return callback->OnKeyDown(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	ウィンドウ移動	****/
	case WM_MOVE:
		return callback->OnWindowMove(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	ウィンドウ終了選択	****/
	case WM_CLOSE:
		return callback->OnClose(h_Handle, h_Message, h_WParam, h_LParam);
		break;

		/****	イベントなし	****/
	default:
		return DefWindowProc(h_Handle, h_Message, h_WParam, h_LParam);
		break;
	}

	return 0;
}

//==============================================================================
//!	@fn		GetHandle
//!	@brief	ハンドル取得
//!	@retval	ハンドル
//==============================================================================
HWND Window::GetHandle() const
{
	return m_Handle;
}

//==============================================================================
//!	@fn		GetCallBack
//!	@brief	コールバック取得
//!	@retval	コールバック
//==============================================================================
WindowCallBack* Window::GetCallBack() const
{
	return m_CallBack;
}


