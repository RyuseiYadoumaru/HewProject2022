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
	//�|�[�Y��ʗp
	bool SetScale();
	bool PauseCursor_Move();
	int Get_Checker();
	void ChangeSelectScene();

	//���U���g��ʗp
	//bool ResultCursor_Move();

	int Cursor_Position;
	int Pause_Checker;
};

