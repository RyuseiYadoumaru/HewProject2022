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
	void ResultBack_init();//�摜�����ւ��p�i�������̂��߁j
	void ResultCursor_Init();//�摜�����ւ��p�i�������̂��߁j
	bool Result_On();
	
	bool ResultCursor_Move();//���U���g��ʗp
	int Get_Checker();
	void ChangeNextScene();
	void ChangeSelectScene();

	
};



