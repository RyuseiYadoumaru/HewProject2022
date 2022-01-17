#pragma once
#include "ydmEngine.h"
using Create::Actor;
class Result :public Actor
{
public:

	string NowScene;
	int Result_Checker=0;
	int Cursor_Position=0;


	Result(string in_Name);
	bool Start() override;
	void ResultBack_init();//画像差し替え用（効率化のため）
	void ResultCursor_Init();//画像差し替え用（効率化のため）
	bool Result_On();
	
	bool ResultCursor_Move();//リザルト画面用
	int Get_Checker();
	void ChangeNextScene();
	void ChangeSelectScene();

	
};



