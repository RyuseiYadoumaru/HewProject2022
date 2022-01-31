#pragma once
#include "ydmEngine.h"
using Create::Actor;
class Result :public Actor
{
public:

	string NowScene;
	int Result_Checker = 0;
	int Cursor_Position = 0;


	Result(string in_Name);
	bool Start() override;
	void ResultFront_init();//�摜�����ւ��p�i�������̂��߁j
	void ResultFront_init_GameEnd();
	void ResultBack_init();
	void ResultCursor_Init();//�摜�����ւ��p�i�������̂��߁j
	bool Result_On();

	bool ResultCursor_Move();//���U���g��ʗp
	int Get_Checker();
	void ChangeNextScene();
	void ChangeSelectScene();

	enum SceneTransition {//�V�[���؂�ւ��t���O
		NONE,
		STAGE_SELECT,
		RETRY,
		NEXT_SCENE
	};

	SceneTransition m_SceneTransition;

	bool S_flg;
	bool m_ShootingStarSE;
};

