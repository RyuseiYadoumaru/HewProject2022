#pragma once
#include"ydmEngine.h"
#include"Tutorial_XYAnimController.h"

#define Y_TUTORIAL_X (1400.0f)
#define Y_TUTORIAL_Y (730.0f)
#define Y_TUTORIAL_Z (0.0f)

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class Tutorial_Y :public Actor
{
public:
	Tutorial_Y(string in_Name);
public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_Start_Y_TutorialFlg; };//チュートリアル開始フラグ
	bool GetTutorialLookPerfectFlg() { return m_PerfectLook_Y_TutorialFlg; };//チュートリアル完全に見えたフラグ

	bool GetTutorialEndStartFlg() { return m_EndStart_Y_TutorialFlg; };//チュートリアル消え始めフラグ
	bool GetTutorialEndFlg() { return m_End_Y_TutorialFlg; };//チュートリアル終了フラグ

private:
	Tutorial_XYAnimController m_Tutorial_XYAnimController;//Xのアニメーション流用

	//ここ変数名直したい
	bool m_Start_Y_TutorialFlg;//Yチュートリアルが見え始めた
	bool m_PerfectLook_Y_TutorialFlg;//Yチュートリアルが完全に見えた

	bool m_EndStart_Y_TutorialFlg;//Yチュートリアルが消え始めた
	bool m_End_Y_TutorialFlg;//Yチュートリアルが完全に見えなくなった

};