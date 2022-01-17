#pragma once
#include"ydmEngine.h"
#include"TutorialEffectAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class TutorialEffect : public Actor
{
public:
	TutorialEffect(string in_Name);

public:
	bool Start() override;
	bool Update() override;

private:
	TutorialEffectAnimController m_TutoriaEffectlAnimController;

	bool m_MoveTutorialEffectFlg;//移動チュートリアルエフェクトが見えるかどうか
	bool m_JumpTutorialEffectFlg;//ジャンプチュートリアルエフェクトが見えるかどうか

};

