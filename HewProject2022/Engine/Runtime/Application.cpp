//*****************************************************************************
//!	@file	Engime/Runtime/Application.cpp
//!	@brief	
//!	@note	アプリケーションクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Application.h"
#include "Window/Window.h"
#include "Tools/Log.h"
#include "Tools/SystemTimer.h"
#include "Graphics/Shader.h"
#include "Engine.h"
#include "Graphics/DirectXGraphics.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------

const char*	Application::WINDOW_TITLE = "ゲームタイトル";
const char*	Application::WINDOW_CLASS_NAME = "GameName";

#if 1
const uint32_t	Application::SCREEN_WIDTH = 1920;
const uint32_t	Application::SCREEN_HEIGHT = 1080;

#else
const uint32_t	Application::SCREEN_WIDTH = 1280;
const uint32_t	Application::SCREEN_HEIGHT = 720;

#endif // 1


const float		Application::FPS = 60.0f;


//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Application::Application()
{
	m_hWnd = NULL;
	m_hInstance = NULL;
	hr = NULL;
	isSucceed = FALSE;
}

//==============================================================================
//!	@fn		Instance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
Application* Application::Instance()
{
	static Application Instance;

	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	アプリケーション初期化
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Application::Init(HINSTANCE hInstance)
{
	//メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	// コンソールを割り当てる
	AllocConsole();

	// 標準出力の割り当て
	freopen_s(&fp, "CON", "w", stdout);

	Window* window = Window::Instance();


	/****	ウィンドウのパラメーター設定	****/
	isSucceed = window->SetWindowParam(hInstance, WINDOW_CLASS_NAME, CS_CLASSDC);

	if (isSucceed == false)
	{
		Log::LogError("アプリケーション初期化に失敗しました");
		return false;
	}

	/****	ウィンドウ作成	****/
	isSucceed = window->SetWindow
	(
		WINDOW_CLASS_NAME,
		WINDOW_TITLE,
		hInstance,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	);

	if (isSucceed == false)
	{
		Log::LogError("アプリケーション初期化に失敗しました");
		return false;
	}

	/****	DirectX11初期化	****/
	DirectXGraphics* DirectXGraphic = DirectXGraphics::Instance();

	bool sts = DirectXGraphic->Init(window->GetHandle(), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	if (sts == false)
	{
		Log::LogError(window->GetHandle(), "DirectXの初期化に失敗しました");
		return false;
	}


	/****	ハンドルデータ取得	****/
	m_hWnd = window->GetHandle();

	/****	アプリケーションインスタンス取得	****/
	m_hInstance = hInstance;

	return true;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	メインループ
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Application::MainLoop()
{
	/****	アプリケーション生成	****/
	Log* log = Log::Instance();
	SystemTimer* systemtimer = SystemTimer::Instance();
	GameEngine::Engine* engine = GameEngine::Engine::Instance();
	bool isEnd = false;


	/****	エンジン初期化	****/
	engine->Init();

	/****	エンジン更新	****/
	while (log->ExecMessage() == false && !isEnd)
	{
		engine->Update();
		systemtimer->SystemWait(FPS);
		log->FPSWindowText(m_hWnd, systemtimer->GetNowFPS());

	}

	/****	エンジン終了処理	****/
	engine->Uninit();

	return true;
}

//==============================================================================
//!	@fn		Uninit
//!	@brief	アプリケーション終了処理
//!	@param	
//!	@retval	
//==============================================================================
void Application::Uninit()
{
	/*	DirectX解放	*/
	DirectXGraphics* DirectXGraphic = DirectXGraphics::Instance();
	DirectXGraphic->Uninit();

	/*	標準出力クローズ	*/
	fclose(fp);
	/*	コンソール解放	*/
	::FreeConsole();
}

//==============================================================================
//!	@fn		GetHandle
//!	@brief	ハンドル取得
//!	@param	
//!	@retval	ハンドル
//==============================================================================
HWND Application::GetHandle() const
{
	return m_hWnd;
}