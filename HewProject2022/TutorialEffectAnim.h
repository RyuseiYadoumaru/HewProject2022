#pragma once
#include "ydmEngine.h"

using Create::Animation;

class TutorialEffectAnim :public Animation
{
public:
	/*	���	*///
	enum KIND
	{
		EFFECT,
		KIND_MAX
	};

	/*	�p�^�[��	*/
	enum TUTORIAL_ANIM//��
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

