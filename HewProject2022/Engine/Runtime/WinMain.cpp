//*****************************************************************************
//!	@file	Engime/Runtime/WimMain.cpp
//!	@brief	Hal Event Week 2022 Project
//!	@brief	#出会いはまさかのマッチングアプリ
//!	@note	
//!	@author	YadoumaruRyusei	
//*****************************************************************************

#include "Application.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	メイン関数
//!	@param　hInstance     : このアプリケーションのインスタンスハンドル(識別子)
//!	@param	hPrevInstance : 常にNULL(16bit時代の名残り)
//!	@param	lpCmdLine     : コマンドラインから受け取った引数へのポインタ
//!	@param	nCmdShow      : アプリケーションの初期ウインドウ表示方法の指定
//!	@retval	0
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/****	アプリケーショ生成	****/
	Application* App = Application::Instance();

	/****	アプリケーション初期化	****/
	App->Init(hInstance);

	/****	ウィンドウ表示	****/
	ShowWindow(App->GetHandle(), nCmdShow);
	UpdateWindow(App->GetHandle());

	/****	メイン処理	****/
	App->MainLoop();

	/****	アプリケーション終了処理	****/
	App->Uninit();

	return 0;

}
