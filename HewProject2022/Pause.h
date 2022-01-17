#pragma once
#include"ydmEngine.h"
using Create::Actor;

class Pause :public Actor
{
public:
	string NowScene;
	Pause(string in_Name);
	bool Start() override;
	
	bool Pause_On();
	bool Pause_Off();
	//ポーズ画面用
	bool SetScale();
	bool PauseCursor_Move();
	int Get_Checker();
	void ChangeSelectScene();

	//リザルト画面用
	//bool ResultCursor_Move();

	int Cursor_Position;
	int Pause_Checker;
};

