#pragma once
#include "ydmEngine.h"

using Create::Animation;

class TutorialEffectAnim :public Animation
{
public:
	/*	種類	*///
	enum KIND
	{
		EFFECT,
		KIND_MAX
	};

	/*	パターン	*/
	enum TUTORIAL_ANIM//横
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_MAX
	};
public:
	void Init() override;
};

