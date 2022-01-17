#pragma once
#include "ydmEngine.h"
#include "TutorialEffectAnim.h"

class TutorialEffectAnimController :public Create::AnimationController
{
public:
	bool Init() override;
	void Update() override;

private:
	bool m_MoveInitFirstFlg;//移動第一初期化フラグ
	bool m_MoveInitSecondFlg;//移動第二初期化フラグ

	bool m_JumpInitFirstFlg;//ジャンプ第一初期化フラグ
	bool m_JumpInitSecondFlg;//ジャンプ第二初期化フラグ
};

