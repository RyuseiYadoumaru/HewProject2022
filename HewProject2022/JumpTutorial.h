#pragma once
#include"ydmEngine.h"
#include"JumpTutorialAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

#define	JUMP_TUTORIAL_X (1477.0f)
#define JUMP_TUTORIAL_Y (830.0f)
#define JUMP_TUTORIAL_Z (0.0f)

class JumpTutorial :public Actor
{
public:
	JumpTutorial(string in_Name);

public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_StartJumpTutorialFlg; };//チュートリアル開始フラグ
	bool GetTutorialLookPerfectFlg() { return m_PerfectLookJumpTutorialFlg; };//チュートリアル完全に見えたフラグ

	bool GetTutorialEndStartFlg() { return m_EndStartJumpTutorialFlg; };//チュートリアル消え始めフラグ
	bool GetTutorialEndFlg() { return m_EndJumpTutorialFlg; };//チュートリアル終了フラグ

private:
	//ジャンプ用アニメーションコントローラーを持たせる
	JumpTutorialAnimController m_JumpTutorialAnimController;

	//ここ変数名直したい
	bool m_StartJumpTutorialFlg;//ジャンプチュートリアルが見え始めた
	bool m_PerfectLookJumpTutorialFlg;//ジャンプチュートリアルが完全に見えた

	bool m_EndStartJumpTutorialFlg;//ジャンプチュートリアルが消え始めた
	bool m_EndJumpTutorialFlg;//ジャンプチュートリアルが完全に見えなくなった
};

