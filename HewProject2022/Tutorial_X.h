#pragma once
#include"ydmEngine.h"
#include"Tutorial_XYAnimController.h"

#define X_TUTORIAL_X (2190.0f)
#define X_TUTORIAL_Y (730.0f)
#define X_TUTORIAL_Z (0.0f)

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class Tutorial_X :public Actor
{
public:
	Tutorial_X(string in_Name);
public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_Start_X_TutorialFlg; };//チュートリアル開始フラグ
	bool GetTutorialLookPerfectFlg() { return m_PerfectLook_X_TutorialFlg; };//チュートリアル完全に見えたフラグ

	bool GetTutorialEndStartFlg() { return m_EndStart_X_TutorialFlg; };//チュートリアル消え始めフラグ
	bool GetTutorialEndFlg() { return m_End_X_TutorialFlg; };//チュートリアル終了フラグ

private:
	Tutorial_XYAnimController m_Tutorial_XYAnimController;

	//ここ変数名直したい
	bool m_Start_X_TutorialFlg;//Xチュートリアルが見え始めた
	bool m_PerfectLook_X_TutorialFlg;//Xチュートリアルが完全に見えた

	bool m_EndStart_X_TutorialFlg;//Xチュートリアルが消え始めた
	bool m_End_X_TutorialFlg;//Xチュートリアルが完全に見えなくなった

};

