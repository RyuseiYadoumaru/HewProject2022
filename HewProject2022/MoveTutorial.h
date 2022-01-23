#pragma once
#include"ydmEngine.h"
#include"TutorialAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

#define MOVE_TUTORIAL_X (1100.0f)
#define MOVE_TUTORIAL_Y (830.0f)
#define MOVE_TUTORIAL_Z (0.0f)

class MoveTutorial : public Actor
{
public:
	MoveTutorial(string in_Name);
public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_StartMoveTutorialFlg; };//チュートリアル開始フラグ
	bool GetTutorialLookPerfectFlg() { return m_PerfectLookMoveTutorialFlg; };//チュートリアル完全に見えたフラグ

	bool GetTutorialEndStartFlg() { return m_EndStartMoveTutorialFlg; };//チュートリアル消え始めフラグ
	bool GetTutorialEndFlg() { return m_EndMoveTutorialFlg; };//チュートリアル終了フラグ

private:
	TutorialAnimController m_TutorialAnimController;

	//ここ変数名直したい
	bool m_StartMoveTutorialFlg;//移動チュートリアルが見え始めた
	bool m_PerfectLookMoveTutorialFlg;//移動チュートリアルが完全に見えた

	bool m_EndStartMoveTutorialFlg;//移動チュートリアルが消え始めた
	bool m_EndMoveTutorialFlg;//移動チュートリアルが完全に見えなくなった

};
