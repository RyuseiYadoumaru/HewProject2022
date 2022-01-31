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
	void ResultFront_init();//画像差し替え用（効率化のため）
	void ResultFront_init_GameEnd();
	void ResultBack_init();
	void ResultCursor_Init();//画像差し替え用（効率化のため）
	bool Result_On();

	bool ResultCursor_Move();//リザルト画面用
	int Get_Checker();
	void ChangeNextScene();
	void ChangeSelectScene();

	enum SceneTransition {//シーン切り替えフラグ
		NONE,
		STAGE_SELECT,
		RETRY,
		NEXT_SCENE
	};

	SceneTransition m_SceneTransition;

	bool S_flg;
	bool m_ShootingStarSE;
};

