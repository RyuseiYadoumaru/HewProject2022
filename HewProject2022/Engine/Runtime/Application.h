//*****************************************************************************
//!	@file	Engime/Runtime/Application.h
//!	@brief	
//!	@note	アプリケーションクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include <Windows.h>
#include <string>
#include<sstream>

/****	アプリケーション	****/
class Application
{
public:

	static const char*		WINDOW_TITLE;				// ウィンドウタイトル
	static const char*		WINDOW_CLASS_NAME;			// クラスネーム

	static const uint32_t		SCREEN_WIDTH;				// スクリーン横幅
	static const uint32_t		SCREEN_HEIGHT;				// スクリーン縦幅

	static const float			FPS;						// フレームカウント

private:

	HWND m_hWnd;				//Windowsハンドル
	HINSTANCE m_hInstance;		//アプリケーション実体

	HRESULT hr;					//終了ステータス
	BOOL isSucceed;				//処理正常終了

public:

	Application();

	static Application* Instance();

	bool Init(HINSTANCE hInstance);		//初期化

	bool MainLoop();

	void Uninit();		//終了処理


	HWND GetHandle() const;


};